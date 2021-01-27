#include "processprotectortable.h"

ProcessProtectorTable::ProcessProtectorTable(QWidget *parent)
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

	m_processText = new QLabel();
	m_processText->setFixedHeight(36);
	m_processText->setFont(FONT);
	m_processText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_processText->setText("PROCESS");


	titleLayout->addWidget(m_checkAllBox);
	titleLayout->addWidget(checkboxSpacer);
	titleLayout->addWidget(m_processText);

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

	connect(m_checkAllBox, &SAPCheckBox::boxSetChecked, this, &ProcessProtectorTable::allCheckBoxSetCheck);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ProcessProtectorTable::changeTheme);

	QString name;
	for (int a = 1; a <= 30; a++)
	{
		name = "process.exe" + QString::number(a) + " ";
		AddProcess(name);
		m_defaultList.append(name);
	}

}

ProcessProtectorTable::~ProcessProtectorTable()
{
}

void ProcessProtectorTable::allCheckBoxSetCheck(Qt::CheckState state)
{
	if (state == Qt::Checked)
	{
		for (auto& row : m_processRowMap)
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
		for (auto& row : m_processRowMap)
		{
			if (row->rowWg->isVisible())
			{
				row->checkBox->setButtonChecked(Qt::Unchecked);
			}
		}
		emit setRemoveBtnDisabled(true);
	}
}

void ProcessProtectorTable::changeTheme()
{
	setStyle();

	for (auto& row : m_processRowMap)
	{
		setRowStyle(row);
	}
}

void ProcessProtectorTable::scrollBarRangeChanged(int min, int max)
{
}

void ProcessProtectorTable::rowCheckBoxSetCheck(Qt::CheckState)
{
	setCheckBoxsState();
}

void ProcessProtectorTable::AddProcess(QString process)
{
	ProcessProtectorRow* row = new ProcessProtectorRow();

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

	row->processProtector = new QLabel();
	row->processProtector->setFixedHeight(36);
	row->processProtector->setFont(FONT);
	row->processProtector->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	row->processProtector->setText(process);
	row->processProtector->setToolTip(process);

	row->line = new QLabel();
	row->line->setFixedHeight(2);

	rowLayout->addWidget(row->checkBox);
	rowLayout->addWidget(centerSpacer);
	rowLayout->addWidget(row->processProtector);
	setRowStyle(row);

	m_rowLayout->addWidget(row->rowWg);
	m_rowLayout->addWidget(row->line);

	m_rowCount++;

	m_processRowMap.append(row);

	m_rowWg->resize(this->width(), (38 * m_rowCount));

	connect(row->checkBox, &SAPCheckBox::boxSetChecked, this, &ProcessProtectorTable::rowCheckBoxSetCheck);

}

void ProcessProtectorTable::resetToDefault()
{
	QList<ProcessProtectorRow*> keyList;
	for (auto& row : m_processRowMap)
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
		m_processRowMap.removeOne(key);
	}
	for (auto& key : m_defaultList)
	{
		AddProcess(key);
	}

	setCheckBoxsState();

}

void ProcessProtectorTable::AddProcessFromDialog(QString process)
{
	int cout = -1;

	for (auto& row : m_processRowMap)
	{
		cout++;

		if (row->processProtector->text() == process)
		{
			QWidget* wg = m_rowLayout->itemAt(cout * 2)->widget();
			m_scrollView->ensureWidgetVisible(wg, 150, 150);
			return;
		}
	}

	AddProcess(process);
}

void ProcessProtectorTable::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event);
	m_rowWg->resize(m_scrollView->width(), m_rowWg->height());
}

void ProcessProtectorTable::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_titleWg->setStyleSheet("background-color:#C9C9C9;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_processText->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");

		m_processText->setStyleSheet("QLabel{color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		break;

	default:
		break;
	}
}

void ProcessProtectorTable::setRowStyle(ProcessProtectorRow * row)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		row->processProtector->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");

		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:

		row->processProtector->setStyleSheet("QLabel{color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		row->line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		break;

	default:
		break;
	}

}

Button_Check_State ProcessProtectorTable::buttonCheckState()
{
	Button_Check_State checkState = Button_All_Unchecked;

	int countCheck = 0;

	for (auto& row : m_processRowMap)
	{
		if (row->checkBox->getCheckState() == Qt::Checked && row->rowWg->isVisible())
		{
			countCheck++;
		}
	}


	int rowCount = m_processRowMap.count();

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

void ProcessProtectorTable::setCheckBoxsState()
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

void ProcessProtectorTable::removeRows()
{
	QList<ProcessProtectorRow*> keyList;
	for (auto& row : m_processRowMap)
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
		m_processRowMap.removeOne(key);
	}

	if (m_processRowMap.count() == 0) // remove all
	{
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
		emit setRemoveBtnDisabled(true);
		return;
	}

	setCheckBoxsState();
}