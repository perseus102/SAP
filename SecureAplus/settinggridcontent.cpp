#include "settinggridcontent.h"

SettingGridContent::SettingGridContent(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_flowLayout = new FlowLayout(0, 15, 15);
	m_flowLayout->setContentsMargins(0, 20, 30, 0);

	m_scanning = new GridWidget(SCAN_SETTINGS, QSize(38,30));
	m_scanning->setTitleText("Scanning Settings");
	m_scanning->setSubTitleText("Universal AV, Engines, Antivirus Settings");
	m_scanning->setObjectName("scanSettings");

	m_protectionMode = new GridWidget(PROTECTION_MODE, QSize(28,30));
	m_protectionMode->setTitleText("Protection Mode");
	m_protectionMode->setSubTitleText("Automatic. Interactive, Lock Down, Trust All modes");
	m_protectionMode->setObjectName("protectionMode");

	m_languagePersonal = new GridWidget(LANGUAGE_PERSIONAL, QSize(38,30));
	m_languagePersonal->setTitleText("Language & Personalization");
	m_languagePersonal->setSubTitleText("Language, Themes, Notification");
	m_languagePersonal->setObjectName("languagePersonal");

	m_diagnosis = new GridWidget(DIAGNOSIS,QSize(30,30));
	m_diagnosis->setTitleText("Diagnosis");
	m_diagnosis->setSubTitleText("Send log and dump files to server");
	m_diagnosis->setObjectName("diagnosis");	
	
	m_managementServer = new GridWidget(MANAGEMENT_SERVER, QSize(35,30));
	m_managementServer->setTitleText("Management Server");
	m_managementServer->setSubTitleText("Retrieve and Implement Policy");
	m_managementServer->setObjectName("managementServer");

	m_security = new GridWidget(SECURITY, QSize(30,30));
	m_security->setTitleText("Security");
	m_security->setSubTitleText("Password Protection");
	m_security->setObjectName("security");

	m_updates = new GridWidget(UPDATE, QSize(30,30));
	m_updates->setTitleText("Updates");
	m_updates->setSubTitleText("Software and APEX updates");
	m_updates->setObjectName("updates");

	m_flowLayout->addWidget(m_scanning);
	m_flowLayout->addWidget(m_protectionMode);
	m_flowLayout->addWidget(m_languagePersonal);
	m_flowLayout->addWidget(m_diagnosis);
	m_flowLayout->addWidget(m_managementServer);
	m_flowLayout->addWidget(m_security);
	m_flowLayout->addWidget(m_updates);

	setLayout(m_flowLayout);

	setConnection();
}

SettingGridContent::~SettingGridContent()
{
}

void SettingGridContent::setConnection()
{
	connect(m_scanning, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_protectionMode, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_languagePersonal, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_diagnosis, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_managementServer, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_security, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_updates, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
}

void SettingGridContent::widgetPressed()
{
	QString senderName = sender()->objectName();
	emit gridWidgetPressed(senderName);
}