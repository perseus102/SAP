#include "scriptstable.h"

ScriptsTable::ScriptsTable(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setContentsMargins(0, 0, 0, 0);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	m_titleWg = new QWidget();
	m_titleWg->setFixedHeight(36);

	QHBoxLayout* titleLayout = new QHBoxLayout();
	titleLayout->setContentsMargins(20, 0, 0, 0);
	titleLayout->setSpacing(0);
	m_titleWg->setLayout(titleLayout);

	m_checkAllBox = new SAPCheckBox(true);
	m_checkAllBox->setFixedSize(18, 36);

	m_checkAllBox->setButtonChecked(Qt::Unchecked);

	QLabel* checkboxSpacer = new QLabel();
	checkboxSpacer->setFixedWidth(12);

	m_interpreter = new QLabel();
	m_interpreter->setFixedHeight(36);
	m_interpreter->setFont(FONT);
	m_interpreter->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_interpreter->setText("INTERPRETER");

	m_extensions = new QLabel();
	m_extensions->setFixedSize(250, 36);
	m_extensions->setFont(FONT);
	m_extensions->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_extensions->setText("EXTENSIONS");


	titleLayout->addWidget(m_checkAllBox);
	titleLayout->addWidget(checkboxSpacer);
	titleLayout->addWidget(m_interpreter);
	titleLayout->addWidget(m_extensions);

	m_layout->addWidget(m_titleWg);

	QLabel* bottomSpacer = new QLabel();

	m_rowWg = new QWidget();
	m_rowLayout = new QVBoxLayout();
	m_rowLayout->setContentsMargins(0, 0, 0, 0);
	m_rowLayout->setSpacing(0);
	m_rowWg->setLayout(m_rowLayout);

	m_scrollView = new SAPSCrollArea(QMargins(5, 5, 0, 5));
	m_scrollView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
	m_scrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	m_scrollView->verticalScrollBar()->setVisible(false);
	m_scrollView->setWidget(m_rowWg);

	m_layout->addWidget(m_scrollView);

	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);
	setStyle();

	m_rowCount = 0;
}

ScriptsTable::~ScriptsTable()
{
}

void ScriptsTable::allCheckBoxSetCheck(Qt::CheckState)
{
}

void ScriptsTable::scrollBarRangeChanged(int min, int max)
{
}

void ScriptsTable::rowCheckBoxSetCheck(Qt::CheckState)
{
}
void ScriptsTable::AddScriptsFromDialog(QString interpreter, QString extensions)
{
}

void ScriptsTable::AddScripts(QString interpreter, QString extensions)
{
}
void ScriptsTable::removeRows()
{
}
void ScriptsTable::resetToDefault()
{
}
void ScriptsTable::resizeEvent(QResizeEvent * event)
{
}
void ScriptsTable::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_titleWg->setStyleSheet("background-color:#C9C9C9;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_interpreter->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		m_extensions->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";"
			"padding-left:5px;}");
		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_interpreter->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
		m_extensions->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";"
			"padding-left:5px;}");

		break;

	default:
		break;
	}
}
void ScriptsTable::setRowStyle(ScriptsRow * row)
{
}
Button_Check_State ScriptsTable::buttonCheckState()
{
	return Button_Check_State();
}
void ScriptsTable::setCheckBoxsState()
{
}
void ScriptsTable::changeTheme()
{

}