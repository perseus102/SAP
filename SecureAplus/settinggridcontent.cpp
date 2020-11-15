#include "settinggridcontent.h"

SettingGridContent::SettingGridContent(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_flowLayout = new FlowLayout(0, 15, 15);
	m_flowLayout->setContentsMargins(0, 20, 0, 0);

	m_scanning = new GridWidget();
	m_scanning->setTitleText("Scanning Settings");
	m_scanning->setSubTitleText("Universal AV, Engines, Antivirus Settings");
	m_scanning->setObjectName("scanning");

	m_allowList = new GridWidget();
	m_allowList->setTitleText("Application Allow List");
	m_allowList->setSubTitleText("Digital Signature Advanced, Command Line, Removable Device");
	m_allowList->setObjectName("allowList");

	m_vulnerability = new GridWidget();
	m_vulnerability->setTitleText("Vulnerability Assessment");
	m_vulnerability->setSubTitleText("Digital Signature Advanced, Command Line, Removable Device");
	m_vulnerability->setObjectName("vulnerability");

	m_protectionMode = new GridWidget();
	m_protectionMode->setTitleText("Protection Mode");
	m_protectionMode->setSubTitleText("Auto Protect, Lock Down, Trust All");
	m_protectionMode->setObjectName("protectionMode");

	m_info = new GridWidget();
	m_info->setTitleText("Info & Licenses");
	m_info->setSubTitleText();
	m_info->setObjectName("info");

	m_languagePersonal = new GridWidget();
	m_languagePersonal->setTitleText("Language & Personalization");
	m_languagePersonal->setSubTitleText();
	m_languagePersonal->setObjectName("languagePersonal");

	m_manageUser = new GridWidget();
	m_manageUser->setTitleText("Manage User Rights");
	m_manageUser->setSubTitleText();
	m_manageUser->setObjectName("manageUser");

	m_updates = new GridWidget();
	m_updates->setTitleText("Updates");
	m_updates->setSubTitleText();
	m_updates->setObjectName("updates");

	m_others = new GridWidget();
	m_others->setTitleText("Others");
	m_others->setSubTitleText();
	m_others->setObjectName("others");

	m_flowLayout->addWidget(m_scanning);
	m_flowLayout->addWidget(m_allowList);
	m_flowLayout->addWidget(m_vulnerability);
	m_flowLayout->addWidget(m_protectionMode);
	m_flowLayout->addWidget(m_info);
	m_flowLayout->addWidget(m_languagePersonal);
	m_flowLayout->addWidget(m_manageUser);
	m_flowLayout->addWidget(m_updates);
	m_flowLayout->addWidget(m_others);

	setLayout(m_flowLayout);

	setConnection();
}

SettingGridContent::~SettingGridContent()
{
}

void SettingGridContent::setConnection()
{
	connect(m_scanning, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_allowList, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_vulnerability, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_protectionMode, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_info, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_languagePersonal, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_manageUser, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_updates, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
	connect(m_others, &GridWidget::pressWidget, this, &SettingGridContent::widgetPressed);
}

void SettingGridContent::widgetPressed()
{
	QString senderName = sender()->objectName();
	emit gridWidgetPressed(senderName);
}