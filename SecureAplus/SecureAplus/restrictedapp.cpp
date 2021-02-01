#include "restrictedapp.h"

RestrictedApp::RestrictedApp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 0, 30, 10);
	m_layout->setSpacing(0);

	m_description = new QLabel();
	m_description->setFixedHeight(60);
	m_description->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_description->setFont(FONT);
	m_description->setWordWrap(true);
	m_description->setText("The applications listed below may download, extract, or copy files from external sources such as internet or removable media that may potentially harm your system. Hence, any new executable files that are created by these applications will noy be automatically trusted.");

	QLabel* descSpacer = new QLabel();
	descSpacer->setFixedHeight(20);

	m_searchWg = new Search();

	QLabel* searchSpacer = new QLabel();
	searchSpacer->setFixedHeight(15);

	m_fileNameTable = new FileNameTable();
	//m_fileNameTable->setFixedHeight(250);

	QLabel* bottomTableSpacer = new QLabel();
	bottomTableSpacer->setFixedHeight(10);

	QWidget* bottomBtns = new QWidget();
	bottomBtns->setFixedHeight(30);
	QHBoxLayout* btnsLayout = new QHBoxLayout();
	btnsLayout->setContentsMargins(0, 0, 0, 0);
	btnsLayout->setSpacing(0);
	bottomBtns->setLayout(btnsLayout);

	m_resetToDefaultBtn = new ClickableLabel();
	m_resetToDefaultBtn->setFixedSize(100, 30);
	m_resetToDefaultBtn->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_resetToDefaultBtn->setFont(FONT);
	m_resetToDefaultBtn->setText("Reset to Defaults");

	QLabel* centerBtnsSpacer = new QLabel();
	
	m_removeBtn = new QPushButton();
	m_removeBtn->setFixedSize(80, 30);
	m_removeBtn->setFont(FONT);
	m_removeBtn->setText("Remove");
	m_removeBtn->setDisabled(true);

	QLabel* btnsSpacer = new QLabel();
	btnsSpacer->setFixedWidth(8);

	m_addBtn = new QPushButton();
	m_addBtn->setFixedSize(80, 30);
	m_addBtn->setFont(FONT);
	m_addBtn->setText("Add");

	btnsLayout->addWidget(m_resetToDefaultBtn);
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

	m_addResAppDialog = new AddResAppDialog();
	transparent = new WidgetTransparent();

	setLayout(m_layout);
	setStyle();

	connect(m_removeBtn, &QPushButton::clicked, m_fileNameTable, &FileNameTable::removeRows);
	connect(m_removeBtn, &QPushButton::clicked, this, &RestrictedApp::removeButtonClicked);

	connect(m_addBtn, &QPushButton::clicked, this, &RestrictedApp::addButtonClicked);

	connect(m_resetToDefaultBtn, &ClickableLabel::clicked, this, &RestrictedApp::resetToDefaultClicked);
	connect(m_resetToDefaultBtn, &ClickableLabel::clicked, m_fileNameTable, &FileNameTable::resetToDefault);

	connect(m_fileNameTable, &FileNameTable::addWord, m_searchWg, &Search::addWordList);
	connect(m_fileNameTable, &FileNameTable::removeWord, m_searchWg, &Search::removeWordList);

	connect(m_addResAppDialog, &AddResAppDialog::addFile, m_fileNameTable, &FileNameTable::AddFileNameFromDialog);

	connect(m_searchWg, &Search::updateFilter, m_fileNameTable, &FileNameTable::updateFilterRow);
	connect(m_searchWg, &Search::setFilter, m_fileNameTable, &FileNameTable::setFilterRow);

	connect(m_fileNameTable, &FileNameTable::setRemoveBtnDisabled, this, &RestrictedApp::setRemoveBtnDisabled);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &RestrictedApp::changeTheme);

	m_fileNameTable->AddFileName("7z.exe");
	m_fileNameTable->AddFileName("7zfm.exe");
	m_fileNameTable->AddFileName("7zg.exe");
	m_fileNameTable->AddFileName("ace32loader.exe");
	m_fileNameTable->AddFileName("browser.exe");
	m_fileNameTable->AddFileName("Chrome.exe");
	m_fileNameTable->AddFileName("explorer.exe");
	m_fileNameTable->AddFileName("firefox.exe");
	m_fileNameTable->AddFileName("goodsync.exe");
	m_fileNameTable->AddFileName("microsoftedge.exe");
	m_fileNameTable->AddFileName("microsoftedgecp.exe");
	m_fileNameTable->AddFileName("notepad++.exe");
	m_fileNameTable->AddFileName("onedrive.exe");
	m_fileNameTable->AddFileName("outlook.exe");
}

RestrictedApp::~RestrictedApp()
{
}
void RestrictedApp::removeButtonClicked()
{
	//qDebug() << "clicked";
}

void RestrictedApp::addButtonClicked()
{
	QRect geometry = AppSetting::getInstance()->getAppGeometry();

	transparent->showWidget();
	m_addResAppDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 190 /*190 is half width*/, geometry.y() + 16, 380, 170);
	m_addResAppDialog->showDialog();
	transparent->hide();
}

void RestrictedApp::resetToDefaultClicked()
{
	//do something
}

void RestrictedApp::changeTheme()
{
	setStyle();
}

void RestrictedApp::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);

}

void RestrictedApp::setRemoveBtnDisabled(bool disabled)
{
	m_removeBtn->setDisabled(disabled);
	setRemoveBtnStyle();
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
		
		m_resetToDefaultBtn->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		
		setRemoveBtnStyle();

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:
		m_description->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		
		m_resetToDefaultBtn->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		
		setRemoveBtnStyle();

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

void RestrictedApp::setRemoveBtnStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if (m_removeBtn->isEnabled())
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		}
		else
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:"+ TAB_CONTENT_BTN_BACKGROUND_DISABLED_LT +";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_LT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

	case Theme_Type::Dark_Theme:

		if (m_removeBtn->isEnabled())
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		}
		else
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_DT + ";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_DT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

		//MORE THEME
	default:
		break;
	}
}
