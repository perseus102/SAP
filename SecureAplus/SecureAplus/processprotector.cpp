#include "processprotector.h"

ProcessProtector::ProcessProtector(QWidget *parent)
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
	m_scriptsDesc->setText("Some malwares have the ability to inject their code into another process, and run as the infected process. The process in this list will be protected against such attack.");

	QLabel* descSpacer = new QLabel();
	descSpacer->setFixedHeight(15);

	m_processProtectorTable = new ProcessProtectorTable();

	QLabel* bottomTableSpacer = new QLabel();
	bottomTableSpacer->setFixedHeight(10);

	QWidget* bottomBtns = new QWidget();
	bottomBtns->setFixedHeight(30);
	QHBoxLayout* btnsLayout = new QHBoxLayout();
	btnsLayout->setContentsMargins(0, 0, 0, 0);
	btnsLayout->setSpacing(0);
	bottomBtns->setLayout(btnsLayout);

	QLabel* leftBtnsSpacer = new QLabel();

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

	btnsLayout->addWidget(leftBtnsSpacer);
	btnsLayout->addWidget(m_removeBtn);
	btnsLayout->addWidget(btnsSpacer);
	btnsLayout->addWidget(m_addBtn);

	QLabel* bottomSpacer = new QLabel();

	m_layout->addWidget(m_scriptsDesc);
	m_layout->addWidget(descSpacer);
	m_layout->addWidget(m_processProtectorTable);
	m_layout->addWidget(bottomTableSpacer);
	m_layout->addWidget(bottomBtns);
	m_layout->addWidget(bottomSpacer);

	transparent = new WidgetTransparent();
	m_addProcessDialog = new AddProcessProtectorDialog();

	setLayout(m_layout);
	setStyle();

	connect(m_removeBtn, &QPushButton::clicked, m_processProtectorTable, &ProcessProtectorTable::removeRows);
	connect(m_removeBtn, &QPushButton::clicked, this, &ProcessProtector::removeButtonClicked);

	connect(m_addBtn, &QPushButton::clicked, this, &ProcessProtector::addButtonClicked);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &ProcessProtector::changeTheme, Qt::ConnectionType::DirectConnection);

	connect(m_processProtectorTable, &ProcessProtectorTable::setRemoveBtnDisabled, this, &ProcessProtector::setRemoveBtnDisabled);
	connect(m_addProcessDialog, &AddProcessProtectorDialog::addProcess, m_processProtectorTable, &ProcessProtectorTable::AddProcessFromDialog);


}

ProcessProtector::~ProcessProtector()
{
}

void ProcessProtector::addButtonClicked()
{
	QRect geometry = AppSetting::getInstance()->getAppGeometry();

	transparent->showWidget();
	m_addProcessDialog->setGeometry(geometry.x() + (geometry.width() / 2) - 190 /*190 is half width*/, geometry.y() + 16, 380, 195);
	m_addProcessDialog->showDialog();
	transparent->hide();
}

void ProcessProtector::removeButtonClicked()
{
}

void ProcessProtector::changeTheme()
{
	setStyle();
}

void ProcessProtector::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:

		setRemoveBtnStyle();

		m_scriptsDesc->setStyleSheet("QLabel{color: " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_addBtn->setStyleSheet("QPushButton {background-color:none;"
			"color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:

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
void ProcessProtector::setRemoveBtnStyle()
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
void ProcessProtector::setRemoveBtnDisabled(bool disabled)
{
	m_removeBtn->setDisabled(disabled);
	setRemoveBtnStyle();
}
