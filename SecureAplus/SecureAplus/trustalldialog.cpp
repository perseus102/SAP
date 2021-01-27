#include "trustalldialog.h"

TrustAllDialog::TrustAllDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);

	/* Init main layout */
	setFixedSize(440, 170);
	layout = new QVBoxLayout();
	layout->setContentsMargins(35, 25, 35, 35);
	layout->setSpacing(0);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(20);
	m_titleText->setWordWrap(true);
	setTitleText("SecureAPlus will trust all threats for");  //call function get text multi language

	/* Init Radio Button */
	QHBoxLayout* radioButtonLayout = new QHBoxLayout();
	radioButtonLayout->setContentsMargins(0, 0, 0, 0);
	radioButtonLayout->setSpacing(0);

	QWidget* radioButtonWidget = new QWidget();
	radioButtonWidget->setLayout(radioButtonLayout);

	m_5minsRadioBtn = new QPushButton();
	m_5minsRadioBtn->setFixedSize(20, 20);

	m_30minsRadioBtn = new QPushButton();
	m_30minsRadioBtn->setFixedSize(20, 20);

	m_nextRebootRadioBtn = new QPushButton();
	m_nextRebootRadioBtn->setFixedSize(20, 20);

	m_5minsText = new ClickableLabel();
	m_5minsText->setFixedSize(57, 20);
	m_5minsText->setFont(SMALL_FONT);
	m_5minsText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	m_30minsText = new ClickableLabel();
	m_30minsText->setFixedSize(57, 20);
	m_30minsText->setFont(SMALL_FONT);
	m_30minsText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	m_nextRebootText = new ClickableLabel();
	m_nextRebootText->setFixedSize(97, 20);
	m_nextRebootText->setFont(SMALL_FONT);
	m_nextRebootText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QLabel* spacerRadio5Mins = new QLabel;
	spacerRadio5Mins->setFixedWidth(10);
	spacerRadio5MinsText = new QLabel;
	spacerRadio5MinsText->setFixedWidth(36);

	radioButtonLayout->addWidget(m_5minsRadioBtn);
	radioButtonLayout->addWidget(spacerRadio5Mins);
	radioButtonLayout->addWidget(m_5minsText);
	radioButtonLayout->addWidget(spacerRadio5MinsText);

	QLabel* spacerRadio30Mins = new QLabel;
	spacerRadio30Mins->setFixedWidth(10);
	spacerRadio30MinsText = new QLabel;
	spacerRadio30MinsText->setFixedWidth(36);

	radioButtonLayout->addWidget(m_30minsRadioBtn);
	radioButtonLayout->addWidget(spacerRadio30Mins);
	radioButtonLayout->addWidget(m_30minsText);
	radioButtonLayout->addWidget(spacerRadio30MinsText);

	spacerRadioNextReboot = new QLabel;
	spacerRadioNextReboot->setFixedWidth(10);

	radioButtonLayout->addWidget(m_nextRebootRadioBtn);
	radioButtonLayout->addWidget(spacerRadioNextReboot);
	radioButtonLayout->addWidget(m_nextRebootText);

	/* Init Dialog Button */
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);

	QWidget* buttonWidget = new QWidget();
	buttonWidget->setLayout(buttonLayout);

	m_cancelButton = new QPushButton();
	m_cancelButton->setFixedSize(70, 30);
	m_cancelButton->setFont(SMALL_FONT);

	m_applyButton = new QPushButton();
	m_applyButton->setFont(SMALL_FONT);
	m_applyButton->setFixedSize(70, 30);
	buttonLayout->addWidget(m_cancelButton);
	buttonLayout->addWidget(m_applyButton);
	buttonLayout->insertSpacing(0, 200);

	layout->addWidget(m_titleText);
	QLabel* spacerRadioTop = new QLabel;
	spacerRadioTop->setFixedHeight(18);
	layout->addWidget(spacerRadioTop);
	layout->addWidget(radioButtonWidget);
	QLabel* spacerRadioBottom = new QLabel;
	spacerRadioTop->setFixedHeight(18);
	layout->addWidget(spacerRadioBottom);
	layout->addWidget(buttonWidget);

	

	m_trustAllTime = TrustAllTime::TRUSTALL_5MINS;
	m_trustAll = TrustAll::TRUSTALL_CANCEL;
	setLayout(layout);
	setStyle();
	setButtonStyle();

	setFiveMinsText("5 minutes"); //call function get text multi language
	setThirtyMinsText("30 minutes"); //call function get text multi language
	setNextRebootMinsText("Until next reboot"); //call function get text multi language
	setCancelText("Cancel"); //call function get text multi language
	setApplyText("Apply"); //call function get text multi language

	connect(m_cancelButton, &QPushButton::clicked, this, &TrustAllDialog::cancelBtnClicked);
	connect(m_cancelButton, &QPushButton::clicked, this, &TrustAllDialog::cancelBtnClicked);
	connect(m_applyButton, &QPushButton::clicked, this, &TrustAllDialog::applyBtnClicked);
	connect(m_5minsRadioBtn, &QPushButton::clicked, this, &TrustAllDialog::fiveMinsClicked);
	connect(m_30minsRadioBtn, &QPushButton::clicked, this, &TrustAllDialog::thirtyMinsClicked);
	connect(m_nextRebootRadioBtn, &QPushButton::clicked, this, &TrustAllDialog::nextRebootClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &TrustAllDialog::changeTheme);
	connect(m_5minsText, &ClickableLabel::clicked, this, &TrustAllDialog::fiveMinsClicked);
	connect(m_30minsText, &ClickableLabel::clicked, this, &TrustAllDialog::thirtyMinsClicked);
	connect(m_nextRebootText, &ClickableLabel::clicked, this, &TrustAllDialog::nextRebootClicked);
}

TrustAllDialog::~TrustAllDialog()
{
}

void TrustAllDialog::setTitleText(QString text)
{
	m_titleText->setText(text);
}

void TrustAllDialog::setFiveMinsText(QString text)
{
	QFontMetrics fm(SMALL_FONT);
	int pixelsHigh = fm.height();
	int width = fm.width(text);
	m_5minsText->setFixedWidth(width);
	m_5minsText->setFixedHeight(pixelsHigh);
	m_5minsText->setText(text);
	spacerRadio5MinsText->setFixedWidth(57 - width + 36);
}

void TrustAllDialog::setThirtyMinsText(QString text)
{
	QFontMetrics fm(SMALL_FONT);
	int pixelsHigh = fm.height();
	int width = fm.width(text);
	m_30minsText->setFixedWidth(width);
	m_30minsText->setFixedHeight(pixelsHigh);
	m_30minsText->setText(text);
	spacerRadio30MinsText->setFixedWidth(57 - width + 36);

}

void TrustAllDialog::setNextRebootMinsText(QString text)
{
	QFontMetrics fm(SMALL_FONT);
	int pixelsHigh = fm.height();
	int width = fm.width(text);
	m_nextRebootText->setFixedWidth(width);
	m_nextRebootText->setFixedHeight(pixelsHigh);
	m_nextRebootText->setText(text);
}

void TrustAllDialog::setCancelText(QString text)
{
	m_cancelButton->setText(text);
}

void TrustAllDialog::setApplyText(QString text)
{
	m_applyButton->setText(text);
}

void TrustAllDialog::cancelBtnClicked()
{
	m_trustAll = TrustAll::TRUSTALL_CANCEL;
	this->close();
}
void TrustAllDialog::applyBtnClicked()
{
	m_trustAll = TrustAll::TRUSTALL_APPLY;
	this->close();
}

void TrustAllDialog::fiveMinsClicked()
{
	m_trustAllTime = TrustAllTime::TRUSTALL_5MINS;
	setButtonStyle();
}

void TrustAllDialog::thirtyMinsClicked()
{
	m_trustAllTime = TrustAllTime::TRUSTALL_30MINS;
	setButtonStyle();
}

void TrustAllDialog::nextRebootClicked()
{
	m_trustAllTime = TrustAllTime::TRUSTALL_NEXTREBOOT;
	setButtonStyle();
}

void TrustAllDialog::changeTheme()
{
	setStyle();
	setButtonStyle();
}

void TrustAllDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_cancelButton->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");

		m_applyButton->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
			"color: " + DIALOG_BUTTON_TEXT_DT + ";"
			"border-radius:4px;}");

		m_5minsText->setStyleSheet("QLabel {color: " + DIALOG_BUTTON_TEXT_DT + "}");
		m_30minsText->setStyleSheet("QLabel {color: " + DIALOG_BUTTON_TEXT_DT + "}");
		m_nextRebootText->setStyleSheet("QLabel {color: " + DIALOG_BUTTON_TEXT_DT + "}");

		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");
		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_cancelButton->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");

		m_applyButton->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
			"color: " + DIALOG_BUTTON_TEXT_LT + ";"
			"border-radius:4px;}");

		m_5minsText->setStyleSheet("QLabel {color: " + DIALOG_TITLE_TEXT_LT + "}");
		m_30minsText->setStyleSheet("QLabel {color: " + DIALOG_TITLE_TEXT_LT + "}");
		m_nextRebootText->setStyleSheet("QLabel {color: " + DIALOG_TITLE_TEXT_LT + "}");

		break;

		/* MORE THEME */
	default:
		break;
	}

}

void TrustAllDialog::setButtonStyle()
{
	QIcon active;
	QIcon unactive;

	m_5minsRadioBtn->setStyleSheet("QPushButton {border: 0px;}");
	m_30minsRadioBtn->setStyleSheet("QPushButton {border: 0px;}");
	m_nextRebootRadioBtn->setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		active.addFile(RING_SELECTED_LT);
		unactive.addFile(RING_UNSELECTED_LT);
		break;

	case Theme_Type::Dark_Theme:
		active.addFile(RING_SELECTED_DT);
		unactive.addFile(RING_UNSELECTED_DT);

		break;

		//MORE THEME
	default:
		break;
	}

	switch (m_trustAllTime)
		
	{
	case TrustAllTime::TRUSTALL_5MINS:
		m_5minsRadioBtn->setIcon(active);
		m_5minsRadioBtn->setIconSize(QSize(20, 20));

		m_30minsRadioBtn->setIcon(unactive);
		m_30minsRadioBtn->setIconSize(QSize(20, 20));

		m_nextRebootRadioBtn->setIcon(unactive);
		m_nextRebootRadioBtn->setIconSize(QSize(20, 20));
		break;
	case TrustAllTime::TRUSTALL_30MINS:
		m_5minsRadioBtn->setIcon(unactive);
		m_5minsRadioBtn->setIconSize(QSize(20, 20));

		m_30minsRadioBtn->setIcon(active);
		m_30minsRadioBtn->setIconSize(QSize(20, 20));

		m_nextRebootRadioBtn->setIcon(unactive);
		m_nextRebootRadioBtn->setIconSize(QSize(20, 20));
		break;
	case TrustAllTime::TRUSTALL_NEXTREBOOT:
		m_5minsRadioBtn->setIcon(unactive);
		m_5minsRadioBtn->setIconSize(QSize(20, 20));

		m_30minsRadioBtn->setIcon(unactive);
		m_30minsRadioBtn->setIconSize(QSize(20, 20));

		m_nextRebootRadioBtn->setIcon(active);
		m_nextRebootRadioBtn->setIconSize(QSize(20, 20));
		break;
	default:
		break;
	}
}

void TrustAllDialog::showDialog()
{
	m_trustAll = TrustAll::TRUSTALL_CANCEL;
	activateWindow();
	raise();
	exec();
}

TrustAll TrustAllDialog::getDialogButtonClicked()
{
	return m_trustAll;
}

TrustAllTime TrustAllDialog::getTrustAllTime()
{
	return m_trustAllTime;
}
