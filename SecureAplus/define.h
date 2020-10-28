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

/* Define Home Main Content */
#define HOME_STATUS_TEXT_DARK_THEME			QString("Home Content/Status_Text_Color_Dark_Theme")
#define HOME_STATUS_TEXT_LIGHT_THEME		QString("Home Content/Status_Text_Color_Light_Theme")
#define SCAN_NOW_BUTTON						QString("Home Content/Scan_Now_Button_Color")
#define FEATURE_DETAILS_TEXT				QString("Home Content/Feature_Details_Text_Color")

/* Define for Grid Widget */
#define GRID_BACKGROUND_DARK_THEME			QString("Grid Widget/Grid_Background_Dark_Theme")
#define GRID_BACKGROUND_LIGHT_THEME			QString("Grid Widget/Grid_Background_Light_Theme")
#define GRID_BORDER_DARK_THEME				QString("Grid Widget/Grid_Border_Dark_Theme")
#define GRID_BORDER_LIGHT_THEME				QString("Grid Widget/Grid_Border_Light_Theme")

/* Define for title bar icon*/
#define APP_ICON							QString(":/images/icon.png")
#define HELP_ICON							QString(":/images/help.png")
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

/* Define for help link */
#define HELP_LINK							QString("https://support.secureaplus.com/")

/* Define font */
#define FONT								QFont("Lato", 10, QFont::Normal)
#define HOME_CONTENT_STATUS_FONT			QFont("Lato", 16, QFont::Medium)

/* Define for navigation button color */
#define GRADIENT_START_DARK					Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_START_DARK)
#define GRADIENT_START_LIGHT				Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_START_LIGHT)
#define GRADIENT_END						Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_END)
#define BTN_BACKGROUND_DARK					Config::getInstance()->getConfigValue(NAVIGATION_BTN_BACKGROUND_DARK)
#define BTN_BACKGROUND_LIGHT				Config::getInstance()->getConfigValue(NAVIGATION_BTN_BACKGROUND_LIGHT)

/* Define for home button color */
#define HOME_PROTECTED_COLOR				Config::getInstance()->getConfigValue(HOME_PROTECTED)
#define HOME_WARNING_COLOR					Config::getInstance()->getConfigValue(HOME_WARNING)

/* Define text and icon of Scan, manage setting color */
#define TEXT_ICON_COLOR_LIGHT_THEME			Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_LIGHT_THEME_PATH)
#define TEXT_ICON_COLOR_DARK_THEME			Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_DARK_THEME_PATH)
#define TEXT_ICON_COLOR_ACTIVE				Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_ACTIVE_PATH)

/* Define for application background color */
#define BACKGROUND_LIGHT_MODE				Config::getInstance()->getConfigValue(LIGHT_MODE_BACKGROUND)
#define BACKGROUND_DARK_MODE				Config::getInstance()->getConfigValue(DARK_MODE_BACKGROUND)

/* Define Home Main Content Color */
#define HOME_STATUS_COLOR_TEXT_DARK_THEME	Config::getInstance()->getConfigValue(HOME_STATUS_TEXT_DARK_THEME)
#define HOME_STATUS_COLOR_TEXT_LIGHT_THEME	Config::getInstance()->getConfigValue(HOME_STATUS_TEXT_LIGHT_THEME)
#define FEATURE_DETAILS_TEXT_COLOR			Config::getInstance()->getConfigValue(FEATURE_DETAILS_TEXT)
#define SCAN_NOW_BUTTON_COLOR				Config::getInstance()->getConfigValue(SCAN_NOW_BUTTON)

/* Define for Grid Widget Color */
#define GRID_BACKGROUND_DARK_THEME_COLOR	Config::getInstance()->getConfigValue(GRID_BACKGROUND_DARK_THEME)
#define GRID_BACKGROUND_LIGHT_THEME_COLOR	Config::getInstance()->getConfigValue(GRID_BACKGROUND_LIGHT_THEME)
#define GRID_BORDER_DARK_THEME_COLOR		Config::getInstance()->getConfigValue(GRID_BORDER_DARK_THEME)
#define GRID_BORDER_LIGHT_THEME_COLOR		Config::getInstance()->getConfigValue(GRID_BORDER_LIGHT_THEME)

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

