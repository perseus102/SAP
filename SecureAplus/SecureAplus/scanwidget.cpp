#include "scanwidget.h"
#include <QSettings>
#include <QStringList>

ScanWidget::ScanWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ScanWidget)
{
	ui->setupUi(this);

	/* Init scan icon */
	m_scanIcon = new QLabel();
	m_scanIcon->setFixedWidth(140);
	m_scanIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	/* Init scan title */
	m_scanText = new QLabel();
	m_scanText->setFont(FONT);
	m_scanText->setFixedWidth(140);
	m_scanText->setAlignment(Qt::AlignCenter);
	
	/* Init scan layout */
	m_scanLayout = new QVBoxLayout(this);
	m_scanLayout->setSpacing(0);
	m_scanLayout->setContentsMargins(0, 0, 0, 0);
	m_scanLayout->addWidget(m_scanIcon);
	m_scanLayout->addWidget(m_scanText);

	/* Set scan layout */
	setLayout(m_scanLayout);

	setFixedWidth(140);
	setFixedHeight(96);

	m_Selected = false;
	setWidgetStyle();
	setWidgetText("Scan"); // Can use get text for multi language

	/* Gradient background animation */
	m_backgroundAnimation = new QVariantAnimation();
	m_backgroundAnimation->setStartValue(0.00001);
	m_backgroundAnimation->setEndValue(0.9999);
	m_backgroundAnimation->setDuration(150);

	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ScanWidget::changeTheme);
	connect(m_backgroundAnimation, &QVariantAnimation::valueChanged, this, &ScanWidget::valueAnimation);


}

ScanWidget::~ScanWidget()
{
	delete	ui;
	delete	m_scanIcon;
	delete	m_scanText;
	delete	m_scanLayout;

	ui				= nullptr;
	m_scanIcon		= nullptr;
	m_scanText		= nullptr;
	m_scanLayout	= nullptr;

}

void ScanWidget::changeBackground(ColorType type)
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

	default:
		break;
	}
}

void ScanWidget::setIcon()
{

	if (m_Selected)
	{
		icon = util::getInstance()->ChangeSVGColor(SCAN_ICON_PATH, TEXT_ICON_COLOR_ACTIVE);
	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{

		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{


		}

		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			icon = util::getInstance()->ChangeSVGColor(SCAN_ICON_PATH, TEXT_ICON_COLOR_LIGHT_THEME);
			break;

		case Theme_Type::Dark_Theme:
			icon = util::getInstance()->ChangeSVGColor(SCAN_ICON_PATH, TEXT_ICON_COLOR_DARK_THEME);
			break;

			//MORE THEME
		default:
			break;
		}
	}

	m_scanIcon->setPixmap(icon.pixmap(35, 35));

}

void ScanWidget::setWidgetText(QString text)
{

	m_scanText->setText(text);
}

void ScanWidget::setSelected(bool isSeletected)
{
	m_Selected = isSeletected;
}

void ScanWidget::setWidgetStyle()
{
	setIcon();
	setBackground();
	setWidgetTextStyle();

}

void ScanWidget::setWidgetTextStyle()
{	
	/* Set widget title style */
	if (m_Selected)
	{

		m_scanText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_ACTIVE + "; padding-bottom: 18px;}");

	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			m_scanText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_LIGHT_THEME + "; padding-bottom: 18px;}");
		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			m_scanText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_DARK_THEME + "; padding-bottom: 18px;}");

		}
	}
}

void ScanWidget::setBackground()
{
	if (!m_Selected)
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
	else
	{
		/* if widget selected change background gradient */
		changeBackground(ColorType::Gradient_Type);
	}

}


void ScanWidget::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	if (!m_Selected)
	{
		m_Selected = !m_Selected;
		setWidgetStyle();
		emit setActive();
		//AppSetting::getInstance()->setTheme(Theme_Type::Dark_Theme);

	}
}

void ScanWidget::changeTheme()
{
	setWidgetStyle();
}

bool ScanWidget::event(QEvent* e)
{
	if (!m_Selected)
	{
		/* Hover widget */
		if (e->type() == QEvent::Enter)
		{
			m_scanIcon->setPixmap(icon.pixmap(29, 29));
		}
		/* Leave Widget */
		if (e->type() == QEvent::Leave)
		{
			m_scanIcon->setPixmap(icon.pixmap(35, 35));

		}
	}
	return QWidget::event(e);
}

void ScanWidget::valueAnimation(const QVariant& value)
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