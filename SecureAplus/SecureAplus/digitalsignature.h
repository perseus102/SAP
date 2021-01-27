#pragma once

#include <QWidget>
#include "ui_digitalsignature.h"
#include "define.h"
#include "appsetting.h"
#include "switch.h"
#include "sapradiobutton.h"
class DigitalSignature : public QWidget
{
	Q_OBJECT

public:
	DigitalSignature(QWidget *parent = Q_NULLPTR);
	~DigitalSignature();
private slots:
	void trustBasedToggleClicked();
	void changeTheme();
	void radioButtonClicked();
private:
	Ui::DigitalSignature ui;
	QVBoxLayout* m_layout;
	QLabel* m_trustBased;
	QLabel* m_allowAppTitle;
	QLabel* m_nameInTrusted;
	QLabel* m_nameInTrustedDesc;
	QLabel* m_trustedByOS;
	QLabel* m_trustedByOSDesc;
	QLabel* m_nameAndThumbprint;
	QLabel* m_nameAndThumbprintDesc;
	
	Switch* m_trustBasedToggle;

	SAPRadioButton* m_nameInTrustedBtn;
	SAPRadioButton* m_trustedByOSBtn;
	SAPRadioButton* m_nameAndThumbprintBtn;

	QWidget* nameInTrustedWg;
	QWidget* trustedByOSWg;
	QWidget* nameAndThumbprintWg;

	QWidget* nameInTrustedDescWg;
	QWidget* trustedByOSDescWg;
	QWidget* nameAndThumbprintDescWg;

	void setLabelText();
	void setStyle();
	void setAllowAppListVisible(bool isVisible);
};
