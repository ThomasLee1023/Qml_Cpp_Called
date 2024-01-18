#include "changeqmlcolor.h"

#include <QDateTime>
#include <QTimer>
#include <QColor>

ChangeQmlColor::ChangeQmlColor(QObject* pTarget, QObject *parent)
    : QObject{parent}
{
    m_pTimer = new QTimer(this);
    m_pTarget = pTarget;

    srand((unsigned)time(0));

    // 连接信号与槽函数
    connect(m_pTimer, &QTimer::timeout, this, &ChangeQmlColor::onTimeOut);

    m_pTimer->start(1000);
}

ChangeQmlColor::~ChangeQmlColor()
{
    delete m_pTimer;
    m_pTimer = nullptr;
}

// 槽函数
void ChangeQmlColor::onTimeOut()
{
    QColor color = QColor::fromRgb(rand() % 256, rand() % 256, rand() % 256);;
    m_pTarget->setProperty("color", color);
}
