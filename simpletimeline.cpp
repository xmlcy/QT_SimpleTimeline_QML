#include "simpletimeline.h"

#include "simpletimeline.h"

SimpleTimeline::SimpleTimeline(QQuickItem *parent)
    : QQuickItem(parent)
{
    // 可以在这里进行一些初始化操作
}

void SimpleTimeline::createAnimate(QObject *target, const QByteArray &propertyName, QString name, int msecs)
{
    // 创建串行动画组
    QSequentialAnimationGroup *seqAnimation = new QSequentialAnimationGroup(this);
    //    QSequentialAnimationGroup seqAnimation(this);

    // 创建属性动画
    QPropertyAnimation *propertyAnimation = new QPropertyAnimation(target, propertyName, this);

    // 设置动画的一些参数，例如持续时间、起始值、结束值等
    propertyAnimation->setDuration(msecs);  // 设置动画持续时间为1秒

    // 将属性动画添加到串行动画组中
    seqAnimation->addAnimation(propertyAnimation);

    // 将动画组添加到向量中，以便稍后管理
    animation.push_back(propertyAnimation);

    // 将串行动画组添加到向量中，以便稍后管理
    seqGroup[name] = seqAnimation;

    // 将串行动画组添加到并行动画组中
    parGroup.addAnimation(seqAnimation);
}

void SimpleTimeline::addFrame(QString name, int index, qreal step, const QVariant &value)
{
    auto it = seqGroup.find(name);
    // 检查是否有串行动画组可用
    if (it != seqGroup.end())
    {
        // 获取最后一个串行动画组
        QSequentialAnimationGroup *lastSeqAnimation = it->second;

        lastSeqAnimation->animationAt(index);

        // 创建属性动画
        QPropertyAnimation *propertyAnimation = qobject_cast<QPropertyAnimation*>(lastSeqAnimation->animationAt(index));

        // 设置关键帧的一些参数，例如时间点、值等
        propertyAnimation->setKeyValueAt(step, value);   // 在时间点0设置关键帧值为0

        // 将属性动画添加到串行动画组中
        lastSeqAnimation->addAnimation(propertyAnimation);
    } else {
        qDebug() << "Key" << name << "does not exist.";
    }
}

void SimpleTimeline::addFrame(QString name, qreal step, const QVariant &value)
{
    auto it = seqGroup.find(name);
    // 检查是否有串行动画组可用
    if (it != seqGroup.end())
    {
        // 获取最后一个串行动画组
        QPropertyAnimation *lastPropertyAnimation = animation.back();

        // 设置关键帧的一些参数，例如时间点、值等
        lastPropertyAnimation->setKeyValueAt(step, value);   // 在时间点0设置关键帧值为0
    } else {
        qDebug() << "Key" << name << "does not exist.";
    }
}



void SimpleTimeline::start()
{
    parGroup.start();
}


// 在析构函数中记得释放动态分配的内存，防止内存泄漏
SimpleTimeline::~SimpleTimeline()
{
    // 释放动态分配的 QPropertyAnimation 对象
    for (QPropertyAnimation* anim : animation)
    {
        delete anim;
    }

    // 释放动态分配的 QSequentialAnimationGroup 对象
    for (auto it = seqGroup.begin(); it != seqGroup.end(); ++it) {
        delete it->second;  // 释放 QSequentialAnimationGroup
        seqGroup.erase(it++);
    }
    seqGroup.clear();  // 清空 map
}

