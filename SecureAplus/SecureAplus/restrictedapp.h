#pragma once

#include <QWidget>
#include "ui_rectrictedapp.h"
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include "search.h"
#include "filenametable.h"
#include "sapscrollarea.h"
#include "addresappdialog.h"
#include "widgettransparent.h"
#include "clickablelabel.h"
#include "resetbutton.h"

class RestrictedApp : public QWidget
{
	Q_OBJECT

public:
	RestrictedApp(QWidget *parent = Q_NULLPTR);
	~RestrictedApp();
	void setDescText(QString text);

private slots:
	void removeButtonClicked();
	void addButtonClicked();
	void resetToDefaultClicked();
public slots:
	void setRemoveBtnDisabled(bool disabled);
	void changeTheme();

protected:
	void resizeEvent(QResizeEvent *event) override;
private:
	Ui::RectrictedApp ui;

	QLabel*			m_description;
	Search *		m_searchWg;
	QVBoxLayout*	m_layout;
	QPushButton*	m_removeBtn;
	QPushButton*	m_addBtn;

	ResetButton*		m_resetBtn;

	FileNameTable*		m_fileNameTable;
	AddResAppDialog*	m_addResAppDialog;
	WidgetTransparent*	transparent;

	void setStyle();
	void setRemoveBtnStyle();

};
