#pragma once

#include <QWidget>
#include "ui_filenametable.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "sapcheckbox.h"
#include "sapscrollarea.h"

struct FileNameRow
{
	QWidget* rowWg;
	SAPCheckBox* checkBox;
	QLabel*	fileNameText;
	QLabel* line;
};

class FileNameTable : public QWidget
{
	Q_OBJECT

public:
	FileNameTable(QWidget *parent = Q_NULLPTR);
	~FileNameTable();

private slots:
	void changeTheme();
	void allCheckBoxSetCheck(Qt::CheckState);
	void scrollBarRangeChanged(int min, int max);
	void rowCheckBoxSetCheck(Qt::CheckState);

public slots:
	void removeRows();
	void AddFileName(QString fileName);
	void updateFilterRow(QStringList list);
	void setFilterRow(bool isFilter);
	void resetToDefault();
	void AddFileNameFromDialog(QString fileName);

signals:
	void addWord(QString word);
	void removeWord(QString word);
	void setRemoveBtnDisabled(bool disabled);
protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	Ui::FileNameTable ui;

	QWidget*		m_titleWg;
	QLabel*			m_titleText;
	SAPCheckBox*	m_checkAllBox;
	QVBoxLayout*	m_layout;
	SAPSCrollArea*	m_scrollView;
	QWidget*		m_rowWg;
	QVBoxLayout*	m_rowLayout;

	QMultiMap<QString, FileNameRow*> m_fileNameRowMap;
	QStringList m_defaultList;
	QStringList m_fileNameList;

	int m_rowCount;
	bool m_isFilter = false;
	int m_rowChecked = 0;
	int m_filterCount;

	void setStyle();
	void setRowStyle(FileNameRow* row);
	bool checkAllUnChecked();
	bool checkAllChecked();

	Button_Check_State buttonCheckState();

	void setCheckBoxsState();
};