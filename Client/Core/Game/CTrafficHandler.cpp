//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CTrafficHandler.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CTrafficHandler.h"
#include <Patcher/CPatcher.h>
#include <CCore.h>
extern CCore * g_pCore;

CTrafficLights::eGTATrafficLightState dwTrafficLightState;

void __declspec(naked) GetTrafficLightState1()
{
	_asm	pushad;

	dwTrafficLightState = g_pCore->GetGame()->GetTrafficLights()->GetTrafficLightState();

	_asm	popad;
	_asm	mov eax, dwTrafficLightState;
	_asm	retn;
}

void __declspec(naked) GetTrafficLightState2()
{
	_asm	pushad;

	dwTrafficLightState = g_pCore->GetGame()->GetTrafficLights()->GetTrafficLightAltState();

	_asm	popad;
	_asm	mov eax, dwTrafficLightState;
	_asm	retn;
}

CTrafficHandler::CTrafficHandler()
{
	m_pTrafficLights = new CTrafficLights;
}

CTrafficHandler::~CTrafficHandler()
{
	SAFE_DELETE(m_pTrafficLights);
}

void CTrafficHandler::InstallTrafficLightsHook()
{
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetTrafficLightState1, (DWORD)GetTrafficLightState1);
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetTrafficLightState2, (DWORD)GetTrafficLightState2);
}

void CTrafficHandler::InstallTrafficHook()
{
	// Disable parked cars
    CPatcher::InstallRetnPatch(COffsets::IV_Hook__DisableParkedCars);

    // Disable emergency services and garbage trucks
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableEmergencyAndGarbageTrucks, 5);

    // Disable vehicle entries
    *(DWORD *)(COffsets::IV_Hook__DisableVehicleEntries) = 0x0CC2C033;
    *(BYTE *)(COffsets::IV_Hook__DisableVehicleEntries + 0x4) = 0x00;

    // Disable vehicle exits
    *(BYTE *)(COffsets::IV_Hook__DisableVehicleExists) = 0xEB;

    // Disable random peds and vehicles
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableRandomPedsAndVehicles_1, 5);
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableRandomPedsAndVehicles_2, 5);
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableRandomPedsAndVehicles_3, 5);

    // Disable scenario peds
    *(BYTE *)(COffsets::IV_Hook__DisableScenarioPeds) = 0xB8; // mov eax,
    *(DWORD *)(COffsets::IV_Hook__DisableScenarioPeds + 0x1) = 0x0; // 0
    *(BYTE *)(COffsets::IV_Hook__DisableScenarioPeds + 0x5) = 0xC3; // retn

    // Disable fake cars
    CPatcher::InstallRetnPatch(COffsets::IV_Hook__DisableFakeCars);
}