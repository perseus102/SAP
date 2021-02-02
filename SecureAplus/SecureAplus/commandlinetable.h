#pragma once

#include <QWidget>
#include "ui_commandlinetable.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "sapcheckbox.h"
#include "sapscrollarea.h"

struct CommandLineRow
{
	QWidget* rowWg;
	SAPCheckBox* checkBox;
	QLabel*	commandLine;
	QLabel* line;
	QPushButton* copyBtn;
};
class CommandLineTable : public QWidget
{
	Q_OBJECT

public:
	CommandLineTable(QWidget *parent = Q_NULLPTR);
	~CommandLineTable();

private slots:
	void changeTheme();
	void allCheckBoxSetCheck(Qt::CheckState);
	void scrollBarRangeChanged(int min, int max);
	void rowCheckBoxSetCheck(Qt::CheckState);
	void scrollbarChangeValue(int value);

public slots:
	void AddCommandLine(QString commandLine);
	void AddCommandLineFromDialog(QString commandLine);
	void removeRows();
	void resetToDefault();

signals:
	void setRemoveBtnDisabled(bool disabled);

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	Ui::CommandLineTable ui;

	QWidget*		m_titleWg;
	SAPCheckBox*	m_checkAllBox;
	QLabel*			m_commandLine;
	QLabel*			m_action;

	QVBoxLayout*	m_layout;
	SAPSCrollArea*	m_scrollView;
	QWidget*		m_rowWg;
	QVBoxLayout*	m_rowLayout;


	QList<QString> m_defaultList;
	QList<CommandLineRow*> m_commandLineRowMap;
	QList<CommandLineRow*> resizeRow;

	int m_rowCount;

	void setStyle();
	void setRowStyle(CommandLineRow* row);

	Button_Check_State buttonCheckState();

	void setCheckBoxsState();
	void resizeLabel();
};
