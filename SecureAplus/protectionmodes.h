#pragma once

#include <QWidget>
#include "ui_protectionmodes.h"
#include "selectwidget.h"
#include <QVBoxLayout>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "flowlayout.h"
class ProtectionModes : public QWidget
{
	Q_OBJECT

public:
	ProtectionModes(QWidget *parent = Q_NULLPTR);
	~ProtectionModes();

signals:
	void changeMode(Protection_Modes);

public slots:
	void changeProtectMode();
	void changeTheme();
	void toogleChanged(bool isChecked);

private:
	Ui::ProtectionModes ui;
	SelectWidget* m_automatic;
	SelectWidget* m_interactive;
	SelectWidget* m_lockdown;
	SelectWidget* m_trustall;
	SelectWidget* m_observation;

	QVBoxLayout* m_layout;
	QObject* m_modeSelected;
	FlowLayout* m_selectLayout;
	QLabel* m_title;
	QLabel* m_modeTitle;
	QLabel* m_description;
	void setConnection();
	void setModeText();
	void setStyle();
	void switchMode();
};
