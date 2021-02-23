#include "scriptstable.h"
#include "threadpopulatescript.h"
#include "NamedPipeSecureAPlusAdminSettings.h"
#include "scripts.h"

BOOLEAN callback_add_scripts(void* lpContext, LPCWSTR interpreter, LPCWSTR extensions)
{
	ScriptsTable* t = (ScriptsTable*)lpContext;
	t->AddScriptsGUIOnly(interpreter, extensions);
	return TRUE;
}

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

	connect(m_checkAllBox, &SAPCheckBox::boxSetChecked, this, &ScriptsTable::allCheckBoxSetCheck);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ScriptsTable::changeTheme);
	ScriptsString rowString;
	/*for (int a = 1; a <= 10; a++)
	{
		rowString.interpreter += "Scripts.exe" + QString::number(a) + " ";
		rowString.extensions = ".js|.jse|.vbe|.vbs|.wsc|.wsf|.wsh";
		AddScripts(rowString.interpreter, rowString.extensions);
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
}

ScriptsTable::~ScriptsTable()
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

void ScriptsTable::loadData(BOOLEAN force)
{
	if (force && hThread && WaitForSingleObject(hCompletedEvent, 0) == 0)
	{
		// previously loaded data successfully
		// reset all state-tracking objects involved in loadData()
		if (hCompletedEvent) SetEvent(hCompletedEvent);
		CloseHandle(hThread);
		hThread = NULL;
	}
	if (!hThread)
	{
		hThread = CreateThreadPopulateScript(this, callback_add_scripts, hStopEvent, hCompletedEvent);
		m_timerRefresh->start(500);
	}
}

void ScriptsTable::allCheckBoxSetCheck(Qt::CheckState state)
{
	if (state == Qt::Checked)
	{
		for (auto& row : m_scriptsRowMap)
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
		for (auto& row : m_scriptsRowMap)
		{
			if (row->rowWg->isVisible())
			{
				row->checkBox->setButtonChecked(Qt::Unchecked);
			}
		}
		emit setRemoveBtnDisabled(true);
	}
}

void ScriptsTable::scrollBarRangeChanged(int min, int max)
{
	Q_UNUSED(min);
	Q_UNUSED(max);
	if (m_rowWg->height() > m_scrollView->height())
	{
		emit m_scrollView->verticalScrollBar()->valueChanged(m_scrollView->verticalScrollBar()->value());
	}
}

void ScriptsTable::rowCheckBoxSetCheck(Qt::CheckState)
{
	setCheckBoxsState();
}

void ScriptsTable::AddScriptsFromDialog(QString &interpreter, QString &extensions)
{
	int cout = -1;

	for (auto& row : m_scriptsRowMap)
	{
		cout++;

		if (row->interpreter->text() == interpreter)
		{
			QWidget* wg = m_rowLayout->itemAt(cout * 2)->widget();
			m_scrollView->ensureWidgetVisible(wg, 150, 150);
			return;
		}
	}

	AddScripts(interpreter, extensions);
	refresh();
}

void ScriptsTable::AddScriptsGUIOnly(LPCWSTR interpreter, LPCWSTR extensions)
{
	EnterCriticalSection(&m_cs);
	m_incomingData.push_back(std::make_pair(QString::fromWCharArray(interpreter), QString::fromWCharArray(extensions)));
	LeaveCriticalSection(&m_cs);
}

void ScriptsTable::AddScripts(QString &interpreter, QString &extensions)
{
	DWORD dwLastError = 0;
	std::wstring interpreterW, extensionsW;

	interpreterW = interpreter.toStdWString();
	extensionsW = extensions.toStdWString();
	dwLastError = SecureaplusAdminSettingsAddScript(interpreterW.c_str(), extensionsW.c_str());
	if (dwLastError != 0)
	{
		// TODO: display error, when add fails
		return;
	}

	EnterCriticalSection(&m_cs);
	m_incomingData.push_back(std::make_pair(interpreter, extensions));
	LeaveCriticalSection(&m_cs);
}

void ScriptsTable::removeRows()
{
	DWORD dwLastError = 0;
	QList<ScriptsRow*> keyList;
	for (auto& row : m_scriptsRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			dwLastError = SecureaplusAdminSettingsDeleteScript(row->interpreter->text().toStdWString().c_str());
			if (dwLastError != 0)
			{
				// TODO: display error, when remove fails
				// Beware that this error display code can be called multiple times in this for loop!
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
		m_scriptsRowMap.removeOne(key);
	}

	if (m_scriptsRowMap.count() == 0) // remove all
	{
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
		emit setRemoveBtnDisabled(true);
		return;

	}

	setCheckBoxsState();
}
void ScriptsTable::resetToDefault()
{
	DWORD dwLastError = 0;
	QList<ScriptsRow*> keyList;

	// TODO: disable/deactivate "Reset to default" label here

	// restore defaults in backend
	dwLastError = SecureaplusAdminSettingsRestoreDefaultScript();
	if (dwLastError)
	{
		// TODO: display error, when reset to default fails 
		return;
	}

	// de-populate all rows in GUI
	for (auto& row : m_scriptsRowMap)
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
		m_scriptsRowMap.removeOne(key);
	}
	setCheckBoxsState();
	resizeLabel();

	// re-populate all rows in GUI
	loadData(TRUE);
}

void ScriptsTable::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event);
	m_rowWg->resize(m_scrollView->width(), m_rowWg->height());

	resizeLabel();
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
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		row->interpreter->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");

		row->extensions->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";"
		"padding-left:5px;}");

		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		row->interpreter->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		row->extensions->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";"
		"padding-left:5px;}");

		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		break;

	default:
		break;
	}

}
Button_Check_State ScriptsTable::buttonCheckState()
{
	Button_Check_State checkState = Button_All_Unchecked;

	int countCheck = 0;

	for (auto& row : m_scriptsRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			countCheck++;
		}
	}

	
	int rowCount = m_scriptsRowMap.count();

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
void ScriptsTable::setCheckBoxsState()
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
void ScriptsTable::resizeLabel()
{
	int fullTextWidth, labelWidth, defaultCharsNum, threeDotSize, textWidth, nextCharWidth, remainSpace;
	QFontMetrics fm(FONT);
	QString interpreter;

	for (auto& row : m_scriptsRowMap)
	{

		fullTextWidth = fm.width(row->interpreter->toolTip());
		labelWidth = (m_rowWg->width() - 20/*margin*/ - 18/*checkbox*/ - 12/*spacer*/) - 250;
		defaultCharsNum = 19; // 19 character <= 131px 
		threeDotSize = fm.width("..."); // ... => 12px

		do
		{
			interpreter = row->interpreter->toolTip();

			if ((fullTextWidth <= labelWidth))
			{
				row->interpreter->setText(interpreter);
				break;
			}

			textWidth = fm.width(interpreter.mid(0, defaultCharsNum));

			nextCharWidth = fm.width(interpreter.mid(defaultCharsNum, 1));

			remainSpace = (labelWidth - (textWidth + threeDotSize));

			if (remainSpace > nextCharWidth)
			{
				defaultCharsNum++;
				continue;
			}
			if ((textWidth + threeDotSize) <= labelWidth)
			{
				interpreter = interpreter.mid(0, defaultCharsNum) + "...";
				row->interpreter->setText(interpreter);
				break;
			}

			defaultCharsNum--;

		} while (true);
	}

}

void ScriptsTable::refresh()
{
	QString interpreter, extensions;
	if (TryEnterCriticalSection(&m_cs))
	{
		for (auto it : m_incomingData)
		{
			interpreter = it.first;
			extensions = it.second;

			ScriptsRow* row = new ScriptsRow();

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

			row->interpreter = new QLabel();
			row->interpreter->setFixedHeight(36);
			row->interpreter->setFont(FONT);
			row->interpreter->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			row->interpreter->setText(interpreter);
			row->interpreter->setToolTip(interpreter);

			row->extensions = new QLabel();
			row->extensions->setFixedSize(250, 36);
			row->extensions->setFont(FONT);
			row->extensions->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			row->extensions->setText(extensions);

			row->line = new QLabel();
			row->line->setFixedHeight(2);

			rowLayout->addWidget(row->checkBox);
			rowLayout->addWidget(centerSpacer);
			rowLayout->addWidget(row->interpreter);
			rowLayout->addWidget(row->extensions);
			setRowStyle(row);

			m_rowLayout->addWidget(row->rowWg);
			m_rowLayout->addWidget(row->line);

			m_rowCount++;

			m_scriptsRowMap.append(row);

			m_rowWg->resize(this->width(), (38 * m_rowCount));

			connect(row->checkBox, &SAPCheckBox::boxSetChecked, this, &ScriptsTable::rowCheckBoxSetCheck);
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

void ScriptsTable::changeTheme()
{
	setStyle();

	for (auto& row : m_scriptsRowMap)
	{
		setRowStyle(row);
	}
}