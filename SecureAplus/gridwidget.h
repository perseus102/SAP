#pragma once

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "ui_gridwidget.h"

namespace Ui {
	class GridWidget;
}

class GridWidget : public QWidget
{
	Q_OBJECT

public:
	GridWidget(QWidget *parent = Q_NULLPTR);
	~GridWidget();

public slots:
	void changeTheme();

private:
	Ui::GridWidget *ui;
	QFrame *m_frame;
	QVBoxLayout *m_gridLayout;
	void setBackground();
};
