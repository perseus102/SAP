#include "settingslanguagepersonal.h"

SettingsLanguagePersonal::SettingsLanguagePersonal(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_contentLayout = new QVBoxLayout();
	m_contentLayout->setContentsMargins(30, 20, 30, 0);
	m_contentLayout->setSpacing(0);

	m_appearance = new QLabel();
	m_appearance->setFont(FONT);
	m_appearance->setAlignment(Qt::AlignLeft);

	m_appearLightTheme	= new QLabel();
	m_appearLightTheme->setFixedSize(107, 80);
	m_appearLightTheme->setAlignment(Qt::AlignLeft);

	m_appearDarkTheme	= new QLabel();
	m_appearDarkTheme->setFixedSize(107, 80);

	m_appearDarkTheme->setAlignment(Qt::AlignLeft);

	QLabel* spacerRight = new QLabel();

	/*Init Apperance Image */
	QWidget* appear_Img_Widget = new QWidget();
	appear_Img_Widget->setFixedHeight(80);
	QHBoxLayout* appear_Img_Layout = new QHBoxLayout();
	appear_Img_Layout->setContentsMargins(0, 0, 0, 0);
	appear_Img_Layout->setSpacing(25);
	appear_Img_Layout->addWidget(m_appearLightTheme);
	appear_Img_Layout->addWidget(m_appearDarkTheme);
	appear_Img_Layout->addWidget(spacerRight);
	appear_Img_Widget->setLayout(appear_Img_Layout);

	/*Init Apperance button */
	m_lightThemeBtn = new SAPRadioButton();
	m_lightThemeBtn->setFixedSize(20, 20);

	m_darkThemeBtn = new SAPRadioButton();
	m_darkThemeBtn->setFixedSize(20, 20);

	m_appearLightThemeText = new ClickableLabel();
	m_appearLightThemeText->setFont(FONT);
	m_appearLightThemeText->setFixedSize(80, 20);
	m_appearLightThemeText->setAlignment(Qt::AlignCenter);

	m_appearDarkThemeText = new ClickableLabel();
	m_appearDarkThemeText->setFont(FONT);
	m_appearDarkThemeText->setFixedSize(80,20);
	m_appearDarkThemeText->setAlignment(Qt::AlignCenter);

	QLabel* radioBtnSpacerRight = new QLabel();
	spacerCenter = new QLabel();
	spacerCenter->setFixedWidth(10);

	QWidget* appear_button_Widget = new QWidget();
	appear_button_Widget->setFixedHeight(20);
	QHBoxLayout* appear_button_Layout = new QHBoxLayout();
	appear_button_Layout->setContentsMargins(0, 0, 0, 0);
	appear_button_Layout->setSpacing(7);
	appear_button_Layout->addWidget(m_lightThemeBtn);
	appear_button_Layout->addWidget(m_appearLightThemeText);
	appear_button_Layout->addWidget(spacerCenter);
	appear_button_Layout->addWidget(m_darkThemeBtn);
	appear_button_Layout->addWidget(m_appearDarkThemeText);
	appear_button_Layout->addWidget(radioBtnSpacerRight);
	appear_button_Widget->setLayout(appear_button_Layout);


	QLabel *spacerTitleAndImg = new QLabel();
	spacerTitleAndImg->setFixedHeight(20);
	QLabel* spacerImgAndButton = new QLabel();
	spacerImgAndButton->setFixedHeight(15);
	QLabel *spacerBottom = new QLabel();

	m_contentLayout->addWidget(m_appearance);

	/* Add spacer between Title and image  */
	m_contentLayout->addWidget(spacerTitleAndImg);

	/* Add appearance Image */
	m_contentLayout->addWidget(appear_Img_Widget);

	/* Add spacer between image and button */
	m_contentLayout->addWidget(spacerImgAndButton);

	/* Add appearance radio button */
	m_contentLayout->addWidget(appear_button_Widget);

	/* Add spacer bottom */
	m_contentLayout->addWidget(spacerBottom);

	setLayout(m_contentLayout);
	setTextStyle();
	setAppearImage();
	setButtonStyle();
	/* Test */
	setAppearanceText("Appearance");
	setAppearLightThemeText("Light theme");
	setAppearDarkThemeText("Dark theme");

	/* Connection */
	connect(m_lightThemeBtn, &SAPRadioButton::clicked, this, &SettingsLanguagePersonal::radioButtonClicked);
	connect(m_darkThemeBtn, &SAPRadioButton::clicked, this, &SettingsLanguagePersonal::radioButtonClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SettingsLanguagePersonal::changeTheme);
	connect(m_appearLightThemeText, &ClickableLabel::clicked, this, &SettingsLanguagePersonal::themeTextClicked);
	connect(m_appearDarkThemeText, &ClickableLabel::clicked, this, &SettingsLanguagePersonal::themeTextClicked);
}

SettingsLanguagePersonal::~SettingsLanguagePersonal()
{
}

void SettingsLanguagePersonal::setAppearanceText(QString text)
{
	/* Mearsuring text height */
	QFontMetrics fm(FONT);
	int pixelsHigh = fm.height();
	m_appearance->setFixedHeight(pixelsHigh);
	m_appearance->setText(text);
}

void SettingsLanguagePersonal::setAppearLightThemeText(QString text)
{
	QFontMetrics fm(FONT);
	int pixelsHigh = fm.height();
	int width = fm.width(text);
	m_appearLightThemeText->setFixedWidth(width);
	m_appearLightThemeText->setFixedHeight(pixelsHigh);
	m_appearLightThemeText->setText(text);

	spacerCenter->setFixedWidth(80 - width + 10);
}

void SettingsLanguagePersonal::setAppearDarkThemeText(QString text)
{
	QFontMetrics fm(FONT);
	int pixelsHigh = fm.height();
	int width = fm.width(text);
	m_appearDarkThemeText->setFixedWidth(width);
	m_appearDarkThemeText->setFixedHeight(pixelsHigh);
	m_appearDarkThemeText->setText(text);

}

void SettingsLanguagePersonal::changeTheme()
{
	setTextStyle();
	setAppearImage();
	//setButtonStyle();
}

void SettingsLanguagePersonal::setTextStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_appearance->setStyleSheet("QLabel { color:" + LANG_PERS_TEXT_COLOR_LIGHT_THEME + ";}");
		m_appearLightThemeText->setStyleSheet("QLabel { color:" + LANG_PERS_TEXT_COLOR_LIGHT_THEME + ";}");
		m_appearDarkThemeText->setStyleSheet("QLabel { color:" + LANG_PERS_TEXT_COLOR_LIGHT_THEME + ";}");
		break;

	case Theme_Type::Dark_Theme:
		m_appearance->setStyleSheet("QLabel { color:" + LANG_PERS_TEXT_COLOR_DARK_THEME + ";}");
		m_appearLightThemeText->setStyleSheet("QLabel { color:" + LANG_PERS_TEXT_COLOR_DARK_THEME + ";}");
		m_appearDarkThemeText->setStyleSheet("QLabel { color:" + LANG_PERS_TEXT_COLOR_DARK_THEME + ";}");

		break;

		//MORE THEME
	default:
		break;
	}
}

void SettingsLanguagePersonal::setAppearImage()
{
	QPixmap appearDarkImg;
	QPixmap appearLightImg;
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		appearDarkImg.load(APPEAR_DARK_THEME_LIGHT_MODE);
		appearLightImg.load(APPEAR_LIGHT_THEME_LIGHT_MODE);
		break;

	case Theme_Type::Dark_Theme:
		appearDarkImg.load(APPEAR_DARK_THEME_DARK_MODE);
		appearLightImg.load(APPEAR_LIGHT_THEME_DARK_MODE);
		break;

		//MORE THEME
	default:
		break;
	}
	m_appearLightTheme->setPixmap(appearLightImg);
	m_appearDarkTheme->setPixmap(appearDarkImg);
}

void SettingsLanguagePersonal::setButtonStyle()
{

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_lightThemeBtn->setButtonChecked(Qt::Checked);
		m_darkThemeBtn->setButtonChecked(Qt::Unchecked);
		break;

	case Theme_Type::Dark_Theme:
		m_lightThemeBtn->setButtonChecked(Qt::Unchecked);
		m_darkThemeBtn->setButtonChecked(Qt::Checked);
		break;

		//MORE THEME
	default:
		break;
	}

}

void SettingsLanguagePersonal::radioButtonClicked()
{
	//switch theme
	if (sender() == m_lightThemeBtn)
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			AppSetting::getInstance()->setTheme(Theme_Type::Light_Theme);
		}
		m_lightThemeBtn->setButtonChecked(Qt::Checked);
		m_darkThemeBtn->setButtonChecked(Qt::Unchecked);

	}
	else if (sender() == m_darkThemeBtn)
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			AppSetting::getInstance()->setTheme(Theme_Type::Dark_Theme);
		}
		m_lightThemeBtn->setButtonChecked(Qt::Unchecked);
		m_darkThemeBtn->setButtonChecked(Qt::Checked);
	}
}


void SettingsLanguagePersonal::themeTextClicked()
{
	if (sender() == m_appearLightThemeText)
	{
		m_lightThemeBtn->setButtonChecked(Qt::Checked);
		m_darkThemeBtn->setButtonChecked(Qt::Unchecked);
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			AppSetting::getInstance()->setTheme(Theme_Type::Light_Theme);
		}

	}
	else if (sender() == m_appearDarkThemeText)
	{
		m_lightThemeBtn->setButtonChecked(Qt::Unchecked);
		m_darkThemeBtn->setButtonChecked(Qt::Checked);
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			AppSetting::getInstance()->setTheme(Theme_Type::Dark_Theme);
		}
	}
}