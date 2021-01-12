#include "certificatetable.h"
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
	m_validFrom->setFixedHeight(36);
	m_validFrom->setFont(FONT);
	m_validFrom->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_validFrom->setText("VALID FROM");

	m_validTo = new QLabel();
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

	CertificateRowString rowString1;
	rowString1.CertificateNameText = "Uninstall_Service.cmd";
	rowString1.validFromText = "2006-06-28";
	rowString1.validToText = "2009-06-27";
	rowString1.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF1";

	CertificateRowString rowString2;
	rowString2.CertificateNameText = "QWERTYUIOPASDFGHJKL.ZXCVBNM1234567890";
	rowString2.validFromText = "2006-06-28";
	rowString2.validToText = "2009-06-27";
	rowString2.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF2";

	CertificateRowString rowString3;
	rowString3.CertificateNameText = "Uninstall_Service1.cmd";
	rowString3.validFromText = "2006-06-28";
	rowString3.validToText = "2009-06-27";
	rowString3.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF3";

	CertificateRowString rowString4;
	rowString4.CertificateNameText = "Uninstall_Service2.cmd";
	rowString4.validFromText = "2006-06-28";
	rowString4.validToText = "2009-06-27";
	rowString4.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF4";

	CertificateRowString rowString5;
	rowString5.CertificateNameText = "Uninstall_Service3.cmd";
	rowString5.validFromText = "2006-06-28";
	rowString5.validToText = "2009-06-27";
	rowString5.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF5";

	CertificateRowString rowString6;
	rowString6.CertificateNameText = "Uninstall_Service4.cmd";
	rowString6.validFromText = "2006-06-28";
	rowString6.validToText = "2009-06-27";
	rowString6.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF6";

	CertificateRowString rowString7;
	rowString7.CertificateNameText = "Uninstall_Service5.cmd";
	rowString7.validFromText = "2006-06-28";
	rowString7.validToText = "2009-06-27";
	rowString7.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF7";

	CertificateRowString rowString8;
	rowString8.CertificateNameText = "Uninstall_Service6.cmd";
	rowString8.validFromText = "2006-06-28";
	rowString8.validToText = "2009-06-27";
	rowString8.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF8";

	CertificateRowString rowString9;
	rowString9.CertificateNameText = "Uninstall_Service7.cmd";
	rowString9.validFromText = "2006-06-28";
	rowString9.validToText = "2009-06-27";
	rowString9.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUH9F";

	CertificateRowString rowString10;
	rowString10.CertificateNameText = "Uninstall_Service8.cmd";
	rowString10.validFromText = "2006-06-28";
	rowString10.validToText = "2009-06-27";
	rowString10.thumprintText = "IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF10";

	AddCertificate(rowString1);
	AddCertificate(rowString2);
	AddCertificate(rowString3);
	AddCertificate(rowString4);
	AddCertificate(rowString5);
	AddCertificate(rowString6);
	AddCertificate(rowString7);
	AddCertificate(rowString8);
	AddCertificate(rowString9);
	AddCertificate(rowString10);

}

CertificateTable::~CertificateTable()
{
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
	QList<QString> keyList;
	for (auto& row : m_CertificateRowMap)
	{
		keyList.append(m_CertificateRowMap.key(row));
		m_rowLayout->removeWidget(row->rowWg);
		m_rowLayout->removeWidget(row->line);
		row->rowWg->setParent(nullptr);
		row->line->setParent(nullptr);
		delete row->rowWg;
		delete row->line;
		m_rowCount--;
		QSize size = m_rowWg->size();
		m_rowWg->resize(this->width(), size.height() - 50);
	}

	for (auto& key : keyList)
	{
		m_CertificateRowMap.remove(key);
		//emit removeWord(key);
	}

	for (auto& key : m_defaultList)
	{
		AddCertificate(key);
	}

	setCheckBoxsState();
}

void CertificateTable::AddCertificateFromDialog(CertificateRowString rowString)
{
	int cout = -1;

	for (auto& row : m_CertificateRowMap)
	{
		cout++;
		if (row->thumprint->text() == rowString.thumprintText)
		{
			QWidget* wg = m_rowLayout->itemAt(cout * 2)->widget();
			m_scrollView->ensureWidgetVisible(wg);
			return;
		}
	}

	AddCertificate(rowString);
}

void CertificateTable::removeRows()
{
	QList<QString> keyList;
	for (auto& row : m_CertificateRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			keyList.append(m_CertificateRowMap.key(row));
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
		m_CertificateRowMap.remove(key);
		//emit removeWord(key);
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

	for (auto& row : m_CertificateRowMap)
	{
		QString CertificateName;

		QFontMetrics fm(FONT);
		int fullTextWidth = fm.width(row->CertificateName->toolTip());
		int labelWidth = (m_rowWg->width() - 20/*margin*/ - 18/*checkbox*/ - 12/*spacer*/) / 3;


		int defaultCharsNum = 19; // 19 character <= 131px 
		int treeDotSize = 12; // ... => 12px
		do
		{
			if ((fullTextWidth <= labelWidth))
			{
				CertificateName = row->CertificateName->toolTip();
				row->CertificateName->setText(row->CertificateName->toolTip());
				break;
			}

			CertificateName = row->CertificateName->toolTip();
			QFontMetrics fm(FONT);
			int textWidth = fm.width(CertificateName.mid(0, defaultCharsNum));

			if ((labelWidth - (textWidth + treeDotSize)) >= 10) //10px is for 1 character
			{
				defaultCharsNum++;
				continue;
			}
			if ((textWidth + treeDotSize) <= labelWidth)
			{
				CertificateName = CertificateName.mid(0, defaultCharsNum) + "...";
				row->CertificateName->setText(CertificateName);
				break;
			}
			defaultCharsNum--;
		} while (true);
	}
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

		row->thumprint->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		row->CertificateName->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		row->validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";"
											"padding-left:5px;}");
		row->validTo->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		row->thumprint->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
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

void CertificateTable::AddCertificate(CertificateRowString rowString)
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
	row->validFrom->setFixedHeight(36);
	row->validFrom->setFont(FONT);
	row->validFrom->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->validFrom->setText(rowString.validFromText);

	row->validTo = new QLabel();
	row->validTo->setFixedHeight(36);
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

	row->thumprint = new QLabel();
	row->thumprint->setFixedHeight(14);
	row->thumprint->setFont(FONT);
	row->thumprint->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->thumprint->setText(rowString.thumprintText);

	thumprintLayout->addWidget(row->thumprint);

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

	m_CertificateRowMap.insert(rowString.CertificateNameText, row);

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

	//emit addWord(fileName);

}

void CertificateTable::changeTheme()
{
	setStyle();

	for (auto& row : m_CertificateRowMap)
	{
		setRowStyle(row);
	}
}
