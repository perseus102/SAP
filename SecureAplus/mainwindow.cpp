#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQuickView>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent /*, Qt::FramelessWindowHint*/),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	m_statusWidget = new StatusWidget(ui->status_widget);
	m_homeWidget = new HomeWidget(ui->home_widget);
	m_scanWidget = new ScanWidget(ui->scan_widget);
	m_manageWidget = new ManageWidget(ui->manage_widget);
	m_SettingWidget = new SettingWidget(ui->setting_widget);

	ActiveWidget = m_homeWidget;
	setConnection();
	changeBackground();
	//QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
	//windowShadow->setBlurRadius(9.0);
	//windowShadow->setColor(QColor(0, 0, 0));
	//windowShadow->setOffset(0.0);
	//ui->main_widget->setGraphicsEffect(windowShadow);

	homeContent = new HomeContent;
	firstPageWidget = new QWidget;
	secondPageWidget = new QWidget;
	thirdPageWidget = new QWidget;
	
	//homeContent->setStyleSheet("background-color:black");
	firstPageWidget->setStyleSheet("background-color:black");
	secondPageWidget->setStyleSheet("background-color:green");
	thirdPageWidget->setStyleSheet("background-color:blue");
	
	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget(homeContent);
	stackedWidget->addWidget(firstPageWidget);
	stackedWidget->addWidget(secondPageWidget);
	stackedWidget->addWidget(thirdPageWidget);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(stackedWidget);

	ui->main_widget->setLayout(layout);

}


void MainWindow::setConnection()
{
	/* Connect for active widget */
	connect(m_statusWidget, &StatusWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(m_homeWidget, &HomeWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(m_scanWidget, &ScanWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(m_manageWidget, &ManageWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(m_SettingWidget, &SettingWidget::setActive, this, &MainWindow::switchActiveWidget);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &MainWindow::changeBackground);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);
	// Your code here.
}

void MainWindow::switchActiveWidget()
{
	if (sender() == m_homeWidget)
	{
		qDebug() << "ui->main_widget->x " << ui->main_widget->x();
		qDebug() << "ui->main_widget->y " << ui->main_widget->y();
		qDebug() << "ui->main_widget->height() " << ui->main_widget->height();
		qDebug() << "ui->main_widget->width()" << ui->main_widget->width();


		//QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
		//firstPageWidget->setGraphicsEffect(eff);
		//QPropertyAnimation *a = new QPropertyAnimation(eff, "opacity");
		//a->setDuration(300);
		//a->setStartValue(0);
		//a->setEndValue(1);
		//a->start(QPropertyAnimation::DeleteWhenStopped);
		stackedWidget->setCurrentWidget(homeContent);

	}

	if (sender() == m_scanWidget)
	{
		qDebug() << "ui->main_widget->x " << ui->main_widget->x();
		qDebug() << "ui->main_widget->y " << ui->main_widget->y();
		qDebug() << "ui->main_widget->height() " << ui->main_widget->height();
		qDebug() << "ui->main_widget->width()" << ui->main_widget->width();


		//QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
		//secondPageWidget->setGraphicsEffect(eff);
		//QPropertyAnimation *a = new QPropertyAnimation(eff, "opacity");
		//a->setDuration(300);
		//a->setStartValue(0);
		//a->setEndValue(1);
		//a->start(QPropertyAnimation::DeleteWhenStopped);
		stackedWidget->setCurrentWidget(secondPageWidget);

	}

	if (sender() == m_manageWidget)
	{
		qDebug() << "ui->main_widget->x " << ui->main_widget->x();
		qDebug() << "ui->main_widget->y " << ui->main_widget->y();
		qDebug() << "ui->main_widget->height() " << ui->main_widget->height();
		qDebug() << "ui->main_widget->width()" << ui->main_widget->width();


		//QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
		//thirdPageWidget->setGraphicsEffect(eff);
		//QPropertyAnimation *a = new QPropertyAnimation(eff, "opacity");
		//a->setDuration(150);
		//a->setStartValue(0);
		//a->setEndValue(1);
		//a->start(QPropertyAnimation::DeleteWhenStopped);
		stackedWidget->setCurrentWidget(thirdPageWidget);

	}






	if (ActiveWidget == m_statusWidget)
	{
		
	}
	else if (ActiveWidget == m_homeWidget)
	{
		m_homeWidget->setSelected(false);
		m_homeWidget->changeStatus();

	}
	else if (ActiveWidget == m_scanWidget)
	{
		m_scanWidget->setSelected(false);
		m_scanWidget->changeStatus();


	}
	else if (ActiveWidget == m_manageWidget)
	{
		m_manageWidget->setSelected(false);
		m_manageWidget->changeStatus();


	}
	else if (ActiveWidget == m_SettingWidget)
	{
		m_SettingWidget->setSelected(false);
		m_SettingWidget->changeStatus();
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
			"background-color:" + BTN_BACKGROUND_LIGHT + ";}");
		
	}
	else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
	{
		ui->main_widget->setStyleSheet(
			"#main_widget{border: 0px none palette(shadow); "
			"border-top-left-radius:10px;"
			"background-color:" + BTN_BACKGROUND_DARK + ";}");
	}
}


