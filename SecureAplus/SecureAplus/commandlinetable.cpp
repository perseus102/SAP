#include "commandlinetable.h"

CommandLineTable::CommandLineTable(QWidget *parent)
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

	m_commandLine = new QLabel();
	m_commandLine->setFixedHeight(36);
	m_commandLine->setFont(FONT);
	m_commandLine->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_commandLine->setText("COMMAND LINE");	
	
	m_action = new QLabel();
	m_action->setFixedSize(90,36);
	m_action->setFont(FONT);
	m_action->setAlignment(Qt::AlignCenter);
	m_action->setText("ACTION");

	titleLayout->addWidget(m_checkAllBox);
	titleLayout->addWidget(checkboxSpacer);
	titleLayout->addWidget(m_commandLine);
	titleLayout->addWidget(m_action);

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

	connect(m_checkAllBox, &SAPCheckBox::boxSetChecked, this, &CommandLineTable::allCheckBoxSetCheck);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CommandLineTable::changeTheme);
	//connect(m_scrollView->verticalScrollBar(), &QScrollBar::valueChanged, this, &CommandLineTable::scrollbarChangeValue);
	//connect(m_scrollView->verticalScrollBar(), &QScrollBar::rangeChanged, this, &CommandLineTable::scrollBarRangeChanged);
	
	QString rowString;

	for (int a = 1; a <= 10; a++)
	{
		rowString = "c:\\windows\\system32\\windowspowercell\\v1.0\\powercell.exe - execution policy unrestricted - noninteractive - noprofile" + QString::number(a) + " ";
		AddCommandLine(rowString);
		m_defaultList.append(rowString);
	}

	emit m_scrollView->verticalScrollBar()->valueChanged(m_scrollView->verticalScrollBar()->value());
}

CommandLineTable::~CommandLineTable()
{
}

void CommandLineTable::changeTheme()
{
	setStyle();

	for (auto& row : m_commandLineRowMap)
	{
		setRowStyle(row);
	}
}

void CommandLineTable::allCheckBoxSetCheck(Qt::CheckState state)
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
	}
}

void CommandLineTable::scrollBarRangeChanged(int min, int max)
{
	Q_UNUSED(min);
	Q_UNUSED(max);
	if (m_rowWg->height() > m_scrollView->height())
	{
		emit m_scrollView->verticalScrollBar()->valueChanged(m_scrollView->verticalScrollBar()->value());
	}
}

void CommandLineTable::rowCheckBoxSetCheck(Qt::CheckState)
{
	setCheckBoxsState();
}

void CommandLineTable::scrollbarChangeValue(int value)
{
	//resizeLabel();
}

void CommandLineTable::AddCommandLine(QString commandLine)
{
	CommandLineRow* row = new CommandLineRow();

	row->rowWg = new QWidget();
	row->rowWg->setFixedHeight(50);

	QHBoxLayout* rowLayout = new QHBoxLayout();
	rowLayout->setContentsMargins(20, 0, 0, 0);
	rowLayout->setSpacing(0);

	row->rowWg->setLayout(rowLayout);

	row->checkBox = new SAPCheckBox();
	row->checkBox->setFixedSize(18, 36);
	row->checkBox->setButtonChecked(Qt::Unchecked);

	QLabel* centerSpacer = new QLabel();
	centerSpacer->setFixedWidth(12);

	row->commandLine = new QLabel();
	row->commandLine->setFixedHeight(30);
	row->commandLine->setFont(FONT);
	row->commandLine->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->commandLine->setText(commandLine);
	row->commandLine->setWordWrap(true);
	row->commandLine->setToolTip(commandLine);

	QWidget* btnWg = new QWidget();
	btnWg->setFixedSize(90, 50);

	QHBoxLayout*  btnLayout = new QHBoxLayout();
	btnLayout->setContentsMargins(0, 0, 0, 0);
	btnLayout->setSpacing(0);
	btnWg->setLayout(btnLayout);

	row->copyBtn = new QPushButton();
	row->copyBtn->setFixedSize(18, 18);
	btnLayout->addWidget(row->copyBtn);

	row->line = new QLabel();
	row->line->setFixedHeight(2);

	rowLayout->addWidget(row->checkBox);
	rowLayout->addWidget(centerSpacer);
	rowLayout->addWidget(row->commandLine);
	rowLayout->addWidget(btnWg);

	setRowStyle(row);

	m_rowLayout->addWidget(row->rowWg);
	m_rowLayout->addWidget(row->line);

	m_rowCount++;

	m_commandLineRowMap.append(row);

	m_rowWg->resize(this->width(), (52 * m_rowCount));

	int labelWidth, commandLineWidth;
	QFontMetrics fm(FONT);

	labelWidth = (m_rowWg->width() - 20/*margin*/ - 18/*checkbox*/ - 12/*spacer*/);
	commandLineWidth = fm.width(commandLine);

	if (commandLineWidth > labelWidth)
	{
		resizeRow.append(row);
	}

	connect(row->checkBox, &SAPCheckBox::boxSetChecked, this, &CommandLineTable::rowCheckBoxSetCheck);
}

void CommandLineTable::AddCommandLineFromDialog(QString commandLine)
{
	int cout = -1;

	for (auto& row : m_commandLineRowMap)
	{
		cout++;

		if (row->commandLine->text() == commandLine)
		{
			QWidget* wg = m_rowLayout->itemAt(cout * 2)->widget();
			m_scrollView->ensureWidgetVisible(wg, 150, 150);
			return;
		}
	}

	AddCommandLine(commandLine);

}

void CommandLineTable::removeRows()
{
	QList<CommandLineRow*> keyList;
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
			m_rowWg->resize(this->width(), size.height() - 52 /* row height */);
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
		return;
	}

	setCheckBoxsState();
}

void CommandLineTable::resetToDefault()
{
	QList<CommandLineRow*> keyList;
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
		m_rowWg->resize(this->width(), size.height() - 52 /* row height */);
	}

	for (auto& key : keyList)
	{
		m_commandLineRowMap.removeOne(key);
	}
	for (auto& key : m_defaultList)
	{
		AddCommandLine(key);
	}

	setCheckBoxsState();

	resizeLabel();
}

void CommandLineTable::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event);
	m_rowWg->resize(m_scrollView->width(), m_rowWg->height());

	resizeLabel();
}

void CommandLineTable::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_titleWg->setStyleSheet("background-color:#C9C9C9;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_commandLine->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		
		m_action->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_commandLine->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
		
		m_action->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		break;

	default:
		break;
	}

}

void CommandLineTable::setRowStyle(CommandLineRow * row)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		row->commandLine->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		row->commandLine->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		break;

	default:
		break;
	}
}

Button_Check_State CommandLineTable::buttonCheckState()
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

void CommandLineTable::setCheckBoxsState()
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
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
		break;

	case Button_All_Checked:
		emit setRemoveBtnDisabled(false);
		m_checkAllBox->setButtonChecked(Qt::Checked);
		break;
	default:
		break;
	}
}

void CommandLineTable::resizeLabel()
{


	int fullTextWidth, labelWidth, defaultCharsNum, threeDotSize, textWidth, nextCharWidth, remainSpace;
	QFontMetrics fm(FONT);

	QString commandLine, commandLineRow1, commandLineRow2;
	bool isRow1 = true;

	for (auto& row : m_commandLineRowMap)
	{

		fullTextWidth = fm.width(row->commandLine->toolTip());
		labelWidth = (m_rowWg->width() - 20/*margin*/ - 18/*checkbox*/ - 12/*spacer*/ - 90);
		defaultCharsNum = 55;  
		threeDotSize = fm.width("..."); // ... => 12px

		do
		{
			if(isRow1) commandLine = row->commandLine->toolTip();

			if (!isRow1)
			{
				fullTextWidth = fm.width(commandLine);
			}

			if (isRow1)
			{
				if ((fullTextWidth <= labelWidth))
				{
					row->commandLine->setText(commandLine);
					break;
				}
			}
			else
			{
				if ((fullTextWidth <= labelWidth))
				{
					row->commandLine->setText(commandLineRow1 + commandLine);
					break;
				}
			}

			textWidth = fm.width(commandLine.mid(0, defaultCharsNum));
			nextCharWidth = fm.width(commandLine.mid(defaultCharsNum, 1));

			if (isRow1)
			{
				remainSpace = (labelWidth - textWidth);
			}
			else
			{
				remainSpace = (labelWidth - (textWidth + threeDotSize));

			}

			if (remainSpace > nextCharWidth)
			{
				defaultCharsNum++;
				continue;
			}

			if (isRow1)
			{
				if (textWidth <= labelWidth)
				{

					commandLineRow1 = commandLine.mid(0, defaultCharsNum) + "\n";
					commandLine = commandLine.mid(defaultCharsNum, commandLine.length() - 1);
					isRow1 = false;
					defaultCharsNum = 55;
					//commandLine = commandLine.mid(0, defaultCharsNum) + "...";
					//row->commandLine->setText(commandLine);
					//break;
				}
			}
			else
			{
				if ((textWidth + threeDotSize) <= labelWidth)
				{
					commandLineRow2 = commandLine.mid(0, defaultCharsNum) + "...";
					row->commandLine->setText(commandLineRow1 + commandLineRow2);
					break;
				}
			}

			defaultCharsNum--;

		} while (true);
	}
}
