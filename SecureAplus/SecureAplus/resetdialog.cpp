#include "resetdialog.h"

ResetDialog::ResetDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);

	setFixedSize(380, 174);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(23, 23, 23, 0);
	m_layout->setSpacing(0);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(15);
	m_titleText->setWordWrap(true);
	m_titleText->setFont(LARGE_FONT);
	m_titleText->setText("Reset to default");

	QLabel* titleSpacer = new QLabel();
	titleSpacer->setFixedHeight(20);

	m_decsText = new QLabel();
	m_decsText->setFixedHeight(30);
	m_decsText->setWordWrap(true);
	m_decsText->setFont(FONT);
	m_decsText->setText("Reset to default may change the action of current data. Would you like to continue?");

	QLabel *buttonSpacer = new QLabel();
	buttonSpacer->setFixedHeight(20);

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

	m_continueBtn = new QPushButton();
	m_continueBtn->setFixedSize(80, 30);
	m_continueBtn->setFont(FONT);
	m_continueBtn->setText("Continue");

	buttonLayout->addWidget(btnLeftSpacer);
	buttonLayout->addWidget(m_cancelBtn);
	buttonLayout->addWidget(centerBtnSpacer);
	buttonLayout->addWidget(m_continueBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_titleText);
	m_layout->addWidget(titleSpacer);
	m_layout->addWidget(m_decsText);
	m_layout->addWidget(buttonSpacer);
	m_layout->addWidget(buttonWg);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);
	setStyle();

	connect(m_cancelBtn, &QPushButton::clicked, this, &ResetDialog::cancelClicked);
	connect(m_continueBtn, &QPushButton::clicked, this, &ResetDialog::continueClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ResetDialog::changeTheme);


}

ResetDialog::~ResetDialog()
{
}

void ResetDialog::showDialog()
{
	activateWindow();
	raise();
	exec();
}

void ResetDialog::continueClicked()
{
	this->close();
	emit resetToDefault();
}

void ResetDialog::cancelClicked()
{
	this->close();
}

void ResetDialog::changeTheme()
{
	setStyle();
}

void ResetDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");

		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

		m_decsText->setStyleSheet("color: " + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");

		m_continueBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");

		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");

		m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

		m_decsText->setStyleSheet("color: " + TAB_CONTENT_DESC_TEXT_LT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");

		m_continueBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");
		break;

		/* MORE THEME */
	default:
		break;
	}
}

