#include "sapcombobox.h"

SAPCombobox::SAPCombobox(QWidget *parent)
	: QComboBox(parent)
{
	ui.setupUi(this);
	m_backgroundColorDarkTheme = COMBOBOX_BACKGROUND_DT;
	m_backgroundColorLightTheme = COMBOBOX_BACKGROUND_LT;
	setStyle();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SAPCombobox::changeTheme);
}

SAPCombobox::~SAPCombobox()
{
}

void SAPCombobox::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		this->setStyleSheet(
			"QComboBox{"
			"background-color:" + m_backgroundColorLightTheme + ";"
			"color: " + COMBOBOX_TEXT_ICON_LT + ";"
			"padding-left:10px;"
			"border: none;"
			"}"

			"QComboBox::drop-down{"
			"border: none;"
			"}"

			"QComboBox::down-arrow {"
			"image: url(" + DOWN_ARROW_LT + ");"
			"width:12px;"
			"height:12px;"
			"padding-right:30px;"
			"}"

			"QComboBox QAbstractItemView {"
			"background-color:" + m_backgroundColorLightTheme + ";"
			"selection-background-color: " + COMBOBOX_SELECTION_BACKGROUND_LT + ";"
			"color:" + COMBOBOX_TEXT_ICON_LT + ";"
			"outline: 1px solid " + COMBOBOX_SELECTION_BACKGROUND_LT + ";"
			"padding-left:10px;"
			"selection-color: white;"
			"}");

		break;

	case Theme_Type::Dark_Theme:

		this->setStyleSheet(
			"QComboBox{"
			"background-color:" + m_backgroundColorDarkTheme + ";"
			"color: " + COMBOBOX_TEXT_ICON_DT + ";"
			"padding-left:10px;"
			"border: none;"
			"}"

			"QComboBox::drop-down{"
			"border: none;"
			//"padding-left:10px"
			"}"

			"QComboBox::down-arrow {"
			"image: url(" + DOWN_ARROW_DT + ");"
			"width:12px;"
			"height:12px;"
			"padding-right:30px;"
			"}"

			"QComboBox QAbstractItemView {"
			"background-color:" + m_backgroundColorDarkTheme + ";"
			"selection-background-color: " + COMBOBOX_SELECTION_BACKGROUND_DT + ";"
			"color: " + COMBOBOX_TEXT_ICON_DT + ";"
			"outline: 1px solid " + COMBOBOX_SELECTION_BACKGROUND_DT + ";"
			"padding-left:10px;"
			"selection-color: " + COMBOBOX_TEXT_ICON_DT + ";"
			"}");

		
		break;

		//MORE THEME
	default:
		break;
	}
}

void SAPCombobox::setBackroungColor(QString backgroundDT, QString backgroundLT)
{
	m_backgroundColorDarkTheme = backgroundDT;
	m_backgroundColorLightTheme = backgroundLT;
	setStyle();
}

void SAPCombobox::changeTheme()
{
	setStyle();
}