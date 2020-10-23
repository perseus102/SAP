#include "scanwidget.h"
#include <QSettings>
#include <QStringList>

ScanWidget::ScanWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ScanWidget)
{
	ui->setupUi(this);
	//Create Home Icon
	m_scanIcon = new QLabel();
	m_scanIcon->setFixedWidth(140);
	m_scanIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	m_scanText = new QLabel();
	m_scanText->setFont(FONT);
	m_scanText->setFixedWidth(140);
	m_scanText->setAlignment(Qt::AlignCenter);

	m_scanLayout = new QVBoxLayout(this);
	m_scanLayout->setSpacing(0);
	m_scanLayout->setContentsMargins(0, 0, 0, 0);
	m_scanLayout->addWidget(m_scanIcon);
	m_scanLayout->addWidget(m_scanText);
	setLayout(m_scanLayout);

	setFixedWidth(140);
	setFixedHeight(96);

	m_Selected = false;
	changeStatus();
	setWidgetText("Scan");

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ScanWidget::changeTheme);

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

void ScanWidget::setIcon()
{
	QIcon icon;

	if (m_Selected)
	{
		icon = util::getInstance()->ChangeSVGColor(SCAN_ICON_PATH, TEXT_ICON_COLOR_ACTIVE);
	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			icon = util::getInstance()->ChangeSVGColor(SCAN_ICON_PATH, TEXT_ICON_COLOR_LIGHT_THEME);

		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			icon = util::getInstance()->ChangeSVGColor(SCAN_ICON_PATH, TEXT_ICON_COLOR_DARK_THEME);


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

void ScanWidget::changeStatus()
{
	setIcon();
	setBackground();
	setWidgetTextStyle();

}

void ScanWidget::setWidgetTextStyle()
{
	if (m_Selected)
	{

		m_scanText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_ACTIVE + "; padding-bottom: 10px;}");

	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			m_scanText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_LIGHT_THEME + "; padding-bottom: 10px;}");
		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			m_scanText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_DARK_THEME + "; padding-bottom: 10px;}");

		}
	}
}

void ScanWidget::setBackground()
{
	if (!m_Selected)
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
	else
	{
		changeBackground(ColorType::Gradient_Type);
	}

}


void ScanWidget::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	if (!m_Selected)
	{
		m_Selected = !m_Selected;
		changeStatus();
		emit setActive();
		//AppSetting::getInstance()->setTheme(Theme_Type::Dark_Theme);

	}
}

void ScanWidget::changeTheme()
{
	changeStatus();
	qDebug() << "ScanWidget Change themee";
}
