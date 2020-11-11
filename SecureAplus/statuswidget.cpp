#include "statuswidget.h"

StatusWidget::StatusWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::StatusWidget)
{
	ui->setupUi(this);
	//Create Home Icon
	m_statusLayout = new QVBoxLayout(this);
	m_statusLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_statusLayout);

	m_iconWidget = new QWidget();
	m_iconWidget->setFixedHeight(140);

	QVBoxLayout* boxlayout = new QVBoxLayout();
	boxlayout->setContentsMargins(25, 0, 0, 0);
	m_iconWidget->setLayout(boxlayout);

	m_statusIcon = new QLabel();
	m_statusIcon->setAlignment(Qt::AlignCenter);
	m_statusIcon->setFixedSize(90, 90);

	boxlayout->addWidget(m_statusIcon);
	m_statusLayout->addWidget(m_iconWidget);

	m_toggle = new Switch("Auto Protect");
	m_statusLayout->addWidget(m_toggle);
	m_toggle->setChecked(true);
	setFixedWidth(140);
	setFixedHeight(158);
	
	setStyle();
	setIcon();

	connect(AppSetting::getInstance(), &AppSetting::signal_changeMode, this, &StatusWidget::protectionModeChanged);
	connect(m_toggle, &Switch::released, this, &StatusWidget::toggleClicked);
	connect(this, &StatusWidget::toggleChanged, AppSetting::getInstance(), &AppSetting::toggleClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &StatusWidget::changeTheme);

}

StatusWidget::~StatusWidget()
{
	delete	ui;
	delete	m_statusIcon;
	delete	m_statusLayout;

	ui				= nullptr;
	m_statusIcon	= nullptr;
	m_statusLayout	= nullptr;
}

void StatusWidget::toggleClicked()
{
	bool ischecked = m_toggle->isChecked();
	emit toggleChanged(ischecked);
	setIcon();

}

void StatusWidget::changeTheme()
{
	setStyle();
	setIcon();
}

void StatusWidget::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		
		m_statusIcon->setStyleSheet("background-color:" + LABEL_ICON_SELECTED_BACKGROUND_COLOR_LT + ";"
			"border-radius: 45px;");
		break;

	case Theme_Type::Dark_Theme:
		m_statusIcon->setStyleSheet("background-color:" + LABEL_ICON_SELECTED_BACKGROUND_COLOR_DT + ";"
			"border-radius: 45px;");
		break;

		//MORE THEME
	default:
		break;
	}
}

void StatusWidget::setIcon()
{
	int width = 0;
	int height = 0;
	Protection_Modes mode = AppSetting::getInstance()->getProtectionMode();
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		switch (mode)
		{
		case Automatic_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(AUTOMATIC, ICON_SELECTED_COLOR_LT);
			break;
		case Interactive_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(INTERACTIVE, ICON_SELECTED_COLOR_LT);
			break;
		case Lockdown_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(LOCKDOWN, ICON_SELECTED_COLOR_LT);
			break;
		case TrustAll_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(TRUSTALL, ICON_SELECTED_COLOR_LT);
			break;
		case Observation_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(OBSERVATION, ICON_SELECTED_COLOR_LT);
			break;
		default:
			break;
		}

		break;

	case Theme_Type::Dark_Theme:
		switch (mode)
		{
		case Automatic_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(AUTOMATIC, ICON_SELECTED_COLOR_DT);
			break;
		case Interactive_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(INTERACTIVE, ICON_SELECTED_COLOR_DT);
			break;
		case Lockdown_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(LOCKDOWN, ICON_SELECTED_COLOR_DT);
			break;
		case TrustAll_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(TRUSTALL, ICON_SELECTED_COLOR_DT);
			break;
		case Observation_Mode:
			m_icon = util::getInstance()->ChangeSVGColor(OBSERVATION, ICON_SELECTED_COLOR_DT);
			break;
		default:
			break;
		}

		break;

		//MORE THEME
	default:
		break;
	}

	switch (mode)
	{
	case Automatic_Mode:
		width = 50;
		height = 54;
		break;
	case Interactive_Mode:
		width = 50;
		height = 54;
		break;
	case Lockdown_Mode:
		width = 47;
		height = 54;
		break;
	case TrustAll_Mode:
		width = 47;
		height = 52;
		break;
	case Observation_Mode:
		width = 54;
		height = 34;
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(m_icon.pixmap(width, height));
}

void StatusWidget::protectionModeChanged(Protection_Modes mode)
{
	if (mode != Automatic_Mode && m_toggle->isChecked())
	{
		m_toggle->setChecked(false);
	}
	else if(mode == Automatic_Mode)
	{
		m_toggle->setChecked(true);
	}
	setIcon();
}
