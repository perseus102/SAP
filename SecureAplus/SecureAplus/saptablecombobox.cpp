#include "saptablecombobox.h"

SAPTableCombobox::SAPTableCombobox(int arrowPadding, QWidget *parent)
	: QComboBox(parent),
	m_arrowPadding(arrowPadding)
{
	ui.setupUi(this);
	setStyle();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SAPTableCombobox::changeTheme);
}

SAPTableCombobox::~SAPTableCombobox()
{
}

void SAPTableCombobox::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		this->setStyleSheet(
			"QComboBox{"
			"background-color: none;"
			"color: " + COMBOBOX_TEXT_ICON_LT + ";"
			"padding-left:10px;"
			"}"

			"QComboBox::drop-down{"
			"border: 2px;"
			"padding-left:10px"
			"}"

			"QComboBox::down-arrow {"
			"image: url(" + DOWN_ARROW_LT + ");"
			"width:12px;"
			"height:12px;"
			"padding-right:30px;"
			"}"

			"QComboBox QAbstractItemView {"
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
			"background-color: #48556E;"
			"color: " + TAB_CONTENT_TITLE_TEXT_DT + ";"
			//"padding-left:10px;"
			"}"

			"QComboBox::drop-down{"
			"border: 2px;"
			//"padding-left:10px"
			"width:" + QString::number(m_arrowPadding - 5 /* spacer */) + ";"
			"}"

			"QComboBox::down-arrow {"
			"image: url(" + TALBE_COMBOBOX_ICON_DT + ");"
			"width:6px;"
			"height:4px;"
			"padding-right:" + QString::number(m_arrowPadding - 6/*icon width*/ - 5 /* spacer */) +";"
			"}"

			"QComboBox QAbstractItemView {"
			"selection-background-color: " + COMBOBOX_SELECTION_BACKGROUND_DT + ";"
			"color: " + TAB_CONTENT_TITLE_TEXT_DT + ";"
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
void SAPTableCombobox::changeTheme()
{
	setStyle();
}
