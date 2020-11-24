#pragma once

#include <QWidget>
#include "ui_featuredetails.h"
#include "featurestatus.h"
#include <QLabel>
class FeatureDetails : public QWidget
{
	Q_OBJECT

public:
	FeatureDetails(QWidget *parent = Q_NULLPTR);
	~FeatureDetails();

private:
	Ui::FeatureDetails ui;
	QVBoxLayout *m_layout;

	FeatureStatus *m_licenseFeature;
	void setStyle();
};
