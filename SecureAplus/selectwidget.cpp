#include "selectwidget.h"

SelectWidget::SelectWidget(Protection_Modes mode, bool selected, QWidget* parent)
	: QWidget(parent),
	m_mode(mode),
	m_selected(selected)
{
	ui.setupUi(this);


	/* Init frame widget */
	m_frame = new QFrame();

	/* Init widget layout */
	m_layout = new QVBoxLayout;


	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	m_frame->setFixedSize(270, 90);
	m_layout->addWidget(m_frame);
	this->setFixedSize(270, 90);
	/* Set layout */
	setLayout(m_layout);

	/* Init frame content layout */
	m_contentLayout = new QHBoxLayout;
	m_contentLayout->setContentsMargins(22, 18, 22, 18);
	m_contentLayout->setSpacing(20);

	/* Init icon label */
	m_iconLabel = new QLabel();
	m_iconLabel->setFixedSize(54, 54);
	m_iconLabel->setAlignment(Qt::AlignCenter);

	/* Init title */
	m_title = new QLabel();
	m_title->setFont(FONT);
	m_title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_title->setWordWrap(true);


	if (m_mode == Observation_Mode)
	{
		m_title->setFixedHeight(20);

		observationProver = new QWidget();
		observationLayout = new QVBoxLayout();
		observationProver->setLayout(observationLayout);
		observationLayout->setContentsMargins(0, 0, 0, 0);
		observationLayout->setSpacing(0);

		m_proIconLabel = new QLabel();
		m_proIconLabel->setFixedSize(26, 13);
		m_proIconLabel->setAlignment(Qt::AlignLeft| Qt::AlignTop);
		observationLayout->addWidget(m_title);
		observationLayout->addWidget(m_proIconLabel);
	}
	else if (m_mode == Lockdown_Mode)
	{
		m_title->setFixedHeight(20);

		lockDownMode = new QWidget();
		lockdownLayout = new QVBoxLayout();
		lockdownLayout->setContentsMargins(0, 0, 0, 0);
		lockdownLayout->setSpacing(0);
		lockDownMode->setLayout(lockdownLayout);

		m_lockdownModeLabel = new QLabel();
		m_lockdownModeLabel->setFixedSize(66, 20);
		m_lockdownModeLabel->setAlignment(Qt::AlignCenter);
		m_lockdownModeLabel->setFont(SMALL_FRONT);
		lockdownLayout->addWidget(m_title);
		lockdownLayout->addWidget(m_lockdownModeLabel);
		m_lockdownModeLabel->setVisible(false);
	}

	/* Init title */
	m_description = new QLabel();
	m_description->setFont(SMALL_FRONT);
	m_description->setWordWrap(true);
	m_description->setVisible(false);

	m_contentLayout->addWidget(m_iconLabel);

	if (m_mode == Observation_Mode)
	{

		m_contentLayout->addWidget(observationProver);
	}
	else if(m_mode == Lockdown_Mode)
	{
		m_contentLayout->addWidget(lockDownMode);

	}
	else
	{
		m_contentLayout->addWidget(m_title);
	}

	m_contentLayout->addWidget(m_description);
	/* Set frame layout */
	m_frame->setLayout(m_contentLayout);
	setStyle();
	setIcon();
	setModeText();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &SelectWidget::changeTheme);
}

SelectWidget::~SelectWidget()
{
}

void SelectWidget::setSelected(bool selected)
{
	m_selected = selected;
	setStyle();
	setIcon();
	m_iconLabel->setVisible(true);
	m_title->setVisible(true);
	m_description->setVisible(false);

	if (m_mode == Observation_Mode)
	{
		observationProver->setVisible(true);
		m_title->setVisible(true);
		m_proIconLabel->setVisible(true);
	}
}

void SelectWidget::setLockDownText(QString text)
{
	if (text == "")
	{
		m_lockdownModeLabel->setVisible(false);
	}
	else
	{
		m_lockdownModeLabel->setText(text);
		m_lockdownModeLabel->setVisible(true);
	}
}



void SelectWidget::setIcon()
{
	int width = 0;
	int height = 0;

	if (m_selected)
	{
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			switch (m_mode)
			{
			case Automatic_Mode:
				icon = util::getInstance()->ChangeSVGColor(AUTOMATIC, ICON_SELECTED_COLOR_LT);
				break;
			case Interactive_Mode:
				icon = util::getInstance()->ChangeSVGColor(INTERACTIVE, ICON_SELECTED_COLOR_LT);
				break;
			case Lockdown_Mode:
				icon = util::getInstance()->ChangeSVGColor(LOCKDOWN, ICON_SELECTED_COLOR_LT);
				break;
			case TrustAll_Mode:
				icon = util::getInstance()->ChangeSVGColor(TRUSTALL, ICON_SELECTED_COLOR_LT);
				break;
			case Observation_Mode:
				icon = util::getInstance()->ChangeSVGColor(OBSERVATION, ICON_SELECTED_COLOR_LT);
				m_proIcon = util::getInstance()->ChangeSVGColor(PRO, PRO_ICON_SELECTED_COLOR_LT);
				break;
			default:
				break;
			}

			break;

		case Theme_Type::Dark_Theme:
			switch (m_mode)
			{
			case Automatic_Mode:
				icon = util::getInstance()->ChangeSVGColor(AUTOMATIC, ICON_SELECTED_COLOR_DT);
				break;
			case Interactive_Mode:
				icon = util::getInstance()->ChangeSVGColor(INTERACTIVE, ICON_SELECTED_COLOR_DT);
				break;
			case Lockdown_Mode:
				icon = util::getInstance()->ChangeSVGColor(LOCKDOWN, ICON_SELECTED_COLOR_DT);
				break;
			case TrustAll_Mode:
				icon = util::getInstance()->ChangeSVGColor(TRUSTALL, ICON_SELECTED_COLOR_DT);
				break;
			case Observation_Mode:
				icon = util::getInstance()->ChangeSVGColor(OBSERVATION, ICON_SELECTED_COLOR_DT);
				m_proIcon = util::getInstance()->ChangeSVGColor(PRO, PRO_ICON_SELECTED_COLOR_DT);
				break;
			default:
				break;
			}

			break;

			//MORE THEME
		default:
			break;
		}

	}
	else
	{
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			switch (m_mode)
			{
			case Automatic_Mode:
				icon = util::getInstance()->ChangeSVGColor(AUTOMATIC, ICON_UNSELECTED_COLOR_LT);
				break;

			case Interactive_Mode:
				icon = util::getInstance()->ChangeSVGColor(INTERACTIVE, ICON_UNSELECTED_COLOR_LT);
				break;

			case Lockdown_Mode:
				icon = util::getInstance()->ChangeSVGColor(LOCKDOWN, ICON_UNSELECTED_COLOR_LT);
				break;

			case TrustAll_Mode:
				icon = util::getInstance()->ChangeSVGColor(TRUSTALL, ICON_UNSELECTED_COLOR_LT);
				break;

			case Observation_Mode:
				icon = util::getInstance()->ChangeSVGColor(OBSERVATION, ICON_UNSELECTED_COLOR_LT);
				m_proIcon = util::getInstance()->ChangeSVGColor(PRO, PRO_ICON_UNSELECTED_COLOR_LT);

				break;

			default:
				break;
			}

			break;

		case Theme_Type::Dark_Theme:
			switch (m_mode)
			{
			case Automatic_Mode:
				icon = util::getInstance()->ChangeSVGColor(AUTOMATIC, ICON_UNSELECTED_COLOR_DT);
				break;
			case Interactive_Mode:
				icon = util::getInstance()->ChangeSVGColor(INTERACTIVE, ICON_UNSELECTED_COLOR_DT);
				break;
			case Lockdown_Mode:
				icon = util::getInstance()->ChangeSVGColor(LOCKDOWN, ICON_UNSELECTED_COLOR_DT);
				break;
			case TrustAll_Mode:
				icon = util::getInstance()->ChangeSVGColor(TRUSTALL, ICON_UNSELECTED_COLOR_DT);
				break;
			case Observation_Mode:
				icon = util::getInstance()->ChangeSVGColor(OBSERVATION, ICON_UNSELECTED_COLOR_DT);
				m_proIcon = util::getInstance()->ChangeSVGColor(PRO, PRO_ICON_UNSELECTED_COLOR_DT);
				break;
			default:
				break;
			}

			break;

			//MORE THEME
		default:
			break;
		}
	}

	switch (m_mode)
	{
	case Automatic_Mode:
		width = 31;
		height = 33;
		break;
	case Interactive_Mode:
		width = 31;
		height = 33;
		break;
	case Lockdown_Mode:
		width = 29;
		height = 33;
		break;
	case TrustAll_Mode:
		width = 29;
		height = 33;
		break;
	case Observation_Mode:
		width = 33;
		height = 21;
		break;
	default:
		break;
	}

	if (m_mode == Observation_Mode)
	{
		m_proIconLabel->setPixmap(m_proIcon.pixmap(26, 13));
	}

	m_iconLabel->setPixmap(icon.pixmap(width, height));
}

void SelectWidget::setStyle()
{
	if (m_selected)
	{
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			m_frame->setStyleSheet("QFrame {background-color:" + WDG_SELECTED_BGROUND_COLOR_LT + ";"
				"border-radius:6px;}"
				"QFrame:hover{border: 1px solid " + GRID_BORDER_LIGHT_THEME_COLOR + ";}"
				"QLabel:hover{border: none;}"
				"QLabel { border-radius:0px;}");

			m_iconLabel->setStyleSheet("QLabel {background-color:" + LABEL_ICON_SELECTED_BACKGROUND_COLOR_LT + ";"
				"border-radius:27px;}");

			m_title->setStyleSheet("QLabel {  color:" + TITLTE_SELECTED_COLOR_LT + ";border-radius:0px;}");
			m_description->setStyleSheet("QLabel {  color:" + TITLTE_SELECTED_COLOR_LT + ";border-radius:0px;}");
			if (m_mode == Lockdown_Mode)
			{
				m_lockdownModeLabel->setStyleSheet("QLabel {  color:" + TITLTE_SELECTED_COLOR_LT + "; border-radius:6px;"
					"border: 1px solid " + GRID_BORDER_LIGHT_THEME_COLOR + ";}");
			}
			break;

		case Theme_Type::Dark_Theme:
			m_frame->setStyleSheet("QFrame {background-color:" + WDG_SELECTED_BGROUND_COLOR_DT + ";"
				"border-radius:6px;}"
				"QFrame:hover{border: 1px solid " + GRID_BORDER_DARK_THEME_COLOR + ";}"
				"QLabel:hover{border: none;}"
				"QLabel { border-radius:0px;}");

			m_iconLabel->setStyleSheet("QLabel {background-color:" + LABEL_ICON_SELECTED_BACKGROUND_COLOR_DT + ";"
				"border-radius:27px}");

			m_title->setStyleSheet("QLabel {color:" + TITLTE_SELECTED_COLOR_DT + ";border-radius:0px;}");
			m_description->setStyleSheet("QLabel {  color:" + TITLTE_SELECTED_COLOR_DT + ";border-radius:0px;}");

			if (m_mode == Lockdown_Mode)
			{
				m_lockdownModeLabel->setStyleSheet("QLabel {  color:#FFFFFF; border-radius:10px;"
					"border: 1px solid #FFFFFF;}");
			}
			break;

			//MORE THEME
		default:
			break;
		}
	}
	else
	{
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			m_frame->setStyleSheet("QFrame {background-color:" + WDG_UNSELECTED_BGROUND_COLOR_LT + ";"
				"border-radius:6px;}"
				"QFrame:hover{border: 1px solid " + GRID_BORDER_LIGHT_THEME_COLOR + ";}"
				"QLabel:hover{border: none;}"
				"QLabel { border-radius:0px;}");

			m_iconLabel->setStyleSheet("QLabel {background-color:" + LABEL_ICON_UNSELECTED_BACKGROUND_COLOR_LT + ";"
				"border-radius:27px;}");

			m_title->setStyleSheet("QLabel {  color:" + TITLTE_UNSELECTED_COLOR_LT + ";border-radius:0px;}");
			m_description->setStyleSheet("QLabel {  color:" + TITLTE_UNSELECTED_COLOR_LT + ";border-radius:0px;}");
			
			if (m_mode == Lockdown_Mode)
			{
				m_lockdownModeLabel->setStyleSheet("QLabel {  color:" + TITLTE_SELECTED_COLOR_LT + "; border-radius:10px;"
					"border: 1px solid " + GRID_BORDER_LIGHT_THEME_COLOR + ";}");
			}

			break;

		case Theme_Type::Dark_Theme:
			m_frame->setStyleSheet("QFrame {background-color:" + WDG_UNSELECTED_BGROUND_COLOR_DT + ";"
				"border-radius:6px;}"
				"QFrame:hover{border: 1px solid " + GRID_BORDER_DARK_THEME_COLOR + ";}"
				"QLabel:hover{border: none;}"
				"QLabel { border-radius:0px;}");

			m_iconLabel->setStyleSheet("QLabel {background-color:" + LABEL_ICON_UNSELECTED_BACKGROUND_COLOR_DT + ";"
				"border-radius:27px;}");

			m_title->setStyleSheet("QLabel {  color:" + TITLTE_UNSELECTED_COLOR_DT + ";border-radius:0px;}");
			m_description->setStyleSheet("QLabel {  color:" + TITLTE_UNSELECTED_COLOR_DT + ";border-radius:0px;}");

			if (m_mode == Lockdown_Mode)
			{
				m_lockdownModeLabel->setStyleSheet("QLabel {  color:#FFFFFF; border-radius:10px;"
					"border: 1px solid #FFFFFF;}");
			}

			break;

			//MORE THEME
		default:
			break;
		}
	}
}
void SelectWidget::setModeText()
{
	switch (m_mode)
	{
	case Automatic_Mode:
		m_title->setText("Automatic");
		m_description->setText("Keep prompts to a minimum. Automatically block or trust majority of new program outside of your trusted list");
		break;

	case Interactive_Mode:
		m_title->setText("Interactive");
		m_description->setText("You will receive security prompts with recommended actions but all decisions to allow or deny a file/ program is always yours to make.");
		break;

	case Lockdown_Mode:
		m_title->setText("Lockdown");
		m_description->setText("Programs outside of your trusted list will be automatically blocked.");
		break;

	case TrustAll_Mode:
		m_title->setText("Trust All");
		m_description->setText("No prompts for a specified duration. Any program is allowed to run and is automatically added to your trusted list.");
		break;

	case Observation_Mode:
		m_title->setText("Observation");
		m_description->setText("Untrusted applications are allowed to run, and will be recorded in the log file. The untrusted applications will remain untrusted when Observation Mode is switched off.");
		break;

	default:
		break;
	}
}

bool SelectWidget::event(QEvent* e)
{
	if (!m_selected)
	{
		/* Hover widget */
		if (e->type() == QEvent::Enter)
		{
			m_iconLabel->setVisible(false);
			m_title->setVisible(false);
			m_description->setVisible(true);
			if (m_mode == Observation_Mode)
			{
				observationProver->setVisible(false);
				m_title->setVisible(false);
				m_proIconLabel->setVisible(false);
			}
			else if (m_mode == Lockdown_Mode)
			{
				lockDownMode->setVisible(false);
				m_title->setVisible(false);
				m_lockdownModeLabel->setVisible(false);
			}
		}
		/* Leave Widget */
		if (e->type() == QEvent::Leave)
		{
			m_iconLabel->setVisible(true);
			m_title->setVisible(true);
			m_description->setVisible(false);
			if (m_mode == Observation_Mode)
			{
				observationProver->setVisible(true);
				m_title->setVisible(true);
				m_proIconLabel->setVisible(true);
			}
			else if (m_mode == Lockdown_Mode)
			{
				lockDownMode->setVisible(true);
				m_title->setVisible(true);
				if (m_lockdownModeLabel->text() != "")
				{
					m_lockdownModeLabel->setVisible(true);
				}
			}
		}
	}
	return QWidget::event(e);
}

void SelectWidget::mousePressEvent(QMouseEvent* event)
{
	if (!m_selected)
	{
		emit changeMode();
	}
}

void SelectWidget::changeTheme()
{
	setStyle();
	setIcon();
}
