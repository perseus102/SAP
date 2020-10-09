#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "homewidget.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = Q_NULLPTR);

	HomeWidget *home_widget;

	~MainWindow();
private slots:
	void home_btnClick();

protected:
	void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;
	QPushButton* home_btn;
	bool home_btn_Clicked = true;
};
#endif  // MAINWINDOW_H