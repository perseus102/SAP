#include "filenametable.h"

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

	m_checkAllBox = new SAPCheckBox();
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
	m_scrollView->setFixedHeight(214);
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

	AddFileName("Uninstall_Service1.cmd");
	AddFileName("Uninstall_Service2.cmd");
	AddFileName("Uninstall_Service3.cmd");
	AddFileName("Uninstall_Service4.cmd");
	AddFileName("Uninstall_Service5.cmd");
	AddFileName("Uninstall_Service6.cmd");
	AddFileName("Uninstall_Service7.cmd");
	AddFileName("Uninstall_Service8.cmd");
	AddFileName("Uninstall_Service9.cmd");
	AddFileName("Uninstall_Service10.cmd");

}

FileNameTable::~FileNameTable()
{

}

void FileNameTable::AddFileName(QString fileName)
{
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

	row->m_line = new QLabel();
	row->m_line->setFixedHeight(2);

	rowLayout->addWidget(row->checkBox);
	rowLayout->addWidget(centerSpacer);
	rowLayout->addWidget(row->fileNameText);
	rowLayout->addWidget(titleRightSpacer);
	setRowStyle(row);

	m_rowLayout->addWidget(row->rowWg);
	m_rowLayout->addWidget(row->m_line);

	m_fileNameRowMap.insert(fileName, row);
	m_rowCount++;

	m_rowWg->resize(this->width(), (36 * m_rowCount));
	
	connect(row->checkBox, &SAPCheckBox::boxSetChecked, this, &FileNameTable::rowCheckBoxSetCheck);

}

void FileNameTable::allCheckBoxSetCheck(Qt::CheckState state)
{
	if (state == Qt::Checked)
	{
		for (auto& row : m_fileNameRowMap)
		{
			row->checkBox->setButtonChecked(Qt::Checked);
		}
	}
	else
	{
		for (auto& row : m_fileNameRowMap)
		{
			row->checkBox->setButtonChecked(Qt::Unchecked);
		}
	}
}

void FileNameTable::scrollBarRangeChanged(int min, int max)
{

	if (m_rowWg->height() > m_scrollView->height())
	{
		emit m_scrollView->verticalScrollBar()->valueChanged(m_scrollView->verticalScrollBar()->value());
	}
}

void FileNameTable::rowCheckBoxSetCheck(Qt::CheckState state)
{
	if (state == Qt::Checked)
	{
		bool allChecked = true;

		for (auto& row : m_fileNameRowMap)
		{
			if(row->checkBox->getCheckState() == Qt::Unchecked)
			{
				allChecked = false;
				break;
			}
		}
		if (allChecked)
		{
			m_checkAllBox->setButtonChecked(Qt::Checked);
		}
	}
	else
	{
		m_checkAllBox->setButtonChecked(Qt::Unchecked);
	}
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
		m_titleText->setStyleSheet("QLabel{color:#737373;}");

		break;

	case Theme_Type::Dark_Theme:
		m_titleWg->setStyleSheet("background-color:#48556E;"
			"border-top-left-radius:2px; border-top-right-radius:2px;");
		m_titleText->setStyleSheet("QLabel{color:#737373;}");

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
		row->fileNameText->setStyleSheet("QLabel{color:#737373;}");
		row->m_line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		row->fileNameText->setStyleSheet("QLabel{color:#48556E;}");
		row->m_line->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		break;

	default:
		break;
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
