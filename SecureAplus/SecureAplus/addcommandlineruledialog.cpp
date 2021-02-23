#include "addcommandlineruledialog.h"

AddnEditCmdLineRuleDialog::AddnEditCmdLineRuleDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);

	setFixedSize(380, 372);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(23, 23, 23, 0);
	m_layout->setSpacing(0);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(20);
	m_titleText->setFont(LARGE_FONT);

	QLabel* titleSpacer = new QLabel();
	titleSpacer->setFixedHeight(20);

	m_processWg = new QWidget();
	m_processWg->setFixedHeight(30);

	QHBoxLayout* processLayout = new QHBoxLayout();
	processLayout->setContentsMargins(10, 0, 10, 0);
	processLayout->setSpacing(0);
	m_processWg->setLayout(processLayout);

	m_process = new QLineEdit();
	m_process->setFont(FONT);
	m_process->setFixedHeight(30);
	m_process->setPlaceholderText("Input Command Line");
	processLayout->addWidget(m_process);

	m_paramText = new QLabel();
	m_paramText->setFixedHeight(20);
	m_paramText->setFont(FONT);
	m_paramText->setText("Parameters");

	m_ruleCbb = new SAPCombobox();
	m_ruleCbb->setFixedHeight(30);
	m_ruleCbb->setBackgroundColor(DIALOG_TEXBOX_DT, DIALOG_TEXBOX_LT);

	m_cmdRuleList.append("Exactly match");
	m_cmdRuleList.append("Starts with");
	m_cmdRuleList.append("Contains");
	m_ruleCbb->addItem("Exactly match");
	m_ruleCbb->addItem("Starts with");
	m_ruleCbb->addItem("Contains");

	m_caseSensCbb = new SAPCombobox();
	m_caseSensCbb->setFixedHeight(30);
	m_caseSensCbb->setBackgroundColor(DIALOG_TEXBOX_DT, DIALOG_TEXBOX_LT);

	m_sensitiveList.append("Case sensitive");
	m_sensitiveList.append("Case insensitive");
	m_caseSensCbb->addItem("Case sensitive");
	m_caseSensCbb->addItem("Case insensitive");

	m_stringWg = new QWidget();
	m_stringWg->setFixedHeight(30);

	QHBoxLayout* stringLayout = new QHBoxLayout();
	stringLayout->setContentsMargins(10, 0, 10, 0);
	stringLayout->setSpacing(0);
	m_stringWg->setLayout(stringLayout);

	m_string = new QLineEdit();
	m_string->setFont(FONT);
	m_string->setFixedHeight(30);
	m_string->setPlaceholderText("Input string");
	stringLayout->addWidget(m_string);

	m_actionCbb = new SAPCombobox();
	m_actionCbb->setFixedHeight(30);
	m_actionCbb->setBackgroundColor(DIALOG_TEXBOX_DT, DIALOG_TEXBOX_LT);

	m_actionList.append("Always block.");
	m_actionList.append("Let trusted userdecide.");
	m_actionList.append("Never trust  permanently.");

	m_actionCbb->addItem("Always block.");
	m_actionCbb->addItem("Let trusted userdecide.");
	m_actionCbb->addItem("Never trust  permanently.");

	QWidget* buttonWg = new QWidget();
	buttonWg->setFixedHeight(30);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);
	buttonWg->setLayout(buttonLayout);

	QLabel* btnLeftSpacer = new QLabel();

	m_cancelBtn = new QPushButton();
	m_cancelBtn->setFixedSize(80, 30);
	m_cancelBtn->setFont(FONT);
	m_cancelBtn->setText("Cancel");

	QLabel* centerBtnSpacer = new QLabel();
	centerBtnSpacer->setFixedWidth(8);

	m_addnSaveBtn = new QPushButton();
	m_addnSaveBtn->setFixedSize(80, 30);
	m_addnSaveBtn->setFont(FONT);


	m_addnSaveBtn->setEnabled(false);

	buttonLayout->addWidget(btnLeftSpacer);
	buttonLayout->addWidget(m_cancelBtn);
	buttonLayout->addWidget(centerBtnSpacer);
	buttonLayout->addWidget(m_addnSaveBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_titleText);
	m_layout->insertSpacing(1, 20);
	m_layout->addWidget(m_processWg);
	m_layout->insertSpacing(3, 10);
	m_layout->addWidget(m_paramText);
	m_layout->insertSpacing(5, 10);
	m_layout->addWidget(m_ruleCbb);
	m_layout->insertSpacing(7, 10);
	m_layout->addWidget(m_caseSensCbb);
	m_layout->insertSpacing(9, 10);
	m_layout->addWidget(m_stringWg);
	m_layout->insertSpacing(11, 30);
	m_layout->addWidget(m_actionCbb);
	m_layout->insertSpacing(13, 24);
	m_layout->addWidget(buttonWg);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);
	setStyle();
	setAddBtnStyle();

	connect(m_cancelBtn, &QPushButton::clicked, this, &AddnEditCmdLineRuleDialog::cancelClicked);
	connect(m_addnSaveBtn, &QPushButton::clicked, this, &AddnEditCmdLineRuleDialog::addnSaveClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &AddnEditCmdLineRuleDialog::changeTheme);
	connect(m_process, &QLineEdit::textChanged, this, &AddnEditCmdLineRuleDialog::textChanged);
	connect(m_string, &QLineEdit::textChanged, this, &AddnEditCmdLineRuleDialog::textChanged);
	connect(m_ruleCbb, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxChangeIndex(int)));
	connect(m_caseSensCbb, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxChangeIndex(int)));
	connect(m_actionCbb, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxChangeIndex(int)));
}

AddnEditCmdLineRuleDialog::~AddnEditCmdLineRuleDialog()
{
}

void AddnEditCmdLineRuleDialog::showDialog(bool isEdit)
{
	if (!isEdit)
	{
		m_process->clear();
		m_string->clear();
	}

	m_addnSaveBtn->setEnabled(false);
	m_isEdit = isEdit;
	m_isEdit == true ? m_titleText->setText("Edit Command Line Rules") : m_titleText->setText("Add Command Line Rules");
	m_isEdit == true ? m_addnSaveBtn->setText("Save") : m_addnSaveBtn->setText("Add");
	setAddBtnStyle();
	activateWindow();
	raise();
	exec();

}

void AddnEditCmdLineRuleDialog::setEditInfo(CommandLineRuleString & cmdRuleStr)
{
	int index;

	m_process->setText(cmdRuleStr.processStr);
	index = m_ruleCbb->findText(cmdRuleStr.ruleStr);
	m_ruleCbb->setCurrentIndex(index);
	index = m_caseSensCbb->findText(cmdRuleStr.caseSensitiveStr);
	m_caseSensCbb->setCurrentIndex(index);
	m_string->setText(cmdRuleStr.string);
	index = m_actionCbb->findText(cmdRuleStr.actionStr);
	m_actionCbb->setCurrentIndex(index);
}

void AddnEditCmdLineRuleDialog::cancelClicked()
{
	this->close();
}

void AddnEditCmdLineRuleDialog::addnSaveClicked()
{
	CommandLineRuleString cmdLineRuleStr;
	cmdLineRuleStr.processStr = m_process->text();
	cmdLineRuleStr.ruleStr = m_ruleCbb->currentText();
	cmdLineRuleStr.caseSensitiveStr = m_caseSensCbb->currentText();
	cmdLineRuleStr.string = m_string->text();
	cmdLineRuleStr.actionStr = m_actionCbb->currentText();

	if (!m_isEdit)
	{
		emit addCmdLineRule(cmdLineRuleStr);
	}
	else
	{
		emit editCmdLineRule(cmdLineRuleStr);
	}
	this->close();
}

void AddnEditCmdLineRuleDialog::changeTheme()
{
	setStyle();
	setAddBtnStyle();
}

void AddnEditCmdLineRuleDialog::textChanged()
{
	if (m_isEdit)
	{
		if (m_process->text() == "" || m_string->text() == "")
		{
			m_addnSaveBtn->setEnabled(false);
		}
		else
		{
			m_addnSaveBtn->setEnabled(true);

		}
	}
	else
	{
		if (m_process->text() != "" && m_string->text()!= "" )
		{
			m_addnSaveBtn->setEnabled(true);
		}
		else
		{
			m_addnSaveBtn->setEnabled(false);
		}
	}

	setAddBtnStyle();

}

void AddnEditCmdLineRuleDialog::comboboxChangeIndex(int)
{
	if (m_isEdit)
	{
		m_addnSaveBtn->setEnabled(true);
		setAddBtnStyle();
	}
}

void AddnEditCmdLineRuleDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("QDialog{background-color: " + DIALOG_BACKGROUND_DT + ";}");

		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_processWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

		m_process->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_paramText->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_stringWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

		m_string->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");


		break;

	case Theme_Type::Light_Theme:

		this->setStyleSheet("QDialog{background-color: " + DIALOG_BACKGROUND_LT + ";}");

		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_processWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

		m_process->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

		m_paramText->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

		m_stringWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

		m_string->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");
		break;

		/* MORE THEME */
	default:
		break;
	}
}

void AddnEditCmdLineRuleDialog::setAddBtnStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if (m_addnSaveBtn->isEnabled())
		{
			m_addnSaveBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
				"color: " + DIALOG_BUTTON_TEXT_LT + ";"
				"border-radius:4px;}");
		}
		else
		{
			m_addnSaveBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BACKGROUND_DISABLE_LT + ";"
				"color: " + DIALOG_BUTTON_TEXT_DISABLE_LT + ";"
				"border-radius:4px;"
				"border:none;}");
		}
		break;

	case Theme_Type::Dark_Theme:

		if (m_addnSaveBtn->isEnabled())
		{
			m_addnSaveBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
				"color: " + DIALOG_BUTTON_TEXT_DT + ";"
				"border-radius:4px;}");
		}
		else
		{
			m_addnSaveBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BACKGROUND_DISABLE_DT + ";"
				"color: " + DIALOG_BUTTON_TEXT_DISABLE_DT + ";"
				"border-radius:4px;"
				"border:none;}");
		}
		break;

		//MORE THEME
	default:
		break;
	}

}
