#pragma once

#include <QWidget>
#include "ui_allowliststatus.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
class AllowListStatus : public QWidget
{
	Q_OBJECT

public:
	AllowListStatus(AllowList_Type allistType, AllowList_States allistState, QWidget *parent = Q_NULLPTR);
	~AllowListStatus();
	void setAllowListName(QString name);
	void setStatusText(QString text);
	void setAllowState(AllowList_States allistState);
	AllowList_States getAllowState();
	void setViewBtnText(QString text);
signals:
	void viewBtnClicked();

private slots:
	void changeTheme();
	void viewBtnClick();

private:
	Ui::AllowListStatus ui;
	QLabel *m_allowListNameLabel;
	QLabel *m_statusIcon;
	QLabel *m_statusTextLabel;
	QPushButton *m_viewButton;
	QHBoxLayout *m_layout;
	QWidget *m_allowListWidget;
	QVBoxLayout *m_allowListLayout;
	AllowList_Type m_allowListType;
	AllowList_States m_allowListState;
	void setStyle();
	void setViewBtnStyle();
};
