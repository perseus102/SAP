#include "universalav.h"

UniversalAV::UniversalAV(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setMinimumWidth(500);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 25, 0, 0);
	m_layout->setSpacing(10);

	m_autoUpload		= new QLabel();
	m_autoUpload->setFont(LARGE_FONT);
	m_autoUpload->setFixedHeight(12);
	m_autoUpload->setWordWrap(true);

	m_autoUploadDesc	= new QLabel();
	m_autoUploadDesc->setFont(FONT);
	m_autoUploadDesc->setFixedHeight(10);
	m_autoUploadDesc->setWordWrap(true);

	m_selectFileTyle	= new QLabel();
	m_selectFileTyle->setFont(FONT);
	m_selectFileTyle->setFixedHeight(10);
	m_selectFileTyle->setWordWrap(true);

	m_GoodNew			= new QLabel();
	m_GoodNew->setFont(LARGE_FONT);
	m_GoodNew->setFixedHeight(12);
	m_GoodNew->setWordWrap(true);

	m_GoodNewDesr		= new QLabel();
	m_GoodNewDesr->setFont(FONT);
	m_GoodNewDesr->setFixedHeight(10);
	m_GoodNewDesr->setWordWrap(true);

	m_fullScan			= new QLabel();
	m_fullScan->setFont(LARGE_FONT);
	m_fullScan->setFixedHeight(12);
	m_fullScan->setWordWrap(true);

	m_fullScanDesc		= new QLabel();
	m_fullScanDesc->setFont(FONT);
	m_fullScanDesc->setFixedHeight(10);
	m_fullScanDesc->setWordWrap(true);

	m_autoFullScan		= new QLabel();
	m_autoFullScan->setFont(FONT);
	m_autoFullScan->setFixedHeight(10);
	m_autoFullScan->setWordWrap(true);

	m_demandScanning	= new QLabel();
	m_demandScanning->setFont(LARGE_FONT);
	m_demandScanning->setFixedHeight(12);
	m_demandScanning->setWordWrap(true);

	m_demandScanningDesc	= new QLabel();
	m_demandScanningDesc->setFont(FONT);
	m_demandScanningDesc->setFixedHeight(10);
	m_demandScanningDesc->setWordWrap(true);

	m_realTimeScanning		= new QLabel();
	m_realTimeScanning->setFont(LARGE_FONT);
	m_realTimeScanning->setFixedHeight(12);
	m_realTimeScanning->setWordWrap(true);

	m_realTimeScanningDesc	= new QLabel();
	m_realTimeScanningDesc->setFont(FONT);
	m_realTimeScanningDesc->setFixedHeight(10);
	m_realTimeScanningDesc->setWordWrap(true);

	m_dailyUpload			= new QLabel();
	m_dailyUpload->setFont(LARGE_FONT);
	m_dailyUpload->setFixedHeight(12);
	m_dailyUpload->setWordWrap(true);

	m_fileTypeCbb = new QComboBox();
	m_fileTypeCbb->setFixedSize(240, 32);

	m_autoUploadToggle	= new Switch();
	m_goodNewToggle		= new Switch();
	m_fullScanToggle	= new Switch();
	m_onDemandToggle	= new Switch();
	m_realTimeToggle	= new Switch();
	m_autoFullScanToggle = new Switch();

	m_slider			= new QSlider();
	m_slider->setRange(1, 4);

	m_layout->addWidget(m_autoUpload);
	m_layout->addWidget(m_autoUploadDesc);
	m_layout->addWidget(m_autoUploadToggle);
	m_layout->addWidget(m_selectFileTyle);
	m_layout->addWidget(m_fileTypeCbb);
	m_layout->addWidget(m_GoodNew);
	m_layout->addWidget(m_GoodNewDesr);
	m_layout->addWidget(m_goodNewToggle);
	m_layout->addWidget(m_fullScan);
	m_layout->addWidget(m_fullScanDesc);
	m_layout->addWidget(m_fullScanToggle);
	m_layout->addWidget(m_autoFullScan);
	m_layout->addWidget(m_autoFullScanToggle);
	m_layout->addWidget(m_demandScanning);
	m_layout->addWidget(m_demandScanningDesc);
	m_layout->addWidget(m_onDemandToggle);
	m_layout->addWidget(m_realTimeScanning);
	m_layout->addWidget(m_realTimeScanningDesc);
	m_layout->addWidget(m_realTimeToggle);
	m_layout->addWidget(m_dailyUpload);
	m_layout->addWidget(m_slider);

	setLayout(m_layout);
	setStyle();
	setLabelText();
	setStyleSheet("background-color:none;");
}

UniversalAV::~UniversalAV()
{
}

void UniversalAV::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		m_autoUpload->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_autoUploadDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		m_selectFileTyle->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		m_GoodNew->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_GoodNewDesr->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		m_fullScan->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_fullScanDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");
		m_autoFullScan->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		m_demandScanning->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_demandScanningDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		m_realTimeScanning->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");
		m_realTimeScanningDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_LT + ";}");

		m_dailyUpload->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:

		m_autoUpload->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_autoUploadDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");

		m_selectFileTyle->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");

		m_GoodNew->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_GoodNewDesr->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");

		m_fullScan->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_fullScanDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");
		m_autoFullScan->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");

		m_demandScanning->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_demandScanningDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");

		m_realTimeScanning->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");
		m_realTimeScanningDesc->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_DESCRIPTION_TEXT_DT + ";}");

		m_dailyUpload->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TITLE_TEXT_DT + ";}");

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
