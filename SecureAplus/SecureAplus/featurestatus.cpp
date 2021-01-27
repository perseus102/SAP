#include "featurestatus.h"
#include "SecurityFeaturesNoOfflineAV.h"
SettingButton::SettingButton(QWidget* parent)
	: QPushButton(parent)
{
	setFixedSize(16, 16);
	setStyleSheet("QPushButton {border: 0px;}");
	initIcon();
	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SettingButton::changeTheme);
}

SettingButton::~SettingButton() {};

void SettingButton::enterEvent(QEvent*)
{
	setIconSize(QSize(14, 14));
}

void SettingButton::leaveEvent(QEvent*)
{
	setIconSize(QSize(16, 16));
}

void SettingButton::initIcon()
{
	QIcon settingIcon;
	setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		settingIcon = util::getInstance()->ChangeSVGColor(FEATURE_SETTING, FEATURE_SETTING_LT);
		break;

	case Theme_Type::Dark_Theme:
		settingIcon = util::getInstance()->ChangeSVGColor(FEATURE_SETTING, FEATURE_SETTING_DT);

		break;

		//MORE THEME
	default:
		break;
	}

	setIcon(settingIcon);
	setIconSize(QSize(16, 16));
}

void SettingButton::changeTheme()
{
	initIcon();
}

FeatureStatus::FeatureStatus(Feature featureName, Feature_States state, QWidget *parent)
	: QWidget(parent),
	m_featureName(featureName),
	m_featureState(state)
{
	ui.setupUi(this);

	m_featureWidget = new QWidget();
	//m_featureWidget->setFixedSize(560, 50);
	m_featureWidget->setFixedHeight(50);
	m_featureLayout = new QVBoxLayout();
	m_featureLayout->setContentsMargins(0, 0, 0, 0 );
	m_featureLayout->setSpacing(0);
	m_featureLayout->addWidget(m_featureWidget);
	setLayout(m_featureLayout);

	m_layout = new QHBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	m_featureWidget->setLayout(m_layout);

	m_featureNameLabel = new QLabel();
	//m_featureNameLabel->setFixedWidth(226);
	m_featureNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_featureNameLabel->setFont(FONT);

	m_statusIcon = new QLabel();
	m_statusIcon->setFixedWidth(12);
	m_statusIcon->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	m_statusTextLabel = new QLabel();
	//m_statusTextLabel->setFixedWidth(264);
	m_statusTextLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_statusTextLabel->setFont(FONT);

	QLabel *spacerLeft = new QLabel();
	spacerLeft->setFixedWidth(24);

	QLabel *spacerCenter = new QLabel();
	spacerCenter->setFixedWidth(10);

	m_layout->addWidget(spacerLeft);
	m_layout->addWidget(m_featureNameLabel);
	m_layout->addWidget(m_statusIcon);
	m_layout->addWidget(spacerCenter);
	m_layout->addWidget(m_statusTextLabel);

	if (m_featureName == Feature::Lisence || m_featureName == Feature::RealTime_Scanning)
	{
		//m_statusTextLabel->setFixedWidth(248);

		m_settingButton = new SettingButton();
		m_settingButton->setFixedSize(16, 16);
		m_layout->addWidget(m_settingButton);
		//setSettingBtnStyle();
		connect(m_settingButton, &QPushButton::clicked, this, &FeatureStatus::settingBtnClicked);

	}

	QLabel *spacerRight = new QLabel();
	spacerRight->setFixedWidth(24);
	m_layout->addWidget(spacerRight);
	setStyle();

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &FeatureStatus::changeTheme);
	connect(this, &FeatureStatus::changeScreen, AppSetting::getInstance(), &AppSetting::appChangeScreen);
	connect(&timerRefresh, SIGNAL(timeout()), this, SLOT(refresh()));
}

FeatureStatus::~FeatureStatus()
{

}

void FeatureStatus::setFeatureName(QString name)
{
	m_featureNameLabel->setText(name);
}

void FeatureStatus::setStatusText(QString text)
{
	m_statusTextLabel->setText(text);
}

void FeatureStatus::setFeatureState(Feature_States featureState)
{
	m_featureState = featureState;
	setStyle();
}

Feature_States FeatureStatus::getFeatureState()
{
	return m_featureState;
}

void FeatureStatus::setFeatureName(Feature featureName)
{
	m_featureName = featureName;
}

Feature FeatureStatus::getFeatureName()
{
	return m_featureName;
}

void FeatureStatus::settingBtnClicked()
{
	if (m_featureName == Feature::Lisence)
	{
		//emit changeScreen(Screen::License_Screen);
	}
	else if (m_featureName == Feature::RealTime_Scanning)
	{
		emit changeScreen(Screen::Antivirus_Tab);
	}
}

void FeatureStatus::resizeEvent(QResizeEvent *)
{
	if (m_featureName == Feature::Lisence || m_featureName == Feature::RealTime_Scanning)
	{
		m_featureNameLabel->setFixedSize((this->width() / 2) - 24 - 12, 50);
	}
}

void FeatureStatus::showEvent(QShowEvent * event)
{
	refresh();
	timerRefresh.start(1500);
}

void FeatureStatus::setStyle()
{
	/*switch (m_featureName)
	{
	case Lisence:
		setLicenseStyle();
		break;
	case RealTime_Scanning:
		setRTimeScanStyle();
		break;
	case Universal_AV:
		setUAVServiceStyle();
		break;
	case WhiteList_Driver:
		setWListDriverStyle();
		break;
	case WhiteList_Service:
		setWListServiceStyle();
		break;
	case SAP_Service:
		setSAPServiceStyle();
		break;
	case Antivirus_Driver:
		setAntivDrivereStyle();
		break;
	case Offline_Antivirus_Service:
		setOffAntivServiceStyle();
		break;
	default:
		break;
	}*/

	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_featureState)
	{
	case Active:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_ACTIVE);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_ACTIVE + ";border-radius:0px;}");
		break;
	case Off_Intentional:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_OFF_INTENTIONAL);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_OFF_INTENTIONAL + ";border-radius:0px;}");
		break;
	case Off_NotIntentional:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_OFF_NOT_INTENTIONAL);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_OFF_NOT_INTENTIONAL + ";border-radius:0px;}");
		break;
	case Expire_Soon:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_EXPIRE_SOON);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_EXPIRE_SOON + ";border-radius:0px;}");
		break;
	case Expired:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_EXPIRED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_EXPIRED + ";border-radius:0px;}");
		break;
	case Invalid:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_INVALID);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_INVALID + ";border-radius:0px;}");
		break;
	case Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Installed:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_INSTALLED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_INSTALLED + ";border-radius:0px;}");
		break;
	case Start_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_START_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_START_PENDING + ";border-radius:0px;}");
		break;
	case Stop_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_STOP_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_STOP_PENDING + ";border-radius:0px;}");
		break;
	case Continue_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_CONTINUE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_CONTINUE_PENDING + ";border-radius:0px;}");
		break;
	case Pause_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSE_PENDING + ";border-radius:0px;}");
		break;
	case Paused:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSED + ";border-radius:0px;}");
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		
		this->setStyleSheet("background-color:" + FEATURE_BACKGROUND_LT + ";");
		m_featureNameLabel->setStyleSheet("QLabel {color:" + FEATURE_NAME_LT + ";border-radius:0px;}");
		break;

	case Theme_Type::Dark_Theme:
		this->setStyleSheet("background-color:" + FEATURE_BACKGROUND_DT + ";");
		m_featureNameLabel->setStyleSheet("QLabel {color:" + FEATURE_NAME_DT + ";border-radius:0px;}");

		break;

		//MORE THEME
	default:
		break;
	}

}

void FeatureStatus::setLicenseStyle()
{
	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_featureState)
	{
	case Active:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_ACTIVE);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_ACTIVE + ";border-radius:0px;}");
		break;
	case Off_Intentional:
		break;
	case Off_NotIntentional:
		break;
	case Expire_Soon:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_EXPIRE_SOON);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_EXPIRE_SOON + ";border-radius:0px;}");
		break;
	case Expired:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_EXPIRED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_EXPIRED + ";border-radius:0px;}");
		break;
	case Invalid:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_INVALID);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_INVALID + ";border-radius:0px;}");
		break;
	case Feature_States::Running:
		break;
	case Not_Running:
		break;
	case Not_Installed:
		break;
	case Start_Pending:
		break;
	case Stop_Pending:
		break;
	case Continue_Pending:
		break;
	case Pause_Pending:
		break;
	case Paused:
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));
}

void FeatureStatus::setRTimeScanStyle()
{
	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_featureState)
	{
	case Active:
		break;
	case Off_Intentional:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_OFF_INTENTIONAL);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_OFF_INTENTIONAL + ";border-radius:0px;}");
		break;
	case Off_NotIntentional:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_OFF_NOT_INTENTIONAL);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_OFF_NOT_INTENTIONAL + ";border-radius:0px;}");
		break;
	case Expire_Soon:
		break;
	case Expired:
		break;
	case Invalid:
		break;
	case Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Running:
		break;
	case Not_Installed:
		break;
	case Start_Pending:
		break;
	case Stop_Pending:
		break;
	case Continue_Pending:
		break;
	case Pause_Pending:
		break;
	case Paused:
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));
}

void FeatureStatus::setUAVServiceStyle()
{
	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_featureState)
	{
	case Active:
		break;
	case Off_Intentional:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_OFF_INTENTIONAL);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_OFF_INTENTIONAL + ";border-radius:0px;}");
		break;
	case Off_NotIntentional:

		break;
	case Expire_Soon:
		break;
	case Expired:
		break;
	case Invalid:
		break;
	case Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Installed:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_INSTALLED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_INSTALLED + ";border-radius:0px;}");
		break;
	case Start_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_START_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_START_PENDING + ";border-radius:0px;}");
		break;
	case Stop_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_STOP_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_STOP_PENDING + ";border-radius:0px;}");
		break;
	case Continue_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_CONTINUE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_CONTINUE_PENDING + ";border-radius:0px;}");
		break;
	case Pause_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSE_PENDING + ";border-radius:0px;}");
		break;
	case Paused:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSED + ";border-radius:0px;}");
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));
}

void FeatureStatus::setWListDriverStyle()
{
	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_featureState)
	{
	case Active:
		break;
	case Off_Intentional:
		break;
	case Off_NotIntentional:
		break;
	case Expire_Soon:
		break;
	case Expired:
		break;
	case Invalid:
		break;
	case Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Installed:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_INSTALLED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_INSTALLED + ";border-radius:0px;}");
		break;
	case Start_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_START_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_START_PENDING + ";border-radius:0px;}");
		break;
	case Stop_Pending:
		//dotStatusIcon = util::getInstance()->ChangeSVGColor(DOT_STATUS, FEATURE_STOP_PENDING);
		//m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_STOP_PENDING + ";border-radius:0px;}");
		break;
	case Continue_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_CONTINUE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_CONTINUE_PENDING + ";border-radius:0px;}");
		break;
	case Pause_Pending:
		//dotStatusIcon = util::getInstance()->ChangeSVGColor(DOT_STATUS, FEATURE_PAUSE_PENDING);
		//m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSE_PENDING + ";border-radius:0px;}");
		break;
	case Paused:
		//dotStatusIcon = util::getInstance()->ChangeSVGColor(DOT_STATUS, FEATURE_PAUSED);
		//m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSED + ";border-radius:0px;}");
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));
}

void FeatureStatus::setWListServiceStyle()
{
	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_featureState)
	{
	case Active:
		break;
	case Off_Intentional:
		break;
	case Off_NotIntentional:
		break;
	case Expire_Soon:
		break;
	case Expired:
		break;
	case Invalid:
		break;
	case Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Installed:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_INSTALLED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_INSTALLED + ";border-radius:0px;}");
		break;
	case Start_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_START_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_START_PENDING + ";border-radius:0px;}");
		break;
	case Stop_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_STOP_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_STOP_PENDING + ";border-radius:0px;}");
		break;
	case Continue_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_CONTINUE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_CONTINUE_PENDING + ";border-radius:0px;}");
		break;
	case Pause_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSE_PENDING + ";border-radius:0px;}");
		break;
	case Paused:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSED + ";border-radius:0px;}");
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));
}

void FeatureStatus::setSAPServiceStyle()
{
	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_featureState)
	{
	case Active:
		break;
	case Off_Intentional:
		break;
	case Off_NotIntentional:
		break;
	case Expire_Soon:
		break;
	case Expired:
		break;
	case Invalid:
		break;
	case Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Installed:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_INSTALLED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_INSTALLED + ";border-radius:0px;}");
		break;
	case Start_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_START_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_START_PENDING + ";border-radius:0px;}");
		break;
	case Stop_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_STOP_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_STOP_PENDING + ";border-radius:0px;}");
		break;
	case Continue_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_CONTINUE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_CONTINUE_PENDING + ";border-radius:0px;}");
		break;
	case Pause_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSE_PENDING + ";border-radius:0px;}");
		break;
	case Paused:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSED + ";border-radius:0px;}");
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));
}

void FeatureStatus::setAntivDrivereStyle()
{
	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_featureState)
	{
	case Active:
		break;
	case Off_Intentional:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_OFF_INTENTIONAL);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_OFF_INTENTIONAL + ";border-radius:0px;}");
		break;
	case Off_NotIntentional:
		break;
	case Expire_Soon:
		break;
	case Expired:
		break;
	case Invalid:
		break;
	case Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Installed:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_INSTALLED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_INSTALLED + ";border-radius:0px;}");
		break;
	case Start_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_START_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_START_PENDING + ";border-radius:0px;}");
		break;
	case Stop_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_STOP_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_STOP_PENDING + ";border-radius:0px;}");
		break;
	case Continue_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_CONTINUE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_CONTINUE_PENDING + ";border-radius:0px;}");
		break;
	case Pause_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSE_PENDING + ";border-radius:0px;}");
		break;
	case Paused:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSED + ";border-radius:0px;}");
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));
}

void FeatureStatus::setOffAntivServiceStyle()
{
	QIcon dotStatusIcon;

	switch (m_featureState)
	{
	case Active:
		break;
	case Off_Intentional:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_OFF_INTENTIONAL);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_OFF_INTENTIONAL + "; border-radius:0px;}");
		break;
	case Off_NotIntentional:
		break;
	case Expire_Soon:
		break;
	case Expired:
		break;
	case Invalid:
		break;
	case Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_RUNNING + ";border-radius:0px;}");
		break;
	case Not_Installed:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_NOT_INSTALLED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_NOT_INSTALLED + ";border-radius:0px;}");
		break;
	case Start_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_START_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_START_PENDING + ";border-radius:0px;}");
		break;
	case Stop_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_STOP_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_STOP_PENDING + ";border-radius:0px;}");
		break;
	case Continue_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_CONTINUE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_CONTINUE_PENDING + ";border-radius:0px;}");
		break;
	case Pause_Pending:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSE_PENDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSE_PENDING + ";border-radius:0px;}");
		break;
	case Paused:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, FEATURE_PAUSED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + FEATURE_PAUSED + ";border-radius:0px;}");
		break;
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));
}

void FeatureStatus::setSettingBtnStyle()
{
	QIcon settingIcon;
	m_settingButton->setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		settingIcon = util::getInstance()->ChangeSVGColor(FEATURE_SETTING, FEATURE_SETTING_LT);
		break;

	case Theme_Type::Dark_Theme:
		settingIcon = util::getInstance()->ChangeSVGColor(FEATURE_SETTING, FEATURE_SETTING_DT);

		break;

		//MORE THEME
	default:
		break;
	}

	m_settingButton->setIcon(settingIcon);
	m_settingButton->setIconSize(QSize(16, 16));
}

void FeatureStatus::refresh()
{
	QString str;

	bool b = GetSecurityFeatureStatus(m_featureName);

	getSecurityFeatureString(str, m_featureName);



	QStringList splitStr = str.split(":");

	qDebug()<< m_featureName << str << splitStr[1];
	if (splitStr.count() < 2) return;
	
	if (splitStr[1] == " Valid")
	{
		m_featureState = Feature_States::Active;
		setStatusText("Active");
	}
	else if (splitStr[1] == " Running")
	{
		m_featureState = Feature_States::Running;
		setStatusText("Running");
	}
	else if (splitStr[1] == " Trust all mode")
	{
		m_featureState = Feature_States::Running;
		setStatusText("Trust all mode");
	}
	else if (splitStr[1] == " APEX")
	{
		m_featureState = Feature_States::Running;
		setStatusText("APEX");
	}
	else if (splitStr[1] == " Not available")
	{
		m_featureState = Feature_States::Not_Running;
		setStatusText("Not available");
	}
	else if (splitStr[1] == " Disabled")
	{
		m_featureState = Feature_States::Not_Running;
		setStatusText("Disabled");
	}
	else if (splitStr[1] == " Off")
	{
		m_featureState = Feature_States::Off_NotIntentional;
		setStatusText("Off");
	}
	else if (splitStr[1] == " On")
	{
		m_featureState = Feature_States::Running;
		setStatusText("On");
	}
	else if (splitStr[1] == " Expired")
	{
		m_featureState = Feature_States::Expired;
		setStatusText("Expired");
	}
	else if (splitStr[1] == " Not installed")
	{
		m_featureState = Feature_States::Not_Installed;
		setStatusText("Not installed");
	}
	else if (splitStr[1] == " Not running")
	{
		m_featureState = Feature_States::Not_Running;
		setStatusText("Not running");
	}
	else if (splitStr[1] == " Start pending")
	{
		m_featureState = Feature_States::Start_Pending;
		setStatusText("Start pending");
	}
	else if (splitStr[1] == " Stop pending")
	{
		m_featureState = Feature_States::Stop_Pending;
		setStatusText("Stop pending");
	}
	else if (splitStr[1] == " Continue pending")
	{
		m_featureState = Feature_States::Continue_Pending;
		setStatusText("Continue pending");
	}
	else if (splitStr[1] == " Pause pending")
	{
		m_featureState = Feature_States::Pause_Pending;
		setStatusText("Pause pending");
	}
	else if (splitStr[1] == " Paused")
	{
		m_featureState = Feature_States::Paused;
		setStatusText("Paused");
	}
	else if (splitStr[1] == " Unknown state")
	{
		m_featureState = Feature_States::Not_Running;
		setStatusText("Unknown state");
	}


	setStyle();
}

void FeatureStatus::changeTheme()
{
	setStyle();
	//if (m_featureName == Feature::Lisence || m_featureName == Feature::RealTime_Scanning)
	//{
	//	setSettingBtnStyle();
	//}
}


