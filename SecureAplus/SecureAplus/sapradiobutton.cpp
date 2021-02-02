#include "sapradiobutton.h"

SAPRadioButton::SAPRadioButton(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SAPRadioButton::changeTheme);
}

SAPRadioButton::~SAPRadioButton()
{
}

void SAPRadioButton::setButtonChecked(Qt::CheckState state)
{
	this->setChecked(state);
	m_state = state;
	setButtonStyle(state);
}


void SAPRadioButton::setButtonStyle(Qt::CheckState state)
{
	QIcon icon;

	this->setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		state == Qt::Checked ? icon.addFile(RADIO_BTN_SELECTED_LT) : icon.addFile(RADIO_BTN_UNSELECTED_LT);
		break;

	case Theme_Type::Dark_Theme:
		state == Qt::Checked ? icon.addFile(RADIO_BTN_SELECTED_DT) : icon.addFile(RADIO_BTN_UNSELECTED_DT);
		break;

		//MORE THEME
	default:
		break;
	}

	this->setIcon(icon);
	this->setIconSize(QSize(20, 20));

}

void SAPRadioButton::changeTheme()
{
	setButtonStyle(m_state);
}
