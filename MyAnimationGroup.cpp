#include "MyAnimationGroup.h"

MyAnimationGroup::MyAnimationGroup(QSequentialAnimationGroup *SeqAnimation,std::vector<int> Times,QString SeqGroupName)
{
    seqAnimation = SeqAnimation;
    times = Times;
    seqGroupName = SeqGroupName;
};

MyAnimationGroup::~MyAnimationGroup(){

}
