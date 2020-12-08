#include "sapslider.h"

SAPSlider::SAPSlider(QWidget *parent)
	: QSlider(parent)
{
	ui.setupUi(this);
	this->setOrientation(Qt::Horizontal);
	setStyle();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SAPSlider::changeTheme);
}

SAPSlider::~SAPSlider()
{
}

void SAPSlider::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		this->setStyleSheet(

			"QSlider::groove:horizontal{"
			"border: 1px solid none;"
			"height: 1px;"
			"background: none;"
			"margin: 0px 10px;"
			"}"
			"QSlider::handle:horizontal {"
			/*"width: 20px;"
			"background-image: url(" + SLIDER_THUMB_ICON_DT + ");"*/
			"background: " + SLIDER_THUMB_LT + ";"
			//"border: 1px solid #B5E61D;"
			"height: 20px;"
			"width: 20px;"
			"margin: -10px -10px;"
			"border-radius: 10px;"
			"}"

			"QSlider::add-page:qlineargradient {"
			"background: " + SLIDER_INACTIVE_TRACK_LT + ";"
			"border-top-right-radius: 5px;"
			"border-bottom-right-radius: 5px;"
			"border-top-left-radius: 0px;"
			"border-bottom-left-radius: 0px;"
			"}"

			"QSlider::sub-page:qlineargradient {"
			"background: " + SLIDER_ACTIVE_TRACK_LT + ";"
			"border-top-right-radius: 0px;"
			"border-bottom-right-radius: 0px;"
			"border-top-left-radius: 5px;"
			"border-bottom-left-radius: 5px;"
			"}"
		);

		break;

	case Theme_Type::Dark_Theme:

		this->setStyleSheet(

			"QSlider::groove:horizontal{"
			"border: 1px solid none;"
			"height: 1px;"
			"background: none;"
			"margin: 0px 10px;"
			"}"
			"QSlider::handle:horizontal {"
			/*"width: 20px;"
			"background-image: url(" + SLIDER_THUMB_ICON_DT + ");"*/
			"background: " + SLIDER_THUMB_DT + ";"
			//"border: 1px solid #B5E61D;"
			"height: 20px;"
			"width: 20px;"
			"margin: -10px -10px;"
			"border-radius: 10px;"
			"}"

			"QSlider::add-page:qlineargradient {"
			"background: " + SLIDER_INACTIVE_TRACK_DT + ";"
			"border-top-right-radius: 5px;"
			"border-bottom-right-radius: 5px;"
			"border-top-left-radius: 0px;"
			"border-bottom-left-radius: 0px;"
			"}"

			"QSlider::sub-page:qlineargradient {"
			"background: " + SLIDER_ACTIVE_TRACK_DT + ";"
			"border-top-right-radius: 0px;"
			"border-bottom-right-radius: 0px;"
			"border-top-left-radius: 5px;"
			"border-bottom-left-radius: 5px;"
			"}"
		);


		break;

		//MORE THEME
	default:
		break;
	}
}

void SAPSlider::changeTheme()
{
	setStyle();
}