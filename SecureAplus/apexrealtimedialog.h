#pragma once

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include "ui_apexrealtimedialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
class APEXRealTimeDialog : public QDialog
{
	Q_OBJECT

public:
	APEXRealTimeDialog(QWidget *parent = Q_NULLPTR);
	~APEXRealTimeDialog();
	void showDialog();
	void setTitleText(QString text);
	void setNoBtnText(QString text);
	void setYesBtnText(QString text);
	DialogCode getBtnClicked();
private slots:
	void NoBtnClicked();
	void YesBtnClicked();
	void changeTheme();
private:
	Ui::APEXRealTimeDialog ui;
	void setStyle();
	QLabel* m_titleText;
	QPushButton * m_noBtn;
	QPushButton * m_yesBtn;
	QVBoxLayout*  m_layout;
	DialogCode m_buttonCode;
};
