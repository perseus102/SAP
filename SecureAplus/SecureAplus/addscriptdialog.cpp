#include "addscriptdialog.h"

AddScriptDialog::AddScriptDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);

	setFixedSize(380, 300);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(23, 23, 23, 0);
	m_layout->setSpacing(0);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(15);
	m_titleText->setWordWrap(true);
	m_titleText->setFont(LARGE_FONT);
	m_titleText->setText("Add Script");

	QLabel* titleSpacer = new QLabel();
	titleSpacer->setFixedHeight(5);

	m_scriptInterpreter = new QLabel();
	m_scriptInterpreter->setFixedHeight(15);
	m_scriptInterpreter->setWordWrap(true);
	m_scriptInterpreter->setFont(FONT);
	m_scriptInterpreter->setText("Script interpreter");

	QLabel* InterpreterSpacer = new QLabel();
	InterpreterSpacer->setFixedHeight(10);

	m_filePathWg = new QWidget();
	m_filePathWg->setFixedHeight(30);

	QHBoxLayout* fileNameLayout = new QHBoxLayout();
	fileNameLayout->setContentsMargins(18, 0, 18, 0);
	fileNameLayout->setSpacing(0);
	m_filePathWg->setLayout(fileNameLayout);

	m_filePath = new QLineEdit(this);
	m_filePath->setFont(FONT);
	m_filePath->setFixedHeight(30);
	m_filePath->setPlaceholderText("Enter file name without path or full path");
	
	fileNameLayout->addWidget(m_filePath);

	QLabel* filePathSpacer = new QLabel();
	titleSpacer->setFixedHeight(20);

	m_fileExtensions = new QLabel();
	m_fileExtensions->setFixedHeight(15);
	m_fileExtensions->setWordWrap(true);
	m_fileExtensions->setFont(FONT);
	m_fileExtensions->setText("File extensions");

	QLabel *extSpacer = new QLabel();
	extSpacer->setFixedHeight(10);

	m_fileExtensionsDesc = new QLabel();
	m_fileExtensionsDesc->setFixedHeight(30);
	m_fileExtensionsDesc->setWordWrap(true);
	m_fileExtensionsDesc->setFont(FONT);
	m_fileExtensionsDesc->setText("To enter multiple extensions, please separate them using |, for example: .exe| .dll| .sys. Use * to include all extionsions");

	QLabel *extDescSpacer = new QLabel();
	extDescSpacer->setFixedHeight(12);

	m_fileExtWg = new QWidget();
	m_fileExtWg->setFixedHeight(30);

	QHBoxLayout* fileExtLayout = new QHBoxLayout();
	fileExtLayout->setContentsMargins(18, 0, 18, 0);
	fileExtLayout->setSpacing(0);
	m_fileExtWg->setLayout(fileExtLayout);

	m_fileExtensionEdit = new QLineEdit(this);
	m_fileExtensionEdit->setFont(FONT);
	m_fileExtensionEdit->setFixedHeight(30);
	m_fileExtensionEdit->setPlaceholderText("File extension");

	fileExtLayout->addWidget(m_fileExtensionEdit);

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

	m_layout->addWidget(m_titleText);
	m_layout->addWidget(titleSpacer);
	m_layout->addWidget(m_scriptInterpreter);
	m_layout->addWidget(InterpreterSpacer);
	m_layout->addWidget(m_filePathWg);
	m_layout->addWidget(filePathSpacer);
	m_layout->addWidget(m_fileExtensions);
	m_layout->addWidget(extSpacer);
	m_layout->addWidget(m_fileExtensionsDesc);
	m_layout->addWidget(extDescSpacer);
	m_layout->addWidget(m_fileExtWg);
	m_layout->addWidget(buttonSpacer);
	m_layout->addWidget(buttonWg);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);

	setStyle();
	setAddBtnStyle();

	connect(m_cancelBtn, &QPushButton::clicked, this, &AddScriptDialog::cancelClicked);
	connect(m_addFileBtn, &QPushButton::clicked, this, &AddScriptDialog::addFileClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &AddScriptDialog::changeTheme);
	connect(m_filePath, &QLineEdit::textChanged, this, &AddScriptDialog::textChange);
	connect(m_fileExtensionEdit, &QLineEdit::textChanged, this, &AddScriptDialog::textChange);

}

AddScriptDialog::~AddScriptDialog()
{
}

void AddScriptDialog::showDialog()
{
	m_addFileBtn->setEnabled(false);
	setAddBtnStyle();
	m_filePath->setText("");
	m_fileExtensionEdit->setText("");
	activateWindow();
	raise();
	exec();
}

void AddScriptDialog::addFileClicked()
{
	emit addScript(m_filePath->text(), m_fileExtensionEdit->text());
	this->close();
}

void AddScriptDialog::cancelClicked()
{
	this->close();
}

void AddScriptDialog::changeTheme()
{
	setStyle();
}

void AddScriptDialog::textChange(QString text)
{
	if (m_filePath->text() == "" || m_fileExtensionEdit->text() == "")
	{
		m_addFileBtn->setEnabled(false);
	}
	else
	{
		m_addFileBtn->setEnabled(true);

	}

	setAddBtnStyle();
}

void AddScriptDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");

		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_scriptInterpreter->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_filePathWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

		m_filePath->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_fileExtensions->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_fileExtensionsDesc->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_fileExtWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

		m_fileExtensionEdit->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");


		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");

		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_scriptInterpreter->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_filePathWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

		m_filePath->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

		m_fileExtensions->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_fileExtensionsDesc->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

		m_fileExtWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

		m_fileExtensionEdit->setStyleSheet("border:none; color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");
		break;

		/* MORE THEME */
	default:
		break;
	}
}

void AddScriptDialog::setAddBtnStyle()
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
