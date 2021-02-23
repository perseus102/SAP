#ifndef _DIGITAL_SIGNATURE_H_

#define _DIGITAL_SIGNATURE_H_

#pragma pack(push, 8)
#include <Wintrust.h>

#ifdef WIN64
// certenrolls_begin -- *_BLOB
typedef struct _CRYPTOAPI_BLOB8 {
    unsigned __int64				cbData;
    __field_bcount(cbData)  BYTE    *pbData;
} CRYPT_INTEGER_BLOB8, *PCRYPT_INTEGER_BLOB8,
CRYPT_UINT_BLOB8, *PCRYPT_UINT_BLOB8,
CRYPT_OBJID_BLOB8, *PCRYPT_OBJID_BLOB8,
CERT_NAME_BLOB8, *PCERT_NAME_BLOB8,
CERT_RDN_VALUE_BLOB8, *PCERT_RDN_VALUE_BLOB8,
CERT_BLOB8, *PCERT_BLOB8,
CRL_BLOB8, *PCRL_BLOB8,
DATA_BLOB8, *PDATA_BLOB8,
CRYPT_DATA_BLOB8, *PCRYPT_DATA_BLOB8,
CRYPT_HASH_BLOB8, *PCRYPT_HASH_BLOB8,
CRYPT_DIGEST_BLOB8, *PCRYPT_DIGEST_BLOB8,
CRYPT_DER_BLOB8, *PCRYPT_DER_BLOB8,
CRYPT_ATTR_BLOB8, *PCRYPT_ATTR_BLOB8;

//+-------------------------------------------------------------------------
//  Type used for any algorithm
//
//  Where the Parameters CRYPT_OBJID_BLOB is in its encoded representation. For most
//  algorithm types, the Parameters CRYPT_OBJID_BLOB is NULL (Parameters.cbData = 0).
//--------------------------------------------------------------------------
typedef struct _CRYPT_ALGORITHM_IDENTIFIER8 {
    LPSTR               pszObjId;
    CRYPT_OBJID_BLOB8    Parameters;
} CRYPT_ALGORITHM_IDENTIFIER8, *PCRYPT_ALGORITHM_IDENTIFIER8;
// certenrolls_end

//+-------------------------------------------------------------------------
//  Information stored in a certificate
//
//  The Issuer, Subject, Algorithm, PublicKey and Extension BLOBs are the
//  encoded representation of the information.
//--------------------------------------------------------------------------
// certenrolls_begin -- CERT_CONTEXT
typedef struct _CERT_INFO8 {
    unsigned __int64			dwVersion;
    CRYPT_INTEGER_BLOB8          SerialNumber;
    CRYPT_ALGORITHM_IDENTIFIER8  SignatureAlgorithm;
    CERT_NAME_BLOB8              Issuer;
    FILETIME                    NotBefore;
    FILETIME                    NotAfter;
    CERT_NAME_BLOB              Subject;
    CERT_PUBLIC_KEY_INFO        SubjectPublicKeyInfo;
    CRYPT_BIT_BLOB              IssuerUniqueId;
    CRYPT_BIT_BLOB              SubjectUniqueId;
    DWORD                       cExtension;
    PCERT_EXTENSION             rgExtension;
} CERT_INFO8, *PCERT_INFO8;
// certenrolls_end

//+-------------------------------------------------------------------------
//  Certificate context.
//
//  A certificate context contains both the encoded and decoded representation
//  of a certificate. A certificate context returned by a cert store function
//  must be freed by calling the CertFreeCertificateContext function. The
//  CertDuplicateCertificateContext function can be called to make a duplicate
//  copy (which also must be freed by calling CertFreeCertificateContext).
//--------------------------------------------------------------------------
// certenrolls_begin -- CERT_CONTEXT8
typedef struct _CERT_CONTEXT8 {
    unsigned __int64		dwCertEncodingType;
    BYTE                    *pbCertEncoded;
    unsigned __int64        cbCertEncoded;
    PCERT_INFO8             pCertInfo;
    HCERTSTORE              hCertStore;
} CERT_CONTEXT8, *PCERT_CONTEXT8;
typedef const CERT_CONTEXT8 *PCCERT_CONTEXT8;
// certenrolls_end

typedef struct _CRYPT_PROVIDER_CERT8
{
    unsigned __int64                    cbStruct;

    PCCERT_CONTEXT8                     pCert;              // must have its own ref-count!

    BOOL                                fCommercial;
    BOOL                                fTrustedRoot;       // certchk policy should set this.
    BOOL                                fSelfSigned;        // set in cert provider

    BOOL                                fTestCert;          // certchk policy will set

    DWORD                               dwRevokedReason;

    DWORD                               dwConfidence;       // set in the Certificate Provider
#                                           define  CERT_CONFIDENCE_SIG             0x10000000  // this cert
#                                           define  CERT_CONFIDENCE_TIME            0x01000000  // issuer cert
#                                           define  CERT_CONFIDENCE_TIMENEST        0x00100000  // this cert
#                                           define  CERT_CONFIDENCE_AUTHIDEXT       0x00010000  // this cert
#                                           define  CERT_CONFIDENCE_HYGIENE         0x00001000  // this cert
#                                           define  CERT_CONFIDENCE_HIGHEST         0x11111000

    DWORD                               dwError;

    CTL_CONTEXT                         *pTrustListContext;

    // 16-Jan-1998 pberkman: added
    BOOL                                fTrustListSignerCert;

    // 25-Feb-1998 philh: added
    //
    // The following two are only applicable to Self Signed certificates
    // residing in a CTL.
    PCCTL_CONTEXT                       pCtlContext;
    DWORD                               dwCtlError;

    // 12-Mar-1998 philh: added
    BOOL                                fIsCyclic;

    // 12-Oct-2000 DSIE: added
    PCERT_CHAIN_ELEMENT                 pChainElement;
} CRYPT_PROVIDER_CERT8, *PCRYPT_PROVIDER_CERT8;
#endif

#ifndef WIN64
#define GetPCert(psProvCert) psProvCert->pCert
#define GetPCertInfo(psProvCert) psProvCert->pCert->pCertInfo
#define GetCertValidFrom(psProvCert) (psProvCert->pCert->pCertInfo->NotBefore)
#define GetCertValidTo(psProvCert) (psProvCert->pCert->pCertInfo->NotAfter)
#else
#define GetPCert(psProvCert) ((PCRYPT_PROVIDER_CERT8)(psProvCert))->pCert
//#define GetPCertInfo(psProvCert) ((PCRYPT_PROVIDER_CERT8)psProvCert)->pCert->pCertInfo)
#define GetCertValidFrom(psProvCert) (((PCRYPT_PROVIDER_CERT8)psProvCert)->pCert->pCertInfo->NotBefore)
#define GetCertValidTo(psProvCert) (((PCRYPT_PROVIDER_CERT8)psProvCert)->pCert->pCertInfo->NotAfter)
#endif

//#define GetCertValidFrom(psProvCert) GetCertExpiryNotBefore(psProvCert)
//#define GetCertValidTo(psProvCert) GetCertExpiryNotAfter(psProvCert)
#define GetCertSerialNumber(psProvCert) GetPCertInfo(psProvCert)->SerialNumber.pbData
#define GetCertSerialNumberSize(psProvCert) GetPCertInfo(psProvCert)->SerialNumber.cbData
/*
  Possible return values:
   if (TRUST_E_NOSIGNATURE == hr)
   {
      _tprintf(_T("No signature found on the file.\n"));
   }
   else if (TRUST_E_BAD_DIGEST == hr)
   {
      _tprintf(_T("The signature of the file is invalid\n"));
   }
   else if (TRUST_E_PROVIDER_UNKNOWN == hr)
   {
      _tprintf(_T("No trust provider on this machine can verify this type of files.\n"));
   }
   else if (S_OK != hr)
   {
      _tprintf(_T("WinVerifyTrust failed with error 0x%.8X\n"), hr);
   }
   else
   {
      _tprintf(_T("File signature is OK.\n"));
   }
*/
HRESULT CloseWintrustData(WINTRUST_DATA *pWintrustData);
HRESULT _VerifyDigitalSignature(__in LPCWSTR _filename, __out_opt PCRYPT_PROVIDER_CERT *psProvCert, BOOLEAN check_cert_revocation, OUT WINTRUST_DATA *pWintrustData);
HRESULT VerifyDigitalSignature(__in LPCWSTR filename, __out_opt PCRYPT_PROVIDER_CERT *psProvCert, OUT WINTRUST_DATA *pWintrustData);

PCRYPT_PROVIDER_CERT GetProviderCert(HANDLE hWVTStateData);

//If there is any data, it returns a non-NULL pointer. User is responsible to free the data using LocalFree() function.
LPWSTR GetCertNameW(CRYPT_PROVIDER_CERT *psProvCert, DWORD dwType, void* pvTypePara);

//If there is any data, it returns a non-NULL pointer. User is responsible to free the data using LocalFree() function.
LPWSTR GetCertIssuerNameW(CRYPT_PROVIDER_CERT  *psProvCert, DWORD dwType, void* pvTypePara);

//If there is any data, it returns a non-NULL pointer. User is responsible to free the data using LocalFree() function.
LPWSTR GetCertNameRDNW(PCRYPT_PROVIDER_CERT psProvCert);

LPWSTR GetCertSubjectW(PCRYPT_PROVIDER_CERT psProvCert);

#define GetCertCommonNameW(psProvCert) GetCertNameW(psProvCert, CERT_NAME_ATTR_TYPE, szOID_COMMON_NAME);

//#define GetCertThumbPrint(psProvCert, thumbprint, pcbThumbprint) if (psProvCert) CertGetCertificateContextProperty(psProvCert->pCert, CERT_HASH_PROP_ID, thumbprint, pcbThumbprint)
//BOOLEAN GetCertThumbPrint(PCRYPT_PROVIDER_CERT psProvCert, BYTE *thumbprint, DWORD *thumbprintSize);
BYTE *GetCertThumbPrint(PCRYPT_PROVIDER_CERT psProvCert, OUT DWORD *pdwThumbprintSize);

void GetCertValidityDate(PCRYPT_PROVIDER_CERT psProvCert, OUT PSYSTEMTIME pValidFrom, OUT PSYSTEMTIME pValidTo);

void GetCertificateInfo(PCRYPT_PROVIDER_CERT psProvCert, OPTIONAL OUT LPWSTR *certCommonName, OPTIONAL OUT wchar_t **pThumbprintStr, OPTIONAL OUT LPWSTR *issuer);

BOOLEAN IsSignedBy(__in LPCWSTR filename, const wchar_t *originalSigner, BYTE *originalThumbprint = NULL, DWORD originalThumbprintSize = 0);

#ifdef WIN64
PCERT_INFO8 GetPCertInfo(PCRYPT_PROVIDER_CERT psProvCert);
#endif

BOOLEAN IsFileSigned(LPCWSTR filename);

BOOLEAN IsSignedBySecureAge(LPCWSTR full_filename);


#ifdef _IMPERSONATE_H_
HRESULT VerifyDigitalSignatureWithTimedOut(DWORD dwTimedOutInMsec, __in LPCWSTR filename, __out_opt PCRYPT_PROVIDER_CERT *psProvCert, BOOLEAN check_cert_revocation, OUT WINTRUST_DATA *pWintrustData, OPTIONAL IN BOOLEAN bImpersonateLoggedOnUser = FALSE, OPTIONAL void(*callback)(WINTRUST_DATA *pWintrustData, LPVOID param_callback) = NULL, OPTIONAL LPVOID param_callback = NULL);
#else
HRESULT VerifyDigitalSignatureWithTimedOut(DWORD dwTimedOutInMsec, __in LPCWSTR filename, __out_opt PCRYPT_PROVIDER_CERT *psProvCert, BOOLEAN check_cert_revocation, OUT WINTRUST_DATA *pWintrustData, OPTIONAL void(*callback)(WINTRUST_DATA *pWintrustData, LPVOID param_callback) = NULL, OPTIONAL LPVOID param_callback = NULL);
#endif

BOOLEAN IsBlacklistedCertificate(BYTE *thunmbprint, DWORD thumbprint_size);

void FreeDigitalSignature();

#pragma pack(pop)

#endif