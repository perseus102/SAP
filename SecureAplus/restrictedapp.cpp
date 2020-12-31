#include "restrictedapp.h"

RestrictedApp::RestrictedApp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 0, 30, 0);
	m_layout->setSpacing(0);

	m_description = new QLabel();
	m_description->setFixedHeight(60);
	m_description->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_description->setFont(FONT);
	m_description->setWordWrap(true);

	QLabel* descSpacer = new QLabel();
	descSpacer->setFixedHeight(20);

	m_searchWg = new Search();

	QLabel* searchSpacer = new QLabel();
	searchSpacer->setFixedHeight(15);

	m_fileNameTable = new FileNameTable();
	m_fileNameTable->setFixedHeight(250);

	QLabel* bottomTableSpacer = new QLabel();
	bottomTableSpacer->setFixedHeight(10);

	QWidget* bottomBtns = new QWidget();
	bottomBtns->setFixedHeight(30);
	QHBoxLayout* btnsLayout = new QHBoxLayout();
	btnsLayout->setContentsMargins(0, 0, 0, 0);
	btnsLayout->setSpacing(0);
	bottomBtns->setLayout(btnsLayout);

	m_resetToDefault = new QLabel();
	m_resetToDefault->setFixedSize(100, 30);
	m_resetToDefault->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_resetToDefault->setFont(FONT);
	m_resetToDefault->setText("Reset to Defaults");

	QLabel* centerBtnsSpacer = new QLabel();
	
	m_removeBtn = new QPushButton();
	m_removeBtn->setFixedSize(80, 30);
	m_removeBtn->setFont(FONT);
	m_removeBtn->setText("Remove");

	QLabel* btnsSpacer = new QLabel();
	btnsSpacer->setFixedWidth(8);

	m_addBtn = new QPushButton();
	m_addBtn->setFixedSize(80, 30);
	m_addBtn->setFont(FONT);
	m_addBtn->setText("Add");

	btnsLayout->addWidget(m_resetToDefault);
	btnsLayout->addWidget(centerBtnsSpacer);
	btnsLayout->addWidget(m_removeBtn);
	btnsLayout->addWidget(btnsSpacer);
	btnsLayout->addWidget(m_addBtn);

	QLabel* bottomSpacer = new QLabel();
	
	m_layout->addWidget(m_description);
	m_layout->addWidget(descSpacer);
	m_layout->addWidget(m_searchWg);
	m_layout->addWidget(searchSpacer);
	m_layout->addWidget(m_fileNameTable);
	m_layout->addWidget(bottomTableSpacer);
	m_layout->addWidget(bottomBtns);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);

	m_description->setText("The applications listed below may download, extract, or copy files from external sources such as internet or removable media that may potentially harm your system. Hence, any new executable files that are created by these applications will noy be automatically trusted.");

	setStyle();

}

RestrictedApp::~RestrictedApp()
{
}
void RestrictedApp::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);

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
		m_description->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		
		m_resetToDefault->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_description->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		
		m_resetToDefault->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		break;

		//MORE THEME
	default:
		break;
	}
}
