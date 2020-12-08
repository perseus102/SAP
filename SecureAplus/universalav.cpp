#include "universalav.h"

UniversalAV::UniversalAV(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	m_autoUpload		= new QLabel();
	m_autoUpload->setFont(LARGE_FONT);
	m_autoUpload->setFixedHeight(20);
	m_autoUpload->setWordWrap(true);

	QLabel* uploadTitleSpacer = new QLabel();
	uploadTitleSpacer->setFixedHeight(12);

	m_autoUploadDesc	= new QLabel();
	m_autoUploadDesc->setFont(SMALL_FONT);
	m_autoUploadDesc->setFixedHeight(15);
	m_autoUploadDesc->setWordWrap(true);

	QLabel* uploadtoggleSpacer = new QLabel();
	uploadtoggleSpacer->setFixedHeight(2);

	m_autoUploadToggle = new Switch(QMargins(0, 8, 16, 8), true);
	m_autoUploadToggle->setFixedSize(50,30);

	QLabel* selectFileSpacer = new QLabel();
	selectFileSpacer->setFixedHeight(20);

	m_selectFileTyle	= new QLabel();
	m_selectFileTyle->setFont(SMALL_FONT);
	m_selectFileTyle->setFixedHeight(15);
	m_selectFileTyle->setWordWrap(true);

	QLabel* CbbSpacer = new QLabel();
	CbbSpacer->setFixedHeight(13);

	m_fileTypeCbb = new SAPCombobox();
	m_fileTypeCbb->setFixedSize(240, 32);
	m_fileTypeCbb->setObjectName("m_fileTypeCbb");

	QLabel* uploadSpacer = new QLabel();
	//uploadSpacer->setFixedHeight(20);

	m_fileTypeCbb->addItem("Executable and script files");
	m_fileTypeCbb->addItem("Executable");
	m_fileTypeCbb->addItem("Executable");
	m_fileTypeCbb->addItem("Executable");

	m_autoUploadLine = new QLabel();
	m_autoUploadLine->setFixedHeight(2);

	QWidget* autoUploadWg = new QWidget();
	autoUploadWg->setFixedHeight(180);
	QVBoxLayout* autoUploadLayout = new QVBoxLayout();
	autoUploadLayout->setSpacing(0);
	autoUploadLayout->setContentsMargins(30, 0, 0, 0);
	autoUploadWg->setLayout(autoUploadLayout);

	autoUploadLayout->addWidget(m_autoUpload);
	autoUploadLayout->addWidget(uploadTitleSpacer);
	autoUploadLayout->addWidget(m_autoUploadDesc);
	autoUploadLayout->addWidget(uploadtoggleSpacer);
	autoUploadLayout->addWidget(m_autoUploadToggle);
	autoUploadLayout->addWidget(selectFileSpacer);
	autoUploadLayout->addWidget(m_selectFileTyle);
	autoUploadLayout->addWidget(CbbSpacer);
	autoUploadLayout->addWidget(m_fileTypeCbb);
	autoUploadLayout->addWidget(uploadSpacer);

	QWidget* goodNewWg = new QWidget();
	goodNewWg->setFixedHeight(116);

	QVBoxLayout* goodNewLayout = new QVBoxLayout();
	goodNewLayout->setSpacing(0);
	goodNewLayout->setContentsMargins(30, 0, 0, 0);
	goodNewWg->setLayout(goodNewLayout);

	QLabel* goodNewTopSpacer = new QLabel();
	goodNewTopSpacer->setFixedHeight(22);

	m_GoodNew			= new QLabel();
	m_GoodNew->setFont(LARGE_FONT);
	m_GoodNew->setFixedHeight(20);
	m_GoodNew->setWordWrap(true);

	QLabel* goodNewDecsSpacer = new QLabel();
	goodNewDecsSpacer->setFixedHeight(11);

	m_GoodNewDesr		= new QLabel();
	m_GoodNewDesr->setFont(SMALL_FONT);
	m_GoodNewDesr->setFixedHeight(15);
	m_GoodNewDesr->setWordWrap(true);

	QLabel* goodNewToggleSpacer = new QLabel();
	goodNewToggleSpacer->setFixedHeight(2);

	m_goodNewToggle = new Switch(QMargins(0,8,16,8), true);
	m_goodNewToggle->setFixedSize(50, 30);

	m_goodNewLine = new QLabel();
	m_goodNewLine->setFixedHeight(2);

	QLabel* goodNewBottomSpacer = new QLabel();

	goodNewLayout->addWidget(goodNewTopSpacer);
	goodNewLayout->addWidget(m_GoodNew);
	goodNewLayout->addWidget(goodNewDecsSpacer);
	goodNewLayout->addWidget(m_GoodNewDesr);
	goodNewLayout->addWidget(goodNewToggleSpacer);
	goodNewLayout->addWidget(m_goodNewToggle);
	goodNewLayout->addWidget(goodNewBottomSpacer);

	QWidget* fullScanWg = new QWidget();
	fullScanWg->setFixedHeight(182);

	QVBoxLayout* fullScanLayout = new QVBoxLayout();
	fullScanLayout->setSpacing(0);
	fullScanLayout->setContentsMargins(30, 0, 0, 0);
	fullScanWg->setLayout(fullScanLayout);

	QLabel* fullScanTopSpacer = new QLabel();
	fullScanTopSpacer->setFixedHeight(22);

	m_fullScan			= new QLabel();
	m_fullScan->setFont(LARGE_FONT);
	m_fullScan->setFixedHeight(20);
	m_fullScan->setWordWrap(true);

	QLabel* fullScanDecsSpacer = new QLabel();
	fullScanDecsSpacer->setFixedHeight(14);

	m_fullScanDesc		= new QLabel();
	m_fullScanDesc->setFont(SMALL_FONT);
	m_fullScanDesc->setFixedHeight(15);
	m_fullScanDesc->setWordWrap(true);

	QLabel* fullScanToggleSpacer = new QLabel();
	fullScanToggleSpacer->setFixedHeight(1);

	m_fullScanToggle = new Switch(QMargins(0, 8, 16, 8), true);
	m_fullScanToggle->setFixedSize(50, 30);

	QLabel* autoFullScanSpacer = new QLabel();
	autoFullScanSpacer->setFixedHeight(16);

	m_autoFullScan		= new QLabel();
	m_autoFullScan->setFont(SMALL_FONT);
	m_autoFullScan->setFixedHeight(15);
	m_autoFullScan->setWordWrap(true);

	m_autoFullScanToggle	= new Switch(QMargins(0, 8, 16, 8), true);
	m_fullScanToggle->setFixedSize(50, 30);

	QLabel* FullScanBottomSpacer = new QLabel();

	m_fullSystemLine = new QLabel();
	m_fullSystemLine->setFixedHeight(2);

	fullScanLayout->addWidget(fullScanTopSpacer);
	fullScanLayout->addWidget(m_fullScan);
	fullScanLayout->addWidget(fullScanDecsSpacer);
	fullScanLayout->addWidget(m_fullScanDesc);
	fullScanLayout->addWidget(fullScanToggleSpacer);
	fullScanLayout->addWidget(m_fullScanToggle);
	fullScanLayout->addWidget(autoFullScanSpacer);
	fullScanLayout->addWidget(m_autoFullScan);
	fullScanLayout->addWidget(m_autoFullScanToggle);
	fullScanLayout->addWidget(FullScanBottomSpacer);

	QWidget* demandWg = new QWidget();
	demandWg->setFixedHeight(110);

	QVBoxLayout* demandLayout = new QVBoxLayout();
	demandLayout->setSpacing(0);
	demandLayout->setContentsMargins(30, 0, 0, 0);
	demandWg->setLayout(demandLayout);

	QLabel* demandTopSpacer = new QLabel();
	demandTopSpacer->setFixedHeight(14);

	m_demandScanning	= new QLabel();
	m_demandScanning->setFont(LARGE_FONT);
	m_demandScanning->setFixedHeight(20);
	m_demandScanning->setWordWrap(true);

	QLabel* demandDecsSpacer = new QLabel();
	demandDecsSpacer->setFixedHeight(14);

	m_demandScanningDesc	= new QLabel();
	m_demandScanningDesc->setFont(SMALL_FONT);
	m_demandScanningDesc->setFixedHeight(15);
	m_demandScanningDesc->setWordWrap(true);

	QLabel* demandtoggleSpacer = new QLabel();
	demandtoggleSpacer->setFixedHeight(2);

	m_onDemandToggle = new Switch(QMargins(0, 8, 16, 8), true);
	m_onDemandToggle->setFixedSize(50, 30);

	QLabel* demandBottomSpacer = new QLabel();

	m_demandScanningLine = new QLabel();
	m_demandScanningLine->setFixedHeight(2);

	demandLayout->addWidget(demandTopSpacer);
	demandLayout->addWidget(m_demandScanning);
	demandLayout->addWidget(demandDecsSpacer);
	demandLayout->addWidget(m_demandScanningDesc);
	demandLayout->addWidget(demandtoggleSpacer);
	demandLayout->addWidget(m_onDemandToggle);
	demandLayout->addWidget(demandBottomSpacer);

	QWidget* realTimeWg = new QWidget();
	realTimeWg->setFixedHeight(130);

	QVBoxLayout* realTimeLayout = new QVBoxLayout();
	realTimeLayout->setSpacing(0);
	realTimeLayout->setContentsMargins(30, 0, 0, 0);
	realTimeWg->setLayout(realTimeLayout);

	QLabel* realTimeTopSpacer = new QLabel();
	realTimeTopSpacer->setFixedHeight(24);

	m_realTimeScanning		= new QLabel();
	m_realTimeScanning->setFont(LARGE_FONT);
	m_realTimeScanning->setFixedHeight(20);
	m_realTimeScanning->setWordWrap(true);

	QLabel* realTimeDecsSpacer = new QLabel();
	realTimeDecsSpacer->setFixedHeight(12);

	m_realTimeScanningDesc = new QLabel();
	m_realTimeScanningDesc->setFont(SMALL_FONT);
	m_realTimeScanningDesc->setFixedHeight(30);
	m_realTimeScanningDesc->setWordWrap(true);

	QLabel* realTimeToggleSpacer = new QLabel();
	realTimeToggleSpacer->setFixedHeight(10);

	m_realTimeToggle = new Switch(QMargins(0, 8, 16, 8), true);
	m_realTimeToggle->setFixedSize(50, 30);

	QLabel* realTimeBottomSpacer = new QLabel();

	m_realTimeScanningLine = new QLabel();
	m_realTimeScanningLine->setFixedHeight(2);

	realTimeLayout->addWidget(realTimeTopSpacer);
	realTimeLayout->addWidget(m_realTimeScanning);
	realTimeLayout->addWidget(realTimeDecsSpacer);
	realTimeLayout->addWidget(m_realTimeScanningDesc);
	realTimeLayout->addWidget(realTimeToggleSpacer);
	realTimeLayout->addWidget(m_realTimeToggle);
	realTimeLayout->addWidget(realTimeBottomSpacer);

	QWidget* dailyUploadWg = new QWidget();
	dailyUploadWg->setFixedHeight(100);

	QVBoxLayout* dailyUploadLayout = new QVBoxLayout();
	dailyUploadLayout->setSpacing(0);
	dailyUploadLayout->setContentsMargins(30, 0, 0, 0);
	dailyUploadWg->setLayout(dailyUploadLayout);

	QLabel* dailyUploadTopSpacer = new QLabel();
	dailyUploadTopSpacer->setFixedHeight(18);

	m_dailyUpload	= new QLabel();
	m_dailyUpload->setFont(LARGE_FONT);
	m_dailyUpload->setFixedHeight(20);
	m_dailyUpload->setWordWrap(true);

	QLabel* sliderSpacer = new QLabel();
	sliderSpacer->setFixedHeight(28);

	m_slider	= new SAPSlider();
	m_slider->setRange(1, 4);

	m_slider->setFixedWidth(330);
	m_slider->setFixedHeight(24);

	QLabel* capacitySpacer = new QLabel();
	capacitySpacer->setFixedHeight(17);

	QWidget* capacityWg = new QWidget();
	capacityWg->setFixedHeight(20);

	QHBoxLayout* capacityLayout = new QHBoxLayout();
	capacityLayout->setContentsMargins(0, 0, 0, 0);
	capacityLayout->setSpacing(0);
	capacityWg->setLayout(capacityLayout);

	m_dailyUpload10MB = new ClickableLabel();
	m_dailyUpload10MB->setFont(SMALL_FONT);
	m_dailyUpload10MB->setFixedHeight(15);

	m_dailyUpload100MB = new ClickableLabel();
	m_dailyUpload100MB->setFont(SMALL_FONT);
	m_dailyUpload100MB->setFixedHeight(15);

	m_dailyUpload1GB = new ClickableLabel();
	m_dailyUpload1GB->setFont(SMALL_FONT);
	m_dailyUpload1GB->setFixedHeight(15);

	m_dailyUploadUnlimited = new ClickableLabel();
	m_dailyUploadUnlimited->setFont(SMALL_FONT);
	m_dailyUploadUnlimited->setFixedHeight(15);

	spacer10MB		= new QLabel();
	spacer100MB		= new QLabel();
	spacer1GB		= new QLabel();

	QLabel* capacityRightSpacer		= new QLabel();
	QLabel* dailyUploadBottomSpacer = new QLabel();

	setDailyUpload10MBText("10MB");
	setDailyUpload100MBText("100MB");
	setDailyUpload1GBText("1GB");
	setDailyUploadUnlimitedText("Unlimited");

	capacityLayout->addWidget(m_dailyUpload10MB);
	capacityLayout->addWidget(spacer10MB);

	capacityLayout->addWidget(m_dailyUpload100MB);
	capacityLayout->addWidget(spacer100MB);

	capacityLayout->addWidget(m_dailyUpload1GB);
	capacityLayout->addWidget(spacer1GB);

	capacityLayout->addWidget(m_dailyUploadUnlimited);
	capacityLayout->addWidget(capacityRightSpacer);


	dailyUploadLayout->addWidget(dailyUploadTopSpacer);
	dailyUploadLayout->addWidget(m_dailyUpload);
	dailyUploadLayout->addWidget(sliderSpacer);
	dailyUploadLayout->addWidget(m_slider);
	dailyUploadLayout->addWidget(capacitySpacer);
	dailyUploadLayout->addWidget(capacityWg);
	dailyUploadLayout->addWidget(dailyUploadBottomSpacer);

	m_layout->addWidget(autoUploadWg);
	m_layout->addWidget(m_autoUploadLine);

	m_layout->addWidget(goodNewWg);
	m_layout->addWidget(m_goodNewLine);

	m_layout->addWidget(fullScanWg);
	m_layout->addWidget(m_fullSystemLine);

	m_layout->addWidget(demandWg);
	m_layout->addWidget(m_demandScanningLine);

	m_layout->addWidget(realTimeWg);
	m_layout->addWidget(m_realTimeScanningLine);

	m_layout->addWidget(dailyUploadWg);

	QLabel* spacerBottom = new QLabel();

	m_layout->addWidget(spacerBottom);

	setLayout(m_layout);
	setStyle();
	setLabelText();

	connect(m_dailyUpload10MB, &ClickableLabel::clicked, this, &UniversalAV::capacityClicked);
	connect(m_dailyUpload100MB, &ClickableLabel::clicked, this, &UniversalAV::capacityClicked);
	connect(m_dailyUpload1GB, &ClickableLabel::clicked, this, &UniversalAV::capacityClicked);
	connect(m_dailyUploadUnlimited, &ClickableLabel::clicked, this, &UniversalAV::capacityClicked);
	connect(m_slider, &QSlider::valueChanged, this, &UniversalAV::sliderChangeValue);
	connect(m_fileTypeCbb, SIGNAL(currentIndexChanged(int)),this, SLOT(comboboxChangeIndex(int)));
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &UniversalAV::changeTheme);
}

UniversalAV::~UniversalAV()
{
}

void UniversalAV::sliderChangeValue(int value)
{
	//do something
	//qDebug() << "sliderChangeValue " << value;

}

void UniversalAV::comboboxChangeIndex(int index)
{
	//do something
	//qDebug() << "comboboxChangeIndex " << index;
}

void UniversalAV::changeTheme()
{
	setStyle();
}


void UniversalAV::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		m_autoUpload->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_autoUploadDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_selectFileTyle->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_autoUploadLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		m_GoodNew->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_GoodNewDesr->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_goodNewLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		m_fullScan->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_fullScanDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_autoFullScan->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_fullSystemLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		m_demandScanning->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_demandScanningDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_demandScanningLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		m_realTimeScanning->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_realTimeScanningDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_realTimeScanningLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		m_dailyUpload->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_dailyUpload10MB->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_dailyUpload100MB->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_dailyUpload1GB->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_dailyUploadUnlimited->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:

		m_autoUpload->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_autoUploadDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_selectFileTyle->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_autoUploadLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_GoodNew->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_GoodNewDesr->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_goodNewLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_fullScan->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_fullScanDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_autoFullScan->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_fullSystemLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_demandScanning->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_demandScanningDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_demandScanningLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_realTimeScanning->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_realTimeScanningDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_realTimeScanningLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_dailyUpload->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_dailyUpload10MB->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_dailyUpload100MB->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_dailyUpload1GB->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_dailyUploadUnlimited->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");

		/*m_fileTypeCbb->setStyleSheet(
			"QComboBox#m_fileTypeCbb{"
			"background-color:"+ COMBOBOX_BACKGROUND_DT +";"
			"color: "+ COMBOBOX_TEXT_ICON_DT +";"
			"padding-left:10px;"
			"}"

			"QComboBox::drop-down{"
			"border: 2px;"
			"padding-left:10px"
			"}"

			"QComboBox::down-arrow {"
			"image: url("+ DOWN_ARROW_DT + ");"
			"width:12px;"
			"height:12px;"
			"padding-right:30px;"
			"}"

			"QComboBox QAbstractItemView {"
			"selection-background-color: "+ COMBOBOX_BACKGROUND_DT +";"
			"color:"+ COMBOBOX_TEXT_ICON_DT +";"
			"outline: 1px solid "+ COMBOBOX_TEXT_ICON_DT +";"
			"padding-left:10px"
			"}");*/

		//m_slider->setStyleSheet(
		//	
		//	"QSlider::groove:horizontal{"
		//	"border: 1px solid none;"
		//	"height: 1px;"
		//	"background: none;"
		//	"margin: 0px 10px;"
		//	"}"
		//	"QSlider::handle:horizontal {"
		//	/*"width: 20px;"
		//	"background-image: url(" + SLIDER_THUMB_ICON_DT + ");"*/
		//	"background: "+ SLIDER_THUMB_DT +";"
		//	//"border: 1px solid #B5E61D;"
		//	"height: 20px;"
		//	"width: 20px;"
		//	"margin: -10px -10px;"
		//	"border-radius: 10px;"
		//	"}"

		//	"QSlider::add-page:qlineargradient {"
		//	"background: "+ SLIDER_INACTIVE_TRACK_DT +";"
		//	"border-top-right-radius: 5px;"
		//	"border-bottom-right-radius: 5px;"
		//	"border-top-left-radius: 0px;"
		//	"border-bottom-left-radius: 0px;"
		//	"}"

		//	"QSlider::sub-page:qlineargradient {"
		//	"background: "+ SLIDER_ACTIVE_TRACK_DT +";"
		//	"border-top-right-radius: 0px;"
		//	"border-bottom-right-radius: 0px;"
		//	"border-top-left-radius: 5px;"
		//	"border-bottom-left-radius: 5px;"
		//	"}"
		//	);
		break;

		//MORE THEME
	default:
		break;
	}
}

void UniversalAV::setLabelText()
{
	m_autoUpload->setText("Auto Upload Sample File");
	m_autoUploadDesc->setText("When it is enabled, Universal AV will automatically upload sample file if required.");
	m_selectFileTyle->setText("Select file type to upload unknown files to Universal AV server");
	m_GoodNew->setText("Good News Dialog");
	m_GoodNewDesr->setText("Display Good News dialog everytime after boot up when the machine is clean");
	m_fullScan->setText("Full System Scan");
	m_fullScanDesc->setText("Disabling this feature will disable manual and automatic periodic full system scan.");
	m_autoFullScan->setText("Automatic Full System Scan");
	m_demandScanning->setText("On Demand Scanning");
	m_demandScanningDesc->setText("Use Universal AV for manual scanning of files and folders in right click menu");
	m_realTimeScanning->setText("Real-time Scanning");
	m_realTimeScanningDesc->setText("Uses cloud antivirus  engines for real time scanning. The result of the scanning will be depending on whether the file has been scanned by Universal AV server before.");
	m_dailyUpload->setText("Daily Upload Limit");
}

void UniversalAV::setDailyUpload10MBText(QString text)
{
	QFontMetrics fm(FONT);
	int width = fm.width(text);

	m_dailyUpload10MB->setFixedWidth(width);
	m_dailyUpload10MB->setText(text);
	spacer10MB->setFixedWidth(100 - width);
}

void UniversalAV::setDailyUpload100MBText(QString text)
{
	QFontMetrics fm(FONT);
	int width = fm.width(text);

	m_dailyUpload100MB->setFixedWidth(width);
	m_dailyUpload100MB->setText(text);
	spacer100MB->setFixedWidth(105 - width);

}

void UniversalAV::setDailyUpload1GBText(QString text)
{
	QFontMetrics fm(FONT);
	int width = fm.width(text);

	m_dailyUpload1GB->setFixedWidth(width);
	m_dailyUpload1GB->setText(text);
	spacer1GB->setFixedWidth(100 - width);

}

void UniversalAV::setDailyUploadUnlimitedText(QString text)
{
	QFontMetrics fm(FONT);
	int width = fm.width(text);

	m_dailyUploadUnlimited->setFixedWidth(width);
	m_dailyUploadUnlimited->setText(text);

}

void UniversalAV::capacityClicked()
{
	//10MB label Clicked
	if (sender() == m_dailyUpload10MB)
	{
		if (m_slider->value() != 1)
		{
			m_slider->setValue(1);
		}
	}
	//100MB label Clicked
	else if (sender() == m_dailyUpload100MB)
	{
		if (m_slider->value() != 2)
		{
			m_slider->setValue(2);
		}
	}
	//1GB label Clicked
	else if (sender() == m_dailyUpload1GB)
	{
		if (m_slider->value() != 3)
		{
			m_slider->setValue(3);
		}
	}
	//Unlimited label Clicked
	else if (sender() == m_dailyUploadUnlimited)
	{
		if (m_slider->value() != 4)
		{
			m_slider->setValue(4);
		}
	}
}