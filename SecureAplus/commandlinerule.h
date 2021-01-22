#pragma once

#include <QWidget>
#include "ui_commandlinerule.h"

class CommandLineRule : public QWidget
{
	Q_OBJECT

public:
	CommandLineRule(QWidget *parent = Q_NULLPTR);
	~CommandLineRule();

private:
	Ui::CommandLineRule ui;
};
