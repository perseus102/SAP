#include "resetbutton.h"

ResetButton::ResetButton(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	setButtonStyle();
	setToolTip("Reset to default");
	transparent = new WidgetTransparent();
	m_resetDialog = new ResetDialog();

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ResetButton::changeTheme);
	connect(this, &QPushButton::clicked, this, &ResetButton::btnClicked);
	connect(m_resetDialog, &ResetDialog::resetToDefault, [this]() { emit signalResetToDefault(); });

}

ResetButton::~ResetButton()
{
}
void ResetButton::enterEvent(QEvent*)
{
	setIconSize(QSize(15,15));
}

void ResetButton::leaveEvent(QEvent*)
{
	setIconSize(QSize(16, 16));
}

void ResetButton::btnClicked()
{
	QRect geometry = AppSetting::getInstance()->getAppGeometry();
	transparent->showWidget();
	m_resetDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 190 /*190 is half width*/, geometry.y() + 16, 380, 174);
	m_resetDialog->showDialog();
	transparent->hide();

}

void ResetButton::setButtonStyle()
{
	QIcon icon;

	this->setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		icon = util::getInstance()->ChangeSVGColor(RESET_BUTTON_ICON, TAB_CONTENT_DESC_TEXT_LT);
		break;

	case Theme_Type::Dark_Theme:
		icon = util::getInstance()->ChangeSVGColor(RESET_BUTTON_ICON, TAB_CONTENT_DESC_TEXT_DT);
		break;

		//MORE THEME
	default:
		break;
	}

	this->setIcon(icon);
	this->setIconSize(QSize(16, 16));
}
void ResetButton::changeTheme()
{
	setButtonStyle();
}