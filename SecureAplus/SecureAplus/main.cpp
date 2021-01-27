#include <QApplication>
#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include "framelesswindow/framelesswindow.h"
#include "framelesswindow/windowdragger.h"
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // create frameless window (and set windowState or title)
  FramelessWindow framelessWindow;
 
  // create our mainwindow instance
  MainWindow *mainWindow = new MainWindow;
  // add the mainwindow to our custom frameless window
  framelessWindow.setContent(mainWindow);
  framelessWindow.show();

  return a.exec();
}
