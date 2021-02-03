#include "commandline.h"

CommandLine::CommandLine(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 0, 40, 10);
	m_layout->setSpacing(0);

	m_commandLineTable = new CommandLineTable();

	QLabel* bottomTableSpacer = new QLabel();
	bottomTableSpacer->setFixedHeight(10);

	QWidget* bottomBtns = new QWidget();
	bottomBtns->setFixedHeight(30);
	QHBoxLayout* btnsLayout = new QHBoxLayout();
	btnsLayout->setContentsMargins(0, 0, 0, 0);
	btnsLayout->setSpacing(0);
	bottomBtns->setLayout(btnsLayout);

	m_resetBtn = new ResetButton();
	m_resetBtn->setFixedSize(16, 16);

	QLabel* centerBtnsSpacer = new QLabel();

	m_removeBtn = new QPushButton();
	m_removeBtn->setFixedSize(80, 30);
	m_removeBtn->setFont(FONT);
	m_removeBtn->setText("Remove");
	m_removeBtn->setDisabled(true);

	QLabel* btnsSpacer = new QLabel();
	btnsSpacer->setFixedWidth(8);

	m_addBtn = new QPushButton();
	m_addBtn->setFixedSize(80, 30);
	m_addBtn->setFont(FONT);
	m_addBtn->setText("Add");

	btnsLayout->addWidget(m_resetBtn);
	btnsLayout->addWidget(centerBtnsSpacer);
	btnsLayout->addWidget(m_removeBtn);
	btnsLayout->addWidget(btnsSpacer);
	btnsLayout->addWidget(m_addBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_commandLineTable);
	m_layout->addWidget(bottomTableSpacer);
	m_layout->addWidget(bottomBtns);
	m_layout->addWidget(bottomSpacer);

	transparent = new WidgetTransparent();
	m_addCommandLineDialog = new AddCommandLineDialog();

	setLayout(m_layout);
	setStyle();

	connect(m_removeBtn, &QPushButton::clicked, m_commandLineTable, &CommandLineTable::removeRows);
	connect(m_removeBtn, &QPushButton::clicked, this, &CommandLine::removeButtonClicked);

	connect(m_addBtn, &QPushButton::clicked, this, &CommandLine::addButtonClicked);

	connect(m_resetBtn, &ResetButton::clicked, this, &CommandLine::resetToDefaultClicked);
	connect(m_resetBtn, &ResetButton::signalResetToDefault, m_commandLineTable, &CommandLineTable::resetToDefault);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CommandLine::changeTheme);

	connect(m_commandLineTable, &CommandLineTable::setRemoveBtnDisabled, this, &CommandLine::setRemoveBtnDisabled);
	connect(m_addCommandLineDialog, &AddCommandLineDialog::addCommandLine, m_commandLineTable, &CommandLineTable::AddCommandLineFromDialog);

}

CommandLine::~CommandLine()
{
}

void CommandLine::addButtonClicked()
{
	QRect geometry = AppSetting::getInstance()->getAppGeometry();
	transparent->showWidget();
	m_addCommandLineDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 190 /*190 is half width*/, geometry.y() + 16, 380, 244);
	m_addCommandLineDialog->showDialog();
	transparent->hide();
}

void CommandLine::removeButtonClicked()
{
}

void CommandLine::resetToDefaultClicked()
{
}

void CommandLine::changeTheme()
{
	setStyle();
}

void CommandLine::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		setRemoveBtnStyle();

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:

		setRemoveBtnStyle();

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void CommandLine::setRemoveBtnStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if (m_removeBtn->isEnabled())
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		}
		else
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_LT + ";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_LT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

	case Theme_Type::Dark_Theme:

		if (m_removeBtn->isEnabled())
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		}
		else
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_DT + ";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_DT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

		//MORE THEME
	default:
		break;
	}
}

void CommandLine::setRemoveBtnDisabled(bool disabled)
{
	m_removeBtn->setDisabled(disabled);
	setRemoveBtnStyle();
}