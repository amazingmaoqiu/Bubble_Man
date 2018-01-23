#ifndef is_included_bubble
#define is_included_bubble
class Bubble
{
protected:
	int playId;
	int range;
	int bitx, bity;
	int blowTime;
	int layTime;
	int state; //0: inactive, 1 avtive
	int firstTime;
	int PlayerIn;

public:
	Bubble() { bitx = 0; bity = 0; int state = 0; int PlayerIn = 0; };
	Bubble(int state, int pId, int xzone, int yzone, int lTime);
	void reset(int state, int pId, int xzone, int yzone, int lTime);
	Bubble(int state, int xzone, int yzone)
	{
		this->state = state;
		this->bitx = xzone;
		this->bity = yzone;
	}

	Bubble(const Bubble& other)
	{
		state = other.state;
		playId = other.playId;
		bitx = other.bitx;
		bity = other.bity;
		//layTime = other.blowTime;
		range = other.range;
		blowTime = other.blowTime;
		layTime  = other.layTime;
	}
	void expose();
	int checkTime() const;
	void setBitX(int x);
	void setBitY(int y);
	void setState(int state);
	void setLayTime(int layTime);
	void setBlowTime0();
	int getBitX() const;
	int getBitY() const;
	void increaseRange();
	int getRange() const;
	int getSate() const;
	int getBlowTime();
	int getPlayerID();
	void setRange(const int r);
	void tictoc();
	~Bubble(){};
	const Bubble& operator=(const Bubble& other)
	{
		state = other.state;
		playId = other.playId;
		bitx = other.bitx;
		bity = other.bity;
		layTime = other.layTime;
		range = other.range;
		blowTime = other.blowTime;
		return *this;
	}
};


struct cmp
{
	bool operator() (Bubble b1, Bubble b2)
	{
		return b1.getBlowTime() > b2.getBlowTime();
	}
};

#endif