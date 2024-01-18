#ifndef CHANGEQMLCOLOR_H
#define CHANGEQMLCOLOR_H

#include <QObject>

class ChangeQmlColor : public QObject
{
    Q_OBJECT
public:
    ChangeQmlColor(QObject* pTarget, QObject *parent = nullptr);

    ~ChangeQmlColor();

protected slots:
    void onTimeOut();

private:
    QTimer* m_pTimer = nullptr;
    QObject* m_pTarget = nullptr;

};

#endif // CHANGEQMLCOLOR_H
