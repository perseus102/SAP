#include "circleprocess.h"

CircleProcess::CircleProcess(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	timer = new QTimer();

	connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
	connect(AppSetting::getInstance(), &AppSetting::signal_changeMode, this, &CircleProcess::changeMode);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &CircleProcess::changeTheme);

	setStyle();

}

CircleProcess::~CircleProcess()
{
}

void CircleProcess::setCircleText(QString text)
{
	m_text = text;
}

void CircleProcess::startCountDown()
{
	progress = 1.0;
	this->update();
	timer->start(1000);
	setCircleText(time.toString("m:ss"));
}

void CircleProcess::setTime(int minutes)
{
	time.setHMS(0, minutes, 0);
	m_totalSec = minutes * 60;
}

void CircleProcess::changeTheme()
{
	setStyle();
}

void CircleProcess::updateCountdown()
{
	//count down end
	if ((time.minute() == 0) && (time.second() == 0))
	{
		timer->stop();
		emit endCountDown();
		//emit time end.
		return;
	}

	//countiue count down
	timer->start(1000);
	time = time.addSecs(-1);

	//Set text
	setCircleText(time.toString("m:ss"));

	//Calculate time remaining
	double calTime = (time.minute() * 60) + (time.second());
	progress = calTime / m_totalSec;
	this->update();
}

void CircleProcess::changeMode()
{
	//Stop timer when change mode
	if (timer->isActive())
	{
		timer->stop();
	}
}

void CircleProcess::paintEvent(QPaintEvent *)
{
	QPainter p(this);

	//Calculate Rect
	QRect drawingRect;
	drawingRect.setX(rect().x() + 80);
	drawingRect.setY(rect().y() + 80);
	drawingRect.setWidth(rect().width() - 80 * 2);
	drawingRect.setHeight(rect().height() - 80 * 2);

	//Calculate angle
	double startAngle = 100 * 16;
	double spanAngle = (progress * 355 * 16);
	double spanAngleBackground = 360 * 16;

	p.setRenderHint(QPainter::Antialiasing);

	//Draw circle background
	p.setPen(m_circleBackgroundPen);
	p.drawArc(drawingRect, startAngle, spanAngleBackground);

	//Draw text
	p.setPen(m_textPen);
	p.setFont(LARGE_FONT);
	p.drawText(drawingRect, Qt::AlignCenter, m_text);
	//Draw circle
	int arcLengthApproximation = 80 + 80 / 3;
	m_circlePen.setCapStyle(Qt::RoundCap);
	p.setPen(m_circlePen);
	p.drawArc(drawingRect, 95 * 16 - arcLengthApproximation, spanAngle);

}
void CircleProcess::setStyle()
{
	//Set style with theme
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_circlePen.setColor(QColor(CIRCLE_COLOR_LT));
		m_circleBackgroundPen.setColor(QColor(CIRCLE_BACKGROUND_COLOR_LT));
		m_textPen.setColor(QColor(CIRCLE_TEXT_COLOR_LT));

		break;

	case Theme_Type::Dark_Theme:
		m_circlePen.setColor(QColor(CIRCLE_COLOR_DT));
		m_circleBackgroundPen.setColor(QColor(CIRCLE_BACKGROUND_COLOR_DT));
		m_textPen.setColor(QColor(CIRCLE_TEXT_COLOR_DT));

		break;

		//MORE THEME
	default:
		break;
	}

	m_circlePen.setWidth(5);
	m_circleBackgroundPen.setWidth(5);
	m_textPen.setWidth(7);

}
void CircleProcess::setProgress(int val)
{
	progress = val;
	this->update();
}