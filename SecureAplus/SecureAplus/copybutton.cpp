#include "copybutton.h"

CopyButton::CopyButton(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	setButtonStyle();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CopyButton::changeTheme);

}

CopyButton::~CopyButton()
{
}

void CopyButton::enterEvent(QEvent *)
{
	setIconSize(QSize(17, 17));
}

void CopyButton::leaveEvent(QEvent *)
{
	setIconSize(QSize(18, 18));
}

void CopyButton::setButtonStyle()
{
	QIcon icon;

	this->setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		icon = util::getInstance()->ChangeSVGColor(COPY_BUTTON_ICON, TAB_CONTENT_DESC_TEXT_LT);
		break;

	case Theme_Type::Dark_Theme:
		icon = util::getInstance()->ChangeSVGColor(COPY_BUTTON_ICON, TAB_CONTENT_DESC_TEXT_DT);
		break;

		//MORE THEME
	default:
		break;
	}

	this->setIcon(icon);
	this->setIconSize(QSize(18, 18));
}

void CopyButton::changeTheme()
{
	setButtonStyle();
}
