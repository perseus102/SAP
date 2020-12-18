#include "managegridcontent.h"

ManageGridContent::ManageGridContent(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_flowLayout = new FlowLayout(0, 15, 15);
	m_flowLayout->setContentsMargins(0, 20, 30, 0);

	m_trustedGroups = new GridWidget(STRUCTED_GROUPS, QSize(46, 30));
	m_trustedGroups->setTitleText("Trusted Groups");
	m_trustedGroups->setSubTitleText("Manage Trusted Groups");
	m_trustedGroups->setObjectName("trustedGroups");

	m_trustedUsers = new GridWidget(STRUCTED_USERS, QSize(38, 30));
	m_trustedUsers->setTitleText("Trusted Users");
	m_trustedUsers->setSubTitleText("Manage Trusted Users");
	m_trustedUsers->setObjectName("trustedUsers");

	m_excInc = new GridWidget(EXC_INC, QSize(21, 30));
	m_excInc->setTitleText("Exclusions, Inclusions");
	//m_excInc->setSubTitleText("");
	m_excInc->setObjectName("excInc");

	m_appControl = new GridWidget(APP_CONTROL, QSize(38, 30));
	m_appControl->setTitleText("Application Control");
	m_appControl->setSubTitleText("Digital Signature, Allow List, Restricted Applications ...");
	m_appControl->setObjectName("appControl");

	m_removableDevices = new GridWidget(REMOVABLE_DEVICES, QSize(30, 30));
	m_removableDevices->setTitleText("Removable Devices");
	//m_removableDevices->setSubTitleText("");
	m_removableDevices->setObjectName("removableDevices");

	m_accountAndLicense = new GridWidget(ACCOUNT_LICENSE, QSize(23, 30));
	m_accountAndLicense->setTitleText("Account & License");
	m_accountAndLicense->setSubTitleText("SecureAgePlus ID, License Code");
	m_accountAndLicense->setObjectName("accountLicense");

	m_flowLayout->addWidget(m_trustedGroups);
	m_flowLayout->addWidget(m_trustedUsers);
	m_flowLayout->addWidget(m_excInc);
	m_flowLayout->addWidget(m_appControl);
	m_flowLayout->addWidget(m_removableDevices);
	m_flowLayout->addWidget(m_accountAndLicense);

	setLayout(m_flowLayout);

	setConnection();
}

ManageGridContent::~ManageGridContent()
{
}

void ManageGridContent::setConnection()
{
	connect(m_trustedGroups, &GridWidget::pressWidget, this, &ManageGridContent::widgetPressed);
	connect(m_trustedUsers, &GridWidget::pressWidget, this, &ManageGridContent::widgetPressed);
	connect(m_excInc, &GridWidget::pressWidget, this, &ManageGridContent::widgetPressed);
	connect(m_appControl, &GridWidget::pressWidget, this, &ManageGridContent::widgetPressed);
	connect(m_removableDevices, &GridWidget::pressWidget, this, &ManageGridContent::widgetPressed);
	connect(m_accountAndLicense, &GridWidget::pressWidget, this, &ManageGridContent::widgetPressed);
}

void ManageGridContent::widgetPressed()
{
	QString senderName = sender()->objectName();
	emit gridWidgetPressed(senderName);
}
