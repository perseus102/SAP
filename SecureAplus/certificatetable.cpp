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
	QStringList keyList;
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
		m_rowWg->resize(this->width(), size.height() - 36);
	}

	for (auto& key : keyList)
	{
		m_CertificateRowMap.remove(key);
		emit removeWord(key);
	}

	for (auto& key : m_defaultList)
	{
		AddCertificate(key);
	}

	setCheckBoxsState();
}

void CertificateTable::resizeEvent(QResizeEvent * event)
{
}

void CertificateTable::setStyle()
{
	switch(AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_titleWg->setStyleSheet("background-color:#C9C9C9;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_certificateName->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		m_validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		m_validTo->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_certificateName->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
		m_validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
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
		row->validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->validTo->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->thumprint->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		row->CertificateName->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		row->validFrom->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
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

void CertificateTable::AddCertificate(CertificateRow* Certificate)
{
}

void CertificateTable::changeTheme()
{
	setStyle();

	for (auto& row : m_CertificateRowMap)
	{
		setRowStyle(row);
	}
}
