#pragma once

#include <QWidget>
#include "ui_certificatetable.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "sapcheckbox.h"
#include "sapscrollarea.h"

struct CertificateRow
{
	QWidget* rowWg;
	SAPCheckBox* checkBox;
	QLabel*	CertificateName;
	QLabel*	validFrom;
	QLabel*	validTo;
	QLabel*	thumprint;
	QLabel* line;
};

class CertificateTable : public QWidget
{
	Q_OBJECT

public:
	CertificateTable(QWidget *parent = Q_NULLPTR);
	~CertificateTable();

private slots:
	void changeTheme();
	void allCheckBoxSetCheck(Qt::CheckState);
	void scrollBarRangeChanged(int min, int max);
	void rowCheckBoxSetCheck(Qt::CheckState);

public slots:
	void AddCertificate(CertificateRowString rowString);
	void AddCertificateFromDialog(CertificateRowString rowString);
	void removeRows();
	void resetToDefault();

signals:
	void setRemoveBtnDisabled(bool disabled);

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	Ui::CertificateTable ui;
	QWidget*		m_titleWg;
	SAPCheckBox*	m_checkAllBox;
	QLabel*			m_certificateName;
	QLabel*			m_validFrom;
	QLabel*			m_validTo;
	QVBoxLayout*	m_layout;
	SAPSCrollArea*	m_scrollView;
	QWidget*		m_rowWg;
	QVBoxLayout*	m_rowLayout;

	//QMap<QString, CertificateRow*> m_CertificateRowMap;
	QList<CertificateRowString> m_defaultList;
	QList<CertificateRow*> m_CertificateRowMap;

	int m_rowCount;
	bool m_isFilter = false;
	int m_rowChecked = 0;
	int m_filterCount;

	void setStyle();
	void setRowStyle(CertificateRow* row);

	Button_Check_State buttonCheckState();

	void setCheckBoxsState();

	void resizeLabel();
};
