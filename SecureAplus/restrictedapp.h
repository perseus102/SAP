#pragma once

#include <QWidget>
#include "ui_rectrictedapp.h"
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include "search.h"
#include "filenametable.h"
#include "sapscrollarea.h"
class RestrictedApp : public QWidget
{
	Q_OBJECT

public:
	RestrictedApp(QWidget *parent = Q_NULLPTR);
	~RestrictedApp();
	void setDescText(QString text);

protected:
	void resizeEvent(QResizeEvent *event) override;
private:
	Ui::RectrictedApp ui;

	QLabel*			m_description;
	Search *		m_searchWg;
	QVBoxLayout*	m_layout;
	QLabel*			m_resetToDefault;
	QPushButton*	m_removeBtn;
	QPushButton*	m_addBtn;

	FileNameTable*	m_fileNameTable;

	void setStyle();


};
