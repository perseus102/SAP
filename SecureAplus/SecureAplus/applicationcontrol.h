#pragma once

#include <QWidget>
#include "ui_applicationcontrol.h"
#include "clickablelabel.h"
#include "sapscrollarea.h"
#include <QStackedWidget>
#include "managedigitalsignature.h"
#include "allowlist.h"
#include "restrictedapp.h"
#include "trustedcertificate.h"
#include "scripts.h"
#include "commandline.h"
#include "commandlinerule.h"
#include "processprotector.h"

class ApplicationControl : public QWidget
{
	Q_OBJECT

public:
	ApplicationControl(QWidget *parent = Q_NULLPTR);
	~ApplicationControl();
	void setTabText();
	void loadData();

private slots:
	void TabClicked();
	void changeTheme();
protected:
	void resizeEvent(QResizeEvent *event) override;
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
	ClickableLabel*		m_processProtector;

	QStackedWidget*		m_tabStackedWidget;
	SAPSCrollArea*		m_scrollView;
	QFrame*				m_tabContentWidget;

	QObject*			m_activeTab;

	ManageDigitalSignature*		m_digitalSignatureTab;
	AllowList*				m_allowListTab;
	RestrictedApp*			m_restrictedAppTab;
	TrustedCertificate*		m_trustedCertificateTab;
	Scripts*				m_scriptsTab;
	CommandLine*			m_commandLineTab;
	ProcessProtector*		m_processProtectorTab;
	CommandLineRule*		m_commandLineRuleTab;

	void setStyle();
	void setTabStyle();
	void setTabActiveStyle(ClickableLabel* tab);
	void setTabInActiveStyle(ClickableLabel* tab);
	void resizeTab();
};
