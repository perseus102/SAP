#include "settingscontent.h"
#include <QScrollArea>

SettingsContent::SettingsContent(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::SettingsContent)
{
	ui->setupUi(this);
	m_settingTopBar = new TopBar();
	m_settingTopBar->setVisibleNaviButton(false);
	m_settingTopBar->addDir("Settings", Directory::Setting); //Can use for multi language
	m_curSettingDir = Directory::Setting;

	stackedWidget = new QStackedWidget();
	m_settingLayout = new QVBoxLayout;
	m_settingLayout->setContentsMargins(30, 20, 0, 0);
	m_settingLayout->setSpacing(0);
	m_settingLayout->addWidget(m_settingTopBar);
	m_settingLayout->addWidget(stackedWidget);

	m_SettingGridContent	= new SettingGridContent();
	m_languagePersonal		= new LanguagePersonal();
	m_protectionModes		= new ProtectionModes();
	m_scanSettings			= new ScanSettings();

	stackedWidget->addWidget(m_SettingGridContent);
	stackedWidget->addWidget(m_languagePersonal);
	stackedWidget->addWidget(m_protectionModes);
	stackedWidget->addWidget(m_scanSettings);
	setLayout(m_settingLayout);

	/* Init Fade In*/
	eff = new QGraphicsOpacityEffect(this);
	this->setGraphicsEffect(eff);
	mpFadeIn = new QPropertyAnimation(eff, "opacity");
	mpFadeIn->setDuration(300);
	mpFadeIn->setStartValue(0);
	mpFadeIn->setEndValue(1);
	connect(mpFadeIn, SIGNAL(finished()), this, SLOT(onFadeInFinished()));

	connect(m_SettingGridContent, &SettingGridContent::gridWidgetPressed, this, &SettingsContent::changeSettingsView);
	
	connect(m_settingTopBar->getButton(), &QPushButton::clicked, this, &SettingsContent::backBtnPressed);

	connect(m_settingTopBar, &TopBar::labelDirClicked, this, &SettingsContent::directoryClicked);

	setStyleSheet("#HomeContent{border: 0px none palette(shadow); "
		"border-top-left-radius:10px;}");

}

SettingsContent::~SettingsContent()
{
}

void SettingsContent::fadeIn()
{
	eff->setEnabled(true);
	mpFadeIn->start();
}

void SettingsContent::changeToAntivirusTab()
{
	stackedWidget->setCurrentWidget(m_scanSettings);
	if (m_settingTopBar->getLastLabel()->text() != "Scan Settings")
	{
		m_settingTopBar->addDir("Scan Settings", Directory::Scan_Settings);
	}
	m_curSettingDir = Directory::Scan_Settings;
	m_settingTopBar->setVisibleNaviButton(true);
	m_scanSettings->activeAntivirusTab();
	fadeIn();
}

void SettingsContent::changeSettingsView(QString widgetName)
{
	if (widgetName == "scanSettings")
	{
		stackedWidget->setCurrentWidget(m_scanSettings);
		m_settingTopBar->addDir("Scan Settings", Directory::Scan_Settings);
		m_curSettingDir = Directory::Scan_Settings;
		m_settingTopBar->setVisibleNaviButton(true);
	}
	else if (widgetName == "allowList")
	{
		//stackedWidget->setCurrentWidget();
	}
	else if (widgetName == "vulnerability")
	{
		//stackedWidget->setCurrentWidget();
	}
	else if (widgetName == "protectionMode")
	{
		stackedWidget->setCurrentWidget(m_protectionModes);
		m_settingTopBar->addDir("Protection Modes", Directory::Protection_mode);
		m_curSettingDir = Directory::Protection_mode;
		m_settingTopBar->setVisibleNaviButton(true);

	}
	else if (widgetName == "info")
	{
		//stackedWidget->setCurrentWidget();
	}
	else if (widgetName == "languagePersonal")
	{
		stackedWidget->setCurrentWidget(m_languagePersonal);
		m_settingTopBar->addDir("Language & Personalization", Directory::Language_Personal);
		m_curSettingDir = Directory::Language_Personal;
		m_settingTopBar->setVisibleNaviButton(true);

	}
	else if (widgetName == "manageUser")
	{
		//stackedWidget->setCurrentWidget();
	}
	else if (widgetName == "updates")
	{
		//stackedWidget->setCurrentWidget();
	}
	else if (widgetName == "others")
	{
		//stackedWidget->setCurrentWidget();
	}

	fadeIn();

}

void SettingsContent::backBtnPressed()
{
	switch (m_curSettingDir)
	{
	case Setting:
		break;
	case Protection_mode:
	case Language_Personal:
	case Scan_Settings:
		m_settingTopBar->setVisibleNaviButton(false);
		stackedWidget->setCurrentWidget(m_SettingGridContent);
		m_curSettingDir = Directory::Setting;
		break;
	default:
		break;
	}

	fadeIn();
}

void SettingsContent::directoryClicked(Directory dir)
{
	switch (dir)
	{
	case Setting:
		if (m_curSettingDir == Directory::Setting)
			return;

		stackedWidget->setCurrentWidget(m_SettingGridContent);
		m_curSettingDir = Directory::Setting;
		m_settingTopBar->setVisibleNaviButton(false);

		break;
	case Protection_mode:
		if (m_curSettingDir == Directory::Protection_mode)
			return;

		break;
	case Language_Personal:
		if (m_curSettingDir == Directory::Language_Personal)
			return;

	case Scan_Settings:
		if (m_curSettingDir == Directory::Scan_Settings)
			return;
		break;
	default:
		break;
	}

	fadeIn();

}

void SettingsContent::showEvent(QShowEvent *)
{
	//eff->setEnabled(true);
	//mpFadeIn->start();
	//fadeIn();
}

void SettingsContent::onFadeInFinished()
{
	eff->setEnabled(false);
}