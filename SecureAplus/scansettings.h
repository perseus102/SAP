#pragma once

#include <QWidget>
#include "ui_scansettings.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "clickablelabel.h"
#include "universalav.h"
#include "anitivirus.h"
#include "vulassessment.h"
#include "sapscrollarea.h"
#include <QStackedWidget>
#include <QScrollArea>
#include <QTimer>

class ScanSettings : public QWidget
{
	Q_OBJECT

public:
	ScanSettings(QWidget *parent = Q_NULLPTR);
	~ScanSettings();
	void setTabText();

private slots:
	void TabClicked();
	void changeTheme();
	void scrollBarChangeValue(int);
	void scrollBarTimeout();
protected:
	void resizeEvent(QResizeEvent *event) override;
private:
	Ui::ScanSettings ui;
	QHBoxLayout*		m_contentLayout;
	QVBoxLayout*		m_tabLayout;
	QWidget*			m_tabWidget;
	ClickableLabel*		m_universalAV;
	ClickableLabel*		m_antivirus;
	ClickableLabel*		m_VulAssessment;

	QStackedWidget*		m_tabStackedWidget;
	SAPSCrollArea*		m_scrollView;
	QFrame*				m_tabContentWidget;
	UniversalAV*		m_universalAVTab;
	Anitivirus*			m_antivirusTab;
	VulAssessment*		m_vulAssessmentTab;
	QObject*			m_activeTab;
	QTimer*				m_scrollBarTimer;
	void setStyle();
	void setTabStyle();
	void resizeTab();
	void setTabActiveStyle(ClickableLabel* tab);
	void setTabInActiveStyle(ClickableLabel* tab);
};
