#pragma once

#include <QWidget>
#include <QComboBox>
#include "ui_sapcombobox.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
class SAPCombobox : public QComboBox
{
	Q_OBJECT

public:
	SAPCombobox(QWidget *parent = Q_NULLPTR);
	~SAPCombobox();

private slots:
	void changeTheme();
private:
	Ui::SAPCombobox ui;
	void setStyle();

};
