#include "bubble.h"

int Bubble::getBlowTime()
{
	return blowTime;
}

void Bubble::tictoc()
{
	blowTime++;
}

int Bubble::checkTime() const
{
	if(blowTime >= layTime)
	{
		return 1;
	}
	return 0;
}

void Bubble::setBitX(int x)
{
	this->bitx = x;
}

void Bubble::setBitY(int y)
{
	this->bity = y;
}

int Bubble::getBitX() const
{
	return this->bitx;
}

int Bubble::getBitY() const
{
	return this->bity;
}

void Bubble::setState(int state)
{
	this->state = state;
}

void Bubble::setRange(const int r)
{
	this->range = r;
}

Bubble::Bubble(int state, int pId, int xzone, int yzone, int lTime)
{
	this->state = state;
	this->playId = pId;
	this->setBitX(xzone);
	this->setBitY(yzone);
	this->layTime = lTime;
	this->blowTime = 0;
	this->range = 3;
	firstTime = 1;
}
void Bubble::setBlowTime0()
{
	blowTime = 0;
}

void Bubble::setLayTime(int layTime)
{
	this->layTime = layTime;
}

/*void Bubble::setRange(int r)
{
	this->range = r;
}*/


void Bubble::reset(int state, int pId, int xzone, int yzone, int lTime)
{
	this->state = state;
	this->playId = pId;
	this->setBitX(xzone);
	this->setBitY(yzone);
	this->layTime = lTime;
	this->blowTime = 0;
	//this->range = 3;
	this->firstTime = 1;
}

void Bubble::increaseRange()
{
	range++;
}

int Bubble::getPlayerID()
{
	return playId;
}

int Bubble::getRange() const
{
	return range;
}


int Bubble::getSate() const
{
	return state;
}