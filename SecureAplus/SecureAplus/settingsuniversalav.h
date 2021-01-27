#pragma once

#include <QWidget>
#include "ui_universalav.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "switch.h"
#include "clickablelabel.h"
#include "sapcombobox.h"
#include "sapslider.h"

class SettingsUniversalAV : public QWidget
{
	Q_OBJECT

public:
	SettingsUniversalAV(QWidget *parent = Q_NULLPTR);
	~SettingsUniversalAV();

public slots:
	void offRealTimeScan();

private slots:
	void capacityClicked();
	void sliderChangeValue(int value);
	void comboboxChangeIndex(int index);
	void changeTheme();
	void toggleClicked();

private:
	Ui::UniversalAV ui;

	QVBoxLayout* m_layout;

	QLabel*		m_autoUpload;
	QLabel*		m_autoUploadDesc;
	QLabel*		m_selectFileTyle;
	QLabel*		m_GoodNew;
	QLabel*		m_GoodNewDesr;
	QLabel*		m_fullScan;
	QLabel*		m_fullScanDesc;
	QLabel*		m_autoFullScan;
	QLabel*		m_demandScanning;
	QLabel*		m_demandScanningDesc;
	QLabel*		m_realTimeScanning;
	QLabel*		m_realTimeScanningDesc;
	QLabel*		m_dailyUpload;

	ClickableLabel*		m_dailyUpload10MB;
	ClickableLabel*		m_dailyUpload100MB;
	ClickableLabel*		m_dailyUpload1GB;
	ClickableLabel*		m_dailyUploadUnlimited;

	QLabel*				spacer10MB;
	QLabel*				spacer100MB;
	QLabel*				spacer1GB;

	SAPCombobox*		m_fileTypeCbb;

	Switch*		m_autoUploadToggle;
	Switch*		m_goodNewToggle;
	Switch*		m_fullScanToggle;
	Switch*		m_autoFullScanToggle;
	Switch*		m_onDemandToggle;
	Switch*		m_realTimeToggle;
	SAPSlider*	m_slider;
	
	QLabel*		m_autoUploadLine;
	QLabel*		m_goodNewLine;
	QLabel*		m_fullSystemLine;
	QLabel*		m_demandScanningLine;
	QLabel*		m_realTimeScanningLine;

	void setStyle();
	void setLabelText();
	void setDailyUpload10MBText(QString text);
	void setDailyUpload100MBText(QString text);
	void setDailyUpload1GBText(QString text);
	void setDailyUploadUnlimitedText(QString text);
};
