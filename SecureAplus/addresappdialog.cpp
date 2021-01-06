#include "addresappdialog.h"

AddResAppDialog::AddResAppDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);
	setFixedSize(380, 170);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 30, 30, 0);
	m_layout->setSpacing(0);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(15);
	m_titleText->setWordWrap(true);
	m_titleText->setFont(FONT);
	m_titleText->setText("ADD RESTRICTED APPLICATION");

	QLabel* titleSpacer = new QLabel();
	titleSpacer->setFixedHeight(5);
	
	m_fileNameWg = new QWidget();
	m_fileNameWg->setFixedHeight(30);
	
	QHBoxLayout* fileNameLayout = new QHBoxLayout();
	fileNameLayout->setContentsMargins(18, 0, 18, 0);
	fileNameLayout->setSpacing(0);
	m_fileNameWg->setLayout(fileNameLayout);

	m_fileNameLabel = new QLineEdit(this);
	m_fileNameLabel->setFont(FONT);
	m_fileNameLabel->setFixedHeight(30);
	m_fileNameLabel->setPlaceholderText("File name or file path");

	fileNameLayout->addWidget(m_fileNameLabel);

	QLabel* textBoxSpacer = new QLabel();
	titleSpacer->setFixedHeight(22);

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

	buttonLayout->addWidget(btnLeftSpacer);
	buttonLayout->addWidget(m_cancelBtn);
	buttonLayout->addWidget(centerBtnSpacer);
	buttonLayout->addWidget(m_addFileBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_titleText);
	m_layout->addWidget(titleSpacer);
	m_layout->addWidget(m_fileNameWg);
	m_layout->addWidget(textBoxSpacer);
	m_layout->addWidget(buttonWidget);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);

	setStyle();

	connect(m_cancelBtn, &QPushButton::clicked, this, &AddResAppDialog::cancelClicked);
	connect(m_addFileBtn, &QPushButton::clicked, this, &AddResAppDialog::addFileClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &AddResAppDialog::changeTheme);
}

AddResAppDialog::~AddResAppDialog()
{
}

void AddResAppDialog::cancelClicked()
{
	this->close();
}

void AddResAppDialog::addFileClicked()
{
	if (m_fileNameLabel->text() != "")
	{
		emit addFile(m_fileNameLabel->text());
	}
	this->close();
}

void AddResAppDialog::setStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_fileNameWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");

		m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
			"color: " + DIALOG_BUTTON_TEXT_DT + ";"
			"border-radius:4px;}");

		m_fileNameLabel->setStyleSheet("border:none;"
			"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_fileNameWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");

		m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
			"color: " + DIALOG_BUTTON_TEXT_LT + ";"
			"border-radius:4px;}");

		m_fileNameLabel->setStyleSheet("border:none;"
			"color:"+ TAB_CONTENT_DESC_TEXT_LT +";");
		break;

		/* MORE THEME */
	default:
		break;
	}
}

void AddResAppDialog::changeTheme()
{
	setStyle();
}

void AddResAppDialog::showDialog()
{
	m_fileNameLabel->setText("");
	activateWindow();
	raise();
	exec();
}