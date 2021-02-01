#pragma once

#include <QWidget>
#include "ui_allowlist.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include "allowliststatus.h"
#include "sapradiobutton.h"
#include "clickablelabel.h"
class AllowList : public QWidget
{
	Q_OBJECT

public:
	AllowList(QWidget *parent = Q_NULLPTR);
	~AllowList();
private slots:
	void changeTheme();
	void radioButtonClicked();
	void textClicked();

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

	SAPRadioButton *m_slowBtn;
	SAPRadioButton *m_fastBtn;
	ClickableLabel* m_slowText;
	ClickableLabel* m_fastText;

	void setSlowText(QString text);
	void setFastText(QString text);

	void setStyle();
	void setLabelText();
	void setButtonStyle();
	

};
