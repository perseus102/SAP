#pragma once

#include <QWidget>
#include "ui_compactdialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
class CompactDialog : public QDialog
{
	Q_OBJECT

public:
	CompactDialog(QDialog *parent = Q_NULLPTR);
	~CompactDialog();
	void showDialog();

private slots:
	void cancelBtnClicked();
	void startBtnClicked();
	void changeTheme();

signals:
	void startCompactAllowList();

private:
	Ui::CompactDialog ui;

	QLabel*			m_decsText;
	QVBoxLayout*	m_layout;

	QPushButton*	m_startBtn;
	QPushButton*	m_cancelBtn;

	void setStyle();
};
