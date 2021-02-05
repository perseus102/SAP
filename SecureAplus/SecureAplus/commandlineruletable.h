#pragma once

#include <QWidget>
#include "ui_commandlineruletable.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "sapcheckbox.h"
#include "sapscrollarea.h"
#include "copybutton.h"
#include "widgettransparent.h"
#include "saptablecombobox.h"
#include <QLineEdit>

struct CommandLineRuleRow
{
	QWidget* rowWg;
	SAPCheckBox* checkBox;
	QLabel*	process;
	QLabel* caseSensitive;
	QLabel* string;
	QLabel* rule;
	QLabel* action;
};
struct CommandLineRuleString
{
	QString	processStr;
	QString caseSensitiveStr;
	QString string;
	QString ruleStr;
	QString actionStr;
};
class CommandLineRuleTable : public QWidget
{
	Q_OBJECT

public:
	CommandLineRuleTable(QWidget *parent = Q_NULLPTR);
	~CommandLineRuleTable();
private slots:
	void changeTheme();
	void allCheckBoxSetCheck(Qt::CheckState);
	void rowCheckBoxSetCheck(Qt::CheckState);
	void comboboxChangeIndex(int index);

public slots:
	void AddCommandLineRule(CommandLineRuleString &commandLine);
	void AddCommandLineRuleFromDialog(CommandLineRuleString &commandLine);
	void removeRows();
	void resetToDefault(); 

signals:
	void setRemoveBtnDisabled(bool disabled);

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	Ui::CommandLineRuleTable ui;

	QWidget*		m_titleWg;
	SAPCheckBox*	m_checkAllBox;
	QLabel*			m_process;
	QLabel*			m_string;

	SAPTableCombobox*			m_caseSensitiveCbb;
	SAPTableCombobox*			m_rulesCbb;
	SAPTableCombobox*			m_actionsCbb;

	QLineEdit*					m_caseSensitiveEdt;
	QLineEdit*					m_rulesEdt;
	QLineEdit*					m_actionsEdt;

	WidgetTransparent*	transparent;
	QList<QString> m_defaultList;
	QList<CommandLineRuleRow*> m_commandLineRowMap;
	//QList<CommandLineRuleRow*> resizeRow;

	QVBoxLayout*	m_layout;
	SAPSCrollArea*	m_scrollView;
	QWidget*		m_rowWg;
	QVBoxLayout*	m_rowLayout;

	int m_rowCount;

	void setStyle();
	void setRowStyle(CommandLineRuleRow* row);

	Button_Check_State buttonCheckState();

	void setCheckBoxsState();
};
