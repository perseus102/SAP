#pragma once

#include <QWidget>
#include "ui_selectwidget.h"
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"

class SelectWidget : public QWidget
{
	Q_OBJECT

public:
	SelectWidget(Protection_Modes mode, bool selected = false, QWidget* parent = Q_NULLPTR);
	~SelectWidget();
	void setSelected(bool selected);
	void setLockDownText(QString text);
signals:
	void changeMode();
public slots:
	void changeTheme();

protected:
	bool event(QEvent* e) override;
	void mousePressEvent(QMouseEvent* event);

private:
	Ui::SelectWidget ui;
	QFrame*			m_frame;
	QVBoxLayout*	m_layout;
	QVBoxLayout*	m_ProVersionLayout;
	QHBoxLayout*	m_contentLayout;
	QLabel*			m_iconLabel;
	QLabel*			m_title;
	QLabel*			m_description;
	QLabel*			m_proIconLabel;
	QWidget*		observationProver;
	QWidget*		lockDownMode;
	QLabel*			m_lockdownModeLabel;
	QVBoxLayout*	observationLayout;
	QVBoxLayout*	lockdownLayout;
	QIcon			icon;
	QIcon			m_proIcon;

	Protection_Modes	m_mode;
	bool				m_selected;
	void setIcon();
	void setStyle();
	void setModeText();

};
