#ifndef _TRUSTED_ACCOUNT_H_
#define _TRUSTED_ACCOUNT_H_

#define MAX_TRUSTED_SID 3

extern const wchar_t *trusted_sid[MAX_TRUSTED_SID];

BOOLEAN IsMemberOfTrustedGroup(HANDLE hToken);

BOOLEAN IsTrustedGroupSid(IN wchar_t *groupSid);
BOOLEAN IsTrustedGroup(IN wchar_t *groupName);
BOOLEAN IsTrustedAccount(IN wchar_t *userName);
BOOLEAN IsPidRunByTrustedAccount(IN DWORD pid, OUT wchar_t **pUserName);

BOOLEAN IsDefaultTrustedSid(LPCWSTR sid);
BOOLEAN IsDefaultTrustedAccount(LPCWSTR userName);

DWORD AddTrustedAccount(LPCWSTR user_or_group, LPCWSTR name, LPCWSTR sid);
DWORD DeleteTrustedAccount(LPCWSTR user_or_group, LPCWSTR name, LPCWSTR sid);
DWORD DeleteTrustedGroupByName(LPCWSTR name);
DWORD DeleteTrustedUserByName(LPCWSTR name);


//LPCWSTR user_or_group = L"User" for sser, L"Group" for group.
//User is responsible to free() the result
wchar_t *get_name_from_trusted_sid(LPCWSTR user_or_group, LPCWSTR sid);
wchar_t *GetNameFromTrustedSid(LPCWSTR sid);

//LPCWSTR user_or_group = L"User" for sser, L"Group" for group.
//User is responsible to free() the result
wchar_t *get_sid_from_trusted_name(LPCWSTR user_or_group, LPCWSTR name);

#define AddTrustedUser(name, sid) AddTrustedAccount(L"User", name, sid)
#define AddTrustedGroup(name, sid) AddTrustedAccount(L"Group", name, sid)

#define DeleteTrustedUser(name, sid) DeleteTrustedAccount(L"User", name, sid)
#define DeleteTrustedGroup(name, sid) DeleteTrustedAccount(L"Group", name, sid)

#define GetUserNameFromTrustedSid(sid) get_name_from_trusted_sid(L"User", sid)
#define GetGroupNameFromTrustedSid(sid) get_name_from_trusted_sid(L"Group", sid)

#define GetUserSidFromTrustedName(name) get_sid_from_trusted_name(L"User", name)
#define GetGroupSidFromTrustedName(name) get_sid_from_trusted_name(L"Group", name)

BOOLEAN IsCurrentProcessRunByTrustedAccount(BOOLEAN bRefresh = FALSE);

#endif
