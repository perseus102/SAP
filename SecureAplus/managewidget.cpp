#include "managewidget.h"

ManageWidget::ManageWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ManageWidget)
{
	ui->setupUi(this);

	//Create Home Icon
	m_manageIcon = new QLabel();
	m_manageIcon->setFixedWidth(140);
	m_manageIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	m_manageText = new QLabel();
	m_manageText->setFont(FONT);
	m_manageText->setFixedWidth(140);
	m_manageText->setAlignment(Qt::AlignCenter);

	m_manageLayout = new QVBoxLayout(this);
	m_manageLayout->setSpacing(0);
	m_manageLayout->setContentsMargins(0, 0, 0, 0);
	m_manageLayout->addWidget(m_manageIcon);
	m_manageLayout->addWidget(m_manageText);
	setLayout(m_manageLayout);

	setFixedWidth(140);
	setFixedHeight(96);
	m_Selected = false;
	changeStatus();
	setWidgetText("Manage");

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ManageWidget::changeTheme);

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

void ManageWidget::setIcon()
{
	QIcon icon;

	if (m_Selected)
	{
		icon = util::getInstance()->ChangeSVGColor(MANAGE_ICON_PATH, TEXT_ICON_COLOR_ACTIVE);
	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			icon = util::getInstance()->ChangeSVGColor(MANAGE_ICON_PATH, TEXT_ICON_COLOR_LIGHT_THEME);

		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			icon = util::getInstance()->ChangeSVGColor(MANAGE_ICON_PATH, TEXT_ICON_COLOR_DARK_THEME);


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

void ManageWidget::changeStatus()
{
	setIcon();
	setBackground();
	setWidgetTextStyle();

}

void ManageWidget::setWidgetTextStyle()
{
	if (m_Selected)
	{

		m_manageText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_ACTIVE + "; padding-bottom: 10px;}");

	}
	else
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			m_manageText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_LIGHT_THEME + "; padding-bottom: 10px;}");
		}
		else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			m_manageText->setStyleSheet("QLabel {  color:" + TEXT_ICON_COLOR_DARK_THEME + "; padding-bottom: 10px;}");

		}
	}
}

void ManageWidget::setBackground()
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


void ManageWidget::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	if (!m_Selected)
	{
		m_Selected = !m_Selected;
		changeStatus();
		emit setActive();
	}
}

void ManageWidget::changeTheme()
{
	changeStatus();
	qDebug() << "ManageWidget Change themee";
}
