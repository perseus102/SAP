#include "homecontent.h"

HomeContent::HomeContent(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::HomeContent)
{
	ui->setupUi(this);

	m_homeMainContent	= new HomeMainContent();
	m_featureDetails	= new FeatureDetails();
	stackedWidget		= new QStackedWidget();

	stackedWidget->addWidget(m_homeMainContent);
	stackedWidget->addWidget(m_featureDetails);

	/* Init home content layout */
	m_homeContentLayout = new QVBoxLayout;
	m_homeContentLayout->setContentsMargins(0, 0, 0, 0);
	m_homeContentLayout->setSpacing(0);
	m_homeContentLayout->addWidget(stackedWidget);

	/* Set widget layout */
	setLayout(m_homeContentLayout);


	/* Init Fade In*/
	eff = new QGraphicsOpacityEffect(this);
	this->setGraphicsEffect(eff);
	mpFadeIn = new QPropertyAnimation(eff, "opacity");
	mpFadeIn->setDuration(300);
	mpFadeIn->setStartValue(0);
	mpFadeIn->setEndValue(1);
	connect(mpFadeIn, SIGNAL(finished()), this, SLOT(onFadeInFinished()));

	/* Set style for home main widget */
	setStyleSheet("#HomeContent{border: 0px none palette(shadow); "
		"border-top-left-radius:10px;}");


	connect(m_homeMainContent, &HomeMainContent::featureDetailsClicked, this, &HomeContent::showDetails);
}

HomeContent::~HomeContent()
{
}

void HomeContent::onFadeInFinished()
{
	/* Disable effect */
	eff->setEnabled(false);
}

void HomeContent::fadeIn()
{

}

void HomeContent::showDetails()
{
	stackedWidget->setCurrentWidget(m_featureDetails);
}

void HomeContent::showEvent(QShowEvent *)
{
	/* When widget paint set eff true and start animation */
	eff->setEnabled(true);
	mpFadeIn->start();
}

void HomeContent::resizeEvent(QResizeEvent *)
{

}
