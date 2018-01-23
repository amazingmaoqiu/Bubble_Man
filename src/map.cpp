#include "map.h"
void Map::setMapState(int x, int y, int state)
{
	this->map[x][y] = state;
}

int Map::getPixel(int bitX, int bitY) const
{
	return this->map[bitX][bitY];
}


void Map::setBubbleMapRange(int x, int y, int range)
{
	bubbleMap[x][y].setRange(range);
}


int Map::getMapState(int x, int y) const
{
	return map[y][x];
}

/*void Map::Draw(void)
{
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			switch (map[i][j])
			{
			case 0:
				glBegin(GL_QUADS);
				glColor3ub(255, 255, 255);

				glVertex2i(j * 50, i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				break;
			case 1:
				glBegin(GL_QUADS);
				glColor3ub(255, 0, 0);

				glVertex2i(j * 50, i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				break;
			case 2:
				glBegin(GL_QUADS);
				glColor3ub(0, 0, 0);

				glVertex2i(j * 50, i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				break;
			case 3:
				glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);

				glVertex2i(j * 50, i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				break;
			case 4:
				glBegin(GL_QUADS);
				glColor3ub(0,0,255);

				glVertex2i(j * 50, i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				break;
			}
		}
	}
}*/

void Map::setBubbleMap(int x, int y, int state, int range, int layTime, int playerID)
{
	this->bubbleMap[x][y].setRange(range);
	this->bubbleMap[x][y].setBlowTime0();
	this->bubbleMap[x][y].reset(state, playerID, x, y, layTime);
}


/*void Map::setBubbleRange(const int x, const int y, const int range)
{
	this->bubbleMap[x][y].setRange(range);
}*/

int Map::getRange(int x, int y) const
{
	return bubbleMap[x][y].getRange();
}

int Map::getBubbleMapState(int x, int y) const
{
	return bubbleMap[x][y].getSate();
}

int Map::checkBubbleTime(int x, int y) const
{
	return bubbleMap[x][y].checkTime();
}

void Map::setBlowTime(int x, int y)
{
	bubbleMap[x][y].tictoc();
}


void Map::adjacentExplode(int x, int y, int range, int left, int right, int up, int down, int& num1, int& num2) //recursion
	{
		//base case:
		num1 = 0;
		num2 = 0;
		    if(range < 1) return;
			if (x <= 0 || x >= 14 || y <= 0 || y >= 14) 
			{
				return;
			}
			int count = 1;
			while(count <= range && (x+count)<=14 && left == 1)
			{
				if(bubbleMap[x+count][y].getSate() == 1)   //向右侧查找
			    {
				    adjacentExplode(x+count,y,bubbleMap[x+count][y].getRange(),1,0,1,1,num1,num2);
				    map[x+count][y] = 3;
					//11/19 hesongl
					//toolmap[x + count][y] = 0;

					/*if(bubbleMap[x+count][y].getPlayerID() == 1)
					{
						num1++;
					}
					else if(bubbleMap[x+count][y].getPlayerID() == 2)
					{
						num2++;
					}*/
					//bubbleMap[x+count][y].setState(0);
				    
					
					break;
			    }
			    if(map[x+count][y] == 1 || map[x+count][y] == 4)
			    {
			    	map[x+count][y] = 3;
			    	break;
			    }
				if(map[x+count][y] == 2 || map[x+count][y] == 3)
				{
					break;
				}
			    map[x+count][y] = 3;
				//11/19 hesongl
				toolmap[x + count][y] = 0;
				count++;
			}
			count = 1;
			while(count <= range && (x - count) >= 0 && right == 1)
			{
				if(bubbleMap[x-count][y].getSate() == 1)   //向右侧查找
			    {
				    adjacentExplode(x-count,y,bubbleMap[x-count][y].getRange(),0,1,1,1,num1,num2);
				    map[x-count][y] = 3;
					//11/19 hesongl
					//toolmap[x + count][y] = 0;

					//bubbleMap[x-count][y].setState(0);
					/*if(bubbleMap[x-count][y].getPlayerID() == 1)
					{
						num1++;
					}
					else if(bubbleMap[x-count][y].getPlayerID() == 2)
					{
						num2++;
					}*/


				    break;
			    }
			    if(map[x-count][y] == 1 || map[x-count][y] == 4)
			    {
					if(toolmap[x-count][y] != 0)
					{
						int a = 0;
					}
			    	map[x-count][y] = 3;
					//11/19 hesongl
					//toolmap[x + count][y] = 0;
			    	break;
			    }
				if(map[x - count][y] == 2 || map[x - count][y] == 3)
				{
					break;
				}
			    map[x-count][y] = 3;
				//11/19 hesongl
				toolmap[x - count][y] = 0;
				count++;
			}
			count = 1;
			while(count <= range && (y + count) <= 14 && up == 1)
			{
				if(bubbleMap[x][y+count].getSate() == 1)   //向xia侧查找
			    {
				    adjacentExplode(x,y+count,bubbleMap[x][y+count].getRange(),1,1,1,0,num1,num2);
				    map[x][y+count] = 3;
					//11/19 hesongl
					//toolmap[x + count][y] = 0;

					//bubbleMap[x][y+count].setState(0);
					/*if(bubbleMap[x][y+count].getPlayerID() == 1)
					{
						num1++;
					}
					else if(bubbleMap[x][y+count].getPlayerID() == 2)
					{
						num2++;
					}*/

				    break;
			    }
			    if(map[x][y+count] == 1 || map[x][y+count] == 4)
			    {
					if(toolmap[x][y+count] != 0)
					{
						int a = 0;
					}
			    	map[x][y+count] = 3;
					//11/19 hesongl
					//toolmap[x + count][y] = 0;
			    	break;
			    }
				if(map[x][y + count] == 2 || map[x][y + count] == 3)
				{
					break;
				}
			    map[x][y+count] = 3;
				//11/19 hesongl
				toolmap[x][y + count] = 0;
				count++;
			}
			count = 1;
			while(count <= range && (y - count) >= 0 && down == 1)
			{
				if(bubbleMap[x][y-count].getSate() == 1)   //向up侧查找
			    {
					adjacentExplode(x,y-count,bubbleMap[x][y-count].getRange(),1,1,0,1,num1,num2);
				    map[x][y-count] = 3;
					//11/19 hesongl
					//toolmap[x + count][y] = 0;

					//bubbleMap[x][y-count].setState(0);
					/*if(bubbleMap[x][y-count].getPlayerID() == 1)
					{
						num1++;
					}
					else if(bubbleMap[x][y-count].getPlayerID() == 2)
					{
						num2++;
					}*/

				    break;
			    }
			    if(map[x][y-count] == 1 || map[x][y-count] == 4)
			    {
					if(toolmap[x][y-count] != 0)
					{
						int a = 0;
					}
			    	map[x][y-count] = 3;
					//11/19 hesongl
					//toolmap[x + count][y] = 0;
			    	break;
			    }
				if(map[x][y - count] == 2 || map[x][y - count] == 3)
				{
					break;
				}
			    map[x][y-count] = 3;
				//11/19 hesongl
				toolmap[x][y - count] = 0;
				count++;
			}
			if(bubbleMap[x][y].getPlayerID() == 1)
			{
				num1++;
			}
			if(bubbleMap[x][y].getPlayerID() == 2)
			{
				num2++;
			}
			//bubbleMap[x][y].setState(0);
			return;
	}



int Map::getID(int x, int y)
{
	return bubbleMap[x][y].getPlayerID();
}









void Map::drawTool(int x, int y)
{
	if (getMapState(y, x) == 0 && getToolMapState(x, y) != 0)
	{
		int state = getToolMapState(x, y);  
		int r[4] = {0,255,255,200};
		int g[4] = {255,255,0,50 };
		int b[4] = {0,100,255,0 };
		glBegin(GL_QUADS);
		glColor3ub(r[state-1], g[state-1], b[state-1]);

		glVertex2i(y * 50, x * 50);
		glVertex2i((y + 1) * 50, x * 50);
		glVertex2i((y + 1) * 50, (x + 1) * 50);
		glVertex2i(y * 50, (x + 1) * 50);

		glEnd();
		printf("%d\n", state);
	}
}


int Map::getToolMapState(int bitx, int bity)
{
	return toolmap[bitx][bity];
}


void Map::setToolState(int x, int y, int state)
{
	toolmap[x][y] = state;
}

void Map::Draw(void)
{
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			// 11/23 Chen Hu, the underneath pic is the ground, no matter what the upper pic is
			glRasterPos2d(j * 50, (i + 1) * 50);
			glDrawPixels(MyPng[0].wid, MyPng[0].hei, GL_RGBA, GL_UNSIGNED_BYTE, MyPng[0].rgba);

			switch (map[i][j])
			{
			case 0:
				if (toolmap[i][j] != 0)
				{
					drawTool(i, j);
				}
				else
				{
					/*
					glBegin(GL_QUADS);
					glColor3ub(255, 255, 255);

					glVertex2i(j * 50, i * 50);
					glVertex2i((j + 1) * 50, i * 50);
					glVertex2i((j + 1) * 50, (i + 1) * 50);
					glVertex2i(j * 50, (i + 1) * 50);

					glEnd();*/
				}
				break;
			case 1:
				glRasterPos2d(j * 50, (i + 1) * 50);
				glDrawPixels(MyPng[1].wid, MyPng[1].hei, GL_RGBA, GL_UNSIGNED_BYTE, MyPng[1].rgba);

				/*
				glBegin(GL_QUADS);
				glColor3ub(255, 0, 0);

				glVertex2i(j * 50,  i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				*/
				break;
			case 2:
				glRasterPos2d(j * 50, (i + 1) * 50 - 1);
				glDrawPixels(MyPng[2].wid, MyPng[2].hei, GL_RGBA, GL_UNSIGNED_BYTE, MyPng[2].rgba);

				/*
				glBegin(GL_QUADS);
				glColor3ub(0, 0, 0);

				glVertex2i(j * 50, i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				*/
				break;
			case 3:
				glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);

				glVertex2i(j * 50, i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				break;
			case 4:
				// Enable blending
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glRasterPos2d(j * 50, (i + 1) * 50 - 1);
				glDrawPixels(MyPng[4].wid, MyPng[4].hei, GL_RGBA, GL_UNSIGNED_BYTE, MyPng[4].rgba);

				/*
				glBegin(GL_QUADS);
				glColor3ub(0,0,255);

				glVertex2i(j * 50, i * 50);
				glVertex2i((j + 1) * 50, i * 50);
				glVertex2i((j + 1) * 50, (i + 1) * 50);
				glVertex2i(j * 50, (i + 1) * 50);

				glEnd();
				*/
				break;
			}
		}
	}
}