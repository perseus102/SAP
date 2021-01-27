#pragma once

#include <QWidget>
#include "ui_widgettransparent.h"
#include "appsetting.h"
class WidgetTransparent : public QWidget
{
	Q_OBJECT

public:
	WidgetTransparent(QWidget *parent = Q_NULLPTR);
	~WidgetTransparent();
	void showWidget();
private slots:
	void changeTheme();
private:
	Ui::WidgetTransparent ui;
	void setStyle();

};
