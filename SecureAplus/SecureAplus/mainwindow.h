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
#include "settingscontent.h"
#include "managecontent.h"
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
	void changeScreenView(Screen screen);

protected:
	void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
	void setConnection();
	QObject *ActiveWidget;
	QWidget *firstPageWidget;
	QWidget *secondPageWidget;
	HomeContent *m_homeContent;
	SettingsContent *m_settingContent;
	ManageContent *m_manageContent;
	QStackedWidget *stackedWidget;
	QPropertyAnimation *animation;
	QGraphicsOpacityEffect *effect;
};
#endif  // MAINWINDOW_H