#ifndef _UNIVERSAL_AV_H_

#define _UNIVERSAL_AV_H_

#include "AppControl.h"
#include "av_engine_and_virus.h"
#include "UniversalAV_Classified.h"

#define UNIVERSALAV_FTP_PORT INTERNET_DEFAULT_FTP_PORT

enum {UAV_ON_DEMAND_STATUS_CLEAN, UAV_ON_DEMAND_STATUS_VIRUS, UAV_ON_DEMAND_STATUS_UNKNOWN, UAV_ON_DEMAND_STATUS_UNKNOWN_BUT_SAMPLE_EXISTS};

typedef BOOLEAN (*callback_uav_whitelist_entry)(LPVOID context, const char *filename, ULONGLONG filesize, BYTE *hash, BYTE trust_level);
typedef BOOLEAN (*callback_uav_progress_bar)(LPVOID context, ULONGLONG pos, ULONGLONG max);

typedef struct _PARAM_UPLOAD_FILE
{
	char *utf8_filename_only;
	char *remote_filename_only;
	ULONGLONG filesize;
	BYTE *hash;
	size_t hash_size;
	DWORD dwLastError;
	wchar_t *full_path_filename; //OUT - source file
	BOOLEAN bNotApplicable; //NOT for upload
	BOOLEAN bExcluded;
	BOOLEAN bSuccessfullyUploaded;
} PARAM_UPLOAD_FILE, *PPARAM_UPLOAD_FILE;

enum {UAV_NAMED_PIPE_REPORT_MISSING_FILE = 1, UAV_NAMED_PIPE_GET_CURRENT_STATUS, 
      UAV_NAMED_PIPE_GET_NEW_WHITELIST_INFO, UAV_NAMED_PIPE_GET_SAMPLE_FILE_INFO,
	  UAV_NAMED_PIPE_GET_SCAN_RESULT,
	  UAV_NAMED_PIPE_IS_SUBMIT_FOR_SCAN_ENABLED,
	  UAV_NAMED_PIPE_SUBMIT_FOR_SCAN,
	  UAV_NAMED_PIPE_GET_NUMBER_OF_UPLOADED_HASH,
	  UAV_NAMED_PIPE_GET_NUMBER_OF_LOCAL_NTFS_HARD_DISK,
	  UAV_NAMED_PIPE_GET_SCAN_RESULT_V2,
	  UAV_NAMED_PIPE_SET_DAILY_UPLOAD_LIMIT,
	  UAV_NAMED_PIPE_IS_PROCESSING_SCAN_RESULT,
	  UAV_NAMED_PIPE_REFRESH_SCAN_RESULT,
	  UAV_NAMED_PIPE_PURGE_UAV_LOG,
	  UAV_NAMED_PIPE_IS_UPLOAD_ENABLED,
	  UAV_NAMED_PIPE_ENABLE_UPLOAD,
	  UAV_NAMED_PIPE_ENABLE_GOOD_NEWS,
	  UAV_NAMED_PIPE_CONSUME_QUOTA,
	  UAV_NAMED_PIPE_INCREMENT_TOTAL_NUMBER_OF_UPLOADED_FILE_TODAY,
	  UAV_NAMED_PIPE_CREDIT_TO_UPLOAD_QUOTA,
	  UAV_NAMED_PIPE_SAVE_UAV_ENGINES,
	  UAV_NAMED_PIPE_SAVE_EXCLUDED_UAV_ENGINES,
	  UAV_NAMED_PIPE_ENABLE_SEARCH_OPTIMIZATION,
	  UAV_NAMED_PIPE_REFRESH_UAV_STATUS,
	  UAV_NAMED_PIPE_UNSUPPORTED
};

enum {UAV_UI_NAMED_PIPE_EXIT = 1,
	  UAV_UI_NAMED_PIPE_SET_CURRENT_STATUS = 200, 
      UAV_UI_NAMED_PIPE_SET_PROGRESS_BAR, UAV_UI_NAMED_PIPE_HIDE_PROGRESS_BAR,
	  UAV_UI_NAMED_PIPE_SET_NEW_WHITELIST_INFO,
	  UAV_UI_NAMED_PIPE_SET_SAMPLE_FILE_INFO,
	  UAV_UI_NAMED_PIPE_SET_SCAN_RESULT,
	  UAV_UI_NAMED_PIPE_ENABLE_SUBMIT_FOR_SCAN,
	  UAV_UI_NAMED_PIPE_SET_NUMBER_OF_UPLOADED_HASH,
	  UAV_UI_NAMED_PIPE_SET_SCAN_RESULT_V2,
	  UAV_UI_NAMED_PIPE_SET_NUMBER_OF_LOCAL_NTFS_HARD_DISK,
	  UAV_UI_NAMED_PIPE_SET_SCAN_RESULT_NUMBER_OF_INFECTED_FILES,
	  UAV_UI_NAMED_PIPE_SET_SCAN_RESULT_NUMBER_OF_EXCLUDED_FILES
};

//Application requests to service
typedef struct _UAV_NAMED_PIPE_CMD
{
	unsigned short cmd;
	DWORD size;

	union {
		struct
		{
			unsigned __int64 filesize;
			BYTE hash[APPWHITELISTING_HASH_SIZE];
			char utf8_filename[1]; //file name only (without path)
		} ReportMissingFile;

		struct
		{
			ULONGLONG upload_limit_in_bytes;
		} SetSetDailyUploadLimit;

		struct
		{
			BOOLEAN bEnable;
		} EnableUpload;

		struct
		{
			BOOLEAN bEnable;
		} EnableGoodNews;

		struct
		{
			BOOLEAN bEnable;
		} EnableSearchOptimization;

		struct
		{
			ULONGLONG filesize;
			wchar_t filename[1];
		} ConsumeQuota;

		struct
		{
			ULONGLONG filesize;
			ULONGLONG compressed_filesize;
			wchar_t filename[1];
		} IncrementTotalNumberOfUploadedFileToday;

		struct
		{
			ULONGLONG credit_size_in_bytes;
			wchar_t filename[1];
		} CreditToUploadQuota;

		struct
		{
			char data[1];
		} SaveUAVEngines;

		struct
		{
			char data[1];
		} SaveExcludedUAVEngines;

		/*
		struct
		{
			ULONGLONG number_of_infected_files;
			ULONGLONG number_of_additional_excluded_files;
		} UpdateUAVStatus;
		*/
	};

} UAV_NAMED_PIPE_CMD, *PUAV_NAMED_PIPE_CMD;

typedef struct _UAV_NAMED_PIPE_REPLY
{
	DWORD size;
	DWORD dwLastError;

	union {
		struct
		{
			wchar_t msg[1];
		} GetCurrentStatus;
		struct
		{
			ULONGLONG number_of_new_whitelist; //new hashes
			ULONGLONG number_of_new_whitelist_missing; //hashes without sample file
		} GetNewWhitelistInfo;
		struct
		{
			ULONGLONG number_of_requested_file_by_the_server;
			ULONGLONG number_of_files_successfully_uploaded;
			ULONGLONG number_of_files_not_successfully_uploaded;
			ULONGLONG number_of_missing_files;
		} GetSampleFileInfo;

		struct
		{
			ULONGLONG number_of_clean_hashes;
			ULONGLONG number_of_not_uploaded_sample;
			ULONGLONG number_of_infected_hashes;
			ULONGLONG number_of_infected_files;
			ULONGLONG number_of_failed_uploaded_files;
			ULONGLONG number_of_missing_files;
		} GetScanResult;

		struct
		{
			BOOLEAN bEnabled;
		} IsSubmitForScanEnabled;

		struct
		{
			ULONGLONG number_of_uploaded_hash;
		} GetNumberOfUploadedHash;

		struct
		{
			BYTE number_of_hard_disk;
			BOOLEAN ntfs_drive[26];
		} GetLocalNTFSHardDisk;

		struct
		{
			ULONGLONG number_of_clean_hashes;
			ULONGLONG number_of_not_uploaded_sample;
			ULONGLONG number_of_infected_hashes;
			ULONGLONG number_of_infected_files;
			ULONGLONG number_of_failed_uploaded_files;
			ULONGLONG number_of_missing_files;
			ULONGLONG number_of_ignored_malware_files;
			ULONGLONG number_of_quarantine_files;
		} GetScanResultV2;

		struct
		{
			DWORD dwLastError;
		} SetSetDailyUploadLimit;

		struct
		{
			BOOLEAN bInProgress;
		} IsProcessingScanResult;

		struct
		{
			BOOLEAN bEnabled;
		} IsUploadEnabled;

		struct
		{
			DWORD dwLastError;
		} EnableGoodNews;

		struct
		{
			DWORD dwLastError;
		} EnableSearchOptimization;

		struct
		{
			DWORD dwLastError;
			BOOLEAN bAllowed;
			ULONGLONG total_number_of_bytes_taken_today;
		} ConsumeQuota;

		struct
		{
			DWORD dwLastError;
			ULONGLONG total_number_of_uploaded_file_today;
		} IncrementTotalNumberOfUploadedFileToday;

		struct
		{
			DWORD dwLastError;
			ULONGLONG total_bytes_uploaded_today;
		} CreditToUploadQuota;
	};
} UAV_NAMED_PIPE_REPLY, *PUAV_NAMED_PIPE_REPLY;

//Service send to the UI
typedef struct _UAV_UI_NAMED_PIPE_CMD
{
	unsigned short cmd;
	DWORD size;

	union {
		struct
		{
			wchar_t msg[1];
		} SetCurrentStatus;

		struct
		{
			ULONGLONG current;
			ULONGLONG max;
			wchar_t unit[1];
		} SetProgressBar;

		struct
		{
			ULONGLONG number_of_new_whitelist; //new hashes
			ULONGLONG number_of_new_whitelist_missing; //hashes without sample file
		} SetNewWhitelistInfo;

		struct
		{
			ULONGLONG number_of_requested_file_by_the_server;
			ULONGLONG number_of_files_successfully_uploaded;
			ULONGLONG number_of_files_not_successfully_uploaded;
			ULONGLONG number_of_missing_files;
		} SetSampleFileInfo;

		struct
		{
			ULONGLONG number_of_clean_hashes;
			ULONGLONG number_of_not_uploaded_sample;
			ULONGLONG number_of_infected_hashes;
			ULONGLONG number_of_infected_files;
			ULONGLONG number_of_failed_uploaded_files;
			ULONGLONG number_of_missing_files; //number of missing files + NA
		} SetScanResult;

		struct
		{
			ULONGLONG number_of_clean_hashes;
			ULONGLONG number_of_not_uploaded_sample;
			ULONGLONG number_of_infected_hashes;
			ULONGLONG number_of_infected_files;
			ULONGLONG number_of_failed_uploaded_files;
			ULONGLONG number_of_missing_files; //number of missing files + NA
			ULONGLONG number_of_ignored_malware_files;
			ULONGLONG number_of_quarantine_files;
		} SetScanResultV2;

		struct
		{
			BOOLEAN bEnable;
		} EnableSubmitForScan;

		struct
		{
			ULONGLONG number_of_uploaded_hash;
		} SetNumberOfUploadedHash;

		struct
		{
			BYTE number_of_hard_disk;
			BOOLEAN ntfs_drive[26];
		} SetLocalNTFSHardDisk;

		struct
		{
			ULONGLONG number_of_infected_files;
		} SetScanResultNumberOfInfectedFiles;

		struct
		{
			ULONGLONG number_of_excluded_files;
		} SetScanResultNumberOfExcludedFiles;
	};

} UAV_UI_NAMED_PIPE_CMD, *PUAV_UI_NAMED_PIPE_CMD;

typedef struct _UAV_UI_NAMED_PIPE_REPLY
{
	DWORD size;
	DWORD dwLastError;
} UAV_UI_NAMED_PIPE_REPLY, *PUAV_UI__NAMED_PIPE_REPLY;

wchar_t *GetUniversalAVServerW();
char *GetUniversalAVServerA();

unsigned short GetUniversalAVServerPort();

#define uav_http_with_param(lpszVerb, lpszObjectName, preply, format, ...) _http_with_param(GetUniversalAVServerPort(), GetUniversalAVServerPort()==80?FALSE:TRUE, GetUniversalAVServerA(), lpszVerb, lpszObjectName, preply, format, __VA_ARGS__)
#define uav_http_with_header(lpszVerb, lpszObjectName, lplpszAcceptTypes, lpszHeaders, lpOptional, phSession, phConnect, phRequest) _http(GetUniversalAVServerPort(), GetUniversalAVServerPort()==80?FALSE:TRUE, GetUniversalAVServerA(), lpszVerb, lpszObjectName, NULL, lplpszAcceptTypes, NULL, lpszHeaders, lpszHeaders?(DWORD)strlen(lpszHeaders):0, lpOptional, lpOptional?(DWORD)strlen(lpOptional):0, phSession, phConnect, phRequest)
#define uav_http_fixed_buffer(lpszVerb_POST_or_GET, script_name, wcs_status_code, wcs_status_code_size_in_wchar, response, response_size, format, ...) _http_fixed_buffer(GetUniversalAVServerPort(), GetUniversalAVServerPort()==80?FALSE:TRUE, TRUE, GetUniversalAVServerA(), lpszVerb_POST_or_GET, script_name, wcs_status_code, wcs_status_code_size_in_wchar, response, response_size, format, ##__VA_ARGS__)
#define uav_http_fixed_buffer_no_log(lpszVerb_POST_or_GET, script_name, wcs_status_code, wcs_status_code_size_in_wchar, response, response_size, format, ...) _http_fixed_buffer(GetUniversalAVServerPort(), GetUniversalAVServerPort()==80?FALSE:TRUE, FALSE, GetUniversalAVServerA(), lpszVerb_POST_or_GET, script_name, wcs_status_code, wcs_status_code_size_in_wchar, response, response_size, format, ##__VA_ARGS__)

#define uav_http_download(context, lpszVerb, source_filename, target_filename, delete_target_file_upon_success, timeout_in_ms, progress_callback, error_callback) _http_download(GetUniversalAVServerPort(), GetUniversalAVServerPort()==80?FALSE:TRUE, context, GetUniversalAVServerA(), lpszVerb, source_filename, target_filename, delete_target_file_upon_success, timeout_in_ms, progress_callback, error_callback)

//user must free the result
wchar_t *GetWhitelistFtpUser();
wchar_t *GetWhitelistFtpPassword();

const char *get_universal_av_source_string();

//http
/*
//Obsolete - UniversalAVUploadWhitelist() and UniversalAVUploadWhitelistMissing()
DWORD NotifyWhitelistUpload(LPCSTR remote_filename);
DWORD NotifyWhitelistMissing(LPCSTR remote_filename, BYTE *checksum, int checksum_size);
*/

/*
It uses POST command, and take 5 parameters as follow:

MachineID=eGNTomKR-87
Version=1.0
Source=<Gold|Sample>
Filename= 0A4E2EEA6A9B31F1B9F36387B3FB304F608A2C27711EF509D5B89426A3348E4A_5517312
Utf8FilenameOnly = SSHClient3.2.9.exe
Status=<Success|Fail|Missing>

After processing, it will return “OK” after successfully execution, otherwise, it will return appropriate error text.
*/
DWORD NotifyFileStatus(LPCSTR utf8_filename_only, char *filename_only, const char *status, OUT char **reply);
DWORD NotifyFileStatusMissing(LPCSTR utf8_filename_only, ULONGLONG filesize, LPCSTR hash_string, OUT char **reply);

/*
param:
Version=2.0
Filename= 0A4E2EEA6A9B31F1B9F36387B3FB304F608A2C27711EF509D5B89426A3348E4A_5517312
*/
DWORD NotifyFileUploadV2(char *remote_filename_only, OUT char **reply);

/*
output:

<filename>|<filesize>|<file hash>

If not found, I will return either "No record found"
Or "All files uploaded" if you have previously uploaded all the files.
*/
DWORD GetNextFileToUpload(OUT char **reply);

/////////////////////////////////////////////////

// utf8_filename_only - can be NULL
char *universal_av_create_sample_filename(OPTIONAL char *utf8_filename_only, ULONGLONG filesize, const char *hash_in_hex_str);

DWORD UniversalAV_reset_failed_files(OPTIONAL OUT char **reply);

DWORD UniversalAV_NotifyGetServerScanResultDone(LPCSTR source_filename, OPTIONAL OUT char **reply);

BOOLEAN Is_UniversalAV_File_For_Upload(LPCWSTR filename);

char *universal_av_create_sample_filename(char *utf8_filename_only, ULONGLONG filesize, const char *hash_in_hex_str);

BOOLEAN UniversalAV_whitelist_data_parser(char *str, OUT char **filename, OUT ULONGLONG *filesize, OUT BYTE **hash, OUT DWORD *hash_size, OUT char **hash_in_hex_str);

//status=<Success|Fail|Missing|NA>
DWORD universal_av_report_status(char *status, LPCSTR utf8_filename_only, ULONGLONG filesize, BYTE *hash, size_t hash_size);
DWORD universal_av_report_missing_file(LPCSTR utf8_filename_only, ULONGLONG filesize, BYTE *hash, size_t hash_size);

DWORD UniversalAV_CheckWhitelistDone(OUT OPTIONAL char *reply, OPTIONAL IN size_t reply_size);

DWORD reg_create_uav_sub_keys(HKEY hkey);

DWORD set_uav_last_scan(HKEY hkey);
ULONGLONG get_uav_last_scan(HKEY hkey);

BOOLEAN callback_universalav_default_progress_bar(LPVOID lpContext, ULONGLONG pos, ULONGLONG max);

DWORD UniversalAV_notify_uninstall(OPTIONAL OUT char **reply);

//user is responsible to free the result.
//Example: get_timestamp_machine_id_filename("whitelistmissing.txt");
//Result: 20140519033954_eGNTomKR-87_whitelistmissing.txt
wchar_t *get_timestamp_machine_id_filename(LPCWSTR additional_filename);

DWORD UniversalAV_SetMachineStatus(LPCSTR remote_filename);

////////////////////////////////////////////////////////////////////////////////////
void free_uav_scan_result(int number_of_av_engine, PAV_ENGINE_AND_VIRUS result);

void uav_pick_virus_name(OUT CStringW &str_virus_name, int number_of_av_engine, PAV_ENGINE_AND_VIRUS scan_result);
void uav_pick_virus_nameA(OUT CStringA &str_virus_name, int number_of_av_engine, PAV_ENGINE_AND_VIRUS scan_result);

void get_av_engine_name(CStringW &output, int number_of_av_engine, PAV_ENGINE_AND_VIRUS scan_result);
void get_av_engine_nameA(CStringA &output, int number_of_av_engine, PAV_ENGINE_AND_VIRUS scan_result);
////////////////////////////////////////////////////////////////////////////////////

BOOLEAN Is_UniversalAV_Included_Extension(const wchar_t *filename_ext, const wchar_t *filename);
BOOLEAN IsUniversalAVIncludedHeader(BYTE *buffer);

////////////////////////////////////////////////////////////////////////////////////
DWORD uav_fixed_ip_ping();
DWORD uav_ping();

BOOLEAN is_universal_av_server_alive();
DWORD wait_until_universal_av_server_available(BOOLEAN bNoRetry = FALSE);
////////////////////////////////////////////////////////////////////////////////////

//By default it is enabled.
//When it is enabled, file that is not found by Everything Search Engine will be deleted from whitelist database.
//To optimize the searching, if the file is no longer found in whitelist database, the file will be skipped.
//		RegQueryDwordValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\SecureAge Technology\\SecureAge\\Applications\\UniversalAV", L"DisableSearchOptimization", &result);
BOOLEAN IsDisableSearchOptimization(OPTIONAL BOOLEAN bRefresh = FALSE);

//return 0 - if it is json file, otherwise return windows error code;
DWORD CheckUnversalAVJsonFile(LPCSTR FileName);

////////////////////////////////////////////////////////////////////////////////////
enum {UAV_UPLOAD_TYPE_EXECUTABLE, UAV_UPLOAD_TYPE_ANY_TYPE_OF_FILES, UAV_UPLOAD_TYPE_EXECUTABLE_AND_SCRIPT};

BOOLEAN isUAVUploadFileTypeAvailable();
DWORD getUAVUploadFileType();
DWORD setUAVUploadFileType(DWORD dwType);

#endif