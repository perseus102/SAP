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
	//setIconSize(QSize(14, 14));
	//setCursor(Qt::PointingHandCursor);
}

void SearchButton::leaveEvent(QEvent*)
{
	//setIconSize(QSize(16, 16));
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
	m_searchLabel->setFont(FONT);
	m_searchLabel->setFixedHeight(32);

	m_searchLabel->setPlaceholderText("Search file");
	
	//m_wordListModel.setStringList(m_wordList);
	//completer = new QCompleter(this);
	//completer->setCompletionMode(QCompleter::PopupCompletion);
	//completer->setModelSorting(QCompleter::UnsortedModel);
	//completer->setFilterMode(Qt::MatchStartsWith);
	//completer->setCaseSensitivity(Qt::CaseSensitive);

	//completer->setModel(&m_wordListModel);
	//m_searchLabel->setCompleter(completer);
	//completer->popup()->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	//completer->popup()->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

	searchLayout->addWidget(m_searchButton);
	searchLayout->addWidget(centerSpacer);
	searchLayout->addWidget(m_searchLabel);
	m_layout->addWidget(m_searchWg);
	setLayout(m_layout);

	setStyle();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &Search::changeTheme);
	connect(m_searchLabel, &QLineEdit::textChanged, this, &Search::updateWord);
}


Search::~Search()
{
}

void Search::updateWord(QString word)
{
	word == "" ? emit setFilter(false) : emit setFilter(true);
	
	int idx(0);
	QStringList tempList;
	QStringList c_m_list(m_wordList);

	while (idx < c_m_list.size())
	{
		if (c_m_list.at(idx).startsWith(word, Qt::CaseInsensitive))
		{
			tempList.append(c_m_list.takeAt(idx--));
		}
		idx++;
	}

	QStringList filtered = m_wordList.filter(word, Qt::CaseSensitivity::CaseSensitive);

	filtered.append(tempList);

	emit updateFilter(filtered);
}

void Search::addWordList(QString word)
{
	m_wordList.append(word);
	//m_wordListModel.setStringList(m_wordList);
	//completer->setModel(&m_wordListModel);
}

void Search::removeWordList(QString word)
{
	m_wordList.removeOne(word);
	//m_wordListModel.setStringList(m_wordList);
}

void Search::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_searchWg->setStyleSheet("background-color:" + SEARCH_BACKGROUND_LT + ";"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_searchLabel->setStyleSheet("QLineEdit{color:"+ TAB_CONTENT_DESC_TEXT_LT +";"
			"border:none;}");
		//completer->popup()->setStyleSheet("background-color:#FFFFFF; border:none;"
		//	"selection-background-color: #055598;"
		//	"color: #727272;"
		//	"outline: 1px solid #055598;"
		//	"padding-left:10px;"
		//	"}");
		break;

	case Theme_Type::Dark_Theme:
		m_searchWg->setStyleSheet("background-color:"+ SEARCH_BACKGROUND_DT +";"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_searchLabel->setStyleSheet("QLineEdit{color:" + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border:none;}");
		/*completer->popup()->setStyleSheet("background-color:#253653; border:none;"
			"selection-background-color: #19C2E8;"
			"color: #667286;"
			"outline: 1px solid #19C2E8;"
			"padding-left:10px;"

			);*/
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
