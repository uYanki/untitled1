#include "numbtn.h"


numbtn::numbtn(QWidget *parent) : QWidget(parent)
{

    {
        m_btn = new QPushButton(this);

        setNumType(0);

        // 按钮宽高自适应文本内容
        QFontMetrics metrics(m_btn->font());
        m_btn->setFixedSize(metrics.boundingRect(m_btn->text()).size()*1.3);
    }

    {
        m_lbl = new QLabel(this);
        m_lbl->setText("4445554555");

        auto sp = m_lbl->sizePolicy();
        sp.setHorizontalPolicy(QSizePolicy::Expanding);
        m_lbl->setSizePolicy(sp);

        m_lbl->installEventFilter(this);

    }

    {

        m_edit = new QLineEdit(this);

        auto sp = m_edit->sizePolicy();
        sp.setHorizontalPolicy(QSizePolicy::Maximum);
        sp.setVerticalPolicy(QSizePolicy::Maximum);
        m_edit->setSizePolicy(sp);

        m_edit->installEventFilter(this);
    }

    {
        m_hLayout = new QHBoxLayout(this);
        m_hLayout->addWidget(m_lbl);
        m_hLayout->addWidget(m_btn);
        m_hLayout->addWidget(m_edit);
    }

    {
        m_menu = new QMenu(this);

        m_menu->addAction("Bin");
        m_menu->addAction("Oct");
        m_menu->addAction("Dec (singed)");
        m_menu->addAction("Dec (unsigned)");
        m_menu->addAction("Hex");
        m_menu->addAction("Float");

        m_menu->addSeparator();

        m_menu->addAction("16-bit");
        m_menu->addAction("32-bit");
        m_menu->addAction("64-bit");

    }

    setEditMode(false);

}

void numbtn::setEditMode(bool state)
{
    m_edit->setVisible(state);
    m_lbl->setVisible(!state);
    m_btn->setVisible(!state);

    if(state)
    {
        m_edit->setFocus();
    }

}

#include "random"

void numbtn::setNumType(int i){

    static QString LabelStyle =
            "QPushButton{"
            "background-color: %1;"
            "border-radius: 5px;"
            "padding: 2px 4px;"
            "color: white; }";

    static const char* styles[][2] = {
        {"bin", "rgb(128, 225, 128)"}, // binary
        {"oct", "rgb(128, 225, 128)"}, // octal
        {"u16", "rgb(128, 225, 225)"}, // decimalism
        {"u32", "rgb(128, 225, 225)"},
        {"u64", "rgb(128, 225, 225)"},
        {"s16", "rgb(128, 225, 225)"},
        {"s32", "rgb(128, 225, 225)"},
        {"s64", "rgb(128, 225, 225)"},
        {"hex", "rgb(128, 225, 128)"}, // hexadecimal
        {"f32", "rgb(225, 225, 128)"}, // float point
        {"f64", "rgb(225, 225, 128)"},
    };

    i = qrand() % 10;

    m_btn->setText(styles[i][0]);
    m_btn->setStyleSheet(LabelStyle.arg(styles[i][1]));

}

bool numbtn::eventFilter(QObject *watched, QEvent *event)
{

    if (watched == m_lbl)
    {
        switch ( event->type() )
        {

            case QEvent::MouseButtonDblClick: // 双击
            {
                m_edit->setText(m_lbl->text());
                setEditMode(true);
                break;
            }

            case QEvent::MouseButtonRelease: // 单击
            {
                m_lbl->setFocus();
                break;
            }

            case QEvent::KeyRelease : // 按键
            {
                m_edit->setText("");
                setEditMode(true);
                break;
            }

            case QEvent::FocusIn: // 获得焦点
            {
                // 解决获得焦点时触发重绘, 导致文本上移问题
                return true; // 拦截事件
            }

            default: break;

        }

    }
    else if (watched == m_edit )
    {
        if( event->type() == QEvent::KeyRelease )
        {
            QKeyEvent* ke = ( QKeyEvent* )event;

            if( ke->key() == Qt::Key::Key_Enter) // 确认键
            {
                m_lbl->setText(m_edit->text());
                setEditMode(false); // 触发变更
            }
        }
        else if( event->type() == QEvent::FocusOut ) // 失去焦点
        {
            setEditMode(false); // 不变更
        }

    }

    return QWidget::eventFilter(watched, event);
}
