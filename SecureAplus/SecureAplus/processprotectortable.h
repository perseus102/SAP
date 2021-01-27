#pragma once

#include <QWidget>
#include "ui_processprotectortable.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "sapcheckbox.h"
#include "sapscrollarea.h"

struct ProcessProtectorRow
{
	QWidget* rowWg;
	SAPCheckBox* checkBox;
	QLabel*	processProtector;
	QLabel* line;
};

class ProcessProtectorTable : public QWidget
{
	Q_OBJECT

public:
	ProcessProtectorTable(QWidget *parent = Q_NULLPTR);
	~ProcessProtectorTable();

private slots:
	void changeTheme();
	void allCheckBoxSetCheck(Qt::CheckState);
	void scrollBarRangeChanged(int min, int max);
	void rowCheckBoxSetCheck(Qt::CheckState);

public slots:
	void removeRows();
	void AddProcess(QString process);
	void resetToDefault();
	void AddProcessFromDialog(QString process);

signals:
	void setRemoveBtnDisabled(bool disabled);

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	Ui::ProcessProtectorTable ui;

	QWidget*		m_titleWg;
	QLabel*			m_processText;
	SAPCheckBox*	m_checkAllBox;
	QVBoxLayout*	m_layout;
	SAPSCrollArea*	m_scrollView;
	QWidget*		m_rowWg;
	QVBoxLayout*	m_rowLayout;

	QList<ProcessProtectorRow*> m_processRowMap;
	QStringList m_fileNameList;
	QStringList m_defaultList;

	int m_rowCount;

	void setStyle();
	void setRowStyle(ProcessProtectorRow* row);
;

	Button_Check_State buttonCheckState();

	void setCheckBoxsState();
};
