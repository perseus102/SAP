#include "settingscontent.h"

#include <QScrollArea>

SettingsContent::SettingsContent(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::SettingsContent)
{
	ui->setupUi(this);
	m_settingTopBar = new TopBar();
	m_settingTopBar->setVisibleNaviButton(false);
	m_settingTopBar->setDirectoryText("Settings");
	stackedWidget = new QStackedWidget();

	m_settingLayout = new QVBoxLayout;
	m_settingLayout->setContentsMargins(20, 20, 20, 0);
	m_settingLayout->setSpacing(0);
	m_settingLayout->addWidget(m_settingTopBar);
	m_settingLayout->addWidget(stackedWidget);

	QWidget *SettingsContent = new QWidget();
	QGridLayout *grid = new QGridLayout;
	GridWidget *Grid1 = new GridWidget();
	GridWidget *Grid2 = new GridWidget();
	GridWidget *Grid3 = new GridWidget();
	GridWidget *Grid4 = new GridWidget();
	GridWidget *Grid5 = new GridWidget();
	GridWidget *Grid6 = new GridWidget();
	GridWidget *Grid7 = new GridWidget();
	GridWidget *Grid8 = new GridWidget();
	GridWidget *Grid9 = new GridWidget();
	grid->addWidget(Grid1,0,0);
	grid->addWidget(Grid2,0,1);
	grid->addWidget(Grid3,0,2);
	grid->addWidget(Grid4,1,0);
	grid->addWidget(Grid5,1,1);
	grid->addWidget(Grid6,1,2);
	grid->addWidget(Grid7,2,0);
	grid->addWidget(Grid8,2, 1);
	SettingsContent->setMaximumHeight(538);
	SettingsContent->setMaximumWidth(620);
	
	SettingsContent->setLayout(grid);
	stackedWidget->addWidget(SettingsContent);
	setLayout(m_settingLayout);

	/* Init Fade In*/
	eff = new QGraphicsOpacityEffect(this);
	this->setGraphicsEffect(eff);
	mpFadeIn = new QPropertyAnimation(eff, "opacity");
	mpFadeIn->setDuration(300);
	mpFadeIn->setStartValue(0);
	mpFadeIn->setEndValue(1);
	connect(mpFadeIn, SIGNAL(finished()), this, SLOT(onFadeInFinished()));

	setStyleSheet("#HomeContent{border: 0px none palette(shadow); "
		"border-top-left-radius:10px;}");
}

SettingsContent::~SettingsContent()
{
}

void SettingsContent::fadeIn()
{
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