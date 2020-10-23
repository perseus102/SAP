#pragma once

#include <QWidget>
#include <qDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "define.h"
#include "ui_scanwidget.h"
#include "util.h"
#include "appsetting.h"

namespace Ui {
	class ScanWidget;
}
class ScanWidget : public QWidget
{
	Q_OBJECT

public:
	ScanWidget(QWidget *parent = Q_NULLPTR);
	~ScanWidget();
	void changeBackground(ColorType type);
	void setWidgetText(QString text);
	void setSelected(bool isSeletected);
	void changeStatus();
	void setIcon();
	void setWidgetTextStyle();
	void setBackground();

signals:
	void setActive();

public slots:
	void changeTheme();

protected:
	void mousePressEvent(QMouseEvent *event);


private:
	Ui::ScanWidget	*ui;
	QLabel			*m_scanIcon;
	QLabel			*m_scanText;
	QVBoxLayout		*m_scanLayout;
	bool			m_Selected;

};