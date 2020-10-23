#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <QSizePolicy>
#include "statuswidget.h"
#include "homewidget.h"
#include "scanwidget.h"
#include "managewidget.h"
#include "settingwidget.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QGraphicsDropShadowEffect>
#include "appsetting.h"
#include "homecontent.h"
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = Q_NULLPTR);

	StatusWidget	*m_statusWidget;
	HomeWidget		*m_homeWidget;
	ScanWidget		*m_scanWidget;
	ManageWidget	*m_manageWidget;
	SettingWidget	*m_SettingWidget;

	~MainWindow();

signals:

public slots:
	void switchActiveWidget();
	void changeBackground();
protected:
	void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
	void setConnection();
	QObject *ActiveWidget;
	QWidget *firstPageWidget;
	QWidget *secondPageWidget;
	QWidget *thirdPageWidget;
	HomeContent *homeContent;
	QStackedWidget *stackedWidget;
	QPropertyAnimation *animation;
	QGraphicsOpacityEffect *effect;
};
#endif  // MAINWINDOW_H