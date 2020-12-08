#include "vulassessment.h"

VulAssessment::VulAssessment(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	QWidget* automaticWg = new QWidget();
	automaticWg->setFixedHeight(80);
	QVBoxLayout* automaticLayout = new QVBoxLayout();
	automaticLayout->setSpacing(0);
	automaticLayout->setContentsMargins(30, 0, 0, 0);
	automaticWg->setLayout(automaticLayout);

	m_automaticCheck = new QLabel();
	m_automaticCheck->setFont(LARGE_FONT);
	m_automaticCheck->setFixedHeight(20);
	m_automaticCheck->setWordWrap(true);

	QLabel* automaticDecsSpacer = new QLabel();
	automaticDecsSpacer->setFixedHeight(5);

	m_automaticCheckDecs = new QLabel();
	m_automaticCheckDecs->setFont(SMALL_FONT);
	m_automaticCheckDecs->setFixedHeight(30);
	m_automaticCheckDecs->setWordWrap(true);

	QLabel* automaticToggleSpacer = new QLabel();
	automaticToggleSpacer->setFixedHeight(10);

	m_automaticToggle = new Switch(QMargins(0, 8, 16, 8), true);
	m_automaticToggle->setFixedSize(50, 30);

	QLabel* autoSpacerBottom = new QLabel();
	QLabel* spacerBottom = new QLabel();

	automaticLayout->addWidget(m_automaticCheck);
	automaticLayout->addWidget(automaticDecsSpacer);
	automaticLayout->addWidget(m_automaticCheckDecs);
	automaticLayout->addWidget(automaticToggleSpacer);
	automaticLayout->addWidget(m_automaticToggle);
	automaticLayout->addWidget(autoSpacerBottom);

	m_layout->addWidget(automaticWg);
	m_layout->addWidget(spacerBottom);

	setLayout(m_layout);
	setLabelText();
	setStyle();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &VulAssessment::changeTheme);
}

VulAssessment::~VulAssessment()
{
}

void VulAssessment::setStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		m_automaticCheck->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_automaticCheckDecs->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_automaticCheck->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_automaticCheckDecs->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");

		break;

		//MORE THEME
	default:
		break;
	}

}

void VulAssessment::setLabelText()
{
	m_automaticCheck->setText("Automatic check for Vulnerability Assessment");
	m_automaticCheckDecs->setText("Runs vulnerability Assessment on installed programs periodically");
}

void VulAssessment::changeTheme()
{
	setStyle();
}
