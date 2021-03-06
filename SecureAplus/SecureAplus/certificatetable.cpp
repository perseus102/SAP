#include "certificatetable.h"
#include "threadpopulatecertificate.h"
#include "NamedPipeSecureAPlusAdminSettings.h"

BOOLEAN callback_add_certificate(LPVOID lpContext, LPCWSTR name, LPCWSTR thumbprint, FILETIME valid_from, FILETIME valid_to)
{
	CertificateTable* t = (CertificateTable*)lpContext;
	t->AddCertificateGUIOnly(name, thumbprint, valid_from, valid_to);
	return TRUE;
}

CertificateTable::CertificateTable(QWidget *parent)
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

	m_certificateName = new QLabel();
	m_certificateName->setFixedHeight(36);
	m_certificateName->setFont(FONT);
	m_certificateName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_certificateName->setText("CERTIFICATE NAME");

	m_validFrom = new QLabel();
	m_validFrom->setFixedSize(130,36);
	m_validFrom->setFont(FONT);
	m_validFrom->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_validFrom->setText("VALID FROM");

	m_validTo = new QLabel();
	m_validTo->setFixedSize(130, 36);
	m_validTo->setFixedHeight(36);
	m_validTo->setFont(FONT);
	m_validTo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_validTo->setText("VALID TO");

	titleLayout->addWidget(m_checkAllBox);
	titleLayout->addWidget(checkboxSpacer);
	titleLayout->addWidget(m_certificateName);
	titleLayout->addWidget(m_validFrom);
	titleLayout->addWidget(m_validTo);

	QLabel* bottomSpacer = new QLabel();
	m_layout->addWidget(m_titleWg);

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

	connect(m_checkAllBox, &SAPCheckBox::boxSetChecked, this, &CertificateTable::allCheckBoxSetCheck);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CertificateTable::changeTheme);

	m_timerRefresh = new QTimer(this);
	if (m_timerRefresh)
	{
		connect(m_timerRefresh, SIGNAL(timeout()), this, SLOT(refresh()));
	}
	hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hCompletedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hThread = NULL;
	InitializeCriticalSection(&m_cs);
	/*for (int a = 1; a <= 50; a++)
	{
		CertificateRowString rowString;
		rowString.CertificateNameText = "Uninstall_Service_Deviceeeee.cmd" + QString::number(a);;
		rowString.validFromText = "2006-06-28";
		rowString.validToText = "2009-06-27";
		rowString.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF" + QString::number(a);
		AddCertificate(rowString);
		m_defaultList.append(rowString);
	}*/
	//init m_defaultList here
}

CertificateTable::~CertificateTable()
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

void CertificateTable::loadData(BOOLEAN force)
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
		hThread = CreateThreadPopulateCertificate(this, callback_add_certificate, hStopEvent, hCompletedEvent);
		m_timerRefresh->start(500);
	}
}

void CertificateTable::AddCertificateGUIOnly(LPCWSTR name, LPCWSTR thumbprint, FILETIME valid_from, FILETIME valid_to)
{
	CertificateRowString rowString;
	SYSTEMTIME valid_from_st, valid_to_st;

	FileTimeToSystemTime(&valid_from, &valid_from_st);
	FileTimeToSystemTime(&valid_to, &valid_to_st);

	rowString.CertificateNameText = QString::fromWCharArray(name);
	rowString.thumprintText = QString::fromWCharArray(thumbprint);
	rowString.validFromText = QString("%3-%2-%1").arg(valid_from_st.wDay, 2, 10, QChar('0')).arg(valid_from_st.wMonth, 2, 10, QChar('0')).arg(valid_from_st.wYear, 4, 10, QLatin1Char('0'));
	rowString.validToText = QString("%3-%2-%1").arg(valid_to_st.wDay, 2, 10, QChar('0')).arg(valid_to_st.wMonth, 2, 10, QChar('0')).arg(valid_to_st.wYear, 4, 10, QLatin1Char('0'));

	EnterCriticalSection(&m_cs);
	m_incomingData.push_back(rowString);
	LeaveCriticalSection(&m_cs);
}

void CertificateTable::AddCertificate(QString& name, QString& thumbprint, FILETIME valid_from, FILETIME valid_to)
{
	CertificateRowString rowString;
	SYSTEMTIME valid_from_st, valid_to_st;
	DWORD dwLastError = 0;
	std::wstring nameW, thumbprintW;

	nameW = name.toStdWString();
	thumbprintW = thumbprint.toStdWString();
	dwLastError = SecureaplusAdminSettingsAddTrustedCertificate(nameW.c_str(), thumbprintW.c_str(), valid_from, valid_to);
	if (dwLastError != 0)
	{
		// TODO: display error, when add fails
		return;
	}

	FileTimeToSystemTime(&valid_from, &valid_from_st);
	FileTimeToSystemTime(&valid_to, &valid_to_st);

	rowString.CertificateNameText = name;
	rowString.thumprintText = thumbprint;
	rowString.validFromText = QString("%3-%2-%1").arg(valid_from_st.wDay, 2, 10, QChar('0')).arg(valid_from_st.wMonth, 2, 10, QChar('0')).arg(valid_from_st.wYear, 4, 10, QLatin1Char('0'));
	rowString.validToText = QString("%3-%2-%1").arg(valid_to_st.wDay, 2, 10, QChar('0')).arg(valid_to_st.wMonth, 2, 10, QChar('0')).arg(valid_to_st.wYear, 4, 10, QLatin1Char('0'));

	EnterCriticalSection(&m_cs);
	m_incomingData.push_back(rowString);
	LeaveCriticalSection(&m_cs);
}

void CertificateTable::allCheckBoxSetCheck(Qt::CheckState state)
{
	if (state == Qt::Checked)
	{
		for (auto& row : m_CertificateRowMap)
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
		for (auto& row : m_CertificateRowMap)
		{
			if (row->rowWg->isVisible())
			{
				row->checkBox->setButtonChecked(Qt::Unchecked);
			}
		}
		emit setRemoveBtnDisabled(true);
	}
}

void CertificateTable::scrollBarRangeChanged(int min, int max)
{
	Q_UNUSED(min);
	Q_UNUSED(max);
	if (m_rowWg->height() > m_scrollView->height())
	{
		emit m_scrollView->verticalScrollBar()->valueChanged(m_scrollView->verticalScrollBar()->value());
	}
}

void CertificateTable::rowCheckBoxSetCheck(Qt::CheckState)
{
	setCheckBoxsState();
}

void CertificateTable::resetToDefault()
{
	DWORD dwLastError = 0;
	QList<CertificateRow*> keyList;

	// TODO: disable/deactivate "Reset to default" label here

	// restore defaults in backend
	dwLastError = SecureaplusAdminSettingsRestoreDefaultTrustedCertificate();
	if (dwLastError)
	{
		// TODO: display error, when reset to default fails 
		return;
	}

	// de-populate all rows in GUI
	for (auto& row : m_CertificateRowMap)
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
		m_CertificateRowMap.removeOne(key);
	}

	setCheckBoxsState();
	resizeLabel();

	// re-populate all rows in GUI
	loadData(TRUE);
}

void CertificateTable::AddCertificateFromDialog(QString &name, QString &thumbprint, FILETIME valid_from, FILETIME valid_to)
{
	int cout = -1;

	for (auto& row : m_CertificateRowMap)
	{
		cout++;

		if (row->thumbprint->text() == thumbprint)
		{
			QWidget* wg = m_rowLayout->itemAt(cout * 2)->widget();
			m_scrollView->ensureWidgetVisible(wg,150,150);
			return;
		}
	}

	AddCertificate(name, thumbprint, valid_from, valid_to);
	refresh();
}

void CertificateTable::removeRows()
{
	DWORD dwLastError = 0;
	std::wstring certnameW, thumbprintW;
	QList<CertificateRow*> keyList;
	for (auto& row : m_CertificateRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			certnameW = row->CertificateName->text().toStdWString();
			thumbprintW = row->thumbprint->text().toStdWString();
			dwLastError = SecureaplusAdminSettingsDeleteTrustedCertificate(certnameW.c_str(), thumbprintW.c_str());
			if (dwLastError == ERROR_FILE_NOT_FOUND) dwLastError = 0; //this is ok, the entry has been deleted.
			if (dwLastError != 0)
			{
				// TODO: display error when remove() fails
				/**pbDeleteThis = false;
				bContinue = false;
				SecureAPlusDisplayError(this, dwLastError);*/
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
			m_rowWg->resize(this->width(), size.height() - 52 /* row height */);
		}
	}

	for (auto& key : keyList)
	{
		m_CertificateRowMap.removeOne(key);
	}

	if (m_CertificateRowMap.count() == 0) // remove all
	{
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
		emit setRemoveBtnDisabled(true);
		return;
	}

	setCheckBoxsState();

}

void CertificateTable::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event);
	m_rowWg->resize(m_scrollView->width(), m_rowWg->height());
	
	resizeLabel();
}

void CertificateTable::setStyle()
{
	switch(AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_titleWg->setStyleSheet("background-color:#C9C9C9;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_certificateName->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		m_validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";"
										"padding-left:5px;}");
		m_validTo->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_certificateName->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
		m_validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";"
										"padding-left:5px;}");
		m_validTo->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		break;

	default:
		break;
	}
}

void CertificateTable::setRowStyle(CertificateRow * row)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		row->CertificateName->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");

		row->validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";"
											"padding-left:5px;}");
		row->validTo->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");

		row->thumbprint->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		row->CertificateName->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		row->validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";"
											"padding-left:5px;}");
		row->validTo->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		row->thumbprint->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		break;

	default:
		break;
	}
}

Button_Check_State CertificateTable::buttonCheckState()
{
	Button_Check_State checkState = Button_All_Unchecked;

	int countCheck = 0;

	for (auto& row : m_CertificateRowMap)
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
		int rowCount = m_CertificateRowMap.count();

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

void CertificateTable::setCheckBoxsState()
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

void CertificateTable::resizeLabel()
{
	int fullTextWidth, labelWidth, defaultCharsNum, threeDotSize, textWidth, nextCharWidth, remainSpace;
	QFontMetrics fm(FONT);
	QString CertificateName;

	for (auto& row : m_CertificateRowMap)
	{

		fullTextWidth = fm.width(row->CertificateName->toolTip());
		labelWidth = (m_rowWg->width() - 20/*margin*/ - 18/*checkbox*/ - 12/*spacer*/) - 260;
		defaultCharsNum = 19; // 19 character <= 131px 
		threeDotSize = fm.width("..."); // ... => 12px

		do
		{
			CertificateName = row->CertificateName->toolTip();

			if ((fullTextWidth <= labelWidth))
			{
				row->CertificateName->setText(CertificateName);
				break;
			}

			textWidth = fm.width(CertificateName.mid(0, defaultCharsNum));

			nextCharWidth = fm.width(CertificateName.mid(defaultCharsNum, 1));

			remainSpace = (labelWidth - (textWidth + threeDotSize));

			if (remainSpace > nextCharWidth)
			{
				defaultCharsNum++;
				continue;
			}
			if ((textWidth + threeDotSize) <= labelWidth)
			{
				CertificateName = CertificateName.mid(0, defaultCharsNum) + "...";
				row->CertificateName->setText(CertificateName);
				break;
			}

			defaultCharsNum--;

		} while (true);
	}
}

void CertificateTable::refresh()
{

	if (TryEnterCriticalSection(&m_cs))
	{
		for (auto rowString : m_incomingData)
		{
			CertificateRow* row = new CertificateRow();

			row->rowWg = new QWidget();
			row->rowWg->setFixedHeight(50);

			QVBoxLayout* rowLayout = new QVBoxLayout();
			rowLayout->setContentsMargins(0, 0, 0, 0);
			rowLayout->setSpacing(0);

			row->rowWg->setLayout(rowLayout);

			QWidget* HRowWg = new QWidget();
			HRowWg->setFixedHeight(36);

			QHBoxLayout* HRowLayout = new QHBoxLayout();
			HRowLayout->setContentsMargins(20, 0, 0, 0);
			HRowLayout->setSpacing(0);
			HRowWg->setLayout(HRowLayout);


			row->rowWg->setLayout(rowLayout);
			row->checkBox = new SAPCheckBox();
			row->checkBox->setFixedSize(18, 36);
			row->checkBox->setButtonChecked(Qt::Unchecked);

			QLabel* centerSpacer = new QLabel();
			centerSpacer->setFixedWidth(12);

			row->CertificateName = new QLabel();
			row->CertificateName->setFixedHeight(36);
			row->CertificateName->setFont(FONT);
			row->CertificateName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			row->CertificateName->setText(rowString.CertificateNameText);
			row->CertificateName->setToolTip(rowString.CertificateNameText);

			row->validFrom = new QLabel();
			row->validFrom->setFixedSize(130, 36);

			row->validFrom->setFont(FONT);
			row->validFrom->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			row->validFrom->setText(rowString.validFromText);

			row->validTo = new QLabel();
			row->validTo->setFixedSize(130, 36);

			row->validTo->setFont(FONT);
			row->validTo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			row->validTo->setText(rowString.validToText);

			HRowLayout->addWidget(row->checkBox);
			HRowLayout->addWidget(centerSpacer);
			HRowLayout->addWidget(row->CertificateName);
			HRowLayout->addWidget(row->validFrom);
			HRowLayout->addWidget(row->validTo);

			QWidget* thumprintWg = new QWidget();
			thumprintWg->setFixedHeight(14);

			QHBoxLayout* thumprintLayout = new QHBoxLayout();
			thumprintLayout->setContentsMargins(50, 0, 0, 0);
			thumprintLayout->setSpacing(0);
			thumprintWg->setLayout(thumprintLayout);

			row->thumbprint = new QLabel();
			row->thumbprint->setFixedHeight(14);
			row->thumbprint->setFont(FONT);
			row->thumbprint->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			row->thumbprint->setText(rowString.thumprintText);

			thumprintLayout->addWidget(row->thumbprint);

			row->line = new QLabel();
			row->line->setFixedHeight(2);

			QLabel* bottomSpacer = new QLabel();
			bottomSpacer->setFixedHeight(6);

			rowLayout->addWidget(HRowWg);
			rowLayout->addWidget(thumprintWg);
			rowLayout->addWidget(bottomSpacer);

			m_rowLayout->addWidget(row->rowWg);
			m_rowLayout->addWidget(row->line);
			setRowStyle(row);
			m_rowCount++;

			m_CertificateRowMap.append(row);
			if (m_isFilter)
			{
				QSize size = m_scrollView->size();
				m_rowWg->resize(this->width(), size.height() + 52);
			}
			else
			{

				m_rowWg->resize(this->width(), (52 * m_rowCount));
			}

			connect(row->checkBox, &SAPCheckBox::boxSetChecked, this, &CertificateTable::rowCheckBoxSetCheck);
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

void CertificateTable::changeTheme()
{
	setStyle();

	for (auto& row : m_CertificateRowMap)
	{
		setRowStyle(row);
	}
}
