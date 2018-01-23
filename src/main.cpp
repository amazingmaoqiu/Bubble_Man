#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <queue>
#include <time.h>
#include "map.h"
#include "Player.h"
#include "bubble.h"
#include "yssimplesound.h"

#define isFloor 0;
#define isBox 1;
#define isObstacle 2;
#define inExplosion 3;
#define isBubble 4;
#define isPlayer 5;

using namespace std;

int main(void)
{
	srand(time(nullptr));
	Map background;
	Player p1(75, 100, 3, 7);
	Player p2(675, 700, 3, 7);
	Bubble player1_bubble(0, 1, p1.getY()/50, p1.getX()/50, 50);
	Bubble player2_bubble(0, 2, p2.getY()/50, p2.getX()/50, 50);
	priority_queue<Bubble, vector<Bubble>, cmp> bubbleQueue;
	vector<Bubble> bubbleVector;
	int num1(0), num2(0);
	char BitMap[] = {
		"222222222222222"
		"200011101110002"
		"202121222121202"
		"111100000001111"
		"212021121120212"
		"111011212110111"
		"202010222010202"
		"202010222010202"
		"202010222010202"
		"111011212110111"
		"212021121120212"
		"111100000001111"
		"202121222121202"
		"200011101110002"
		"222222222222222" };

	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			switch (BitMap[i * 15 + j])
			{
			case '0':
				background.setMapState(i, j, 0);
				break;
			case '1':
				background.setMapState(i, j, 1);
				break;
			case '2':
				background.setMapState(i, j, 2);
				break;
			}
			//printf("%d ", background.getMapState());
		}
		printf("\n");
	}

		//11/19 hesongl temporarily set some tools for mapstate = 1
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if (background.getMapState(i,j) == 1)
			{
				int state = rand() % 5; // 1: life 2: numbubble 3: speed 4:range 0: no state
				//int state = 1;
				background.setToolState(j, i, state);
				if (state != 0)
				{
					cout << "tool on (" << i << "," << j << ") is : state" << endl;
				}
			}
		}
		printf("\n");
	}

	YsSoundPlayer player;
	//	FsChangeToProgramDir();
	player.MakeCurrent();
	player.Start();
	FsChangeToProgramDir();

	YsSoundPlayer::SoundData bgm;
	YsSoundPlayer::SoundData explode;
	YsSoundPlayer::SoundData death;

	if (YSOK != bgm.LoadWav("BGM.wav"))
	{
		printf("Error! Cannot load BGM.wav!\n");
	}
	else
	{
		printf("The BGM is successfully loaded!\n");
	}

	if (YSOK != explode.LoadWav("explode.wav"))
	{
		printf("Error! Cannot load explode.wav!\n");
	}
	else
	{
		printf("The explosion sound is successfully loaded!\n");
	}

	if (YSOK != death.LoadWav("death.wav"))
	{
		printf("Error! Cannot load death.wav!\n");
	}
	else
	{
		printf("The death sound is successfully loaded!\n");
	}


	int P1Flag1 = 0, P1Flag2 = 0, P1Flag3 = 0, P1Flag4 = 0;
	int P2Flag1 = 0, P2Flag2 = 0, P2Flag3 = 0, P2Flag4 = 0;
	FsOpenWindow(16, 16, 750, 750, 1);
	for (;;)
	{
		num1 = 0;
		num2 = 0;
		int direc = 0;

		FsPollDevice();
		player.PlayBackground(bgm);

		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}

		//ensure p1 p2 will not be trapped in the bubble
		p1.CheckInBubble(background);
		p2.CheckInBubble(background);

		//move of player 1
		if (0 == p1.getState())
		{
			if (0 != FsGetKeyState(FSKEY_UP) && 0 == P1Flag2 && 0 == P1Flag3 && 0 == P1Flag4)
			{
				P1Flag1 = 1;
				direc = 1;
				p1.move(direc, background);
				if (p1.getTool(background))
				{
					player1_bubble.increaseRange();
				}
			}
			if (0 != FsGetKeyState(FSKEY_LEFT) && 0 == P1Flag1 && 0 == P1Flag3 && 0 == P1Flag4)
			{
				P1Flag2 = 1;
				direc = 2;
				p1.move(direc, background);
				if (p1.getTool(background))
				{
					player1_bubble.increaseRange();
				}
			}
			if (0 != FsGetKeyState(FSKEY_DOWN) && 0 == P1Flag1 && 0 == P1Flag2 && 0 == P1Flag4)
			{
				P1Flag3 = 1;
				direc = 3;
				p1.move(direc, background);
				if (p1.getTool(background))
				{
					player1_bubble.increaseRange();
				}
			}
			if (0 != FsGetKeyState(FSKEY_RIGHT) && 0 == P1Flag1 && 0 == P1Flag2 && 0 == P1Flag3)
			{
				P1Flag4 = 1;
				direc = 4;
				p1.move(direc, background);
				if (p1.getTool(background))
				{
					player1_bubble.increaseRange();
				}
			}

			if (0 == FsGetKeyState(FSKEY_UP) && 1 == P1Flag1)
			{
				P1Flag1 = 0;
			}
			if (0 == FsGetKeyState(FSKEY_LEFT) && 1 == P1Flag2)
			{
				P1Flag2 = 0;
			}
			if (0 == FsGetKeyState(FSKEY_DOWN) && 1 == P1Flag3)
			{
				P1Flag3 = 0;
			}
			if (0 == FsGetKeyState(FSKEY_RIGHT) && 1 == P1Flag4)
			{
				P1Flag4 = 0;
			}

			if (key == FSKEY_SPACE && background.getBubbleMapState(p1.getY() / 50, p1.getX() / 50) != 1)
			{
				if (p1.getBubbleNum() > 0)
				{
					p1.layBubble(background, player1_bubble.getRange());
					//player1_bubble.reset(0, 1, p1.getX()/50, p1.getY()/50, 100);
					//p1.layBubble(background); 
					background.setBubbleMap(p1.getY() / 50, p1.getX() / 50, 1, player1_bubble.getRange(), 100, 1);
					//bubbleVector.push_back(player1_bubble);
				}
			}
		}



		//move of player 2
		if (0 == p2.getState())
		{
			if (0 != FsGetKeyState(FSKEY_W) && 0 == P2Flag2 && 0 == P2Flag3 && 0 == P2Flag4)
			{
				P2Flag1 = 1;
				direc = 1;
				p2.move(direc, background);
				p2.getTool(background);
			}
			if (0 != FsGetKeyState(FSKEY_A) && 0 == P2Flag1 && 0 == P2Flag3 && 0 == P2Flag4)
			{
				P2Flag2 = 1;
				direc = 2;
				p2.move(direc, background);
				p2.getTool(background);
			}
			if (0 != FsGetKeyState(FSKEY_S) && 0 == P2Flag1 && 0 == P2Flag2 && 0 == P2Flag4)
			{
				P2Flag3 = 1;
				direc = 3;
				p2.move(direc, background);
				p2.getTool(background);
			}
			if (0 != FsGetKeyState(FSKEY_D) && 0 == P2Flag1 && 0 == P2Flag2 && 0 == P2Flag3)
			{
				P2Flag4 = 1;
				direc = 4;
				p2.move(direc, background);
				p2.getTool(background);
			}

			if (0 == FsGetKeyState(FSKEY_W) && 1 == P2Flag1)
			{
				P2Flag1 = 0;
			}
			if (0 == FsGetKeyState(FSKEY_A) && 1 == P2Flag2)
			{
				P2Flag2 = 0;
			}
			if (0 == FsGetKeyState(FSKEY_S) && 1 == P2Flag3)
			{
				P2Flag3 = 0;
			}
			if (0 == FsGetKeyState(FSKEY_D) && 1 == P2Flag4)
			{
				P2Flag4 = 0;
			}

			if (key == FSKEY_ENTER && background.getBubbleMapState(p2.getY() / 50, p2.getX() / 50) != 1)
			{
				if (p2.getBubbleNum() > 0)
				{
					p2.layBubble(background, player1_bubble.getRange());
					//player2_bubble.reset(0, 2, p2.getX()/50, p2.getY()/50, 100);
					//p2.layBubble(background); 
					//background.setBubbleRange(p2.getX()/50, p2.getY()/50,player1_bubble.getRange());
					//background.setBubbleMap(p2.getY()/50, p2.getX()/50,1, player2_bubble.getRange());
					background.setBubbleMap(p2.getY() / 50, p2.getX() / 50, 1, player1_bubble.getRange(), 100, 2);
					//bubbleVector.push_back(player2_bubble);
				}
			}
		}


		/*for(int i=0;i<bubbleVector.size();++i)
		{
			bubbleVector[i].tictoc();
			if(bubbleVector[i].checkTime())
			{
				background.setMapState(bubbleVector[i].getBitY(),bubbleVector[i].getBitX(),3);
				background.adjacentExplode(bubbleVector[i].getBitY(), bubbleVector[i].getBitX(), bubbleVector[i].getRange());
				bubbleVector.erase(bubbleVector.begin() + i);
			}
		}*/

		for(int i=0;i<15;++i)
		{
			for(int j=0;j<15;++j)
			{
				background.setBlowTime(i,j);
				if(background.getBubbleMapState(i,j) == 1 && background.checkBubbleTime(i,j) == true)
				{
					background.setMapState(i,j,3);
					background.adjacentExplode(i, j, background.getRange(i,j),1,1,1,1, num1, num2);
					/*if(background.getID(i,j) == 1)
					{
						p1.plusNum();
					}
					else if(background.getID(i,j) == 2)
					{
						p2.plusNum();
					}*/
					background.setBubbleMap(i,j,0,3,100,0);
					player.PlayOneShot(explode);
					//background.adjacentExplode(i, j, background.getRange(i,j),1,1,1,1);
				}
			}
		}
		p1.plusNum(num1++);
		p2.plusNum(num2++);

		if (1 == p1.CheckInZone(background))
		{
			player.PlayOneShot(death);
		}
		else if (1 == p2.CheckInZone(background))
		{
			player.PlayOneShot(death);
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		background.Draw();
		p1.Draw();
		p2.Draw();
		FsSwapBuffers();
		FsSleep(15);

		for(int i=0;i<15;++i)
		{
			for(int j=0;j<15;++j)
			{
				if(background.getMapState(i,j) == 3)
				{
					background.setMapState(j,i,0);
					background.setBubbleMap(j,i,0,3,100,0);
				}
			}
		}

		if (1 == p1.CheckInZone(background))
		{
			player.PlayOneShot(death);
		}
		else if (1 == p2.CheckInZone(background))
		{
			player.PlayOneShot(death);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		background.Draw();
		p1.Draw();
		p2.Draw();

		player.KeepPlaying();
		FsSwapBuffers();
		FsSleep(5);
	}

	return 0;
}