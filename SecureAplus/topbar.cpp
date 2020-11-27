#include "topbar.h"

BackButton::BackButton(QWidget* parent)
	: QPushButton(parent)
{
	setFixedSize(10, 16);
	setStyleSheet("QPushButton {border: 0px;}");
	initIcon();
	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &BackButton::changeTheme);
}

BackButton::~BackButton(){};

void BackButton::enterEvent(QEvent*)
{
	setIconSize(QSize(9, 14));
}

void BackButton::leaveEvent(QEvent*)
{
	setIconSize(QSize(10, 16));
}

void BackButton::initIcon()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		icon = util::getInstance()->ChangeSVGColor(TOPBAR_ICON_PATH, BACK_BUTTON_LIGHT_THEME_COLOR);
		break;

	case Theme_Type::Dark_Theme:
		icon = util::getInstance()->ChangeSVGColor(TOPBAR_ICON_PATH, BACK_BUTTON_DARK_THEME_COLOR);

		break;

		//MORE THEME
	default:
		break;
	}

	setIcon(icon);
	setIconSize(QSize(10, 16));
}

void BackButton::changeTheme()
{
	initIcon();
}

TopBar::TopBar(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TopBar)
{
	ui->setupUi(this);
	setFixedHeight(16);

	/* Init */
	m_Directory			= new QLabel();
	m_navigationBtn		= new BackButton();
	m_topBarLayout		= new QHBoxLayout();

	/*Init Button */
	m_topBarLayout->setContentsMargins(0, 0, 0, 0);
	m_topBarLayout->setSpacing(10);

	m_Directory->setFixedHeight(16);
	m_Directory->setFont(FONT);
	m_Directory->setAlignment(Qt::AlignLeft);
	setTextStyle();
	
	m_topBarLayout->addWidget(m_navigationBtn);
	m_topBarLayout->addWidget(m_Directory);

	/* Set layout */
	setLayout(m_topBarLayout);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &TopBar::changeTheme);
}

TopBar::~TopBar()
{
}

void TopBar::setDirectoryText(QString text)
{
	m_Directory->setText(text);
}

void TopBar::setVisibleNaviButton(bool visible)
{
	m_navigationBtn->setVisible(visible);
}

QPushButton* TopBar::getButton()
{
	return m_navigationBtn;
}

void TopBar::setTextStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_Directory->setStyleSheet("QLabel { color:" + TOP_BAR_TEXT_COLOR_LIGHT_THEME + ";}");

		break;

	case Theme_Type::Dark_Theme:
		m_Directory->setStyleSheet("QLabel { color:" + TOP_BAR_TEXT_COLOR_DARK_THEME + ";}");


		break;

		//MORE THEME
	default:
		break;
	}
}

void TopBar::changeTheme()
{
	setTextStyle();
}
