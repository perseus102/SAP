#pragma once

#include <QWidget>
#include "ui_addcommandlineruledialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include "sapcombobox.h"

class AddnEditCmdLineRuleDialog : public QDialog
{
	Q_OBJECT

public:
	AddnEditCmdLineRuleDialog(QDialog *parent = Q_NULLPTR);
	~AddnEditCmdLineRuleDialog();
	void showDialog(bool isEdit);
	void setEditInfo(CommandLineRuleString& cmdRuleStr);

private slots:
	void cancelClicked();
	void addnSaveClicked();
	void changeTheme();
	void textChanged();
	void comboboxChangeIndex(int);

signals:
	void addCmdLineRule(CommandLineRuleString cmdRuleStr);
	void editCmdLineRule(CommandLineRuleString cmdRuleStr);

private:
	Ui::AddCommandLineRuleDialog ui;
	QLabel*			m_titleText;
	QWidget*		m_processWg;
	QLineEdit*		m_process;
	QLabel*			m_paramText;
	SAPCombobox*	m_ruleCbb;
	SAPCombobox*	m_caseSensCbb;
	QWidget*		m_stringWg;
	QLineEdit*		m_string;
	SAPCombobox*	m_actionCbb;

	QPushButton*	m_addnSaveBtn;
	QPushButton*	m_cancelBtn;
	QVBoxLayout*	m_layout;

	bool			m_isEdit;
	QStringList		m_cmdRuleList;
	QStringList		m_sensitiveList;
	QStringList		m_actionList;

	void setStyle();
	void setAddBtnStyle();

};
