#include "sapcheckbox.h"

SAPCheckBox::SAPCheckBox(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SAPCheckBox::changeTheme);
	connect(this, &SAPCheckBox::clicked, this, &SAPCheckBox::boxClicked);
}

SAPCheckBox::~SAPCheckBox()
{
}

void SAPCheckBox::changeTheme()
{
	setButtonStyle(m_state);
}

void SAPCheckBox::setButtonChecked(Qt::CheckState state)
{
	m_state = state;
	setButtonStyle(state);
}

Qt::CheckState SAPCheckBox::getCheckState()
{
	return m_state;
}

void SAPCheckBox::boxClicked()
{
	if (m_state == Qt::Checked)
	{
		setButtonChecked(Qt::Unchecked);
		emit boxSetChecked(Qt::Unchecked);

	}
	else
	{
		setButtonChecked(Qt::Checked);
		emit boxSetChecked(Qt::Checked);
	}
}

void SAPCheckBox::setButtonStyle(Qt::CheckState state)
{
	
	QIcon icon;

	this->setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if (state == Qt::Checked)
		{
			icon.addFile(CHECKBOX_CHECKED_LT);
		}
		else
		{
			icon = util::getInstance()->ChangeSVGColor(CHECKBOX_ICON_PATH, TAB_CONTENT_DESC_TEXT_LT);
		}
		break;

	case Theme_Type::Dark_Theme:
		if (state == Qt::Checked)
		{
			icon.addFile(CHECKBOX_CHECKED_DT);
		}
		else
		{
			icon = util::getInstance()->ChangeSVGColor(CHECKBOX_ICON_PATH, TAB_CONTENT_DESC_TEXT_DT);
		}
		break;

		//MORE THEME
	default:
		break;
	}

	this->setIcon(icon);
	this->setIconSize(QSize(18, 18));
}
