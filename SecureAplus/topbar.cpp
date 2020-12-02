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
	//m_Directory			= new QLabel();
	m_navigationBtn		= new BackButton();
	m_topBarLayout		= new QHBoxLayout();

	/*Init Button */
	m_topBarLayout->setContentsMargins(0, 0, 0, 0);
	m_topBarLayout->setSpacing(10);

	//m_Directory->setFixedHeight(16);
	//m_Directory->setFont(FONT);
	//m_Directory->setAlignment(Qt::AlignLeft);
	setTextStyle();
	
	m_topBarLayout->addWidget(m_navigationBtn);
	//m_topBarLayout->addWidget(m_Directory);
	QLabel * spacerRight = new QLabel();
	m_topBarLayout->addWidget(spacerRight);

	/* Set layout */
	setLayout(m_topBarLayout);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &TopBar::changeTheme);
	connect(m_navigationBtn, &BackButton::clicked, this, &TopBar::backButtonClicked);
}

TopBar::~TopBar()
{
}

void TopBar::setDirectoryText(QString text)
{
	//m_Directory->setText(text);
}

void TopBar::setVisibleNaviButton(bool visible)
{
	m_navigationBtn->setVisible(visible);
}

QPushButton* TopBar::getButton()
{
	return m_navigationBtn;
}

void TopBar::addDir(QString dirText, Directory dir)
{
	ClickableLabel * newLabel = new ClickableLabel();
	newLabel->setFont(FONT);
	newLabel->setAlignment(Qt::AlignLeft);
	newLabel->setText(dirText);
	newLabel->setObjectName(dirText);

	QFontMetrics fm(FONT);
	int width = fm.width(dirText);
	newLabel->setFixedSize(width,16);

	if (!m_labelList.isEmpty())
	{
		QLabel * backSlash = new QLabel();
		backSlash->setFont(FONT);
		backSlash->setAlignment(Qt::AlignLeft);

		width = fm.width("\\");
		backSlash->setFixedSize(width, 16);
		backSlash->setText("\\");
		backSlash->setObjectName("\\");

		m_topBarLayout->insertWidget(m_topBarLayout->count() - 1, backSlash);

		m_backSlashList.append(backSlash);

	}

	m_topBarLayout->insertWidget(m_topBarLayout->count() - 1, newLabel);

	m_labelList.append(newLabel);
	m_DirectoryMap.insert(newLabel, dir);

	connect(newLabel, &ClickableLabel::clicked, this, &TopBar::labelClicked);

	setTextStyle();
}

ClickableLabel * TopBar::getLastLabel()
{
	if (!m_labelList.isEmpty())
	{
		return m_labelList.last();
	}
	return nullptr;
}

void TopBar::labelClicked()
{
	//int count = m_topBarLayout->count();
	//Top bar always have minimum 3 item ( 1 back button, 1 label, and spacer right)
	//if (count <= 3) return;

	for (int i = m_topBarLayout->count() - 2; i > 0; i--)
	{
		QWidget * widget = m_topBarLayout->itemAt(i)->widget();

		if (widget == sender())
		{
			for (auto &label : m_labelList)
			{
				if (label == widget)
				{
					Directory dir = m_DirectoryMap.value(label);
					emit labelDirClicked(dir);
				}
			}
			return;
		}

		m_topBarLayout->removeWidget(widget);
		widget->setParent(nullptr);

		for (auto &label : m_labelList) 
		{
			if (label == widget)
			{
				m_labelList.removeOne(label);
				break;
			}
		}

		for (auto &label : m_backSlashList)
		{
			if (label == widget)
			{
				m_backSlashList.removeOne(label);
				break;
			}
		}

		delete widget;
	}
}

void TopBar::backButtonClicked()
{
	int count = m_topBarLayout->count();
	//Top bar always have minimum 3 item ( 1 back button, 1 label, and spacer right)
	if (count <= 3) return;

	for (int i = m_topBarLayout->count() - 2; i >= 2; i--)
	{
		QWidget * widget = m_topBarLayout->itemAt(i)->widget();

		m_topBarLayout->removeWidget(widget);
		widget->setParent(nullptr);

		for (auto &label : m_labelList)
		{
			if (label == widget)
			{
				m_labelList.removeOne(label);
				delete widget;
				break;
			}

		}

		for (auto &label : m_backSlashList)
		{
			if (label == widget)
			{
				m_backSlashList.removeOne(label);
				delete widget;
				return;
			}
		}
	}



}

void TopBar::setTextStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		for (auto &label : m_labelList) {
			label->setStyleSheet("QLabel { color:" + TOP_BAR_TEXT_COLOR_LIGHT_THEME + ";}"
				"QLabel:hover{ color:" + TOP_BAR_TEXT_HOVER_COLOR_LT + ";}");
		}
		for (auto &label : m_backSlashList) {
			label->setStyleSheet("QLabel { color:" + TOP_BAR_TEXT_COLOR_LIGHT_THEME + ";}");
		}
		break;

	case Theme_Type::Dark_Theme:
		for (auto &label : m_labelList) {
			label->setStyleSheet("QLabel { color:" + TOP_BAR_TEXT_COLOR_DARK_THEME + ";}"
				"QLabel:hover{ color:" + TOP_BAR_TEXT_HOVER_COLOR_DT + ";}");
		}

		for (auto &label : m_backSlashList) {
			label->setStyleSheet("QLabel { color:" + TOP_BAR_TEXT_COLOR_DARK_THEME + ";}");
		}
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
