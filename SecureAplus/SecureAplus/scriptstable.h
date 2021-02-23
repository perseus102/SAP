#pragma once
#include "stdafx.h"
#include <QWidget>
#include "ui_scriptstable.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "sapcheckbox.h"
#include "sapscrollarea.h"

struct ScriptsRow
{
	QWidget* rowWg;
	SAPCheckBox* checkBox;
	QLabel*	interpreter;
	QLabel*	extensions;
	QLabel* line;
};

struct ScriptsString
{
	QString	interpreter;
	QString	extensions;
};

class ScriptsTable : public QWidget
{
	Q_OBJECT

public:
	ScriptsTable(QWidget *parent = Q_NULLPTR);
	~ScriptsTable();
	void loadData(BOOLEAN force = FALSE);

private slots:
	void refresh();
	void changeTheme();
	void allCheckBoxSetCheck(Qt::CheckState);
	void scrollBarRangeChanged(int min, int max);
	void rowCheckBoxSetCheck(Qt::CheckState);

public slots:
	void AddScripts(QString &interpreter, QString &extensions);
	void AddScriptsGUIOnly(LPCWSTR interpreter, LPCWSTR extensions);
	void AddScriptsFromDialog(QString &interpreter, QString &extensions);
	void removeRows();
	void resetToDefault();

signals:
	void setRemoveBtnDisabled(bool disabled);

protected:
	void resizeEvent(QResizeEvent *event) override;


private:
	Ui::ScriptsTable ui;

	QWidget*		m_titleWg;
	SAPCheckBox*	m_checkAllBox;
	QLabel*			m_interpreter;
	QLabel*			m_extensions;

	QVBoxLayout*	m_layout;
	SAPSCrollArea*	m_scrollView;
	QWidget*		m_rowWg;
	QVBoxLayout*	m_rowLayout;

	QList<ScriptsString> m_defaultList;
	QList<ScriptsRow*> m_scriptsRowMap;
	QStringList m_fileNameList;

	HANDLE hStopEvent;
	HANDLE hCompletedEvent;
	HANDLE hThread;
	QTimer* m_timerRefresh;
	CRITICAL_SECTION m_cs;
	std::vector<std::pair<QString, QString>> m_incomingData;

	int m_rowCount;
	void setStyle();
	void setRowStyle(ScriptsRow* row);
	Button_Check_State buttonCheckState();
	void setCheckBoxsState();
	void resizeLabel();

};
