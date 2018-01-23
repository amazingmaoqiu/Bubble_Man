#include <vector>
#include "tool.h"
#include <math.h>
#include <unordered_map>
#include <string>
#include "fssimplewindow.h"


#ifndef MAP_IS_INCLUDED
#include "map.h"
#endif
typedef std::unordered_map<std::string,int> stringmap;

class Player
{
protected:
	int BubbleNum, fund_BubbleNum;
	//std::vector<Bubble> bubbles;
	//Bubble myBubble;
	//std::vector<Tool> tools;
	int fund_life,life;
	int trapTime;  //
	int state; //0：ishealthy, 1:trapped 2:dead
	int x,y;
	int v, fund_v;
	bool isInBubble;
	stringmap tool;
	// int id;
	int OnceInBubble;
public:
	Player(int px, int py, int num, int vel );
	void incVelocity();
	void decVelocity();
	void incBubbleNum();
	void addTool(int toolType);
	void update();
	void layBubble(Map &map, int range);
	int getX() const;
	int getY() const;
	void plusNum(int num);
	int getBubbleNum() const;
	void setState(int state);
	int getState() const;
	void countTrapTime();
	void move(int direction, Map bitMap);
	void Draw();
	int Hit(Map bitMap);
	bool getTool(Map &map);
	//judge which zone is the person 

	int CheckInZone(Map &map);	//check whether the player is in the range of the explosion
	void CheckInBubble(Map bitMap);	//check whether the player is in the bubble 11/19 yuyang
};
