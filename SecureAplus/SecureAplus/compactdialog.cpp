#include "compactdialog.h"

CompactDialog::CompactDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);
	setFixedSize(380, 160);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(23, 23, 23, 0);
	m_layout->setSpacing(0);

	m_decsText = new QLabel();
	m_decsText->setFixedHeight(60);
	m_decsText->setWordWrap(true);
	m_decsText->setFont(FONT);
	m_decsText->setText("This operation will delete all allow list which no longer have physical files on the local hard disk(s). If you want to maintain your allow list from external drives, please do not proceed with this operation.");

	QLabel* titleSpacer = new QLabel();
	titleSpacer->setFixedHeight(20);

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

	m_startBtn = new QPushButton();
	m_startBtn->setFixedSize(80, 30);
	m_startBtn->setFont(FONT);
	m_startBtn->setText("Start");

	buttonLayout->addWidget(btnLeftSpacer);
	buttonLayout->addWidget(m_cancelBtn);
	buttonLayout->addWidget(centerBtnSpacer);
	buttonLayout->addWidget(m_startBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_decsText);
	m_layout->addWidget(titleSpacer);
	m_layout->addWidget(buttonWg);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);
	setStyle();
	connect(m_cancelBtn, &QPushButton::clicked, this, &CompactDialog::cancelBtnClicked);
	connect(m_startBtn, &QPushButton::clicked, this, &CompactDialog::startBtnClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CompactDialog::changeTheme);
}

CompactDialog::~CompactDialog()
{
}

void CompactDialog::showDialog()
{
	activateWindow();
	raise();
	exec();
}

void CompactDialog::cancelBtnClicked()
{
	this->close();
}

void CompactDialog::startBtnClicked()
{
	this->close();
	emit startCompactAllowList();
}

void CompactDialog::changeTheme()
{
	setStyle();
}

void CompactDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");

		m_decsText->setStyleSheet("color: " + TAB_CONTENT_DESC_TEXT_DT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");
		
		m_startBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
			"color: " + DIALOG_BUTTON_TEXT_LT + ";"
			"border-radius:4px;}");

		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");

		m_decsText->setStyleSheet("color: " + TAB_CONTENT_DESC_TEXT_LT + ";");

		m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
			"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
			"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");
		
		m_startBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
			"color: " + DIALOG_BUTTON_TEXT_DT + ";"
			"border-radius:4px;}");

		break;

		/* MORE THEME */
	default:
		break;
	}
}

