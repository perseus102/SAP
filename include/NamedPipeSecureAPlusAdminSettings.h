#pragma once
#ifndef _UAV_UPLOAD_LIMIT_H_
#define UPLOAD_LIMIT_1GB 1073741824
#define UPLOAD_LIMIT_100MB 104857600
#define UPLOAD_LIMIT_10MB 10485760
#define UPLOAD_LIMIT_UNLIMITED 0xffffffffffffffff
#endif

DWORD SecureaplusAdminSettingsExit();
DWORD SecureaplusAdminSettingsSetSoftwareUpdateMethod(DWORD method);
DWORD SecureaplusAdminSettingsSetSignaureUpdateMethod(DWORD method);

DWORD SecureaplusAdminSettingsSaveClamAVConf(LPCWSTR signature_server, LPCWSTR proxy_server, LPCWSTR proxy_port);
DWORD SecureaplusAdminSettingsSaveClamAVConfV2(BOOLEAN bUseSystemDefaultProxy, LPCWSTR signature_server, LPCWSTR proxy_server, LPCWSTR proxy_port);

//To support 3rd Party Offline AV
DWORD SecureaplusAdminSettingsSaveProxySettings(BOOLEAN bUseSystemDefaultProxy, LPCWSTR proxy_server, LPCWSTR proxy_port);


//
// Inclusions
//
DWORD SecureaplusAdminSettingsAddFileExtInclusion(LPCWSTR filename_ext);
DWORD SecureaplusAdminSettingsDeleteFileExtInclusion(LPCWSTR filename_ext);

//
// Exclusions
//
DWORD SecureaplusAdminSettingsAddFileExclusion(LPCWSTR filename);

///////////////////////////////////////////////////////////////////
//
// Application Whitelisting
//
//0 - not tursted by cert
//1 - trusted by OS
//2 - trusted by name
//3 - trusted by thumbprint
DWORD SecureaplusAdminSettingsSetTrustByCertificate(DWORD method);

// Trusted Accounts
DWORD SecureaplusAdminSettingsAddTrustedGroup(LPCWSTR name);
DWORD SecureaplusAdminSettingsDeleteTrustedGroup(LPCWSTR name);
DWORD SecureaplusAdminSettingsAddTrustedUser(LPCWSTR name);
DWORD SecureaplusAdminSettingsDeleteTrustedUser(LPCWSTR name);

// Ping
DWORD SecureaplusAdminSettingsPing();

// Observation Mode
DWORD SecureaplusAdminSettingsSetObservationMode(DWORD mode);

//
// Restricted Applications
DWORD SecureaplusAdminSettingsAddRestrictedApp(LPCWSTR filename, LPCWSTR signer);
DWORD SecureaplusAdminSettingsDeleteRestrictedApp(LPCWSTR filename);

// Trusted Certificate
DWORD SecureaplusAdminSettingsAddTrustedCertificate(LPCWSTR certificateName, LPCWSTR thumbprint, FILETIME ftValidFrom, FILETIME ftValidTo);
DWORD SecureaplusAdminSettingsDeleteTrustedCertificate(LPCWSTR certificateName, LPCWSTR thumbprint);

// Script
DWORD SecureaplusAdminSettingsAddScript(LPCWSTR interpreter, LPCWSTR script);
DWORD SecureaplusAdminSettingsDeleteScript(LPCWSTR interpreter);

// Command Line
DWORD SecureaplusAdminSettingsAddCmdLineRule(const wchar_t *command, int rule, BOOLEAN bCaseInsensitive, const wchar_t *parameter, int action);
DWORD SecureaplusAdminSettingsDeleteCmdLineRule(const wchar_t *command, int rule, BOOLEAN bCaseInsensitive, const wchar_t *parameter, int action);


//Offline AV
DWORD SecureaplusAdminSettingsSetOfflineAVEngine(LPCSTR av_engine);

//USB Scan Setting
//0 - Prompt for action
//1 - Automatically scan
//2 - Do not scan
DWORD SecureaplusAdminSettingsSetUsbScanSetting(DWORD value);

//VirusTotal API key
DWORD SecureaplusAdminSettingsSetVirusTotalAPIKey(LPCSTR vtAPIKey);

//USB Device Control
DWORD SecureaplusAdminAddUsbStorageWhitelist(LPCWSTR vendor, LPCWSTR product_id, LPCWSTR serial_number);
DWORD SecureaplusAdminDeleteUsbStorageWhitelist(LPCWSTR vendor, LPCWSTR product_id, LPCWSTR serial_number);
DWORD SecureaplusAdminEnableUsbStorageReadAccess(BOOLEAN bEnable);
DWORD SecureaplusAdminEnableUsbStorageWriteAccess(BOOLEAN bEnable);

//Game Mode
DWORD SecureaplusAdminSetGameMode(DWORD dwMode);

//Set SecureAPlus Password
DWORD SecureaplusAdminSetSecureaAPlusPassword(const char *password);
DWORD SecureaplusAdminResetSecureaAPlusPassword();

//Send Dump files (using SecureAPlusService.exe)
DWORD SecureaplusServiceCompressAndSendServiceDumpFiles();
DWORD SecureaplusServiceCompressAndSendMemoryDumpFiles();

DWORD SecureaplusAdminSetAutoUploadCrashDump(BOOLEAN bEnable);

//DeepAV
DWORD SecureaplusAdminUpdateDeepAVModel(LPCSTR utf8_model_filename, DWORD dwMajorVersion, DWORD dwMinorVersion);

//UAV Scan Settings
DWORD SecureaplusAdminEnableUAVAutoUpload(BOOLEAN bEnabled);
DWORD SecureaplusAdminSetUAVUploadFileType(DWORD type);
DWORD SecureaplusAdminEnableUAVAutoFullSystemScan(BOOLEAN bEnabled);
DWORD SecureaplusAdminEnableUAVForOnDemandScanning(BOOLEAN bEnable);
DWORD SecureaplusAdminEnableUAVForRealTimeScanning(BOOLEAN bEnable);


//Register as antivirus
DWORD SecureaplusSettingsEnableRegisterAsAntivirus(BOOLEAN bEnabled);

//Set APEX Sensitivity
DWORD SecureaplusSettingsSetAPEXSensitivity(DWORD dwSensitivity);

//Vulnerability Assessment settings
DWORD SecureaplusSettingsEnableVulnerability(BOOLEAN bEnabled);
DWORD SecureaplusSettingsSetVulnerabilityJobID(LPCWSTR jobID);
DWORD SecureaplusSettingsSetVulnerabilityJobTime(time_t jobTime);

//Set UAV Daily Upload Limit
DWORD SecureaplusSettingsSetDailyUploadLimit(ULONGLONG daily_upload_limit_in_bytes);

// Automatic mode
DWORD SecureaplusSettingsEnableAutomaticMode(BOOLEAN bEnabled);


