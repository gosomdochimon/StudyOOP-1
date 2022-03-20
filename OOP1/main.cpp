// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#define _CRT_SECURE_NO_WARNINGS
//
#include <Windows.h>
#include <conio.h>
#include <string>
#include <ctime>

#define Random() srand((unsigned)time(NULL))

const int maxCount = 80;
struct Bullet;
struct Enemy;



struct Player{
	int pos;
	char shape[20];

	bool bIsRight = false;

	Player(const char* shape, int pos)
	{
		Random();
		strcpy(this->shape, shape);
		this->pos = rand() % (maxCount - strlen(this->shape));
	}

	bool IsInCanvas(int maxCount)
	{
 		return (this->pos >= 0 && this->pos <= (maxCount - strlen(shape)));
	}

	void Draw(char* canvas, int maxCount)
	{
		strncpy(&canvas[pos], shape, strlen(shape));
	}

	void MoveRight()
	{
		pos += 1;
	}

	void MoveLeft()
	{
		pos -= 1;
	}



};


struct Enemy{
	int pos;
	char shape[20];

	bool bIsRight = false;
	int damagedRemain = 0;

	Enemy(const char* shape, int pos)
	{
		strcpy(this->shape, shape);
		this->pos = rand() % (maxCount - strlen(shape));
	}

	bool IsInCanvas(int maxCount)
	{
		return (this->pos >= 0 && this->pos <= (maxCount - strlen(shape)));
	}

	void Draw(char* canvas, int maxCount)
	{
		strncpy(&canvas[pos], shape, strlen(shape));
	}

	void UpdateShape()
	{
		if ((pos) <= 1 && bIsRight == false)
		{
			bIsRight = true;
		}
		else if (bIsRight == true && (pos) >= (maxCount - strlen(shape)))
		{
			(pos) = maxCount - strlen(shape);

			bIsRight = false;
		}
		else if (bIsRight == false)
			(pos)--;
		else if (bIsRight == true)
			(pos)++;
	}

	//void DamagedEffect(Bullet bullet) //전방선언이 안먹히는듯하다 어찌해야할까 
	//{
	//	if ((this->pos == bullet.pos) || (pos + strlen(shape) >= bullet.pos))
	//	{
	//		if (damagedRemain < 2)
	//		{
	//			strcpy(shape, "(>___<)");
	//		}
	//		
	//	}
	//	else if (damagedRemain <= 2 )
	//	{
	//		damagedRemain = 0;
	//		strcpy(shape, "(*___*)");
	//	}
	//}

};


struct Bullet{
	int pos;
	char shape[20];
	//bullet방향
	bool b_bullet_right;
	//bullet판정 
	bool b_bullet_damaged;
	//bullet 보여지는지 판정
	bool b_is_fire;

	//int maxBullet = 10;
	Bullet() {}

	Bullet(const char* shape)
	{
		this->pos = 0;
		strcpy(this->shape, shape);
		b_is_fire = false;
		b_bullet_damaged = false;
		b_bullet_right = false;
	}

	void Draw(char* canvas, int maxCount)
	{
		strncpy(&canvas[pos], shape, strlen(shape));
	}

	void StartFire(Player player1, char* canvas)
	{
		if (b_is_fire == true) return;
		else
		{
			b_is_fire = true;
			if (b_bullet_right == true)
			{
				strcpy(shape, "==>");
				pos = player1.pos + strlen(player1.shape);
			}
			else {
				strcpy(shape, "<==");
				pos = player1.pos - 1;
			}
			strncpy(&canvas[pos], shape, strlen(shape));
			
		}
	}

	bool IsShotEnd(Enemy enemy)
	{
		if (((pos >= enemy.pos) && (b_bullet_right == true)) || ((b_bullet_right == false) && (pos <= (enemy.pos + strlen(enemy.shape)))) || (pos <=1) || (pos >= (maxCount - strlen(shape)))) //bullet_pos == enemy_shape은 안되는 경우가 있다 왜그런 걸까?
		{
			 b_is_fire = false;
			 return b_is_fire;
		}
	}

	bool ShotPos(Player player, Enemy enemy)
	{
		if (player.pos <= enemy.pos)
		{
			b_bullet_right = true;
			return b_bullet_right;
		}
		else
		{
			b_bullet_right = false;
			return b_bullet_right;
		}
	}

	void UpdateBulletShape()
	{
		if (b_is_fire == false) return;
		else if (b_is_fire == true)
		{
			 if (b_bullet_right == false)
			{
				 strcpy(shape, "<==");
				(pos)--;
			}
			else
			{
				 strcpy(shape, "==>");
				(pos)++;
			}
		}
	}
};
Bullet B[100];


void Clear(char* canvas)
{
	memset(canvas, ',', maxCount);
	canvas[maxCount] = '\0';
}

bool CanvasCheck(char* canvas, char* Shape, int * Pos)
{
	if (*Pos <= canvas[0] || *Pos >= strlen(Shape))
	{
		return false;
	}
}

void draw(char* canvas, char* shape, int pos) {// 원본 정보 vs 복사정보

	//shape이 canvas를 벗어나는지 확인하기.

	//draw
		// shape 그림을 canvas 공간에 player 위치에 복사
	for (int i = 0; i < strlen(shape); i++)
		canvas[pos + i] = shape[i];

	//strncpy(&canvas[player_pos], playershape, strlen(playershape));
}

void Render(char* canvas)
{
	canvas[maxCount] = '\0';
	printf("%s\r", canvas);
}

void Update_shape(char* shape, int* pos, bool& bPos) //웬만하면int형은 복사값을 가져온다.
{
	if ((*pos) <= 1 && bPos == false)
	{
		bPos = true;
	}
	else if (bPos == true && (*pos) >= (maxCount - strlen(shape)))
	{
		(*pos) = maxCount - strlen(shape);

		bPos = false;
	}
	else if (bPos == false)
		(*pos)--;
	else if (bPos == true)
		(*pos)++;

}

int main()
{

	char canvas[maxCount + 1];

	//int player_pos = 0;
	//char player_shape[20] = "(o__o)";
	Player player1{ "(0__0)", maxCount };

	//char enemy_shape[20] = "(*____*)";
	Enemy enemy1{ "(*___*)", maxCount };

	//char bullet_shape[10] = "==";
	//Bullet bullet1{ "==" };

	//int enemy_pos = maxCount - strlen(enemy_shape);
	//적이 canvas 끝에 도착할때마다 방향 조정.
	bool B_enemy_pos_is = false;

	

	//char key;


	while (1)
	{
		//CanvasCheck(canvas, player_shape, &player_pos, enemy_shape,  &enemy_pos, bullet_shape, &bullet_pos);
		if (player1.IsInCanvas(maxCount) == false || enemy1.IsInCanvas(maxCount) == false)
			break;
		//--------------------draw------------------------
		//canvas 그리기.
		Clear(canvas);

		// player 그림을 canvas 공간에 enemy 위치에 복사
		//draw(canvas, player_shape, player_pos);
		player1.Draw(canvas, maxCount);
		// enemy 그림을 canvas 공간에 enemy 위치에 복사
		//draw(canvas, enemy_shape, enemy_pos);
		enemy1.Draw(canvas, maxCount);
		
		for (int i = 0; i < 100; ++i)
		{
			if (B[i].IsShotEnd(enemy1))
			{
				B[i].Draw(canvas, maxCount);
			}
		}
	
		//-------------------update----------------------
		//Update_shape(enemy1.shape, &enemy1.pos, B_enemy_pos_is);
		enemy1.UpdateShape();

		//if (((bullet_pos >= enemy1.pos)&&(b_bullet_right == true)) || ((b_bullet_right == false)&&(bullet_pos <= (enemy1.pos + strlen(enemy1.shape))))) //bullet_pos == enemy_shape은 안되는 경우가 있다 왜그런 걸까?
		//{
		//	b_is_fire = false;
		//}
		//UpdateBulletShape(bullet1.shape, &bullet_pos, bullet1.b_bullet_right, &bullet1.b_is_fire);
	
		for (int i = 0; i < 100; ++i)
		{
			B[i].UpdateBulletShape();
		}
		//총알 발사 시.
		/*if (b_is_fire == true)
		{
			Update_shape(bullet_shape, &bullet_pos, b_bullet_right);
		}*/
		//---------------input-----------------------------
		//int *bullet_pos, int* owner_pos, char* bulletshape, char* ownershape, bool* startFire, bool* bulletright, char* canvas
		if (_kbhit()) // keyboard 받는지 확인.
		{

			char key = _getch();

			switch (key) {
			case 'd':
				player1.MoveRight();
				break;

			case 'a':
				player1.MoveLeft();
				break;

			case ' ':
				for (int i = 0; i < 100; ++i)
				{
					if (B[i].b_is_fire == false) {
						if (enemy1.pos > player1.pos)
						{
							B[i].b_bullet_right = true;
						}
						else
							B[i].b_bullet_right = false;

						//StartFire(&bullet_pos, &player1.pos, bullet1.shape, player1.shape, &bullet1.b_is_fire, &bullet1.b_bullet_right, canvas);
						B[i].StartFire(player1, canvas);
						break;
					}
					
				}
				
			}

		}

		//----------------render-----------------------
		Render(canvas);
		//b_is_fire = false;

		Sleep(100);

	}

	printf("\n정상적으로 종료되었습니다.\n");

	return 0;

}