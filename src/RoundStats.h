#ifndef ROUNDSTATS
#define ROUNDSTATS

#include <iostream>
using namespace std;

class RoundStats
{
public:
	RoundStats(int round, int maxDucks);
	int getHitsToAdvance();
	float getSpeed();
	float getFlyAwayTime();
	float getScoreMultiplicator();
	void printOut();
private:
	int hitsToAdvance_;
	float speed_;
	float flyAwayTime_;
	float scoreMultiplicator_;
};

#endif