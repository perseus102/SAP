#pragma once

#include <QWidget>
#include "ui_trustalldialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
#include "clickablelabel.h"
class TrustAllDialog : public QDialog
{
	Q_OBJECT

public:
	TrustAllDialog(QDialog *parent = Q_NULLPTR);
	~TrustAllDialog();
	void setTitleText(QString text);
	void setFiveMinsText(QString text);
	void setThirtyMinsText(QString text);
	void setNextRebootMinsText(QString text);
	void setCancelText(QString text);
	void setApplyText(QString text);
	void showDialog();
	TrustAll getDialogButtonClicked();
	TrustAllTime getTrustAllTime();

private slots:
	void cancelBtnClicked();
	void applyBtnClicked();
	void fiveMinsClicked();
	void thirtyMinsClicked();
	void nextRebootClicked();
	void changeTheme();
private:
	Ui::TrustAllDialog ui;
	void setStyle();
	void setButtonStyle();
	QLabel*			m_titleText;
	QPushButton *	m_cancelButton;
	QPushButton *	m_applyButton;
	QPushButton *	m_5minsRadioBtn;
	QPushButton *	m_30minsRadioBtn;
	QPushButton *	m_nextRebootRadioBtn;
	ClickableLabel*	m_5minsText;
	ClickableLabel*	m_30minsText;
	ClickableLabel*	m_nextRebootText;
	QLabel*			spacerRadio5MinsText;
	QLabel*			spacerRadio30MinsText;
	QLabel*			spacerRadioNextReboot;
	QVBoxLayout*	layout;
	TrustAll		m_trustAll;
	TrustAllTime	m_trustAllTime;

};
