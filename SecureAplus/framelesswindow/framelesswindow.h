

#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>
#include <QScreen>
#include <QSizeGrip>
#include "ui_framelesswindow.h"
#include <qDebug>
#include <QDesktopServices>
#include "../util.h"
#include "../appsetting.h"
#include "../Config.h"
namespace Ui {
class FramelessWindow;
}

class FramelessWindow : public QWidget {
  Q_OBJECT

 public:
  explicit FramelessWindow(QWidget *parent = Q_NULLPTR);
  virtual ~FramelessWindow();
  void setContent(QWidget *w);

 private:
  bool leftBorderHit(const QPoint &pos);
  bool rightBorderHit(const QPoint &pos);
  bool topBorderHit(const QPoint &pos);
  bool bottomBorderHit(const QPoint &pos);
  void styleWindow(bool bActive, bool bNoState);
  void setWindowIcon();
  void setWindowTitle(const QString &text);
  QString getBackroundColor();


 private slots:
  void on_applicationStateChanged(Qt::ApplicationState state);
  void on_minimizeButton_clicked();
  void on_restoreButton_clicked();
  void on_maximizeButton_clicked();
  void on_closeButton_clicked();
  void on_windowTitlebar_doubleClicked();
  void on_helpButton_clicked();

public slots:
	void changeTheme();

 protected:
  virtual void changeEvent(QEvent *event);
  virtual void mouseDoubleClickEvent(QMouseEvent *event);
  virtual void checkBorderDragging(QMouseEvent *event);
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
  virtual bool eventFilter(QObject *obj, QEvent *event);

 private:
  Ui::FramelessWindow *ui;
  QRect m_StartGeometry;
  const quint8 CONST_DRAG_BORDER_SIZE = 20;
  bool m_bMousePressed;
  bool m_bDragTop;
  bool m_bDragLeft;
  bool m_bDragRight;
  bool m_bDragBottom;
};

#endif  // FRAMELESSWINDOW_H
