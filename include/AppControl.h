/*++

Copyright (c) 1999-2002  Microsoft Corporation

Module Name:

    scanuk.h

Abstract:

    Header file which contains the structures, type definitions,
    constants, global variables and function prototypes that are
    shared between kernel and user mode.

Environment:

    Kernel & user mode

--*/
#ifndef __APP_CONTROL_H__
#define __APP_CONTROL_H__

#define APPWHITELISTING_HASH_SIZE 32

enum {REWHITELIST_MODE_NONE, REWHITELIST_MODE_SYSTEM_FILES = 1};

#if (APPWHITELISTING_HASH_SIZE == 20)
#define INITIAL_WHITELIST L"InitialDatabase"
#define APPWHITELISTING_HASH_STR_SIZE 41
#endif
#if (APPWHITELISTING_HASH_SIZE == 32)
#define INITIAL_WHITELIST L"InitialWhitelist"
#define REWHITELIST L"ReWhitelist"
#define APPWHITELISTING_HASH_STR_SIZE 65
#endif

#define INITIAL_WHITELIST_SPEED L"InitialWhitelistSpeed"

#pragma pack(push, 1)

//
//  Name of port used to communicate
//
#define AppControlPortName L"\\SAAppCtlPort" //for service to send down command to the driver
#define  AppControlCommandPortName L"\\SAAppCtlCommandPort" //For driver to send command to the service, e.g. requesting to verify digital signature
#define  AppControlNotifierPortName L"\\SAAppCtlNotifierPort" //For driver to send notification to the GUI
#define  AppWhitelistingCmdPortName L"\\SAAppWhitelistingPort" //For used by public

#define PROCESS_FLAG_NO_MORE_PROMPTING_THROUGHOUT_THIS_SESSION  1
#define PROCESS_FLAG_EVERYTHING_EXECUTED_AS_TRUSTED_APPLICATION 2
//#define PROCESS_FLAG_HAS_INTERNET_ACCESS                      4

/*
const PWSTR AppControlPortName = L"\\SAAppCtlPort";
const PWSTR AppControlCommandPortName = L"\\SAAppCtlCommandPort";
*/
#define APPCONTROL_MAX_FILENAME   290 //Maximum name of the filename that we can handle

// Obsolete:
// APPCONTROL_EVENT_BLOCK_EXECUTION, APPCONTROL_EVENT_BLOCK_SCRIPT -> APPCONTROL_NOTIFIER_BLOCK
enum {APPCONTROL_EVENT_PRE_CREATE_FILE_EXECUTE, APPCONTROL_EVENT_PRE_EXECUTE, APPCONTROL_EVENT_CREATE_PROCESS_NOTIFICATION, APPCONTROL_EVENT_TERMINATE_PROCESS_NOTIFICATION, APPCONTROL_EVENT_DELETE_FILE, APPCONTROL_EVENT_RENAME_FILE, APPCONTROL_EVENT_BLOCK_EXECUTION, APPCONTROL_EVENT_BLOCK_SCRIPT, APPCONTROL_EVENT_END};

//Command send to service
enum {APPCONTROL_CMD_VERIFY_DIGITAL_SIGNATURE, APPCONTROL_CMD_GET_USER_NAME_BY_PID, APPCONTROL_CMD_GET_LONG_FILENAME, APPCONTROL_CMD_GET_FILESIZE, APPCONTROL_CMD_GET_HASH_INFO, APPCONTROL_CMD_CALCULATE_AND_UPDATE_HASH, APPCONTROL_CMD_VERIFY_JAVA_SIGNATURE, APPCONTROL_CMD_ADD_FILE_HASH, APPCONTROL_CMD_ADD_FILE_HASH_V2, 
      APPCONTROL_CMD_GET_CERT_INFO, 
	  APPCONTROL_CMD_GET_USER_NAME_BY_SID, 
	  APPCONTROL_CMD_ADD_TRUSTED_CERTIFICATE_BY_FILENAME,
	  APPCONTROL_CMD_DELETE_TRUSTED_CERTIFICATE_BY_FILENAME,
	  APPCONTROL_CMD_SET_UNINSTALL_STRING,
	  APPCONTROL_CMD_SET_UNINSTALLER_BY_UNINSTALL_STRING,
	  APPCONTROL_CMD_ADD_TRUSTED_CERTIFICATE_BY_FILENAME_AND_HASH,
	  APPCONTROL_CMD_SKIP_INITIAL_WHITELIST,
	  APPCONTROL_CMD_GET_ON_DEMAND_WHITELIST_TRUST_LEVEL,
	  APPCONTROL_CMD_END};

//Command send to sanotifier
// APPCONTROL_NOTIFIER_PROMPT_USER_V2 - started in the beginning of UAV.
//APPCONTROL_NOTIFIER_PROMPT_USER_V3 - started in v4.7.3 to support Run as administrator when login as restricted user.
enum {APPCONTROL_NOTIFIER_BLOCK, APPCONTROL_NOTIFIER_PROMPT_USER, APPCONTROL_NOTIFIER_PROMPT_UNTRUSTED_APP_CREATION, APPCONTROL_NOTIFIER_TERMINATE_PROCESS, 
	  APPCONTROL_NOTIFIER_PROMPT_USER_V2, APPCONTROL_NOTIFIER_PROMPT_UNTRUSTED_APP_CREATION_V2, APPCONTROL_NOTIFIER_PROMPT_CMD_LINE, 
	  APPCONTROL_NOTIFIER_GET_ON_DEMAND_WHITELIST_TRUST_LEVEL,
	  APPCONTROL_NOTIFIER_BLOCK_V2,
	  APPCONTROL_NOTIFIER_PROMPT_CMD_LINE_V2,
	  APPCONTROL_NOTIFIER_BLOCK_CMD_LINE,
	  APPCONTROL_NOTIFIER_PROMPT_USER_V3, //Prompt User for trusted account
	  APPCONTROL_NOTIFIER_BLOCK_V3, //Notity file is blocked for trusted account
	  APPCONTROL_NOTIFIER_GET_MAX_SUPPORTED_COMMAND,
	  APPCONTROL_NOTIFIER_END};

//Command send to driver
typedef enum _APPWHITELISTING_CMD_COMMAND {
	APPWHITELISTING_CMD_GET_TRUST_LEVEL, //get trust level by full path name from cache
	APPWHITELISTING_CMD_GET_TRUST_LEVEL_BY_HASH, 
	APPWHITELISTING_CMD_SET_TRUST_LEVEL, 
	APPWHITELISTING_CMD_SET_TRUST_LEVEL_AND_CERTIFICATE, 
	APPWHITELISTING_CMD_DELETE_CACHE,
	APPWHITELISTING_CMD_GET_EXPIRY_DATE,
	APPWHITELISTING_CMD_SET_EXPIRY_DATE,
	APPWHITELISTING_CMD_DELETE_TRUSTED_CERTIFICATE,
	APPWHITELISTING_CMD_ADD_TRUSTED_CERTIFICATE,
	APPWHITELISTING_CMD_GET_NUMBER_OF_WHITELIST_ENTRIES,
	APPWHITELISTING_CMD_SET_APPLICATION_WHITELISTING_MODE, // 0 - Interactive, 1 - LockDown, 2 - Trust all for 5 minutes, 3 - Trust all for 30 minutes, 4 - Trust all until computer restarted
	APPWHITELISTING_CMD_GET_APPLICATION_WHITELISTING_MODE,
	APPWHITELISTING_CMD_SET_BACKGROUND_WHITELIST_SPEED,
	APPWHITELISTING_CMD_ENABLE_FILE_JOURNAL,
	APPWHITELISTING_CMD_OVERWRITE_WHITELIST_TABLE,
	APPWHITELISTING_CMD_GET_MAX_COMMAND,
	APPWHITELISTING_CMD_DELETE_BY_HASH,
	APPWHITELISTING_CMD_COMPACT_WHITELIST_DATABASE,
	APPWHITELISTING_CMD_SET_TRUST_LEVEL_NO_LOG,	
	APPWHITELISTING_CMD_WHITELIST_EXISTS,
	APPWHITELISTING_CMD_STOP_WHITELIST_FILESIZE_FILEHASH,
	APPWHITELISTING_CMD_GET_TRUST_LEVEL_FROM_DB,
	APPWHITELISTING_CMD_START_WHITELIST_FILESIZE_FILEHASH,
	APPWHITELISTING_CMD_END
} APPWHITELISTING_CMD_COMMAND;

enum TrustLevelMode {INVALID_TRUST = -1, NOT_TRUSTED = 0, TRUSTED_APPLICATION, TRUSTED_INSTALLER, FULLY_TRUSTED_APPLICATION, TRUST_LEVEL_OUT_OF_BOUND};

enum UntrustedAppOptions {OPTION_SET_FILE_TRUST_LEVEL, OPTION_SET_SCRIPT_AS_TRUSTED_INSTALLER, OPTION_SET_PROCESS_AS_TRUSTED_INSTALLER, OPTION_ALWAYS_REMAIN_AS_TRUSTED_APPLICATION, OPTION_DO_NOT_DO_ANYTHING, 
						OPTION_SET_PROCESS_AS_TRUSTED_INSTALLER_TEMPORARILY, OPTION_PROCESS_REMAIN_AS_NON_INSTALLER_THROGHOUT_THIS_SESSION};

/*
typedef union _APPCONTROL_NOTIFICATION_PARAM
{

} APPCONTROL_NOTIFICATION_PARAM, *PAPPCONTROL_NOTIFICATION_PARAM;
*/
typedef struct _APPWHITELISTING_CMD {
	union {
		struct
		{
			unsigned __int64 filesize;
			wchar_t filename[1]; //Full path file name
		} GetTrustLevel;

		struct
		{
			unsigned __int64 filesize;
			UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
			wchar_t filename_only[1]; 
		} GetTrustLevelByHash;

		struct
		{
			unsigned __int64 filesize;
			UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
			UCHAR trust_level;
			wchar_t filename_only[1]; 
		} SetTrustLevel;

		struct
		{
			unsigned __int64 filesize;
			UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
			UCHAR trust_level;
			wchar_t filename_only[1]; 
		} SetTrustLevelNoLog; //Driver will not log this operation

		struct
		{
			unsigned __int64 filesize;
			UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
			UCHAR trust_level;
			BOOLEAN bSetNonInstallerList;
			wchar_t filename[1]; //Full path file name
		} SetTrustLevelAndCertificate; // the certificate will be added into trusted certificate

		struct
		{
			wchar_t filename[1]; //Full path file name
		} DeleteCache;

		struct
		{
			unsigned __int64 start_date;
			unsigned __int64 length;
			unsigned __int64 end_date;
		} SetExpiryDate;

		struct
		{
			wchar_t data[1]; //cert common name, followed by thumbprint
		} DeleteTrustedCertificate;

		struct
		{
			UCHAR cn_checksum[8];
			UCHAR checksum[8];
			UCHAR validfrom[8];
			UCHAR validto[8];
			wchar_t data[1]; //cert common name, followed by thumbprint
		} AddTrustedCertificate;

		struct
		{
			ULONG mode; //
		} SetApplicationWhitelistingMode;

		struct
		{
			ULONG speed; //
		} SetBackgroundWhitelistingSpeed;

		struct
		{
			wchar_t filename[1]; //Full path file name
		} OverwriteWhitelistTable;

		struct
		{
			unsigned __int64 filesize;
			UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
			wchar_t filename_only[1]; 
		} DeleteByHash;

		struct
		{
			unsigned __int64 filesize;
			UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
			wchar_t filename_only[1]; 
		} WhitelistExists;

		struct
		{
			unsigned __int64 filesize;
			UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
			UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
			wchar_t filename[1];
		} GetTrustLevelFromDb;
	};
} APPWHITELISTING_CMD, *PAPPWHITELISTING_CMD;

typedef struct _APPWHITELISTING_CMD_REPLY {
	union {
		struct {
			UCHAR trust_level;
		} GetTrustLevel;

		struct {
			UCHAR trust_level;
		} GetTrustLevelFromDb;

		struct {
			UCHAR trust_level;
		} GetTrustLevelByHash;

		struct {
			unsigned long ntstatus;
		} SetTrustLevel;

		struct {
			unsigned long ntstatus;
		} SetTrustLevelAndCertificate;

		struct {
			unsigned long ntstatus;
		} AddTrustedCertificateByFileName;

		struct {
			unsigned long ntstatus;
		} DeleteTrustedCertificateByFileName;

		struct {
			unsigned long ntstatus;
		} SetExpiryDate;

		struct {
			unsigned __int64 number_of_entries;
		} GetNumberOfWhitelistEntries;

		struct {
			unsigned long mode;
			unsigned __int64 trust_all_expiry_time;
		} GetApplicationWhitelistingMode;

		struct {
			unsigned long number_of_cmd; 
		} GetMaxCommand;

		struct {
			BOOLEAN bExists;
		} WhitelistExists;
	};
} APPWHITELISTING_CMD_REPLY, *PAPPWHITELISTING_CMD_REPLY;


typedef struct _APPCONTROL_NOTIFICATION {

	UCHAR Event;
	union {
		struct 
		{
			wchar_t filename[APPCONTROL_MAX_FILENAME];
		} BlockExecution;

		/////////////////////////////////////////////////////////
		// Cmd
		struct
		{
			union {
				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
				} VerifyDigitalSignature;

				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
				} VerifyJavaSignature;

				struct
				{
					HANDLE PID;
				} GetUserNameByPid;

				struct
				{
					wchar_t sidStr[1]; //sid string
				} GetUserNameBySid;

				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
				} GetLongFileName;

				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
				} GetFileSize;

				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
				} GetHashInfo;

				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
					int trust_level;
				} CalculateAndUpdateHash;

				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
					ULONGLONG filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					int trust_level;
					BOOLEAN bIsRemovableMedia;
				} AddFileHash;

				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
					ULONGLONG filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					int trust_level;
					BOOLEAN bIsRemovableMedia;
					BOOLEAN bPermanentlyStored;
					//UCHAR checksum[APPWHITELISTING_HASH_SIZE];
				} AddFileHashV2;

				struct
				{
					wchar_t filename[1];	// [in] - filename
				} GetCertInfo;

				struct
				{
					unsigned short delay; //initial delay in ms
					wchar_t filename[1];	// [in] - filename
				} AddTrustedCertificateByFileName;

				struct
				{
					unsigned short delay; //initial delay in ms
					unsigned __int64 filesize; //for temp filename
					unsigned char hash_standard[APPWHITELISTING_HASH_SIZE]; //for temp filename
					wchar_t filename[1];	// [in] - filename
				} AddTrustedCertificateByFileNameAndHash;

				struct
				{
					unsigned short delay; //initial delay in ms
					wchar_t filename[1];	// [in] - filename
				} DeleteTrustedCertificateByFileName;

				struct
				{
					unsigned char bWow6432Node;
					wchar_t uninstall_sub_key[300];
				} SetUninstallString;

				struct
				{
					wchar_t UninstallString[300];
				} SetUninstallerByUninstallString;

				struct 
				{
					unsigned __int64 filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					UCHAR filename[1];
				} GetOnDemandWhitelistTrustLevel;

			};
		} Cmd;

		/////////////////////////////////////////////////////////
		// Notifier
		struct	{
			union {
				struct 
				{
					UCHAR bObservationMode;
					UCHAR bIsScript;
					HANDLE pid;
					int offsetFilename;
					int offsetProcess;
					UCHAR data[1];
				} BlockExecution;

				struct 
				{
					UCHAR bObservationMode;
					UCHAR bIsScript;
					HANDLE pid;
					int offsetFilename;
					int offsetProcess;
					unsigned __int64 filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					UCHAR data[1];
				} BlockV2;

				struct 
				{
					UCHAR bIsScript;
					HANDLE pid;
					int offsetFilename;
					int offsetProcess;
					UCHAR data[1];
				} PromptUser;

				struct 
				{
					unsigned __int64 filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					UCHAR bIsScript;
					HANDLE pid;
					int offsetFilename;
					int offsetProcess;
					UCHAR data[1];
				} PromptUserV2;

				struct 
				{
					unsigned __int64 filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					UCHAR filename[1];
				} GetOnDemandWhitelistTrustLevel;

				struct 
				{
					UCHAR bIsScript;
					HANDLE pid;
					UCHAR process_trust_level;
					int offsetFilename;
					int offsetProcess;
					int offsetScript;
					UCHAR data[1];
				} UntrustedAppCreation;

				struct 
				{
					UCHAR bIsScript;
					HANDLE pid;
					UCHAR process_trust_level;
					unsigned __int64 process_filesize;
					UCHAR process_hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR process_hash_whole_file[APPWHITELISTING_HASH_SIZE];
					unsigned __int64 filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					int offsetFilename;
					int offsetProcess;
					int offsetScript;
					UCHAR data[1];
				} UntrustedAppCreationV2;

				struct
				{
					HANDLE pid;
				} TerminateProcess;

				struct
				{
					HANDLE pid;
					BOOLEAN bCaseInsensitive;
					int action;
					wchar_t data[1]; //wchar_t *command line
				} PromptCmdLine;

				struct
				{
					HANDLE pid;
					BOOLEAN bCaseInsensitive;
					int action;
					unsigned __int64 cmd_line_size; //in bytes
					UCHAR hash_secureaplus[APPWHITELISTING_HASH_SIZE];
					wchar_t *entry_name;
					UCHAR data[1]; //wchar_t *entry_name
				} PromptCmdLineV2;

				struct
				{
					HANDLE pid;
					unsigned __int64 cmd_line_size; //in bytes
					UCHAR hash_secureaplus[APPWHITELISTING_HASH_SIZE];
					wchar_t *entry_name;
					UCHAR data[1]; //wchar_t *entry_name
				} BlockedCmdLine;

			};
		} Notifier;

	};
    
} APPCONTROL_NOTIFICATION, *PAPPCONTROL_NOTIFICATION;

enum CallbackOnPreCleanupMode {};

typedef struct _APPCONTROL_REPLY {
	union {
		struct 
		{
			BOOLEAN SafeToContinue;
			enum CallbackOnPreCleanupMode CallbackOnPreCleanup;
			int TrustLevel;
		} PostCreate;

		struct
		{
			BOOLEAN bHashIsAvailable;
			BOOLEAN bDoDigitalSignatureVerification;
			int OriginalTrustLevel;
			int CurrentTrustLevel;
			BOOLEAN ElevatedTrustLevel;
			unsigned __int64 Filesize; //file size according to the database
			UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
			UCHAR hash[APPWHITELISTING_HASH_SIZE];
			HANDLE GrandParentPID;
		} PreExecute;

		struct
		{
			union {
				struct
				{
					BOOLEAN Valid;
					unsigned short thumbprintSize;
					unsigned short offsetCN;
					unsigned short offsetThumbprint;
					UCHAR data[1];
				} VerifyDigitalSignature;

				struct
				{
					BOOLEAN Valid;
				} VerifyJavaSignature;

				struct
				{
					wchar_t userName[129];
					wchar_t domainName[129];
				} GetUserNameByPid;

				struct
				{
					ULONG userNameOffset; //offset position is relative to data
					ULONG domainNameOffset;
					ULONG status; //Windows error code
					UCHAR data[1];
				} GetUserNameBySid;

				struct
				{
					WCHAR Filename[APPCONTROL_MAX_FILENAME];
				} GetLongFileName;

				struct
				{
					ULONGLONG filesize;
				} GetFileSize;

				struct
				{
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					ULONGLONG filesize;
					int trust_level;
				} GetHashInfo;

				struct
				{
					ULONG hresult;
					unsigned short dataSize;
					unsigned short thumbprintOffset;
					unsigned short thumbprintSize;
					unsigned short issuedToOffset;
					UCHAR data[540];
				} GetCertInfo;

				struct
				{
					UCHAR trust_level;
					ULONGLONG filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					ULONG windows_error_code;
				} GetOnDemandWhitelistTrustLevel;

			};
		} Cmd;

		/////////////////////////////////////////////////////

		struct
		{
			union {
				struct
				{
					UCHAR trust_level;
					ULONGLONG filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					BOOLEAN bDoNotPromptAnyMore;
					UCHAR process_flag;
				} PromptUser;

				struct
				{
					UCHAR trust_level;
					ULONGLONG filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					BOOLEAN bDoNotPromptAnyMore;
					UCHAR process_flag;
				} PromptUserV2;
				
				struct
				{
					UCHAR trust_level;
					ULONGLONG filesize;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					ULONG windows_error_code;
				} GetOnDemandWhitelistTrustLevel;

				struct
				{
					UCHAR action_option; //defined in: enum UntrustedAppOptions
					UCHAR trust_level;
					BOOLEAN bDoNotPromptAnyMore;
					unsigned short user_name_offset; //the user who responded to this question
					UCHAR data[512];
				} UntrustedAppCreation;

				struct
				{
					UCHAR trust_level;
					UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					BOOLEAN bTrustOnce;
				} PromptCmdLine;
				
				struct
				{
					UCHAR trust_level;
					//UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
					//UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
					BOOLEAN bTrustOnce;
				} PromptCmdLineV2;

				struct
				{
					//UCHAR trust_level;
					//BOOLEAN bTrustOnce;
					unsigned long dwLastError;
				} BlockCmdLine;

				struct
				{
					unsigned long maxCmd;
				} GetMaxSupportedCmd;
			};
		} Notifier;

	};
} APPCONTROL_REPLY, *PAPPCONTROL_REPLY;


typedef enum _APPCONTROL_COMMAND {
    CMD_APP_CONTROL_LOOPBACK,
	CMD_GET_PROCESS_FILE_NAME_BY_PID,
	CMD_GET_PARENT_PID,
	CMD_DELETE_CACHE,
	CMD_LOGOFF,
	CMD_LOGON,
	CMD_SHUTDOWN,
	CMD_ADD_FILE_HASH_DONE,
	CMD_SESSIONCHANGE,
} APPCONTROL_COMMAND;


//
//  Defines the command structure between the utility and the filter.
//

//#pragma warning(push)
#pragma warning(disable:4200) // disable warnings for structures with zero length arrays.

typedef union _APPCONTROL_COMMAND_PARAM
{
	UCHAR Data[];

	struct {
		HANDLE PID;
	} GetProcessFileNameByPid, GetParentPid;

	struct {
		WCHAR Filename[APPCONTROL_MAX_FILENAME];
		unsigned __int64 filesize;
		UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
		UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
	} DeleteCache;

	struct
	{
		wchar_t sid_str[256];
	} LogOff;

	struct
	{
		wchar_t sid_str[129];
		wchar_t user_name[129];
	} LogOn;

	struct
	{
		UCHAR eventType;
		unsigned short offset_sid_str;
		UCHAR data[1];
	} SessionChange;

	struct
	{
		WCHAR filename_only[APPCONTROL_MAX_FILENAME];
		unsigned __int64 filesize;
		UCHAR hash_standard[APPWHITELISTING_HASH_SIZE];
		UCHAR hash_whole_file[APPWHITELISTING_HASH_SIZE];
		BOOLEAN bIsRemovableMedia;
	} AddFileHashDone;

} APPCONTROL_COMMAND_PARAM, *PAPPCONTROL_COMMAND_PARAM;

typedef struct _COMMAND_MESSAGE {
    APPCONTROL_COMMAND Command;
    ULONG Reserved;  // Alignment on IA64
	APPCONTROL_COMMAND_PARAM Param;
} COMMAND_MESSAGE, *PCOMMAND_MESSAGE;

typedef struct _APPWHITELISTING_CMD_MESSAGE {
    APPWHITELISTING_CMD_COMMAND Command;
    ULONG Reserved;  // Alignment on IA64
	APPWHITELISTING_CMD Param;
} APPWHITELISTING_CMD_MESSAGE, *PAPPWHITELISTING_CMD_MESSAGE;

typedef enum _PUBLIC_APPCONTROL_COMMAND {
    CMD_GET_TRUST_LEVEL,
} PUBLIC_APPCONTROL_COMMAND;

typedef union _PUBLIC_APPCONTROL_COMMAND_PARAM
{
	UCHAR Data[];

	struct {
		UCHAR filename[1];
	} GetTrustLevel;

} PUBLIC_APPCONTROL_COMMAND_PARAM, *PPUBLIC_APPCONTROL_COMMAND_PARAM;

typedef union _PUBLIC_APPCONTROL_COMMAND_OUTPUT
{
	UCHAR Data[];

	struct {
		UCHAR trust_level;
	} GetTrustLevel;

} PUBLIC_APPCONTROL_COMMAND_OUTPUT, *PPUBLIC_APPCONTROL_COMMAND_OUTPUT;

typedef struct _PUBLIC_COMMAND_MESSAGE {
    PUBLIC_APPCONTROL_COMMAND Command;
    ULONG Reserved;  // Alignment on IA64
	PUBLIC_APPCONTROL_COMMAND_PARAM Param;
} PUBLIC_COMMAND_MESSAGE, *PPUBLIC_COMMAND_MESSAGE;

//#pragma warning(pop)
#pragma pack(pop)
#endif //  __SCANUK_H__


