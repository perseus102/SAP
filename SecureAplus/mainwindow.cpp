#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSizePolicy>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent /*, Qt::FramelessWindowHint*/),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	ui->status_widget->setStyleSheet("background-color: #253653; border: 0px; border-top-right-radius: 40px;");
	//ui->home_wigdet->setStyleSheet("border-image:url(:/images/Rectangle.svg);");
	ui->scan_widget->setStyleSheet("background-color: #253653; ");
	ui->manager_widget->setStyleSheet("background-color: #253653; ");
	ui->setting_widget->setStyleSheet("background-color: #253653; ");
	ui->home_wigdet->setContentsMargins(0, 0, 0, 0);
	home_widget = new HomeWidget(ui->home_wigdet);
	//home_btn = new QPushButton();
	////button->setFlat(true);
	//home_btn->setAutoFillBackground(true);
	//home_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//home_btn->setText("button");
	//QVBoxLayout *boxlayout = new QVBoxLayout(ui->home_wigdet);
	//QLabel test;
	//test.setMinimumSize(20, 20);
	//test.setText("LABEL");
	////boxlayout->setContentsMargins(0, 0, 0, 0);
	//boxlayout->addWidget(home_btn);
	//boxlayout->addWidget(&test);
	//qDebug() << "button width" << home_btn->width() << "button height" << home_btn->height();
	//ui->home_wigdet->setLayout(boxlayout);
	//boxlayout->setContentsMargins(0, 0, 0, 0);

	
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::resizeEvent(QResizeEvent* event)
{
	qDebug() << "navi widget width " << ui->navi_widget->width();
	qDebug() << "navi widget height" << ui->navi_widget->height();
	QMainWindow::resizeEvent(event);
	// Your code here.

}

void MainWindow::home_btnClick()
{
	home_btn_Clicked = !home_btn_Clicked;
	qDebug() << "home button clicked";

	if(home_btn_Clicked)
	{ 
		home_btn->setStyleSheet("border-image:url(:/images/Rectangle.svg);");
	}
	else
	{
		home_btn->setStyleSheet("border-image:url(:/images/RectangleUnclicked.svg);");
	}
}
