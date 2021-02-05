#include "commandlineruletable.h"

CommandLineRuleTable::CommandLineRuleTable(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

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

	m_process = new QLabel();
	//m_process->setFixedSize(105,36);
	m_process->setFixedHeight( 36);
	m_process->setMinimumWidth( 135);
	m_process->setFont(FONT);
	m_process->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_process->setText("PROCESS");

	m_caseSensitiveCbb = new SAPTableCombobox(35);
	m_caseSensitiveCbb->setFixedSize(120, 36);
	m_caseSensitiveCbb->setEditable(true);

	m_caseSensitiveCbb->addItem("All");
	m_caseSensitiveCbb->addItem("Yes");
	m_caseSensitiveCbb->addItem("No");
	m_caseSensitiveCbb->setCurrentText("CASE SENSITIVE");

	m_caseSensitiveEdt = new QLineEdit();
	m_caseSensitiveEdt->setFixedWidth(85);
	m_caseSensitiveEdt->setReadOnly(true);
	m_caseSensitiveCbb->setLineEdit(m_caseSensitiveEdt);

	m_string = new QLabel();
	m_string->setFixedSize(80, 36);
	m_string->setFont(FONT);
	m_string->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_string->setText("STRING");

	m_rulesCbb = new SAPTableCombobox(70);
	m_rulesCbb->setFixedSize(105, 36);
	m_rulesCbb->setEditable(true);

	m_rulesCbb->addItem("All");
	m_rulesCbb->addItem("Exactly Match");
	m_rulesCbb->addItem("Starts with");
	m_rulesCbb->addItem("Contains");
	m_rulesCbb->setCurrentText("RULES");

	m_rulesEdt = new QLineEdit();
	m_rulesEdt->setFixedWidth(35);
	m_rulesEdt->setReadOnly(true);
	m_rulesCbb->setLineEdit(m_rulesEdt);

	m_actionsCbb = new SAPTableCombobox(90);
	m_actionsCbb->setFixedSize(135, 36);
	//m_actionsCbb->setFixedHeight( 36);
	//m_actionsCbb->setMinimumWidth( 135);
	m_actionsCbb->setEditable(true);

	m_actionsCbb->addItem("All");
	m_actionsCbb->addItem("Never trust permanently");
	m_actionsCbb->addItem("Let trusted userdecide");
	m_actionsCbb->addItem("Always block");
	m_actionsCbb->setCurrentText("ACTION");

	m_actionsEdt = new QLineEdit();
	m_actionsEdt->setFixedWidth(45);
	m_actionsEdt->setReadOnly(true);
	m_actionsCbb->setLineEdit(m_actionsEdt);

	titleLayout->addWidget(m_checkAllBox);
	titleLayout->addWidget(checkboxSpacer);
	titleLayout->addWidget(m_process);
	titleLayout->addWidget(m_caseSensitiveCbb);
	titleLayout->addWidget(m_string);
	titleLayout->addWidget(m_rulesCbb);
	titleLayout->addWidget(m_actionsCbb);
	//m_layout->addWidget(m_titleWg);

	//m_layout->addWidget(m_titleWg);

	QLabel* bottomSpacer = new QLabel();

	m_rowWg = new QWidget();
	m_rowLayout = new QVBoxLayout();
	m_rowLayout->setContentsMargins(0, 0, 0, 0);
	m_rowLayout->setSpacing(0);
	m_rowWg->setLayout(m_rowLayout);

	m_rowLayout->addWidget(m_titleWg);

	m_scrollView = new SAPSCrollArea(QMargins(5, 5, 0, 5));
	m_scrollView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
	m_scrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
	m_scrollView->verticalScrollBar()->setVisible(false);
	m_scrollView->setWidget(m_rowWg);

	m_layout->addWidget(m_scrollView);

	m_layout->addWidget(bottomSpacer);

	transparent = new WidgetTransparent();
	//m_copyCommandLineDlg = new CopyCommandLineDialog();

	setLayout(m_layout);
	setStyle();

	m_rowCount = 0;
	connect(m_caseSensitiveCbb, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxChangeIndex(int)));
	connect(m_rulesCbb, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxChangeIndex(int)));
	connect(m_actionsCbb, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxChangeIndex(int)));
}

CommandLineRuleTable::~CommandLineRuleTable()
{
}

void CommandLineRuleTable::allCheckBoxSetCheck(Qt::CheckState)
{
}

void CommandLineRuleTable::rowCheckBoxSetCheck(Qt::CheckState)
{
}

void CommandLineRuleTable::comboboxChangeIndex(int index)
{
	auto sender = this->sender();

	if (sender == m_caseSensitiveCbb)
	{
		m_caseSensitiveCbb->setEditText("CASE SENSITIVE");

	}
	else if (sender == m_rulesCbb)
	{
		m_rulesCbb->setEditText("RULES");
	}
	else if (sender == m_actionsCbb)
	{
		m_actionsCbb->setEditText("ACTION");
	}
}

void CommandLineRuleTable::AddCommandLineRule(CommandLineRuleString & commandLine)
{
}

void CommandLineRuleTable::AddCommandLineRuleFromDialog(CommandLineRuleString & commandLine)
{
}

void CommandLineRuleTable::removeRows()
{
}

void CommandLineRuleTable::resetToDefault()
{
}

void CommandLineRuleTable::resizeEvent(QResizeEvent * event)
{
	qDebug() << m_titleWg->size() << this->size();
	auto width = m_scrollView->size().width();
	if (width > 600)
	{
		m_titleWg->resize(width, 36);
		m_rowWg->resize(m_scrollView->width(), m_rowWg->height());

	}
	else
	{
		m_titleWg->resize(600, 36);
		m_rowWg->resize(600, m_rowWg->height());
	}
}

void CommandLineRuleTable::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_titleWg->setStyleSheet("background-color:#C9C9C9;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_process->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		m_string->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_process->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		m_string->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		break;

	default:
		break;
	}
}
void CommandLineRuleTable::setRowStyle(CommandLineRuleRow * row)
{
}
Button_Check_State CommandLineRuleTable::buttonCheckState()
{
	return Button_Check_State();
}
void CommandLineRuleTable::setCheckBoxsState()
{
}
void CommandLineRuleTable::changeTheme()
{

}