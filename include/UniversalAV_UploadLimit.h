#ifndef _UAV_UPLOAD_LIMIT_H_
#define _UAV_UPLOAD_LIMIT_H_
// For UAV service, defined the following:
// #define UAV_SERVER

#define UPLOAD_LIMIT_1GB 1073741824
#define UPLOAD_LIMIT_100MB 104857600
#define UPLOAD_LIMIT_10MB 10485760
#define UPLOAD_LIMIT_UNLIMITED 0xffffffffffffffff


DWORD reg_create_uav_upload_limit_sub_keys();

BOOLEAN is_filesize_larger_than_upload_limit(ULONGLONG filesize);

ULONGLONG uav_get_daily_upload_limit();
DWORD uav_set_daily_upload_limit(ULONGLONG upload_limit_in_bytes);

//return Windows error code
DWORD uav_set_today_total_upload(ULONGLONG total_upload);

//return total number of bytes of the uploaded files

//ULONGLONG uav_add_today_total_upload(ULONGLONG filesize);

DWORD uav_increment_today_upload_counter(LPCWSTR EntryName);
ULONGLONG uav_get_today_upload_value(LPCWSTR EntryName);

BOOLEAN is_exceeding_uav_upload_limit(ULONGLONG filesize);

BOOLEAN uav_consume_upload_quota(LPCWSTR filename, ULONGLONG filesize, OUT OPTIONAL ULONGLONG *ptotal_number_of_bytes_taken_today = NULL);
ULONGLONG uav_increment_total_number_of_uploaded_file_today(OPTIONAL LPCWSTR filename = NULL, OPTIONAL ULONGLONG filesize = 0, OPTIONAL ULONGLONG compressed_filesize = 0);

ULONGLONG uav_credit_to_upload_quota(ULONGLONG credit_size_in_bytes, OPTIONAL LPCWSTR filename = NULL);

#ifndef UAV_SERVER
BOOLEAN NamedPipeUniversalAVUI_IsUploadEnabled();
#endif

#define uav_add_today_total_number_of_requested_files() uav_increment_today_upload_counter(L"NumberOfRequestedFiles")
#define uav_add_today_total_number_of_missing_files() uav_increment_today_upload_counter(L"NumberOfMissingFiles")

#define uav_get_today_total_upload() uav_get_today_upload_value(L"TotalUpload")
#define uav_get_today_number_of_uploaded_files() uav_get_today_upload_value(L"NumberOfUploadedFiles")
#define uav_get_today_total_number_of_requested_files() uav_get_today_upload_value(L"NumberOfRequestedFiles")
#define uav_get_today_total_number_of_missing_files() uav_get_today_upload_value(L"NumberOfMissingFiles")

#endif