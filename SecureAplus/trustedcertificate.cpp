#include "trustedcertificate.h"

TrustedCertificate::TrustedCertificate(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 0, 30, 30);
	m_layout->setSpacing(0);

	m_certificateTable = new CertificateTable();

	QLabel* bottomTableSpacer = new QLabel();
	bottomTableSpacer->setFixedHeight(10);

	QWidget* bottomBtns = new QWidget();
	bottomBtns->setFixedHeight(30);
	QHBoxLayout* btnsLayout = new QHBoxLayout();
	btnsLayout->setContentsMargins(0, 0, 0, 0);
	btnsLayout->setSpacing(0);
	bottomBtns->setLayout(btnsLayout);

	m_resetToDefaultBtn = new ClickableLabel();
	m_resetToDefaultBtn->setFixedSize(100, 30);
	m_resetToDefaultBtn->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_resetToDefaultBtn->setFont(FONT);
	m_resetToDefaultBtn->setText("Reset to Defaults");

	QLabel* centerBtnsSpacer = new QLabel();

	m_removeBtn = new QPushButton();
	m_removeBtn->setFixedSize(80, 30);
	m_removeBtn->setFont(FONT);
	m_removeBtn->setText("Remove");
	m_removeBtn->setDisabled(true);

	QLabel* btnsSpacer = new QLabel();
	btnsSpacer->setFixedWidth(8);

	m_addBtn = new QPushButton();
	m_addBtn->setFixedSize(80, 30);
	m_addBtn->setFont(FONT);
	m_addBtn->setText("Add");

	btnsLayout->addWidget(m_resetToDefaultBtn);
	btnsLayout->addWidget(centerBtnsSpacer);
	btnsLayout->addWidget(m_removeBtn);
	btnsLayout->addWidget(btnsSpacer);
	btnsLayout->addWidget(m_addBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_certificateTable);
	m_layout->addWidget(bottomTableSpacer);
	m_layout->addWidget(bottomBtns);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);
	setStyle();
}

TrustedCertificate::~TrustedCertificate()
{
}

void TrustedCertificate::addButtonClicked()
{
}

void TrustedCertificate::resetToDefaultClicked()
{
}

void TrustedCertificate::changeTheme()
{
	setStyle();
}

void TrustedCertificate::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		setRemoveBtnStyle();

		m_resetToDefaultBtn->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:

		m_resetToDefaultBtn->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");

		setRemoveBtnStyle();

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void TrustedCertificate::setRemoveBtnStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if (m_removeBtn->isEnabled())
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		}
		else
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_LT + ";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_LT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

	case Theme_Type::Dark_Theme:

		if (m_removeBtn->isEnabled())
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		}
		else
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_DT + ";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_DT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

		//MORE THEME
	default:
		break;
	}
}

void TrustedCertificate::removeButtonClicked()
{
}

void TrustedCertificate::setRemoveBtnDisabled(bool disabled)
{
	m_removeBtn->setDisabled(disabled);
	setRemoveBtnStyle();
}
