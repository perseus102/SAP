#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "define.h"
#include "ui_topbar.h"

namespace Ui {
	class TopBar;
}

class TopBar : public QWidget
{
	Q_OBJECT

public:
	TopBar(QWidget *parent = Q_NULLPTR);
	~TopBar();
	void setDirectoryText(QString text);
	void setVisibleNaviButton(bool visible);
private:
	Ui::TopBar *ui;
	QPushButton		*m_naviButton;
	QLabel			*m_Directory;
	QHBoxLayout		*m_topBarLayout;
};
