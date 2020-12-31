#include "search.h"

SearchButton::SearchButton(QWidget* parent)
	: QPushButton(parent)
{
	setFixedSize(16, 16);
	setStyleSheet("QPushButton {border: 0px;}");
	initIcon();
	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SearchButton::changeTheme);
}

SearchButton::~SearchButton() {};

void SearchButton::enterEvent(QEvent*)
{
	setIconSize(QSize(14, 14));
	setCursor(Qt::PointingHandCursor);
}

void SearchButton::leaveEvent(QEvent*)
{
	setIconSize(QSize(16, 16));
}

void SearchButton::initIcon()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		icon = util::getInstance()->ChangeSVGColor(SCAN_ICON_PATH, TAB_CONTENT_DESC_TEXT_LT);
		break;

	case Theme_Type::Dark_Theme:
		icon = util::getInstance()->ChangeSVGColor(SCAN_ICON_PATH, TAB_CONTENT_DESC_TEXT_DT);

		break;

		//MORE THEME
	default:
		break;
	}

	setIcon(icon);
	setIconSize(QSize(16, 16));
}

void SearchButton::changeTheme()
{
	initIcon();
}

Search::Search(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedHeight(32);

	m_searchWg = new QWidget();
	m_searchWg->setFixedHeight(32);

	QHBoxLayout* searchLayout = new QHBoxLayout();
	searchLayout->setContentsMargins(20, 0, 0, 0);
	searchLayout->setSpacing(0);
	m_searchWg->setLayout(searchLayout);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	m_searchButton = new SearchButton();

	QLabel *centerSpacer = new QLabel();
	centerSpacer->setFixedWidth(10);

	m_searchLabel = new QLineEdit(this);
	m_searchLabel->setFont(SMALL_FONT);
	m_searchLabel->setFixedHeight(32);

	m_searchLabel->setPlaceholderText("Search file");
	QStringList wordList;
	wordList.append("Uninstall_Service.cmd");
	wordList.append("Uninstall_Service1.cmd");
	wordList.append("Uninstall_Service2.cmd");
	wordList.append("kmspico-setup.exe");
	m_wordList.setStringList(wordList);
	completer = new QCompleter(this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setModel(&m_wordList);

	m_searchLabel->setCompleter(completer);



	searchLayout->addWidget(m_searchButton);
	searchLayout->addWidget(centerSpacer);
	searchLayout->addWidget(m_searchLabel);
	m_layout->addWidget(m_searchWg);

	setLayout(m_layout);

	setStyle();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &Search::changeTheme);
}


Search::~Search()
{
}

void Search::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_searchWg->setStyleSheet("background-color:#FFFFFF;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_searchLabel->setStyleSheet("QLineEdit{color:#727272; border:none;}");
		completer->popup()->setStyleSheet("background-color:#FFFFFF; border:none;"
			"selection-background-color: #055598;"
			"color: #727272;"
			"outline: 1px solid #055598;"
			"padding-left:10px;"
			"}");
		break;

	case Theme_Type::Dark_Theme:
		m_searchWg->setStyleSheet("background-color:#253653;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_searchLabel->setStyleSheet("color:#667286; border:none;"); 
		completer->popup()->setStyleSheet("background-color:#253653; border:none;"
			"selection-background-color: #19C2E8;"
			"color: #667286;"
			"outline: 1px solid #19C2E8;"
			"padding-left:10px;"
			"}");
		break;

		//MORE THEME
	default:
		break;
	}

}
void Search::changeTheme()
{
	setStyle();
}
