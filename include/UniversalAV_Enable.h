#pragma once

BOOLEAN IsUniversalAVAvailable();
BOOLEAN IsUniversalAVEnabled();

BOOLEAN IsUniversalAVEnabledForAutoFullSystemScan();
BOOLEAN IsUniversalAVEnabledForManualScanning();
BOOLEAN IsUniversalAVEnabledForRealTimeScanning();

void ShowUniversalAVStatus(HWND hwnd, LPCWSTR title);

//UAV Scan Settings
DWORD EnableUniversalAVAutoFullSystemScan(BOOLEAN bEnable);
DWORD EnableUniversalAVForOnDemandScanning(BOOLEAN bEnable);
DWORD EnableUniversalAVForRealTimeScanning(BOOLEAN bEnable);

DWORD EnableUniversalAVAutoUpload(BOOLEAN bEnable);
BOOLEAN IsUniversalAVAutoUploadEnabled(OPTIONAL BOOLEAN bIgnoreUAVAvailable = FALSE);

#ifdef _SERVICE_H_
DWORD EnableUniversalAV(BOOLEAN bEnable);
#endif
