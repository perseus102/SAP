#include "homewidget.h"

HomeWidget::HomeWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::HomeWidget)
{
	ui->setupUi(this);

	/* Init Home icon */
	m_homeIcon = new QLabel();
	m_homeIcon->setFixedWidth(140);
	m_homeIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	/* Init Home title */
	m_homeText = new QLabel();
	m_homeText->setFont(FONT);
	m_homeText->setFixedWidth(140);
	m_homeText->setAlignment(Qt::AlignCenter);

	/* Init Home layout */
	m_homeLayout = new QVBoxLayout(this);
	m_homeLayout->setSpacing(0);
	m_homeLayout->setContentsMargins(0, 0, 0, 0);
	m_homeLayout->addWidget(m_homeIcon);
	m_homeLayout->addWidget(m_homeText);

	/* Set home widget layout */
	setLayout(m_homeLayout);

	setFixedWidth(140);
	setFixedHeight(96);

	/* Gradient background animation */
	m_backgroundAnimation = new QVariantAnimation();
	m_backgroundAnimation->setStartValue(0.00001);
	m_backgroundAnimation->setEndValue(0.9999);
	m_backgroundAnimation->setDuration(150);

	/* init */
	m_Selected = true;
	setWidgetStyle();
	setWidgetText("Home"); // Can use get text for multi language

	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &HomeWidget::changeTheme);
	connect(m_backgroundAnimation, &QVariantAnimation::valueChanged, this, &HomeWidget::valueAnimation);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeStatus, this, &HomeWidget::changeStatus);

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
	/*Change background with color type */
	switch (type)
	{
	case ColorType::Dark_Type:
		setStyleSheet("background-color:" + BTN_BACKGROUND_DARK + ";");
		break;

	case ColorType::Light_Type:
		setStyleSheet("background-color:" + BTN_BACKGROUND_LIGHT + ";");
		break;

	case ColorType::Gradient_Type:
		m_backgroundAnimation->setDirection(QAbstractAnimation::Backward);
		m_backgroundAnimation->start();
		break;

	default:
		break;
	}
}

void HomeWidget::setIcon()
{
	Status status = AppSetting::getInstance()->refreshStatus();

	if (status == Status::Protected_Status)
	{
		icon = util::getInstance()->ChangeSVGColor(HOME_PROTECTED_PATH, HOME_PROTECTED_COLOR);
	}
	else if (status == Status::Warning_Status)
	{

		icon = util::getInstance()->ChangeSVGColor(HOME_WARNING_PATH, HOME_WARNING_COLOR);
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

void HomeWidget::setWidgetStyle()
{
	setIcon();
	setBackground();
	setWidgetTextStyle();

}

void HomeWidget::setWidgetTextStyle()
{
	/* Set widget title style */
	if (m_Selected)
	{
		
		m_homeText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_ACTIVE + "; padding-bottom: 18px;}");

	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			m_homeText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_LIGHT_THEME  + "; padding-bottom: 18px;}");
		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			m_homeText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_DARK_THEME + "; padding-bottom: 18px;}");

		}
	}
}

void HomeWidget::setBackground()
{
	if (m_Selected)
	{
		/* if widget selected change background gradient */
		changeBackground(ColorType::Gradient_Type);
	}
	else
	{
		/* if widget unselected change background with theme color */
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


void HomeWidget::valueAnimation(const QVariant & value)
{
	/* Gradient animation when widget selected */
	if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
	{
		//setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 " + GRADIENT_START_LIGHT + ", stop:1 " + GRADIENT_END + ");");
		setStyleSheet("background: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0" + GRADIENT_START_LIGHT + ","
			"stop:" + value.toString() + " " + GRADIENT_START_LIGHT + ","
			"stop:1.0" + GRADIENT_END + ");");
	}
	else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
	{
		//setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 " + GRADIENT_START_DARK + ", stop:1 " + GRADIENT_END + ");");
		setStyleSheet("background: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0" + GRADIENT_START_DARK + ","
			"stop:" + value.toString() + " " + GRADIENT_START_DARK + ","
			"stop:1.0" + GRADIENT_END + ");");
	}
	
}

void HomeWidget::changeStatus()
{
	setIcon();
}

void HomeWidget::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	if (!m_Selected)
	{
		m_Selected = !m_Selected;
		setWidgetStyle();
		emit setActive();
		//AppSetting::getInstance()->setTheme(Theme_Type::Light_Theme);
	}
}

void HomeWidget::changeTheme()
{
	setWidgetStyle();
}


bool HomeWidget::event(QEvent* e)
{
	if (!m_Selected)
	{
		/* Hover widget */
		if (e->type() == QEvent::Enter)
		{
			m_homeIcon->setPixmap(icon.pixmap(29, 29));
		}
		/* Leave Widget */
		if (e->type() == QEvent::Leave)
		{
			m_homeIcon->setPixmap(icon.pixmap(35, 35));

		}
	}
	return QWidget::event(e); 
}