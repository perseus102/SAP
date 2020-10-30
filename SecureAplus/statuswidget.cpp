#include "statuswidget.h"

StatusWidget::StatusWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::StatusWidget)
{
	ui->setupUi(this);
	//Create Home Icon
	m_statusLayout = new QVBoxLayout(this);
	m_statusLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_statusLayout);

	m_statusIcon = new QLabel();
	QIcon status_ico(":/images/status/status_protected_icon.svg");
	m_statusIcon->setPixmap(status_ico.pixmap(90, 90));
	m_statusIcon->setAlignment(Qt::AlignCenter);

	m_statusIcon->setFixedWidth(140);
	m_statusIcon->setStyleSheet("QLabel { color : #FFFFFF; }");

	m_statusLayout->addWidget(m_statusIcon);

	switch4 = new Switch("Auto Protect");
	m_statusLayout->addWidget(switch4);
	switch4->setChecked(true);
	//switch4->setDisabled(false);
	setFixedWidth(140);
	setFixedHeight(158);
	setIcon(ColorType::Default);
}

StatusWidget::~StatusWidget()
{
	delete	ui;
	delete	m_statusIcon;
	delete	m_statusLayout;

	ui				= nullptr;
	m_statusIcon	= nullptr;
	m_statusLayout	= nullptr;
}

void StatusWidget::setIcon(ColorType type)
{
	switch (type)
	{
	case ColorType::Default:
		break;
	case ColorType::Dark_Type:
		break;
	case ColorType::Light_Type:
		break;
	case ColorType::Gradient_Type:
		break;
	default:
		break;
	}

}
