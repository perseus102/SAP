#ifndef _CMD_LINE_RULES_H_
#define _CMD_LINE_RULES_H_

#include "CmdLineRulesDef.h"

DWORD CreateDefaultCmdLineRules(BOOLEAN bRefresh);

DWORD SaveCmdLineRule(const wchar_t *command, const wchar_t *param_rule);

void add_rule(wchar_t **buffer, size_t *pmax_buffer_size_in_wchar, int rule, BOOLEAN bCaseInSensitive, const wchar_t *parameter, int action);

BOOLEAN enum_command_line_rules(const wchar_t *param_rule, BOOLEAN (*callback)(void *context, int rule, BOOLEAN bCaseInsensitive, const wchar_t*param, int action), OPTIONAL void *context = NULL);

//return the action
int is_parameter_match_command_line_rules(const wchar_t *parameter, const wchar_t *param_rule, OUT OPTIONAL BOOLEAN *pbCaseInsensitive);
int is_parameter_match_command_line_rules(const wchar_t *command_line_with_parameter, OUT OPTIONAL BOOLEAN *pbCaseInsensitive);
int exists_in_command_line_rules(const wchar_t *param_rule, int rule, BOOLEAN bCaseInsensitive, const wchar_t *parameter, int action);

BOOLEAN update_cmd_line_rule(wchar_t *param_rule, size_t param_rule_size, const wchar_t *command, int rule, BOOLEAN bCaseInsensitive, const wchar_t *parameter, int action, OPTIONAL OUT BOOLEAN *bNotChanged = NULL);

DWORD AddCmdLineRule(const wchar_t *command, int rule, BOOLEAN bCaseInsensitive, const wchar_t *parameter, int action, OPTIONAL OUT BOOLEAN *bNewRule = NULL, OPTIONAL OUT BOOLEAN *bUpdateRule = NULL);
DWORD DeleteCmdLineRule(const wchar_t *command, int rule, BOOLEAN bCaseInsensitive, const wchar_t *parameter, int action);

DWORD EnumCmdLineRules(BOOLEAN (*callback)(void *context, const wchar_t *command, int rule, BOOLEAN bCaseInsensitive, const wchar_t *param, int action), OPTIONAL LPVOID lpContext = NULL, OPTIONAL HANDLE hStopEvent = NULL, OPTIONAL BOOLEAN(*callback_raw_data)(LPVOID lpContext, LPCWSTR command, LPCWSTR rules) = NULL, OPTIONAL BOOLEAN(*callback_progress)(LPVOID lpContext, ULONGLONG pos, ULONGLONG max) = NULL);

wchar_t *cmd_line_compare_rule_to_string(int compare_rule);
wchar_t *cmd_line_case_sensitivity_to_string(int case_sensitivity);
wchar_t *cmd_line_action_to_string(int action);

wchar_t *load_cmd_line_rules(wchar_t *command);

#endif

