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
	void setTitleText(QString text = NULL);
	void setSubTitleText(QString text = NULL);

signals:
	void pressWidget();

public slots:
	void changeTheme();

protected:
	void mousePressEvent(QMouseEvent* event);

private:
	Ui::GridWidget *ui;
	QFrame *m_frame;
	QVBoxLayout *m_layout;
	QVBoxLayout *m_contentLayout;
	QLabel			*m_gridIcon;
	QLabel			*m_gridTitle;
	QLabel			*m_gridSubTitle;
	QIcon			icon;

	void setBackground();
	void setIcon();
	void setTextStyle();
};
