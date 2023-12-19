#ifndef MYANIMATIONGROUP_H
#define MYANIMATIONGROUP_H

#include <QObject>
#include <QSequentialAnimationGroup>
#include <vector>

class MyAnimationGroup
{

public:
    QSequentialAnimationGroup *seqAnimation; //串



    MyAnimationGroup(QSequentialAnimationGroup *SeqAnimation,std::vector<int> Times,QString SeqGroupName);
    ~MyAnimationGroup();

    QString seqGroupName;
    std::vector<int> times;
};
#endif // MYANIMATIONGROUP_H
