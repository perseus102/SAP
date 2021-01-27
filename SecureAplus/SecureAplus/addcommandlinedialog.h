#pragma once

#include <QWidget>
#include "ui_addcommandlinedialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
#include <QTextEdit>

class AddCommandLineDialog : public QDialog
{
	Q_OBJECT

public:
	AddCommandLineDialog(QDialog *parent = Q_NULLPTR);
	~AddCommandLineDialog();

	void showDialog();

private slots:
	void cancelClicked();
	void addFileClicked();
	void changeTheme();
	void cmdTextChange();

signals:
	void addCommandLine(QString commandLine);

private:
	Ui::AddCommandLineDialog ui;

	QLabel*			m_titleText;
	QTextEdit*		m_commandLine;
	QVBoxLayout*	m_cmdLayout;

	QPushButton*	m_addFileBtn;
	QPushButton*	m_cancelBtn;

	void setStyle();
	void setAddBtnStyle();
};
