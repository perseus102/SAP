#pragma once

#include <QWidget>
#include "ui_languagepersonal.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "define.h"
#include "appsetting.h"
#include "clickablelabel.h"
class LanguagePersonal : public QWidget
{
	Q_OBJECT

public:
	LanguagePersonal(QWidget *parent = Q_NULLPTR);
	~LanguagePersonal();
	void setAppearanceText(QString text);
	void setAppearLightThemeText(QString text);
	void setAppearDarkThemeText(QString text);

public slots:
	void radioButtonClicked();
	void themeTextClicked();
	void changeTheme();
private:
	Ui::LanguagePersonal ui;
	QVBoxLayout* m_contentLayout;
	QLabel* m_appearance;
	QLabel* m_appearLightTheme;
	QLabel* m_appearDarkTheme;
	QPushButton *m_lightThemeBtn;
	QPushButton *m_darkThemeBtn;
	ClickableLabel* m_appearLightThemeText;
	ClickableLabel* m_appearDarkThemeText;
	QLabel* spacerCenter;

	void setTextStyle();
	void setAppearImage();
	void setButtonStyle();

};
