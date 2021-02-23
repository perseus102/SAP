#pragma once

DWORD LaunchAtHighestPriv(LPCWSTR filename, OPTIONAL LPCWSTR pszParameters, OPTIONAL BOOLEAN bWaitUntilExit = FALSE, OPTIONAL HWND hwndParent = NULL, OPTIONAL OUT HANDLE *phProcess = NULL);