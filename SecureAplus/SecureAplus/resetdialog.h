#pragma once

#include <QWidget>
#include "ui_resetdialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>

class ResetDialog : public QDialog
{
	Q_OBJECT

public:
	ResetDialog(QDialog *parent = Q_NULLPTR);
	~ResetDialog();
	void showDialog();

private slots:
	void cancelClicked();
	void continueClicked();
	void changeTheme();

signals:
	void resetToDefault();

private:
	Ui::ResetDialog ui;
	QLabel*			m_titleText;
	QLabel*			m_decsText;
	QVBoxLayout*	m_layout;

	QPushButton*	m_continueBtn;
	QPushButton*	m_cancelBtn;

	void setStyle();
};
