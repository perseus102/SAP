#pragma once

#include <QObject>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "ui_featurestatus.h"

class FeatureStatus : public QWidget
{
	Q_OBJECT

public:
	FeatureStatus(Feature featureName, Feature_States state, QWidget* parent = Q_NULLPTR);
	~FeatureStatus();
	void setFeatureName(QString name);
	void setStatusText(QString text);
	void setFeatureState(Feature_States featureState);
	Feature_States getFeatureState();
	void setFeatureName(Feature featureName);
	Feature getFeatureName();

public slots:
	void changeTheme();
	void settingBtnClicked();

signals:
	void settingFeature();
private:
	Ui::FeatureStatus ui;
	QLabel *m_featureNameLabel;
	QLabel *m_statusIcon;
	QLabel *m_statusTextLabel;
	QPushButton *m_settingButton;
	QHBoxLayout *m_layout;
	Feature m_featureName;
	Feature_States m_featureState;
	QWidget *m_featureWidget;
	QVBoxLayout *m_featureLayout;

	void setStyle();
	void setLicenseStyle();
	void setRTimeScanStyle();
	void setUAVServiceStyle();
	void setWListDriverStyle();
	void setWListServiceStyle();
	void setSAPServiceStyle();
	void setAntivDrivereStyle();
	void setOffAntivServiceStyle();
	void setSettingBtnStyle();

};
