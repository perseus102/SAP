#pragma once

enum {
	TAG_SMS_OS_VERSION = 1,
	TAG_SMS_COMPUTER_INFORMATION = 2,
	TAG_SMS_OVERWRITE_COMPRESSED_WHITELIST = 3,
	TAG_SMS_ADD_MODIFY_COMPRESSED_WHITELIST = 4,
	TAG_SMS_ADD_MODIFY_WHITELIST = 5,
	TAG_SMS_OVERWRITE_TRUSTED_USERS = 6,
	TAG_SMS_ADD_TRUSTED_USERS = 7,
	TAG_SMS_DELETE_TRUSTED_USERS = 8,
	TAG_SMS_OVERWRITE_TRUSTED_GROUPS = 9,
	TAG_SMS_ADD_TRUSTED_GROUPS = 0xA,
	TAG_SMS_DELETE_TRUSTED_GROUPS = 0xB,
	TAG_SMS_OVERWRITE_APP_WHITELISTING_SETTINGS = 0xC,
	TAG_SMS_ADD_TRUSTED_CERTIFICATE = 0xD,
	TAG_SMS_DELETE_TRUSTED_CERTIFICATE = 0xE,
	TAG_SMS_OVERWRITE_TRUSTED_CERTIFICATE = 0xF,
	TAG_SMS_ADD_RESTRICTED_APPLICATION = 0x10,
	TAG_SMS_DELETE_RESTRICTED_APPLICATION = 0x11,
	TAG_SMS_OVERWRITE_RESTRICTED_APPLICATION = 0x12,
	TAG_SMS_ADD_SCRIPT = 0x13,
	TAG_SMS_DELETE_SCRIPT = 0x14,
	TAG_SMS_OVERWRITE_SCRIPT = 0x15,
	TAG_SMS_LIST_OF_HASHES_CLIENT = 0x16,
	TAG_SMS_LIST_OF_HASHES_SERVER = 0x17,
	TAG_SMS_REQUEST_LIST_OF_TAGS = 0x18,
	TAG_SMS_UNIQUE_REFERENCE = 0x19,
	TAG_SMS_OVERWRITE_SCAN_SETTINGS = 0x1A,
	TAG_SMS_OVERWRITE_USB_STORAGE_ACCESS_RIGHTS = 0x1B,
	TAG_SMS_ADD_WHITELISTED_USB_STORAGE = 0x1C,
	TAG_SMS_DELETE_WHITELISTED_USB_STORAGE = 0x1D,
	TAG_SMS_OVERWRITE_WHITELISTED_USB_STORAGE = 0x1E,
	TAG_SMS_TRUST_ALL_UNTIL = 0x1F,
	TAG_SMS_STATUS = 0x20,
	TAG_SMS_REFRESH = 0x21,
	TAG_SMS_ADD_CMD_LINE_RULE = 0x22,
	TAG_SMS_DELETE_CMD_LINE_RULE = 0x23,
	TAG_SMS_OVERWRITE_CMD_LINE_RULE = 0x24,
	TAG_SMS_SOFTWARE_INVENTORY = 0x25,
	TAG_SMS_APEX_SENSITVITY = 0x26,
	TAG_SMS_UAV_FULL_SYSTEM_SCAN = 0x27,
	TAG_SMS_UAV_AUTOMATIC_FULL_SYSTEM_SCAN = 0x28,
	TAG_SMS_UAV_ON_DEMAND_SCAN = 0x29,
	TAG_SMS_UAV_REAL_TIME_SCAN = 0x2A,
	TAG_SMS_UAV_DAILY_UPLOAD_LIMIT = 0x2B,
	TAG_SMS_REAL_TIME_SCAN = 0x2C,
	TAG_SMS_USB_SCAN = 0x2D,
	TAG_SMS_SEND_WHITELIST_LOG = 0x2E,
	TAG_SMS_INCLUDE_NETWORK_DRIVES = 0x2F,
	TAG_SMS_AUTO_ADJUST_TRUST_LEVEL = 0x30,
	TAG_SMS_BUNDLED_WITH_SECUREDATA = 0x31,
	TAG_SMS_SOFTWARE_UPDATE_METHOD = 0x32,
	TAG_SMS_SILENT_MODE = 0x33,
	TAG_SMS_REGISTER_AS_ANTIVIRUS = 0x34,
	TAG_SMS_ADD_EXCLUSIONS_LIST = 0x35,
	TAG_SMS_DELETE_EXCLUSIONS_LIST = 0x36,
	TAG_SMS_OVERWRITE_EXCLUSIONS_LIST = 0x37,
	TAG_SMS_AUTOMATIC_MODE = 0x38,
	TAG_SMS_UNKNOWN,
	TAG_SMS_SOFTWARE_INVENTORY_WRONG_IN_VERSION_6_5_0 = 0x55, //should not use this any more
};
