#pragma once

#include <QWidget>
#include "ui_trustedcertificate.h"
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include "search.h"
#include "certificatetable.h"
#include "sapscrollarea.h"
#include "addresappdialog.h"
#include "widgettransparent.h"
#include "clickablelabel.h"
#include "addtrustedcertdialog.h"

class TrustedCertificate : public QWidget
{
	Q_OBJECT

public:
	TrustedCertificate(QWidget *parent = Q_NULLPTR);
	~TrustedCertificate();

private slots:
	void removeButtonClicked();
	void addButtonClicked();
	void resetToDefaultClicked();

public slots:
	void setRemoveBtnDisabled(bool disabled);
	void changeTheme();

private:
	Ui::TrustedCertificate ui;

	QVBoxLayout*	m_layout;
	QPushButton*	m_removeBtn;
	QPushButton*	m_addBtn;

	ClickableLabel*		m_resetToDefaultBtn;

	CertificateTable*	m_certificateTable;

	AddTrustedCertDialog*	m_addTrustedCertDialog;

	WidgetTransparent*	transparent;

	void setStyle();
	void setRemoveBtnStyle();
};
