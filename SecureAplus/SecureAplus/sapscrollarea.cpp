#include "sapscrollarea.h"

SAPSCrollArea::SAPSCrollArea(QMargins margins,QWidget *parent)
	: QScrollArea(parent),
	m_margins(margins)
{
	ui.setupUi(this);
	setStyle();
	m_scrollBarTimer = new QTimer();

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SAPSCrollArea::changeTheme);
	connect(this->verticalScrollBar(), &QScrollBar::valueChanged, this, &SAPSCrollArea::scrollBarChangeValue);
	connect(m_scrollBarTimer, &QTimer::timeout, this, &SAPSCrollArea::scrollBarTimeout);
}

SAPSCrollArea::~SAPSCrollArea()
{

}

void SAPSCrollArea::scrollBarChangeValue(int)
{
	this->verticalScrollBar()->setVisible(true);
	setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
	if (m_scrollBarTimer->isActive())
	{
		m_scrollBarTimer->stop();
	}
	m_scrollBarTimer->start(1000);
}

void SAPSCrollArea::scrollBarTimeout()
{
	this->verticalScrollBar()->setVisible(false);
	setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
}

void SAPSCrollArea::setStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		this->setStyleSheet("background-color:transparent; border:0px");

		this->verticalScrollBar()->setStyleSheet(
			"QScrollBar:vertical {"
			"border: 0px solid " + VER_SCROLLBAR_TRACK_LT + ";"
			"background: " + VER_SCROLLBAR_TRACK_LT + ";"
			"width:10px;"
			"margin: " + QString::number(m_margins.top()) + "px " + QString::number(m_margins.right()) + "px " + QString::number(m_margins.bottom()) + "px " + QString::number(m_margins.left()) + "px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::handle:vertical {"
			"min-height: 0px;"
			"background-color: " + VER_SCROLLBAR_THUMB_LT + ";"
			"border: 0px solid none;"
			"width:10px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::add-line:vertical {"
			"height: 0px;"
			"subcontrol-position: bottom;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-line:vertical {"
			"height: 0px;"
			"subcontrol-position: top;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-page:vertical {"
			"background: none;"
			"}"

			"QScrollBar::add-page:vertical {"
			"background: none;"
			"}"
		);

		break;

	case Theme_Type::Dark_Theme:

		this->setStyleSheet("background-color:transparent; border:0px");
	
		this->verticalScrollBar()->setStyleSheet(
			"QScrollBar:vertical {"
			"border: 0px solid "+ VER_SCROLLBAR_TRACK_DT +";"
			"background: "+ VER_SCROLLBAR_TRACK_DT +";"
			"width:10px;"
			"margin: " + QString::number(m_margins.top()) + "px " + QString::number(m_margins.right()) + "px " + QString::number(m_margins.bottom()) + "px " + QString::number(m_margins.left()) + "px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::handle:vertical {"
			"min-height: 0px;"
			"background-color: " + VER_SCROLLBAR_THUMB_DT + ";"
			"border: 0px solid none;"
			"width:10px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::add-line:vertical {"
			"height: 0px;"
			"subcontrol-position: bottom;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-line:vertical {"
			"height: 0px;"
			"subcontrol-position: top;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-page:vertical {"
			"background: none;"
			"}"

			"QScrollBar::add-page:vertical {"
			"background: none;"
			"}"
		);

		this->horizontalScrollBar()->setStyleSheet(
			"QScrollBar:horizontal {"
			//"border: 0px solid " + VER_SCROLLBAR_TRACK_DT + ";"
			"background: " + VER_SCROLLBAR_TRACK_DT + ";"
			"height:10px;"
			//"margin: " + QString::number(m_margins.top()) + "px " + QString::number(m_margins.right()) + "px " + QString::number(m_margins.bottom()) + "px " + QString::number(m_margins.left()) + "px;"
			"margin: 0px 10px 5px 10px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::handle:horizontal {"
			"min-height: 0px;"
			"background-color: " + VER_SCROLLBAR_THUMB_DT + ";"
			"border: 0px solid none;"
			"height:10px;"
			"border-radius: 2px;"
			"}"

			"QScrollBar::add-line:horizontal {"
			"height: 0px;"
			"subcontrol-position: right;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-line:horizontal {"
			"height: 0px;"
			"subcontrol-position: left;"
			"subcontrol-origin: margin;"
			"}"

			"QScrollBar::sub-page:horizontal {"
			"background: none;"
			"}"

			"QScrollBar::add-page:horizontal {"
			"background: none;"
			"}"
		);

		break;

		//MORE THEME
	default:
		break;
	}
}

void SAPSCrollArea::changeTheme()
{
	setStyle();
}
