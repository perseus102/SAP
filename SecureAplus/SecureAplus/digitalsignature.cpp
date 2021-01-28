#include "digitalsignature.h"
#include "QTTrustedAccount.h"
#include "SecureAPlusLicenseType.h"
#include "NamedPipeSecureAPlusAdminSettings.h"
#include "Expiry.h"
#include "SecureaPlusLite.h"
#include "TrustedCertificate.h"
DigitalSignature::DigitalSignature(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 0, 0, 0);
	m_layout->setSpacing(0);

	m_trustBased = new QLabel();
	m_trustBased->setFont(LARGE_FONT);
	m_trustBased->setFixedHeight(20);
	m_trustBased->setWordWrap(true);

	QLabel* trustBasedSpacer = new QLabel();
	trustBasedSpacer->setFixedHeight(6);

	m_trustBasedToggle = new Switch(QMargins(0, 8, 16, 8), true);
	m_trustBasedToggle->setFixedSize(50, 30);
	m_trustBasedToggle->setChecked(true);

	QLabel* toggleSpacer = new QLabel();
	toggleSpacer->setFixedHeight(15);

	m_allowAppTitle = new QLabel();
	m_allowAppTitle->setFont(SMALL_FONT);
	m_allowAppTitle->setFixedHeight(15);
	m_allowAppTitle->setWordWrap(true);

	QLabel* allowAppTitleSpacer = new QLabel();
	allowAppTitleSpacer->setFixedHeight(6);

	/* Init Name in Trusted Certificate List */
	nameInTrustedWg = new QWidget();
	nameInTrustedWg->setFixedHeight(20);
	QHBoxLayout* nameInTrustedLayout = new QHBoxLayout();
	nameInTrustedLayout->setContentsMargins(0, 0, 0, 0);
	nameInTrustedLayout->setSpacing(0);
	nameInTrustedWg->setLayout(nameInTrustedLayout);

	m_nameInTrustedBtn = new SAPRadioButton();
	m_nameInTrustedBtn->setFixedSize(20, 20);

	QLabel* nameInTrustBtnSpacer = new QLabel();
	nameInTrustBtnSpacer->setFixedSize(10, 20);

	m_nameInTrusted = new QLabel();
	m_nameInTrusted->setFont(SMALL_FONT);
	m_nameInTrusted->setFixedHeight(20);
	m_nameInTrusted->setWordWrap(true);

	nameInTrustedLayout->addWidget(m_nameInTrustedBtn);
	nameInTrustedLayout->addWidget(nameInTrustBtnSpacer);
	nameInTrustedLayout->addWidget(m_nameInTrusted);

	QLabel* nameInTrustedDescSpacer = new QLabel();
	nameInTrustedDescSpacer->setFixedHeight(5);

	nameInTrustedDescWg = new QWidget();
	nameInTrustedDescWg->setFixedHeight(15);
	QHBoxLayout* nameInTrustedDescLayout = new QHBoxLayout();
	nameInTrustedDescLayout->setContentsMargins(0, 0, 0, 0);
	nameInTrustedDescLayout->setSpacing(0);
	nameInTrustedDescWg->setLayout(nameInTrustedDescLayout);

	QLabel* nameInTrustedDescLeftSpacer = new QLabel();
	nameInTrustedDescLeftSpacer->setFixedWidth(30);

	m_nameInTrustedDesc = new QLabel();
	m_nameInTrustedDesc->setFont(SMALL_FONT);
	m_nameInTrustedDesc->setFixedHeight(15);
	m_nameInTrustedDesc->setWordWrap(true);

	nameInTrustedDescLayout->addWidget(nameInTrustedDescLeftSpacer);
	nameInTrustedDescLayout->addWidget(m_nameInTrustedDesc);

	QLabel* trustedByOSSpacer = new QLabel();
	trustedByOSSpacer->setFixedHeight(25);

	/* Trusted by the OS */
	trustedByOSWg = new QWidget();
	trustedByOSWg->setFixedHeight(20);
	QHBoxLayout* trustedByOSLayout = new QHBoxLayout();
	trustedByOSLayout->setContentsMargins(0, 0, 0, 0);
	trustedByOSLayout->setSpacing(0);
	trustedByOSWg->setLayout(trustedByOSLayout);

	m_trustedByOSBtn = new SAPRadioButton();
	m_trustedByOSBtn->setFixedSize(20, 20);

	QLabel* trustedByOSBtnSpacer = new QLabel();
	trustedByOSBtnSpacer->setFixedSize(10, 20);

	m_trustedByOS = new QLabel();
	m_trustedByOS->setFont(SMALL_FONT);
	m_trustedByOS->setFixedHeight(20);
	m_trustedByOS->setWordWrap(true);

	trustedByOSLayout->addWidget(m_trustedByOSBtn);
	trustedByOSLayout->addWidget(trustedByOSBtnSpacer);
	trustedByOSLayout->addWidget(m_trustedByOS);

	QLabel* trustedByOSDescSpacer = new QLabel();
	trustedByOSDescSpacer->setFixedHeight(5);


	trustedByOSDescWg = new QWidget();
	trustedByOSDescWg->setFixedHeight(15);
	QHBoxLayout* trustedByOSDescLayout = new QHBoxLayout();
	trustedByOSDescLayout->setContentsMargins(0, 0, 0, 0);
	trustedByOSDescLayout->setSpacing(0);
	trustedByOSDescWg->setLayout(trustedByOSDescLayout);

	QLabel* trustedByOSDescLeftSpacer = new QLabel();
	trustedByOSDescLeftSpacer->setFixedWidth(30);

	m_trustedByOSDesc = new QLabel();
	m_trustedByOSDesc->setFont(SMALL_FONT);
	m_trustedByOSDesc->setFixedHeight(15);
	m_trustedByOSDesc->setWordWrap(true);

	trustedByOSDescLayout->addWidget(trustedByOSDescLeftSpacer);
	trustedByOSDescLayout->addWidget(m_trustedByOSDesc);

	QLabel* nameAndThumbprintSpacer = new QLabel();
	nameAndThumbprintSpacer->setFixedHeight(25);

	/* Name & Thumbprint in Trusted Certificate List */
	nameAndThumbprintWg = new QWidget();
	nameAndThumbprintWg->setFixedHeight(20);
	QHBoxLayout* nameAndThumbprintLayout = new QHBoxLayout();
	nameAndThumbprintLayout->setContentsMargins(0, 0, 0, 0);
	nameAndThumbprintLayout->setSpacing(0);
	nameAndThumbprintWg->setLayout(nameAndThumbprintLayout);

	m_nameAndThumbprintBtn = new SAPRadioButton();
	m_nameAndThumbprintBtn->setFixedSize(20, 20);

	QLabel* nameAndThumbprintBtnSpacer = new QLabel();
	nameAndThumbprintBtnSpacer->setFixedSize(10, 20);

	m_nameAndThumbprint = new QLabel();
	m_nameAndThumbprint->setFont(SMALL_FONT);
	m_nameAndThumbprint->setFixedHeight(20);
	m_nameAndThumbprint->setWordWrap(true);

	nameAndThumbprintLayout->addWidget(m_nameAndThumbprintBtn);
	nameAndThumbprintLayout->addWidget(nameAndThumbprintBtnSpacer);
	nameAndThumbprintLayout->addWidget(m_nameAndThumbprint);

	QLabel* nameAndThumbprintDescSpacer = new QLabel();
	nameAndThumbprintDescSpacer->setFixedHeight(5);

	nameAndThumbprintDescWg = new QWidget();
	nameAndThumbprintDescWg->setFixedHeight(15);
	QHBoxLayout* nameAndThumbprintDescLayout = new QHBoxLayout();
	nameAndThumbprintDescLayout->setContentsMargins(0, 0, 0, 0);
	nameAndThumbprintDescLayout->setSpacing(0);
	nameAndThumbprintDescWg->setLayout(nameAndThumbprintDescLayout);

	QLabel* nameAndThumbprintDescLeftSpacer = new QLabel();
	nameAndThumbprintDescLeftSpacer->setFixedWidth(30);

	m_nameAndThumbprintDesc = new QLabel();
	m_nameAndThumbprintDesc->setFont(SMALL_FONT);
	m_nameAndThumbprintDesc->setFixedHeight(15);
	m_nameAndThumbprintDesc->setWordWrap(true);

	nameAndThumbprintDescLayout->addWidget(nameAndThumbprintDescLeftSpacer);
	nameAndThumbprintDescLayout->addWidget(m_nameAndThumbprintDesc);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_trustBased);
	m_layout->addWidget(trustBasedSpacer);

	m_layout->addWidget(m_allowAppTitle);
	m_layout->addWidget(allowAppTitleSpacer);

	m_layout->addWidget(m_trustBasedToggle);
	m_layout->addWidget(toggleSpacer);

	m_layout->addWidget(nameInTrustedWg);
	m_layout->addWidget(nameInTrustedDescSpacer);
	m_layout->addWidget(nameInTrustedDescWg);

	m_layout->addWidget(trustedByOSSpacer);

	m_layout->addWidget(trustedByOSWg);
	m_layout->addWidget(trustedByOSDescSpacer);
	m_layout->addWidget(trustedByOSDescWg);

	m_layout->addWidget(nameAndThumbprintSpacer);

	m_layout->addWidget(nameAndThumbprintWg);
	m_layout->addWidget(nameAndThumbprintDescSpacer);
	m_layout->addWidget(nameAndThumbprintDescWg);

	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);
	setLabelText();
	setStyle();

	setAllowAppListVisible(true);

	DWORD dwTrustDigitalSignature = GetTrustByDigitalSignatureMode();

	switch (GetTrustByDigitalSignatureMode())
	{
	case Not_Trusted:
		setTrustedByDigitalSignature(TrustedBy_DigitalSignaature::Not_Trusted);
		break;

	case Trusted_By_Os:
		setTrustedByDigitalSignature(TrustedBy_DigitalSignaature::Trusted_By_Os);
		break;

	case Trusted_By_Name:
		setTrustedByDigitalSignature(TrustedBy_DigitalSignaature::Trusted_By_Name);
		break;

	case Trusted_By_Thumbprint:
		setTrustedByDigitalSignature(TrustedBy_DigitalSignaature::Trusted_By_Thumbprint);
		break;

	case Trusted_By_Signature_Invalid_Mode:
		break;
	default:
		break;
	}

	connect(m_trustBasedToggle, &Switch::released, this, &DigitalSignature::trustBasedToggleClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &DigitalSignature::changeTheme);
	connect(m_nameInTrustedBtn, &SAPRadioButton::clicked, this, &DigitalSignature::radioButtonClicked);
	connect(m_trustedByOSBtn, &SAPRadioButton::clicked, this, &DigitalSignature::radioButtonClicked);
	connect(m_nameAndThumbprintBtn, &SAPRadioButton::clicked, this, &DigitalSignature::radioButtonClicked);

}

DigitalSignature::~DigitalSignature()
{

}

void DigitalSignature::changeTheme()
{
	setStyle();
}

void DigitalSignature::radioButtonClicked()
{
	if (!IsRunByTrustedAccount())
	{
		//show dialog
		return;
	}

	if (sender() == m_trustedByOSBtn)
	{
		setTrustedByDigitalSignature(TrustedBy_DigitalSignaature::Trusted_By_Os);
	}
	else if (sender() == m_nameInTrustedBtn)
	{
		setTrustedByDigitalSignature(TrustedBy_DigitalSignaature::Trusted_By_Name);
	}
	else if (sender() == m_nameAndThumbprintBtn)
	{
		setTrustedByDigitalSignature(TrustedBy_DigitalSignaature::Trusted_By_Thumbprint);
	}
}

void DigitalSignature::setLabelText()
{
	m_trustBased->setText("Trust based on Digital Signature");
	m_allowAppTitle->setText("Allow application with valid digital signature to be trusted as installer if its certificate");
	m_nameInTrusted->setText("Name in Trusted Certificate List");
	m_nameInTrustedDesc->setText("Trust the file only if the certificate is in the trusted certificate list");
	m_trustedByOS->setText("Trusted by the Operating System");
	m_trustedByOSDesc->setText("Trust the file as long as the certificate is in the Microsoft Trusted Certificate List");
	m_nameAndThumbprint->setText("Name & Thumbprint in Trusted Certificate List");
	m_nameAndThumbprintDesc->setText("Trust the file only if the certificate and thumbprint is in the trusted certificate list.");
}

void DigitalSignature::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_trustBased->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		
		m_allowAppTitle->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		
		m_nameInTrusted->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		m_nameInTrustedDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		
		m_trustedByOS->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		m_trustedByOSDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		
		m_nameAndThumbprint->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		m_nameAndThumbprintDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:
		m_trustBased->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		m_allowAppTitle->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		m_nameInTrusted->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
		m_nameInTrustedDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_trustedByOS->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
		m_trustedByOSDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_nameAndThumbprint->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
		m_nameAndThumbprintDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");
		break;
		//MORE THEME
	default:
		break;
	}
}

void DigitalSignature::setAllowAppListVisible(bool isVisible)
{
	//m_allowAppTitle->setVisible(isVisible);
	nameInTrustedWg->setVisible(isVisible);
	nameInTrustedDescWg->setVisible(isVisible);
	trustedByOSWg->setVisible(isVisible);
	trustedByOSDescWg->setVisible(isVisible);
	nameAndThumbprintWg->setVisible(isVisible);
	nameAndThumbprintDescWg->setVisible(isVisible);
}

void DigitalSignature::trustBasedToggleClicked()
{
	if (m_trustBasedToggle->isChecked())
	{
		//do somthing
		setAllowAppListVisible(true);
		onTrustByCertificateChanged(1); //1 is turn on toggle and set trusted by name is default
		m_nameInTrustedBtn->setButtonChecked(Qt::Checked);
		m_trustedByOSBtn->setButtonChecked(Qt::Unchecked);
		m_nameAndThumbprintBtn->setButtonChecked(Qt::Unchecked);
	}
	else
	{
		//do somthing
		setAllowAppListVisible(false);
		onTrustByCertificateChanged(0);

	}
}
void DigitalSignature::radioBtnClicked(DWORD n) {
	
	if (!IsRunByTrustedAccount())
	{
		return;
	}

	if (IsSoftwareExpired() && IsEligibleForSecureAPlusLite())
	{
		//refresh();
		//QTMessageBox(this, tr("To be able to change this setting, please upgrade your license.\r\nYou can't set this setting because your current license does not support this."), TITLE, QMessageBox::Ok, QMessageBox::Critical); // display error msg
		return;
	}

	m_dwLastError = SecureaplusAdminSettingsSetTrustByCertificate(n);
	if (m_dwLastError != 0)
	{
		//SecureAPlusDisplayError(this, dwLastError);
		qDebug() << "m_dwLastError";
	}
	//refresh();
}

void DigitalSignature::onTrustByCertificateChanged(int value) {
	if (!IsRunByTrustedAccount())
	{
		return;
	}

	if (SecureAPlus_GetRegLicenceType() != SECUREAPLUS_LICENSE_TYPE_PRO) {
		//refresh();
		//QTMessageBox(this, tr("To be able to change this setting, please upgrade your license to Pro.\r\nYou can't set this setting because your current license does not support this."), TITLE, QMessageBox::Ok, QMessageBox::Critical);
		return;
	}
	switch (value)
	{
	case 0:
		// turn off
		m_dwLastError = SecureaplusAdminSettingsSetTrustByCertificate(0);
		if (m_dwLastError != 0)
		{
			//SecureAPlusDisplayError(this, dwLastError);
			qDebug() << "m_dwLastError";
		}
		//refresh();
		break;

	case 1:
		// if turn on Trust By Certificate trusted by name is default
		m_dwLastError = SecureaplusAdminSettingsSetTrustByCertificate(2);
		if (m_dwLastError != 0)
		{
			//SecureAPlusDisplayError(this, dwLastError);
			qDebug() << "m_dwLastError";
		}
		//refresh();
		break;
	}
}

void DigitalSignature::setTrustedByDigitalSignature(TrustedBy_DigitalSignaature mode)
{
	switch (mode)
	{
	case Not_Trusted:
		m_trustBasedToggle->setChecked(false);
		setAllowAppListVisible(false);
		radioBtnClicked(0);
		break;

	case Trusted_By_Os:
		m_nameInTrustedBtn->setButtonChecked(Qt::Unchecked);
		m_trustedByOSBtn->setButtonChecked(Qt::Checked);
		m_nameAndThumbprintBtn->setButtonChecked(Qt::Unchecked);
		radioBtnClicked(1);
		break;

	case Trusted_By_Name:
		m_nameInTrustedBtn->setButtonChecked(Qt::Checked);
		m_trustedByOSBtn->setButtonChecked(Qt::Unchecked);
		m_nameAndThumbprintBtn->setButtonChecked(Qt::Unchecked);
		radioBtnClicked(2);
		break;

	case Trusted_By_Thumbprint:
		m_nameInTrustedBtn->setButtonChecked(Qt::Unchecked);
		m_trustedByOSBtn->setButtonChecked(Qt::Unchecked);
		m_nameAndThumbprintBtn->setButtonChecked(Qt::Checked);
		radioBtnClicked(3);
		break;

	case Trusted_By_Signature_Invalid_Mode:
	default:
		setAllowAppListVisible(false);
		radioBtnClicked(0);
		break;
	}
}
