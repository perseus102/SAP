#pragma once

#include "stdafx.h"
#include <QWidget>
#include "ui_adddtrustedcertdialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "clickablelabel.h"
#include <QPushButton>
#include <QDialog>
#include <QFileDialog>

class ChooseFile : public QFrame
{
	Q_OBJECT

public:
	ChooseFile(QWidget *parent = Q_NULLPTR);
	~ChooseFile();
	void showDialog();
protected:
	void mousePressEvent(QMouseEvent *event);
private slots:
	void changeTheme();
signals:
	void choosedFile(QString fileName);

private:
	QIcon icon;
	QLabel* m_chooseFileLabel;
	QLabel* m_iconLabel;

	QHBoxLayout*	m_layout;

	void setStyle();
	void setIcon();
};

class AddTrustedCertDialog : public QDialog
{
	Q_OBJECT

public:
	AddTrustedCertDialog(QDialog *parent = Q_NULLPTR);
	~AddTrustedCertDialog();
	void showDialog();

private slots:
	void cancelClicked();
	void addClicked();
	void changeTheme();
	void getFileName(QString fileName);

signals:
	void addTrustedCert(QString&, QString&, FILETIME, FILETIME);

private:
	Ui::AdddTrustedCertDialog ui;

	QLabel*			m_titleText;

	QVBoxLayout*	m_layout;

	ChooseFile*		m_chooseFileBtn;
	QLabel*			m_filePathText;
	QLabel*			m_centerLine;

	QLabel*			m_commonNameTitle;
	QLabel*			m_commonName;
	
	QLabel*			m_validFromTitle;
	QLabel*			m_validFrom;

	QLabel*			m_validToTitle;
	QLabel*			m_validTo;

	QLabel*			m_thumbprintTitle;
	QLabel*			m_thumbprint;

	QLabel*			topSpacer;

	QPushButton*	m_cancelBtn;
	QPushButton*	m_addFileBtn;

	QWidget*		m_certificateInforWg;

	QString			m_curFileName;
	QString			m_thumbprintText;

	FILETIME		m_ftValidFrom;
	FILETIME		m_ftValidTo;

	void setStyle();
	void setText();
	void setAddBtnStyle();
	void setThumprintText(QString text);
	void setFilePathText(QString text);
};
