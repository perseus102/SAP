#include "settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::SettingWidget)
{
	ui->setupUi(this);

	//Create Home Icon
	m_settingIcon = new QLabel();
	m_settingIcon->setFixedWidth(140);
	m_settingIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	m_settingText = new QLabel();
	m_settingText->setFont(FONT);
	m_settingText->setFixedWidth(140);
	m_settingText->setAlignment(Qt::AlignCenter);

	m_settingLayout = new QVBoxLayout(this);
	m_settingLayout->setSpacing(0);
	m_settingLayout->setContentsMargins(0, 0, 0, 0);
	m_settingLayout->addWidget(m_settingIcon);
	m_settingLayout->addWidget(m_settingText);
	setLayout(m_settingLayout);

	setFixedWidth(140);
	setFixedHeight(96);
	m_Selected = false;
	changeStatus();
	setWidgetText("Settings");

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SettingWidget::changeTheme);

}

SettingWidget::~SettingWidget()
{
	delete	ui;
	delete	m_settingIcon;
	delete	m_settingText;
	delete	m_settingLayout;

	ui				= nullptr;
	m_settingIcon	= nullptr;
	m_settingText	= nullptr;
	m_settingLayout	= nullptr;
}

void SettingWidget::changeBackground(ColorType type)
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

void SettingWidget::setIcon()
{
	QIcon icon;

	if (m_Selected)
	{
		icon = util::getInstance()->ChangeSVGColor(SETTING_ICON_PATH, TEXT_ICON_COLOR_ACTIVE);
	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			icon = util::getInstance()->ChangeSVGColor(SETTING_ICON_PATH, TEXT_ICON_COLOR_LIGHT_THEME);

		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			icon = util::getInstance()->ChangeSVGColor(SETTING_ICON_PATH, TEXT_ICON_COLOR_DARK_THEME);


		}
	}

	m_settingIcon->setPixmap(icon.pixmap(35, 35));

}

void SettingWidget::setWidgetText(QString text)
{

	m_settingText->setText(text);
}

void SettingWidget::setSelected(bool isSeletected)
{
	m_Selected = isSeletected;
}

void SettingWidget::changeStatus()
{
	setIcon();
	setBackground();
	setWidgetTextStyle();

}

void SettingWidget::setWidgetTextStyle()
{
	if (m_Selected)
	{

		m_settingText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_ACTIVE + "; padding-bottom: 10px;}");

	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			m_settingText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_LIGHT_THEME + "; padding-bottom: 10px;}");
		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			m_settingText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_DARK_THEME + "; padding-bottom: 10px;}");

		}
	}
}

void SettingWidget::setBackground()
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


void SettingWidget::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	if (!m_Selected)
	{
		m_Selected = !m_Selected;
		changeStatus();
		emit setActive();
	}
}

void SettingWidget::changeTheme()
{
	changeStatus();
	qDebug() << "SettingWidget Change themee";
}