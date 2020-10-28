#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::GridWidget)
{
	ui->setupUi(this);

	m_frame = new QFrame();

	m_gridLayout = new QVBoxLayout;
	m_gridLayout->setContentsMargins(0, 0, 0, 0);
	m_gridLayout->setSpacing(0);
	m_gridLayout->addWidget(m_frame);


	m_frame->setFixedSize(173, 130);

	setLayout(m_gridLayout);
	setBackground();

	/* Connection */
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &GridWidget::changeTheme);

}

GridWidget::~GridWidget()
{
}

void GridWidget::setBackground()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_frame->setStyleSheet("QFrame {background-color:"+ GRID_BACKGROUND_LIGHT_THEME_COLOR +";" 
			"border-radius:6px;}"
			"QFrame:hover{border: 2px solid " + GRID_BORDER_LIGHT_THEME_COLOR + ";}");
		break;

	case Theme_Type::Dark_Theme:
		m_frame->setStyleSheet("QFrame {background-color:" + GRID_BACKGROUND_DARK_THEME_COLOR + ";"
			"border-radius:6px;}"
			"QFrame:hover{border: 2px solid " + GRID_BORDER_DARK_THEME_COLOR + ";}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void GridWidget::changeTheme()
{
	setBackground();
}
