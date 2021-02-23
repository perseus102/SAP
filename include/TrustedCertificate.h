#pragma once
//#include "AppControlDb.h"
#include <Softpub.h>

enum TRUST_BY_DIGITAL_SIGNATURE_MODE {NOT_TRUSTED_BY_DIGITAL_SIGNATURE, DIGITAL_SIGNATURE_TRUSTED_BY_OS, DIGITAL_SIGNATURE_TRUSTED_BY_NAME, DIGITAL_SIGNATURE_TRUSTED_BY_NAME_AND_THUMBPRINT, TRUST_BY_DIGITAL_SIGNATURE_INVALID_MODE};
#define SECUREAPLUS_LITE_TRUSTED_BY_DIGITAL_SIGNATURE_DEFAULT DIGITAL_SIGNATURE_TRUSTED_BY_NAME

unsigned __int64 CalculateCertificateChecksum(const wchar_t *name, const wchar_t *thumbprintStr);

DWORD AddTrustedCerticate(LPCWSTR certCommonName, LPCWSTR thumbprintStr, FILETIME validFrom, FILETIME validTo, OPTIONAL OUT BOOLEAN *bNewCertificate);
DWORD AddTrustedCerticateByProvCert(PCRYPT_PROVIDER_CERT psProvCert, OPTIONAL OUT BOOLEAN *bNewCertificate = NULL, OPTIONAL OUT wchar_t **certCN = NULL, FILETIME *certValidFrom = NULL, FILETIME *certValidTo = NULL);
DWORD AddTrustedCertificateByFileName(LPCWSTR filename, LPCWSTR filename_ext);
DWORD DeleteTrustedCertificate(LPCWSTR certCommonName, LPCWSTR thumbprintStr);
BOOLEAN IsTrustedCertificate(wchar_t *certCommonName, wchar_t *thumbprintStr);
BOOLEAN IsTrustedCertificate(wchar_t *certCommonName, BYTE *thumbprint, DWORD thumbprintSize);

//////////////////////////////////////////////////////////////////////////////////

#ifndef SUPPORT_STANDALONE_WITHOUT_SECUREAPLUS
DWORD SetTrustByDigitalSignatureMode(DWORD mode);
DWORD GetTrustByDigitalSignatureMode();
#endif
//////////////////////////////////////////////////////////////////////////////////

BOOLEAN IsFileSignedByTrustedCertificate(LPCWSTR filename);

