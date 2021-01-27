#pragma once

#include <QWidget>
#include "ui_vulassessment.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "switch.h"

class SettingsVulAssessment : public QWidget
{
	Q_OBJECT

public:
	SettingsVulAssessment(QWidget *parent = Q_NULLPTR);
	~SettingsVulAssessment();
private slots:
	void changeTheme();
	void toggleClicked();
private:
	Ui::VulAssessment ui;
	QVBoxLayout*	m_layout;
	QLabel*			m_automaticCheck;
	QLabel*			m_automaticCheckDecs;
	Switch*			m_automaticToggle;

	void setStyle();
	void setLabelText();
};
