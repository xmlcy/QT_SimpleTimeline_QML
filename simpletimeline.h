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
    Q_PROPERTY(double recordstate READ getrecordstate WRITE setrecordstate NOTIFY recordstateChanged FINAL)
    Q_PROPERTY(float xnum READ getxnum WRITE setxnum NOTIFY xnumChanged FINAL)
signals:
    void begin();
public slots:
    //串操作
    void createAnimate(QString name);
    void deleteAnimate(QString name);

    //帧操作
    void addFrame(QObject *target, const QByteArray &propertyName, QString name, const QVariant &value, int type, qreal time);
    void deleteFrame(QString name, qreal time);
    void updateFrame(QString name, const QVariant &value, int type,qreal oldtime, qreal newtime);
    void addFrameButton(QObject *target, const QByteArray &propertyName, QString name, const QVariant &value, int type, qreal time);
    QVariant preview(QString name, qreal time);

    void start();
    void stop();

public:
    explicit SimpleTimeline(QObject *parent = nullptr);
    ~SimpleTimeline(); // 在析构函数中释放动态分配的内存
    void setrecordstate(int state);
    int getrecordstate();
    float getxnum();
    void setxnum(float x);

private slots:
    void onAnimationFinished() {
        // Optionally perform cleanup or take additional actions when all animations finish
        // For example, you can emit a signal to notify the main application
        emit animationFinished();
    }

signals:
    void animationFinished();
    void recordstateChanged(int state);
    void xnumChanged();
private:
    QParallelAnimationGroup parGroup;
//    std::map<QString, QSequentialAnimationGroup*> seqGroup;
    std::vector<MyAnimationGroup> seqGroup;
    std::vector<QPropertyAnimation*> animation;
    int recordstate;
    float xnum;
    float ynum;
};

#endif // SIMPLETIMELINE_H
