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

void ChooseFile::mousePressEvent(QMouseEvent*)
{
	QString fileName = "";
	fileName = QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("Files (*.exe *.dll *.msi *.msu *.ocx *.sys);;All files (*.*)"));

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
			"border: 1px solid " + DIALOG_BUTTON_BGROUND_DT + ";}");

		m_iconLabel->setStyleSheet("QLabel{border:none;background-color:none}");

		m_chooseFileLabel->setStyleSheet("QLabel{border:none;color:" + DIALOG_BUTTON_BGROUND_DT + ";}");
		break;

	case Theme_Type::Light_Theme:

		this->setStyleSheet("QFrame{background-color:none; border-radius:2px;"
			"border: 1px solid "+ DIALOG_BUTTON_BGROUND_LT +";}");

		m_iconLabel->setStyleSheet("QLabel{border:none;background-color:none}");

		m_chooseFileLabel->setStyleSheet("QLabel{border:none;color:"+ DIALOG_BUTTON_BGROUND_LT +";}");
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

		icon = util::getInstance()->ChangeSVGColor(CHOOSE_FILE_ICON, DIALOG_BUTTON_BGROUND_LT);
		break;

	case Theme_Type::Dark_Theme:
		icon = util::getInstance()->ChangeSVGColor(CHOOSE_FILE_ICON, DIALOG_BUTTON_BGROUND_DT);
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
	setFixedSize(380, 180);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(23, 30, 23, 0);
	m_layout->setSpacing(0);

	QWidget* topWg = new QWidget();
	topWg->setFixedHeight(65);
	QVBoxLayout* topLayout = new QVBoxLayout();
	topLayout->setContentsMargins(0, 0, 0, 0);
	topLayout->setSpacing(20);
	topWg->setLayout(topLayout);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(15);
	m_titleText->setFont(LARGE_FONT);

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

	topLayout->addWidget(m_titleText);
	topLayout->addWidget(chooseFileWg);

	/////////////

	topSpacer = new QLabel();
	topSpacer->setFixedHeight(14);

	//////////////////

	m_certificateInforWg = new QWidget();
	m_certificateInforWg->setFixedSize(334, 123);
	m_certificateInforWg->setVisible(false);

	QHBoxLayout* certinforsLayout = new QHBoxLayout();
	certinforsLayout->setContentsMargins(16, 16, 16, 0);
	certinforsLayout->setSpacing(30);
	m_certificateInforWg->setLayout(certinforsLayout);

	//////////

	QWidget* titleWg = new QWidget();
	titleWg->setFixedWidth(100);

	QVBoxLayout* titleLayout = new QVBoxLayout();
	titleLayout->setContentsMargins(0, 0, 0, 0);
	titleLayout->setSpacing(0);
	titleWg->setLayout(titleLayout);

	m_commonNameTitle = new QLabel();
	m_commonNameTitle->setAlignment(Qt::AlignLeft |Qt::AlignTop);
	m_commonNameTitle->setFont(FONT);
	m_commonNameTitle->setFixedHeight(20);
	m_commonNameTitle->setText("Certificate Name");

	m_validFromTitle = new QLabel();
	m_validFromTitle->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_validFromTitle->setFont(FONT);
	m_validFromTitle->setFixedHeight(20);
	m_validFromTitle->setText("Valid From");

	m_validToTitle = new QLabel();
	m_validToTitle->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_validToTitle->setFont(FONT);
	m_validToTitle->setFixedHeight(20);
	m_validToTitle->setText("Valid to");

	m_thumbprintTitle = new QLabel();
	m_thumbprintTitle->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_thumbprintTitle->setFont(FONT);
	m_thumbprintTitle->setText("Thumbprint");

	titleLayout->addWidget(m_commonNameTitle);
	titleLayout->addWidget(m_validFromTitle);
	titleLayout->addWidget(m_validToTitle);
	titleLayout->addWidget(m_thumbprintTitle);

	/////////////

	QWidget* inforWg = new QWidget();
	inforWg->setFixedWidth(172);
	QVBoxLayout* inforLayout = new QVBoxLayout();
	inforLayout->setContentsMargins(0, 0, 0, 0);
	inforLayout->setSpacing(0);
	inforWg->setLayout(inforLayout);

	m_commonName = new QLabel();
	m_commonName->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_commonName->setFont(FONT);
	m_commonName->setFixedHeight(20);
	m_commonName->setWordWrap(true);

	m_validFrom = new QLabel();
	m_validFrom->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_validFrom->setFont(FONT);
	m_validFrom->setFixedHeight(20);
	m_validFrom->setWordWrap(true);

	m_validTo = new QLabel();
	m_validTo->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_validTo->setFont(FONT);
	m_validTo->setFixedHeight(20);
	m_validTo->setWordWrap(true);

	m_thumbprint = new QLabel();
	m_thumbprint->setFont(FONT);
	m_thumbprint->setWordWrap(true);
	m_thumbprint->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	
	inforLayout->addWidget(m_commonName);
	inforLayout->addWidget(m_validFrom);
	inforLayout->addWidget(m_validTo);
	inforLayout->addWidget(m_thumbprint);

	////////////

	certinforsLayout->addWidget(titleWg);
	certinforsLayout->addWidget(inforWg);

	QLabel* rightSpacer = new QLabel();
	certinforsLayout->addWidget(rightSpacer);

	/////////////
	QLabel* inforSpacer = new QLabel();
	inforSpacer->setFixedHeight(26);

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
	m_addFileBtn->setEnabled(false);

	buttonLayout->addWidget(btnLeftSpacer);
	buttonLayout->addWidget(m_cancelBtn);
	buttonLayout->addWidget(centerBtnSpacer);
	buttonLayout->addWidget(m_addFileBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(topWg);
	m_layout->addWidget(topSpacer);
	m_layout->addWidget(m_certificateInforWg);
	m_layout->addWidget(inforSpacer);
	m_layout->addWidget(buttonWidget);
	m_layout->addWidget(bottomSpacer);

	setLayout(m_layout);

	setStyle();
	setText();
	setAddBtnStyle();

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
	setFixedSize(380, 180);
	m_certificateInforWg->setVisible(false);
	topSpacer->setVisible(false);
	m_addFileBtn->setEnabled(false);
	setAddBtnStyle();
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
		certInfor.CertificateNameText = m_commonName->text();
		certInfor.validFromText = m_validFrom->text();
		certInfor.validToText = m_validTo->text();
		certInfor.thumprintText = m_thumbprint->text();
		emit addTrustedCert(certInfor);
	}

	this->close();
}
void AddTrustedCertDialog::changeTheme()
{
	setStyle();
	setAddBtnStyle();
}
void AddTrustedCertDialog::getFileName(QString fileName)
{
	setFixedSize(380, 322);
	m_certificateInforWg->setVisible(true);
	topSpacer->setVisible(true);

	if (m_curFileName == fileName) return;

	m_curFileName = fileName;
	if (fileName != "")
	{
		m_addFileBtn->setEnabled(true);
		setAddBtnStyle();

		setFilePathText(fileName);

		//do something to get common name, valid from, valid to, thumprint

		/* set text after get infor */
		m_commonName->setText("demo test");
		m_validFrom->setText("01/01/2021");
		m_validTo->setText("01/01/2023");
		setThumprintText("2bb95f164c168bfe64340802000b54e3f3460dd7");
		qDebug() << m_thumbprint->size();
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

			m_certificateInforWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_DT + ";");

			m_commonNameTitle->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_commonName->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_validFromTitle->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_validFrom->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_validToTitle->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_validTo->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_thumbprintTitle->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");

			m_thumbprint->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_DT + ";");


			m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_DT + ";"
				"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_DT + "; border-radius:4px;}"
				"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_DT + ";}");



			break;

		case Theme_Type::Light_Theme:
			this->setStyleSheet("background-color: " + DIALOG_BACKGROUND_LT + ";");
			m_titleText->setStyleSheet("color: " + DIALOG_TITLE_TEXT_LT + ";");

			m_filePathText->setStyleSheet("border:none; background-color:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");


			m_certificateInforWg->setStyleSheet("background-color: " + DIALOG_TEXBOX_LT + ";");

			m_commonNameTitle->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_commonName->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_validFromTitle->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_validFrom->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_validToTitle->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_validTo->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_thumbprintTitle->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_thumbprint->setStyleSheet("border:none;"
				"color:" + TAB_CONTENT_DESC_TEXT_LT + ";");

			m_cancelBtn->setStyleSheet("QPushButton {color: " + DIALOG_CANCEL_TEXT_BORDER_LT + ";"
				"border: 1px solid" + DIALOG_CANCEL_TEXT_BORDER_LT + "; border-radius:4px;}"
				"QPushButton:hover{border: 2px solid " + DIALOG_CANCEL_TEXT_BORDER_LT + ";}");



			break;

			/* MORE THEME */
		default:
			break;
}
}
void AddTrustedCertDialog::setText()
{
	m_titleText->setText("Add Trusted Certificate");
	m_filePathText->setText("No file chosen");
	m_commonNameTitle->setText("Certificate Name");
	m_validFromTitle->setText("Valid From");
	m_validToTitle->setText("Valid to");
	m_thumbprintTitle->setText("Thumpbprint");
	m_cancelBtn->setText("Cancel");
	m_addFileBtn->setText("Add");
}

void AddTrustedCertDialog::setAddBtnStyle()
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
			m_addFileBtn->setStyleSheet("QPushButton {background-color: "+ DIALOG_BUTTON_BACKGROUND_DISABLE_LT +";"
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

void AddTrustedCertDialog::setThumprintText(QString text)
{
	m_thumbprintText = text;

	int centerPos = text.count() / 2;
	int thumbprintWidth = m_thumbprint->size().width();
	QFontMetrics fm(FONT);

	int textWidth, remainSpace, nextCharWidth;
	do
	{
		textWidth = fm.width(text.mid(0, centerPos));

		remainSpace = thumbprintWidth - textWidth;

		nextCharWidth = fm.width(text.mid(centerPos, 1));;

		if (remainSpace > nextCharWidth)
		{
			centerPos++;
			continue;
		}

		if (textWidth <= thumbprintWidth)
		{
			break;
		}

		centerPos--;

	} while (true);

	QString thumbprintText = text.insert(centerPos, " ");

	m_thumbprint->setText(thumbprintText);
}

void AddTrustedCertDialog::setFilePathText(QString text)
{
	QFontMetrics fm(FONT);
	int FilePathWidth = m_filePathText->size().width();
	int textWidth = fm.width(text);
	int inscreasePathWidth, threeDotSize;
	int count = 0;

	text.replace("/", "\\");
	m_filePathText->setToolTip(text);
	threeDotSize = fm.width("...");

	if (textWidth <= FilePathWidth)
	{
		m_filePathText->setText(text);
		return;
	}

	QStringList textSplit = text.split("\\");
	QString filePath = textSplit[0] + "\\" +"..."+ "\\"+ textSplit[textSplit.count() - 1];
	QString inscreasePath = "";

	do
	{
		inscreasePath = "";
		for (int i = 0; i <= count + 1; i++)
		{
			inscreasePath += textSplit[i] + "\\";
		}

		inscreasePath += "...\\" + textSplit[textSplit.count() - 1];

		inscreasePathWidth = fm.width(inscreasePath);

		if (inscreasePathWidth == FilePathWidth)
		{
			filePath = inscreasePath;
			break;
		}

		if (inscreasePathWidth < FilePathWidth)
		{
			count++;
			filePath = inscreasePath;
			continue;
			
		}

		break;

	} while (true);

	m_filePathText->setText(filePath);
}

void AddTrustedCertDialog::cancelClicked()
{
	this->close();
}
