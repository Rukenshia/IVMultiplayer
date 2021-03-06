//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
//
// File: CIVModelManager.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVModelManager.h"
#include <CCore.h>
#include <Game/COffsets.h>
#include <IV/CIVScriptEnums.h>

extern CCore * g_pCore;

int CIVModelManager::GetModelIndexFromHash( DWORD dwModelHash )
{
	int iModelIndex = -1;
	int * pModelIndex = &iModelIndex;

	_asm	push pModelIndex;
	_asm	push dwModelHash;
	_asm	call COffsets::FUNC_GetModelIndexFromHash;
	_asm	add esp, 8;

	return iModelIndex;
}

void CIVModelManager::RequestModel( int iModelIndex, DWORD dwFlags )
{
	unsigned int uiFileTypeIndex = *(unsigned int *)COffsets::VAR_ResourceTypeWdrIndex;

	_asm	push dwFlags;
	_asm	push uiFileTypeIndex;
	_asm	push iModelIndex;
	_asm	call COffsets::FUNC_RequestResource;
	_asm	add esp, 0Ch;
}

void CIVModelManager::LoadRequestedModels( )
{
	_asm	push 1;
	_asm	call COffsets::FUNC_LoadAllResources;
	_asm	add esp, 4;
}

bool CIVModelManager::HasModelLoaded( int iModelIndex )
{
	unsigned int uiFileTypeIndex = *(unsigned int *)COffsets::VAR_ResourceTypeWdrIndex;
	bool bLoaded = false;

	_asm	push uiFileTypeIndex;
	_asm	push iModelIndex;
	_asm	call COffsets::FUNC_HasResourceLoaded;
	_asm	add esp, 8;
	_asm	mov bLoaded, al;

	return bLoaded;
}

void CIVModelManager::ReleaseModel( int iModelIndex )
{
	unsigned int uiFileTypeIndex = *(unsigned int *)COffsets::VAR_ResourceTypeWdrIndex;

	_asm	push uiFileTypeIndex;
	_asm	push iModelIndex;
	_asm	call COffsets::FUNC_ReleaseResource;
	_asm	add esp, 8;
}

DWORD CIVModelManager::VehicleIdToModelHash(int iModelId)
{
	switch(iModelId)
	{
		case 0: return CIVScript::MODEL_ADMIRAL;
		case 1: return CIVScript::MODEL_AIRTUG;
		case 2: return CIVScript::MODEL_AMBULANCE;
		case 3: return CIVScript::MODEL_BANSHEE;
		case 4: return CIVScript::MODEL_BENSON;
		case 5: return CIVScript::MODEL_BIFF;
		case 6: return CIVScript::MODEL_BLISTA;
		case 7: return CIVScript::MODEL_BOBCAT;
		case 8: return CIVScript::MODEL_BOXVILLE;
		case 9: return CIVScript::MODEL_BUCCANEER;
		case 10: return CIVScript::MODEL_BURRITO;
		case 11: return CIVScript::MODEL_BURRITO2;
		case 12: return CIVScript::MODEL_BUS;
		case 13: return CIVScript::MODEL_CABBY;
		case 14: return CIVScript::MODEL_CAVALCADE;
		case 15: return CIVScript::MODEL_CHAVOS;
		case 16: return CIVScript::MODEL_COGNOSCENTI;
		case 17: return CIVScript::MODEL_COMET;
		case 18: return CIVScript::MODEL_COQUETTE;
		case 19: return CIVScript::MODEL_DF8;
		case 20: return CIVScript::MODEL_DILETTANTE;
		case 21: return CIVScript::MODEL_DUKES;
		case 22: return CIVScript::MODEL_E109;
		case 23: return CIVScript::MODEL_EMPEROR;
		case 24: return CIVScript::MODEL_EMPEROR2;
		case 25: return CIVScript::MODEL_ESPERANTO;
		case 26: return CIVScript::MODEL_FACTION;
		case 27: return CIVScript::MODEL_FBI;
		case 28: return CIVScript::MODEL_FELTZER;
		case 29: return CIVScript::MODEL_FEROCI;
		case 30: return CIVScript::MODEL_FEROCI2;
		case 31: return CIVScript::MODEL_FIRETRUK;
		case 32: return CIVScript::MODEL_FLATBED;
		case 33: return CIVScript::MODEL_FORTUNE;
		case 34: return CIVScript::MODEL_FORKLIFT;
		case 35: return CIVScript::MODEL_FUTO;
		case 36: return CIVScript::MODEL_FXT;
		case 37: return CIVScript::MODEL_HABANERO;
		case 38: return CIVScript::MODEL_HAKUMAI;
		case 39: return CIVScript::MODEL_HUNTLEY;
		case 40: return CIVScript::MODEL_INFERNUS;
		case 41: return CIVScript::MODEL_INGOT;
		case 42: return CIVScript::MODEL_INTRUDER;
		case 43: return CIVScript::MODEL_LANDSTALKER;
		case 44: return CIVScript::MODEL_LOKUS;
		case 45: return CIVScript::MODEL_MANANA;
		case 46: return CIVScript::MODEL_MARBELLA;
		case 47: return CIVScript::MODEL_MERIT;
		case 48: return CIVScript::MODEL_MINIVAN;
		case 49: return CIVScript::MODEL_MOONBEAM;
		case 50: return CIVScript::MODEL_MRTASTY;
		case 51: return CIVScript::MODEL_MULE;
		case 52: return CIVScript::MODEL_NOOSE;
		case 53: return CIVScript::MODEL_NSTOCKADE;
		case 54: return CIVScript::MODEL_ORACLE;
		case 55: return CIVScript::MODEL_PACKER;
		case 56: return CIVScript::MODEL_PATRIOT;
		case 57: return CIVScript::MODEL_PERENNIAL;
		case 58: return CIVScript::MODEL_PERENNIAL2;
		case 59: return CIVScript::MODEL_PEYOTE;
		case 60: return CIVScript::MODEL_PHANTOM;
		case 61: return CIVScript::MODEL_PINNACLE;
		case 62: return CIVScript::MODEL_PMP600;
		case 63: return CIVScript::MODEL_POLICE;
		case 64: return CIVScript::MODEL_POLICE2;
		case 65: return CIVScript::MODEL_POLPATRIOT;
		case 66: return CIVScript::MODEL_PONY;
		case 67: return CIVScript::MODEL_PREMIER;
		case 68: return CIVScript::MODEL_PRES;
		case 69: return CIVScript::MODEL_PRIMO;
		case 70: return CIVScript::MODEL_PSTOCKADE;
		case 71: return CIVScript::MODEL_RANCHER;
		case 72: return CIVScript::MODEL_REBLA;
		case 73: return CIVScript::MODEL_RIPLEY;
		case 74: return CIVScript::MODEL_ROMERO;
		case 75: return CIVScript::MODEL_ROM;
		case 76: return CIVScript::MODEL_RUINER;
		case 77: return CIVScript::MODEL_SABRE;
		case 78: return CIVScript::MODEL_SABRE2;
		case 79: return CIVScript::MODEL_SABREGT;
		case 80: return CIVScript::MODEL_SCHAFTER;
		case 81: return CIVScript::MODEL_SENTINEL;
		case 82: return CIVScript::MODEL_SOLAIR;
		case 83: return CIVScript::MODEL_SPEEDO;
		case 84: return CIVScript::MODEL_STALION;
		case 85: return CIVScript::MODEL_STEED;
		case 86: return CIVScript::MODEL_STOCKADE;
		case 87: return CIVScript::MODEL_STRATUM;
		case 88: return CIVScript::MODEL_STRETCH;
		case 89: return CIVScript::MODEL_SULTAN;
		case 90: return CIVScript::MODEL_SULTANRS;
		case 91: return CIVScript::MODEL_SUPERGT;
		case 92: return CIVScript::MODEL_TAXI;
		case 93: return CIVScript::MODEL_TAXI2;
		case 94: return CIVScript::MODEL_TRASH;
		case 95: return CIVScript::MODEL_TURISMO;
		case 96: return CIVScript::MODEL_URANUS;
		case 97: return CIVScript::MODEL_VIGERO;
		case 98: return CIVScript::MODEL_VIGERO2;
		case 99: return CIVScript::MODEL_VINCENT;
		case 100: return CIVScript::MODEL_VIRGO;
		case 101: return CIVScript::MODEL_VOODOO;
		case 102: return CIVScript::MODEL_WASHINGTON;
		case 103: return CIVScript::MODEL_WILLARD;
		case 104: return CIVScript::MODEL_YANKEE;
		case 105: return CIVScript::MODEL_BOBBER;
		case 106: return CIVScript::MODEL_FAGGIO;
		case 107: return CIVScript::MODEL_HELLFURY;
		case 108: return CIVScript::MODEL_NRG900;
		case 109: return CIVScript::MODEL_PCJ;
		case 110: return CIVScript::MODEL_SANCHEZ;
		case 111: return CIVScript::MODEL_ZOMBIEB;
		case 112: return CIVScript::MODEL_ANNIHILATOR;
		case 113: return CIVScript::MODEL_MAVERICK;
		case 114: return CIVScript::MODEL_POLMAV;
		case 115: return CIVScript::MODEL_TOURMAV;
		case 116: return CIVScript::MODEL_DINGHY;
		case 117: return CIVScript::MODEL_JETMAX;
		case 118: return CIVScript::MODEL_MARQUIS;
		case 119: return CIVScript::MODEL_PREDATOR;
		case 120: return CIVScript::MODEL_REEFER;
		case 121: return CIVScript::MODEL_SQUALO;
		case 122: return CIVScript::MODEL_TUGA;
		case 123: return CIVScript::MODEL_TROPIC;
		case 124: return CIVScript::MODEL_CABLECAR;
		case 125: return CIVScript::MODEL_SUBWAY_LO;
		case 126: return CIVScript::MODEL_SUBWAY_HI;
		case 127: return CIVScript::MODEL_SLAMVAN;
		case 128: return CIVScript::MODEL_CADDY;
		case 129: return CIVScript::MODEL_APC;
		case 130: return CIVScript::MODEL_SUPERD;
		case 131: return CIVScript::MODEL_SUPERD2;
		case 132: return CIVScript::MODEL_SERRANO;
		case 133: return CIVScript::MODEL_SERRANO2;
		case 134: return CIVScript::MODEL_BUFFALO;
		case 135: return CIVScript::MODEL_AVAN;
		case 136: return CIVScript::MODEL_SCHAFTER2;
		case 137: return CIVScript::MODEL_SCHAFTER3;
		case 138: return CIVScript::MODEL_BULLET;
		case 139: return CIVScript::MODEL_TAMPA;
		case 140: return CIVScript::MODEL_CAVALCADE2;
		case 141: return CIVScript::MODEL_F620;
		case 142: return CIVScript::MODEL_LIMO2;
		case 143: return CIVScript::MODEL_POLICE3;
		case 144: return CIVScript::MODEL_POLICEW;
		case 145: return CIVScript::MODEL_POLICE4;
		case 146: return CIVScript::MODEL_POLICEB;
		case 147: return CIVScript::MODEL_HEXER;
		case 148: return CIVScript::MODEL_FAGGIO2;
		case 149: return CIVScript::MODEL_BATI2;
		case 150: return CIVScript::MODEL_VADER;
		case 151: return CIVScript::MODEL_AKUMA;
		case 152: return CIVScript::MODEL_HAKUCHOU;
		case 153: return CIVScript::MODEL_DOUBLE;
		case 154: return CIVScript::MODEL_BUZZARD;
		case 155: return CIVScript::MODEL_SWIFT;
		case 156: return CIVScript::MODEL_SKYLIFT;
		case 157: return CIVScript::MODEL_SMUGGLER;
		case 158: return CIVScript::MODEL_FLOATER;
		case 159: return CIVScript::MODEL_BLADE;
		case 160: return CIVScript::MODEL_GBURRITO;
		case 161: return CIVScript::MODEL_TOWTRUCK;
		case 162: return CIVScript::MODEL_PACKER2;
		case 163: return CIVScript::MODEL_PBUS;
		case 164: return CIVScript::MODEL_YANKEE2;
		case 165: return CIVScript::MODEL_RHAPSODY;
		case 166: return CIVScript::MODEL_REGINA;
		case 167: return CIVScript::MODEL_ANGEL;
		case 168: return CIVScript::MODEL_BATI;
		case 169: return CIVScript::MODEL_DAEMON;
		case 170: return CIVScript::MODEL_DIABOLUS;
		case 171: return CIVScript::MODEL_DOUBLE2;
		case 172: return CIVScript::MODEL_HAKUCHOU2;
		case 173: return CIVScript::MODEL_INNOVATION;
		case 174: return CIVScript::MODEL_LYCAN;
		case 175: return CIVScript::MODEL_NIGHTBLADE;
		case 176: return CIVScript::MODEL_REVENANT;
		case 177: return CIVScript::MODEL_WAYFARER;
		case 178: return CIVScript::MODEL_WOLFSBANE;
	}

	return 0x00;
}

int CIVModelManager::ModelHashToVehicleId(DWORD dwModelHash)
{
	switch(dwModelHash)
	{
		case CIVScript::MODEL_ADMIRAL: return 0;
		case CIVScript::MODEL_AIRTUG: return 1;
		case CIVScript::MODEL_AMBULANCE: return 2;
		case CIVScript::MODEL_BANSHEE: return 3;
		case CIVScript::MODEL_BENSON: return 4;
		case CIVScript::MODEL_BIFF: return 5;
		case CIVScript::MODEL_BLISTA: return 6;
		case CIVScript::MODEL_BOBCAT: return 7;
		case CIVScript::MODEL_BOXVILLE: return 8;
		case CIVScript::MODEL_BUCCANEER: return 9;
		case CIVScript::MODEL_BURRITO: return 10;
		case CIVScript::MODEL_BURRITO2: return 11;
		case CIVScript::MODEL_BUS: return 12;
		case CIVScript::MODEL_CABBY: return 13;
		case CIVScript::MODEL_CAVALCADE: return 14;
		case CIVScript::MODEL_CHAVOS: return 15;
		case CIVScript::MODEL_COGNOSCENTI: return 16;
		case CIVScript::MODEL_COMET: return 17;
		case CIVScript::MODEL_COQUETTE: return 18;
		case CIVScript::MODEL_DF8: return 19;
		case CIVScript::MODEL_DILETTANTE: return 20;
		case CIVScript::MODEL_DUKES: return 21;
		case CIVScript::MODEL_E109: return 22;
		case CIVScript::MODEL_EMPEROR: return 23;
		case CIVScript::MODEL_EMPEROR2: return 24;
		case CIVScript::MODEL_ESPERANTO: return 25;
		case CIVScript::MODEL_FACTION: return 26;
		case CIVScript::MODEL_FBI: return 27;
		case CIVScript::MODEL_FELTZER: return 28;
		case CIVScript::MODEL_FEROCI: return 29;
		case CIVScript::MODEL_FEROCI2: return 30;
		case CIVScript::MODEL_FIRETRUK: return 31;
		case CIVScript::MODEL_FLATBED: return 32;
		case CIVScript::MODEL_FORTUNE: return 33;
		case CIVScript::MODEL_FORKLIFT: return 34;
		case CIVScript::MODEL_FUTO: return 35;
		case CIVScript::MODEL_FXT: return 36;
		case CIVScript::MODEL_HABANERO: return 37;
		case CIVScript::MODEL_HAKUMAI: return 38;
		case CIVScript::MODEL_HUNTLEY: return 39;
		case CIVScript::MODEL_INFERNUS: return 40;
		case CIVScript::MODEL_INGOT: return 41;
		case CIVScript::MODEL_INTRUDER: return 42;
		case CIVScript::MODEL_LANDSTALKER: return 43;
		case CIVScript::MODEL_LOKUS: return 44;
		case CIVScript::MODEL_MANANA: return 45;
		case CIVScript::MODEL_MARBELLA: return 46;
		case CIVScript::MODEL_MERIT: return 47;
		case CIVScript::MODEL_MINIVAN: return 48;
		case CIVScript::MODEL_MOONBEAM: return 49;
		case CIVScript::MODEL_MRTASTY: return 50;
		case CIVScript::MODEL_MULE: return 51;
		case CIVScript::MODEL_NOOSE: return 52;
		case CIVScript::MODEL_NSTOCKADE: return 53;
		case CIVScript::MODEL_ORACLE: return 54;
		case CIVScript::MODEL_PACKER: return 55;
		case CIVScript::MODEL_PATRIOT: return 56;
		case CIVScript::MODEL_PERENNIAL: return 57;
		case CIVScript::MODEL_PERENNIAL2: return 58;
		case CIVScript::MODEL_PEYOTE: return 59;
		case CIVScript::MODEL_PHANTOM: return 60;
		case CIVScript::MODEL_PINNACLE: return 61;
		case CIVScript::MODEL_PMP600: return 62;
		case CIVScript::MODEL_POLICE: return 63;
		case CIVScript::MODEL_POLICE2: return 64;
		case CIVScript::MODEL_POLPATRIOT: return 65;
		case CIVScript::MODEL_PONY: return 66;
		case CIVScript::MODEL_PREMIER: return 67;
		case CIVScript::MODEL_PRES: return 68;
		case CIVScript::MODEL_PRIMO: return 69;
		case CIVScript::MODEL_PSTOCKADE: return 70;
		case CIVScript::MODEL_RANCHER: return 71;
		case CIVScript::MODEL_REBLA: return 72;
		case CIVScript::MODEL_RIPLEY: return 73;
		case CIVScript::MODEL_ROMERO: return 74;
		case CIVScript::MODEL_ROM: return 75;
		case CIVScript::MODEL_RUINER: return 76;
		case CIVScript::MODEL_SABRE: return 77;
		case CIVScript::MODEL_SABRE2: return 78;
		case CIVScript::MODEL_SABREGT: return 79;
		case CIVScript::MODEL_SCHAFTER: return 80;
		case CIVScript::MODEL_SENTINEL: return 81;
		case CIVScript::MODEL_SOLAIR: return 82;
		case CIVScript::MODEL_SPEEDO: return 83;
		case CIVScript::MODEL_STALION: return 84;
		case CIVScript::MODEL_STEED: return 85;
		case CIVScript::MODEL_STOCKADE: return 86;
		case CIVScript::MODEL_STRATUM: return 87;
		case CIVScript::MODEL_STRETCH: return 88;
		case CIVScript::MODEL_SULTAN: return 89;
		case CIVScript::MODEL_SULTANRS: return 90;
		case CIVScript::MODEL_SUPERGT: return 91;
		case CIVScript::MODEL_TAXI: return 92;
		case CIVScript::MODEL_TAXI2: return 93;
		case CIVScript::MODEL_TRASH: return 94;
		case CIVScript::MODEL_TURISMO: return 95;
		case CIVScript::MODEL_URANUS: return 96;
		case CIVScript::MODEL_VIGERO: return 97;
		case CIVScript::MODEL_VIGERO2: return 98;
		case CIVScript::MODEL_VINCENT: return 99;
		case CIVScript::MODEL_VIRGO: return 100;
		case CIVScript::MODEL_VOODOO: return 101;
		case CIVScript::MODEL_WASHINGTON: return 102;
		case CIVScript::MODEL_WILLARD: return 103;
		case CIVScript::MODEL_YANKEE: return 104;
		case CIVScript::MODEL_BOBBER: return 105;
		case CIVScript::MODEL_FAGGIO: return 106;
		case CIVScript::MODEL_HELLFURY: return 107;
		case CIVScript::MODEL_NRG900: return 108;
		case CIVScript::MODEL_PCJ: return 109;
		case CIVScript::MODEL_SANCHEZ: return 110;
		case CIVScript::MODEL_ZOMBIEB: return 111;
		case CIVScript::MODEL_ANNIHILATOR: return 112;
		case CIVScript::MODEL_MAVERICK: return 113;
		case CIVScript::MODEL_POLMAV: return 114;
		case CIVScript::MODEL_TOURMAV: return 115;
		case CIVScript::MODEL_DINGHY: return 116;
		case CIVScript::MODEL_JETMAX: return 117;
		case CIVScript::MODEL_MARQUIS: return 118;
		case CIVScript::MODEL_PREDATOR: return 119;
		case CIVScript::MODEL_REEFER: return 120;
		case CIVScript::MODEL_SQUALO: return 121;
		case CIVScript::MODEL_TUGA: return 122;
		case CIVScript::MODEL_TROPIC: return 123;
		case CIVScript::MODEL_CABLECAR: return 124;
		case CIVScript::MODEL_SUBWAY_LO: return 125;
		case CIVScript::MODEL_SUBWAY_HI: return 126;
		case CIVScript::MODEL_SLAMVAN: return 127;
		case CIVScript::MODEL_CADDY: return 128;
		case CIVScript::MODEL_APC: return 129;
		case CIVScript::MODEL_SUPERD: return 130;
		case CIVScript::MODEL_SUPERD2: return 131;
		case CIVScript::MODEL_SERRANO: return 132;
		case CIVScript::MODEL_SERRANO2: return 133;
		case CIVScript::MODEL_BUFFALO: return 134;
		case CIVScript::MODEL_AVAN: return 135;
		case CIVScript::MODEL_SCHAFTER2: return 136;
		case CIVScript::MODEL_SCHAFTER3: return 137;
		case CIVScript::MODEL_BULLET: return 138;
		case CIVScript::MODEL_TAMPA: return 139;
		case CIVScript::MODEL_CAVALCADE2: return 140;
		case CIVScript::MODEL_F620: return 141;
		case CIVScript::MODEL_LIMO2: return 142;
		case CIVScript::MODEL_POLICE3: return 143;
		case CIVScript::MODEL_POLICEW: return 144;
		case CIVScript::MODEL_POLICE4: return 145;
		case CIVScript::MODEL_POLICEB: return 146;
		case CIVScript::MODEL_HEXER: return 147;
		case CIVScript::MODEL_FAGGIO2: return 148;
		case CIVScript::MODEL_BATI2: return 149;
		case CIVScript::MODEL_VADER: return 150;
		case CIVScript::MODEL_AKUMA: return 151;
		case CIVScript::MODEL_HAKUCHOU: return 152;
		case CIVScript::MODEL_DOUBLE: return 153;
		case CIVScript::MODEL_BUZZARD: return 154;
		case CIVScript::MODEL_SWIFT: return 155;
		case CIVScript::MODEL_SKYLIFT: return 156;
		case CIVScript::MODEL_SMUGGLER: return 157;
		case CIVScript::MODEL_FLOATER: return 158;
		case CIVScript::MODEL_BLADE: return 159;
		case CIVScript::MODEL_GBURRITO: return 160;
		case CIVScript::MODEL_TOWTRUCK: return 161;
		case CIVScript::MODEL_PACKER2: return 162;
		case CIVScript::MODEL_PBUS: return 163;
		case CIVScript::MODEL_YANKEE2: return 164;
		case CIVScript::MODEL_RHAPSODY: return 165;
		case CIVScript::MODEL_REGINA: return 166;
		case CIVScript::MODEL_ANGEL: return 167;
		case CIVScript::MODEL_BATI: return 168;
		case CIVScript::MODEL_DAEMON: return 169;
		case CIVScript::MODEL_DIABOLUS: return 170;
		case CIVScript::MODEL_DOUBLE2: return 171;
		case CIVScript::MODEL_HAKUCHOU2: return 172;
		case CIVScript::MODEL_INNOVATION: return 173;
		case CIVScript::MODEL_LYCAN: return 174;
		case CIVScript::MODEL_NIGHTBLADE: return 175;
		case CIVScript::MODEL_REVENANT: return 176;
		case CIVScript::MODEL_WAYFARER: return 177;
		case CIVScript::MODEL_WOLFSBANE: return 178;
	}

	return -1;
}