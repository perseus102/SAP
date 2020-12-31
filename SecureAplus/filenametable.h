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
	QLabel* m_line;
};

class FileNameTable : public QWidget
{
	Q_OBJECT

public:
	FileNameTable(QWidget *parent = Q_NULLPTR);
	~FileNameTable();
	void AddFileName(QString fileName);

private slots:
	void changeTheme();
	void allCheckBoxSetCheck(Qt::CheckState);
	void scrollBarRangeChanged(int min, int max);
	void rowCheckBoxSetCheck(Qt::CheckState);
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

	QMap<QString, FileNameRow*> m_fileNameRowMap;

	void setStyle();
	void setRowStyle(FileNameRow* row);
	
	int m_rowCount;

};
