#pragma once

#include <QWidget>
#include "ui_addprocessprotectordialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>

class AddProcessProtectorDialog : public QDialog
{
	Q_OBJECT

public:
	AddProcessProtectorDialog(QDialog *parent = Q_NULLPTR);
	~AddProcessProtectorDialog();
	void showDialog();

private slots:
	void cancelClicked();
	void addClicked();
	void changeTheme();
	void textChange(QString text);

signals:
	void addProcess(QString process);

private:
	Ui::AddProcessProtectorDialog ui;

	QLabel*			m_titleText;
	QLabel*			m_descText;
	QPushButton*	m_cancelBtn;
	QPushButton*	m_addFileBtn;
	QVBoxLayout*	m_layout;
	QLineEdit*		m_processLabel;
	QWidget*		m_processWg;

	void setStyle();
	void setAddBtnStyle();
};
