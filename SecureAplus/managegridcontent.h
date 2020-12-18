#pragma once

#include <QWidget>
#include "ui_managegridcontent.h"
#include "flowlayout.h"
#include "gridwidget.h"
class ManageGridContent : public QWidget
{
	Q_OBJECT

public:
	ManageGridContent(QWidget *parent = Q_NULLPTR);
	~ManageGridContent();
signals:
	void gridWidgetPressed(QString gridName);
public slots:
	void widgetPressed();
private:
	Ui::ManageGridContent ui;

	FlowLayout* m_flowLayout;
	GridWidget* m_trustedGroups;
	GridWidget* m_trustedUsers;
	GridWidget* m_excInc;
	GridWidget* m_appControl;
	GridWidget* m_removableDevices;
	GridWidget* m_accountAndLicense;

	void setConnection();
};
