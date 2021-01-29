#include "settingsanitivirus.h"
#include "UniversalAV_Enable.h"
#include "DeepAVEnabled.h"
#include "OfflineAV.h"
#include "NamedPipeSecureAPlusAdminSettings.h"
#include "NamedPipeSecureAPlusServiceSettings.h"
#include "DriverCommand.h"
#include "QTTrustedAccount.h"
#include "DeepAVAvailable.h"
#include "DisableRegisterAsAntiVirus.h"
SettingsAnitivirus::SettingsAnitivirus(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	NTSTATUS status;
	BOOLEAN bRealTimeEnabled = !IsSAScanDisabled(&status);;
	BOOLEAN bRegisterAsAntivirus;
	bRegisterAsAntivirus = !IsDisableRegisterAsAntiVirus();
	if (!IsDeepAVAvailable())
	{
		//hideAPEX(); // TO DO: implement this function, hide APEX-related settings
	}

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	QWidget* APEXWg = new QWidget();
	APEXWg->setFixedHeight(160);
	QVBoxLayout* APEXLayout = new QVBoxLayout();
	APEXLayout->setSpacing(0);
	APEXLayout->setContentsMargins(30, 0, 30, 0);
	APEXWg->setLayout(APEXLayout);

	m_APEX = new QLabel();
	m_APEX->setFont(LARGE_FONT);
	m_APEX->setFixedHeight(20);
	m_APEX->setWordWrap(true);

	QLabel* APEXDescSpacer = new QLabel();
	APEXDescSpacer->setFixedHeight(14);

	m_APEXDesc = new QLabel();
	m_APEXDesc->setFont(SMALL_FONT);
	m_APEXDesc->setFixedHeight(30);
	m_APEXDesc->setWordWrap(true);

	QLabel* sensitivitySpacer = new QLabel();
	sensitivitySpacer->setFixedHeight(15);

	m_sensitivity = new QLabel();
	m_sensitivity->setFont(SMALL_FONT);
	m_sensitivity->setFixedHeight(15);
	m_sensitivity->setWordWrap(true);

	QLabel* cbbSpacer = new QLabel();
	cbbSpacer->setFixedHeight(11);

	m_sensitivityCbb = new SAPCombobox();
	m_sensitivityCbb->setFixedSize(240, 32);
	m_sensitivityCbb->setObjectName("m_sensitivityCbb");

	m_sensitivityCbb->addItem("Low");
	m_sensitivityCbb->addItem("Medium (Recommended)");
	m_sensitivityCbb->addItem("High");
	m_sensitivityCbb->addItem("Very High");
	m_sensitivityCbb->setCurrentIndex(1);

	QLabel* APEXBottomSpacer = new QLabel();

	m_APEXLine = new QLabel();
	m_APEXLine->setFixedHeight(2);

	APEXLayout->addWidget(m_APEX);
	APEXLayout->addWidget(APEXDescSpacer);
	APEXLayout->addWidget(m_APEXDesc);
	APEXLayout->addWidget(sensitivitySpacer);
	APEXLayout->addWidget(m_sensitivity);
	APEXLayout->addWidget(cbbSpacer);
	APEXLayout->addWidget(m_sensitivityCbb);
	APEXLayout->addWidget(APEXBottomSpacer);

	QWidget* APEXRealTimeWg = new QWidget();
	APEXRealTimeWg->setFixedHeight(130);
	QVBoxLayout* APEXRealTimeLayout = new QVBoxLayout();
	APEXRealTimeLayout->setSpacing(0);
	APEXRealTimeLayout->setContentsMargins(30, 0, 30, 0);
	APEXRealTimeWg->setLayout(APEXRealTimeLayout);

	QLabel* APEXRealTimeTopSpacer = new QLabel();
	APEXRealTimeTopSpacer->setFixedHeight(12);

	m_APEXRealtime = new QLabel();
	m_APEXRealtime->setFont(LARGE_FONT);
	m_APEXRealtime->setFixedHeight(20);
	m_APEXRealtime->setWordWrap(true);

	QLabel* APEXRealTimeDescSpacer = new QLabel();
	APEXRealTimeDescSpacer->setFixedHeight(12);

	m_APEXRealtimeDesc = new QLabel();
	m_APEXRealtimeDesc->setFont(SMALL_FONT);
	m_APEXRealtimeDesc->setFixedHeight(30);
	m_APEXRealtimeDesc->setWordWrap(true);

	QLabel* APEXRealTimeToggleSpacer = new QLabel();
	APEXRealTimeToggleSpacer->setFixedHeight(10);

	m_APEXRealtimeToggle = new Switch(QMargins(0, 8, 16, 8), true);
	m_APEXRealtimeToggle->setFixedSize(50, 30);
	m_APEXRealtimeToggle->setChecked(bRealTimeEnabled);

	QLabel* APEXRealTimeBottomSpacer = new QLabel();

	m_APEXRealTimeLine = new QLabel();
	m_APEXRealTimeLine->setFixedHeight(2);

	APEXRealTimeLayout->addWidget(APEXRealTimeTopSpacer);
	APEXRealTimeLayout->addWidget(m_APEXRealtime);
	APEXRealTimeLayout->addWidget(APEXRealTimeDescSpacer);
	APEXRealTimeLayout->addWidget(m_APEXRealtimeDesc);
	APEXRealTimeLayout->addWidget(APEXRealTimeToggleSpacer);
	APEXRealTimeLayout->addWidget(m_APEXRealtimeToggle);
	APEXRealTimeLayout->addWidget(APEXRealTimeBottomSpacer);

	QWidget* registerWg = new QWidget();
	registerWg->setFixedHeight(140);
	QVBoxLayout* registerLayout = new QVBoxLayout();
	registerLayout->setSpacing(0);
	registerLayout->setContentsMargins(30, 0, 30, 0);
	registerWg->setLayout(registerLayout);

	QLabel* registerTopSpacer = new QLabel();
	registerTopSpacer->setFixedHeight(17);

	m_register = new QLabel();
	m_register->setFont(LARGE_FONT);
	m_register->setFixedHeight(20);
	m_register->setWordWrap(true);

	QLabel* registerdescSpacer = new QLabel();
	registerdescSpacer->setFixedHeight(12);

	m_registerDesc = new QLabel();
	m_registerDesc->setFont(SMALL_FONT);
	m_registerDesc->setFixedHeight(40);
	m_registerDesc->setWordWrap(true);

	QLabel* registerToggleSpacer = new QLabel();
	registerToggleSpacer->setFixedHeight(20);

	m_registerToggle = new Switch(QMargins(0, 8, 16, 8), true);
	m_registerToggle->setFixedSize(50, 30);
	m_registerToggle->setChecked(bRegisterAsAntivirus);

	QLabel* registerBottomSpacer = new QLabel();

	registerLayout->addWidget(registerTopSpacer);
	registerLayout->addWidget(m_register);
	registerLayout->addWidget(registerdescSpacer);
	registerLayout->addWidget(m_registerDesc);
	registerLayout->addWidget(registerToggleSpacer);
	registerLayout->addWidget(m_registerToggle);
	registerLayout->addWidget(registerBottomSpacer);

	m_layout->addWidget(APEXWg);
	m_layout->addWidget(m_APEXLine);

	m_layout->addWidget(APEXRealTimeWg);
	m_layout->addWidget(m_APEXRealTimeLine);

	m_layout->addWidget(registerWg);
	QLabel* bottomSpacer = new QLabel();
	m_layout->addWidget(bottomSpacer);

	m_APEXRealtimeScanDlg = new APEXRealTimeDialog();
	transparent = new WidgetTransparent();

	setLayout(m_layout);
	setStyle();
	setLabelText();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SettingsAnitivirus::changeTheme);
	connect(m_APEXRealtimeToggle, &Switch::pressed, this, &SettingsAnitivirus::toggleClicked);
	connect(m_registerToggle, &Switch::clicked, this, &SettingsAnitivirus::toggleClicked);
	connect(m_sensitivityCbb, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxChangeIndex(int)));
}

SettingsAnitivirus::~SettingsAnitivirus()
{
}

void SettingsAnitivirus::toggleClicked()
{
	if (!IsRunByTrustedAccount())
	{
		return;
	}

	DWORD dwLastError = 0;

	if (sender() == m_APEXRealtimeToggle)
	{
		if (m_APEXRealtimeToggle->isChecked())
		{
			//do somthing
			QRect geometry = AppSetting::getInstance()->getAppGeometry();
			transparent->showWidget();
			m_APEXRealtimeScanDlg->setGeometry(geometry.x() + (geometry.width() / 2) - 220, geometry.y() + 16, 440, 170);
			m_APEXRealtimeScanDlg->showDialog();
			transparent->hide();
			if (m_APEXRealtimeScanDlg->getBtnClicked() == QDialog::Accepted)
			{
				m_APEXRealtimeToggle->setChecked(false);
				AppSetting::getInstance()->changeProtectModeByOtherSetting(Protection_Modes::Lockdown_Default);
				emit setDisableRealTimeScan(true);
			}
			else
			{
				//do somthing
				
			}
		}
		else
		{
			//do somthing
			AppSetting::getInstance()->changeProtectModeByOtherSetting(Protection_Modes::Automatic_Mode);
			emit setDisableRealTimeScan(false);
		}
		bool ischecked = m_APEXRealtimeToggle->isChecked();

		dwLastError = SecureaplusSettingsEnableRealTime(m_APEXRealtimeToggle->isChecked());

		if (dwLastError == 0)
		{
			//When real-time is ON, there has to be at least 1 active engine.
			if (!m_APEXRealtimeToggle->isChecked() == TRUE && IsDeepAVEnabled() == FALSE && IsOfflineAVEnabled() == FALSE && IsUniversalAVEnabledForRealTimeScanning() == FALSE)
			{
				if (IsDeepAVAvailable()) //IsOfflineAVAvailable()
				{
					SecureaplusAdminEnableUAVForRealTimeScanning(TRUE);
				}
				if (IsUniversalAVAvailable())
				{
					SecureaplusAdminEnableUAVForRealTimeScanning(FALSE);
				}
			}
		}
	}
	else if (sender() == m_registerToggle)
	{
		if (m_registerToggle->isChecked())
		{
			//do somthing
			qDebug() << m_registerToggle->isChecked();

		}
		else
		{
			
			//do somthing
			qDebug() << m_registerToggle->isChecked();
		}

		dwLastError = SecureaplusSettingsEnableRegisterAsAntivirus(m_registerToggle->isChecked());
	}
}

void SettingsAnitivirus::comboboxChangeIndex(int index)
{
	Q_UNUSED(index);
	//do somthing
}

void SettingsAnitivirus::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		m_APEX->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_APEXDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_sensitivity->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_APEXLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		m_APEXRealtime->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_APEXRealtimeDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_APEXRealTimeLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		m_register->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_registerDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:

		m_APEX->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_APEXDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_sensitivity->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_APEXLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_APEXRealtime->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_APEXRealtimeDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_APEXRealTimeLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_register->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_registerDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void SettingsAnitivirus::setLabelText()
{
	m_APEX->setText("APEX");
	m_APEXDesc->setText("Deep learning offline antivirus engine that scans executable files. Higher sensitivity may improve the detection rate, but it may cause higher false alarm");
	m_sensitivity->setText("Sensitivity");
	m_APEXRealtime->setText("APEX Real-time Scanning");
	m_APEXRealtimeDesc->setText("Your machine will be scanned immediately for any newly installed or created executable files and when an untrusted application is being executed.");
	m_register->setText("Register as Anrivirus");
	m_registerDesc->setText("By registering as antirivus, other third party antivirus may be disabled by itself. Sometimes you may need to disable this, to allow SecureAPlus to work together with other antivirus products.");
}

void SettingsAnitivirus::changeTheme()
{
	setStyle();
}

