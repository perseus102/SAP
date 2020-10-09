#include <QApplication>
#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include "framelesswindow/framelesswindow.h"
#include "framelesswindow/windowdragger.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // style our application with custom style
  //a.setStyle(new Style);

  // create frameless window (and set windowState or title)
  FramelessWindow framelessWindow;
 
  framelessWindow.setWindowIcon(QIcon(":/images/icon.png"));

  // create our mainwindow instance
  MainWindow *mainWindow = new MainWindow;

  // add the mainwindow to our custom frameless window
  framelessWindow.setContent(mainWindow);
  framelessWindow.show();

  return a.exec();
}
