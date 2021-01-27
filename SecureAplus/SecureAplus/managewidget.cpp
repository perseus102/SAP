#include "managewidget.h"

ManageWidget::ManageWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ManageWidget)
{
	ui->setupUi(this);

	/* init manage icon */
	m_manageIcon = new QLabel();
	m_manageIcon->setFixedWidth(140);
	m_manageIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	/* init manage title */
	m_manageText = new QLabel();
	m_manageText->setFont(FONT);
	m_manageText->setFixedWidth(140);
	m_manageText->setAlignment(Qt::AlignCenter);

	/* init manage layout */
	m_manageLayout = new QVBoxLayout(this);
	m_manageLayout->setSpacing(0);
	m_manageLayout->setContentsMargins(0, 0, 0, 0);
	m_manageLayout->addWidget(m_manageIcon);
	m_manageLayout->addWidget(m_manageText);

	/* set manage widget layout */
	setLayout(m_manageLayout);

	setFixedWidth(140);
	setFixedHeight(96);

	m_Selected = false;
	setWidgetStyle();
	setWidgetText("Manage");// Can use get text for multi language

	/* Gradient background animation */
	m_backgroundAnimation = new QVariantAnimation();
	m_backgroundAnimation->setStartValue(0.00001);
	m_backgroundAnimation->setEndValue(0.9999);
	m_backgroundAnimation->setDuration(150);

	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ManageWidget::changeTheme);
	connect(m_backgroundAnimation, &QVariantAnimation::valueChanged, this, &ManageWidget::valueAnimation);


}

ManageWidget::~ManageWidget()
{
	delete	ui;
	delete	m_manageIcon;
	delete	m_manageText;
	delete	m_manageLayout;

	ui				= nullptr;
	m_manageIcon	= nullptr;
	m_manageText	= nullptr;
	m_manageLayout	= nullptr;

}


void ManageWidget::changeBackground(ColorType type)
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

	//MORE TYPE
	default:
		break;
	}
}

void ManageWidget::setIcon()
{

	if (m_Selected)
	{
		icon = util::getInstance()->ChangeSVGColor(MANAGE_ICON_PATH, TEXT_ICON_COLOR_ACTIVE);
	}
	else
	{
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			icon = util::getInstance()->ChangeSVGColor(MANAGE_ICON_PATH, TEXT_ICON_COLOR_LIGHT_THEME);
			break;

		case Theme_Type::Dark_Theme:
			icon = util::getInstance()->ChangeSVGColor(MANAGE_ICON_PATH, TEXT_ICON_COLOR_DARK_THEME);
			break;

		//MORE THEME
		default:
			break;
		}
		
	}

	m_manageIcon->setPixmap(icon.pixmap(35, 35));

}

void ManageWidget::setWidgetText(QString text)
{

	m_manageText->setText(text);
}

void ManageWidget::setSelected(bool isSeletected)
{
	m_Selected = isSeletected;
}

void ManageWidget::setWidgetStyle()
{
	setIcon();
	setBackground();
	setWidgetTextStyle();

}

void ManageWidget::setWidgetTextStyle()
{
	/* if widget selected */
	if (m_Selected)
	{
		/* Set widget title style */
		m_manageText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_ACTIVE + "; padding-bottom: 18px;}");
	}
	else
	{
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			m_manageText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_LIGHT_THEME + "; padding-bottom: 18px;}");
			break;

		case Theme_Type::Dark_Theme:
			m_manageText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_DARK_THEME + "; padding-bottom: 18px;}");
			break;

			//MORE THEME
		default:
			break;
		}
	}
}

void ManageWidget::setBackground()
{
	if (!m_Selected)
	{
		/* if widget unselected change background with theme color */
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			changeBackground(ColorType::Light_Type);
			break;

		case Theme_Type::Dark_Theme:
			changeBackground(ColorType::Dark_Type);
			break;

			//MORE THEME
		default:
			break;
		}
	}
	else
	{
		/* if widget selected change background gradient */
		changeBackground(ColorType::Gradient_Type);
	}

}

void ManageWidget::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	if (!m_Selected)
	{
		m_Selected = !m_Selected;
		setWidgetStyle();
		emit setActive();
	}
}

void ManageWidget::changeTheme()
{
	setWidgetStyle();
}


bool ManageWidget::event(QEvent* e)
{
	if (!m_Selected)
	{
		/* Hover widget */
		if (e->type() == QEvent::Enter)
		{
			m_manageIcon->setPixmap(icon.pixmap(32, 29));
		}
		/* Leave Widget */
		if (e->type() == QEvent::Leave)
		{
			m_manageIcon->setPixmap(icon.pixmap(35, 35));
		}
	}
	return QWidget::event(e);
}

void ManageWidget::valueAnimation(const QVariant& value)
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