#pragma once

#include <QWidget>
#include "ui_settinggridcontent.h"
#include "flowlayout.h"
#include "gridwidget.h"

class SettingGridContent : public QWidget
{
	Q_OBJECT

public:
	SettingGridContent(QWidget *parent = Q_NULLPTR);
	~SettingGridContent();
signals:
	void gridWidgetPressed(QString gridName);

public slots:
	void widgetPressed();
private:
	Ui::SettingGridContent ui;
	FlowLayout* m_flowLayout;
	GridWidget* m_scanning;
	GridWidget* m_allowList;
	GridWidget* m_vulnerability;
	GridWidget* m_protectionMode;
	GridWidget* m_info;
	GridWidget* m_languagePersonal;
	GridWidget* m_manageUser;
	GridWidget* m_updates;
	GridWidget* m_others;

	void setConnection();

};
