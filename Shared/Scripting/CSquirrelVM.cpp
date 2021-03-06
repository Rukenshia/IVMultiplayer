//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CSquirrelVM.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelVM.h"
#include <CLogFile.h>
#include <SharedUtility.h>
#include <assert.h>
#include <Squirrel/sqvm.h>
#include <Squirrel/sqstdio.h>
#include <Squirrel/sqstdaux.h>
#include "CScriptArgument.h"


void PrintFunction(SQVM * pVM, const char * szFormat, ...)
{
        va_list args;
        char szBuffer[512];
        va_start(args, szFormat);
        vsnprintf(szBuffer, sizeof(szBuffer), szFormat, args);
        va_end(args);
        CLogFile::Print(szBuffer);
}

CSquirrelVM::CSquirrelVM(CResource * pResource)
	: CScriptVM(pResource),
	m_iStackIndex(2)
{
	m_pVM = sq_open(1024);

	// Register the default error handlers
	sqstd_seterrorhandlers(m_pVM);

	// Push the root table onto the stack
	sq_pushroottable(m_pVM);

	sq_setprintfunc(m_pVM, PrintFunction, PrintFunction);
}


CSquirrelVM::~CSquirrelVM()
{
	// Pop the root table from the stack
	sq_pop(m_pVM, 1);

	// Close the squirrel VM
	sq_close(m_pVM);
	m_pVM = NULL;
}


bool CSquirrelVM::LoadScript(CString script)
{
	CString scriptPath( "%s/%s", GetResource()->GetResourceDirectoryPath().Get(), script.Get());
	
	if(!SharedUtility::Exists(script.Get()) && SQ_FAILED(sqstd_dofile( m_pVM, scriptPath.Get(), SQFalse, SQTrue )))
	{
		CLogFile::Printf("[%s] Failed to load file %s.", GetResource()->GetName().Get(), script.Get());
		return false;
	}
	CLogFile::Printf("\t[%s] Loaded file %s.", GetResource()->GetName().Get(), script.Get());
	return true;
}

bool CSquirrelVM::LoadScripts(std::list<CScript> scripts)
{
	for(auto Script : scripts)
		if (Script.GetType() != CLIENT_SCRIPT)
			if (!LoadScript(Script.GetScriptFileName()))
				return false;
	
	return true;
}

void CSquirrelVM::RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount, const char* szFunctionTemplate, bool bPushRootTable)
{
	// Push the function name onto the stack
	sq_pushstring(m_pVM, szFunctionName, -1);

	// Create a new function
	sq_newclosure(m_pVM, (SQFUNCTION)pfnFunction, 0);

	// Set the function parameter template and count
	if(iParameterCount != -1)
	{
		CString strTypeMask;

		// TODO: Change parameter
		CString strFunctionTemplate = szFunctionTemplate;
		if(strFunctionTemplate.IsNotEmpty())
			strTypeMask.Format(".%s", strFunctionTemplate.Get());

		sq_setparamscheck(m_pVM, (iParameterCount + 1), strTypeMask.Get());
	}
	sq_setnativeclosurename(m_pVM, -1, szFunctionName);
	// Create a new slot
	sq_createslot(m_pVM, -3);
}

void CSquirrelVM::RegisterScriptClass(const char* className, scriptFunction pfnFunction, const char* baseClass)
{
	int n = 0;
	int oldtop = sq_gettop(m_pVM);
	sq_pushroottable(m_pVM);
	sq_pushstring(m_pVM, className, -1);

	if(baseClass) {
		sq_pushstring(m_pVM, baseClass, -1);
		if(SQ_FAILED(sq_get(m_pVM, -3))) { // make sure base exists
			sq_settop(m_pVM, oldtop);
			return;
		}
	}
	if(SQ_FAILED(sq_newclass(m_pVM, baseClass ? 1 : 0))) {
		sq_settop(m_pVM, oldtop);
		return;
	}

	sq_pushstring(m_pVM, _SC("constructor"), -1);
	sq_newclosure(m_pVM, (SQFUNCTION)pfnFunction, 0);
	sq_newslot(m_pVM, -3, false); // Add the constructor method

	sq_newslot(m_pVM, -3, SQFalse); // Add the class

	sq_pop(m_pVM, m_pVM->_top-oldtop);
}

SQInteger deleteClassInstance(SQUserPointer ptr, SQInteger size)
{
    int *p = static_cast<int *>(ptr);
    delete p;

    return 0;
}

void CSquirrelVM::SetClassInstance(const char* szClassName, void * pInstance)
{
	HSQOBJECT instance;
	sq_resetobject(&instance);
	sq_getstackobj(m_pVM, -1, &instance);

	sq_pushroottable(m_pVM);
	sq_pushstring(m_pVM, szClassName, -1);
	sq_get(m_pVM, -2);
	sq_setinstanceup(m_pVM, -1, (SQUserPointer *)pInstance);
	sq_setreleasehook(m_pVM, -1, deleteClassInstance);
}

void* CSquirrelVM::GetClassInstance(const char* szClassName)
{
	SQUserPointer pInstance = NULL;

	if(SQ_FAILED(sq_getinstanceup(m_pVM, -1, &pInstance, NULL)))
		pInstance = NULL;

	return pInstance;
}

void CSquirrelVM::RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount, const char* szFunctionTemplate)
{
	sq_pushstring(m_pVM, szFunctionName, -1);
	sq_newclosure(m_pVM, (SQFUNCTION)pfnFunction, 0);
	sq_newslot(m_pVM, -3, SQFalse);
}

void CSquirrelVM::Pop(bool& b)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_BOOL)
	{
		SQBool sqB;
		sq_getbool(m_pVM, m_iStackIndex++, &sqB);
		b = sqB ? true : false;
		return;
	}

	b = false;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(bool& b, bool bDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_BOOL)
	{
		SQBool sqB;
		sq_getbool(m_pVM, m_iStackIndex++, &sqB);
		b = sqB ? true : false;
		return;
	} else {
		if(argType == OT_NULL)
		{
			b = bDefaultValue;
			m_iStackIndex++;
			return;
		}
	}
	b = false;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(int& i)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, &i);
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(int& i, int iDefaultValue)
{
		SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, &i);
		return;
	}else {
		if(argType == OT_NULL)
		{
			i = iDefaultValue;
			m_iStackIndex++;
			return;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(float& f)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_FLOAT)
	{
		sq_getfloat(m_pVM, m_iStackIndex++, &f);
		return;
	}

	f = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(float& f, float fDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_FLOAT)
	{
		sq_getfloat(m_pVM, m_iStackIndex++, &f);
		return;
	} else {
		if(argType == OT_NULL) {
			f = fDefaultValue;
			m_iStackIndex++;
			return;
		}
	}

	f = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(CString& str)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_STRING)
	{
		const char* c = NULL;
		sq_getstring(m_pVM, m_iStackIndex++, &c);
		str = c;
		return;
	}
	
	str = "";
	m_iStackIndex++;
}

void CSquirrelVM::Pop(CString& str, CString strDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_STRING)
	{
		const char* c = NULL;
		sq_getstring(m_pVM, m_iStackIndex++, &c);
		str = c;
		return;
	} else {
		if(argType == OT_NULL) {
			str = strDefaultValue;
		}
	}

	str = "";
	m_iStackIndex++;
}

void CSquirrelVM::Pop(CVector3& vec)
{
	Pop(vec.fX);
	Pop(vec.fY);
	Pop(vec.fZ);
}


void CSquirrelVM::Pop(CVector3& vec, CVector3 vecDefaultValue)
{
	Pop(vec.fX, vecDefaultValue.fX);
	Pop(vec.fY, vecDefaultValue.fY);
	Pop(vec.fZ, vecDefaultValue.fZ);
}


void CSquirrelVM::Push(const bool& b)
{
	sq_pushbool(m_pVM, b);
}

void CSquirrelVM::Push(const int& i)
{
	sq_pushinteger(m_pVM, i);
}

void CSquirrelVM::Push(const float& f)
{
	sq_pushfloat(m_pVM, f);
}

void CSquirrelVM::Push(const CString& str)
{
	sq_pushstring(m_pVM, str.Get(), str.GetLength());
}

void CSquirrelVM::Push(const CVector3& vec)
{
	Push(vec.fX);
	Push(vec.fY);
	Push(vec.fZ);
}

void CSquirrelVM::PushArray(const CScriptArguments &array)
{
	sq_newarray(m_pVM, 0);
	for(auto pArgument : array.m_Arguments)
	{
		pArgument->Push(this);

		sq_arrayappend(m_pVM, -2);
	}
}


void CSquirrelVM::PushTable(const CScriptArguments &table)
{
	sq_newtable(m_pVM);
	for(auto iter = table.m_Arguments.begin(); iter != table.m_Arguments.end(); iter++)
	{
		(*iter)->Push(this);
		++iter;
		(*iter)->Push(this);
		sq_createslot(m_pVM, -3);
	}
}

CScriptArgument::ArgumentType CSquirrelVM::GetType(int idx)
{
	SQVM* VM = reinterpret_cast<CSquirrelVM*>(this)->GetVM();
	SQObjectPtr obj = stack_get(VM, idx);
	switch(obj._type)
	{
	case OT_FLOAT:
		{
				return CScriptArgument::ArgumentType::ST_FLOAT;
		}
	case OT_INTEGER:
		{
				return CScriptArgument::ArgumentType::ST_INTEGER;
		}
	case OT_BOOL:
		{
			return CScriptArgument::ArgumentType::ST_BOOL;
		}
	case OT_STRING:
		{
			return CScriptArgument::ArgumentType::ST_STRING;
		}
	case OT_TABLE:
		{
			return CScriptArgument::ArgumentType::ST_TABLE;
		}	
	case OT_ARRAY:
		{
			return CScriptArgument::ArgumentType::ST_ARRAY;
		}
	case OT_NULL:
	default:
		return CScriptArgument::ArgumentType::ST_INVALID;
	}
}