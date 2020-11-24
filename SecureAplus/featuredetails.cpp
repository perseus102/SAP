#include "featuredetails.h"

FeatureDetails::FeatureDetails(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setContentsMargins(0, 0, 0, 0);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(4);
	setLayout(m_layout);

	m_licenseFeature = new FeatureStatus(Feature::Lisence, Feature_States::Active);
	m_licenseFeature->setFeatureName("License");
	m_licenseFeature->setStatusText("Active");
	QLabel *spacerBottom = new QLabel();

	m_layout->addWidget(m_licenseFeature);
	m_layout->addWidget(spacerBottom);
}

FeatureDetails::~FeatureDetails()
{
}

void FeatureDetails::setStyle()
{
}
