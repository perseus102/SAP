#ifndef _REGISTRY_H_
#define _REGISTRY_H_

//RegDeleteKeyEx is not available in Windows XP 32 bit.
//If the fucntion is not available, the function will fall back to RegDeleteKey
LONG WINAPI _RegDeleteKeyExW(
  __in          HKEY hKey,
  __in          LPCWSTR lpSubKey,
  __in          REGSAM samDesired,
  DWORD Reserved
);

LONG WINAPI _RegDeleteKeyExA(
  __in          HKEY hKey,
  __in          LPCSTR lpSubKey,
  __in          REGSAM samDesired,
  DWORD Reserved
);


/********************************************************************************************
	Create Registry Key
	Argument :
		in	HKEY  SubTree
		in	TCHAR *SubKeyName
	Return :
		NO_ERROR			-> Success
		Otherwise			-> return Windows last error
********************************************************************************************/
DWORD _RegCreateNewKeyW (HKEY  SubTree, 
					    LPCWSTR SubKeyName,
						DWORD dwOptions);

DWORD _RegCreateNewKeyA (HKEY  SubTree, 
					   LPCSTR SubKeyName,
					   DWORD dwOptions);

#define RegCreateNewKeyW(hkey, sub_key) _RegCreateNewKeyW(hkey, sub_key, REG_OPTION_NON_VOLATILE)
#define RegCreateNewKeyA(hkey, sub_key) _RegCreateNewKeyA(hkey, sub_key, REG_OPTION_NON_VOLATILE)

#define RegCreateNewVolatileKeyW(hkey, sub_key) _RegCreateNewKeyW(hkey, sub_key, REG_OPTION_VOLATILE)
#define RegCreateNewVolatileKeyA(hkey, sub_key) _RegCreateNewKeyA(hkey, sub_key, REG_OPTION_VOLATILE)

/********************************************************************************************
	Open Registry Key
	Argument :
		in	HKEY  SubTree
		in	TCHAR *SubKeyName
	Return :
		FALSE	-> Not Exist or Cannot Open the Key
		TRUE	-> Exist
********************************************************************************************/
BOOL RegKeyExist (HKEY  SubTree,
				   LPCTSTR SubKeyName); 

/********************************************************************************************
	Set information to the registry
	Argument :
		in	HKEY  SubTree
		in  TCHAR *SubKeyName
		in	TCHAR *EntryName
		in	DWORD ValueType
		in	VOID  *EntryValue
		in	DWORD EntryValueSize
	Return :
		NO_ERROR			-> Success
		Otherwise			-> return Windows last error
********************************************************************************************/
DWORD _RegSetEntryValueW (HKEY  SubTree, 
						LPCWSTR SubKeyName, 
						LPCWSTR EntryName, 
						DWORD ValueType, 
						VOID  *EntryValue, 
						DWORD EntryValueSize,
						DWORD dwOptions);

DWORD _RegSetEntryValueA (HKEY  SubTree, 
						LPCSTR SubKeyName, 
						LPCSTR EntryName, 
						DWORD ValueType, 
						VOID  *EntryValue, 
						DWORD EntryValueSize,
						DWORD dwOptions);


#define RegSetEntryValueW(hkey, sub_key, entry_name, value_type, value, value_size) _RegSetEntryValueW (hkey, sub_key, entry_name, value_type, value, value_size, REG_OPTION_NON_VOLATILE);
#define RegSetEntryValueA(hkey, sub_key, entry_name, value_type, value, value_size) _RegSetEntryValueA (hkey, sub_key, entry_name, value_type, value, value_size, REG_OPTION_NON_VOLATILE);

#define RegSetEntryValueVolatileW(hkey, sub_key, entry_name, value_type, value, value_size) _RegSetEntryValueW (hkey, sub_key, entry_name, value_type, value, value_size, REG_OPTION_VOLATILE);
#define RegSetEntryValueVolatileA(hkey, sub_key, entry_name, value_type, value, value_size) _RegSetEntryValueA (hkey, sub_key, entry_name, value_type, value, value_size, REG_OPTION_VOLATILE);

/********************************************************************************************
	Query information from the registry
	Argument :
		in	HKEY  SubTree
		in  TCHAR *SubKeyName
		in	TCHAR *EntryName
		out	VOID  *EntryValue
		in/out	DWORD BufferSize - size in bytes
	Return :
		NO_ERROR			-> Success
		Otherwise			-> return Windows last error
********************************************************************************************/
DWORD RegQueryEntryValueW (HKEY  SubTree, 
						  LPCWSTR SubKeyName, 
						  LPCWSTR EntryName, 
						  VOID  *EntryValue, 
						  PDWORD BufferSize);


DWORD RegQueryEntryValueA (HKEY  SubTree, 
						  LPCSTR SubKeyName, 
						  LPCSTR EntryName, 
						  VOID  *EntryValue, 
						  PDWORD BufferSize);


/********************************************************************************************
	Query information from the registry
	Argument :
		in	HKEY  SubTree
		in  TCHAR *SubKeyName
		in	TCHAR *EntryName
		out	VOID  *EntryValue
		in/out	DWORD BufferSize -> [in] size of EntryValue, [out] bytes read
	Return :
		NO_ERROR			-> Success
		Otherwise			-> return Windows last error
********************************************************************************************/
DWORD RegQueryEntryValueAndType (HKEY  SubTree, 
						  TCHAR *SubKeyName, 
						  TCHAR *EntryName, 
						  VOID  *EntryValue, 
						  LPDWORD BufferSize,
						  LPDWORD lpType);


DWORD RegQueryDwordValueW (HKEY  SubTree, 
						  LPCWSTR SubKeyName, 
						  LPCWSTR EntryName, 
						  DWORD  *EntryValue);

DWORD RegQueryDwordValueA (HKEY  SubTree, 
						  LPCSTR SubKeyName, 
						  LPCSTR EntryName, 
						  DWORD  *EntryValue);

/********************************************************************************************
	Delete information from the registry
	Argument :
		in	HKEY  SubTree
		in  TCHAR *SubKeyName
		in	TCHAR *EntryName
	Return :
		NO_ERROR			-> Success
		Otherwise			-> return Windows last error
********************************************************************************************/
DWORD RegDeleteEntryValueW (HKEY  SubTree, 
						  LPCWSTR SubKeyName, 
						  LPCWSTR EntryName);

DWORD RegDeleteEntryValueA (HKEY  SubTree, 
						  LPCSTR SubKeyName, 
						  LPCSTR EntryName);



/********************************************************************************************
	Query information from the registry
	Argument :
		in	HKEY  SubTree
		in  TCHAR *SubKeyName
		out	TCHAR *EntryName
		in	DWORD BufferSize
	Return :
		NO_ERROR			-> Success
		others -> Error Code
********************************************************************************************/
DWORD RegEnumEntryNameW (HKEY  SubTree, 
						  LPCWSTR SubKeyName, 
						  LPWSTR EntryName, 
						  DWORD dwIndex,
						  DWORD BufferSize);
DWORD RegEnumEntryNameA (HKEY  SubTree, 
						  LPCSTR SubKeyName, 
						  LPSTR EntryName, 
						  DWORD dwIndex,
						  DWORD BufferSize);


/********************************************************************************************
	Enumerate sub keys from the registry
	Argument :
		in	HKEY  SubTree
		in  TCHAR *SubKeyName
		out	TCHAR *result     - sub key name
		in	DWORD BufferSize
	Return :
		NO_ERROR			-> Success
		others -> Error Code
********************************************************************************************/
DWORD RegEnumSubKeyW(HKEY  SubTree, LPCWSTR SubKeyName, wchar_t *result, DWORD dwIndex, DWORD BufferSize);
DWORD RegEnumSubKeyA(HKEY  SubTree, LPCSTR SubKeyName, char *result, DWORD dwIndex, DWORD BufferSize);

DWORD RegEnumSubKeyEx(HKEY  SubTree, TCHAR *SubKeyName, TCHAR *result, DWORD dwIndex, IN OUT LPDWORD BufferSize, OUT LPTSTR lpClass, IN OUT LPDWORD lpcClass, OUT PFILETIME lpftLastWriteTime);


DWORD RegRecursiveDeleteEntriesW(HKEY SubTree, LPCWSTR SubKeyName);

///////////////////////////////////////////////////////////////////
//
// Recursively delete sub key with all its sub entries
//
//	Argument :
//		in	HKEY  SubTree      - e.g. HKEY_LOCAL_MACHINE
//		in  TCHAR *SubKeyName  - e.g. "Software\\Company\\Product"
// 
///////////////////////////////////////////////////////////////////
DWORD RegRecursiveDeleteW(HKEY SubTree, LPCWSTR SubKeyName);
DWORD RegRecursiveDeleteA(HKEY SubTree, LPCSTR SubKeyName);

//
//
// Return: 0 - on successful
//         Otherwise return Windows Error Code
DWORD RegNotifyChangeEntryValue(HKEY SubTree, LPCTSTR SubKeyName, TCHAR *EntryName);

DWORD RegGetNumberOfSubKeys(HKEY SubTree, LPCTSTR SubKeyName);
DWORD RegGetNumberOfEntries(HKEY SubTree, LPCTSTR SubKeyName);


//return 0 - successful, otherwise it returns Windows error code
DWORD RegExportKey(HKEY SubTree, LPCTSTR SubKeyName, LPCTSTR filename);
DWORD RegImportKey(HKEY SubTree, LPCTSTR SubKeyName, LPCTSTR filename);

#define RegSetStringValueW(SubTree, SubKeyName, EntryName, EntryValue) _RegSetEntryValueW(SubTree, SubKeyName, EntryName, REG_SZ, (void*)EntryValue, (DWORD)(wcslen(EntryValue) + 1) * sizeof(wchar_t), 0)
#define RegSetStringValueA(SubTree, SubKeyName, EntryName, EntryValue) _RegSetEntryValueA(SubTree, SubKeyName, EntryName, REG_SZ, (void*)EntryValue, (DWORD)(strlen(EntryValue) + 1) * sizeof(char), 0)

#define RegSetStringValueVolatileW(SubTree, SubKeyName, EntryName, EntryValue) _RegSetEntryValueW(SubTree, SubKeyName, EntryName, REG_SZ, (void*)EntryValue, (DWORD)(wcslen(EntryValue) + 1) * sizeof(wchar_t), REG_OPTION_VOLATILE)
#define RegSetStringValueVolatileA(SubTree, SubKeyName, EntryName, EntryValue) _RegSetEntryValueA(SubTree, SubKeyName, EntryName, REG_SZ, (void*)EntryValue, (DWORD)(strlen(EntryValue) + 1) * sizeof(char), REG_OPTION_VOLATILE)

DWORD RegEnumSubKeyWithCallbackW(HKEY  SubTree, TCHAR *SubKeyName, void *context, BOOLEAN (*callback)(void *context, LPCWSTR sub_key));

/*
Callback Example:
return TRUE to continue enumerating,
       FALSE to stop.
bDeleteThisEntry - the callback function can set this to TRUE to delete the entry, by default the value is set to FALSE.

BOOLEAN OnRegEnumEntryName(void *context, wchar_t *EntryName, BOOLEAN *bDeleteThisEntry)
{
	*bDeleteThisEntry = FALSE;
	return TRUE;
}
*/
DWORD RegEnumEntryNameWithCallbackW (HKEY  SubTree, 
						  LPCWSTR SubKeyName,
						  void *context,
						  BOOLEAN (WINAPI *callback)(void *context, wchar_t *EntryName, BOOLEAN *bDeleteThisEntry));


//The result of MoveFileEx operation
DWORD GetPendingMoveFileEx(void *context, void(WINAPI *callback)(void *context, wchar_t *source, wchar_t* target));


/********************************************************************************************
	Query string value from the registry
	Argument :
		in	HKEY  SubTree
		in  TCHAR *SubKeyName
		in	TCHAR *EntryName
		out	OPTIONAL PDWORD pdwErrorCode
	Return :
		NULL - failed, otherwise return string value.
		       User is responsible to free the allocated string value.
********************************************************************************************/
BYTE *_RegQueryBinaryW (HKEY  SubTree, 
						  LPCWSTR SubKeyName, 
						  LPCWSTR EntryName, 
						  OUT OPTIONAL PDWORD pdwBufferSize,
						  OUT OPTIONAL PDWORD pdwErrorCode);


BYTE *_RegQueryBinaryA (HKEY  SubTree, 
						  LPCSTR SubKeyName, 
						  LPCSTR EntryName, 
						  OUT OPTIONAL PDWORD pdwBufferSize,
						  OUT OPTIONAL PDWORD pdwErrorCode
						  );

#define RegQueryBinaryW(SubTree, SubKeyName, EntryName, opt_out_pdword_error_code) _RegQueryBinaryW(SubTree, SubKeyName, EntryName, NULL, opt_out_pdword_error_code)
#define RegQueryBinaryA(SubTree, SubKeyName, EntryName, opt_out_pdword_error_code) _RegQueryBinaryA(SubTree, SubKeyName, EntryName, NULL, opt_out_pdword_error_code)

/********************************************************************************************
	Query string value from the registry
	Argument :
		in	HKEY  SubTree
		in  TCHAR *SubKeyName
		in	TCHAR *EntryName
		out	OPTIONAL PDWORD pdwErrorCode
	Return :
		NULL - failed, otherwise return string value.
		       User is responsible to free the allocated string value.
********************************************************************************************/
#define RegQueryStringW(SubTree, SubKeyName, EntryName, opt_out_pdword_error_code) (LPWSTR)_RegQueryBinaryW(SubTree, SubKeyName, EntryName, NULL, opt_out_pdword_error_code);
#define RegQueryStringA(SubTree, SubKeyName, EntryName, opt_out_pdword_error_code) (LPSTR)_RegQueryBinaryA(SubTree, SubKeyName, EntryName, NULL, opt_out_pdword_error_code);

DWORD RegSetDwordValueW (HKEY  SubTree, 
						LPCWSTR SubKeyName, 
						LPCWSTR EntryName, 
						DWORD EntryValue);

DWORD RegSetDwordValueA (HKEY  SubTree, 
						LPCSTR SubKeyName, 
						LPCSTR EntryName, 
						DWORD EntryValue);

//BOOLEAN(WINAPI *callback)(void *context, wchar_t *source, wchar_t* target) - return FALSE to remove the entry 
//                                                                             return TRUE to retain the entry
DWORD RemovePendingMoveFileExFromRegistry(void *context, BOOLEAN(WINAPI *callback)(void *context, wchar_t *source, wchar_t* target));

BOOLEAN RegValueExistW(HKEY  SubTree, LPCWSTR SubKeyName, LPCWSTR EntryName);

#ifdef UNICODE
#define RegCreateNewKey RegCreateNewKeyW
#define RegSetEntryValue RegSetEntryValueW
#define RegQueryEntryValue RegQueryEntryValueW
#define RegQueryDwordValue RegQueryDwordValueW
#define RegSetStringValue RegSetStringValueW
#define RegQueryString RegQueryStringW
#define RegDeleteEntryValue RegDeleteEntryValueW
#define RegRecursiveDelete RegRecursiveDeleteW
#define RegEnumSubKey RegEnumSubKeyW
#define RegEnumEntryName RegEnumEntryNameW
#define RegSetDwordValue RegSetDwordValueW
#else
#define RegCreateNewKey RegCreateNewKeyA
#define RegSetEntryValue RegSetEntryValueA
#define RegQueryEntryValue RegQueryEntryValueA
#define RegQueryDwordValue RegQueryDwordValueA
#define RegSetStringValue RegSetStringValueA
#define RegQueryString RegQueryStringA
#define RegDeleteEntryValue RegDeleteEntryValueA
#define RegRecursiveDelete RegRecursiveDeleteA
#define RegEnumSubKey RegEnumSubKeyA
#define RegEnumEntryName RegEnumEntryNameA
#define RegSetDwordValue RegSetDwordValueA
#endif

#endif