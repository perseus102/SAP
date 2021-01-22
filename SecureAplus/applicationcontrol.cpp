#include "applicationcontrol.h"

ApplicationControl::ApplicationControl(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_contentLayout = new QHBoxLayout();
	m_contentLayout->setContentsMargins(15, 20, 0, 0);
	m_contentLayout->setSpacing(0);

	m_tabLayout = new QVBoxLayout();
	m_tabLayout->setContentsMargins(0, 28, 0, 0);
	m_tabLayout->setSpacing(0);

	m_tabWidget = new QWidget();
	m_tabWidget->setFixedWidth(100);
	m_tabWidget->setLayout(m_tabLayout);

	m_digitalSignature = new ClickableLabel();
	m_digitalSignature->setFixedSize(100, 48);
	m_digitalSignature->setFont(FONT);
	m_digitalSignature->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_digitalSignature->setWordWrap(true);

	m_allowList = new ClickableLabel();
	m_allowList->setFixedSize(100, 28);
	m_allowList->setFont(FONT);
	m_allowList->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_allowList->setWordWrap(true);

	m_restrictApp = new ClickableLabel();
	m_restrictApp->setFixedSize(100, 48);
	m_restrictApp->setFont(FONT);
	m_restrictApp->setWordWrap(true);
	m_restrictApp->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	
	m_trustedCertificate = new ClickableLabel();
	m_trustedCertificate->setFixedSize(100, 48);
	m_trustedCertificate->setFont(FONT);
	m_trustedCertificate->setWordWrap(true);
	m_trustedCertificate->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	m_scripts = new ClickableLabel();
	m_scripts->setFixedSize(100, 28);
	m_scripts->setFont(FONT);
	m_scripts->setWordWrap(true);
	m_scripts->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	m_cmdRules = new ClickableLabel();
	m_cmdRules->setFixedSize(100, 48);
	m_cmdRules->setFont(FONT);
	m_cmdRules->setWordWrap(true);
	m_cmdRules->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	m_allowedListCmd = new ClickableLabel();
	m_allowedListCmd->setFixedSize(100, 58);
	m_allowedListCmd->setFont(FONT);
	m_allowedListCmd->setWordWrap(true);
	m_allowedListCmd->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);	
	
	m_processProtector = new ClickableLabel();
	m_processProtector->setFixedSize(100, 48);
	m_processProtector->setFont(FONT);
	m_processProtector->setWordWrap(true);
	m_processProtector->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QLabel* bottomSpacer = new QLabel();
	m_tabLayout->addWidget(m_digitalSignature);
	m_tabLayout->addWidget(m_allowList);
	m_tabLayout->addWidget(m_restrictApp);
	m_tabLayout->addWidget(m_trustedCertificate);
	m_tabLayout->addWidget(m_scripts);
	m_tabLayout->addWidget(m_cmdRules);
	m_tabLayout->addWidget(m_allowedListCmd);
	m_tabLayout->addWidget(m_processProtector);
	m_tabLayout->addWidget(bottomSpacer);

	m_tabContentWidget = new QFrame();
	m_tabContentWidget->setObjectName("m_tabContentWidget");

	QVBoxLayout *tabLayout = new QVBoxLayout();
	tabLayout->setContentsMargins(0, 25, 0, 0);
	m_tabContentWidget->setLayout(tabLayout);

	m_digitalSignatureTab	= new DigitalSignature();
	m_allowListTab			= new AllowList();
	m_restrictedAppTab		= new RestrictedApp();
	m_trustedCertificateTab = new TrustedCertificate();
	m_scriptsTab			= new Scripts();
	m_commandLineTab		= new CommandLine();
	m_processProtectorTab	= new ProcessProtector();

	m_tabStackedWidget = new QStackedWidget();
	m_tabStackedWidget->addWidget(m_digitalSignatureTab);
	m_tabStackedWidget->addWidget(m_allowListTab);
	m_tabStackedWidget->addWidget(m_restrictedAppTab);
	m_tabStackedWidget->addWidget(m_trustedCertificateTab);
	m_tabStackedWidget->addWidget(m_scriptsTab);
	m_tabStackedWidget->addWidget(m_commandLineTab);
	m_tabStackedWidget->addWidget(m_processProtectorTab);

	tabLayout->addWidget(m_tabStackedWidget);

	m_contentLayout->addWidget(m_tabWidget);
	m_contentLayout->addWidget(m_tabContentWidget);

	setLayout(m_contentLayout);

	m_activeTab = new QObject();

	m_activeTab = m_digitalSignature;
	setTabStyle();
	setStyle();
	setTabText();

	connect(m_digitalSignature, &ClickableLabel::clicked, this, &ApplicationControl::TabClicked);
	connect(m_allowList, &ClickableLabel::clicked, this, &ApplicationControl::TabClicked);
	connect(m_restrictApp, &ClickableLabel::clicked, this, &ApplicationControl::TabClicked);
	connect(m_trustedCertificate, &ClickableLabel::clicked, this, &ApplicationControl::TabClicked);
	connect(m_scripts, &ClickableLabel::clicked, this, &ApplicationControl::TabClicked);
	connect(m_cmdRules, &ClickableLabel::clicked, this, &ApplicationControl::TabClicked);
	connect(m_allowedListCmd, &ClickableLabel::clicked, this, &ApplicationControl::TabClicked);
	connect(m_processProtector, &ClickableLabel::clicked, this, &ApplicationControl::TabClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ApplicationControl::changeTheme);
}

ApplicationControl::~ApplicationControl()
{
}

void ApplicationControl::setTabText()
{
	m_digitalSignature->setText("Digital Signature");
	m_allowList->setText("Allow List");
	m_restrictApp->setText("Restricted Applications");
	m_trustedCertificate->setText("Trusted Certificates");
	m_scripts->setText("Scripts");
	m_cmdRules->setText("Command Line Rules");
	m_allowedListCmd->setText("Allowed List Command Line");
	m_processProtector->setText("Process Protector");
}

void ApplicationControl::changeTheme()
{
	setStyle();
	setTabStyle();
}

void ApplicationControl::setStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_tabContentWidget->setStyleSheet("QFrame#m_tabContentWidget{border-top-left-radius:10px;"
			"background-color:" + TAB_CONTENT_BACKGROUND_LT + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_tabContentWidget->setStyleSheet("QFrame#m_tabContentWidget{border-top-left-radius:10px;"
			"background-color:" + TAB_CONTENT_BACKGROUND_DT + ";}");

		break;

		//MORE THEME
	default:
		break;
	}
}

void ApplicationControl::setTabStyle()
{
	if (m_activeTab == m_digitalSignature)
	{
		setTabActiveStyle(m_digitalSignature);

		setTabInActiveStyle(m_allowList);
		setTabInActiveStyle(m_restrictApp);
		setTabInActiveStyle(m_trustedCertificate);
		setTabInActiveStyle(m_scripts);
		setTabInActiveStyle(m_cmdRules);
		setTabInActiveStyle(m_allowedListCmd);
		setTabInActiveStyle(m_processProtector);
	}
	else if (m_activeTab == m_allowList)
	{
		setTabActiveStyle(m_allowList);

		setTabInActiveStyle(m_digitalSignature);
		setTabInActiveStyle(m_restrictApp);
		setTabInActiveStyle(m_trustedCertificate);
		setTabInActiveStyle(m_scripts);
		setTabInActiveStyle(m_cmdRules);
		setTabInActiveStyle(m_allowedListCmd);
		setTabInActiveStyle(m_processProtector);
	}
	else if (m_activeTab == m_restrictApp)
	{
		setTabActiveStyle(m_restrictApp);

		setTabInActiveStyle(m_digitalSignature);
		setTabInActiveStyle(m_allowList);
		setTabInActiveStyle(m_trustedCertificate);
		setTabInActiveStyle(m_scripts);
		setTabInActiveStyle(m_cmdRules);
		setTabInActiveStyle(m_allowedListCmd);
		setTabInActiveStyle(m_processProtector);
	}
	else if (m_activeTab == m_trustedCertificate)
	{
		setTabActiveStyle(m_trustedCertificate);

		setTabInActiveStyle(m_digitalSignature);
		setTabInActiveStyle(m_allowList);
		setTabInActiveStyle(m_restrictApp);
		setTabInActiveStyle(m_scripts);
		setTabInActiveStyle(m_cmdRules);
		setTabInActiveStyle(m_allowedListCmd);
		setTabInActiveStyle(m_processProtector);
	}
	else if (m_activeTab == m_scripts)
	{
		setTabActiveStyle(m_scripts);

		setTabInActiveStyle(m_digitalSignature);
		setTabInActiveStyle(m_allowList);
		setTabInActiveStyle(m_restrictApp);
		setTabInActiveStyle(m_trustedCertificate);
		setTabInActiveStyle(m_cmdRules);
		setTabInActiveStyle(m_allowedListCmd);
		setTabInActiveStyle(m_processProtector);
	}
	else if (m_activeTab == m_cmdRules)
	{
		setTabActiveStyle(m_cmdRules);

		setTabInActiveStyle(m_digitalSignature);
		setTabInActiveStyle(m_allowList);
		setTabInActiveStyle(m_restrictApp);
		setTabInActiveStyle(m_trustedCertificate);
		setTabInActiveStyle(m_scripts);
		setTabInActiveStyle(m_allowedListCmd);
		setTabInActiveStyle(m_processProtector);
	}
	else if (m_activeTab == m_allowedListCmd)
	{
		setTabActiveStyle(m_allowedListCmd);

		setTabInActiveStyle(m_digitalSignature);
		setTabInActiveStyle(m_allowList);
		setTabInActiveStyle(m_restrictApp);
		setTabInActiveStyle(m_trustedCertificate);
		setTabInActiveStyle(m_scripts);
		setTabInActiveStyle(m_cmdRules);
		setTabInActiveStyle(m_processProtector);
	}

	else if (m_activeTab == m_processProtector)
	{
		setTabActiveStyle(m_processProtector);

		setTabInActiveStyle(m_digitalSignature);
		setTabInActiveStyle(m_allowList);
		setTabInActiveStyle(m_restrictApp);
		setTabInActiveStyle(m_trustedCertificate);
		setTabInActiveStyle(m_scripts);
		setTabInActiveStyle(m_cmdRules);
		setTabInActiveStyle(m_allowedListCmd);
	}
}

void ApplicationControl::TabClicked()
{
	if (sender() == m_digitalSignature)
	{
		m_tabStackedWidget->setCurrentWidget(m_digitalSignatureTab);
		m_activeTab = m_digitalSignature;

	}
	else if (sender() == m_allowList)
	{
		m_tabStackedWidget->setCurrentWidget(m_allowListTab);
		m_activeTab = m_allowList;
	}
	else if (sender() == m_restrictApp)
	{
		m_tabStackedWidget->setCurrentWidget(m_restrictedAppTab);
		m_activeTab = m_restrictApp;
	}
	else if (sender() == m_trustedCertificate)
	{
		m_tabStackedWidget->setCurrentWidget(m_trustedCertificateTab);
		m_activeTab = m_trustedCertificate;
	}
	else if (sender() == m_scripts)
	{
		m_tabStackedWidget->setCurrentWidget(m_scriptsTab);
		m_activeTab = m_scripts;
	}
	else if (sender() == m_cmdRules)
	{
		m_activeTab = m_cmdRules;
	}
	else if (sender() == m_allowedListCmd)
	{
		m_tabStackedWidget->setCurrentWidget(m_commandLineTab);
		m_activeTab = m_allowedListCmd;
	}	
	else if (sender() == m_processProtector)
	{
		m_tabStackedWidget->setCurrentWidget(m_processProtectorTab);
		m_activeTab = m_processProtector;
	}
	setTabStyle();
}

void ApplicationControl::setTabActiveStyle(ClickableLabel * tab)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		tab->setStyleSheet("QLabel{ color:" + TAB_TITLE_TEXT_ACTIVE_LT + "; border-top-left-radius:2px; border-bottom-left-radius:2px;"
			"background-color:" + TAB_TITLE_BACKGROUND_ACTIVE_LT + ";"
			"padding-left:12px;"
			"padding-right:10px;}");
		break;

	case Theme_Type::Dark_Theme:
		tab->setStyleSheet("QLabel{ color:" + TAB_TITLE_TEXT_ACTIVE_DT + "; border-top-left-radius:2px; border-bottom-left-radius:2px;"
			"background-color:" + TAB_TITLE_BACKGROUND_ACTIVE_DT + ";"
			"padding-left:12px;"
			"padding-right:10px;}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void ApplicationControl::setTabInActiveStyle(ClickableLabel * tab)
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		tab->setStyleSheet("QLabel{ color:" + TAB_TITLE_TEXT_INACTIVE_LT + ";"
			"background-color: none;"
			"padding-left:12px;"
			"padding-right:10px;}");
		break;

	case Theme_Type::Dark_Theme:
		tab->setStyleSheet("QLabel{ color:" + TAB_TITLE_TEXT_INACTIVE_DT + ";"
			"background-color: none;"
			"padding-left:12px;"
			"padding-right:10px;}");
		break;

		//MORE THEME
	default:
		break;
	}
}
