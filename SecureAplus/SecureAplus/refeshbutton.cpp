#include "refeshbutton.h"

RefreshButton::RefreshButton(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	setButtonStyle();
	setToolTip("Refresh");
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &RefreshButton::changeTheme);
	connect(this, &QPushButton::clicked, this, &RefreshButton::btnClicked);

}

RefreshButton::~RefreshButton()
{
}

void RefreshButton::enterEvent(QEvent *)
{
	setIconSize(QSize(15, 15));
}

void RefreshButton::leaveEvent(QEvent *)
{
	setIconSize(QSize(16, 16));
}

void RefreshButton::changeTheme()
{
	setButtonStyle();
}
void RefreshButton::btnClicked()
{
	emit signalRefesh();
}

void RefreshButton::setButtonStyle()
{
	QIcon icon;

	this->setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		icon = util::getInstance()->ChangeSVGColor(REFRESH_BUTTON_ICON, TAB_CONTENT_DESC_TEXT_LT);
		break;

	case Theme_Type::Dark_Theme:
		icon = util::getInstance()->ChangeSVGColor(REFRESH_BUTTON_ICON, TAB_CONTENT_DESC_TEXT_DT);
		break;

		//MORE THEME
	default:
		break;
	}

	this->setIcon(icon);
	this->setIconSize(QSize(16, 16));
}
