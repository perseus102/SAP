#pragma once

#include <QWidget>
#include "ui_scansettings.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "clickablelabel.h"
#include "universalav.h"
#include <QStackedWidget>
#include <QScrollArea>

class ScanSettings : public QWidget
{
	Q_OBJECT

public:
	ScanSettings(QWidget *parent = Q_NULLPTR);
	~ScanSettings();
	void setTabText();

private slots:
	void TabClicked();

private:
	Ui::ScanSettings ui;
	QHBoxLayout*		m_contentLayout;
	QVBoxLayout*		m_tabLayout;
	QWidget*			m_tabWidget;
	ClickableLabel*		m_universalAV;
	ClickableLabel*		m_antivirus;
	ClickableLabel*		m_VulAssessment;

	QStackedWidget*		m_tabStackedWidget;
	QScrollArea*		m_scrollView;

	UniversalAV*		m_universalAVTab;
	void setStyle();
	void setTabActiveStyle(ClickableLabel* tab);
	void setTabInActiveStyle(ClickableLabel* tab);
};
