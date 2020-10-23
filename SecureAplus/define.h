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
#define HOME_PROTECTED_UNSELETED			QString("Color/Home_Protected_Unselected")
#define HOME_WARNING_UNSELETED				QString("Color/Home_Warning_Unselected")

/* Define for text and icon color */
#define TEXT_ICON_COLOR_LIGHT_THEME_PATH	QString("Color/Text_Icon_Color_Light_Theme")
#define TEXT_ICON_COLOR_DARK_THEME_PATH		QString("Color/Text_Icon_Color_Dark_Theme")
#define TEXT_ICON_COLOR_ACTIVE_PATH			QString("Color/Text_Icon_Color_Active")

/* Define for title bar icon*/
#define APP_ICON							QString(":/images/icon.png")
#define HELP_ICON							QString(":/images/help.png")
#define CLOSE_ICON							QString(":/images/icon_window_close.png")
#define RESTORE_ICON						QString(":/images/icon_window_restore.png")
#define MINIMIZE_ICON						QString(":/images/icon_window_minimize.png")
#define MAXIMIZE_ICON						QString(":/images/icon_window_maximize.png")
#define TITLE_TEXT_ICON						QString(":/images/SecureAPlus.png")

/* Define for home icon */
#define HOME_PROTECTED_UNSELECTED_PATH		QString(":/images/home/home_protected_icon.svg")
#define HOME_WARNING_UNSELECTED_PATH		QString(":/images/home/home_warning_icon.svg")
#define HOME_PROTECTED_SELECTED_PATH		QString(":/images/home/home_protected_selected_icon.svg")
#define HOME_WARNING_SELECTED_PATH			QString(":/images/home/home_warning_selected_icon.svg")

/* Define for scan icon */
#define SCAN_ICON_PATH						QString(":/images/scan/scan_icon.svg")

/* Define for manage icon */
#define MANAGE_ICON_PATH					QString(":/images/manage/manage_icon.svg")

/* Define for setting icon */
#define SETTING_ICON_PATH					QString(":/images/setting/setting_icon.svg")

/* Define for help link */
#define HELP_LINK							QString("https://support.secureaplus.com/")

/* Define font */
#define FONT								QFont("Lato", 12, QFont::Normal)

/* Define for navigation button color */
#define GRADIENT_START_DARK					Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_START_DARK)
#define GRADIENT_START_LIGHT				Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_START_LIGHT)
#define GRADIENT_END						Config::getInstance()->getConfigValue(NAVIGATION_BTN_GRADIENT_END)
#define BTN_BACKGROUND_DARK					Config::getInstance()->getConfigValue(NAVIGATION_BTN_BACKGROUND_DARK)
#define BTN_BACKGROUND_LIGHT				Config::getInstance()->getConfigValue(NAVIGATION_BTN_BACKGROUND_LIGHT)

/* Define for home button color */
#define HOME_PROTECTED_UNSELETED_COLOR		Config::getInstance()->getConfigValue(HOME_PROTECTED_UNSELETED)
#define HOME_WARNING_UNSELETED_COLOR		Config::getInstance()->getConfigValue(HOME_WARNING_UNSELETED)

/* Define text and icon of Scan, manage setting color */
#define TEXT_ICON_COLOR_LIGHT_THEME			Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_LIGHT_THEME_PATH)
#define TEXT_ICON_COLOR_DARK_THEME			Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_DARK_THEME_PATH)
#define TEXT_ICON_COLOR_ACTIVE				Config::getInstance()->getConfigValue(TEXT_ICON_COLOR_ACTIVE_PATH)

/* Define for application background color */
#define BACKGROUND_LIGHT_MODE				Config::getInstance()->getConfigValue(LIGHT_MODE_BACKGROUND)
#define BACKGROUND_DARK_MODE				Config::getInstance()->getConfigValue(DARK_MODE_BACKGROUND)

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

