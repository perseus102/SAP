#pragma once
// 0 - Interactive, 1 - LockDown, 2 - Trust all for 5 minutes, 3 - Trust all for 30 minutes, 4 - Trust all until computer restarted, 5 - Trust all until ...
enum {APPWHITELISTING_INTERACTIVE_MODE, APPWHITELISTING_LOCKDOWN_MODE, TRUST_ALL_FOR_5_MINUTES = 2, TRUST_ALL_FOR_30_MINUTES, TRUST_ALL_UNTIL_COMPUTER_RESTARTED, TRUST_ALL_UNTIL, TRUST_ALL_MODE_END};

int GetTrustAllMode();

//This function will return lockdown mode when the user is login as non-trusted account user.
DWORD GetApplicationWhitelistingMode();

DWORD GetApplicationWhitelistingModeForTrustedAccountUser();

UINT GetSecureAPlusIconId();

DWORD SetApplicationWhitelistingMode(DWORD mode);