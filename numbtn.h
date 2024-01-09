#ifndef NUMBTN_H
#define NUMBTN_H

#include <QWidget>

#include <QLabel>
#include <QPushButton>

#include <QHBoxLayout>
#include <QSpacerItem>

#include <QSizePolicy>

#include <QSpinBox>
#include <QLineEdit>

#include <QMenu>
#include <QAction>

#include <QEvent>
#include <QKeyEvent>

#include <QDebug>

class numbtn : public QWidget
{
    Q_OBJECT
public:
    explicit numbtn(QWidget *parent = nullptr);

    void setNumType(int i);
    void setEditMode(bool state);

signals:

private:

protected:
      bool eventFilter(QObject *obj, QEvent *event) override;


    uint64_t m_number;

    QLineEdit* m_edit;
    QLabel* m_lbl;
    QPushButton* m_btn;
    QHBoxLayout *m_hLayout;
    QMenu* m_menu;

};

#endif // NUMBTN_H
