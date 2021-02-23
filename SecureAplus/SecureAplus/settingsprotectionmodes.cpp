#include "settingsprotectionmodes.h"

SettingsProtectionModes::SettingsProtectionModes(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 20, 30, 0);
	m_layout->setSpacing(0);

	QLabel* spacerTitleAndDescription = new QLabel();
	spacerTitleAndDescription->setFixedHeight(15);

	QLabel* spacerBottom = new QLabel();
	m_title = new QLabel();
	m_title->setFont(FONT);
	m_title->setAlignment(Qt::AlignLeft);
	m_title->setFixedHeight(20);
	m_title->setText("SELECT YOUR PROTECTION MODE"); //call function get text

	QWidget* modeDescription = new QWidget();
	modeDescription->setFixedHeight(30);
	modeDescription->setContentsMargins(0, 0, 0, 0);
	QHBoxLayout* descriptionLayout = new QHBoxLayout();
	descriptionLayout->setContentsMargins(0, 0, 0, 0);
	descriptionLayout->setSpacing(20);
	modeDescription->setLayout(descriptionLayout);

	m_modeTitle = new QLabel();
	m_modeTitle->setFont(SMALL_FONT);
	m_modeTitle->setAlignment(Qt::AlignLeft);
	m_modeTitle->setFixedSize(80, 30);

	m_description = new QLabel();
	m_description->setAlignment(Qt::AlignLeft);
	m_description->setFixedHeight(30);
	m_description->setWordWrap(true);

	descriptionLayout->addWidget(m_modeTitle);
	descriptionLayout->addWidget(m_description);

	m_editModeWidget = new QWidget();
	m_editModeWidget->setFixedHeight(24);
	m_editModeWidget->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout* editNotiWiLayout = new QHBoxLayout();
	editNotiWiLayout->setContentsMargins(0, 0, 0, 0);
	editNotiWiLayout->setSpacing(0);

	m_editModeWidget->setLayout(editNotiWiLayout);
	m_editModeWidget->setVisible(false);

	m_editMode = new ClickableLabel();
	m_editMode->setFixedSize(160, 24);
	m_editMode->setAlignment(Qt::AlignCenter);

	QLabel *editNotispacerLeft = new QLabel();
	editNotispacerLeft->setFixedWidth(95);

	QLabel *editNotispacerRight = new QLabel();

	editNotiWiLayout->addWidget(editNotispacerLeft);
	editNotiWiLayout->addWidget(m_editMode);
	editNotiWiLayout->addWidget(editNotispacerRight);

	QWidget* select = new QWidget();
	m_selectLayout = new FlowLayout(0, 15, 15);
	m_selectLayout->setContentsMargins(0, 20, 0, 0);
	select->setLayout(m_selectLayout);

	m_automatic = new SelectWidget(Protection_Modes::Automatic_Mode, true);
	m_interactive = new SelectWidget(Protection_Modes::Interactive_Mode);
	m_lockdown = new SelectWidget(Protection_Modes::Lockdown_Mode);
	m_trustall = new SelectWidget(Protection_Modes::TrustAll_Mode);
	m_observation = new SelectWidget(Protection_Modes::Observation_Mode);

	lockdownDialog = new LockDownDialog();
	trustAllDialog = new TrustAllDialog();
	upgradeDialog = new UpgradeDialog();
	transparent = new WidgetTransparent();

	m_selectLayout->addWidget(m_automatic);
	m_selectLayout->addWidget(m_interactive);
	m_selectLayout->addWidget(m_lockdown);
	m_selectLayout->addWidget(m_trustall);
	m_selectLayout->addWidget(m_observation);

	m_layout->addWidget(m_title);
	m_layout->addWidget(spacerTitleAndDescription);
	m_layout->addWidget(modeDescription);
	m_layout->addWidget(m_editModeWidget);
	m_layout->addWidget(select);
	m_layout->addWidget(spacerBottom);

	setLayout(m_layout);

	m_modeSelected = m_automatic;

	setConnection();
	setModeText();
	setStyle();
}

SettingsProtectionModes::~SettingsProtectionModes()
{
}

void SettingsProtectionModes::setConnection()
{
	connect(m_automatic, &SelectWidget::changeMode, this, &SettingsProtectionModes::changeProtectMode);
	connect(m_interactive, &SelectWidget::changeMode, this, &SettingsProtectionModes::changeProtectMode);
	connect(m_lockdown, &SelectWidget::changeMode, this, &SettingsProtectionModes::changeProtectMode);
	connect(m_trustall, &SelectWidget::changeMode, this, &SettingsProtectionModes::changeProtectMode);
	connect(m_observation, &SelectWidget::changeMode, this, &SettingsProtectionModes::changeProtectMode);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SettingsProtectionModes::changeTheme);
	connect(this, &SettingsProtectionModes::changeMode, AppSetting::getInstance(), &AppSetting::changeProtectionMode);
	connect(AppSetting::getInstance(), &AppSetting::signal_toggleChanged, this, &SettingsProtectionModes::toogleChanged);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeToPrevMode, this, &SettingsProtectionModes::changeToPrevMode);
	connect(AppSetting::getInstance(), &AppSetting::signal_ChangeModeByOtherSetting, this, &SettingsProtectionModes::modeChangedByOtherSetting);
	connect(m_editMode, &ClickableLabel::clicked, this, &SettingsProtectionModes::editModeClicked);
}

void SettingsProtectionModes::setModeText()
{
	//call function get text for multi language

	if (m_modeSelected == m_automatic)
	{
		m_modeTitle->setText("Automatic");
		m_description->setText("Keep prompts to a minimum. Automatically block or trust majority of new program outside of your trusted list");
	}
	else if (m_modeSelected == m_interactive)
	{
		m_modeTitle->setText("Interactive");
		m_description->setText("You will receive security prompts with recommended actions but all decisions to allow or deny a file program is always yours to make.");
	}
	else if (m_modeSelected == m_lockdown)
	{
		m_modeTitle->setText("Lockdown");
		m_description->setText("Programs outside of your trusted list will be automatically blocked.");
		m_editMode->setText("Edit Notification Settings");
	}
	else if (m_modeSelected == m_trustall)
	{
		m_modeTitle->setText("Trust All");
		m_description->setText("No prompts for a specified duration. Any program is allowed to run and is automatically added to your trusted list.");
		m_editMode->setText("Edit Trust All Duration");
	}
	else if (m_modeSelected == m_observation)
	{
		m_modeTitle->setText("Observation");
		m_description->setText("Untrusted applications are allowed to run, and will be recorded in the log file. The untrusted applications will remain untrusted when Observation Mode is switched off.");
	}
}

void SettingsProtectionModes::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_title->setStyleSheet("QLabel {  color:" + TITLE_TEXT_COLOR_LT + ";}");
		m_modeTitle->setStyleSheet("QLabel {  color:" + MODE_TITLE_TEXT_COLOR_LT + ";}");
		m_description->setStyleSheet("QLabel {  color:" + DESCRIPTION_TEXT_COLOR_LT + ";}");
		m_editMode->setStyleSheet("QLabel {  color: " + EDIT_LABEL_COLOR_BACKGROUND_LT + "; border-radius:2px;"
			"border: 1px solid " + EDIT_LABEL_COLOR_BACKGROUND_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:
		m_title->setStyleSheet("QLabel {  color:" + TITLE_TEXT_COLOR_DT + ";}");
		m_modeTitle->setStyleSheet("QLabel {  color:" + MODE_TITLE_TEXT_COLOR_DT + ";}");
		m_description->setStyleSheet("QLabel {  color:" + DESCRIPTION_TEXT_COLOR_DT + ";}");
		m_editMode->setStyleSheet("QLabel {  color: " + EDIT_LABEL_COLOR_BACKGROUND_DT + "; border-radius:2px;"
			"border: 1px solid " + EDIT_LABEL_COLOR_BACKGROUND_DT + ";}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void SettingsProtectionModes::switchMode()
{
	//Deactive previous mode
	if (m_modeSelected == m_automatic)
	{
		m_automatic->setSelected(false);
	}
	else if (m_modeSelected == m_interactive)
	{
		m_interactive->setSelected(false);
	}
	else if (m_modeSelected == m_lockdown)
	{
		m_lockdown->setSelected(false);
		m_lockdown->setLockDownText("");
	}
	else if (m_modeSelected == m_trustall)
	{
		//AppSetting::getInstance()->setStatus(Status::Protected_Status);
		m_trustall->setSelected(false);
	}
	else if (m_modeSelected == m_observation)
	{
		m_observation->setSelected(false);
	}

}

void SettingsProtectionModes::changeProtectMode()
{
	Protection_Modes mode = Protection_Modes::None;
	//Active changed mode
	if (sender() == m_automatic)
	{
		m_automatic->setSelected(true);
		mode = Protection_Modes::Automatic_Mode;
		m_editModeWidget->setVisible(false);

	}
	else if (sender() == m_interactive)
	{
		m_interactive->setSelected(true);
		mode = Protection_Modes::Interactive_Mode;
		m_editModeWidget->setVisible(false);
	}
	else if (sender() == m_lockdown)
	{
		QRect geometry = AppSetting::getInstance()->getAppGeometry();

		transparent->showWidget();
		lockdownDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 220, geometry.y() + 16, 440, 190);
		lockdownDialog->showDialog();
		transparent->hide();
		LockDown ld_mode = lockdownDialog->getLockDownMode();
		switch (ld_mode)
		{
		case LOCKDOWN_CANCEL:
			m_lockdown->setLockDownText("");
			return;
		case LOCKDOWN_SILENT:
			m_lockdown->setLockDownText("Silent");
			break;
		case LOCKDOWN_DEFAULT:
			m_lockdown->setLockDownText("Default");

			break;
		default:
			break;
		}
		m_lockdown->setSelected(true);
		mode = Protection_Modes::Lockdown_Mode;
		m_editModeWidget->setVisible(true);
	}
	else if (sender() == m_trustall)
	{
		QRect geometry = AppSetting::getInstance()->getAppGeometry();

		transparent->showWidget();
		trustAllDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 220, geometry.y() + 16, 440, 156);
		trustAllDialog->showDialog();
		transparent->hide();

		TrustAll trustAll = trustAllDialog->getDialogButtonClicked();
		if (trustAll == TrustAll::TRUSTALL_CANCEL)
		{
			return;
		}
		TrustAllTime trustAllTime = trustAllDialog->getTrustAllTime();

		switch (trustAllTime)
		{
		case TRUSTALL_5MINS:
			mode = Protection_Modes::TrustAll_5Mins;

			break;
		case TRUSTALL_30MINS:
			mode = Protection_Modes::TrustAll_30Mins;

			break;
		case TRUSTALL_NEXTREBOOT:
			mode = Protection_Modes::TrustAll_NetReboot;

			break;
		default:
			mode = Protection_Modes::TrustAll_Mode;
			break;
		}
		m_trustall->setSelected(true);
		m_editModeWidget->setVisible(true);
	}
	else if (sender() == m_observation)
	{
		QRect geometry = AppSetting::getInstance()->getAppGeometry();
		transparent->showWidget();
		upgradeDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 150, geometry.y() + (geometry.height() / 2) - 150, 300, 300);
		upgradeDialog->showDialog();
		transparent->hide();
		Observation observ = upgradeDialog->getObservation();

		if (observ == Observation::Observation_exit)
		{
			return;
		}

		m_observation->setSelected(true);
		mode = Protection_Modes::Observation_Mode;
		m_editModeWidget->setVisible(false);
	}
	switchMode();
	m_modeSelected = sender();
	setModeText();
	emit changeMode(mode);
}

void SettingsProtectionModes::changeTheme()
{
	setModeText();
	setStyle();
}

void SettingsProtectionModes::toogleChanged(bool isChecked)
{
	//Change mode when toggle switch
	switchMode();

	if (isChecked)
	{
		m_automatic->setSelected(true);
		AppSetting::getInstance()->setProtectionMode(Protection_Modes::Automatic_Mode);
		m_modeSelected = m_automatic;
	}
	else
	{
		m_interactive->setSelected(true);
		AppSetting::getInstance()->setProtectionMode(Protection_Modes::Interactive_Mode);
		m_modeSelected = m_interactive;
	}
	setModeText();
	m_editModeWidget->setVisible(false);
}

void SettingsProtectionModes::changeToPrevMode()
{
	switchMode();
	Protection_Modes mode = AppSetting::getInstance()->getPrevMode();
	switch (mode)
	{
	case None:
		break;
	case Automatic_Mode:
		m_automatic->setSelected(true);
		mode = Protection_Modes::Automatic_Mode;
		m_modeSelected = m_automatic;
		m_editModeWidget->setVisible(false);
		break;
	case Interactive_Mode:
		m_interactive->setSelected(true);
		mode = Protection_Modes::Interactive_Mode;
		m_modeSelected = m_interactive;
		m_editModeWidget->setVisible(false);

		break;
	case Lockdown_Mode:
	{
		LockDown ld_mode = lockdownDialog->getLockDownMode();
		switch (ld_mode)
		{
		case LOCKDOWN_CANCEL:
			m_lockdown->setLockDownText("");
			return;
		case LOCKDOWN_SILENT:
			m_lockdown->setLockDownText("Silent");
			break;
		case LOCKDOWN_DEFAULT:
			m_lockdown->setLockDownText("Default");

			break;
		default:
			break;
		}
	}
		m_lockdown->setSelected(true);
		mode = Protection_Modes::Lockdown_Mode;
		m_modeSelected = m_lockdown;
		m_editModeWidget->setVisible(true);

		break;
	case TrustAll_Mode:
		break;
	case TrustAll_5Mins:
		break;
	case TrustAll_30Mins:
		break;
	case TrustAll_NetReboot:
		break;
	case Observation_Mode:
		m_observation->setSelected(true);
		mode = Protection_Modes::Observation_Mode;
		m_modeSelected = m_observation;

		break;
	default:
		break;
	}
	
	setModeText();
	emit changeMode(mode);
}

void SettingsProtectionModes::modeChangedByOtherSetting(Protection_Modes mode)
{
	switchMode();
	m_editModeWidget->setVisible(false);
	switch (mode)
	{
	case None:
		break;
	case Automatic_Mode:
		m_automatic->setSelected(true);
		mode = Protection_Modes::Automatic_Mode;
		m_modeSelected = m_automatic;
		m_editModeWidget->setVisible(false);
		break;
	case Interactive_Mode:
		m_interactive->setSelected(true);
		mode = Protection_Modes::Interactive_Mode;
		m_modeSelected = m_interactive;
		m_editModeWidget->setVisible(false);
		break;
	case Lockdown_Mode:
		break;
	case Lockdown_Silent:
		m_lockdown->setLockDownText("Silent");
		m_lockdown->setSelected(true);
		m_modeSelected = m_lockdown;
		m_editModeWidget->setVisible(true);
		break;
	case Lockdown_Default:
		m_lockdown->setLockDownText("Default");
		m_lockdown->setSelected(true);
		m_modeSelected = m_lockdown;
		m_editModeWidget->setVisible(true);
		break;
	case TrustAll_Mode:
		break;
	case TrustAll_5Mins:
		break;
	case TrustAll_30Mins:
		break;
	case TrustAll_NetReboot:
		break;
	case Observation_Mode:
		break;
	default:
		break;
	}
	setModeText();
}

void SettingsProtectionModes::editModeClicked()
{
	Protection_Modes mode = Protection_Modes::None;
	QRect geometry = AppSetting::getInstance()->getAppGeometry();

	if (m_modeSelected == m_lockdown)
	{
		lockdownDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 220, geometry.y() + 16, 440, 190);

		LockDown currentMode = lockdownDialog->getLockDownMode();

		switch (currentMode)
		{
		case LOCKDOWN_CANCEL:
			break;
		case LOCKDOWN_SILENT:
			transparent->showWidget();
			lockdownDialog->showDefaultDialog();
			transparent->hide();
			break;
		case LOCKDOWN_DEFAULT:
			transparent->showWidget();
			lockdownDialog->showSilentDialog();
			transparent->hide();
			break;
		default:
			break;
		}
		LockDown swichMode = lockdownDialog->getLockDownMode();

		if (swichMode == currentMode)
		{
			return;
		}

		switch (swichMode)
		{
		case LOCKDOWN_CANCEL:
			m_lockdown->setLockDownText("");
			return;
		case LOCKDOWN_SILENT:
			m_lockdown->setLockDownText("Silent");
			//can do something
			break;
		case LOCKDOWN_DEFAULT:
			m_lockdown->setLockDownText("Default");
			//can do something
			break;
		default:
			break;
		}
		mode = Protection_Modes::Lockdown_Mode;
	}
	else if (m_modeSelected == m_trustall)
	{
		transparent->showWidget();
		trustAllDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 220, geometry.y() + 16, 440, 156);
		trustAllDialog->showDialog();
		transparent->hide();

		TrustAll trustAll = trustAllDialog->getDialogButtonClicked();
		if (trustAll == TrustAll::TRUSTALL_CANCEL)
		{
			return;
		}
		TrustAllTime trustAllTime = trustAllDialog->getTrustAllTime();

		switch (trustAllTime)
		{
		case TRUSTALL_5MINS:
			mode = Protection_Modes::TrustAll_5Mins;

			break;
		case TRUSTALL_30MINS:
			mode = Protection_Modes::TrustAll_30Mins;

			break;
		case TRUSTALL_NEXTREBOOT:
			mode = Protection_Modes::TrustAll_NetReboot;

			break;
		default:
			mode = Protection_Modes::TrustAll_Mode;
			break;
		}
		
	}
	emit changeMode(mode,true);

}
