#pragma once
#include "Config.h"

/* Define product name */
#define PRODUCT_NAME "SecureAPlus"
#define PRODUCT_NAME_W L"SecureAPlus"

/* Define navigation button background color */
#define NAVIGATION_BTN_BACKGROUND_DARK		QString("Color/Navi_btn_Background_Dark_Type")
#define NAVIGATION_BTN_BACKGROUND_LIGHT		QString("Color/Navi_btn_Background_Light_Type")

/* Define navigation button gradient color */
#define NAVIGATION_BTN_GRADIENT_START_DARK	QString("Color/Navi_Btn_Gradient_Start_Dark")
#define NAVIGATION_BTN_GRADIENT_START_LIGHT	QString("Color/Navi_Btn_Gradient_Start_Light")
#define NAVIGATION_BTN_GRADIENT_END			QString("Color/Navi_Btn_Gradient_End")

/* Define theme color */
#define DARK_MODE_BACKGROUND				QString("Color/Dark_Background")
#define LIGHT_MODE_BACKGROUND				QString("Color/Light_Background")

/* Define color icon of home button */
#define HOME_PROTECTED						QString("Color/Home_Protected")
#define HOME_WARNING						QString("Color/Home_Warning")

/* Define for text and icon color */
#define TEXT_ICON_COLOR_LIGHT_THEME_PATH	QString("Color/Text_Icon_Color_Light_Theme")
#define TEXT_ICON_COLOR_DARK_THEME_PATH		QString("Color/Text_Icon_Color_Dark_Theme")
#define TEXT_ICON_COLOR_ACTIVE_PATH			QString("Color/Text_Icon_Color_Active")

/* Define for main content */
#define MAIN_BACKGROUND_LIGHT_THEME			QString("Main Content/Background_Light_Theme")
#define MAIN_BACKGROUND_DARK_THEME			QString("Main Content/Background_Dark_Theme")

/* Define Home Main Content */
#define HOME_PROTECTED_TEXT					QString("Home Content/Protected_Text_Color")
#define HOME_AT_RICK_TEXT					QString("Home Content/At_Rick_Text_Color")
#define LAST_SCAN_TEXT_DARK_THEME			QString("Home Content/Last_Scan_Color_Dark_Theme")
#define LAST_SCAN_TEXT_LIGHT_THEME			QString("Home Content/Last_Scan_Color_Light_Theme")
#define SECURE_FEATURE_DARK_THEME			QString("Home Content/Security_Feature_Color_Dark_Theme")
#define SECURE_FEATURE_LIGHT_THEME			QString("Home Content/Security_Feature_Color_Light_Theme")
#define DETAILS_TEXT_DARK_THEME				QString("Home Content/Details_Text_Color_Dark_Theme")
#define DETAILS_TEXT_LIGHT_THEME			QString("Home Content/Details_Text_Color_Light_Theme")
#define SCAN_NOW_BUTTON						QString("Home Content/Scan_Now_Button_Color")


/* Define for Grid Widget */
#define GRID_BACKGROUND_DARK_THEME			QString("Grid Widget/Grid_Background_Dark_Theme")
#define GRID_BACKGROUND_LIGHT_THEME			QString("Grid Widget/Grid_Background_Light_Theme")
#define GRID_BORDER_DARK_THEME				QString("Grid Widget/Grid_Border_Dark_Theme")
#define GRID_BORDER_LIGHT_THEME				QString("Grid Widget/Grid_Border_Light_Theme")
#define GRID_ICON_DARK_THEME				QString("Grid Widget/Grid_Icon_Dark_Theme")
#define GRID_ICON_LIGHT_THEME				QString("Grid Widget/Grid_Icon_Light_Theme")
#define GRID_TITLE_DARK_THEME				QString("Grid Widget/Grid_Tittle_Color_Dark_Theme")
#define GRID_TITLE_LIGHT_THEME				QString("Grid Widget/Grid_Tittle_Color_Light_Theme")
#define GRID_SUB_TITLE_DARK_THEME			QString("Grid Widget/Grid_Sub_Tittle_Color_Dark_Theme")
#define GRID_SUB_TITLE_LIGHT_THEME			QString("Grid Widget/Grid_Sub_iTittle_Color_Light_Theme")

/* Define for Top Bar */
#define BACK_BUTTON_LIGHT_THEME				QString("Top Bar/Back_Button_Light_Theme")
#define BACK_BUTTON_DARK_THEME				QString("Top Bar/Back_Button_Dark_Theme")
#define TOP_BAR_TEXT_DARK_THEME				QString("Top Bar/Text_Color_Dark_Theme")
#define TOP_BAR_TEXT_LIGHT_THEME			QString("Top Bar/Text_Color_Light_Theme")

/* Define for toggle */
#define THUMB_CHECKED_DARK_THEME			QString("Toggle/Thumb_Checked_Dark_Theme")
#define THUMB_CHECKED_LIGHT_THEME			QString("Toggle/Thumb_Checked_Light_Theme")
#define THUMB_UNCHECKED_DARK_THEME			QString("Toggle/Thumb_Unchecked_Dark_Theme")
#define THUMB_UNCHECKED_LIGHT_THEME			QString("Toggle/Thumb_Unchecked_Light_Theme")
#define TRACK_CHECKED_DARK_THEME			QString("Toggle/Track_Checked_Dark_Theme")
#define TRACK_CHECKED_LIGHT_THEME			QString("Toggle/Track_Checked_Light_Theme")
#define TRACK_UNCHECKED_DARK_THEME			QString("Toggle/Track_Unchecked_Dark_Theme")
#define TRACK_UNCHECKED_LIGHT_THEME			QString("Toggle/Track_Unchecked_Light_Theme")
#define TEXT_DARK_THEME						QString("Toggle/Text_Dark_Theme")
#define TEXT_LIGHT_THEME					QString("Toggle/Text_Light_Theme")

/* Define for language and personalization */
#define	LANG_PERS_TEXT_DARK_THEME			QString("Language Personal/Lang_Pers_Text_Dark_Theme")
#define	LANG_PERS_TEXT_LIGHT_THEME			QString("Language Personal/Lang_Pers_Text_Light_Theme")

/* Protection Modes And Status */
#define LABEL_ICON_SELECTED_BACKGROUND_LT	QString("Protection Modes And Status/Icon_Selected_Background_Light_Theme")
#define LABEL_ICON_SELECTED_BACKGROUND_DT	QString("Protection Modes And Status/Icon_Selected_Background_Dark_Theme")
#define ICON_SELECTED_LT					QString("Protection Modes And Status/Icon_Selected_Color_Light_Theme")
#define ICON_SELECTED_DT					QString("Protection Modes And Status/Icon_Selected_Color_Dark_Theme")
#define LABEL_ICON_UNSELECTED_BACKGROUND_LT	QString("Protection Modes And Status/Icon_Unselected_Background_Light_Theme")
#define LABEL_ICON_UNSELECTED_BACKGROUND_DT	QString("Protection Modes And Status/Icon_Unselected_Background_Dark_Theme")
#define ICON_UNSELECTED_LT					QString("Protection Modes And Status/Icon_Unselected_Color_Light_Theme")
#define ICON_UNSELECTED_DT					QString("Protection Modes And Status/Icon_Unselected_Color_Dark_Theme")
#define WDG_SELECTED_BGROUND_LT				QString("Protection Modes And Status/Widget_Selected_Background_Light_Theme")
#define WDG_SELECTED_BGROUND_DT				QString("Protection Modes And Status/Widget_Selected_Background_Dark_Theme")
#define WDG_UNSELECTED_BGROUND_LT			QString("Protection Modes And Status/Widget_Unselected_Background_Light_Theme")
#define WDG_UNSELECTED_BGROUND_DT			QString("Protection Modes And Status/Widget_Unselected_Background_Dark_Theme")
#define TITLTE_SELECTED_LT					QString("Protection Modes And Status/Title_Selected_Light_Theme")
#define TITLTE_SELECTED_DT					QString("Protection Modes And Status/Title_Selected_Dark_Theme")
#define TITLTE_UNSELECTED_LT				QString("Protection Modes And Status/Title_Uselected_Light_Theme")
#define TITLTE_UNSELECTED_DT				QString("Protection Modes And Status/Title_Uselected_Dark_Theme")
#define TITLE_TEXT_DT						QString("Protection Modes And Status/Title_Text_Dark_Theme")
#define TITLE_TEXT_LT						QString("Protection Modes And Status/Title_Text_Light_Theme")
#define MODE_TITLE_TEXT_LT					QString("Protection Modes And Status/Mode_Title_Text_Light_Theme")
#define MODE_TITLE_TEXT_DT					QString("Protection Modes And Status/Mode_Title_Text_Dark_Theme")
#define DESCRIPTION_TEXT_LT					QString("Protection Modes And Status/Description_Light_Theme")
#define DESCRIPTION_TEXT_DT					QString("Protection Modes And Status/Description_Dark_Theme")
#define PRO_ICON_UNSELECTED_LT				QString("Protection Modes And Status/Pro_Icon_Unselected_Light_Theme")
#define PRO_ICON_UNSELECTED_DT				QString("Protection Modes And Status/Pro_Icon_Unselected_Dark_Theme")
#define PRO_ICON_SELECTED_LT				QString("Protection Modes And Status/Pro_Icon_Selected_Light_Theme")
#define PRO_ICON_SELECTED_DT				QString("Protection Modes And Status/Pro_Icon_Selected_Dark_Theme")

/* Define for title bar icon*/
#define APP_ICON							QString(":/images/icon.png")
#define HELP_ICON							QString(":/images/help_icon.svg")
#define CLOSE_ICON							QString(":/images/icon_window_close.png")
#define RESTORE_ICON						QString(":/images/icon_window_restore.png")
#define MINIMIZE_ICON						QString(":/images/icon_window_minimize.png")
#define MAXIMIZE_ICON						QString(":/images/icon_window_maximize.png")
#define TITLE_TEXT_ICON						QString(":/images/SecureAPlus.png")

/* Define for home icon */
#define HOME_PROTECTED_PATH					QString(":/images/home/home_protected_icon.svg")
#define HOME_WARNING_PATH					QString(":/images/home/home_warning_icon.svg")
#define HOME_CONTENT_PROTECTED_PATH			QString(":/images/home/home_main_content_protected_icon.svg")
#define HOME_CONTENT_WARNING_PATH			QString(":/images/home/home_main_content_warning_icon.svg")


/* Define for scan icon */
#define SCAN_ICON_PATH						QString(":/images/scan/scan_icon.svg")

/* Define for manage icon */
#define MANAGE_ICON_PATH					QString(":/images/manage/manage_icon.svg")

/* Define for setting icon */
#define SETTING_ICON_PATH					QString(":/images/setting/setting_icon.svg")

/* Define for top bar icon */
#define TOPBAR_ICON_PATH					QString(":/images/topbar/navigation_button.svg")

/* Define for Grid widget icon */			
#define GRID_WIDGET_ICON_PATH				QString(":/images/grid widget/grid_ring_icon.svg")

/* Define for Appearance */
#define APPEAR_DARK_THEME_LIGHT_MODE		QString(":/images/language personal/appear_dark_theme_light_mode.png")
#define APPEAR_LIGHT_THEME_LIGHT_MODE		QString(":/images/language personal/appear_light_theme_light_mode.png")
#define APPEAR_DARK_THEME_DARK_MODE			QString(":/images/language personal/appear_dark_theme_dark_mode.png")
#define APPEAR_LIGHT_THEME_DARK_MODE		QString(":/images/language personal/appear_light_theme_dark_mode.png")

/* Define for Protection Modes icon */
#define AUTOMATIC							QString(":/images/protection modes/automatic.svg")
#define INTERACTIVE							QString(":/images/protection modes/interactive.svg")
#define LOCKDOWN							QString(":/images/protection modes/lockdown.svg")
#define TRUSTALL							QString(":/images/protection modes/trustall.svg")
#define OBSERVATION							QString(":/images/protection modes/observation.svg")
#define PRO									QString(":/images/protection modes/pro_version.svg")

/* Define for Rings icon */
#define RING_SELECTED_LT					QString(":/images/Rings/light_theme_selected.svg")
#define RING_SELECTED_DT					QString(":/images/Rings/dark_theme_selected.svg")
#define RING_UNSELECTED_LT					QString(":/images/Rings/light_theme_unselected.svg")
#define RING_UNSELECTED_DT					QString(":/images/Rings/dark_theme_unselected.svg")

/* Define for Feature Details icon */
#define DOT_STATUS							QString(":/images/feature details/dot_status.svg")
#define FEATURE_SETTING						QString(":/images/feature details/setting_icon.svg")

/* Define for Scan Settings icon*/
#define DOWN_ARROW_LT						QString(":/images/Scan Settings/down-arrow-lt.svg")
#define DOWN_ARROW_DT						QString(":/images/Scan Settings/down-arrow-dt.svg")
#define SLIDER_THUMB_ICON_DT				QString(":/images/Scan Settings/slider-thumb-dt.svg")

/*Define for setting grid widget icon */
#define SCAN_SETTINGS						QString(":/images/setting/scan_settings.svg")
#define PROTECTION_MODE						QString(":/images/setting/protection_modes.svg")
#define LANGUAGE_PERSIONAL					QString(":/images/setting/language_persional.svg")
#define DIAGNOSIS							QString(":/images/setting/diagnosis.svg")
#define MANAGEMENT_SERVER					QString(":/images/setting/management_server.svg")
#define SECURITY							QString(":/images/setting/security.svg")
#define UPDATE								QString(":/images/setting/update.svg")

/*Define for manage grid widget icon */
#define STRUCTED_GROUPS						QString(":/images/manage/trusted_groups.svg")
#define STRUCTED_USERS						QString(":/images/manage/trusted_users.svg")
#define EXC_INC								QString(":/images/manage/exc_inc.svg")
#define APP_CONTROL							QString(":/images/manage/app_control.svg")
#define REMOVABLE_DEVICES					QString(":/images/manage/removeable_devices.svg")
#define ACCOUNT_LICENSE						QString(":/images/manage/account_license.svg")

/* Define for radio button */
#define RADIO_BTN_SELECTED_LT				QString(":/images/radio button/radio_btn_selected_lt.svg")
#define RADIO_BTN_SELECTED_DT				QString(":/images/radio button/radio_btn_selected_dt.svg")
#define RADIO_BTN_UNSELECTED_LT				QString(":/images/radio button/radio_btn_unselected_lt.svg")
#define RADIO_BTN_UNSELECTED_DT				QString(":/images/radio button/radio_btn_unselected_dt.svg")

/* Define for checkbox icon */
#define CHECKBOX_ICON_PATH					QString(":/images/checkbox/checkbox.svg")
#define CHECKBOX_CHECKED_LT					QString(":/images/checkbox/checkbox_checked_lt.svg")
#define CHECKBOX_CHECKED_DT					QString(":/images/checkbox/checkbox_checked_dt.svg")
#define CHECKBOX_SELECT_ALL_LT				QString(":/images/checkbox/select_all_lt.svg")
#define CHECKBOX_SELECT_ALL_DT				QString(":/images/checkbox/select_all_dt.svg")

/* Define for choose file label icon */
#define CHOOSE_FILE_ICON					QString(":/images/choose file/choose_file_icon.svg")

/* Define for help link */
#define HELP_LINK							QString("https://support.secureaplus.com/")

/* Define font */
#define FONT								QFont("Lato", 10, QFont::Normal) //1 character 5px <= 7px <= 10px
#define HOME_CONTENT_STATUS_FONT			QFont("Lato", 16, QFont::Medium)
#define GRID_SUB_TITLE_FONT					QFont("Lato", 8, QFont::Normal)
#define SMALL_FONT							QFont("Lato", 8, QFont::Normal)
#define SMALL_FONT_BOLD						QFont("Lato", 8, QFont::Bold)
#define LARGE_FONT							QFont("Lato", 12, QFont::Normal)
#define BIG_FONT							QFont("Lato", 16, QFont::Medium)

/* Define for navigation button color */
#define GRADIENT_START_DARK					Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_START_DARK)
#define GRADIENT_START_LIGHT				Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_START_LIGHT)
#define GRADIENT_END						Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_END)
#define BTN_BACKGROUND_DARK					Config::getInstance()->getConfigValue(NAVIGATION_BTN_BACKGROUND_DARK)
#define BTN_BACKGROUND_LIGHT				Config::getInstance()->getConfigValue(NAVIGATION_BTN_BACKGROUND_LIGHT)

/* Define for home button color */
#define HOME_PROTECTED_COLOR				Config::getInstance()->getConfigValue(HOME_PROTECTED)
#define HOME_WARNING_COLOR					Config::getInstance()->getConfigValue(HOME_WARNING)

/*Define for managed by server title text*/
#define MANAGED_BY_SERVER_LTDT				Config::getInstance()->getConfigValue("Color/Managed_By_Server_Text_DT_LT")

/* Define text and icon of Scan, manage setting color */
#define TEXT_ICON_COLOR_LIGHT_THEME			Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_LIGHT_THEME_PATH)
#define TEXT_ICON_COLOR_DARK_THEME			Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_DARK_THEME_PATH)
#define TEXT_ICON_COLOR_ACTIVE				Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_ACTIVE_PATH)

/* Define for application background color */
#define BACKGROUND_LIGHT_MODE				Config::getInstance()->getConfigValue(LIGHT_MODE_BACKGROUND)
#define BACKGROUND_DARK_MODE				Config::getInstance()->getConfigValue(DARK_MODE_BACKGROUND)

/* Define Home Main Content Color */
#define HOME_PROTECTED_TEXT_COLOR			Config::getInstance()->getConfigValue(HOME_PROTECTED_TEXT)
#define HOME_AT_RICK_TEXT_COLOR				Config::getInstance()->getConfigValue(HOME_AT_RICK_TEXT)
#define LAST_SCAN_COLOR_TEXT_DARK_THEME		Config::getInstance()->getConfigValue(LAST_SCAN_TEXT_DARK_THEME)
#define LAST_SCAN_COLOR_TEXT_LIGHT_THEME	Config::getInstance()->getConfigValue(LAST_SCAN_TEXT_LIGHT_THEME)
#define SECURE_FEATURE_COLOR_DARK_THEME		Config::getInstance()->getConfigValue(SECURE_FEATURE_DARK_THEME)
#define SECURE_FEATURE_COLOR_LIGHT_THEME	Config::getInstance()->getConfigValue(SECURE_FEATURE_LIGHT_THEME)
#define DETAILS_TEXT_COLOR_DARK_THEME		Config::getInstance()->getConfigValue(DETAILS_TEXT_DARK_THEME)
#define DETAILS_TEXT_COLOR_LIGHT_THEME		Config::getInstance()->getConfigValue(DETAILS_TEXT_LIGHT_THEME)
#define SCAN_NOW_BUTTON_COLOR				Config::getInstance()->getConfigValue(SCAN_NOW_BUTTON)
#define POLICY_BORDER_TEXT_LT				Config::getInstance()->getConfigValue("Home Content/Policy_Border_Text_Light_Theme")
#define POLICY_BORDER_TEXT_DT				Config::getInstance()->getConfigValue("Home Content/Policy_Border_Text_Dark_Theme")

/* Define for Grid Widget Color */
#define GRID_BACKGROUND_DARK_THEME_COLOR	Config::getInstance()->getConfigValue(GRID_BACKGROUND_DARK_THEME)
#define GRID_BACKGROUND_LIGHT_THEME_COLOR	Config::getInstance()->getConfigValue(GRID_BACKGROUND_LIGHT_THEME)
#define GRID_BORDER_DARK_THEME_COLOR		Config::getInstance()->getConfigValue(GRID_BORDER_DARK_THEME)
#define GRID_BORDER_LIGHT_THEME_COLOR		Config::getInstance()->getConfigValue(GRID_BORDER_LIGHT_THEME)
#define GRID_ICON_DARK_THEME_COLOR			Config::getInstance()->getConfigValue(GRID_ICON_DARK_THEME)
#define GRID_ICON_LIGHT_THEME_COLOR			Config::getInstance()->getConfigValue(GRID_ICON_LIGHT_THEME)
#define GRID_TITLE_DARK_THEME_COLOR			Config::getInstance()->getConfigValue(GRID_TITLE_DARK_THEME)
#define GRID_TITLE_LIGHT_THEME_COLOR		Config::getInstance()->getConfigValue(GRID_TITLE_LIGHT_THEME)
#define GRID_SUB_TITLE_DARK_THEME_COLOR		Config::getInstance()->getConfigValue(GRID_SUB_TITLE_DARK_THEME)
#define GRID_SUB_TITLE_LIGHT_THEME_COLOR	Config::getInstance()->getConfigValue(GRID_SUB_TITLE_LIGHT_THEME)

/* Define for Top Bar Color */
#define BACK_BUTTON_LIGHT_THEME_COLOR		Config::getInstance()->getConfigValue(BACK_BUTTON_LIGHT_THEME)
#define BACK_BUTTON_DARK_THEME_COLOR		Config::getInstance()->getConfigValue(BACK_BUTTON_DARK_THEME)
#define TOP_BAR_TEXT_COLOR_DARK_THEME		Config::getInstance()->getConfigValue(TOP_BAR_TEXT_DARK_THEME)
#define TOP_BAR_TEXT_COLOR_LIGHT_THEME		Config::getInstance()->getConfigValue(TOP_BAR_TEXT_LIGHT_THEME)
#define TOP_BAR_TEXT_HOVER_COLOR_DT			Config::getInstance()->getConfigValue("Top Bar/Text_Hover_Color_Dark_Theme")
#define TOP_BAR_TEXT_HOVER_COLOR_LT			Config::getInstance()->getConfigValue("Top Bar/Text_Hover_Color_Light_Theme")


/* Define for main content background color */
#define MAIN_BACKGROUND_LIGHT_THEME_COLOR	Config::getInstance()->getConfigValue(MAIN_BACKGROUND_LIGHT_THEME)
#define MAIN_BACKGROUND_DARK_THEME_COLOR	Config::getInstance()->getConfigValue(MAIN_BACKGROUND_DARK_THEME)

/* Define for toggle */
#define THUMB_CHECKED_DARK_THEME_COLOR		Config::getInstance()->getConfigValue(THUMB_CHECKED_DARK_THEME)
#define THUMB_CHECKED_LIGHT_THEME_COLOR		Config::getInstance()->getConfigValue(THUMB_CHECKED_LIGHT_THEME)
#define THUMB_UNCHECKED_DARK_THEME_COLOR	Config::getInstance()->getConfigValue(THUMB_UNCHECKED_DARK_THEME)
#define THUMB_UNCHECKED_LIGHT_THEME_COLOR	Config::getInstance()->getConfigValue(THUMB_UNCHECKED_LIGHT_THEME)
#define TRACK_CHECKED_DARK_THEME_COLOR		Config::getInstance()->getConfigValue(TRACK_CHECKED_DARK_THEME)
#define TRACK_CHECKED_LIGHT_THEME_COLOR		Config::getInstance()->getConfigValue(TRACK_CHECKED_LIGHT_THEME)
#define TRACK_UNCHECKED_DARK_THEME_COLOR	Config::getInstance()->getConfigValue(TRACK_UNCHECKED_DARK_THEME)
#define TRACK_UNCHECKED_LIGHT_THEME_COLOR	Config::getInstance()->getConfigValue(TRACK_UNCHECKED_LIGHT_THEME)
#define TEXT_DARK_THEME_COLOR				Config::getInstance()->getConfigValue(TEXT_DARK_THEME)
#define TEXT_LIGHT_THEME_COLOR				Config::getInstance()->getConfigValue(TEXT_LIGHT_THEME)

/* Define for toggle in content view */
#define TOGGLE_ACTIVE_THUMB_LT				Config::getInstance()->getConfigValue("Toggle/Toggle_Active_Thumb_Light_Theme")
#define TOGGLE_ACTIVE_THUMB_DT				Config::getInstance()->getConfigValue("Toggle/Toggle_Active_Thumb_Dark_Theme")
#define TOGGLE_ACTIVE_TRACK_LT				Config::getInstance()->getConfigValue("Toggle/Toggle_Active_Track_Light_Theme")
#define TOGGLE_ACTIVE_TRACK_DT				Config::getInstance()->getConfigValue("Toggle/Toggle_Active_Track_Dark_Theme")

#define TOGGLE_INACTIVE_THUMB_LT			Config::getInstance()->getConfigValue("Toggle/Toggle_Inactive_Thumb_Light_Theme")
#define TOGGLE_INACTIVE_THUMB_DT			Config::getInstance()->getConfigValue("Toggle/Toggle_Inactive_Thumb_Dark_Theme")
#define TOGGLE_INACTIVE_TRACK_LT			Config::getInstance()->getConfigValue("Toggle/Toggle_Inactive_Track_Light_Theme")
#define TOGGLE_INACTIVE_TRACK_DT			Config::getInstance()->getConfigValue("Toggle/Toggle_Inactive_Track_Dark_Theme")

/* Define for language and personalization */
#define	LANG_PERS_TEXT_COLOR_DARK_THEME		Config::getInstance()->getConfigValue(LANG_PERS_TEXT_DARK_THEME)
#define	LANG_PERS_TEXT_COLOR_LIGHT_THEME	Config::getInstance()->getConfigValue(LANG_PERS_TEXT_LIGHT_THEME)

/* Protection Modes And Status icon */
#define LABEL_ICON_SELECTED_BACKGROUND_COLOR_LT		Config::getInstance()->getConfigValue(LABEL_ICON_SELECTED_BACKGROUND_LT)
#define LABEL_ICON_SELECTED_BACKGROUND_COLOR_DT		Config::getInstance()->getConfigValue(LABEL_ICON_SELECTED_BACKGROUND_DT)
#define ICON_SELECTED_COLOR_LT						Config::getInstance()->getConfigValue(ICON_SELECTED_LT)
#define ICON_SELECTED_COLOR_DT						Config::getInstance()->getConfigValue(ICON_SELECTED_DT )
#define LABEL_ICON_UNSELECTED_BACKGROUND_COLOR_LT	Config::getInstance()->getConfigValue(LABEL_ICON_UNSELECTED_BACKGROUND_LT)
#define LABEL_ICON_UNSELECTED_BACKGROUND_COLOR_DT	Config::getInstance()->getConfigValue(LABEL_ICON_UNSELECTED_BACKGROUND_DT)
#define ICON_UNSELECTED_COLOR_LT					Config::getInstance()->getConfigValue(ICON_UNSELECTED_LT)
#define ICON_UNSELECTED_COLOR_DT					Config::getInstance()->getConfigValue(ICON_UNSELECTED_DT)
#define WDG_SELECTED_BGROUND_COLOR_LT				Config::getInstance()->getConfigValue(WDG_SELECTED_BGROUND_LT)
#define WDG_SELECTED_BGROUND_COLOR_DT				Config::getInstance()->getConfigValue(WDG_SELECTED_BGROUND_DT)
#define WDG_UNSELECTED_BGROUND_COLOR_LT				Config::getInstance()->getConfigValue(WDG_UNSELECTED_BGROUND_LT)
#define WDG_UNSELECTED_BGROUND_COLOR_DT				Config::getInstance()->getConfigValue(WDG_UNSELECTED_BGROUND_DT)
#define TITLTE_SELECTED_COLOR_LT					Config::getInstance()->getConfigValue(TITLTE_SELECTED_LT)
#define TITLTE_SELECTED_COLOR_DT					Config::getInstance()->getConfigValue(TITLTE_SELECTED_DT)
#define TITLTE_UNSELECTED_COLOR_LT					Config::getInstance()->getConfigValue(TITLTE_UNSELECTED_LT)
#define TITLTE_UNSELECTED_COLOR_DT					Config::getInstance()->getConfigValue(TITLTE_UNSELECTED_DT)
#define TITLE_TEXT_COLOR_DT							Config::getInstance()->getConfigValue(TITLE_TEXT_DT)
#define TITLE_TEXT_COLOR_LT							Config::getInstance()->getConfigValue(TITLE_TEXT_LT)		
#define MODE_TITLE_TEXT_COLOR_LT					Config::getInstance()->getConfigValue(MODE_TITLE_TEXT_LT)	
#define MODE_TITLE_TEXT_COLOR_DT					Config::getInstance()->getConfigValue(MODE_TITLE_TEXT_DT)	
#define DESCRIPTION_TEXT_COLOR_LT					Config::getInstance()->getConfigValue(DESCRIPTION_TEXT_LT)
#define DESCRIPTION_TEXT_COLOR_DT					Config::getInstance()->getConfigValue(DESCRIPTION_TEXT_DT)
#define PRO_ICON_UNSELECTED_COLOR_LT				Config::getInstance()->getConfigValue(PRO_ICON_UNSELECTED_LT)
#define PRO_ICON_UNSELECTED_COLOR_DT				Config::getInstance()->getConfigValue(PRO_ICON_UNSELECTED_DT)
#define PRO_ICON_SELECTED_COLOR_LT					Config::getInstance()->getConfigValue(PRO_ICON_SELECTED_LT)
#define PRO_ICON_SELECTED_COLOR_DT					Config::getInstance()->getConfigValue(PRO_ICON_SELECTED_DT)
#define LOCKDOWN_ICON_DT_LT							Config::getInstance()->getConfigValue("Protection Modes And Status/Lockdown_Icon_DT_LT")
#define EDIT_LABEL_COLOR_BACKGROUND_LT				Config::getInstance()->getConfigValue("Protection Modes And Status/Edit_Text_Background_Light_Theme")
#define EDIT_LABEL_COLOR_BACKGROUND_DT				Config::getInstance()->getConfigValue("Protection Modes And Status/Edit_Text_Background_Dark_Theme")

/*Define for Trust All status */
#define TRUST_ALL_TEXT_DT							Config::getInstance()->getConfigValue("Protection Modes And Status/Trust_All_Text_Dark_Theme")
#define TRUST_ALL_TEXT_LT							Config::getInstance()->getConfigValue("Protection Modes And Status/Trust_All_Text_Light_Theme")
#define TRUST_ALL_NEXT_REBOOT_DT					Config::getInstance()->getConfigValue("Protection Modes And Status/Trust_All_Next_Reboot_Dark_Theme")
#define TRUST_ALL_NEXT_REBOOT_LT					Config::getInstance()->getConfigValue("Protection Modes And Status/Trust_All_Next_Reboot_Light_Theme")


/* Define for dialog */
#define DIALOG_BACKGROUND_DT						Config::getInstance()->getConfigValue("Dialog/Background_Dark_Theme")
#define DIALOG_BACKGROUND_LT						Config::getInstance()->getConfigValue("Dialog/Background_Light_Theme")
#define DIALOG_TITLE_TEXT_DT						Config::getInstance()->getConfigValue("Dialog/Text_Dark_Mode")
#define DIALOG_TITLE_TEXT_LT						Config::getInstance()->getConfigValue("Dialog/Text_Light_Mode")
#define DIALOG_BUTTON_BGROUND_DT					Config::getInstance()->getConfigValue("Dialog/Button_Bground_Dark_Theme")
#define DIALOG_BUTTON_BGROUND_LT					Config::getInstance()->getConfigValue("Dialog/Button_Bground_Light_Theme")
#define DIALOG_CANCEL_TEXT_BORDER_DT				Config::getInstance()->getConfigValue("Dialog/Cancel_Text_Border_Dark_Theme")
#define DIALOG_CANCEL_TEXT_BORDER_LT				Config::getInstance()->getConfigValue("Dialog/Cancel_Text_Border_Light_Theme")
#define	DIALOG_BUTTON_TEXT_DT						Config::getInstance()->getConfigValue("Dialog/Button_Text_Dark_Theme")
#define	DIALOG_BUTTON_TEXT_LT						Config::getInstance()->getConfigValue("Dialog/Button_Text_Light_Theme")
#define DIALOG_TEXBOX_DT							Config::getInstance()->getConfigValue("Dialog/TextBox_Dark_Theme")
#define DIALOG_TEXBOX_LT							Config::getInstance()->getConfigValue("Dialog/TextBox_Light_Theme")
#define DIALOG_BUTTON_TEXT_DISABLE_LT				Config::getInstance()->getConfigValue("Dialog/Button_Text_Disable_Light_Theme")
#define DIALOG_BUTTON_TEXT_DISABLE_DT				Config::getInstance()->getConfigValue("Dialog/Button_Text_Disable_Dark_Theme")
#define DIALOG_BUTTON_BACKGROUND_DISABLE_LT			Config::getInstance()->getConfigValue("Dialog/Button_Background_Disable_Light_Theme")
#define DIALOG_BUTTON_BACKGROUND_DISABLE_DT			Config::getInstance()->getConfigValue("Dialog/Button_Background_Disable_Dark_Theme")


/* Define for widget Transparent */
#define TRANSPARENT_BACKGROUND_DT					Config::getInstance()->getConfigValue("Transparent/Transparent_Background_Dark_Theme")
#define TRANSPARENT_BACKGROUND_LT					Config::getInstance()->getConfigValue("Transparent/Transparent_Background_Light_Theme")

/* Define for Observation dialog */
#define OBSERVATION_BACKGROUND_DT					Config::getInstance()->getConfigValue("Observation/Obs_Background_Dark_Theme")
#define OBSERVATION_BACKGROUND_LT					Config::getInstance()->getConfigValue("Observation/Obs_Background_Light_Theme")
#define OBSERVATION_TEXT_DT_LT						Config::getInstance()->getConfigValue("Observation/Obs_Text_DT_LT")
#define OBSERVATION_BUTTON_BACKGROUND_DT_LT			Config::getInstance()->getConfigValue("Observation/Obs_Button_Background_DT_LT")

/* Define for Circle process */
#define CIRCLE_COLOR_DT								Config::getInstance()->getConfigValue("Circle Process/Circle_Color_Dark_Theme")
#define CIRCLE_COLOR_LT								Config::getInstance()->getConfigValue("Circle Process/Circle_Color_Light_Theme")
#define CIRCLE_BACKGROUND_COLOR_DT					Config::getInstance()->getConfigValue("Circle Process/Circle_Background_Color_Dark_Theme")
#define CIRCLE_BACKGROUND_COLOR_LT					Config::getInstance()->getConfigValue("Circle Process/Circle_Background_Color_Light_Theme")
#define CIRCLE_TEXT_COLOR_DT						Config::getInstance()->getConfigValue("Circle Process/Circle_Text_Color_Dark_Theme")
#define CIRCLE_TEXT_COLOR_LT						Config::getInstance()->getConfigValue("Circle Process/Circle_Text_Color_Light_Theme")

/* Define for Feature States Color */
#define FEATURE_ACTIVE								Config::getInstance()->getConfigValue("Feature States/Active")
#define FEATURE_OFF_INTENTIONAL						Config::getInstance()->getConfigValue("Feature States/Off_Intentional")
#define FEATURE_OFF_NOT_INTENTIONAL					Config::getInstance()->getConfigValue("Feature States/Off_NotIntentional")
#define FEATURE_EXPIRE_SOON							Config::getInstance()->getConfigValue("Feature States/Expire_Soon")
#define FEATURE_EXPIRED								Config::getInstance()->getConfigValue("Feature States/Expired")
#define FEATURE_INVALID								Config::getInstance()->getConfigValue("Feature States/Invalid")
#define FEATURE_RUNNING								Config::getInstance()->getConfigValue("Feature States/Running")
#define FEATURE_NOT_RUNNING							Config::getInstance()->getConfigValue("Feature States/Not_Running")
#define FEATURE_NOT_INSTALLED						Config::getInstance()->getConfigValue("Feature States/Not_Installed")
#define FEATURE_START_PENDING						Config::getInstance()->getConfigValue("Feature States/Start_Pending")
#define FEATURE_STOP_PENDING						Config::getInstance()->getConfigValue("Feature States/Stop_Pending")
#define FEATURE_CONTINUE_PENDING					Config::getInstance()->getConfigValue("Feature States/Continue_Pending")
#define FEATURE_PAUSE_PENDING						Config::getInstance()->getConfigValue("Feature States/Pause_Pending")
#define FEATURE_PAUSED								Config::getInstance()->getConfigValue("Feature States/Paused")

/* Define for Feature details widget Color */
#define FEATURE_BACKGROUND_LT						Config::getInstance()->getConfigValue("Feature Details/Feature_Background_Light_Theme")
#define FEATURE_BACKGROUND_DT						Config::getInstance()->getConfigValue("Feature Details/Feature_Background_Dark_Theme")
#define FEATURE_NAME_LT								Config::getInstance()->getConfigValue("Feature Details/Feature_Name_Light_Theme")
#define FEATURE_NAME_DT								Config::getInstance()->getConfigValue("Feature Details/Feature_Name_Dark_Theme")
#define FEATURE_SETTING_LT							Config::getInstance()->getConfigValue("Feature Details/Feature_Setting_Light_Theme")
#define FEATURE_SETTING_DT							Config::getInstance()->getConfigValue("Feature Details/Feature_Setting_DarkTheme_Theme")

/* Define for Scan Settings */
#define SCAN_SETTINGS_TITLE_TEXT_LT					Config::getInstance()->getConfigValue("Scan Settings/Title_Text_Light_Theme")
#define SCAN_SETTINGS_TITLE_TEXT_DT					Config::getInstance()->getConfigValue("Scan Settings/Title_Text_Dark_Theme")
#define SCAN_SETTINGS_DESCRIPTION_TEXT_LT			Config::getInstance()->getConfigValue("Scan Settings/Description_Text_Light_Theme")
#define SCAN_SETTINGS_DESCRIPTION_TEXT_DT			Config::getInstance()->getConfigValue("Scan Settings/Description_Text_Dark_Theme")

/* Define for Tab widget */
#define TAB_TITLE_TEXT_ACTIVE_LT					Config::getInstance()->getConfigValue("Tab/Tab_Title_Text_Active_Light_Theme")
#define TAB_TITLE_TEXT_ACTIVE_DT					Config::getInstance()->getConfigValue("Tab/Tab_Title_Text_Active_Dark_Theme")
#define TAB_TITLE_TEXT_INACTIVE_LT					Config::getInstance()->getConfigValue("Tab/Tab_Title_Text_Inactive_Light_Theme")
#define TAB_TITLE_TEXT_INACTIVE_DT					Config::getInstance()->getConfigValue("Tab/Tab_Title_Text_Inactive_Dark_Theme")
#define TAB_TITLE_BACKGROUND_ACTIVE_LT				Config::getInstance()->getConfigValue("Tab/Tab_Title_Active_Background_Light_Theme")
#define TAB_TITLE_BACKGROUND_ACTIVE_DT				Config::getInstance()->getConfigValue("Tab/Tab_Title_Active_Background_Dark_Theme")
//#define TAB_CONTENT_BACKGROUND_LT					Config::getInstance()->getConfigValue("Tab/Tab_Content_Background_Light_Theme")
//#define TAB_CONTENT_BACKGROUND_DT					Config::getInstance()->getConfigValue("Tab/Tab_Content_Background_Dark_Theme")

/* Define for Line between widgets */
#define LINE_COLOR_LT								Config::getInstance()->getConfigValue("Line/Line_Color_Light_Theme")
#define LINE_COLOR_DT								Config::getInstance()->getConfigValue("Line/Line_Color_Dark_Theme")

/* Define for ComboBox */
#define COMBOBOX_TEXT_ICON_LT						Config::getInstance()->getConfigValue("ComboBox/Combobox_Text_Icon_Light_Theme")
#define COMBOBOX_TEXT_ICON_DT						Config::getInstance()->getConfigValue("ComboBox/Combobox_Text_Icon_Dark_Theme")
#define	COMBOBOX_BACKGROUND_LT						Config::getInstance()->getConfigValue("ComboBox/Combobox_Background_Light_Theme")
#define	COMBOBOX_BACKGROUND_DT						Config::getInstance()->getConfigValue("ComboBox/Combobox_Background_Dark_Theme")
#define COMBOBOX_SELECTION_BACKGROUND_LT			Config::getInstance()->getConfigValue("ComboBox/Combobox_Selection_Background_Light_theme")
#define COMBOBOX_SELECTION_BACKGROUND_DT			Config::getInstance()->getConfigValue("ComboBox/Combobox_Selection_Background_Dark_theme")

/* Define for Slider */
#define SLIDER_ACTIVE_TRACK_LT						Config::getInstance()->getConfigValue("Slider/Slider_Active_Track_Light_Theme")
#define SLIDER_ACTIVE_TRACK_DT						Config::getInstance()->getConfigValue("Slider/Slider_Active_Track_Dark_Theme")
#define SLIDER_INACTIVE_TRACK_LT					Config::getInstance()->getConfigValue("Slider/Slider_Inactive_Track_Light_Theme")
#define SLIDER_INACTIVE_TRACK_DT					Config::getInstance()->getConfigValue("Slider/Slider_Inactive_Track_Dark_Theme")
#define SLIDER_THUMB_LT								Config::getInstance()->getConfigValue("Slider/Slider_Thumb_Light_Theme")
#define SLIDER_THUMB_DT								Config::getInstance()->getConfigValue("Slider/Slider_Thumb_Dark_Theme")

/* Define for Vertical Scrollbar */
#define VER_SCROLLBAR_THUMB_LT						Config::getInstance()->getConfigValue("Vertical Scrollbar/Ver_Scroll_Thumb_Light_Theme")
#define VER_SCROLLBAR_THUMB_DT						Config::getInstance()->getConfigValue("Vertical Scrollbar/Ver_Scroll_Thumb_Dark_Theme")
#define VER_SCROLLBAR_TRACK_LT						Config::getInstance()->getConfigValue("Vertical Scrollbar/Ver_Scroll_Track_Light_Theme")
#define VER_SCROLLBAR_TRACK_DT						Config::getInstance()->getConfigValue("Vertical Scrollbar/Ver_Scroll_Track_Dark_Theme")

/* Define for Application Control */
#define APP_CONTROL_TITLE_TEXT_LT					Config::getInstance()->getConfigValue("Application Control/Title_Text_Light_Theme")
#define APP_CONTROL_TITLE_TEXT_DT					Config::getInstance()->getConfigValue("Application Control/Title_Text_Dark_Theme")
#define APP_CONTROL_DESC_TEXT_LT					Config::getInstance()->getConfigValue("Application Control/Description_Text_Light_Theme")
#define APP_CONTROL_DESC_TEXT_DT					Config::getInstance()->getConfigValue("Application Control/Description_Text_Dark_Theme")

/* Define for Application Control > Allow list */
#define ALLOW_LIST_STATUS_BUILDING					Config::getInstance()->getConfigValue("Application Control/Allist_status_Building")
#define ALLOW_LIST_STATUS_RUNNING					Config::getInstance()->getConfigValue("Application Control/Allist_status_Running")
#define ALLOW_LIST_STATUS_COMPLETED					Config::getInstance()->getConfigValue("Application Control/Allist_status_Completed")
#define ALLOW_LIST_BACKGROUND_LT					Config::getInstance()->getConfigValue("Application Control/Allist_Background_Light_Theme")
#define ALLOW_LIST_BACKGROUND_DT					Config::getInstance()->getConfigValue("Application Control/Allist_Background_Dark_Theme")

/* Define for Tab content widget */
#define TAB_CONTENT_TITLE_TEXT_LT					Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Title_Text_Light_Theme")
#define TAB_CONTENT_TITLE_TEXT_DT					Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Title_Text_Dark_Theme")
#define TAB_CONTENT_DESC_TEXT_LT					Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Desc_Text_Light_Theme")
#define TAB_CONTENT_DESC_TEXT_DT					Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Desc_Text_Dark_Theme")
#define TAB_CONTENT_BACKGROUND_LT					Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Background_Light_Theme")
#define TAB_CONTENT_BACKGROUND_DT					Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Background_Dark_Theme")
#define TAB_CONTENT_BTN_TEXT_DISABLED_LT			Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Button_Text_Disabled_Light_Theme")
#define TAB_CONTENT_BTN_TEXT_DISABLED_DT			Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Button_Text_Disabled_Dark_Theme")
#define TAB_CONTENT_BTN_BACKGROUND_DISABLED_LT		Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Button_Background_Disabled_Light_Theme")
#define TAB_CONTENT_BTN_BACKGROUND_DISABLED_DT		Config::getInstance()->getConfigValue("Tab Content/Tab_Content_Button_Background_Disabled_Dark_Theme")

/* Define for Searh widget */
#define SEARCH_BACKGROUND_LT						Config::getInstance()->getConfigValue("Search/Search_Background_Light_Theme")
#define SEARCH_BACKGROUND_DT						Config::getInstance()->getConfigValue("Search/Search_Background_Dark_Theme")
enum ColorType
{
	Default = 0,
	Dark_Type,
	Light_Type,
	Gradient_Type,
};

enum Theme_Type
{
	Light_Theme = 0,
	Dark_Theme,
};

enum Status
{
	Protected_Status = 0,
	Warning_Status,
};

enum Protection_Modes
{
	None = 0,
	Automatic_Mode,
	Interactive_Mode,
	Lockdown_Mode,
	Lockdown_Silent,
	Lockdown_Default,
	TrustAll_Mode,
	TrustAll_5Mins,
	TrustAll_30Mins,
	TrustAll_NetReboot,
	Observation_Mode,
};
enum LockDown
{
	LOCKDOWN_CANCEL = 0,
	LOCKDOWN_SILENT,
	LOCKDOWN_DEFAULT,

};

enum TrustAll
{
	TRUSTALL_CANCEL =0,
	TRUSTALL_APPLY,

};
enum TrustAllTime
{
	TRUSTALL_5MINS = 0,
	TRUSTALL_30MINS,
	TRUSTALL_NEXTREBOOT,
};

enum Observation
{
	Observation_exit = 0,
	Observation_upgrade,
};

enum Feature
{
	Lisence = 0,
	RealTime_Scanning,
	Universal_AV,
	WhiteList_Driver,
	WhiteList_Service,
	SAP_Service,
	Antivirus_Driver,
	Offline_Antivirus_Service,
};

enum Feature_States
{
	Active = 0,
	Off_Intentional,
	Off_NotIntentional,
	Expire_Soon,
	Expired,
	Invalid,
	Running,
	Not_Running,
	Not_Installed,
	Start_Pending,
	Stop_Pending,
	Continue_Pending,
	Pause_Pending,
	Paused,
};

enum License
{
	License_Active = 0,
	License_Expire_Soon,
	License_Expired,
};

enum Directory
{
	Setting = 0,
	Protection_mode,
	Language_Personal,
	Scan_Settings,
	Home,
	Manage,
	AppControl,
};

enum AllowList_Type
{
	Allist_Creation = 0,
	Allist_Service,
	Allist_Driver,
};

enum AllowList_States
{
	Allist_Building = 0,
	Allist_Completed,
	Allist_Running,
};

enum Screen
{
	Screen_None = 0,
	License_Screen,
	Antivirus_Tab,
};

enum Button_Check_State
{
	Button_Checked = 0,
	Button_All_Unchecked,
	Button_All_Checked,
};

struct CertificateRowString
{
	QString	CertificateNameText;
	QString	validFromText;
	QString	validToText;
	QString	thumprintText;
};
