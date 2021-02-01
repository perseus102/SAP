#include "scripts.h"

Scripts::Scripts(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(30, 0, 40, 10);
	m_layout->setSpacing(0);

	m_scriptsDesc = new QLabel();
	m_scriptsDesc->setFont(FONT);
	m_scriptsDesc->setFixedHeight(45);
	m_scriptsDesc->setWordWrap(true);
	m_scriptsDesc->setText("Executing a script requires both the script interpreter (which executes the script) and the script file itself to be trusted. The script interpreter will refuse to open any non-trusted file.");

	QLabel* descSpacer = new QLabel();
	descSpacer->setFixedHeight(15);

	m_scriptsTable = new ScriptsTable();

	QLabel* bottomTableSpacer = new QLabel();
	bottomTableSpacer->setFixedHeight(10);

	QWidget* bottomBtns = new QWidget();
	bottomBtns->setFixedHeight(30);
	QHBoxLayout* btnsLayout = new QHBoxLayout();
	btnsLayout->setContentsMargins(0, 0, 0, 0);
	btnsLayout->setSpacing(0);
	bottomBtns->setLayout(btnsLayout);

	m_resetToDefaultBtn = new ClickableLabel();
	m_resetToDefaultBtn->setFixedSize(100, 30);
	m_resetToDefaultBtn->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_resetToDefaultBtn->setFont(FONT);
	m_resetToDefaultBtn->setText("Reset to Defaults");

	QLabel* centerBtnsSpacer = new QLabel();

	m_removeBtn = new QPushButton();
	m_removeBtn->setFixedSize(80, 30);
	m_removeBtn->setFont(FONT);
	m_removeBtn->setText("Remove");
	m_removeBtn->setDisabled(true);

	QLabel* btnsSpacer = new QLabel();
	btnsSpacer->setFixedWidth(8);

	m_addBtn = new QPushButton();
	m_addBtn->setFixedSize(80, 30);
	m_addBtn->setFont(FONT);
	m_addBtn->setText("Add");

	btnsLayout->addWidget(m_resetToDefaultBtn);
	btnsLayout->addWidget(centerBtnsSpacer);
	btnsLayout->addWidget(m_removeBtn);
	btnsLayout->addWidget(btnsSpacer);
	btnsLayout->addWidget(m_addBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_scriptsDesc);
	m_layout->addWidget(descSpacer);
	m_layout->addWidget(m_scriptsTable);
	m_layout->addWidget(bottomTableSpacer);
	m_layout->addWidget(bottomBtns);
	m_layout->addWidget(bottomSpacer);

	transparent = new WidgetTransparent();
	m_addScriptDialog = new AddScriptDialog();

	setLayout(m_layout);
	setStyle();

	connect(m_removeBtn, &QPushButton::clicked, m_scriptsTable, &ScriptsTable::removeRows);
	connect(m_removeBtn, &QPushButton::clicked, this, &Scripts::removeButtonClicked);

	connect(m_addBtn, &QPushButton::clicked, this, &Scripts::addButtonClicked);

	connect(m_resetToDefaultBtn, &ClickableLabel::clicked, this, &Scripts::resetToDefaultClicked);
	connect(m_resetToDefaultBtn, &ClickableLabel::clicked, m_scriptsTable, &ScriptsTable::resetToDefault);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &Scripts::changeTheme);

	connect(m_scriptsTable, &ScriptsTable::setRemoveBtnDisabled, this, &Scripts::setRemoveBtnDisabled);
	connect(m_addScriptDialog, &AddScriptDialog::addScript, m_scriptsTable, &ScriptsTable::AddScriptsFromDialog);

}

Scripts::~Scripts()
{
}

void Scripts::removeButtonClicked()
{
}

void Scripts::addButtonClicked()
{
	QRect geometry = AppSetting::getInstance()->getAppGeometry();

	transparent->showWidget();
	m_addScriptDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 190 /*190 is half width*/, geometry.y() + 16, 380, 290);
	m_addScriptDialog->showDialog();
	transparent->hide();
}

void Scripts::resetToDefaultClicked()
{
}

void Scripts::changeTheme()
{
	setStyle();
}

void Scripts::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		setRemoveBtnStyle();

		m_resetToDefaultBtn->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		
		m_scriptsDesc->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:

		m_resetToDefaultBtn->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_scriptsDesc->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_DT + ";}");

		setRemoveBtnStyle();

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		break;

		//MORE THEME
	default:
		break;
	}
}

void Scripts::setRemoveBtnStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		if (m_removeBtn->isEnabled())
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		}
		else
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_LT + ";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_LT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

	case Theme_Type::Dark_Theme:

		if (m_removeBtn->isEnabled())
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:none;"
				"color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
				"border-radius:2px;"
				"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");
		}
		else
		{
			m_removeBtn->setStyleSheet("QPushButton {background-color:" + TAB_CONTENT_BTN_BACKGROUND_DISABLED_DT + ";"
				"color: " + TAB_CONTENT_BTN_TEXT_DISABLED_DT + ";"
				"border-radius:2px;"
				"border:none;}");
		}
		break;

		//MORE THEME
	default:
		break;
	}

}

void Scripts:: setRemoveBtnDisabled(bool disabled)
{
	m_removeBtn->setDisabled(disabled);
	setRemoveBtnStyle();
}
