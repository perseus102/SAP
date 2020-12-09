#pragma once

#include <QWidget>
#include "ui_anitivirus.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "switch.h"
#include "sapcombobox.h"
class Anitivirus : public QWidget
{
	Q_OBJECT

public:
	Anitivirus(QWidget *parent = Q_NULLPTR);
	~Anitivirus();

private slots:
	void changeTheme();
	void toggleClicked();
	void comboboxChangeIndex(int index);
private:
	Ui::Anitivirus ui;
	QVBoxLayout*	m_layout;

	QLabel*			m_APEX;
	QLabel*			m_APEXDesc;
	QLabel*			m_sensitivity;
	SAPCombobox*	m_sensitivityCbb;
	QLabel*			m_APEXRealtime;
	QLabel*			m_APEXRealtimeDesc;
	Switch*			m_APEXRealtimeToggle;
	QLabel*			m_register;
	QLabel*			m_registerDesc;
	Switch*			m_registerToggle;

	QLabel*		m_APEXLine;
	QLabel*		m_APEXRealTimeLine;

	void setStyle();
	void setLabelText();
};
