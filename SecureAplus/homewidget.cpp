#include "homewidget.h"

HomeWidget::HomeWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::HomeWidget)
{
	ui->setupUi(this);

	//Create Home Icon
	m_homeIcon = new QLabel();
	m_homeIcon->setFixedWidth(140);
	m_homeIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	m_homeText = new QLabel();
	m_homeText->setFont(FONT);
	m_homeText->setFixedWidth(140);
	m_homeText->setAlignment(Qt::AlignCenter);

	m_homeLayout = new QVBoxLayout(this);
	m_homeLayout->setSpacing(0);
	m_homeLayout->setContentsMargins(0, 0, 0, 0);
	m_homeLayout->addWidget(m_homeIcon);
	m_homeLayout->addWidget(m_homeText);
	setLayout(m_homeLayout);
	setFixedWidth(140);
	setFixedHeight(96);

	/* init */
	m_Selected = true;
	changeStatus();
	setWidgetText("Home");
	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &HomeWidget::changeTheme);

}

HomeWidget::~HomeWidget()
{
	delete	ui;
	delete	m_homeIcon;
	delete	m_homeText;
	delete	m_homeLayout;

	ui = nullptr;
	m_homeIcon = nullptr;
	m_homeText = nullptr;
	m_homeLayout = nullptr;

}

void HomeWidget::changeBackground(ColorType type)
{

	switch (type)
	{
	case ColorType::Dark_Type:
		setStyleSheet("background-color:" + BTN_BACKGROUND_DARK + ";");
		break;

	case ColorType::Light_Type:
		setStyleSheet("background-color:" + BTN_BACKGROUND_LIGHT + ";");
		break;

	case ColorType::Gradient_Type:
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 " + GRADIENT_START_LIGHT + ", stop:1 " + GRADIENT_END + ");");

		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 " + GRADIENT_START_DARK + ", stop:1 " + GRADIENT_END + ");");

		}
		break;

	default:
		break;
	}
}

void HomeWidget::setIcon()
{
	QIcon icon;
	Status status = AppSetting::getInstance()->getStatus();

	//if (m_Selected)
	//{
	//	if (status == Status::Protected_Status)
	//	{
	//		icon = util::getInstance()->ChangeSVGColor(HOME_PROTECTED_SELECTED_PATH, TEXT_ICON_COLOR_ACTIVE);

	//	}
	//	else if (status == Status::Warning_Status)
	//	{
	//		icon = util::getInstance()->ChangeSVGColor(HOME_WARNING_SELECTED_PATH, TEXT_ICON_COLOR_ACTIVE);

	//	}
	//}
	//else
	//{
	//	
	//}
	if (status == Status::Protected_Status)
	{
		icon = util::getInstance()->ChangeSVGColor(HOME_PROTECTED_UNSELECTED_PATH, HOME_PROTECTED_UNSELETED_COLOR);
	}
	else if (status == Status::Warning_Status)
	{

		icon = util::getInstance()->ChangeSVGColor(HOME_WARNING_UNSELECTED_PATH, HOME_WARNING_UNSELETED_COLOR);
	}

	m_homeIcon->setPixmap(icon.pixmap(35, 35));

}

void HomeWidget::setWidgetText(QString text)
{

	m_homeText->setText(text);
}

void HomeWidget::setSelected(bool isSeletected)
{
	m_Selected = isSeletected;
}

void HomeWidget::changeStatus()
{
	setIcon();
	setBackground();
	setWidgetTextStyle();

}

void HomeWidget::setWidgetTextStyle()
{
	if (m_Selected)
	{
		
		m_homeText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_ACTIVE + "; padding-bottom: 10px;}");

	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			m_homeText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_LIGHT_THEME  + "; padding-bottom: 10px;}");
		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			m_homeText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_DARK_THEME + "; padding-bottom: 10px;}");

		}
	}
}

void HomeWidget::setBackground()
{
	if (m_Selected)
	{
		changeBackground(ColorType::Gradient_Type);
	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			changeBackground(ColorType::Light_Type);
		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			changeBackground(ColorType::Dark_Type);
		}
	}

}


void HomeWidget::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	if (!m_Selected)
	{
		m_Selected = !m_Selected;
		changeStatus();
		emit setActive();
		//AppSetting::getInstance()->setTheme(Theme_Type::Light_Theme);
	}
}
void HomeWidget::changeTheme()
{
	changeStatus();
	qDebug() << "home Change themee";
}
