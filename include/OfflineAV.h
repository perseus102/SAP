#pragma once

BOOLEAN IsAntiVirusDriverInstalled();
BOOLEAN IsAntiVirusServiceInstalled();

LPCWSTR GetActiveEngine(BOOLEAN bRefresh = FALSE);
DWORD SetActiveEngineA(const char *engine_name);
BOOLEAN IsActiveOfflineAVEngine(const wchar_t *engine_name);
BOOLEAN IsActiveOfflineAVEngineA(const char *engine_name);

BOOLEAN IsOfflineAVEnabled();
DWORD SetOfflineAVDisable(BOOLEAN bDisabled);

BOOLEAN IsAviraEnabled();

