#include "upgradedialog.h"

UpgradeDialog::UpgradeDialog(QDialog *parent)
	: QDialog(parent, Qt::FramelessWindowHint)
{
	ui.setupUi(this);
	setFixedSize(300, 300);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(0, 12, 12, 0);
	m_layout->setSpacing(0);

	m_exitButton = new QPushButton();
	m_exitButton->setFixedSize(14, 14);

	m_iconLabel = new QLabel();
	m_iconLabel->setFixedSize(50, 50);

	m_titleText = new QLabel();
	m_titleText->setFixedHeight(30);
	m_titleText->setWordWrap(true);
	m_titleText->setFont(LARGE_FONT);
	m_titleText->setAlignment(Qt::AlignBottom | Qt::AlignVCenter);

	m_upgradeButton = new QPushButton();
	m_upgradeButton->setFixedSize(110, 28);

	/* Init exit button */
	QWidget *exitWg = new QWidget();
	exitWg->setFixedHeight(14);
	QLabel *exitSpacerLeft = new QLabel();
	QHBoxLayout *exitLayout = new QHBoxLayout();
	exitLayout->setContentsMargins(0, 0, 0, 0);
	exitLayout->setSpacing(0);

	exitWg->setLayout(exitLayout);
	exitSpacerLeft->setFixedSize(270, 14);
	exitLayout->addWidget(exitSpacerLeft);
	exitLayout->addWidget(m_exitButton);

	m_layout->addWidget(exitWg);

	/* Init icon */
	QWidget *iconWg = new QWidget();
	iconWg->setFixedHeight(50);
	QLabel *iconSpacerLeft = new QLabel();
	QLabel *iconSpaceRight = new QLabel();
	QHBoxLayout *iconLayout = new QHBoxLayout();
	iconLayout->setContentsMargins(0, 0, 0, 0);
	iconLayout->setSpacing(0);
	iconSpacerLeft->setFixedSize(125, 50);
	iconWg->setLayout(iconLayout);
	iconLayout->addWidget(iconSpacerLeft);
	iconLayout->addWidget(m_iconLabel);
	iconLayout->addWidget(iconSpaceRight);

	m_layout->addWidget(iconWg);


	/* Init title text */
	QWidget *titleWg = new QWidget();
	titleWg->setFixedHeight(30);
	QLabel *titleSpacerLeft = new QLabel();
	//QLabel *titleSpaceRight = new QLabel();
	QHBoxLayout *titleLayout = new QHBoxLayout();
	titleLayout->setContentsMargins(0, 0, 0, 0);
	titleLayout->setSpacing(0);
	titleSpacerLeft->setFixedSize(85, 30);
	titleWg->setLayout(titleLayout);
	titleLayout->addWidget(titleSpacerLeft);
	titleLayout->addWidget(m_titleText);

	m_layout->addWidget(titleWg);

	QLabel *spacerContent = new QLabel();
	spacerContent->setFixedHeight(32);

	m_layout->addWidget(spacerContent);

	/* Init content */
	QWidget *contentWg = new QWidget();
	contentWg->setFixedHeight(80);
	QLabel *contentSpacerLeft = new QLabel();
	QLabel *content = new QLabel();
	//QLabel *contentSpaceRight = new QLabel();
	QHBoxLayout *contentLayout = new QHBoxLayout();
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	content->setAlignment(Qt::AlignLeft);
	//content->setText("Content Here");
	contentSpacerLeft->setFixedSize(60, 80);
	content->setFixedHeight(80);
	contentWg->setLayout(contentLayout);
	contentLayout->addWidget(contentSpacerLeft);
	contentLayout->addWidget(content);
	//test
	content->setText("Lorem Ipsum \n\nLorem Ipsum dolor sit amit\n\nLorem Ipsum");
	content->setFont(FONT);
	content->setStyleSheet("color: " + OBSERVATION_TEXT_DT_LT + ";");
	m_layout->addWidget(contentWg);

	QLabel *spacerBtn = new QLabel();
	spacerBtn->setFixedHeight(24);
	m_layout->addWidget(spacerBtn);

	/* Init upgrade button */
	QWidget *upgradeWg = new QWidget();
	upgradeWg->setFixedHeight(28);
	QLabel *btnSpacerLeft = new QLabel();
	QLabel *btnSpaceRight = new QLabel();
	QHBoxLayout *btnLayout = new QHBoxLayout();
	btnLayout->setContentsMargins(0, 0, 0, 0);
	btnLayout->setSpacing(0);
	upgradeWg->setLayout(btnLayout);
	btnSpacerLeft->setFixedSize(95, 28);
	btnSpaceRight->setFixedSize(83, 28);

	btnLayout->addWidget(btnSpacerLeft);
	btnLayout->addWidget(m_upgradeButton);
	btnLayout->addWidget(btnSpaceRight);

	m_layout->addWidget(upgradeWg);

	QLabel * spacerBottom = new QLabel();
	m_layout->addWidget(spacerBottom);

	setLayout(m_layout);
	setStyle();
	setButtonIcon();
	setTitleText("Observation Mode");
	setUpgradeBtnText("Upgrade to Pro");

	m_observation = Observation::Observation_exit;

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &UpgradeDialog::changeTheme);
	connect(m_exitButton, &QPushButton::clicked, this, &UpgradeDialog::exitButtonClicked);
	connect(m_upgradeButton, &QPushButton::clicked, this, &UpgradeDialog::upgradeButtonClicked);

}

UpgradeDialog::~UpgradeDialog()
{
}

void UpgradeDialog::showDialog()
{
	m_observation = Observation::Observation_exit;
	activateWindow();
	raise();
	exec();
}

void UpgradeDialog::setTitleText(QString text)
{
	m_titleText->setText(text);
}

void UpgradeDialog::setUpgradeBtnText(QString text)
{
	m_upgradeButton->setText(text);
}

Observation UpgradeDialog::getObservation()
{
	return m_observation;
}

void UpgradeDialog::exitButtonClicked()
{
	m_observation = Observation::Observation_exit;
	this->close();
}

void UpgradeDialog::upgradeButtonClicked()
{
	m_observation = Observation::Observation_upgrade;
	this->close();
}

void UpgradeDialog::setStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color: " + OBSERVATION_BACKGROUND_DT + ";");
		m_titleText->setStyleSheet("color: " + OBSERVATION_TEXT_DT_LT + ";");
		m_upgradeButton->setStyleSheet("QPushButton {background-color: " + OBSERVATION_BUTTON_BACKGROUND_DT_LT + ";"
			"color: " + OBSERVATION_TEXT_DT_LT + ";"
			"border-radius:4px;}");
		break;

	case Theme_Type::Light_Theme:
		this->setStyleSheet("background-color: " + OBSERVATION_BACKGROUND_LT + ";");
		m_titleText->setStyleSheet("color: " + OBSERVATION_TEXT_DT_LT + ";");

		m_upgradeButton->setStyleSheet("QPushButton {background-color: " + OBSERVATION_BUTTON_BACKGROUND_DT_LT + ";"
			"color: " + OBSERVATION_TEXT_DT_LT + ";"
			"border-radius:4px;}");
		break;

		/* MORE THEME */
	default:
		break;
	}

}

void UpgradeDialog::setButtonIcon()
{
	QIcon iconExit(":/images/Observation/exit_icon.svg");
	QIcon observIcon(":/images/Observation/observation_icon.svg");
	m_exitButton->setStyleSheet("QPushButton {border: 0px;}");

	m_exitButton->setIcon(iconExit);
	m_exitButton->setIconSize(QSize(14,14));
	m_iconLabel->setPixmap(observIcon.pixmap(50, 50));
}

void UpgradeDialog::changeTheme()
{
	setStyle();

}
