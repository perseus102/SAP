#pragma once

#include <QWidget>
#include "ui_copycommandlinedialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
#include <QTextEdit>
#include <QClipboard>
class CopyCommandLineDialog : public QDialog
{
	Q_OBJECT

public:
	CopyCommandLineDialog(QDialog *parent = Q_NULLPTR);
	~CopyCommandLineDialog();
	void showDialog(QString comandLine);

private slots:
	void cancelClicked();
	void copyClicked();
	void changeTheme();
	void cmdTextChange();

signals:
	void copyToClipBoard(QString commandLine);

private:
	Ui::CopyCommandLineDialog ui;
	QLabel*			m_titleText;
	QTextEdit*		m_commandLine;
	QVBoxLayout*	m_cmdLayout;

	QPushButton*	m_copyBtn;
	QPushButton*	m_cancelBtn;
	QString			m_commandLineStr;

	void setStyle();
};
