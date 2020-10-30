#pragma once

#include <QWidget>
#include <qDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "define.h"
#include "ui_settingwidget.h"
#include "util.h"
#include "appsetting.h"

namespace Ui {
	class SettingWidget;
}

class SettingWidget : public QWidget
{
	Q_OBJECT

public:
	SettingWidget(QWidget *parent = Q_NULLPTR);
	~SettingWidget();

	void changeBackground(ColorType type);
	void setWidgetText(QString text);
	void setSelected(bool isSeletected);
	void setWidgetStyle();
	void setIcon();
	void setWidgetTextStyle();
	void setBackground();

signals:
	void setActive();

public slots:
	void changeTheme();

protected:
	void mousePressEvent(QMouseEvent *event);
	bool event(QEvent * e);

private:
	Ui::SettingWidget	*ui;
	QLabel				*m_settingIcon;
	QLabel				*m_settingText;
	QVBoxLayout			*m_settingLayout;
	bool				m_Selected;
	QIcon				icon;
};
