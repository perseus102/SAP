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
#include <QLineEdit>

struct CommandLineRuleRow
{
	QWidget* rowWg;
	SAPCheckBox* checkBox;
	QLabel*	process;
	QLabel* rule;
	QLabel* caseSensitive;
	QLabel* string;
	QLabel* action;
	QLabel* line;
};


class CommandLineRuleTable : public QWidget
{
	Q_OBJECT

public:
	CommandLineRuleTable(QWidget *parent = Q_NULLPTR);
	~CommandLineRuleTable();
	CommandLineRuleString getEditCmdLineRuleInfo();

private slots:
	void changeTheme();
	void allCheckBoxSetCheck(Qt::CheckState);
	void rowCheckBoxSetCheck(Qt::CheckState);
	void sortBtnClicked();
	void scrollbarChangeValue(int value);

public slots:
	void AddCommandLineRule(CommandLineRuleString &commandLine);
	void AddCommandLineRuleFromDialog(CommandLineRuleString commandLine);
	void editCommandLineRule(CommandLineRuleString commandLine);
	void removeRows();
	void resetToDefault(); 

signals:
	void setRemoveBtnDisabled(bool disabled);
	void setEditBtnDisabled(bool disabled);

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	Ui::CommandLineRuleTable ui;

	QWidget*		m_titleWg;
	SAPCheckBox*	m_checkAllBox;
	QLabel*			m_process;
	QPushButton*	m_sortProcessBtn;
	QLabel*			m_parameters;
	QPushButton*	m_sortparamBtn;
	QLabel*			m_string;
	QLabel*			m_action;
	bool			m_processSortUp;
	bool			m_paramSortUp;


	QLineEdit*					m_caseSensitiveEdt;
	QLineEdit*					m_rulesEdt;
	QLineEdit*					m_actionsEdt;

	WidgetTransparent*	transparent;
	QList<CommandLineRuleString> m_defaultList;
	QList<CommandLineRuleRow*> m_commandLineRowMap;
	//QList<CommandLineRuleRow*> resizeRow;

	QVBoxLayout*	m_layout;
	SAPSCrollArea*	m_scrollView;
	SAPSCrollArea*	m_titleScroll;
	QWidget*		m_rowWg;
	QVBoxLayout*	m_rowLayout;

	int m_rowCount;

	void setStyle();
	void setRowStyle(CommandLineRuleRow* row);

	Button_Check_State buttonCheckState();

	void setCheckBoxsState();

	void setSortBtnStyle(QPushButton* btn);

};
