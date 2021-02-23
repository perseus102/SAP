#include "filenametable.h"
#include "threadpopulaterestrictedapp.h"
#include "NamedPipeSecureAPlusAdminSettings.h"

BOOLEAN callback_add_restricted_app(void* lpContext, LPCWSTR filename, LPCWSTR certCN)
{
	FileNameTable* t = (FileNameTable*)lpContext;
	t->AddRestrictedAppGUIOnly(filename, certCN);
	return TRUE;
}

FileNameTable::FileNameTable(QWidget *parent)
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

	QLabel* centerSpacer = new QLabel();
	centerSpacer->setFixedWidth(12);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(36);
	m_titleText->setFont(FONT);
	m_titleText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_titleText->setText("FILE NAME");

	QLabel* titleRightSpacer = new QLabel();

	titleLayout->addWidget(m_checkAllBox);
	titleLayout->addWidget(centerSpacer);
	titleLayout->addWidget(m_titleText);
	titleLayout->addWidget(titleRightSpacer);

	QLabel* bottomSpacer = new QLabel();
	m_layout->addWidget(m_titleWg);

	m_rowWg = new QWidget();
	m_rowLayout = new QVBoxLayout();
	m_rowLayout->setContentsMargins(0, 0, 0, 0);
	m_rowLayout->setSpacing(0);
	m_rowWg->setLayout(m_rowLayout);

	m_scrollView = new SAPSCrollArea(QMargins(5, 5, 0, 5));
	//m_scrollView->setFixedHeight(214);
	m_scrollView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
	m_scrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	m_scrollView->verticalScrollBar()->setVisible(false);
	m_scrollView->setWidget(m_rowWg);

	m_layout->addWidget(m_scrollView);

	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);
	setStyle();

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &FileNameTable::changeTheme);
	connect(m_checkAllBox, &SAPCheckBox::boxSetChecked, this, &FileNameTable::allCheckBoxSetCheck);
	connect(m_scrollView->verticalScrollBar(), &QScrollBar::rangeChanged, this, &FileNameTable::scrollBarRangeChanged);

	m_rowCount = 0;

	//Init default list here
	/*m_defaultList.append("7z.exe");
	m_defaultList.append("7zfm.exe");
	m_defaultList.append("7zg.exe");
	m_defaultList.append("ace32loader.exe");
	m_defaultList.append("browser.exe");
	m_defaultList.append("Chrome.exe");
	m_defaultList.append("explorer.exe");
	m_defaultList.append("firefox.exe");
	m_defaultList.append("goodsync.exe");
	m_defaultList.append("microsoftedge.exe");
	m_defaultList.append("microsoftedgecp.exe");
	m_defaultList.append("notepad++.exe");
	m_defaultList.append("onedrive.exe");
	m_defaultList.append("outlook.exe");*/
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

FileNameTable::~FileNameTable()
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

void FileNameTable::loadData(BOOLEAN force)
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
		hThread = CreateThreadPopulateRestrictedApp(this, callback_add_restricted_app, hStopEvent, hCompletedEvent);
		m_timerRefresh->start(500);
	}
}

void FileNameTable::AddRestrictedAppGUIOnly(LPCWSTR filename, LPCWSTR certCN)
{
	EnterCriticalSection(&m_cs);
	m_incomingData.push_back(std::make_pair(QString::fromWCharArray(filename), QString::fromWCharArray(certCN)));
	LeaveCriticalSection(&m_cs);
}

void FileNameTable::AddRestrictedApp(QString& fileName, QString& certCN)
{
	DWORD dwLastError = 0;
	std::wstring fileNameW, certCNW;

	fileNameW = fileName.toStdWString();
	certCNW = certCN.toStdWString();
	dwLastError = SecureaplusAdminSettingsAddRestrictedApp(fileNameW.c_str(), certCNW.c_str());
	if (dwLastError != 0)
	{
		// TODO: display error, when add fails
		return;
	}

	EnterCriticalSection(&m_cs);
	m_incomingData.push_back(std::make_pair(fileName, certCN));
	LeaveCriticalSection(&m_cs);
}

void FileNameTable::updateFilterRow(QStringList list)
{
	m_filterCount = 0;
	for (auto& row : m_fileNameRowMap)
	{
		row->rowWg->setVisible(false);
		row->line->setVisible(false);
		if (list.indexOf(row->fileNameText->text()) != -1)
		{
			row->rowWg->setVisible(true);
			row->line->setVisible(true);
			m_filterCount++;
		}
	}

	m_rowWg->resize(this->width(), (36 * m_filterCount));
	qDebug() << "count" << m_filterCount;

	setCheckBoxsState();
}

void FileNameTable::setFilterRow(bool isFilter)
{
	m_isFilter = isFilter;
}

void FileNameTable::resetToDefault()
{
	DWORD dwLastError = 0;
	QStringList keyList;

	// TODO: disable/deactivate "Reset to default" label here

	// restore defaults in backend
	dwLastError = SecureaplusAdminSettingsRestoreDefaultRestrictedApp();
	if (dwLastError)
	{
		// TODO: display error, when reset to default fails 
		return;
	}

	for (auto& row : m_fileNameRowMap)
	{
		keyList.append(m_fileNameRowMap.key(row));
		m_rowLayout->removeWidget(row->rowWg);
		m_rowLayout->removeWidget(row->line);
		row->rowWg->setParent(nullptr);
		row->line->setParent(nullptr);
		delete row->rowWg;
		delete row->line;
		m_rowCount--;
		QSize size = m_rowWg->size();
		m_rowWg->resize(this->width(), size.height() - 36);
	}

	for (auto& key : keyList)
	{
		m_fileNameRowMap.remove(key);
		emit removeWord(key);
	}
	setCheckBoxsState();

	// re-populate all rows in GUI
	loadData(TRUE);
}


void FileNameTable::allCheckBoxSetCheck(Qt::CheckState state)
{
	if (state == Qt::Checked)
	{
		for (auto& row : m_fileNameRowMap)
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
		for (auto& row : m_fileNameRowMap)
		{
			if (row->rowWg->isVisible())
			{
				row->checkBox->setButtonChecked(Qt::Unchecked);
			}
		}
		emit setRemoveBtnDisabled(true);
	}
}

void FileNameTable::scrollBarRangeChanged(int min, int max)
{
	Q_UNUSED(min);
	Q_UNUSED(max);
	if (m_rowWg->height() > m_scrollView->height())
	{
		emit m_scrollView->verticalScrollBar()->valueChanged(m_scrollView->verticalScrollBar()->value());
	}
}

void FileNameTable::rowCheckBoxSetCheck(Qt::CheckState state)
{
	Q_UNUSED(state);
	setCheckBoxsState();
}

void FileNameTable::AddFileNameFromDialog(QString fileName)
{
	int cout = -1;
	//check exist row
	if (m_fileNameRowMap.value(fileName) != nullptr)
	{
		for (auto& name : m_fileNameList)
		{
			cout++;
			if (name == fileName)
			{
				QWidget* wg = m_rowLayout->itemAt(cout * 2)->widget();
				m_scrollView->ensureWidgetVisible(wg, 150, 150);
				return;
			}
		}
	}

	AddRestrictedApp(fileName, QString("")); // [Ben] TODO: dive into Browse button in addResAppDialog to define cert
	refresh();
}

void FileNameTable::removeRows()
{
	DWORD dwLastError = 0;
	QStringList keyList;
	for (auto& row : m_fileNameRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			dwLastError = SecureaplusAdminSettingsDeleteRestrictedApp(row->fileNameText->text().toStdWString().c_str());
			if (dwLastError != 0)
			{
				// TODO: display error, when remove fails
				break;
			}

			keyList.append(m_fileNameRowMap.key(row));
			m_rowLayout->removeWidget(row->rowWg);
			m_rowLayout->removeWidget(row->line);
			row->rowWg->setParent(nullptr);
			row->line->setParent(nullptr);
			delete row->rowWg;
			delete row->line;
			m_rowCount--;
			QSize size = m_rowWg->size();
			m_rowWg->resize(this->width(), size.height() - 36);
		}
	}

	for (auto& key : keyList)
	{
		m_fileNameRowMap.remove(key);
		emit removeWord(key);
	}

	if (m_fileNameRowMap.count() == 0) // remove all
	{
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
		emit setRemoveBtnDisabled(true);
		return;
	}

	setCheckBoxsState();
}

void FileNameTable::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);
	m_rowWg->resize(m_scrollView->width(), m_rowWg->height());
}

void FileNameTable::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_titleWg->setStyleSheet("background-color:#C9C9C9;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_titleText->setStyleSheet("QLabel{color:"+ TAB_CONTENT_TITLE_TEXT_LT +";}");

		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_titleText->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		break;

	default:
		break;
	}
}

void FileNameTable::setRowStyle(FileNameRow * row)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		row->fileNameText->setStyleSheet("QLabel{color:"+ TAB_CONTENT_DESC_TEXT_LT +";}");
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		row->fileNameText->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		break;

	default:
		break;
	}
}

bool FileNameTable::checkAllUnChecked()
{
	bool allUnChecked = true;
	for (auto& row : m_fileNameRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			allUnChecked = false;
			emit setRemoveBtnDisabled(false);
			break;
		}
	}
	if (allUnChecked)
	{
		emit setRemoveBtnDisabled(true);
	}

	return allUnChecked;

}

bool FileNameTable::checkAllChecked()
{
	bool allChecked = true;

	for (auto& row : m_fileNameRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Unchecked && row->rowWg->isVisible())
		{
			allChecked = false;
			break;
		}
	}
	if (allChecked)
	{
		m_checkAllBox->setButtonChecked(Qt::Checked);
	}

	return allChecked;
}

Button_Check_State FileNameTable::buttonCheckState()
{
	Button_Check_State checkState = Button_All_Unchecked;

	int countCheck = 0;

	for (auto& row : m_fileNameRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			countCheck++;
		}
	}

	if (m_isFilter)
	{
		if (m_filterCount == 0)
		{
			checkState = Button_All_Unchecked;
		}
		else if (countCheck == m_filterCount)
		{
			checkState = Button_All_Checked;
		}
		else if ((countCheck > 0) && (countCheck < m_filterCount))
		{
			checkState = Button_Checked;
		}
		else if (countCheck == 0)
		{
			checkState = Button_All_Unchecked;
		}
	}
	else
	{
		int rowCount = m_fileNameRowMap.count();
		
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
	}


	return checkState;
}

void FileNameTable::setCheckBoxsState()
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

void FileNameTable::refresh()
{
	QString fileName;
	if (TryEnterCriticalSection(&m_cs))
	{
		for (auto it : m_incomingData)
		{
			fileName = it.first;

			FileNameRow* row = new FileNameRow();

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

			row->fileNameText = new QLabel();
			row->fileNameText->setFixedHeight(36);
			row->fileNameText->setFont(FONT);
			row->fileNameText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			row->fileNameText->setText(fileName);

			QLabel* titleRightSpacer = new QLabel();

			row->line = new QLabel();
			row->line->setFixedHeight(2);

			rowLayout->addWidget(row->checkBox);
			rowLayout->addWidget(centerSpacer);
			rowLayout->addWidget(row->fileNameText);
			rowLayout->addWidget(titleRightSpacer);
			setRowStyle(row);

			m_rowLayout->addWidget(row->rowWg);
			m_rowLayout->addWidget(row->line);

			m_fileNameRowMap.insert(fileName, row);
			m_fileNameList.append(fileName);
			m_rowCount++;

			if (m_isFilter)
			{
				QSize size = m_rowWg->size();
				m_rowWg->resize(this->width(), size.height() + 38);
			}
			else
			{
				m_rowWg->resize(this->width(), (38 * m_rowCount));
			}

			connect(row->checkBox, &SAPCheckBox::boxSetChecked, this, &FileNameTable::rowCheckBoxSetCheck);

			emit addWord(fileName);
		}

		if (hCompletedEvent)
		{
			if (WaitForSingleObject(hCompletedEvent, 0) == 0)
			{
				//Completed
				if (m_timerRefresh) m_timerRefresh->stop();
			}
		}

		m_incomingData.clear();
		LeaveCriticalSection(&m_cs);
	}
}

void FileNameTable::changeTheme()
{
	setStyle();

	for (auto& row : m_fileNameRowMap)
	{
		setRowStyle(row);
	}
}
