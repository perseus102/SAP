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
#define GRID_RING_DARK_THEME				QString("Grid Widget/Ring_Icon_Dark_Theme")
#define GRID_RING_LIGHT_THEME				QString("Grid Widget/Ring_Icon_Light_Theme")
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
#define LIGHT_THEME_ICON_SELECTED			QString(":/images/language personal/light_theme_selected.svg")
#define LIGHT_THEME_ICON_UNSELECTED			QString(":/images/language personal/light_theme_unselected.svg")
#define DARK_THEME_ICON_SELECTED			QString(":/images/language personal/dark_theme_selected.svg")
#define DARK_THEME_ICON_UNSELECTED			QString(":/images/language personal/dark_theme_unselected.svg")

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

/* Define for help link */
#define HELP_LINK							QString("https://support.secureaplus.com/")

/* Define font */
#define FONT								QFont("Lato", 10, QFont::Normal)
#define HOME_CONTENT_STATUS_FONT			QFont("Lato", 16, QFont::Medium)
#define GRID_SUB_TITLE_FONT					QFont("Lato", 8, QFont::Normal)
#define SMALL_FONT							QFont("Lato", 8, QFont::Normal)
#define LARGE_FONT							QFont("Lato", 12, QFont::Normal)

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
#define GRID_RING_DARK_THEME_COLOR			Config::getInstance()->getConfigValue(GRID_RING_DARK_THEME)
#define GRID_RING_LIGHT_THEME_COLOR			Config::getInstance()->getConfigValue(GRID_RING_LIGHT_THEME)
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
#define SCAN_SETTINGS_TAB_SELECTED_TEXT_LT			Config::getInstance()->getConfigValue("Scan Settings/Tab_Selected_Text_Light_Theme")
#define SCAN_SETTINGS_TAB_SELECTED_TEXT_DT			Config::getInstance()->getConfigValue("Scan Settings/Tab_Selected_Text_Dark_Theme")
#define SCAN_SETTINGS_TAB_UNSELECTED_TEXT_LT		Config::getInstance()->getConfigValue("Scan Settings/Tab_Unselected_Text_Light_Theme")
#define SCAN_SETTINGS_TAB_UNSELECTED_TEXT_DT		Config::getInstance()->getConfigValue("Scan Settings/Tab_Unselected_Text_Dark_Theme")
#define SCAN_SETTINGS_TAB_ACTIVE_BACKGROUND_LT		Config::getInstance()->getConfigValue("Scan Settings/Tab_Active_Background_Light_Theme")
#define SCAN_SETTINGS_TAB_ACTIVE_BACKGROUND_DT		Config::getInstance()->getConfigValue("Scan Settings/Tab_Active_Background_Dark_Theme")
#define SCAN_SETTINGS_SCROLL_AREA_BACKGROUND_LT		Config::getInstance()->getConfigValue("Scan Settings/Scroll_Area_Background_Light_Theme")
#define SCAN_SETTINGS_SCROLL_AREA_BACKGROUND_DT		Config::getInstance()->getConfigValue("Scan Settings/Scroll_Area_Background_Dark_Theme")
#define SCAN_SETTINGS_TITLE_TEXT_LT					Config::getInstance()->getConfigValue("Scan Settings/Title_Text_Light_Theme")
#define SCAN_SETTINGS_TITLE_TEXT_DT					Config::getInstance()->getConfigValue("Scan Settings/Title_Text_Dark_Theme")
#define SCAN_SETTINGS_DESCRIPTION_TEXT_LT			Config::getInstance()->getConfigValue("Scan Settings/Description_Text_Light_Theme")
#define SCAN_SETTINGS_DESCRIPTION_TEXT_DT			Config::getInstance()->getConfigValue("Scan Settings/Description_Text_Dark_Theme")

/* Define for Line between widgets */
#define LINE_COLOR_LT								Config::getInstance()->getConfigValue("Line/Line_Color_Light_Theme")
#define LINE_COLOR_DT								Config::getInstance()->getConfigValue("Line/Line_Color_Dark_Theme")

/* Define for ComboBox */
#define COMBOBOX_TEXT_ICON_LT						Config::getInstance()->getConfigValue("ComboBox/Combobox_Text_Icon_Light_Theme")
#define COMBOBOX_TEXT_ICON_DT						Config::getInstance()->getConfigValue("ComboBox/Combobox_Text_Icon_Dark_Theme")
#define	COMBOBOX_BACKGROUND_LT						Config::getInstance()->getConfigValue("ComboBox/Combobox_Background_Light_Theme")
#define	COMBOBOX_BACKGROUND_DT						Config::getInstance()->getConfigValue("ComboBox/Combobox_Background_Dark_Theme")

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
};
