#pragma once

#include <QWidget>
#include "ui_lockdowndialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
class LockDownDialog : public QDialog
{
	Q_OBJECT

public:
	LockDownDialog(QDialog*parent = Q_NULLPTR);
	~LockDownDialog();
	void setTitleText(QString text);
	void setCancelText(QString text);
	void setSilentText(QString text);
	void setDefaultText(QString text);
	void showDialog();
	void showSilentDialog();
	void showDefaultDialog();
	LockDown getLockDownMode();

public slots:
	void cancelClicked();
	void silentClicked();
	void defaultClicked();
	void changeTheme();

private:
	Ui::LockDownDialog ui;
	void setStyle();
	QLabel* m_titleText;
	QPushButton * m_cancelBtn;
	QPushButton * m_silentBtn;
	QPushButton * m_DefaultBtn;
	QVBoxLayout* layout;
	LockDown m_lockdownMode;
};
