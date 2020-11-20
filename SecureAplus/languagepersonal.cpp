#include "languagepersonal.h"

LanguagePersonal::LanguagePersonal(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_contentLayout = new QVBoxLayout();
	m_contentLayout->setContentsMargins(0, 20, 0, 0);
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
	m_lightThemeBtn = new QPushButton();
	m_lightThemeBtn->setFixedSize(20, 20);

	m_darkThemeBtn = new QPushButton();
	m_darkThemeBtn->setFixedSize(20, 20);

	m_appearLightThemeText = new QLabel();
	m_appearLightThemeText->setFont(FONT);
	m_appearLightThemeText->setFixedSize(80, 20);
	m_appearLightThemeText->setAlignment(Qt::AlignCenter);

	m_appearDarkThemeText = new QLabel();
	m_appearDarkThemeText->setFont(FONT);
	m_appearDarkThemeText->setFixedSize(80,20);
	m_appearDarkThemeText->setAlignment(Qt::AlignCenter);

	QLabel* radioBtnSpacerRight = new QLabel();
	QLabel* spacerCenter = new QLabel();
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
	connect(m_lightThemeBtn, &QPushButton::clicked, this, &LanguagePersonal::radioButtonClicked);
	connect(m_darkThemeBtn, &QPushButton::clicked, this, &LanguagePersonal::radioButtonClicked);
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &LanguagePersonal::changeTheme);
}

LanguagePersonal::~LanguagePersonal()
{
}

void LanguagePersonal::setAppearanceText(QString text)
{
	/* Mearsuring text height */
	QFontMetrics fm(FONT);
	int pixelsHigh = fm.height();
	m_appearance->setFixedHeight(pixelsHigh);
	m_appearance->setText(text);
}

void LanguagePersonal::setAppearLightThemeText(QString text)
{
	m_appearLightThemeText->setText(text);
}

void LanguagePersonal::setAppearDarkThemeText(QString text)
{
	m_appearDarkThemeText->setText(text);

}

void LanguagePersonal::changeTheme()
{
	setTextStyle();
	setAppearImage();
	setButtonStyle();
}

void LanguagePersonal::setTextStyle()
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

void LanguagePersonal::setAppearImage()
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

void LanguagePersonal::setButtonStyle()
{
	QIcon lightTheme;
	QIcon darkTheme;

	m_darkThemeBtn->setStyleSheet("QPushButton {border: 0px;}");
	m_lightThemeBtn->setStyleSheet("QPushButton {border: 0px;}");

	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		lightTheme.addFile(LIGHT_THEME_ICON_SELECTED);
		darkTheme.addFile(DARK_THEME_ICON_UNSELECTED);
		break;

	case Theme_Type::Dark_Theme:
		lightTheme.addFile(LIGHT_THEME_ICON_UNSELECTED);
		darkTheme.addFile(DARK_THEME_ICON_SELECTED);
		break;

		//MORE THEME
	default:
		break;
	}

	m_lightThemeBtn->setIcon(lightTheme);
	m_lightThemeBtn->setIconSize(QSize(20, 20));

	m_darkThemeBtn->setIcon(darkTheme);
	m_darkThemeBtn->setIconSize(QSize(20, 20));
}

void LanguagePersonal::radioButtonClicked()
{
	//switch theme
	if (sender() == m_lightThemeBtn)
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
		{
			AppSetting::getInstance()->setTheme(Theme_Type::Light_Theme);
		}

	}
	else if (sender() == m_darkThemeBtn)
	{
		if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
		{
			AppSetting::getInstance()->setTheme(Theme_Type::Dark_Theme);
		}
	}
}