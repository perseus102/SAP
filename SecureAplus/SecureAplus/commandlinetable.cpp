#include "commandlinetable.h"
#include "threadpopulateallowedcommandline.h"
#include "AppControl.h"
#include "hash.h"
#include "utf8.h"
#include "log.h"
#include "CmdLineRules.h"
#include "WhitelistCmdLine.h"

BOOLEAN callback_add_allowed_cmdline(LPVOID lpContext, PWHITELIST_KEY pKey, PWHITELIST_DATA pData, ULONGLONG pos, ULONGLONG max)
{
	PPARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE param = (PPARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE)lpContext;
	CommandLineTable* t = (CommandLineTable*)param->callback_parent_obj;
	char* keyword = "|cmd|";
	int keyword_length = strlen(keyword);
	LPWSTR cmdlineW;
	BOOLEAN bContinue = WaitForSingleObject(param->hStopEvent, 0) != 0;

	if (bContinue && pData->trust_level != 0 && strncmp(pKey->filename, keyword, keyword_length) == 0)
	{
		BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE];
		size_t length;

		length = strlen(pKey->filename + strlen(keyword));
		if (pKey->filesize == length)
		{
			HashMemoryV2(pKey->filename + strlen(keyword), length, hash_whole_file);
			if (memcmp(hash_whole_file, pKey->hash_whole_file, APPWHITELISTING_HASH_SIZE) == 0)
			{
				cmdlineW = utf8_to_wchar(pKey->filename + keyword_length);
				if (cmdlineW)
				{
					t->AddCertificateGUIOnly(cmdlineW);
					free(cmdlineW);
				}
			}
			else
			{
				write_log(L"### Wrong hash command line: %S", pKey->filename);
			}
		}
		else
		{
			write_log(L"### Wrong length command line: %S", pKey->filename);
		}
	}
	return bContinue;
}

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

	transparent = new WidgetTransparent();
	m_copyCommandLineDlg = new CopyCommandLineDialog();

	setLayout(m_layout);
	setStyle();

	m_rowCount = 0;

	connect(m_checkAllBox, &SAPCheckBox::boxSetChecked, this, &CommandLineTable::allCheckBoxSetCheck);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CommandLineTable::changeTheme);
	//connect(m_scrollView->verticalScrollBar(), &QScrollBar::valueChanged, this, &CommandLineTable::scrollbarChangeValue);
	//connect(m_scrollView->verticalScrollBar(), &QScrollBar::rangeChanged, this, &CommandLineTable::scrollBarRangeChanged);
	
	connect(m_copyCommandLineDlg, &CopyCommandLineDialog::copyToClipBoard, this, &CommandLineTable::copyCmdLineToClipBoard);

	/*QString rowString;

	for (int a = 1; a <= 10; a++)
	{
		rowString += "Command Line" + QString::number(a) + " ";
		AddCommandLine(rowString);
		m_defaultList.append(rowString);
	}*/
	m_timerRefresh = new QTimer(this);
	if (m_timerRefresh)
	{
		connect(m_timerRefresh, SIGNAL(timeout()), this, SLOT(refresh()));
	}
	hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hCompletedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hThread = NULL;
	InitializeCriticalSection(&m_cs);

	emit m_scrollView->verticalScrollBar()->valueChanged(m_scrollView->verticalScrollBar()->value());
}

CommandLineTable::~CommandLineTable()
{
	if (hThread)
	{
		if (hStopEvent) SetEvent(hStopEvent);
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		hThread = NULL;
	}
	if (m_timerRefresh) delete m_timerRefresh;
	DeleteCriticalSection(&m_cs);
}

void CommandLineTable::loadData(BOOLEAN force)
{
	if (force && hThread && WaitForSingleObject(hCompletedEvent, 0) == 0)
	{
		// previously loaded data successfully
		// reset all state-tracking objects involved in loadData()
		if (hCompletedEvent) ResetEvent(hCompletedEvent);
		CloseHandle(hThread);
		hThread = NULL;
	}
	if (!hThread)
	{
		hThread = CreateThreadPopulateAllowedCommandLine(this, callback_add_allowed_cmdline, hStopEvent, hCompletedEvent);
		m_timerRefresh->start(500);
	}
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

void CommandLineTable::AddCertificateGUIOnly(LPCWSTR cmdline)
{
	EnterCriticalSection(&m_cs);
	m_incomingData.push_back(QString::fromWCharArray(cmdline));
	LeaveCriticalSection(&m_cs);
}

void CommandLineTable::AddCommandLine(QString& commandLine)
{
	DWORD dwLastError = 0;
	BOOLEAN bCaseInsensitive = FALSE;

	if (is_parameter_match_command_line_rules(commandLine.toStdWString().c_str(), &bCaseInsensitive))
	{
		if (bCaseInsensitive)
		{
			commandLine = commandLine.toLower();
		}
	}
	dwLastError = set_cmd_line_trust_level(commandLine.toStdWString().c_str(), 1);
	if (dwLastError != 0)
	{
		// TODO: display error, when add fails
		return;
	}

	EnterCriticalSection(&m_cs);
	m_incomingData.push_back(commandLine);
	LeaveCriticalSection(&m_cs);
}

void CommandLineTable::AddCommandLineFromDialog(QString& commandLine)
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
	refresh();
}

void CommandLineTable::removeRows()
{
	DWORD dwLastError = 0;
	QList<CommandLineRow*> keyList;
	std::wstring cmdline;
	for (auto& row : m_commandLineRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			cmdline = row->commandLine->text().toStdWString();
			dwLastError = set_cmd_line_trust_level(cmdline.c_str(), 0);
			if (dwLastError != 0)
			{
				// TODO: display error when remove() fails
				break;
			}

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

	for (auto& row : m_commandLineRowMap)
	{
		bool isRow1 = true;
		fullTextWidth = fm.width(row->commandLine->toolTip());
		labelWidth = (m_rowWg->width() - 20/*margin*/ - 18/*checkbox*/ - 12/*spacer*/ - 90);
		defaultCharsNum = 55;
		threeDotSize = fm.width("..."); // ... => 12px

		do
		{
			if (isRow1)
			{
				commandLine = row->commandLine->toolTip();
			}

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

void CommandLineTable::refresh()
{

	if (TryEnterCriticalSection(&m_cs))
	{
		for (auto commandLine : m_incomingData)
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

			row->copyBtn = new CopyButton();
			row->copyBtn->setFixedSize(18, 18);
			btnLayout->addWidget(row->copyBtn);
			row->copyBtn->setObjectName(QString::number(m_rowCount));

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
				//resizeRow.append(row);
			}

			connect(row->checkBox, &SAPCheckBox::boxSetChecked, this, &CommandLineTable::rowCheckBoxSetCheck);
			connect(row->copyBtn, &CopyButton::clicked, this, &CommandLineTable::copyBtnClicked);
		}

		if (hCompletedEvent)
		{
			if (WaitForSingleObject(hCompletedEvent, 0) == 0)
			{
				//Completed
				if (m_timerRefresh) m_timerRefresh->stop();

				// TODO: enable/activate "Reset to default" label here
			}
		}

		m_incomingData.clear();
		LeaveCriticalSection(&m_cs);
	}
}

void CommandLineTable::copyBtnClicked()
{
	auto sender = this->sender();
	QString commandLine;
	for (auto& row : m_commandLineRowMap)
		if (sender == row->copyBtn)
		{
			commandLine = row->commandLine->toolTip();
			break;
		}
	QRect geometry = AppSetting::getInstance()->getAppGeometry();
	transparent->showWidget();
	m_copyCommandLineDlg->setGeometry(geometry.x() + (geometry.width() / 2) - 190 /*190 is half width*/, geometry.y() + 16, 380, 244);
	m_copyCommandLineDlg->showDialog(commandLine);
	transparent->hide();
}

void CommandLineTable::copyCmdLineToClipBoard(QString commandLine)
{
	QApplication::clipboard()->setText(commandLine);
}
