#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::GridWidget)
{
	ui->setupUi(this);

	/* Init frame widget */
	m_frame = new QFrame();

	/* Init widget layout */
	m_layout = new QVBoxLayout;
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_frame->setFixedSize(174, 130);
	m_layout->addWidget(m_frame);

	/* Set layout */
	setLayout(m_layout);

	/* Init frame content layout */
	m_contentLayout= new QVBoxLayout;
	m_contentLayout->setContentsMargins(1, 15, 1, 15);
	m_contentLayout->setSpacing(14);
	m_gridIcon = new QLabel();
	m_gridIcon->setFixedWidth(170);
	//m_gridIcon->setFixedHeight(50);
	//m_gridIcon->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	m_gridIcon->setAlignment(Qt::AlignCenter);

	/* Init grid title */
	m_gridTitle = new QLabel();
	m_gridTitle->setFont(FONT);
	m_gridTitle->setFixedWidth(170);
	//m_gridTitle->setFixedHeight(30);
	m_gridTitle->setAlignment(Qt::AlignCenter);
	m_gridTitle->setWordWrap(true);

	/* Init grid sub title */
	m_gridSubTitle = new QLabel();
	m_gridSubTitle->setFont(GRID_SUB_TITLE_FRONT);
	m_gridSubTitle->setFixedWidth(170);
	m_gridSubTitle->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	m_gridSubTitle->setWordWrap(true);
	m_contentLayout->addWidget(m_gridIcon);
	m_contentLayout->addWidget(m_gridTitle);
	m_contentLayout->addWidget(m_gridSubTitle);

	/* Set frame layout */
	m_frame->setLayout(m_contentLayout);

	setBackground();
	setIcon();
	setTextStyle();

	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &GridWidget::changeTheme);
}

GridWidget::~GridWidget()
{
}

void GridWidget::setBackground()
{
	/* Set background with theme style */
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_frame->setStyleSheet("QFrame {background-color:"+ GRID_BACKGROUND_LIGHT_THEME_COLOR +";" 
			"border-radius:6px;}"
			"QFrame:hover{border: 1px solid " + GRID_BORDER_LIGHT_THEME_COLOR + ";}"
			"QLabel:hover{border: none;}"
			"QLabel { border-radius:0px;}");
		break;

	case Theme_Type::Dark_Theme:
		m_frame->setStyleSheet("QFrame {background-color:" + GRID_BACKGROUND_DARK_THEME_COLOR + ";"
			"border-radius:6px;}"
			"QFrame:hover{border: 1px solid " + GRID_BORDER_DARK_THEME_COLOR + ";}"
			"QLabel:hover{border: none;}"
			"QLabel { border-radius:0px;}");
		break;

		//MORE THEME
	default:
		break;
	}

}

void GridWidget::setIcon()
{
	/* Set icon with theme style */
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		icon = util::getInstance()->ChangeSVGColor(GRID_WIDGET_ICON_PATH, GRID_RING_LIGHT_THEME_COLOR);
		break;

	case Theme_Type::Dark_Theme:
		icon = util::getInstance()->ChangeSVGColor(GRID_WIDGET_ICON_PATH, GRID_RING_DARK_THEME_COLOR);

		break;

		//MORE THEME
	default:
		break;
	}
	m_gridIcon->setPixmap(icon.pixmap(30, 30));
}

void GridWidget::setTitleText(QString text)
{
	m_gridTitle->setText(text);
}

void GridWidget::setSubTitleText(QString text)
{
	m_gridSubTitle->setText(text);
	qDebug() << "m_gridSubTitle: " << m_gridSubTitle->height();
}

void GridWidget::mousePressEvent(QMouseEvent* event)
{
	emit pressWidget();
}

void GridWidget::setTextStyle()
{
	/* Set text style with theme style */
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_gridTitle->setStyleSheet("QLabel {  color:" + GRID_TITLE_LIGHT_THEME_COLOR + "; border-radius:0px;}");
		m_gridSubTitle->setStyleSheet("QLabel {  color:" + GRID_SUB_TITLE_LIGHT_THEME_COLOR + ";border-radius:0px;}");
		break;

	case Theme_Type::Dark_Theme:
		m_gridTitle->setStyleSheet("QLabel {  color:" + GRID_TITLE_DARK_THEME_COLOR + ";border-radius:0px;}");
		m_gridSubTitle->setStyleSheet("QLabel {  color:" + GRID_SUB_TITLE_DARK_THEME_COLOR + "; border-radius:0px;}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void GridWidget::changeTheme()
{
	setBackground();
	setIcon();
	setTextStyle();
}
