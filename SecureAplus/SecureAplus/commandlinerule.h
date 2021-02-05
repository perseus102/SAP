#pragma once

#include <QWidget>
#include "ui_commandlinerule.h"
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include "clickablelabel.h"
#include <QPushButton>
#include "widgettransparent.h"
#include "commandlineruletable.h"
#include "resetbutton.h"
class CommandLineRule : public QWidget
{
	Q_OBJECT

public:
	CommandLineRule(QWidget *parent = Q_NULLPTR);
	~CommandLineRule();

private slots:
	void removeButtonClicked();
	void addButtonClicked();
	void resetToDefaultClicked();

public slots:
	void setRemoveBtnDisabled(bool disabled);
	void changeTheme();

private:
	Ui::CommandLineRule ui;

	QLabel*	m_commandLineRuleDesc;

	QVBoxLayout*	m_layout;
	QPushButton*	m_removeBtn;
	QPushButton*	m_addBtn;

	CommandLineRuleTable*	m_commandLineRuleTable;

	ResetButton*		m_resetBtn;

	WidgetTransparent*	transparent;

	void setStyle();
	void setRemoveBtnStyle();
};
