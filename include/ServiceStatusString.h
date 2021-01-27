#pragma once
#include <qstring.h>

QString GetServiceStateQString(DWORD CurrentState);
QString GetServiceStateString(__in const wchar_t *ServiceName, OUT OPTIONAL DWORD *pCurrentState);
