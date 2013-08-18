#include "RoundStats.h"

RoundStats::RoundStats(int round, int maxDucks)
{
	hitsToAdvance_=5+round*0.25; //fairly good
	if(hitsToAdvance_>maxDucks)
	{
		hitsToAdvance_=maxDucks;
	}
	speed_=140+10*round*round; //either linear or exponential (maybe fine for now?)
	flyAwayTime_=4;
	scoreMultiplicator_=0.9+0.1*round;
}

int RoundStats::getHitsToAdvance()
{
	return hitsToAdvance_;
}

float RoundStats::getSpeed()
{
	return speed_;
}

float RoundStats::getFlyAwayTime()
{
	return flyAwayTime_;
}

float RoundStats::getScoreMultiplicator()
{
	return scoreMultiplicator_;
}

void RoundStats::printOut()
{
	cout << "hitsToAdvance_: " << hitsToAdvance_ << endl;
	cout << "speed_: " << speed_ << endl;
	cout << "flyAwayTime_: " << flyAwayTime_ << endl;
	cout << "scoreMultiplicator_: " << scoreMultiplicator_ << endl;
}