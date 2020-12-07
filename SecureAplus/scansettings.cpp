#include "scansettings.h"

ScanSettings::ScanSettings(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_contentLayout		= new QHBoxLayout();
	m_contentLayout->setContentsMargins(0, 20, 0, 0);
	m_contentLayout->setSpacing(0);

	m_tabLayout			= new QVBoxLayout();
	m_tabLayout->setContentsMargins(0, 28, 0, 0);
	m_tabLayout->setSpacing(0);

	m_tabWidget			= new QWidget();
	m_tabWidget->setFixedWidth(100);
	m_tabWidget->setLayout(m_tabLayout);

	m_universalAV		= new ClickableLabel();
	m_universalAV->setFixedSize(100, 28);
	m_universalAV->setFont(FONT);
	m_universalAV->setAlignment(Qt::AlignCenter);

	m_antivirus			= new ClickableLabel();
	m_antivirus->setFixedSize(100, 28);
	m_antivirus->setFont(FONT);
	m_antivirus->setAlignment(Qt::AlignCenter);

	m_VulAssessment		= new ClickableLabel();
	m_VulAssessment->setFixedSize(100, 48);
	m_VulAssessment->setFont(FONT);
	m_VulAssessment->setWordWrap(true);
	m_VulAssessment->setAlignment(Qt::AlignCenter);

	QLabel* bottomSpacer = new QLabel();
	m_tabLayout->addWidget(m_universalAV);
	m_tabLayout->addWidget(m_antivirus);
	m_tabLayout->addWidget(m_VulAssessment);
	m_tabLayout->addWidget(bottomSpacer);

	m_tabContentWidget = new QFrame();
	m_tabContentWidget->setObjectName("m_tabContentWidget");

	QVBoxLayout *tabLayout = new QVBoxLayout();
	tabLayout->setContentsMargins(0, 25, 0, 0);
	m_tabContentWidget->setLayout(tabLayout);

	m_tabStackedWidget	= new QStackedWidget();

	m_universalAVTab = new UniversalAV();
	m_universalAVTab->setObjectName("m_universalAVTab");
	m_tabStackedWidget->addWidget(m_universalAVTab);
	m_universalAVTab->setFixedHeight(880);

	m_scrollView		= new QScrollArea();
	m_scrollView->setObjectName("m_scrollView");
	m_scrollView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	m_scrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

	m_scrollView->setWidget(m_tabStackedWidget);
	tabLayout->addWidget(m_scrollView);

	m_contentLayout->addWidget(m_tabWidget);
	m_contentLayout->addWidget(m_tabContentWidget);

	setLayout(m_contentLayout);
	setTabText();

	setTabActiveStyle(m_universalAV);
	setTabInActiveStyle(m_antivirus);
	setTabInActiveStyle(m_VulAssessment);

	m_universalAVTab->resize(400, 880);
	m_tabStackedWidget->resize(400, 880);

	setStyle();

	connect(m_universalAV, &ClickableLabel::clicked, this, &ScanSettings::TabClicked);
	connect(m_antivirus, &ClickableLabel::clicked, this, &ScanSettings::TabClicked);
	connect(m_VulAssessment, &ClickableLabel::clicked, this, &ScanSettings::TabClicked);
}

ScanSettings::~ScanSettings()
{
}

void ScanSettings::setTabText()
{
	m_universalAV->setText("Universal AV");
	m_antivirus->setText("Antivirus");
	m_VulAssessment->setText("Vulnerability Assessment");
}

void ScanSettings::TabClicked()
{
	if (sender() == m_universalAV)
	{
		setTabActiveStyle(m_universalAV);
		setTabInActiveStyle(m_antivirus);
		setTabInActiveStyle(m_VulAssessment);
	}

	if (sender() == m_antivirus)
	{
		setTabActiveStyle(m_antivirus);
		setTabInActiveStyle(m_universalAV);
		setTabInActiveStyle(m_VulAssessment);
	}


	if (sender() == m_VulAssessment)
	{
		setTabActiveStyle(m_VulAssessment);
		setTabInActiveStyle(m_antivirus);
		setTabInActiveStyle(m_universalAV);
	}
}


void ScanSettings::setStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_tabContentWidget->setStyleSheet("#m_scrollView{border-top-left-radius:10px;}"
			"background-color:" + SCAN_SETTINGS_SCROLL_AREA_BACKGROUND_LT + ";}");

		m_scrollView->setStyleSheet("background-color:transparent; border:0px");

		break;

	case Theme_Type::Dark_Theme:
		m_tabContentWidget->setStyleSheet("QFrame#m_tabContentWidget{border-top-left-radius:10px;"
			"background-color:" + SCAN_SETTINGS_SCROLL_AREA_BACKGROUND_DT + ";}");

		m_scrollView->setStyleSheet("background-color:transparent; border:0px");

		break;

		//MORE THEME
	default:
		break;
	}
}

void ScanSettings::setTabActiveStyle(ClickableLabel * tab)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		tab->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TAB_SELECTED_TEXT_LT + "; border-top-left-radius:2px; border-bottom-left-radius:2px;"
			"background-color:" + SCAN_SETTINGS_TAB_ACTIVE_BACKGROUND_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:
		tab->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TAB_SELECTED_TEXT_DT + "; border-top-left-radius:2px; border-bottom-left-radius:2px;"
			"background-color:" + SCAN_SETTINGS_TAB_ACTIVE_BACKGROUND_DT + ";}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void ScanSettings::setTabInActiveStyle(ClickableLabel * tab)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		tab->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TAB_UNSELECTED_TEXT_LT + ";"
			"background-color: none;}");
		break;

	case Theme_Type::Dark_Theme:
		tab->setStyleSheet("QLabel{ color:" + SCAN_SETTINGS_TAB_UNSELECTED_TEXT_DT + ";"
			"background-color: none;}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void ScanSettings::resizeEvent(QResizeEvent* event)
{
	// Your code here.
	QSize size = m_scrollView->size();
	if (size.width() < 450) size = QSize(489,800);
	m_universalAVTab->resize(size.width()- 15, m_universalAVTab->height());
	m_tabStackedWidget->resize(size.width() - 15, m_universalAVTab->height());
	qDebug() << size;
}