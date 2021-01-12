#pragma once

#include <QWidget>
#include "ui_adddtrustedcertdialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
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
	void addTrustedCert(CertificateRowString);

private:
	Ui::AdddTrustedCertDialog ui;

	QLabel*			m_titleText;

	QVBoxLayout*	m_layout;

	ChooseFile*		m_chooseFileBtn;
	QLabel*			m_filePathText;
	QLabel*			m_centerLine;

	QLabel*			m_commonNameLabel;
	QWidget*		m_commonNameWg;
	
	QLabel*			m_validFromLabel;
	QWidget*		m_validFromWg;

	QLabel*			m_validToLabel;
	QWidget*		m_validToWg;

	QLabel*			m_thumbprintLabel;
	QWidget*		m_thumbprintWg;

	QPushButton*	m_cancelBtn;
	QPushButton*	m_addFileBtn;

	QString m_curFileName;

	void setStyle();
	void setText();
};
