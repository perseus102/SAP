#pragma once

#include <QWidget>
#include "ui_scripts.h"
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include "clickablelabel.h"
#include "scriptstable.h"
#include <QPushButton>
#include "widgettransparent.h"
#include "addscriptdialog.h"

class Scripts : public QWidget
{
	Q_OBJECT

public:
	Scripts(QWidget *parent = Q_NULLPTR);
	~Scripts();

private slots:
	void removeButtonClicked();
	void addButtonClicked();
	void resetToDefaultClicked();

public slots:
	void setRemoveBtnDisabled(bool disabled);
	void changeTheme();

private:
	Ui::Scripts ui;

	QVBoxLayout*	m_layout;
	QPushButton*	m_removeBtn;
	QPushButton*	m_addBtn;

	ScriptsTable*	m_scriptsTable;

	ClickableLabel*		m_resetToDefaultBtn;

	WidgetTransparent*	transparent;
	AddScriptDialog*	m_addScriptDialog;

	void setStyle();
	void setRemoveBtnStyle();
};
