#include "addprocessprotectordialog.h"

AddProcessProtectorDialog::AddProcessProtectorDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);

	setFixedSize(380, 195);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 30, 30, 0);
	m_layout->setSpacing(0);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(15);
	m_titleText->setWordWrap(true);
	m_titleText->setFont(LARGE_FONT);
	m_titleText->setText("Add Process Projector");

	QLabel* titleSpacer = new QLabel();
	titleSpacer->setFixedHeight(10);

	m_descText = new QLabel();
	m_descText->setFixedHeight(30);
	m_descText->setWordWrap(true);
	m_descText->setFont(FONT);
	m_descText->setText("Enter either file name only (e.g notepad.exe) or full path name (e.g. c:\\window\\notepad.exe)");

	QLabel* decsSpacer = new QLabel();
	decsSpacer->setFixedHeight(10);

	m_processWg = new QWidget();
	m_processWg->setFixedHeight(30);

	QHBoxLayout* processLayout = new QHBoxLayout();
	processLayout->setContentsMargins(18, 0, 18, 0);
	processLayout->setSpacing(0);
	m_processWg->setLayout(processLayout);

	m_processLabel = new QLineEdit(this);
	m_processLabel->setFont(FONT);
	m_processLabel->setFixedHeight(30);
	m_processLabel->setPlaceholderText("File name or file path");

	processLayout->addWidget(m_processLabel);

	QLabel* textBoxSpacer = new QLabel();
	textBoxSpacer->setFixedHeight(20);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);

	QWidget* buttonWidget = new QWidget();
	buttonWidget->setFixedHeight(30);
	buttonWidget->setLayout(buttonLayout);

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
	m_layout->addWidget(m_descText);
	m_layout->addWidget(decsSpacer);
	m_layout->addWidget(m_processWg);
	m_layout->addWidget(textBoxSpacer);
	m_layout->addWidget(buttonWidget);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);

	setStyle();
	setAddBtnStyle();

	connect(m_cancelBtn, &QPushButton::clicked, this, &AddProcessProtectorDialog::cancelClicked);
	connect(m_addFileBtn, &QPushButton::clicked, this, &AddProcessProtectorDialog::addClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &AddProcessProtectorDialog::changeTheme);
	connect(m_processLabel, &QLineEdit::textChanged, this, &AddProcessProtectorDialog::textChange);


}

AddProcessProtectorDialog::~AddProcessProtectorDialog()
{
}

void AddProcessProtectorDialog::showDialog()
{
	m_addFileBtn->setEnabled(false);
	setAddBtnStyle();
	m_processLabel->setText("");
	activateWindow();
	raise();
	exec();
}

void AddProcessProtectorDialog::addClicked()
{
	if (m_processLabel->text() != "")
	{
		emit addProcess(m_processLabel->text());
	}
	this->close();
}

void AddProcessProtectorDialog::changeTheme()
{
	setStyle();
}

void AddProcessProtectorDialog::textChange(QString text)
{
	if (text == "")
	{
		m_addFileBtn->setEnabled(false);
	}
	else
	{
		m_addFileBtn->setEnabled(true);

	}
	setAddBtnStyle();
}

void AddProcessProtectorDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");
		
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_descText->setStyleSheet("color: " + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_processWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");

		/*m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
			"color: " + DIALOG_BUTTON_TEXT_DT + ";"
			"border-radius:4px;}");*/

		m_processLabel->setStyleSheet("border:none;"
			"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");
		
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");
		
		m_descText->setStyleSheet("color: " + TAB_CONTENT_DESC_TEXT_LT + ";");
	
		m_processWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");

		/*m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
			"color: " + DIALOG_BUTTON_TEXT_LT + ";"
			"border-radius:4px;}");*/

		m_processLabel->setStyleSheet("border:none;"
			"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");
		break;

		/* MORE THEME */
	default:
		break;
	}
}

void AddProcessProtectorDialog::setAddBtnStyle()
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

void AddProcessProtectorDialog::cancelClicked()
{
	this->close();
}
