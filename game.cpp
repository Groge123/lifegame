#include "game.h"

Init::Init()
{
	memset(this->map, 0, sizeof(this->map));
	memset(this->Num, 0, sizeof(this->Num));
	memset(this->Add, -1, sizeof(this->Add));
	memset(this->Delete, -1, sizeof(this->Delete));

	initgraph(WIDTH, HEIGHT, 1);
	setbkcolor(RGB(37, 137, 103));
	cleardevice();
	
	setfillcolor(WHITE);

}

void Game::Eraser(int x, int y)
{
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			this->StatsNum(x + i, y + i,-1);
			
			this->map[x + i][y + j] = 0;
			
		}
	}
}

void Game::MouseOp()
{
	
	ExMessage msg;
	while (peekmessage(&msg, EM_MOUSE))
	{
		int x = msg.x/10;
		int y = msg.y/10;
		if (msg.message == WM_LBUTTONDOWN)
		{
			cout << this->Num[x][y] << "   " <<x<<"  " << y << endl;
			//this->UpdateGame();
			this->flag = 1;
		}
		if (msg.message == WM_MOUSEMOVE&&this->flag==1)
		{
			//cout << "×ó¼üÒÆ¶¯" << endl;
			if(this->map[x][y]==0) this->StatsNum(x,y,1);
			
			this->map[x][y] = 1;
			
			this->PaintGame();
		}
		if (msg.message == WM_LBUTTONUP)
		{
			
			this->flag = 0;
		}
		if (msg.message == WM_RBUTTONDOWN)
		{
			this->flag = -1;
		}
		if (msg.message == WM_MOUSEMOVE && this->flag == -1)
		{
			this->Eraser(x, y);
			//cout << "ÓÒ¼üÒÆ¶¯" << endl;
			PaintGame();
		}
		if (msg.message == WM_RBUTTONUP)
		{
			this->flag = 0;
			
		}
		if (msg.shift)
		{
			begin =(begin+1)%2;
		}
	}
}

void Game::BeginE()
{
	if (this->begin == 1) this->UpdateGame();
}

void Game::Line()
{
	for (int i = 0; i <= WIDTH; i += 10)
	{
		line(i, 0, i, HEIGHT);
	}
	for (int i = 0; i <= HEIGHT; i += 10)
	{
		line(0, i, WIDTH, i);
	}
}

void Game::StatsNum(int x,int y,int flag)
{
	int m = 0;
	cout << "stas=" << this->Num[x - 1][y] << " " << x - 1 << " " << y << endl;
	for (int i = -1; i <= 1; i++)
	{
		if (x + i >= 0 && x + i < WIDTH/10)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (y + j >= 0 && y + j < HEIGHT/10)
				{
					if (i == 0 && j == 0) continue;
					else
					{
						
						if (flag == 1)
						{
							this->Num[x + i][y + j] += 1;
							cout <<  "breakrupt" << endl;
						}
						else if (flag == -1)
						{
							cout << "came in" <<++m<< endl;
							if (this->Num[x + i][y + j])
							{
								this->Num[x + i][y + j] -= 1;
								cout << "cao" << endl;
							}
						}
					}
				}
			}
		}
	}
	/*this->UpdateGame();*/
}

void Game::UpdateGame()
{
	int x = 0;
	int y = 0;
	int num = 0;
	for (int i = 0; i < WIDTH/10; i++)
	{
		for (int j = 0; j < HEIGHT/10; j++)
		{
			num += this->Num[i][j];
			/*cout << this->Num[i][j] << "   " << i << "  " << j <<"all" << endl;*/
			if (this->Num[i][j] == 2)
			{
				cout << this->Num[i][j] << "   " << i << "  " << j << endl;
				
				continue;
			}
			else if (this->Num[i][j] == 3)
			{
				if (this->map[i][j] == 0)
				{
					cout << "add::" << this->Num[i][j] << "   " << i << "  " << j << "all" << endl;

					this->Add[x++] = i;
					this->Add[x++] = j;
					//cout << "x1=" <<this->Add[0] << endl;
				}
				
				cout << this->Num[i][j] << "   " << i << "  " << j << endl;
				this->map[i][j] = 1;
			}
			else
			{
				if (this->map[i][j] == 1)
				{
					cout << "delete::"<<this->Num[i][j] << "   " << i << "  " << j << "all" << endl;
					this->Delete[y++] = i;
					this->Delete[y++] = j;
					//cout << "y1=" << this->Delete[1] << endl;

					/*cout << Delete[y-1]<<j << endl;*/
				}
				this->map[i][j] = 0;
			}
			
		}
	}
	cout << "all="<<num << endl;
	

	this->Mod();
	this->PaintGame();
	Sleep(20);
}

void Game::Mod()
{
	int x = 0, y = 0;
	
	//cout << "x=" << this->Delete[0] << endl;
	while (this->Add[x]!=-1)
	{
		this->StatsNum(this->Add[x], this->Add[x+1], 1);
		x += 2;
		cout << "mod add" << this->Add[x - 2] << "   " << this->Add[x - 1] << endl;
		//cout << "x=" << x << endl;
	}
	while (this->Delete[y]!=-1)
	{	
		cout << "mod delete" << this->Delete[y ] << "   " << this->Delete[y+1] << endl;
		this->StatsNum(this->Delete[y], this->Delete[y+1], -1);
		y += 2;
		

		}

	memset(this->Add, -1, sizeof(this->Add));
	memset(this->Delete, -1, sizeof(this->Delete));
}


void Game::PaintGame()
{
	
	cleardevice();
	BeginBatchDraw();
	
	for (int i = 0; i < WIDTH/10; i++)
	{
		for (int j = 0; j < HEIGHT/10; j++)
		{
			if (this->map[i][j] == 1)
			{
				solidrectangle(i*10, j*10,i*10+10,j*10+10);
			}
			
		}
	}
	this->Line();
	EndBatchDraw();
}