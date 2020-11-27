#pragma once

#include <QLabel>
#include "ui_clickablelabel.h"

class ClickableLabel : public QLabel
{
	Q_OBJECT

public:
	ClickableLabel(QWidget *parent = Q_NULLPTR);
	~ClickableLabel();
signals:
	void clicked();
protected:
	void mousePressEvent(QMouseEvent* event);
private:
	Ui::ClickableLabel ui;
};
