#include "managecontent.h"

ManageContent::ManageContent(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_manageTopBar = new TopBar();
	m_manageTopBar->setVisibleNaviButton(false);
	m_manageTopBar->addDir("Manage", Directory::Manage); //Can use for multi language
	m_curManageDir = Directory::Manage;

	stackedWidget = new QStackedWidget();
	m_manageLayout = new QVBoxLayout;
	m_manageLayout->setContentsMargins(30, 20, 0, 0);
	m_manageLayout->setSpacing(0);
	m_manageLayout->addWidget(m_manageTopBar);
	m_manageLayout->addWidget(stackedWidget);

	m_manageGridContent = new ManageGridContent();

	stackedWidget->addWidget(m_manageGridContent);

	setLayout(m_manageLayout);

	/* Init Fade In*/
	eff = new QGraphicsOpacityEffect(this);
	this->setGraphicsEffect(eff);
	mpFadeIn = new QPropertyAnimation(eff, "opacity");
	mpFadeIn->setDuration(300);
	mpFadeIn->setStartValue(0);
	mpFadeIn->setEndValue(1);
	connect(mpFadeIn, SIGNAL(finished()), this, SLOT(onFadeInFinished()));

	connect(m_manageGridContent, &ManageGridContent::gridWidgetPressed, this, &ManageContent::changeManageView);

	connect(m_manageTopBar->getButton(), &QPushButton::clicked, this, &ManageContent::backBtnPressed);

	connect(m_manageTopBar, &TopBar::labelDirClicked, this, &ManageContent::directoryClicked);

	setStyleSheet("#HomeContent{border: 0px none palette(shadow); "
		"border-top-left-radius:10px;}");

}

ManageContent::~ManageContent()
{
}

void ManageContent::fadeIn()
{
	eff->setEnabled(true);
	mpFadeIn->start();
}

void ManageContent::onFadeInFinished()
{
	eff->setEnabled(false);
}

void ManageContent::changeManageView(QString widgetName)
{
	if (widgetName == "trustedGroups")
	{

	}
	else if (widgetName == "trustedUsers")
	{

	}
	else if (widgetName == "excInc")
	{

	}
	else if (widgetName == "appControl")
	{

	}
	else if (widgetName == "removableDevices")
	{

	}
	else if (widgetName == "accountLicense")
	{

	}
}

void ManageContent::backBtnPressed()
{
	switch (m_curManageDir)
	{
	case Manage:
		break;
	default:
		break;
	}

	fadeIn();
}

void ManageContent::directoryClicked(Directory dir)
{
	switch (dir)
	{
	case Manage:
		if (m_curManageDir == Directory::Manage)
			return;

		stackedWidget->setCurrentWidget(m_manageGridContent);
		m_curManageDir = Directory::Manage;
		m_manageTopBar->setVisibleNaviButton(false);

		break;
	default:
		break;
	}

	fadeIn();
}
