#include "sapscrollarea.h"

SAPSCrollArea::SAPSCrollArea(QWidget *parent)
	: QScrollArea(parent)
{
	ui.setupUi(this);
	setStyle();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SAPSCrollArea::changeTheme);
}

SAPSCrollArea::~SAPSCrollArea()
{
}

void SAPSCrollArea::setStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		this->setStyleSheet("background-color:transparent; border:0px");

		this->verticalScrollBar()->setStyleSheet(
			"QScrollBar:vertical {"
			"border: 0px solid " + VER_SCROLLBAR_TRACK_LT + ";"
			"background: " + VER_SCROLLBAR_TRACK_LT + ";"
			"width:10px;"
			"margin: 0px 5px 30px 0px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::handle:vertical {"
			"min-height: 0px;"
			"background-color: " + VER_SCROLLBAR_THUMB_LT + ";"
			"border: 0px solid none;"
			"width:10px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::add-line:vertical {"
			"height: 0px;"
			"subcontrol-position: bottom;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-line:vertical {"
			"height: 0px;"
			"subcontrol-position: top;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-page:vertical {"
			"background: none;"
			"}"

			"QScrollBar::add-page:vertical {"
			"background: none;"
			"}"
		);

		break;

	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color:transparent; border:0px");
	
		this->verticalScrollBar()->setStyleSheet(
			"QScrollBar:vertical {"
			"border: 0px solid "+ VER_SCROLLBAR_TRACK_DT +";"
			"background: "+ VER_SCROLLBAR_TRACK_DT +";"
			"width:10px;"
			"margin: 0px 5px 30px 0px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::handle:vertical {"
			"min-height: 0px;"
			"background-color: " + VER_SCROLLBAR_THUMB_DT + ";"
			"border: 0px solid none;"
			"width:10px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::add-line:vertical {"
			"height: 0px;"
			"subcontrol-position: bottom;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-line:vertical {"
			"height: 0px;"
			"subcontrol-position: top;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-page:vertical {"
			"background: none;"
			"}"

			"QScrollBar::add-page:vertical {"
			"background: none;"
			"}"
		);
		break;

		//MORE THEME
	default:
		break;
	}
}

void SAPSCrollArea::changeTheme()
{
	setStyle();
}
