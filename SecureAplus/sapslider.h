#pragma once

#include <QWidget>
#include <QSlider>
#include "ui_sapslider.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"

class SAPSlider : public QSlider
{
	Q_OBJECT

public:
	SAPSlider(QWidget *parent = Q_NULLPTR);
	~SAPSlider();

private slots:
	void changeTheme();

private:
	Ui::SAPSlider ui;
	void setStyle();
};
