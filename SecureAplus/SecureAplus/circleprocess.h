#pragma once

#include <QWidget>
#include <QLabel>
#include "ui_circleprocess.h"
#include <QPainter>
#include <QTimer>
#include <QTime>
#include "define.h"
#include "appsetting.h"
class CircleProcess : public QWidget
{
	Q_OBJECT

public:
	CircleProcess(QWidget *parent = Q_NULLPTR);
	~CircleProcess();

	void setCircleText(QString text);
	void startCountDown();
	void setTime(int minutes);

public slots:
	void setProgress(int val);
	void changeTheme();
	void updateCountdown();
	void changeMode();
signals:
	void endCountDown();

protected:
	void paintEvent(QPaintEvent *);

private:
	QPen m_circlePen;
	QPen m_circleBackgroundPen;
	QPen m_textPen;
	QString m_text;
	Ui::CircleProcess ui;
	double progress;
	double m_totalSec;
	void setStyle();
	QTimer* timer;
	QTime time;
};
