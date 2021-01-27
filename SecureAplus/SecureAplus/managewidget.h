#pragma once

#include <QWidget>
#include <QWidget>
#include <qDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "define.h"
#include "ui_managewidget.h"
#include "util.h"
#include "appsetting.h"
namespace Ui {
	class ManageWidget;
}


class ManageWidget : public QWidget
{
	Q_OBJECT

public:
	ManageWidget(QWidget *parent = Q_NULLPTR);
	~ManageWidget();

	void changeBackground(ColorType type);
	void setWidgetText(QString text);
	void setSelected(bool isSeletected);
	void setWidgetStyle();

signals:
	void setActive();

public slots:
	void changeTheme();
	void valueAnimation(const QVariant& value);

protected:
	void mousePressEvent(QMouseEvent *event);
	bool event(QEvent * e);

private:
	Ui::ManageWidget	*ui;
	QLabel				*m_manageIcon;
	QLabel				*m_manageText;
	QVBoxLayout			*m_manageLayout;
	bool				m_Selected;
	QIcon				icon;
	QVariantAnimation	*m_backgroundAnimation;

	void setIcon();
	void setWidgetTextStyle();
	void setBackground();
};
