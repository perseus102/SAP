#include "allowliststatus.h"

AllowListStatus::AllowListStatus(AllowList_Type allistType, AllowList_States allistState, QWidget *parent)
	: QWidget(parent),
	m_allowListType(allistType),
	m_allowListState(allistState)
{
	ui.setupUi(this);
	//setFixedSize(444, 50);
	setContentsMargins(0, 0, 0, 0);

	m_allowListWidget = new QWidget();
	m_allowListWidget->setFixedHeight(50);
	m_allowListLayout = new QVBoxLayout();
	m_allowListLayout->setContentsMargins(0, 0, 0, 0);
	m_allowListLayout->setSpacing(0);
	m_allowListLayout->addWidget(m_allowListWidget);
	setLayout(m_allowListLayout);

	m_layout = new QHBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	m_allowListWidget->setLayout(m_layout);

	m_allowListNameLabel = new QLabel();
	//m_allowListNameLabel->setFixedWidth(206);
	//m_allowListNameLabel->setMinimumWidth(206);
	m_allowListNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_allowListNameLabel->setFont(FONT);

	m_statusIcon = new QLabel();
	m_statusIcon->setFixedSize(12,12);
	m_statusIcon->setAlignment(Qt::AlignVCenter);

	m_statusTextLabel = new QLabel();
	//m_statusTextLabel->setFixedWidth(264);
	m_statusTextLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_statusTextLabel->setFont(FONT);

	QLabel *spacerLeft = new QLabel();
	spacerLeft->setFixedWidth(22);

	QLabel *spacerCenterIcon = new QLabel();
	spacerCenterIcon->setFixedWidth(10);

	m_layout->addWidget(spacerLeft);
	m_layout->addWidget(m_allowListNameLabel);
	m_layout->addWidget(m_statusIcon);
	m_layout->addWidget(spacerCenterIcon);
	m_layout->addWidget(m_statusTextLabel);

	if (m_allowListType == AllowList_Type::Allist_Creation)
	{
		//m_statusTextLabel->setFixedWidth(113);

		m_viewButton = new QPushButton();
		m_viewButton->setFixedSize(60, 24);
		m_layout->addWidget(m_viewButton);

		setViewBtnText("View");//call api multi language
		setViewBtnStyle();

		QLabel *spacerRight = new QLabel();
		spacerRight->setFixedWidth(22);
		m_layout->addWidget(spacerRight);


		connect(m_viewButton, &QPushButton::clicked, this, &AllowListStatus::viewBtnClick);
	}
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &AllowListStatus::changeTheme);
	setStyle();

}

AllowListStatus::~AllowListStatus()
{
}

void AllowListStatus::setAllowListName(QString name)
{
	m_allowListNameLabel->setText(name);
}

void AllowListStatus::setStatusText(QString text)
{
	m_statusTextLabel->setText(text);

}

void AllowListStatus::setAllowState(AllowList_States allistState)
{
	m_allowListState = allistState;
	setStyle();
}

AllowList_States AllowListStatus::getAllowState()
{
	return m_allowListState;
}

void AllowListStatus::setViewBtnText(QString text)
{
	m_viewButton->setText(text);
}

void AllowListStatus::viewBtnClick()
{
	emit viewBtnClicked();
}

void AllowListStatus::resizeEvent(QResizeEvent*)
{
	if (m_allowListType == AllowList_Type::Allist_Creation)
	{
		m_allowListNameLabel->setFixedSize((this->width() / 2) - 22, 50);

	}

}

void AllowListStatus::setStyle()
{
	QIcon dotStatusIcon;
	m_statusIcon->setStyleSheet("QLabel {border-radius:0px;}");

	switch (m_allowListState)
	{
	case Allist_Building:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, ALLOW_LIST_STATUS_BUILDING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + ALLOW_LIST_STATUS_BUILDING + ";border-radius:0px;}");
		break;

	case Allist_Completed:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, ALLOW_LIST_STATUS_COMPLETED);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + ALLOW_LIST_STATUS_COMPLETED + ";border-radius:0px;}");
		break;

	case Allist_Running:
		dotStatusIcon = util::getInstance()->ChangeCircleSVGColor(DOT_STATUS, ALLOW_LIST_STATUS_RUNNING);
		m_statusTextLabel->setStyleSheet("QLabel {color:" + ALLOW_LIST_STATUS_RUNNING + ";border-radius:0px;}");
		break;

		//more state
	default:
		break;
	}
	m_statusIcon->setPixmap(dotStatusIcon.pixmap(12, 12));

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		this->setStyleSheet("background-color:" + ALLOW_LIST_BACKGROUND_LT + ";");
		m_allowListNameLabel->setStyleSheet("QLabel {color:" + APP_CONTROL_TITLE_TEXT_LT + ";border-radius:0px;}");
		break;

	case Theme_Type::Dark_Theme:
		this->setStyleSheet("background-color:" + ALLOW_LIST_BACKGROUND_DT + ";");
		m_allowListNameLabel->setStyleSheet("QLabel {color:" + APP_CONTROL_TITLE_TEXT_DT + ";border-radius:0px;}");

		break;

		//MORE THEME
	default:
		break;
	}

}

void AllowListStatus::setViewBtnStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_viewButton->setStyleSheet("QPushButton {background-color:none; color: " + APP_CONTROL_TITLE_TEXT_LT + ";"
												"border-radius:2px;"
												"border: 1px solid " + APP_CONTROL_TITLE_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:
		m_viewButton->setStyleSheet("QPushButton {background-color:none; color: " + APP_CONTROL_TITLE_TEXT_DT + ";"
												"border-radius:2px;"
												"border: 1px solid " + APP_CONTROL_TITLE_TEXT_DT + ";}");

		break;

		//MORE THEME
	default:
		break;
	}
}

void AllowListStatus::changeTheme()
{
	setStyle();
	if (m_allowListType == AllowList_Type::Allist_Creation)
	{
		setViewBtnStyle();
	}
}
