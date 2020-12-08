#pragma once

#include <QWidget>
#include "ui_vulassessment.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "switch.h"

class VulAssessment : public QWidget
{
	Q_OBJECT

public:
	VulAssessment(QWidget *parent = Q_NULLPTR);
	~VulAssessment();
private slots:
	void changeTheme();

private:
	Ui::VulAssessment ui;
	QVBoxLayout*	m_layout;
	QLabel*			m_automaticCheck;
	QLabel*			m_automaticCheckDecs;
	Switch*			m_automaticToggle;

	void setStyle();
	void setLabelText();
};
