#pragma once
#include <fltuser.h>
DWORD SetDisableSAScan(BOOLEAN bDisabled);
BOOLEAN IsSAScanDisabled(NTSTATUS *pStatus);

DWORD SetSAAntiVirusSoftwareUpdate(DWORD dwSoftwareUpdate);