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

class CommandLine : public QWidget
{
	Q_OBJECT

public:
	CommandLine(QWidget *parent = Q_NULLPTR);
	~CommandLine();

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

	ClickableLabel*		m_resetToDefaultBtn;

	WidgetTransparent*	transparent;
	AddCommandLineDialog* m_addCommandLineDialog;

	void setStyle();
	void setRemoveBtnStyle();
};
