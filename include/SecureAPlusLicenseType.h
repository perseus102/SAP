#pragma once
enum {SECUREAPLUS_LICENSE_TYPE_FREEMIUM, SECUREAPLUS_LICENSE_TYPE_PREMIUM, SECUREAPLUS_LICENSE_TYPE_INVALID = 999};
enum {SECUREAPLUS_LICENSE_TYPE_LITE, SECUREAPLUS_LICENSE_TYPE_ESSENTIALS, SECUREAPLUS_LICENSE_TYPE_PRO};

DWORD SecureAPlus_GetLicenceTypeRaw(OUT char **reply);

//if it returns SECUREAPLUS_LICENSE_TYPE_INVALID, use GetLastError() to get the error code.
int SecureAPlus_GetLicenceType();

//Save to registry
DWORD SaveLicenseType(DWORD dwLicenseType);

//Read from registry
int SecureAPlus_GetRegLicenceType();
