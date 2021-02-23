#include "stdafx.h"
#include "featuredetails.h"
#include "SecurityFeaturesNoOfflineAV.h"
#include <Windows.h>

HANDLE hStopEventThreadIsSecurityFeaturesRunning = NULL;
HANDLE hThreadIsSecurityFeaturesRunning = NULL;

DWORD WINAPI ThreadIsSecurityFeaturesRunning(LPVOID lpParam)
{
	HANDLE hStopEvent = (HANDLE)lpParam;
	do
	{
		IsSecurityFeaturesRunning();
	} while (hStopEvent && WaitForSingleObject(hStopEvent, 1000) != 0);

	return 0;
}

FeatureDetails::FeatureDetails(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	if (hStopEventThreadIsSecurityFeaturesRunning == NULL && hThreadIsSecurityFeaturesRunning == NULL)
	{
		hStopEventThreadIsSecurityFeaturesRunning = CreateEvent(NULL, TRUE, FALSE, NULL);
		hThreadIsSecurityFeaturesRunning = CreateThread(NULL, 0, ThreadIsSecurityFeaturesRunning, hStopEventThreadIsSecurityFeaturesRunning, 0, NULL);
	}

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(29, 20, 30, 0);
	m_layout->setSpacing(0);

	m_FeatureTopBar = new TopBar();
	m_FeatureTopBar->setVisibleNaviButton(true);
	m_FeatureTopBar->addDir("Back to Home", Directory::Home); //Can use for multi language
	
	QLabel *spacerTopBar = new QLabel();
	spacerTopBar->setFixedHeight(20);

	QWidget* featureWg = new QWidget();
	featureWg->setFixedHeight(428); // increase 54px for 1 FeatureStatus
	QVBoxLayout* featureLayout = new QVBoxLayout();
	featureLayout->setContentsMargins(0, 0, 0, 0);
	featureLayout->setSpacing(4);
	featureWg->setLayout(featureLayout);

	m_LicenseFeature = new FeatureStatus(Feature::Lisence, Feature_States::Expire_Soon);
	m_LicenseFeature->setFeatureName("License");
	m_LicenseFeature->setStatusText("Expire Soon");

	m_RTimeFeature = new FeatureStatus(Feature::RealTime_Scanning, Feature_States::Off_Intentional);
	m_RTimeFeature->setFeatureName("Real-time Scanning");
	m_RTimeFeature->setStatusText("Off");

	//m_UAVServiceFeature = new FeatureStatus(Feature::Universal_AV, Feature_States::Running);
	//m_UAVServiceFeature->setFeatureName("Universal AV Service");
	//m_UAVServiceFeature->setStatusText("Running");

	m_WListDriverFeature = new FeatureStatus(Feature::WhiteList_Driver, Feature_States::Running);
	m_WListDriverFeature->setFeatureName("App Whitelisting Driver");
	m_WListDriverFeature->setStatusText("Running");

	m_WListServiceFeature = new FeatureStatus(Feature::WhiteList_Service, Feature_States::Running);
	m_WListServiceFeature->setFeatureName("App Whitelisting Service");
	m_WListServiceFeature->setStatusText("Running");

	m_SAPServiceFeature = new FeatureStatus(Feature::SAP_Service, Feature_States::Running);
	m_SAPServiceFeature->setFeatureName("SecureAPlus Service");
	m_SAPServiceFeature->setStatusText("Running");

	m_AntivDriverFeature = new FeatureStatus(Feature::Antivirus_Driver, Feature_States::Running);
	m_AntivDriverFeature->setFeatureName("Antivirus Driver");
	m_AntivDriverFeature->setStatusText("Running");

	m_OffAntivServiceFeature = new FeatureStatus(Feature::Offline_Antivirus_Service, Feature_States::Running);
	m_OffAntivServiceFeature->setFeatureName("Offline Antivirus Service");
	m_OffAntivServiceFeature->setStatusText("Apex");

	QLabel *spacerBottom = new QLabel();
	QLabel *featureBottom = new QLabel();

	m_layout->addWidget(m_FeatureTopBar);
	m_layout->addWidget(spacerTopBar);

	featureLayout->addWidget(m_LicenseFeature);
	featureLayout->addWidget(m_RTimeFeature);
	//featureLayout->addWidget(m_UAVServiceFeature);
	featureLayout->addWidget(m_WListDriverFeature);
	featureLayout->addWidget(m_WListServiceFeature);
	featureLayout->addWidget(m_SAPServiceFeature);
	featureLayout->addWidget(m_AntivDriverFeature);
	featureLayout->addWidget(m_OffAntivServiceFeature);
	featureLayout->addWidget(featureBottom);

	m_layout->addWidget(featureWg);
	m_layout->addWidget(spacerBottom);

	setLayout(m_layout);
	checkFeatureLicense();
	connect(m_FeatureTopBar->getButton(), &QPushButton::clicked, this, &FeatureDetails::backBtnCliked);
	connect(m_FeatureTopBar, &TopBar::labelDirClicked, this, &FeatureDetails::backToHomeClick);

}

FeatureDetails::~FeatureDetails()
{
}

void FeatureDetails::checkFeatureLicense()
{
	if (AppSetting::getInstance()->getLicense() == License::License_Expired)
	{
		m_RTimeFeature->setVisible(false);
		//m_UAVServiceFeature->setVisible(false);
		m_WListDriverFeature->setVisible(false);
		m_WListServiceFeature->setVisible(false);
		m_SAPServiceFeature->setVisible(false);
		m_AntivDriverFeature->setVisible(false);
		m_OffAntivServiceFeature->setVisible(false);
	}
	else
	{
		m_RTimeFeature->setVisible(true);
		//m_UAVServiceFeature->setVisible(true);
		m_WListDriverFeature->setVisible(true);
		m_WListServiceFeature->setVisible(true);
		m_SAPServiceFeature->setVisible(true);
		m_AntivDriverFeature->setVisible(true);
		m_OffAntivServiceFeature->setVisible(true);
	}
}

void FeatureDetails::backBtnCliked()
{
	emit backToHome();
}

void FeatureDetails::backToHomeClick(Directory dir)
{
	Q_UNUSED(dir);

	emit backToHome();
}
