#include "restrictedapp.h"

RestrictedApp::RestrictedApp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 0, 30, 0);
	m_layout->setSpacing(0);

	m_description = new QLabel();
	//m_statusTextLabel->setFixedWidth(264);
	m_description->setFixedHeight(60);
	m_description->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_description->setFont(FONT);
	m_description->setWordWrap(true);

	QLabel* descSpacer = new QLabel();
	descSpacer->setFixedHeight(20);

	m_searchWg = new Search();

	QLabel* bottomSpacer = new QLabel();
	
	m_layout->addWidget(m_description);
	m_layout->addWidget(descSpacer);
	m_layout->addWidget(m_searchWg);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);

	m_description->setText("The applications listed below may download, extract, or copy files from external sources such as internet or removable media that may potentially harm your system. Hence, any new executable files that are created by these applications will noy be automatically trusted.");

	setStyle();
}

RestrictedApp::~RestrictedApp()
{
}

void RestrictedApp::setDescText(QString text)
{
	m_description->setText(text);
}

void RestrictedApp::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_description->setStyleSheet("QLabel{ color:#7A7A7A;}");
		break;

	case Theme_Type::Dark_Theme:
		m_description->setStyleSheet("QLabel{ color:#A2A6AC;}");


		break;

		//MORE THEME
	default:
		break;
	}
}
