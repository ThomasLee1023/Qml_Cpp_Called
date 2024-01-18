#ifndef COLORMAKER_H
#define COLORMAKER_H

#include <QObject>
#include <QColor>

class ColorMaker : public QObject
{
    Q_OBJECT

    // Q_PROPERTY 定义的函数等参数，QML可以直接调用
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor timeColor READ timeColor)

public:
    explicit ColorMaker(QObject *parent = nullptr);

    ~ColorMaker();

    enum GenerateAlgorithm
    {
        RandomRGB,
        RandomRed,
        RandomGreen,
        RandomBlue,
        LinearIncrease
    };


    QColor color() const;
    void setColor(const QColor& color);
    QColor timeColor() const;


    Q_INVOKABLE GenerateAlgorithm algorithm() const;
    Q_INVOKABLE void SetAlgorithm(GenerateAlgorithm algorithm);

signals:
    void colorChanged(const QColor& color);
    void currentTime(const QString& strTime);

public:
    // 添加Q_INVOKABLE前缀，表示QML可直接调用
    Q_INVOKABLE void QuitApp();

public slots:
    void Start();
    void Stop();


protected:
    void timerEvent(QTimerEvent* e);

private:
    GenerateAlgorithm m_Algorithm = RandomRGB;
    QColor m_CurrentColor = Qt::black;
    int m_nColorTimer = 0;

};

#endif // COLORMAKER_H
