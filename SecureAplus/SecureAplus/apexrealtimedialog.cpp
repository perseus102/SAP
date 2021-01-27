#include "apexrealtimedialog.h"

APEXRealTimeDialog::APEXRealTimeDialog(QWidget *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);
	setFixedSize(440, 190);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 30, 30, 30);
	m_layout->setSpacing(30);
	m_titleText = new QLabel();
	m_titleText->setFixedHeight(72);
	m_titleText->setWordWrap(true);
	m_titleText->setFont(SMALL_FONT);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);

	QWidget* buttonWidget = new QWidget();
	buttonWidget->setFixedHeight(50);
	buttonWidget->setLayout(buttonLayout);

	QLabel* leftSpacer = new QLabel();
	leftSpacer->setFixedWidth(200);

	m_noBtn = new QPushButton();
	m_noBtn->setFixedSize(80, 30);
	m_noBtn->setFont(FONT);
	setNoBtnText("No"); //call function get text multi language

	m_yesBtn = new QPushButton();
	m_yesBtn->setFixedSize(80, 30);
	m_yesBtn->setFont(FONT);
	setYesBtnText("Yes"); //call function get text multi language

	buttonLayout->addWidget(leftSpacer);
	buttonLayout->addWidget(m_noBtn);
	buttonLayout->addWidget(m_yesBtn);

	m_layout->addWidget(m_titleText);
	m_layout->addWidget(buttonWidget);

	setTitleText("Change your mode to Lockdown\n\n"
		"Turn of APEX real - time scanning will also turn off Universal AV real time scanning and put SecureAPlus to LockDown mode");

	setLayout(m_layout);

	setStyle();

	connect(m_noBtn, &QPushButton::clicked, this, &APEXRealTimeDialog::NoBtnClicked);
	connect(m_yesBtn, &QPushButton::clicked, this, &APEXRealTimeDialog::YesBtnClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &APEXRealTimeDialog::changeTheme);
}

APEXRealTimeDialog::~APEXRealTimeDialog()
{
}

void APEXRealTimeDialog::showDialog()
{
	m_buttonCode = QDialog::Rejected;
	activateWindow();
	raise();
	exec();
}

void APEXRealTimeDialog::setTitleText(QString text)
{
	m_titleText->setText(text);
}

void APEXRealTimeDialog::setNoBtnText(QString text)
{
	m_noBtn->setText(text);
}

void APEXRealTimeDialog::setYesBtnText(QString text)
{
	m_yesBtn->setText(text);
}

QDialog::DialogCode APEXRealTimeDialog::getBtnClicked()
{
	return m_buttonCode;
}

void APEXRealTimeDialog::YesBtnClicked()
{
	m_buttonCode = QDialog::Accepted;
	this->close();
}
void APEXRealTimeDialog::NoBtnClicked()
{
	m_buttonCode = QDialog::Rejected;
	this->close();
}

void APEXRealTimeDialog::changeTheme()
{
	setStyle();
}

void APEXRealTimeDialog::setStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_noBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");

		m_yesBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
			"color: " + DIALOG_BUTTON_TEXT_DT + ";"
			"border-radius:4px;}");

		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_noBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");

		m_yesBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
			"color: " + DIALOG_BUTTON_TEXT_LT + ";"
			"border-radius:4px;}");

		break;

		/* MORE THEME */
	default:
		break;
	}

}
