#include "homemaincontent.h"

HomeMainContent::HomeMainContent(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::HomeMainContent)
{
	ui->setupUi(this);

	/* Init */
	/* Layout of Scan now button */
	QWidget *policyWidget		= new QWidget();
	policyWidget->setFixedHeight(60);
	QHBoxLayout *policyLayout	= new QHBoxLayout();
	policyLayout->setContentsMargins(0, 0, 0, 0);
	policyLayout->setSpacing(0);
	policyWidget->setLayout(policyLayout);

	m_policy	= new QLabel();
	m_policy->setFixedSize(180, 30);
	m_policy->setFont(FONT);
	m_policy->setAlignment(Qt::AlignCenter);
	QLabel* policySpacerLeft = new QLabel();
	policyLayout->addWidget(policySpacerLeft);
	policyLayout->addWidget(m_policy);

	m_statusIcon			= new QLabel();
	m_statusText			= new QLabel();
	m_lastScan				= new QLabel();
	m_securityFeature		= new QLabel();
	m_featureDetails		= new FeatureDetailsLabel();
	m_btn_scanNow			= new QPushButton();

	/* Spacer between last scan and security feature */
	QLabel *spacerCenter	= new QLabel();

	/* Space left and right of Security feature */
	QLabel *spacerRight		= new QLabel();
	QLabel *spacerLeft		= new QLabel();

	/* Spacer bottom */
	QLabel *spacer			= new QLabel();

	/* Layout of Scan now button */
	QWidget *scanNowWidget	= new QWidget();
	scanNowWidget->setFixedHeight(80);
	QVBoxLayout *scanNowbox = new QVBoxLayout();

	scanNowbox->setContentsMargins(0, 0, 0, 0);
	scanNowbox->setSpacing(0);
	scanNowWidget->setLayout(scanNowbox);
	scanNowbox->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	scanNowbox->addWidget(m_btn_scanNow);

	/* Set size */
	m_statusIcon->setMaximumHeight(250);
	m_statusText->setFixedHeight(50);
	m_lastScan->setFixedHeight(30);
	m_securityFeature->setFixedHeight(40);
	m_featureDetails->setFixedHeight(40);
	m_btn_scanNow->setFixedSize(126, 40);

	spacer->setMinimumHeight(160);
	spacerCenter->setFixedHeight(20);

	/* Set font */
	m_statusText->setFont(HOME_CONTENT_STATUS_FONT);
	m_lastScan->setFont(FONT);
	m_securityFeature->setFont(FONT);
	m_featureDetails->setFont(FONT);

	/* Set Align */
	m_statusIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	m_statusText->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	m_lastScan->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	m_securityFeature->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	m_featureDetails->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	/* Init layout */
	m_vBoxlayout = new QGridLayout;
	m_vBoxlayout->setContentsMargins(0, 0, 0, 0);
	m_vBoxlayout->setSpacing(0);

	/* Icon */
	m_vBoxlayout->addWidget(policyWidget,0,0,1,4);

	m_vBoxlayout->addWidget(m_statusIcon,1,0,1,4);

	/* Status Text */
	m_vBoxlayout->addWidget(m_statusText,2,0,1,4);

	/*  Last scan date time */
	m_vBoxlayout->addWidget(m_lastScan,3,0,1,4);


	m_vBoxlayout->addWidget(spacerCenter,4,0,1,4);

	/* Security feature */
	m_vBoxlayout->addWidget(spacerLeft,5,0);
	m_vBoxlayout->addWidget(m_securityFeature,5,1);
	m_vBoxlayout->addWidget(m_featureDetails,5,2);
	m_vBoxlayout->addWidget(spacerRight,5,3);
	
	/* Scan button */
	m_vBoxlayout->addWidget(scanNowWidget,6,0,1,4);

	/* spacer bottom */
	m_vBoxlayout->addWidget(spacer);

	/* Set widget layout */
	setLayout(m_vBoxlayout);

	/* Test */
	setStatusText(QString("All's Good. Your PC is Protected"));
	setLastScanText(QString("Last scan: Septemper 3rd, 2020 at 9:30"));
	setSecurityFearuteText(QString("All security is running."));
	setSecureFearuteDetailsText(QString(" Show details"));
	m_btn_scanNow->setText("Scan Now");

	setIcon();
	setStyle();

	//test
	switch (AppSetting::getInstance()->refreshStatus())
	{
	case Status::Protected_Status:
		setStatusText(QString("All's Good. Your PC is Protected"));
		break;
	case Status::Warning_Status:
		setStatusText(QString("Your device is at risk"));

		/* MORE STATUS */
		break;
	default:
		break;
	}

	m_policy->setText("Policy: v2020FDSF48N..."); //Call API or function
	m_policy->setToolTip("Policy: v2020FDSF48N45345dff45656SSAX");

	connect(m_btn_scanNow, &QPushButton::clicked, this, &HomeMainContent::scanButtonClick);
	connect(m_featureDetails, &FeatureDetailsLabel::clicked, this, &HomeMainContent::featureDetailsClick);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &HomeMainContent::changeTheme);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeStatus, this, &HomeMainContent::changeStatus);
}

HomeMainContent::~HomeMainContent()
{
}

void HomeMainContent::setStatusText(QString text)
{

	m_statusText->setText(text);
}

void HomeMainContent::setLastScanText(QString text)
{
	m_lastScan->setText(text);

}

void HomeMainContent::setSecurityFearuteText(QString text)
{
	/* Mearsuring text width */
	QFontMetrics fm(FONT);
	int width = fm.width(text);
	m_securityFeature->setFixedWidth(width);
	int pixelsHigh = fm.height();
	m_securityFeature->setFixedHeight(pixelsHigh);


	/* Set text */
	m_securityFeature->setText(text);

}

void HomeMainContent::setSecureFearuteDetailsText(QString text)
{
	/* Mearsuring text width */
	QFontMetrics fm(FONT);
	int width = fm.width(text);
	int pixelsHigh = fm.height();
	m_featureDetails->setFixedWidth(width);
	m_featureDetails->setFixedHeight(pixelsHigh);

	/* Set text */
	m_featureDetails->setText(text);

}

void HomeMainContent::setIcon()
{
	QIcon icon;

	switch (AppSetting::getInstance()->refreshStatus())
	{
	case Status::Protected_Status:
		icon.addFile(HOME_CONTENT_PROTECTED_PATH);
		break;
	case Status::Warning_Status:
		icon.addFile(HOME_CONTENT_WARNING_PATH);

	/* MORE STATUS */
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(icon.pixmap(120, 120));

}

void HomeMainContent::setStyle()
{
	this->setStyleSheet("#HomeMainContent{border: 0px none palette(shadow); "
		"border-top-left-radius:10px;}");

	m_btn_scanNow->setStyleSheet("QPushButton {color: " + SCAN_NOW_BUTTON_COLOR + ";"
		"border: 1px solid" + SCAN_NOW_BUTTON_COLOR + "; border-radius:6px;}"
		"QPushButton:hover{border: 2px solid " + SCAN_NOW_BUTTON_COLOR + ";}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:
		switch (AppSetting::getInstance()->refreshStatus())
		{
		case Status::Protected_Status:
			m_statusText->setStyleSheet("QLabel {color:" + HOME_PROTECTED_TEXT_COLOR + ";}");

			break;
		case Status::Warning_Status:
			m_statusText->setStyleSheet("QLabel {color:" + HOME_AT_RICK_TEXT_COLOR + ";}");
			/* MORE STATUS */
			break;
		default:
			break;
		}

		m_lastScan->setStyleSheet("QLabel { color:" + LAST_SCAN_COLOR_TEXT_DARK_THEME + ";}");
		m_securityFeature->setStyleSheet("QLabel { color:" + SECURE_FEATURE_COLOR_DARK_THEME + ";}");
		m_featureDetails->setStyleSheet("QLabel { color:" + DETAILS_TEXT_COLOR_DARK_THEME + ";}");
		m_policy->setStyleSheet("QLabel{ color:" + POLICY_BORDER_TEXT_DT + ";"
			"border-top-left-radius: 14px;"
			"border-bottom-left-radius: 14px;"
			"border: 1px solid " + POLICY_BORDER_TEXT_DT + ";"
			"}");
		break;

	case Theme_Type::Light_Theme:

		switch (AppSetting::getInstance()->refreshStatus())
		{
		case Status::Protected_Status:
			m_statusText->setStyleSheet("QLabel {color:" + HOME_PROTECTED_TEXT_COLOR + ";}");

			break;
		case Status::Warning_Status:
			m_statusText->setStyleSheet("QLabel {color:" + HOME_AT_RICK_TEXT_COLOR + ";}");
			/* MORE STATUS */
			break;
		default:
			break;
		}
		m_lastScan->setStyleSheet("QLabel {  color:" + LAST_SCAN_COLOR_TEXT_LIGHT_THEME + ";}");
		m_securityFeature->setStyleSheet("QLabel {  color:" + SECURE_FEATURE_COLOR_LIGHT_THEME + ";}");
		m_featureDetails->setStyleSheet("QLabel {  color:" + DETAILS_TEXT_COLOR_LIGHT_THEME + ";}");
		m_policy->setStyleSheet("QLabel{ color:" + POLICY_BORDER_TEXT_LT + ";"
			"border-top-left-radius: 14px;"
			"border-bottom-left-radius: 14px;"
			"border: 1px solid " + POLICY_BORDER_TEXT_LT + ";"
			"}");
		break;

		/* MORE THEME */
	default:
		break;
	}

}

void HomeMainContent::scanButtonClick()
{
	emit scanNowButtonClicked();
}

void HomeMainContent::featureDetailsClick()
{
	emit featureDetailsClicked();
}

void HomeMainContent::changeTheme()
{
	setStyle();
}

void HomeMainContent::changeStatus()
{
	setStyle();
	setIcon();
	switch (AppSetting::getInstance()->refreshStatus())
	{
	case Status::Protected_Status:
		setStatusText(QString("All's Good. Your PC is Protected"));
		break;
	case Status::Warning_Status:
		setStatusText(QString("Your device is at risk"));

		/* MORE STATUS */
		break;
	default:
		break;
	}
}

FeatureDetailsLabel::FeatureDetailsLabel(QLabel *parent)
	: QLabel(parent)
{

}

FeatureDetailsLabel::~FeatureDetailsLabel()
{
}

void FeatureDetailsLabel::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	emit clicked();
}
