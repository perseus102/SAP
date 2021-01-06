#pragma once

#include <QWidget>
#include "ui_addresappdialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>

class AddResAppDialog : public QDialog
{
	Q_OBJECT

public:
	AddResAppDialog(QDialog *parent = Q_NULLPTR);
	~AddResAppDialog();
	void showDialog();

private slots:
	void cancelClicked();
	void addFileClicked();
	void changeTheme();

signals:
	void addFile(QString fileName);

private:
	Ui::AddResAppDialog ui;
	QLabel*			m_titleText;
	QPushButton*	m_cancelBtn;
	QPushButton*	m_addFileBtn;
	QVBoxLayout*	m_layout;
	QLineEdit*		m_fileNameLabel;
	QWidget*		m_fileNameWg;

	void setStyle();
};
