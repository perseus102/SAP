#include "addcommandlinedialog.h"

AddCommandLineDialog::AddCommandLineDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);

	setFixedSize(380, 244);

	m_cmdLayout = new QVBoxLayout();
	m_cmdLayout->setContentsMargins(23, 23, 23, 0);
	m_cmdLayout->setSpacing(0);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(20);
	m_titleText->setWordWrap(true);
	m_titleText->setFont(LARGE_FONT);
	m_titleText->setText("Add Command Line");

	QLabel* titleSpacer = new QLabel();
	titleSpacer->setFixedHeight(20);

	m_commandLine = new QTextEdit();
	m_commandLine->setFont(FONT);
	m_commandLine->setFixedHeight(100);
	m_commandLine->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_commandLine->setPlaceholderText("Input Command Line");

	QLabel *buttonSpacer = new QLabel();
	buttonSpacer->setFixedHeight(20);
	//
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);

	QWidget* buttonWg = new QWidget();
	buttonWg->setFixedHeight(30);
	buttonWg->setLayout(buttonLayout);

	QLabel* btnLeftSpacer = new QLabel();

	m_cancelBtn = new QPushButton();
	m_cancelBtn->setFixedSize(80, 30);
	m_cancelBtn->setFont(FONT);
	m_cancelBtn->setText("Cancel");

	QLabel* centerBtnSpacer = new QLabel();
	centerBtnSpacer->setFixedWidth(8);

	m_addFileBtn = new QPushButton();
	m_addFileBtn->setFixedSize(80, 30);
	m_addFileBtn->setFont(FONT);
	m_addFileBtn->setText("Add File");
	m_addFileBtn->setEnabled(false);

	buttonLayout->addWidget(btnLeftSpacer);
	buttonLayout->addWidget(m_cancelBtn);
	buttonLayout->addWidget(centerBtnSpacer);
	buttonLayout->addWidget(m_addFileBtn);

	QLabel* bottomSpacer = new QLabel();

	m_cmdLayout->addWidget(m_titleText);
	m_cmdLayout->addWidget(titleSpacer);
	m_cmdLayout->addWidget(m_commandLine);
	m_cmdLayout->addWidget(buttonSpacer);
	m_cmdLayout->addWidget(buttonWg);
	m_cmdLayout->addWidget(bottomSpacer);

	setLayout(m_cmdLayout);
	setStyle();
	setAddBtnStyle();

	connect(m_cancelBtn, &QPushButton::clicked, this, &AddCommandLineDialog::cancelClicked);
	connect(m_addFileBtn, &QPushButton::clicked, this, &AddCommandLineDialog::addFileClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &AddCommandLineDialog::changeTheme);
	connect(m_commandLine, &QTextEdit::textChanged, this, &AddCommandLineDialog::cmdTextChange);
}

AddCommandLineDialog::~AddCommandLineDialog()
{
}

void AddCommandLineDialog::showDialog()
{
	m_commandLine->clear();
	m_addFileBtn->setEnabled(false);
	setAddBtnStyle();
	activateWindow();
	raise();
	exec();
}

void AddCommandLineDialog::cancelClicked()
{
	this->close();
}

void AddCommandLineDialog::addFileClicked()
{
	emit addCommandLine(m_commandLine->toPlainText());
	this->close();
}

void AddCommandLineDialog::changeTheme()
{
	setStyle();
}

void AddCommandLineDialog::cmdTextChange()
{
	if (m_commandLine->toPlainText().isEmpty())
	{
		m_addFileBtn->setEnabled(false);
	}
	else
	{
		m_addFileBtn->setEnabled(true);

	}

	setAddBtnStyle();
}

void AddCommandLineDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");

		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_commandLine->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + "; border-radius:2px;"
			"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
		"padding-left:18px; padding-top:14px; padding-right:18px; padding-bottom:14px;");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");


		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");

		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_commandLine->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + "; border-radius:2px;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"padding-left:18px; padding-top:14px; padding-right:18px; padding-bottom:14px;");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");
		break;

		/* MORE THEME */
	default:
		break;
	}
}

void AddCommandLineDialog::setAddBtnStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if (m_addFileBtn->isEnabled())
		{
			m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
				"color: " + DIALOG_BUTTON_TEXT_LT + ";"
				"border-radius:4px;}");
		}
		else
		{
			m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BACKGROUND_DISABLE_LT + ";"
				"color: " + DIALOG_BUTTON_TEXT_DISABLE_LT + ";"
				"border-radius:4px;"
				"border:none;}");
		}
		break;

	case Theme_Type::Dark_Theme:

		if (m_addFileBtn->isEnabled())
		{
			m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
				"color: " + DIALOG_BUTTON_TEXT_DT + ";"
				"border-radius:4px;}");
		}
		else
		{
			m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BACKGROUND_DISABLE_DT + ";"
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
