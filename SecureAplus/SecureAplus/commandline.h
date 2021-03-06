#pragma once

#include <QWidget>
#include "ui_commandline.h"
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include "clickablelabel.h"
#include <QPushButton>
#include "widgettransparent.h"
#include "commandlinetable.h"
#include "addcommandlinedialog.h"
#include "resetbutton.h"

class CommandLine : public QWidget
{
	Q_OBJECT

public:
	CommandLine(QWidget *parent = Q_NULLPTR);
	~CommandLine();
	void loadData();

private slots:
	void removeButtonClicked();
	void addButtonClicked();
	void resetToDefaultClicked();

public slots:
	void setRemoveBtnDisabled(bool disabled);
	void changeTheme();

private:
	Ui::CommandLine ui;

	QVBoxLayout*	m_layout;
	QPushButton*	m_removeBtn;
	QPushButton*	m_addBtn;

	CommandLineTable*	m_commandLineTable;

	ResetButton*		m_resetBtn;

	WidgetTransparent*	transparent;
	AddCommandLineDialog* m_addCommandLineDialog;

	void setStyle();
	void setRemoveBtnStyle();
};
