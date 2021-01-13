#include "addtrustedcertdialog.h"

ChooseFile::ChooseFile(QWidget* parent)
	: QFrame(parent)
{
	setFixedSize(120, 30);
	m_layout = new QHBoxLayout();
	m_layout->setContentsMargins(16, 0, 16, 0);
	m_layout->setSpacing(6);
	setLayout(m_layout);

	m_iconLabel = new QLabel();
	m_iconLabel->setFixedSize(15,15);

	m_chooseFileLabel = new QLabel();
	m_chooseFileLabel->setFixedHeight(30);
	m_chooseFileLabel->setFont(FONT);
	m_chooseFileLabel->setText("Choose File");

	m_layout->addWidget(m_iconLabel);
	m_layout->addWidget(m_chooseFileLabel);

	setStyle();
	setIcon();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ChooseFile::changeTheme);


}
ChooseFile::~ChooseFile()
{
}

void ChooseFile::showDialog()
{
}

void ChooseFile::changeTheme()
{
	setStyle();
	setIcon();
}

void ChooseFile::mousePressEvent(QMouseEvent * event)
{
	QString fileName = "";
	fileName = QFileDialog::getOpenFileName(this, tr("Select File"), "C:/", tr("Files (*.exe *.dll *.msi *.msu *.ocx *.sys);;All files (*.*)"));

	if (fileName != "")
	{
		emit choosedFile(fileName);
	}
}
void ChooseFile::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:
		this->setStyleSheet("QFrame{background-color:none; border-radius:2px;"
			"border: 1px solid #19C2E8;}");

		m_iconLabel->setStyleSheet("QLabel{border:none;background-color:none}");

		m_chooseFileLabel->setStyleSheet("QLabel{border:none;color:#19C2E8;}");
		break;

	case Theme_Type::Light_Theme:

		this->setStyleSheet("QFrame{background-color:none; border-radius:2px;"
			"border: 1px solid #055598;}");

		m_iconLabel->setStyleSheet("QLabel{border:none;background-color:none}");

		m_chooseFileLabel->setStyleSheet("QLabel{border:none;color:#055598;}");
		break;

		/* MORE THEME */
	default:
		break;
	}
}

void ChooseFile::setIcon()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		icon = util::getInstance()->ChangeSVGColor(CHOOSE_FILE_ICON, "#055598");
		break;

	case Theme_Type::Dark_Theme:
		icon = util::getInstance()->ChangeSVGColor(CHOOSE_FILE_ICON, "#19C2E8");
		break;

		/* MORE THEME */
	default:
		break;
	}
	m_iconLabel->setPixmap(icon.pixmap(15, 15));
}

AddTrustedCertDialog::AddTrustedCertDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);
	setFixedSize(380, 360);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 30, 30, 0);
	m_layout->setSpacing(0);

	QWidget* topWg = new QWidget();
	topWg->setFixedHeight(87);
	QVBoxLayout* topLayout = new QVBoxLayout();
	topLayout->setContentsMargins(0, 0, 0, 0);
	topLayout->setSpacing(20);
	topWg->setLayout(topLayout);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(15);
	m_titleText->setFont(FONT);

	QWidget* chooseFileWg = new QWidget();
	chooseFileWg->setFixedHeight(30);
	QHBoxLayout* chooseFileLayout = new QHBoxLayout();
	chooseFileLayout->setContentsMargins(0, 0, 0, 0);
	chooseFileLayout->setSpacing(25);
	chooseFileWg->setLayout(chooseFileLayout);

	m_chooseFileBtn = new ChooseFile();

	m_filePathText = new QLabel();
	m_filePathText->setFixedHeight(30);
	m_filePathText->setFont(FONT);

	chooseFileLayout->addWidget(m_chooseFileBtn);
	chooseFileLayout->addWidget(m_filePathText);

	m_centerLine = new QLabel();
	m_centerLine->setFixedHeight(2);

	topLayout->addWidget(m_titleText);
	topLayout->addWidget(chooseFileWg);
	topLayout->addWidget(m_centerLine);

	QWidget* inforWg = new QWidget();
	inforWg->setFixedHeight(164);
	QVBoxLayout* inforLayout = new QVBoxLayout();
	inforLayout->setContentsMargins(0, 20, 0, 0);
	inforLayout->setSpacing(8);
	inforWg->setLayout(inforLayout);

	//////////
	m_commonNameWg = new QWidget();
	m_commonNameWg->setFixedHeight(30);

	QHBoxLayout* commonNameLayout = new QHBoxLayout();
	commonNameLayout->setContentsMargins(18, 0, 18, 0);
	commonNameLayout->setSpacing(0);
	m_commonNameWg->setLayout(commonNameLayout);

	m_commonNameLabel = new QLabel(this);
	m_commonNameLabel->setFont(FONT);
	m_commonNameLabel->setFixedHeight(30);

	commonNameLayout->addWidget(m_commonNameLabel);
	
	/////////
	m_validFromWg = new QWidget();
	m_validFromWg->setFixedHeight(30);

	QHBoxLayout* validFromLayout = new QHBoxLayout();
	validFromLayout->setContentsMargins(18, 0, 18, 0);
	validFromLayout->setSpacing(0);
	m_validFromWg->setLayout(validFromLayout);

	m_validFromLabel = new QLabel(this);
	m_validFromLabel->setFont(FONT);
	m_validFromLabel->setFixedHeight(30);

	validFromLayout->addWidget(m_validFromLabel);

	/////////
	m_validToWg = new QWidget();
	m_validToWg->setFixedHeight(30);

	QHBoxLayout* validToLayout = new QHBoxLayout();
	validToLayout->setContentsMargins(18, 0, 18, 0);
	validToLayout->setSpacing(0);
	m_validToWg->setLayout(validToLayout);

	m_validToLabel = new QLabel(this);
	m_validToLabel->setFont(FONT);
	m_validToLabel->setFixedHeight(30);

	validToLayout->addWidget(m_validToLabel);

	/////////
	m_thumbprintWg = new QWidget();
	m_thumbprintWg->setFixedHeight(30);

	QHBoxLayout* thumbprintLayout = new QHBoxLayout();
	thumbprintLayout->setContentsMargins(18, 0, 18, 0);
	thumbprintLayout->setSpacing(0);
	m_thumbprintWg->setLayout(thumbprintLayout);

	m_thumbprintLabel = new QLabel(this);
	m_thumbprintLabel->setFont(FONT);
	m_thumbprintLabel->setFixedHeight(30);

	thumbprintLayout->addWidget(m_thumbprintLabel);

	inforLayout->addWidget(m_commonNameWg);
	inforLayout->addWidget(m_validFromWg);
	inforLayout->addWidget(m_validToWg);
	inforLayout->addWidget(m_thumbprintWg);

	QLabel* inforSpacer = new QLabel();
	inforSpacer->setFixedHeight(25);

	///////////////
	QWidget* buttonWidget = new QWidget();
	buttonWidget->setFixedHeight(30);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);
	buttonWidget->setLayout(buttonLayout);

	QLabel* btnLeftSpacer = new QLabel();

	m_cancelBtn = new QPushButton();
	m_cancelBtn->setFixedSize(80, 30);
	m_cancelBtn->setFont(FONT);

	QLabel* centerBtnSpacer = new QLabel();
	centerBtnSpacer->setFixedWidth(8);

	m_addFileBtn = new QPushButton();
	m_addFileBtn->setFixedSize(80, 30);
	m_addFileBtn->setFont(FONT);

	buttonLayout->addWidget(btnLeftSpacer);
	buttonLayout->addWidget(m_cancelBtn);
	buttonLayout->addWidget(centerBtnSpacer);
	buttonLayout->addWidget(m_addFileBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(topWg);
	m_layout->addWidget(inforWg);
	m_layout->addWidget(inforSpacer);
	m_layout->addWidget(buttonWidget);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);

	setStyle();
	setText();

	connect(m_chooseFileBtn, &ChooseFile::choosedFile, this, &AddTrustedCertDialog::getFileName);
	connect(m_cancelBtn, &QPushButton::clicked, this, &AddTrustedCertDialog::cancelClicked);
	connect(m_addFileBtn, &QPushButton::clicked, this, &AddTrustedCertDialog::addClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &AddTrustedCertDialog::changeTheme);
}

AddTrustedCertDialog::~AddTrustedCertDialog()
{
}

void AddTrustedCertDialog::showDialog()
{
	m_curFileName = "";
	setText();
	activateWindow();
	raise();
	exec();
}

void AddTrustedCertDialog::addClicked()
{
	if (m_curFileName != "")
	{
		CertificateRowString certInfor;
		certInfor.CertificateNameText = m_commonNameLabel->text();
		certInfor.validFromText = m_validFromLabel->text();
		certInfor.validToText = m_validToLabel->text();
		certInfor.thumprintText = m_thumbprintLabel->text();
		emit addTrustedCert(certInfor);
	}

	this->close();
}
void AddTrustedCertDialog::changeTheme()
{
	setStyle();
}
void AddTrustedCertDialog::getFileName(QString fileName)
{
	if (m_curFileName == fileName) return;

	m_curFileName = fileName;

	if (fileName != "")
	{
		m_filePathText->setText(fileName);

		//do something to get common name, valid from, valid to, thumprint

		/* set text after get infor */
		m_commonNameLabel->setText("demo test");
		m_validFromLabel->setText("01/01/2021");
		m_validToLabel->setText("01/01/2023");
		m_thumbprintLabel->setText("IAJDVIWEORFIOJE2748729HFOI3NDJ2EF2IUHF50");
	}
}
void AddTrustedCertDialog::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
		case Theme_Type::Dark_Theme:

			this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_DT + ";");
			m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_DT + ";");

			m_filePathText->setStyleSheet("border:none; background-color:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_centerLine->setStyleSheet("border:none; background-color: " + DIALOG_TEXBOX_DT + ";");

			m_commonNameWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

			m_commonNameLabel->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_validFromWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

			m_validFromLabel->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_validToWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

			m_validToLabel->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_thumbprintWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

			m_thumbprintLabel->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
				"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
				"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");

			m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_DT + ";"
				"color: " + DIALOG_BUTTON_TEXT_DT + ";"
				"border-radius:4px;}");

			break;

		case Theme_Type::Light_Theme:
			this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");
			m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

			m_filePathText->setStyleSheet("border:none; background-color:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_centerLine->setStyleSheet("border:none; background-color: " + DIALOG_TEXBOX_LT + ";");

			m_commonNameWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

			m_commonNameLabel->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_validFromWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

			m_validFromLabel->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_validToWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

			m_validToLabel->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_thumbprintWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

			m_thumbprintLabel->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
				"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
				"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");

			m_addFileBtn->setStyleSheet("QPushButton {background-color: " + DIALOG_BUTTON_BGROUND_LT + ";"
				"color: " + DIALOG_BUTTON_TEXT_LT + ";"
				"border-radius:4px;}");


			break;

			/* MORE THEME */
		default:
			break;
}
}
void AddTrustedCertDialog::setText()
{
	m_titleText->setText("ADD TRUSTED CERTIFICATE");
	m_filePathText->setText("No file chosen");
	m_validFromLabel->setText("Valid From");
	m_validToLabel->setText("Valid To");
	m_thumbprintLabel->setText("Thumpbprint");
	m_commonNameLabel->setText("Certificate Common Name");
	m_cancelBtn->setText("Cancel");
	m_addFileBtn->setText("Add");
}
void AddTrustedCertDialog::cancelClicked()
{
	this->close();
}
