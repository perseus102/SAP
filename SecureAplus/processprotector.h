#pragma once

#include <QWidget>
#include "ui_processprotector.h"
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include "clickablelabel.h"
#include <QPushButton>
#include "widgettransparent.h"
#include "processprotectortable.h"
#include "addprocessprotectordialog.h"
class ProcessProtector : public QWidget
{
	Q_OBJECT

public:
	ProcessProtector(QWidget *parent = Q_NULLPTR);
	~ProcessProtector();

private slots:
	void removeButtonClicked();
	void addButtonClicked();

public slots:
	void setRemoveBtnDisabled(bool disabled);
	void changeTheme();

private:
	Ui::ProcessProtector ui;

	QLabel*	m_scriptsDesc;

	QVBoxLayout*	m_layout;
	QPushButton*	m_removeBtn;
	QPushButton*	m_addBtn;

	ProcessProtectorTable*	m_processProtectorTable;

	WidgetTransparent*	transparent;
	AddProcessProtectorDialog* m_addProcessDialog;
	
	void setStyle();
	void setRemoveBtnStyle();
};
