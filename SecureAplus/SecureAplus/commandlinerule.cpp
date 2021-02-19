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
	
	QLabel* resetBtnSpacer = new QLabel();
	resetBtnSpacer->setFixedWidth(25);

	m_refreshBtn = new RefreshButton();
	m_refreshBtn->setFixedSize(16, 16);

	QLabel* centerBtnsSpacer = new QLabel();

	m_removeBtn = new QPushButton();
	m_removeBtn->setFixedSize(80, 30);
	m_removeBtn->setFont(FONT);
	m_removeBtn->setText("Remove");
	m_removeBtn->setDisabled(true);

	QLabel* btnsSpacer = new QLabel();
	btnsSpacer->setFixedWidth(8);

	m_editBtn = new QPushButton();
	m_editBtn->setFixedSize(80, 30);
	m_editBtn->setFont(FONT);
	m_editBtn->setText("Edit");
	m_editBtn->setDisabled(true);

	QLabel* editBtnSpacer = new QLabel();
	editBtnSpacer->setFixedWidth(8);

	m_addBtn = new QPushButton();
	m_addBtn->setFixedSize(80, 30);
	m_addBtn->setFont(FONT);
	m_addBtn->setText("Add");

	btnsLayout->addWidget(m_resetBtn);
	btnsLayout->addWidget(resetBtnSpacer);
	btnsLayout->addWidget(m_refreshBtn);
	btnsLayout->addWidget(centerBtnsSpacer);
	btnsLayout->addWidget(m_removeBtn);
	btnsLayout->addWidget(btnsSpacer);
	btnsLayout->addWidget(m_editBtn);
	btnsLayout->addWidget(editBtnSpacer);
	btnsLayout->addWidget(m_addBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_commandLineRuleDesc);
	m_layout->addWidget(descSpacer);
	m_layout->addWidget(m_commandLineRuleTable);
	m_layout->addWidget(bottomTableSpacer);
	m_layout->addWidget(bottomBtns);
	m_layout->addWidget(bottomSpacer);

	transparent = new WidgetTransparent();
	m_addnEditcmdLineRuleDlg = new AddnEditCmdLineRuleDialog();

	setLayout(m_layout);
	setStyle();

	connect(m_removeBtn, &QPushButton::clicked, m_commandLineRuleTable, &CommandLineRuleTable::removeRows);
	connect(m_removeBtn, &QPushButton::clicked, this, &CommandLineRule::removeButtonClicked);

	connect(m_addBtn, &QPushButton::clicked, this, &CommandLineRule::addButtonClicked);
	connect(m_editBtn, &QPushButton::clicked, this, &CommandLineRule::editButtonClicked);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CommandLineRule::changeTheme, Qt::ConnectionType::DirectConnection);

	connect(m_commandLineRuleTable, &CommandLineRuleTable::setRemoveBtnDisabled, this, &CommandLineRule::setRemoveBtnDisabled);
	connect(m_commandLineRuleTable, &CommandLineRuleTable::setEditBtnDisabled, this, &CommandLineRule::setEditBtnDisabled);
	connect(m_addnEditcmdLineRuleDlg, &AddnEditCmdLineRuleDialog::addCmdLineRule, m_commandLineRuleTable, &CommandLineRuleTable::AddCommandLineRuleFromDialog);
	connect(m_addnEditcmdLineRuleDlg, &AddnEditCmdLineRuleDialog::editCmdLineRule, m_commandLineRuleTable, &CommandLineRuleTable::editCommandLineRule);

	connect(m_resetBtn, &ResetButton::clicked, this, &CommandLineRule::resetToDefaultClicked);
	connect(m_resetBtn, &ResetButton::signalResetToDefault, m_commandLineRuleTable, &CommandLineRuleTable::resetToDefault);
}

CommandLineRule::~CommandLineRule()
{
}

void CommandLineRule::removeButtonClicked()
{
}

void CommandLineRule::addButtonClicked()
{
	QRect geometry = AppSetting::getInstance()->getAppGeometry();
	transparent->showWidget();
	m_addnEditcmdLineRuleDlg->setGeometry(geometry.x() + (geometry.width() / 2) - 190 /*190 is half width*/, geometry.y() + 16, 380, 372);
	m_addnEditcmdLineRuleDlg->showDialog(false);
	transparent->hide();
}

void CommandLineRule::editButtonClicked()
{
	QRect geometry = AppSetting::getInstance()->getAppGeometry();
	transparent->showWidget();
	m_addnEditcmdLineRuleDlg->setGeometry(geometry.x() + (geometry.width() / 2) - 190 /*190 is half width*/, geometry.y() + 16, 380, 372);
	m_addnEditcmdLineRuleDlg->setEditInfo(m_commandLineRuleTable->getEditCmdLineRuleInfo());
	m_addnEditcmdLineRuleDlg->showDialog(true);
	transparent->hide();
}

void CommandLineRule::resetToDefaultClicked()
{
}

void CommandLineRule::setEditBtnDisabled(bool disabled)
{
	m_editBtn->setDisabled(disabled);
	setEditBtnStyle();
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
		setEditBtnStyle();
		m_commandLineRuleDesc->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:

		m_commandLineRuleDesc->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");

		setRemoveBtnStyle();
		setEditBtnStyle();
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

void CommandLineRule::setEditBtnStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if (m_editBtn->isEnabled())
		{
			m_editBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		}
		else
		{
			m_editBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_LT + ";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_LT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

	case Theme_Type::Dark_Theme:

		if (m_editBtn->isEnabled())
		{
			m_editBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		}
		else
		{
			m_editBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_DT + ";"
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
