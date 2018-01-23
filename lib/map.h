#include <vector>
#include <string>
#include "fssimplewindow.h"
// added 11/23 Chen Hu
#include "yspng.h"

#ifndef is_included_bubble
#include "bubble.h"
#endif

#define isFloor 0;
#define isBox 1;
#define isObstacle 2;
#define inExplosion 3;
#define isBubble 4;
#define isPlayer 5;


#ifndef MAP_IS_INCLUDED
#define MAP_IS_INCLUDED
class Map
{
protected:
	//enum map_state {floor = 0, box = 1, obstacle = 2, isWithinExposedZone=3, hasBubble=4, player = 5};
	Bubble bubbleMap[15][15];
	//map_state map[15][15];
	int map[15][15];
    //to be implemented...



	int toolmap[15][15];
	//added 11/23 Chen Hu Background pics
	//MyPng[0]: ground; MyPng[1]: box; MyPng[2]: obstacle; MyPng[3]: bubble around player(no use); MyPng[4]: bubble
	YsRawPngDecoder *MyPng;


public:
		Map()
	{
		for (int i = 0; i < 15; i++) 
		{
			for (int j = 0; j < 15; j++)
			{
				Bubble tempb(0,i,j);
				bubbleMap[i][j] = tempb;
				//map[i][j] = 0;
			}
		}
		//added 11/19
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				toolmap[i][j] = 0;
			}
		}
		//added 11/23 Chen Hu, initialize background pics
		MyPng = NULL;
		MyPng = new YsRawPngDecoder[5];
		if (YSOK == MyPng[0].Decode("ground.png"))
		{
			printf("Read ground Width=%d Height=%d\n", MyPng[0].wid, MyPng[0].hei);
			MyPng[0].Flip();
		}
		else printf("Read obs Error!\n");
		if (YSOK == MyPng[1].Decode("box.png"))
		{
			printf("Read box Width=%d Height=%d\n", MyPng[1].wid, MyPng[1].hei);
			MyPng[1].Flip();
		}
		else printf("Read box Error!\n");
		if (YSOK == MyPng[2].Decode("obs.png"))
		{
			printf("Read obs Width=%d Height=%d\n", MyPng[2].wid, MyPng[2].hei);
			MyPng[2].Flip();
		}
		else printf("Read obs Error!\n");
		if (YSOK == MyPng[3].Decode("around.png"))
		{
			printf("Read around Width=%d Height=%d\n", MyPng[3].wid, MyPng[3].hei);
			MyPng[3].Flip();
		}
		else printf("Read around Error!\n");
		if (YSOK == MyPng[4].Decode("bub.png"))
		{
			printf("Read bub Width=%d Height=%d\n", MyPng[4].wid, MyPng[4].hei);
			MyPng[4].Flip();
		}
		else printf("Read bub Error!\n");
	}
	//11/19 hesongl setToolState
	void setToolState(int x, int y, int state);

	/*Map(std::string fileName)
	{
		//...load file, remaining to be completed
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				bubbleMap[i][j] = new Bubble(0,0,i,j,0); // just set state
			}
		}
	}*/
	void setPixel();
	void setBubbleMap(int x, int y, int state, int range, int layTime, int playerID);
	//void setBubbleRange(const int x, const int y, const int range);
	int  getPixel(int bitX, int bitY) const;
	int getID(int x, int y);
	void Draw();
	//check whether the current bit map zone is exposed or not
	void setMapState(int x, int y, int state);
	void setBubbleMapRange(int x, int y, int range);
	void checkExposeTime(); // traverse row and col
	void adjacentExplode(int x, int y, int range, int left, int right, int up, int down, int& num1, int& num2);//recursion
    int getMapState(int i, int j) const;
	int getBubbleMapState(int i, int j) const;
	int checkBubbleTime(int x, int y) const;
	int getRange(int x, int y) const;
	void setBlowTime(int x, int y);



	int getToolMapState(int bitx, int bity);
	void drawTool(int x, int y);
};
#endif