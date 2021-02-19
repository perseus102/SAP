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

	QFontMetrics fm(FONT);
	int pixelsHigh = fm.height();

	QWidget* processWg = new QWidget();
	processWg->setFixedHeight(36);
	processWg->setMinimumWidth(120);

	QHBoxLayout* processLayout = new QHBoxLayout();
	processLayout->setContentsMargins(0, 0, 0, 0);
	processLayout->setSpacing(6);
	processWg->setLayout(processLayout);

	m_process = new QLabel();
	int processWidth = fm.width("PROCESS");
	m_process->setFixedSize(processWidth, 36);
	m_process->setFont(FONT);
	m_process->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_process->setText("PROCESS");

	m_sortProcessBtn = new QPushButton();
	m_sortProcessBtn->setFixedSize(6, 4);
	m_processSortUp = false;

	setSortBtnStyle(m_sortProcessBtn);

	QLabel* processSpacer = new QLabel();

	processLayout->addWidget(m_process);
	processLayout->addWidget(m_sortProcessBtn);
	processLayout->addWidget(processSpacer);

	////////////////////

	QWidget* paramWg = new QWidget();
	paramWg->setFixedSize(305, 36);

	QHBoxLayout* paramLayout = new QHBoxLayout();
	paramLayout->setContentsMargins(0, 0, 0, 0);
	paramLayout->setSpacing(6);
	paramWg->setLayout(paramLayout);

	m_parameters = new QLabel();
	int paramWidth = fm.width("PARAMETERS");
	m_parameters->setFixedSize(paramWidth, 36);
	m_parameters->setText("PARAMETERS");
	m_parameters->setFont(FONT);
	m_parameters->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	m_sortparamBtn = new QPushButton();
	m_sortparamBtn->setFixedSize(6, 4);
	m_paramSortUp = false;

	setSortBtnStyle(m_sortparamBtn);

	QLabel* paramSpacer = new QLabel();

	paramLayout->addWidget(m_parameters);
	paramLayout->addWidget(m_sortparamBtn);
	paramLayout->addWidget(paramSpacer);

	//////////////////////////////

	m_action = new QLabel();
	m_action->setFixedSize(160, 36);
	m_action->setText("ACTION");
	m_action->setFont(FONT);
	m_action->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	titleLayout->addWidget(m_checkAllBox);
	titleLayout->addWidget(checkboxSpacer);
	titleLayout->addWidget(processWg);
	titleLayout->addWidget(paramWg);
	titleLayout->addWidget(m_action);

	QLabel* bottomSpacer = new QLabel();

	m_rowWg = new QWidget();
	m_rowLayout = new QVBoxLayout();
	m_rowLayout->setContentsMargins(0, 0, 0, 0);
	m_rowLayout->setSpacing(0);
	m_rowWg->setLayout(m_rowLayout);

	m_titleScroll = new SAPSCrollArea(QMargins(5, 5, 0, 5));
	m_titleScroll->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	m_titleScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	m_titleScroll->setFixedHeight(36);
	m_titleScroll->setWidget(m_titleWg);

	m_scrollView = new SAPSCrollArea(QMargins(5, 5, 0, 5));
	m_scrollView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
	m_scrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
	m_scrollView->verticalScrollBar()->setVisible(false);
	m_scrollView->setWidget(m_rowWg);

	m_layout->addWidget(m_titleScroll);
	m_layout->addWidget(m_scrollView);

	m_layout->addWidget(bottomSpacer);

	transparent = new WidgetTransparent();
	//m_copyCommandLineDlg = new CopyCommandLineDialog();

	setLayout(m_layout);
	setStyle();

	m_rowCount = 0;


	CommandLineRuleString cmdStr;
	cmdStr.processStr = "powershell.exe";
	cmdStr.ruleStr = "Exactly match";
	cmdStr.caseSensitiveStr = "Case sensitive";
	cmdStr.string = "javascript;";
	cmdStr.actionStr = "Let trusted userdecide.";
	for (int a = 1; a <= 10; a++)
	{
		AddCommandLineRule(cmdStr);
		m_defaultList.append(cmdStr);
	}
	connect(m_sortProcessBtn, &QPushButton::clicked, this, &CommandLineRuleTable::sortBtnClicked);
	connect(m_sortparamBtn, &QPushButton::clicked, this, &CommandLineRuleTable::sortBtnClicked);
	connect(m_scrollView->horizontalScrollBar(), &QScrollBar::valueChanged, this, &CommandLineRuleTable::scrollbarChangeValue);
	connect(m_checkAllBox, &SAPCheckBox::boxSetChecked, this, &CommandLineRuleTable::allCheckBoxSetCheck);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CommandLineRuleTable::changeTheme);

	emit m_scrollView->verticalScrollBar()->valueChanged(m_scrollView->verticalScrollBar()->value());
}

CommandLineRuleTable::~CommandLineRuleTable()
{
}

CommandLineRuleString CommandLineRuleTable::getEditCmdLineRuleInfo()
{
	CommandLineRuleString cmdRuleStr;

	for (auto& row : m_commandLineRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			cmdRuleStr.processStr = row->process->text();
			cmdRuleStr.ruleStr = row->rule->text();
			cmdRuleStr.caseSensitiveStr = row->caseSensitive->text();
			cmdRuleStr.string = row->string->text();
			cmdRuleStr.actionStr = row->action->text();
			break;
		}
	}
	return cmdRuleStr;
}

void CommandLineRuleTable::allCheckBoxSetCheck(Qt::CheckState state)
{
	if (state == Qt::Checked)
	{
		for (auto& row : m_commandLineRowMap)
		{
			if (row->rowWg->isVisible())
			{
				row->checkBox->setButtonChecked(Qt::Checked);
			}
		}
		if (m_commandLineRowMap.count() == 1)
		{
			emit setEditBtnDisabled(false);
		}

		emit setRemoveBtnDisabled(false);
	}
	else
	{
		for (auto& row : m_commandLineRowMap)
		{
			if (row->rowWg->isVisible())
			{
				row->checkBox->setButtonChecked(Qt::Unchecked);
			}
		}
		emit setRemoveBtnDisabled(true);
		emit setEditBtnDisabled(true);
	}
}

void CommandLineRuleTable::rowCheckBoxSetCheck(Qt::CheckState)
{
	setCheckBoxsState();
}


void CommandLineRuleTable::sortBtnClicked()
{
	auto sender = this->sender();

	if (sender == m_sortProcessBtn)
	{
		m_processSortUp = !m_processSortUp;
	}
	else
	{
		m_paramSortUp = !m_paramSortUp;
	}
	setSortBtnStyle((QPushButton*)sender);

}

void CommandLineRuleTable::scrollbarChangeValue(int value)
{
	m_titleScroll->horizontalScrollBar()->setValue(value);
}

void CommandLineRuleTable::AddCommandLineRule(CommandLineRuleString & commandLineRule)
{
	CommandLineRuleRow* row = new CommandLineRuleRow();

	row->rowWg = new QWidget();
	row->rowWg->setFixedHeight(36);

	QHBoxLayout* rowLayout = new QHBoxLayout();
	rowLayout->setContentsMargins(20, 0, 0, 0);
	rowLayout->setSpacing(0);

	row->rowWg->setLayout(rowLayout);

	row->checkBox = new SAPCheckBox();
	row->checkBox->setFixedSize(18, 36);
	row->checkBox->setButtonChecked(Qt::Unchecked);
		
	QLabel* centerSpacer = new QLabel();
	centerSpacer->setFixedWidth(12);

	row->process = new QLabel();
	row->process->setFixedHeight(36);
	row->process->setFont(FONT);
	row->process->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->process->setText(commandLineRule.processStr);
	row->process->setWordWrap(true);
	row->process->setToolTip(commandLineRule.processStr);
	row->process->setMinimumWidth(120);

	row->rule = new QLabel();
	row->rule->setFixedSize(105,36);
	row->rule->setFont(FONT);
	row->rule->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->rule->setText(commandLineRule.ruleStr);
	row->rule->setToolTip(commandLineRule.ruleStr);

	row->caseSensitive = new QLabel();
	row->caseSensitive->setFixedSize(120, 36);
	row->caseSensitive->setFont(FONT);
	row->caseSensitive->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->caseSensitive->setText(commandLineRule.caseSensitiveStr);
	row->caseSensitive->setWordWrap(true);
	row->caseSensitive->setToolTip(commandLineRule.caseSensitiveStr);


	row->string = new QLabel();
	row->string->setFixedSize(80, 36);
	row->string->setFont(FONT);
	row->string->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->string->setText(commandLineRule.string);
	row->string->setWordWrap(true);
	row->string->setToolTip(commandLineRule.string);


	row->action = new QLabel();
	row->action->setFixedSize(160, 36);
	row->action->setFont(FONT);
	row->action->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->action->setText(commandLineRule.actionStr);
	row->action->setWordWrap(true);
	row->action->setToolTip(commandLineRule.actionStr);

	row->line = new QLabel();
	row->line->setFixedHeight(2);

	rowLayout->addWidget(row->checkBox);
	rowLayout->addWidget(centerSpacer);
	rowLayout->addWidget(row->process);
	rowLayout->addWidget(row->rule);
	rowLayout->addWidget(row->caseSensitive);
	rowLayout->addWidget(row->string);
	rowLayout->addWidget(row->action);

	setRowStyle(row);

	m_rowLayout->addWidget(row->rowWg);
	m_rowLayout->addWidget(row->line);

	m_rowCount++;

	m_commandLineRowMap.append(row);

	m_rowWg->resize(this->width(), (38 * m_rowCount));

	connect(row->checkBox, &SAPCheckBox::boxSetChecked, this, &CommandLineRuleTable::rowCheckBoxSetCheck);

}

void CommandLineRuleTable::AddCommandLineRuleFromDialog(CommandLineRuleString  commandLine)
{
	AddCommandLineRule(commandLine);

	auto width = m_scrollView->size().width();
	if (width > 640)
	{
		m_titleWg->resize(width, 36);
		m_rowWg->resize(m_scrollView->width(), (38 * m_rowCount));

	}
	else
	{
		m_titleWg->resize(640, 36);
		m_rowWg->resize(640, (38 * m_rowCount));
	}
}

void CommandLineRuleTable::editCommandLineRule(CommandLineRuleString commandLine)
{
	for (auto& row : m_commandLineRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			row->process->setText(commandLine.processStr);
			row->rule->setText(commandLine.ruleStr);
			row->caseSensitive->setText(commandLine.caseSensitiveStr);
			row->string->setText(commandLine.string);
			row->action->setText(commandLine.actionStr);
			break;
		}
	}
}

void CommandLineRuleTable::removeRows()
{
	QList<CommandLineRuleRow*> keyList;
	for (auto& row : m_commandLineRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			keyList.append(row);
			m_rowLayout->removeWidget(row->rowWg);
			m_rowLayout->removeWidget(row->line);
			row->rowWg->setParent(nullptr);
			row->line->setParent(nullptr);
			delete row->rowWg;
			delete row->line;
			m_rowCount--;

			QSize size = m_rowWg->size();
			m_rowWg->resize(this->width(), size.height() - 38 /* row height */);
		}
	}

	for (auto& key : keyList)
	{
		m_commandLineRowMap.removeOne(key);
	}

	if (m_commandLineRowMap.count() == 0) // remove all
	{
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
		emit setRemoveBtnDisabled(true);
		emit setEditBtnDisabled(true);
		return;
	}

	auto width = m_scrollView->size().width();
	if (width > 640)
	{
		m_titleWg->resize(width, 36);
		m_rowWg->resize(m_scrollView->width(), (38 * m_rowCount));

	}
	else
	{
		m_titleWg->resize(640, 36);
		m_rowWg->resize(640, (38 * m_rowCount));
	}

	setCheckBoxsState();
}

void CommandLineRuleTable::resetToDefault()
{
	QList<CommandLineRuleRow*> keyList;
	for (auto& row : m_commandLineRowMap)
	{
		keyList.append(row);
		m_rowLayout->removeWidget(row->rowWg);
		m_rowLayout->removeWidget(row->line);
		row->rowWg->setParent(nullptr);
		row->line->setParent(nullptr);
		delete row->rowWg;
		delete row->line;
		m_rowCount--;
		QSize size = m_rowWg->size();
		m_rowWg->resize(this->width(), size.height() - 38 /* row height */);
	}

	for (auto& key : keyList)
	{
		m_commandLineRowMap.removeOne(key);
	}
	for (auto& key : m_defaultList)
	{
		AddCommandLineRule(key);
	}

	auto width = m_scrollView->size().width();
	if (width > 640)
	{
		m_titleWg->resize(width, 36);
		m_rowWg->resize(m_scrollView->width(), (38 * m_rowCount));

	}
	else
	{
		m_titleWg->resize(640, 36);
		m_rowWg->resize(640, (38 * m_rowCount));
	}

	setCheckBoxsState();
}

void CommandLineRuleTable::resizeEvent(QResizeEvent * event)
{
	qDebug() << m_titleWg->size() << this->size();
	auto width = m_scrollView->size().width();
	if (width > 640)
	{
		m_titleWg->resize(width, 36);
		m_rowWg->resize(m_scrollView->width(), (38 * m_rowCount));

	}
	else
	{
		m_titleWg->resize(640, 36);
		m_rowWg->resize(640, (38 * m_rowCount));
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

		m_parameters->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		m_action->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_process->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		m_parameters->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		m_action->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		break;

	default:
		break;
	}
}
void CommandLineRuleTable::setRowStyle(CommandLineRuleRow * row)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		row->process->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->rule->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->caseSensitive->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->string->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->action->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		row->process->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		row->rule->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		row->caseSensitive->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		row->string->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		row->action->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		break;

	default:
		break;
	}

}
Button_Check_State CommandLineRuleTable::buttonCheckState()
{
	Button_Check_State checkState = Button_All_Unchecked;

	int countCheck = 0;

	for (auto& row : m_commandLineRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			countCheck++;
		}
	}

	if (countCheck == 1)
	{
		emit setEditBtnDisabled(false);
	}
	else if (countCheck > 1)
	{
		emit setEditBtnDisabled(true);
	}

	int rowCount = m_commandLineRowMap.count();

	if (rowCount == 0)
	{
		checkState = Button_All_Unchecked;
	}
	else if (countCheck == rowCount)
	{
		checkState = Button_All_Checked;
	}
	else if ((countCheck > 0) && (countCheck < rowCount))
	{
		checkState = Button_Checked;
	}
	else if (countCheck == 0)
	{
		checkState = Button_All_Unchecked;
	}

	return checkState;
}
void CommandLineRuleTable::setCheckBoxsState()
{
	Button_Check_State checkState = buttonCheckState();

	switch (checkState)
	{
	case Button_Checked:
		emit setRemoveBtnDisabled(false);
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
		break;
	case Button_All_Unchecked:
		emit setRemoveBtnDisabled(true);
		emit setEditBtnDisabled(true);
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
		break;

	case Button_All_Checked:
		emit setRemoveBtnDisabled(false);
		if (m_commandLineRowMap.count() > 1)
		{
			emit setEditBtnDisabled(true);
		}
		m_checkAllBox->setButtonChecked(Qt::Checked);
		break;
	default:
		break;
	}
}
void CommandLineRuleTable::setSortBtnStyle(QPushButton * btn)
{
	if (btn == nullptr) return;

	QIcon sortIcon;
	setStyleSheet("QPushButton {border: 0px;}");
	bool sortUp = btn == m_sortProcessBtn ? m_processSortUp : m_paramSortUp;

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if(!sortUp)
		{
			sortIcon = util::getInstance()->ChangeSVGColor(TALBE_SORT_DOWN_ICON_DT, "#A3AAB6");
		}
		else
		{
			sortIcon = util::getInstance()->ChangeSVGColor(TALBE_SORT_UP_ICON_DT, "#A3AAB6");
		}
		break;

	case Theme_Type::Dark_Theme:
		if (!sortUp)
		{
			sortIcon = util::getInstance()->ChangeSVGColor(TALBE_SORT_DOWN_ICON_DT, "#A3AAB6");
		}
		else
		{
			sortIcon = util::getInstance()->ChangeSVGColor(TALBE_SORT_UP_ICON_DT, "#A3AAB6");
		}

		break;

		//MORE THEME
	default:
		break;
	}

	btn->setIcon(sortIcon);
	btn->setIconSize(QSize(6, 4));

}

void CommandLineRuleTable::changeTheme()
{
	setStyle();

	for (auto& row : m_commandLineRowMap)
	{
		setRowStyle(row);
	}
}