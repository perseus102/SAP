#pragma once

#include <QWidget>
#include "ui_rectrictedapp.h"
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include "search.h"
class RestrictedApp : public QWidget
{
	Q_OBJECT

public:
	RestrictedApp(QWidget *parent = Q_NULLPTR);
	~RestrictedApp();
	void setDescText(QString text);

private:
	Ui::RectrictedApp ui;

	QLabel* m_description;
	Search *m_searchWg;
	QVBoxLayout* m_layout;

	void setStyle();
};
