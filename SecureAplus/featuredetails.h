#pragma once

#include <QWidget>
#include "ui_featuredetails.h"
#include "featurestatus.h"
#include "topbar.h"
#include <QLabel>
class FeatureDetails : public QWidget
{
	Q_OBJECT

public:
	FeatureDetails(QWidget *parent = Q_NULLPTR);
	~FeatureDetails();

public slots:
	void backBtnCliked();

signals:
	void backToHome();

private:
	Ui::FeatureDetails ui;
	QVBoxLayout		*m_layout;
	TopBar			*m_FeatureTopBar;
	FeatureStatus	*m_LicenseFeature;
	FeatureStatus	*m_RTimeFeature;
	FeatureStatus	*m_UAVServiceFeature;
	FeatureStatus	*m_WListDriverFeature;
	FeatureStatus	*m_WListServiceFeature;
	FeatureStatus	*m_SAPServiceFeature;
	FeatureStatus	*m_AntivDriverFeature;
	FeatureStatus	*m_OffAntivServiceFeature;

	void checkFeatureLicense();

};
