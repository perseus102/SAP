#pragma once

#include <QWidget>
#include "ui_allowlist.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include "allowliststatus.h"
#include "SafeParamThreadExportWhitelist.h"

#include "sapradiobutton.h"
#include "clickablelabel.h"
#include "compactdialog.h"
#include "widgettransparent.h"
class AllowList : public QWidget
{
	Q_OBJECT

public:
	AllowList(QWidget *parent = Q_NULLPTR);
	~AllowList();
private slots:
	void changeTheme();
	void onRefresh();
	void radioButtonClicked();
	void textClicked();
	void compactBtnClicked();

public slots:
	void runCompactAllowList();

private:
	Ui::AllowList ui;

	QVBoxLayout* m_layout;

	QLabel* m_status;
	QLabel* m_imExport;
	QLabel* m_imExportDesc;
	QLabel* m_compactAllowList;
	QLabel* m_compactAllowListDesc;
	QLabel* m_statusLine;
	QLabel* m_imExportLine;

	QPushButton* m_exportAllistBtn;
	QPushButton* m_importAllistBtn;
	QPushButton* m_compactAllistBtn;

	AllowListStatus* m_allistCreation;
	AllowListStatus* m_allistService;
	AllowListStatus* m_allistDriver;

	QTimer* m_timerRefresh;
	HANDLE hProcessImportWhitelist;
	HANDLE hThreadExportWhitelist;
	SafeParamThreadExportWhitelist* paramThreadExportWhitelist;
	SAPRadioButton *m_slowBtn;
	SAPRadioButton *m_fastBtn;
	ClickableLabel* m_slowText;
	ClickableLabel* m_fastText;

	void setSlowText(QString text);
	void setFastText(QString text);

	void setStyle();
	void setLabelText();

	void refreshInitialWhitelistStatus();
	void refreshAllowlistServiceAndDriverStatus();
	void refreshServiceStatus(const wchar_t* service_name);

	void freeParamThreadExportWhitelist();
	void onImportWhitelist();
	void onExportWhitelist();

	
	WidgetTransparent*	transparent;
	CompactDialog* m_compactDialog;
};
