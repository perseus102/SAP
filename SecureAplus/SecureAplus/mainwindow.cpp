#include "stdafx.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQuickView>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent /*, Qt::FramelessWindowHint*/),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	m_statusWidget		= new StatusWidget(ui->status_widget);
	m_homeWidget		= new HomeWidget(ui->home_widget);
	m_scanWidget		= new ScanWidget(ui->scan_widget);
	m_manageWidget		= new ManageWidget(ui->manage_widget);
	m_SettingWidget		= new SettingWidget(ui->setting_widget);

	m_homeContent		= new HomeContent;
	firstPageWidget		= new QWidget;
	secondPageWidget	= new QWidget;
	m_settingContent	= new SettingsContent;
	m_manageContent		= new ManageContent;

	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget(m_homeContent);

	stackedWidget->addWidget(firstPageWidget);
	stackedWidget->addWidget(secondPageWidget);
	stackedWidget->addWidget(m_manageContent);
	stackedWidget->addWidget(m_settingContent);

	ActiveWidget = m_homeWidget;

	setConnection();
	changeBackground();

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(stackedWidget);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	ui->main_widget->setLayout(layout);

}


void MainWindow::setConnection()
{
	/* Connect for active widget */
	connect(m_homeWidget, &HomeWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(m_scanWidget, &ScanWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(m_manageWidget, &ManageWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(m_SettingWidget, &SettingWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &MainWindow::changeBackground);
	connect(AppSetting::getInstance(), &AppSetting::signal_ChangeScreen, this, &MainWindow::changeScreenView);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);
	// Your code here.
}

void MainWindow::switchActiveWidget()
{
	/*switch widget*/
	if (sender() == m_homeWidget)
	{

		stackedWidget->setCurrentWidget(m_homeContent);

	}
	QRect rect;
	if (sender() == m_scanWidget)
	{
		stackedWidget->setCurrentWidget(secondPageWidget);
	}

	if (sender() == m_manageWidget)
	{
		stackedWidget->setCurrentWidget(m_manageContent);

	}
	if (sender() == m_SettingWidget)
	{
		stackedWidget->setCurrentWidget(m_settingContent);
	}

	/* set change status for current widget */
	if (ActiveWidget == m_statusWidget)
	{
		//do something
	}
	else if (ActiveWidget == m_homeWidget)
	{
		m_homeWidget->setSelected(false);
		m_homeWidget->setWidgetStyle();

	}
	else if (ActiveWidget == m_scanWidget)
	{
		m_scanWidget->setSelected(false);
		m_scanWidget->setWidgetStyle();


	}
	else if (ActiveWidget == m_manageWidget)
	{
		m_manageWidget->setSelected(false);
		m_manageWidget->setWidgetStyle();


	}
	else if (ActiveWidget == m_SettingWidget)
	{
		m_SettingWidget->setSelected(false);
		m_SettingWidget->setWidgetStyle();
	}

	ActiveWidget = sender();

}

void MainWindow::changeBackground()
{
	if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
	{
		ui->main_widget->setStyleSheet(
			"#main_widget{border: 0px none palette(shadow); "
			"border-top-left-radius:10px;"
			"background-color:" + MAIN_BACKGROUND_LIGHT_THEME_COLOR + ";}");
		
	}
	else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
	{
		ui->main_widget->setStyleSheet(
			"#main_widget{border: 0px none palette(shadow); "
			"border-top-left-radius:10px;"
			"background-color:" + MAIN_BACKGROUND_DARK_THEME_COLOR + ";}");
	}
}

void MainWindow::changeScreenView(Screen screen)
{
	if (ActiveWidget == m_statusWidget)
	{
		//do something
	}
	else if (ActiveWidget == m_homeWidget)
	{
		m_homeWidget->setSelected(false);
		m_homeWidget->setWidgetStyle();

	}
	else if (ActiveWidget == m_scanWidget)
	{
		m_scanWidget->setSelected(false);
		m_scanWidget->setWidgetStyle();


	}
	else if (ActiveWidget == m_manageWidget)
	{
		m_manageWidget->setSelected(false);
		m_manageWidget->setWidgetStyle();


	}
	else if (ActiveWidget == m_SettingWidget)
	{
		m_SettingWidget->setSelected(false);
		m_SettingWidget->setWidgetStyle();
	}

	switch (screen)
	{
	case Screen_None:
		break;
	case License_Screen:
		break;
	case Antivirus_Tab:
		m_SettingWidget->setSelected(true);
		m_SettingWidget->setWidgetStyle();
		ActiveWidget = m_SettingWidget;
		stackedWidget->setCurrentWidget(m_settingContent);
		m_settingContent->changeToAntivirusTab();
		break;
	default:
		break;
	}
}


