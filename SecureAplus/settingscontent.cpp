#include "settingscontent.h"
#include <QScrollArea>

SettingsContent::SettingsContent(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::SettingsContent)
{
	ui->setupUi(this);
	m_settingTopBar = new TopBar();
	m_settingTopBar->setVisibleNaviButton(false);
	m_settingTopBar->setDirectoryText("Settings"); //Can use for multi language
	stackedWidget = new QStackedWidget();

	m_settingLayout = new QVBoxLayout;
	m_settingLayout->setContentsMargins(30, 20, 30, 0);
	m_settingLayout->setSpacing(0);
	m_settingLayout->addWidget(m_settingTopBar);
	m_settingLayout->addWidget(stackedWidget);

	m_SettingGridContent	= new SettingGridContent();
	m_languagePersonal		= new LanguagePersonal();
	m_protectionModes		= new ProtectionModes();

	stackedWidget->addWidget(m_SettingGridContent);
	stackedWidget->addWidget(m_languagePersonal);
	stackedWidget->addWidget(m_protectionModes);
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

void SettingsContent::changeSettingsView(QString widgetName)
{
	qDebug() << widgetName;
	if (widgetName == "scanning")
	{
		//stackedWidget->setCurrentWidget();
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
		m_settingTopBar->setDirectoryText("Settings \\ Protection Modes");

	}
	else if (widgetName == "info")
	{
		//stackedWidget->setCurrentWidget();
	}
	else if (widgetName == "languagePersonal")
	{
		stackedWidget->setCurrentWidget(m_languagePersonal);
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
	m_settingTopBar->setVisibleNaviButton(true);

	fadeIn();
}

void SettingsContent::backBtnPressed()
{
	stackedWidget->setCurrentWidget(m_SettingGridContent);
	m_settingTopBar->setVisibleNaviButton(false);
	m_settingTopBar->setDirectoryText("Settings");

	fadeIn();
}

void SettingsContent::showEvent(QShowEvent *)
{
	eff->setEnabled(true);
	mpFadeIn->start();
}

void SettingsContent::onFadeInFinished()
{
	eff->setEnabled(false);
}