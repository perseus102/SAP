#pragma once

#include <QWidget>
#include "ui_addscriptdialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>

class AddScriptDialog : public QDialog
{
	Q_OBJECT

public:
	AddScriptDialog(QDialog *parent = Q_NULLPTR);
	~AddScriptDialog();
	void showDialog();

private slots:
	void cancelClicked();
	void addFileClicked();
	void changeTheme();
	void textChange(const QString &text);
signals:
	void addScript(QString &interpreter, QString &extensions);
private:
	Ui::AddScriptDialog ui;

	QLabel*			m_titleText;
	QLabel*			m_scriptInterpreter;
	QLineEdit*		m_filePath;
	QWidget*		m_filePathWg;

	QWidget*		m_fileExtWg;
	QLabel*			m_fileExtensions;
	QLabel*			m_fileExtensionsDesc;

	QLineEdit*		m_fileExtensionEdit;

	QVBoxLayout*	m_layout;

	QPushButton*	m_addFileBtn;
	QPushButton*	m_cancelBtn;

	void setStyle();
	void setAddBtnStyle();
};
