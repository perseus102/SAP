#pragma once
#include "UniversalAV.h"

#define UNIVERSALAV_REGISTRY_DIALOG_SUBKEY_A UNIVERSALAV_REGISTRY_SUBKEY_A "\\Dialog"
#define UNIVERSALAV_REGISTRY_DIALOG_SUBKEY UNIVERSALAV_REGISTRY_SUBKEY L"\\Dialog"

DWORD uav_create_volatile_registry();

DWORD uav_set_scan_result_is_available_flag();

DWORD uav_ui_set_current_status(LPCWSTR msg);

DWORD uav_ui_delete_current_status();

//user is responsible to free() the result
wchar_t *uav_ui_get_current_status();

BOOLEAN uav_ui_registry_key_exist();

DWORD uav_registry_set_scan_result(LPCWSTR EntryName, DWORD ValueType, void *EntryValue, DWORD EntryValueSize);
#define uav_registry_set_scan_result_ulonglong(EntryName, pulonglong) uav_registry_set_scan_result(EntryName, REG_BINARY, pulonglong, sizeof(ULONGLONG));
#define uav_registry_set_scan_result_dword(EntryName, pdword) uav_registry_set_scan_result(EntryName, REG_DWORD, pdword, sizeof(DWORD));

ULONGLONG uav_registry_get_scan_result_ulonglong(LPCWSTR EntryName);

DWORD uav_registry_set_progress_bar(LPCWSTR EntryName, DWORD ValueType, void *EntryValue, DWORD EntryValueSize);
#define uav_registry_set_progress_bar_dword(EntryName, pdword) uav_registry_set_progress_bar(EntryName, REG_DWORD, pdword, sizeof(DWORD));
#define uav_registry_set_progress_bar_ulonglong(EntryName, pulonglong) uav_registry_set_progress_bar(EntryName, REG_BINARY, pulonglong, sizeof(ULONGLONG));
DWORD uav_registry_get_progress_bar_dword(LPCWSTR EntryName);
ULONGLONG uav_registry_get_progress_bar_ulonglong(LPCWSTR EntryName);

DWORD uav_notify_registry_set_last_scan_file(char *filename);