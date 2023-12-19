//#include "simpletimeline.h"


//SimpleTimeline::SimpleTimeline(QObject *parent)
//    : QObject{parent}
//{

//}



//void SimpleTimeline::createAnimate(QObject *target, const QByteArray &propertyName)
//{
//    QSequentialAnimationGroup seqGroup;
//    seqGroup_.push_back(seqGroup);

//    QPropertyAnimation *animation = new QPropertyAnimation(target, propertyName);
//    seqGroup.addAnimation(animation);

//    parGroup_.addAnimation(&seqGroup_[0]);


//}


// simpletimeline.cpp

#include "simpletimeline.h"
typedef QPair<qreal, QVariant> KeyValue;
typedef QList<KeyValue> KeyValues;

SimpleTimeline::SimpleTimeline(QObject *parent)
    : QObject(parent)
{
    // 可以在这里进行一些初始化操作
}

void SimpleTimeline::createAnimate(QObject *target, QString name){
    qDebug() << "进入createAnimate";
    // 创建串行动画组
    QSequentialAnimationGroup *seqAnimation = new QSequentialAnimationGroup(this);
    std::vector<int> times;
    MyAnimationGroup animationgroup = MyAnimationGroup(seqAnimation,times,name);
    seqGroup.push_back(animationgroup);
    // 将串行动画组添加到并行动画组中
    parGroup.addAnimation(seqAnimation);
}

//target指将动画绑定在谁身上，name是串名字，value是传过来的值，type是曲线类型, time是此帧的时间点
void SimpleTimeline::addFrame(QObject *target, const QByteArray &propertyName, QString name, const QVariant &value, int type, qreal time)
{
    auto it = seqGroup.begin();
    int ani_position = -1; // 初始化位置为-1，表示未找到
    int flag = 0;
    // 根据名字从所有串中检索是否有串行动画组可用
    while (it != seqGroup.end()){
        if(it->seqGroupName == name)
            flag = 1;
        it++;
    }
    it--;
    if (flag == 1)
    {
        //获取串
        QSequentialAnimationGroup *animationGroup = it->seqAnimation;
        //获取串上每个帧的时间点
        std::vector<int> times(it->times);
        //遍历串中所有帧，判断新增的时间点在中间还是末尾

        for (int i = 0; i < times.size(); i++){
            if (time >= times[i]){
                ani_position = i;
            } else {
                break;
            }
        }

        // 输出结果
        if(animationGroup->animationCount() == 0){
            qDebug() << "串为空";
            QPropertyAnimation *animation = new QPropertyAnimation(target,propertyName);
            animation->setDuration(time);
            animation->setEasingCurve(static_cast<QEasingCurve::Type>(type));
            animation->setKeyValueAt(1,value);
            it->times.push_back(time);
            it->seqAnimation->addAnimation(animation);
        } else if (ani_position == animationGroup->animationCount() - 1) {
            qDebug() << "给定的时间点在序列动画组之后";
            QPropertyAnimation *animation = new QPropertyAnimation(target,propertyName);
            qreal timebefor = times[ani_position];
            qDebug() << "timebefor:" << timebefor;
            animation->setDuration(time-timebefor);
            animation->setEasingCurve(static_cast<QEasingCurve::Type>(type));
            animation->setKeyValueAt(1,value);
            it->times.push_back(time);
            it->seqAnimation->addAnimation(animation);
        } else {
            //新帧为第一个且后边还有其他帧时 或 插在中间位置前后都有帧时
            qDebug() << "给定的时间点在序列动画组的第" << ani_position + 1 << "个动画之后";
            QPropertyAnimation *animation = new QPropertyAnimation(target,propertyName);
            qreal timebefor = times[ani_position];
            qDebug() << "timebefor:" << timebefor;
            animation->setDuration(time-timebefor);
            animation->setEasingCurve(static_cast<QEasingCurve::Type>(type));
            animation->setKeyValueAt(1,value);
            auto it1 = it->times.begin();
            it->times.insert((it1+1),time);

            //修改后一个帧的持续时间
            QPropertyAnimation *animationafter =  qobject_cast<QPropertyAnimation*>(animationGroup->animationAt(ani_position+1));
            qreal timeafter = it->times[ani_position+2];
            qDebug() << "timeafter:" << timeafter;
            QPropertyAnimation *absAni = qobject_cast<QPropertyAnimation*>(it->seqAnimation->animationAt(ani_position+1));
            if (absAni != NULL){
                qDebug() << "absAni not null";
                absAni->setDuration(timeafter-time);
            }

            it->seqAnimation->insertAnimation(ani_position+1,animation);
        }
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
//    // 释放动态分配的 QPropertyAnimation 对象
//    for (QPropertyAnimation* anim : animation)
//    {
//        delete anim;
//    }

//    // 释放动态分配的 QSequentialAnimationGroup 对象
//    for (auto it = seqGroup.begin(); it != seqGroup.end(); ++it) {
//        delete it->seqAnimation;  // 释放 QSequentialAnimationGroup
//        seqGroup.erase(it++);
//    }
//    seqGroup.clear();  // 清空 map
}
