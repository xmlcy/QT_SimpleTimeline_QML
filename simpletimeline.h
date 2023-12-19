#ifndef SIMPLETIMELINE_H
#define SIMPLETIMELINE_H

#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <vector>
#include "MyAnimationGroup.h"


class SimpleTimeline : public QObject
{
    Q_OBJECT
    QML_ELEMENT
signals:
    void begin();
public slots:
    void doSomething(QString text) {
        qDebug() << text << "SimpleTimeline::doSomething() called";
    }


    void createAnimate(QObject *target, QString name);
    void addFrame(QObject *target, const QByteArray &propertyName, QString name, const QVariant &value, int type, qreal time);

    void start();

public:
    explicit SimpleTimeline(QObject *parent = nullptr);
    ~SimpleTimeline(); // 在析构函数中释放动态分配的内存

private slots:
    void onAnimationFinished() {
        // Optionally perform cleanup or take additional actions when all animations finish
        // For example, you can emit a signal to notify the main application
        emit animationFinished();
    }

signals:
    void animationFinished();
private:
    QParallelAnimationGroup parGroup;
//    std::map<QString, QSequentialAnimationGroup*> seqGroup;
    std::vector<MyAnimationGroup> seqGroup;
    std::vector<QPropertyAnimation*> animation;

};

#endif // SIMPLETIMELINE_H
