#pragma once

#include <QWidget>
#include "ui_allowlist.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include "allowliststatus.h"
class AllowList : public QWidget
{
	Q_OBJECT

public:
	AllowList(QWidget *parent = Q_NULLPTR);
	~AllowList();

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

	void setStyle();
	void setLabelText();

};
