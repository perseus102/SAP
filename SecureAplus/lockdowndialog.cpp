#include "lockdowndialog.h"
LockDownDialog::LockDownDialog(QDialog*parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);
	setFixedSize(440, 190);
	layout = new QVBoxLayout();
	layout->setContentsMargins(30, 30, 30, 30);
	layout->setSpacing(36);
	m_titleText		= new QLabel();
	m_titleText->setFixedHeight(72);
	m_titleText->setWordWrap(true);
	m_titleText->setFont(SMALL_FONT);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);

	QWidget* buttonWidget = new QWidget();
	buttonWidget->setLayout(buttonLayout);

	m_cancelBtn		= new QPushButton();
	m_cancelBtn->setFixedSize(70, 30);
	m_cancelBtn->setFont(SMALL_FONT);
	setCancelText("Cancel"); //call function get text multi language

	m_silentBtn		= new QPushButton();
	m_silentBtn->setFixedSize(92, 30);
	m_silentBtn->setFont(SMALL_FONT);
	setSilentText("Silent");//call function get text multi language

	m_DefaultBtn	= new QPushButton();
	m_DefaultBtn->setFixedSize(92, 30);
	m_DefaultBtn->setFont(SMALL_FONT);
	setDefaultText("Default");//call function get text multi language

	buttonLayout->addWidget(m_cancelBtn);
	buttonLayout->addWidget(m_silentBtn);
	buttonLayout->addWidget(m_DefaultBtn);

	buttonLayout->insertSpacing(1, 90);

	layout->addWidget(m_titleText);
	layout->addWidget(buttonWidget);

	setTitleText("Would you like to enable silent for Lockdown Mode?\n\n You will never get prompted by SecureAPlus.Untrusted applications will be automatically blockedand viruses detected by real - time scanning will be automatically quarantined.");
	setLayout(layout);

	setStyle();
	connect(m_cancelBtn, &QPushButton::clicked, this, &LockDownDialog::cancelClicked);
	connect(m_silentBtn, &QPushButton::clicked, this, &LockDownDialog::silentClicked);
	connect(m_DefaultBtn, &QPushButton::clicked, this, &LockDownDialog::defaultClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &LockDownDialog::changeTheme);
}

LockDownDialog::~LockDownDialog()
{
}

void LockDownDialog::setTitleText(QString text)
{
	m_titleText->setText(text);
}

void LockDownDialog::setCancelText(QString text)
{
	m_cancelBtn->setText(text);
}

void LockDownDialog::setSilentText(QString text)
{
	m_silentBtn->setText(text);
}

void LockDownDialog::setDefaultText(QString text)
{
	m_DefaultBtn->setText(text);
}

void LockDownDialog::showDialog()
{
	m_silentBtn->setVisible(true);
	m_DefaultBtn->setVisible(true);
	m_lockdownMode = LockDown::LOCKDOWN_CANCEL;
	activateWindow();
	raise();
	exec();
}

void LockDownDialog::showSilentDialog()
{
	m_silentBtn->setVisible(true);
	m_DefaultBtn->setVisible(false);
	activateWindow();
	raise();
	exec();
	if (m_lockdownMode == LockDown::LOCKDOWN_CANCEL)
	{
		m_lockdownMode = LockDown::LOCKDOWN_DEFAULT;
	}
}

void LockDownDialog::showDefaultDialog()
{
	m_silentBtn->setVisible(false);
	m_DefaultBtn->setVisible(true);
	activateWindow();
	raise();
	exec();
	if (m_lockdownMode == LockDown::LOCKDOWN_CANCEL)
	{
		m_lockdownMode = LockDown::LOCKDOWN_SILENT;
	}
}

LockDown LockDownDialog::getLockDownMode()
{
	return m_lockdownMode;
}

void LockDownDialog::cancelClicked()
{
	m_lockdownMode = LockDown::LOCKDOWN_CANCEL;
	this->close();
}

void LockDownDialog::silentClicked()
{
	m_lockdownMode = LockDown::LOCKDOWN_SILENT;
	this->close();
}

void LockDownDialog::defaultClicked()
{
	m_lockdownMode = LockDown::LOCKDOWN_DEFAULT;

	this->close();
}

void LockDownDialog::changeTheme()
{
	setStyle();
}

void LockDownDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");

		m_silentBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
			"color: " + DIALOG_BUTTON_TEXT_DT + ";"
			"border-radius:4px;}");

		m_DefaultBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
			"color: " + DIALOG_BUTTON_TEXT_DT + ";"
			"border-radius:4px;}");

		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");

		m_silentBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
			"color: " + DIALOG_BUTTON_TEXT_LT + ";"
			"border-radius:4px;}");

		m_DefaultBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
			"color: " + DIALOG_BUTTON_TEXT_LT + ";"
			"border-radius:4px;}");

		break;

		/* MORE THEME */
	default:
		break;
	}
}
