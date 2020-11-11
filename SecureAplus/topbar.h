#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "define.h"
#include "ui_topbar.h"
#include "appsetting.h"
#include "util.h"
namespace Ui {
	class TopBar;
}

class BackButton : public QPushButton
{
    Q_OBJECT
public:
	BackButton(QWidget* parent = Q_NULLPTR);
	~BackButton();

public slots:
	void changeTheme();

protected:
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;

private:
	void initIcon();
	QIcon icon;
};

class TopBar : public QWidget
{
	Q_OBJECT

public:
	TopBar(QWidget *parent = Q_NULLPTR);
	~TopBar();
	void setDirectoryText(QString text);
	void setVisibleNaviButton(bool visible);
	QPushButton* getButton();

public slots:
	void changeTheme();

private:
	Ui::TopBar *ui;
	BackButton		*m_navigationBtn;
	QLabel			*m_Directory;
	QHBoxLayout		*m_topBarLayout;
	
	void setTextStyle();
};
