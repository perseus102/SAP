#include "commandlinerule.h"

CommandLineRule::CommandLineRule(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 0, 40, 10);
	m_layout->setSpacing(0);

	m_commandLineRuleDesc = new QLabel();
	m_commandLineRuleDesc->setFont(FONT);
	m_commandLineRuleDesc->setFixedHeight(60);
	m_commandLineRuleDesc->setWordWrap(true);
	m_commandLineRuleDesc->setText("Some malwares have the ability to inject their code into another process, and run as the infected process. The process in this list will be protected against such attack.");

	QLabel* descSpacer = new QLabel();
	descSpacer->setFixedHeight(15);

	m_commandLineRuleTable = new CommandLineRuleTable();

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

	m_layout->addWidget(m_commandLineRuleDesc);
	m_layout->addWidget(descSpacer);
	m_layout->addWidget(m_commandLineRuleTable);
	m_layout->addWidget(bottomTableSpacer);
	m_layout->addWidget(bottomBtns);
	m_layout->addWidget(bottomSpacer);

	transparent = new WidgetTransparent();

	setLayout(m_layout);
	setStyle();

	connect(m_removeBtn, &QPushButton::clicked, m_commandLineRuleTable, &CommandLineRuleTable::removeRows);
	connect(m_removeBtn, &QPushButton::clicked, this, &CommandLineRule::removeButtonClicked);

	connect(m_addBtn, &QPushButton::clicked, this, &CommandLineRule::addButtonClicked);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CommandLineRule::changeTheme, Qt::ConnectionType::DirectConnection);

	connect(m_commandLineRuleTable, &CommandLineRuleTable::setRemoveBtnDisabled, this, &CommandLineRule::setRemoveBtnDisabled);
	//connect(m_addProcessDialog, &AddProcessProtectorDialog::addProcess, m_processProtectorTable, &CommandLineRuleTable::AddProcessFromDialog);


}

CommandLineRule::~CommandLineRule()
{
}

void CommandLineRule::removeButtonClicked()
{
}

void CommandLineRule::addButtonClicked()
{
}

void CommandLineRule::resetToDefaultClicked()
{
}

void CommandLineRule::changeTheme()
{
	setStyle();
}

void CommandLineRule::setRemoveBtnDisabled(bool disabled)
{
	m_removeBtn->setDisabled(disabled);
	setRemoveBtnStyle();
}

void CommandLineRule::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		setRemoveBtnStyle();

		m_commandLineRuleDesc->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:

		m_commandLineRuleDesc->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");

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

void CommandLineRule::setRemoveBtnStyle()
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
