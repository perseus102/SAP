#pragma once

//#define INCLUDE_SEARCH_SERVICE
#include "stdafx.h"
#ifdef INCLUDE_SEARCH_SERVICE
enum {STATUS_SECUREAPLUS_LICENSE, STATUS_APP_WHITELISTING_DRIVER, STATUS_APP_WHITELISTING_SERVICE, STATUS_SECUREAPLUS_SERVICE, STATUS_SEARCH_SERVICE, STATUS_UNIVERSAL_AV_SERVICE, STATUS_ANTIVIRUS_DRIVER, STATUS_ANTIVIRUS_SERVICE, STATUS_OFFLINE_AV, MAX_STATUS_ITEM};
#else
enum {STATUS_SECUREAPLUS_LICENSE, STATUS_APP_WHITELISTING_DRIVER, STATUS_APP_WHITELISTING_SERVICE, STATUS_SECUREAPLUS_SERVICE, STATUS_UNIVERSAL_AV_SERVICE, STATUS_ANTIVIRUS_DRIVER, STATUS_ANTIVIRUS_SERVICE, STATUS_OFFLINE_AV, MAX_STATUS_ITEM};
#endif

void StopCheckSecurityStatus();

BOOLEAN IsSAScanAvailable();

BOOLEAN IsSecurityFeaturesRunning();
BOOLEAN GetCachedSecurityFeaturesStatus();

BOOLEAN GetSecurityFeatureStatus(int index);
void getSecurityFeatureString(OUT QString &str, int index);

void UninitializeSecurityFeatures();
