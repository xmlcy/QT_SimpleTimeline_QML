#include "simpletimeline.h"

typedef QPair<qreal, QVariant> KeyValue;
typedef QList<KeyValue> KeyValues;

SimpleTimeline::SimpleTimeline(QObject *parent)
    : QObject(parent)
{
}

void SimpleTimeline::createAnimate(QString name){
//    qDebug() << "进入createAnimate";
    // 创建串行动画组
    QSequentialAnimationGroup *seqAnimation = new QSequentialAnimationGroup(this);
    std::vector<int> times;
    MyAnimationGroup animationgroup = MyAnimationGroup(seqAnimation,times,name);
    seqGroup.push_back(animationgroup);
    // 将串行动画组添加到并行动画组中
    parGroup.addAnimation(seqAnimation);
    qDebug() << name << "创建成功";
}

//删除串
void SimpleTimeline::deleteAnimate(QString name){
    auto it = seqGroup.begin();
    while (it != seqGroup.end()){
        if(it->seqGroupName == name){
            seqGroup.erase(it);
            parGroup.removeAnimation(it->seqAnimation);
        }
    }
}

//target指将动画绑定在谁身上，name是串名字，value是传过来的值，type是曲线类型, time是此帧的时间点
void SimpleTimeline::addFrame(QObject *target, const QByteArray &propertyName, QString name, const QVariant &value, int type, qreal time)
{
    auto it = seqGroup.begin();
    int ani_position = -1; // 初始化位置为-1，表示未找到
    int flag = 0;
    // 根据名字从所有串中检索是否有串行动画组可用
    while (it != seqGroup.end()){
        if(it->seqGroupName == name) {
            flag = 1;
            break;
        }
        it++;
    }
    if (flag == 1)
    {
        qDebug() << "Key" << it->seqGroupName;
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
            qreal timebefor;
            QPropertyAnimation *animation = new QPropertyAnimation(target,propertyName);
            if (ani_position == -1) {
                timebefor = 0;
            }else{
                timebefor = times[ani_position];
            }
            qDebug() << "timebefor:" << timebefor;
            animation->setDuration(time-timebefor);
            animation->setEasingCurve(static_cast<QEasingCurve::Type>(type));
            animation->setKeyValueAt(1,value);
            auto it1 = it->times.begin();
            //在第ani_position+1后加
            it->times.insert((it1+ani_position+1),time);

            //修改后一个帧的持续时间
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

//name是串名，time是时间点
void SimpleTimeline::deleteFrame(QString name, qreal time)
{
    //根据串名找到串
    auto it = seqGroup.begin();
    int flag = 0;
    // 根据名字从所有串中检索是否有串行动画组可用
    while (it != seqGroup.end()){
        if(it->seqGroupName == name) {
            flag = 1;
            break;
        }
        it++;
    }
    if (flag == 1)
    {
        //获取串上所有时间
        std::vector<int> times(it->times);
        //找到传回的时间在times中的位置
        int t = -1;
        for (int i = 0; i < times.size(); ++i)
        {
            qDebug() << "t:" << t << "times[i]" << times[i];
            if(time == times[i]){
                t = i;
            }

        }
        qDebug() << "t=" << t;
        //删除帧为最后一帧
        if (t == times.size()-1)
        {
            qDebug() << "删除最后一帧";
            it->seqAnimation->takeAnimation(t);
            it->times.erase(it->times.begin()+t);
        }
        else{
            qDebug() << "删除第" << t+1 << "帧";
            qreal timeafter = it->times[t+1];
            qreal timebefor = it->times[t-1];
            qDebug() << "timebefor:" << timebefor;
            qDebug() << "timeafter:" << timeafter;
            QPropertyAnimation *absAni = qobject_cast<QPropertyAnimation*>(it->seqAnimation->animationAt(t+1));
            if (absAni != NULL){
                qDebug() << "absAni not null";
                absAni->setDuration(timeafter-timebefor);
            }
            it->seqAnimation->takeAnimation(t);
            auto it1 = it->times.begin();
            it->times.erase(it1+t);
        }
        for (int i = 0; i < it->times.size(); ++i)
        {
            qDebug() << "删除元素后times[i]" << it->times[i];
        }
    }
}

void SimpleTimeline::updateFrame(QString name, const QVariant &value, int type, qreal oldtime, qreal newtime)
{
    //根据串名找到串
    auto it = seqGroup.begin();
    int flag = 0;
    // 根据名字从所有串中检索是否有串行动画组可用
    while (it != seqGroup.end()){
        if(it->seqGroupName == name)
        {
            flag = 1;
            break;
        }
        it++;
    }
    if (flag == 1)
    {
        //获取串上所有时间
        std::vector<int> times(it->times);
        //找到传回的时间在times中的位置
        int t = -1;
        for (int i = 0; i < times.size(); ++i)
        {
            qDebug() << "t:" << t << "times[i]" << times[i];
            if(oldtime == times[i]){
                t = i;
            }

        }
        qDebug() << "t=" << t;

        it->times[t] = newtime;
        qDebug() << "修改第" << t+1 << "帧";
        qreal timeafter = it->times[t+1];
        qreal timebefor = it->times[t-1];
        qDebug() << "timebefor:" << timebefor;
        qDebug() << "timeafter:" << timeafter;
        QPropertyAnimation *absAni = qobject_cast<QPropertyAnimation*>(it->seqAnimation->animationAt(t));
        if (absAni != NULL){
            qDebug() << "absAni not null";
            absAni->setDuration(newtime-timebefor);
            absAni->setKeyValueAt(1,value);
            absAni->setEasingCurve(static_cast<QEasingCurve::Type>(type));
        }
        if (t != it->times.size()-1){
            QPropertyAnimation *absAni1 = qobject_cast<QPropertyAnimation*>(it->seqAnimation->animationAt(t+1));
            if (absAni1 != NULL){
                absAni1->setDuration(timeafter-newtime);
            }
        }
    }
}

QVariant SimpleTimeline::preview(QString name, qreal time)
{
    //根据串名找到串
    auto it = seqGroup.begin();
    int flag = 0;
    //判断是添加还是更新
    int state = -1;
    // 初始化位置为-1，表示未找到
    int ani_position = -1;
    // 根据名字从所有串中检索是否有串行动画组可用
    while (it != seqGroup.end()){
        if(it->seqGroupName == name)
        {
            flag = 1;
            break;
        }
        it++;
    }
    if (flag == 1)
    {
        for (int i = 0; i < it->times.size(); ++i)
        {
            if (time == it->times[i]){
                state = i;
            }
            if (time >= it->times[i]){
                ani_position = i;
            }
        }
    }else{
        qDebug() << "没有对应的串";
    }
    //在最后一帧的后边
    if(ani_position == it->times.size()-1){
        qDebug() << "此处还没有动画";
        QPoint p(1000,200);
        QVariant myVariant = QVariant::fromValue(p);
        return myVariant;
    }else if (state == -1){
        //不是关键帧，需要计算位置
        QVariant startsite;
        QVariant endsite;
        QPoint p;
        double progress;
        qDebug() << "this point isn't a keyframe.";
        //在第一帧前边，特殊处理
        if (ani_position == -1){
            startsite = QPoint(1000,200);
            QPropertyAnimation *absAni = qobject_cast<QPropertyAnimation*>(it->seqAnimation->animationAt(0));
            endsite = absAni->keyValueAt(1);
            qDebug() << "absAni->keyValueAt(1)" << absAni->keyValueAt(1);
            progress = time/it->times[0];
        }else{
            //在某两帧中间
            QPropertyAnimation *absAnibefor = qobject_cast<QPropertyAnimation*>(it->seqAnimation->animationAt(ani_position));
            QPropertyAnimation *absAniafter = qobject_cast<QPropertyAnimation*>(it->seqAnimation->animationAt(ani_position+1));
            startsite = absAnibefor->keyValueAt(1);
            endsite = absAniafter->keyValueAt(1);
            qDebug() << "absAnibefor->keyValueAt(1)" << absAnibefor->keyValueAt(1);
            qDebug() << "absAniafter->keyValueAt(1)" << absAniafter->keyValueAt(1);
            progress = (time - it->times[ani_position])/absAniafter->duration();
        }
        qDebug() << "progress:===============" << progress;
        float x = (1 - progress) * startsite.value<qreal>() + endsite.value<qreal>() * progress;
//        float y = (1 - progress) * startsite.value<QPoint>().y() + endsite.value<QPoint>().y() * progress;
        qDebug() << x;
//        qDebug() << startsite.value<QPoint>().y();
//        qDebug() << y;
        p.setX(x);
//        p.setY(y);
        QVariant myVariant = QVariant::fromValue(p);
        return myVariant;
    }else{
        qDebug() << "this point is a keyframe.";
        QPropertyAnimation *absAni = qobject_cast<QPropertyAnimation*>(it->seqAnimation->animationAt(state));
        return absAni->keyValueAt(1);
    }
}

void SimpleTimeline::addFrameButton(QObject *target, const QByteArray &propertyName, QString name, const QVariant &value, int type, qreal time)
{
    //根据串名找到串
    auto it = seqGroup.begin();
    int flag = 0;
    //判断是添加还是更新
    int state = -1;
    // 根据名字从所有串中检索是否有串行动画组可用
    while (it != seqGroup.end()){
        if(it->seqGroupName == name)
        {
            flag = 1;
            break;
        }
        it++;
    }
    if (flag == 1)
    {
        for (int i = 0; i < it->times.size(); ++i)
        {
            if(time == it->times[i]){
                state = i;
            }
        }
    }else{
        qDebug() << "没有对应的串";
    }

    if (state == -1){
        qDebug() << "add animation";
        addFrame(target, propertyName, name, value, type, time);
    }else{
        qDebug() << "update animation";
        updateFrame(name, value, type, time, time);
    }
}



void SimpleTimeline::start()
{
    parGroup.start();
}

void SimpleTimeline::stop()
{
    parGroup.stop();
}

void SimpleTimeline::setrecordstate(int state){
    recordstate = state;
    emit recordstateChanged(state);
}

int SimpleTimeline::getrecordstate(){
    return recordstate;
}

float SimpleTimeline::getxnum(){
    return xnum;
}

void SimpleTimeline::setxnum(float x){
    xnum = x;
//    qDebug() << "set xnum.";
//    emit xnumChanged();
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
        delete it->seqAnimation;  // 释放 QSequentialAnimationGroup
        seqGroup.erase(it++);
    }
    seqGroup.clear();  // 清空 map
}
