#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QMetaObject>
#include "define.h"
#include "ui_topbar.h"
#include "appsetting.h"
#include "util.h"
#include "clickablelabel.h"
namespace Ui {
	class TopBar;
}
class BackButton : public QPushButton
{
    Q_OBJECT
public:
	BackButton(QWidget* parent = Q_NULLPTR);
	~BackButton();

public slots:
	void changeTheme();

protected:
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;

private:
	void initIcon();
	QIcon icon;
};

class TopBar : public QWidget
{
	Q_OBJECT

public:
	TopBar(QWidget *parent = Q_NULLPTR);
	~TopBar();
	void setDirectoryText(QString text);
	void setVisibleNaviButton(bool visible);
	QPushButton* getButton();
	void addDir(QString dirText, Directory dir);
	ClickableLabel* getLastLabel();

public slots:
	void changeTheme();
	void labelClicked();
	void backButtonClicked();

signals:
	void labelDirClicked(Directory);

private:
	Ui::TopBar *ui;
	BackButton		*m_navigationBtn;
	QLabel			*m_Directory;
	QHBoxLayout		*m_topBarLayout;
	QList<ClickableLabel*> m_labelList;
	QMap<ClickableLabel*,Directory> m_DirectoryMap;
	QList<QLabel*> m_backSlashList;
	QLabel * lastItem;
	void setTextStyle();
};
