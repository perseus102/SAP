#pragma once

#include <QWidget>
#include "ui_applicationcontrol.h"
#include "clickablelabel.h"
#include "sapscrollarea.h"
#include <QStackedWidget>
#include "digitalsignature.h"
#include "allowlist.h"
class ApplicationControl : public QWidget
{
	Q_OBJECT

public:
	ApplicationControl(QWidget *parent = Q_NULLPTR);
	~ApplicationControl();
	void setTabText();

private slots:
	void TabClicked();
	void changeTheme();

private:
	Ui::ApplicationControl ui;
	QHBoxLayout*		m_contentLayout;
	QVBoxLayout*		m_tabLayout;
	QWidget*			m_tabWidget;

	ClickableLabel*		m_digitalSignature;
	ClickableLabel*		m_allowList;
	ClickableLabel*		m_restrictApp;
	ClickableLabel*		m_trustedCertificate;
	ClickableLabel*		m_scripts;
	ClickableLabel*		m_cmdRules;
	ClickableLabel*		m_allowedListCmd;

	QStackedWidget*		m_tabStackedWidget;
	SAPSCrollArea*		m_scrollView;
	QFrame*				m_tabContentWidget;

	QObject*			m_activeTab;

	DigitalSignature*	m_digitalSignatureTab;
	AllowList*			m_allowListTab;
	void setStyle();
	void setTabStyle();
	void setTabActiveStyle(ClickableLabel* tab);
	void setTabInActiveStyle(ClickableLabel* tab);
};
