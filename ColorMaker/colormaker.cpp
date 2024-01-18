#include "colormaker.h"

#include <QTimerEvent>
#include <QDateTime>
#include <QRandomGenerator>

#include <QtGlobal>

#include <QTimer>
#include <qapplicationstatic.h>

ColorMaker::ColorMaker(QObject *parent)
    : QObject{parent}
{
    srand((unsigned)time(0));
}

ColorMaker::~ColorMaker()
{

}

// 获取颜色
QColor ColorMaker::color() const
{
    return m_CurrentColor;
}

// 设置颜色
void ColorMaker::setColor(const QColor& color)
{
    m_CurrentColor = color;
    emit colorChanged(m_CurrentColor);
}

QColor ColorMaker::timeColor() const
{
    QTime time = QTime::currentTime();
    int r = time.hour();
    int g = time.minute() * 2;
    int b = time.second() * 4;

    return QColor::fromRgb(r, g, b);
}

// 获取算法
ColorMaker::GenerateAlgorithm ColorMaker::algorithm() const
{
    return m_Algorithm;
}

// 设置算法
void ColorMaker::SetAlgorithm(GenerateAlgorithm algorithm)
{
    m_Algorithm = algorithm;
}

// 开始计时器
void ColorMaker::Start()
{
    if (m_nColorTimer == 0)
    {
        m_nColorTimer = startTimer(1000);
    }
}

// 停止计时器
void ColorMaker::Stop()
{
    if (m_nColorTimer > 0)
    {
        killTimer(m_nColorTimer);
        m_nColorTimer = 0;
    }
}

void ColorMaker::timerEvent(QTimerEvent* e)
{
    if (e->timerId() == m_nColorTimer)
    {
        switch (m_Algorithm)
        {
        case RandomRGB:
            m_CurrentColor.setRgb(rand() % 255, rand() % 255, rand() % 255);
            break;
        case RandomRed:
            m_CurrentColor.setRgb(rand() % 255);
        case RandomBlue:
            m_CurrentColor.setRgb(rand() % 255);
        case RandomGreen:
            m_CurrentColor.setRgb(rand() % 255);
        case LinearIncrease:
        {
            int r = m_CurrentColor.red() + 10;
            int g = m_CurrentColor.green() + 10;
            int b = m_CurrentColor.blue() + 10;

            m_CurrentColor.setRgb(r, g, b);
        }
        default:
            break;
        }

        emit colorChanged(m_CurrentColor);
        emit currentTime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    else
    {
        QObject::timerEvent(e);
    }
}

// 封装退出App函数
void ColorMaker::QuitApp()
{
    QTimer::singleShot(0, qApp, &QCoreApplication::quit);
}
