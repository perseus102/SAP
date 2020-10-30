#include "topbar.h"

TopBar::TopBar(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TopBar)
{
	ui->setupUi(this);

	/* Init */
	m_Directory			= new QLabel();
	m_naviButton		= new QPushButton();
	m_topBarLayout		= new QHBoxLayout();

	/*Init Button */
	m_naviButton->setIcon(QIcon(TOPBAR_ICON_PATH));
	m_naviButton->setIconSize(QSize(10, 16));
	m_naviButton->setFixedSize(10, 16);
	m_topBarLayout->setContentsMargins(0, 0, 0, 0);
	m_topBarLayout->setSpacing(10);

	m_Directory->setFixedHeight(16);
	m_Directory->setFont(FONT);
	m_Directory->setAlignment(Qt::AlignLeft);
	m_Directory->setStyleSheet("QLabel { color:" + TEXT_ICON_COLOR_DARK_THEME + ";}");

	m_topBarLayout->addWidget(m_naviButton);
	m_topBarLayout->addWidget(m_Directory);

	/* Set layout */
	setLayout(m_topBarLayout);
}

TopBar::~TopBar()
{
}

void TopBar::setDirectoryText(QString text)
{
	m_Directory->setText(text);
}

void TopBar::setVisibleNaviButton(bool visible)
{
	m_naviButton->setVisible(visible);
}
