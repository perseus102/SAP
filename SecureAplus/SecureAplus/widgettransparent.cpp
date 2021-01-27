#include "widgettransparent.h"

WidgetTransparent::WidgetTransparent(QWidget *parent)
	: QWidget(parent, Qt::Tool)
{
	ui.setupUi(this);
	QRect geometry = AppSetting::getInstance()->getAppGeometry();
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);
	setWindowOpacity(0.8);
	setStyle();
	activateWindow();
	raise();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &WidgetTransparent::changeTheme);

}

WidgetTransparent::~WidgetTransparent()
{
}

void WidgetTransparent::showWidget()
{
	//Get application geometry
	QRect geometry = AppSetting::getInstance()->getAppGeometry();

	//calulate and set widget geometry
	if (AppSetting::getInstance()->isFullScreen())
	{
		setGeometry(geometry);
	}
	else
	{
		setGeometry(geometry.x() + 15, geometry.y() + 15, geometry.width() - 30, geometry.height() - 30);
	}
	show();
}

void WidgetTransparent::setStyle()
{
	//Set style with theme
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:
		this->setStyleSheet("background-color: " + TRANSPARENT_BACKGROUND_DT + ";");

		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + TRANSPARENT_BACKGROUND_LT + ";");

		break;

		/* MORE THEME */
	default:
		break;
	}
}

void WidgetTransparent::changeTheme()
{
	setStyle();
}
