#include "homewidget.h"
#include <qDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
HomeWidget::HomeWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QPushButton *home_btn = new QPushButton();
	//button->setFlat(true);
	home_btn->setAutoFillBackground(true);
	home_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	home_btn->setText("button");
	QVBoxLayout *boxlayout = new QVBoxLayout(this);
	QLabel test;
	test.setMinimumSize(20, 20);
	test.setText("LABEL");
	//boxlayout->setContentsMargins(0, 0, 0, 0);
	boxlayout->addWidget(home_btn);
	boxlayout->addWidget(&test);
	qDebug() << "button width" << home_btn->width() << "button height" << home_btn->height();
	this->setLayout(boxlayout);
	boxlayout->setContentsMargins(0, 0, 0, 0);
}

HomeWidget::~HomeWidget()
{
}

void HomeWidget::mousePressEvent(QMouseEvent * event)
{
	qDebug() << "mouse press";
}
