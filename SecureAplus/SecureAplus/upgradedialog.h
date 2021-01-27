#pragma once

#include <QWidget>
#include "ui_upgradedialog.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QPushButton>
#include <QDialog>
class UpgradeDialog : public QDialog
{
	Q_OBJECT

public:
	UpgradeDialog(QDialog *parent = Q_NULLPTR);
	~UpgradeDialog();
	void showDialog();
	void setTitleText(QString text);
	void setUpgradeBtnText(QString text);
	Observation getObservation();

private slots:
	void changeTheme();
	void exitButtonClicked();
	void upgradeButtonClicked();

private:
	Ui::UpgradeDialog ui;
	
	void setStyle();
	void setButtonIcon();
	QPushButton* m_exitButton;
	QLabel* m_iconLabel;
	QLabel* m_titleText;
	QPushButton* m_upgradeButton;
	QVBoxLayout* m_layout;

	Observation m_observation;
};
