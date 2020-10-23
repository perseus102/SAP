#include "homecontent.h"
#include <qDebug>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>

HomeContent::HomeContent(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::HomeContent)
{
	ui->setupUi(this);


	/*m_homeIcon = new QLabel();
	m_homeIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	m_homeIcon->setStyleSheet("QLabel { background-color : grey; color : blue; }");
	m_homeText = new QLabel();
	m_homeText->setFont(FONT);
	m_homeText->setAlignment(Qt::AlignCenter);
	m_homeText->setStyleSheet("QLabel { background-color : blue; color : blue; }");

	m_homeLayout = new QVBoxLayout(this);
	m_homeLayout->setSpacing(0);
	m_homeLayout->setContentsMargins(0, 0, 0, 0);
	m_homeLayout->addWidget(m_homeIcon);
	m_homeLayout->addWidget(m_homeText);
	setLayout(m_homeLayout);*/

	eff = new QGraphicsOpacityEffect(this);
	this->setGraphicsEffect(eff);
	mpFadeIn = new QPropertyAnimation(eff, "opacity");
	mpFadeIn->setDuration(300);
	mpFadeIn->setStartValue(0);
	mpFadeIn->setEndValue(1);
	connect(mpFadeIn, SIGNAL(finished()), this, SLOT(onFadeInFinished()));



	firstPageWidget = new QWidget;
	secondPageWidget = new QWidget;
	thirdPageWidget = new QWidget;

	firstPageWidget->setStyleSheet("background-color:green");
	secondPageWidget->setStyleSheet("background-color:black");
	thirdPageWidget->setStyleSheet("background-color:red");

	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget(firstPageWidget);
	stackedWidget->addWidget(secondPageWidget);
	stackedWidget->addWidget(thirdPageWidget);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(stackedWidget);

	setLayout(layout);
	stackedWidget->setCurrentWidget(thirdPageWidget);
}

HomeContent::~HomeContent()
{
}

void HomeContent::onFadeInFinished()
{
	qDebug() << "onFadeInFinished";
	eff->setEnabled(false);
}

void HomeContent::fadeIn()
{
	eff->setEnabled(true);
	mpFadeIn->start();
}

void HomeContent::showEvent(QShowEvent *)
{

}

void HomeContent::resizeEvent(QResizeEvent *)
{

}
