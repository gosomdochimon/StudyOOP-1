// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#define _CRT_SECURE_NO_WARNINGS
//
#include <Windows.h>
#include <conio.h>
#include <string>

const int maxCount = 80;

struct{
	int pos;
	char shape[20];

} Player;


struct {
	int pos;
	char shape[20];

}Enemy;

struct {
	int pos;
	char shape[20];
	const int MaxBullet = 10;
}Bullet;

void Clear(char* canvas)
{
	memset(canvas, ',', maxCount);
}

void CanvasCheck(char* canvas, char* playerShape, int * playerPos, char* enemyShape, int *enemyPos, char* bulletShape, int *bulletPos)
{
	if (*bulletPos <= canvas[0] || *bulletPos >= strlen(bulletShape))
	{
		*bulletPos = 0;
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

void MoveLeft(int*pos)
{
	if ((*pos) <= 0)// update로 보낼것.
		(*pos) = 0;
	else {
	(*pos)--;
	}
}

void MoveRight(int*pos)
{
	if ((*pos) >= 75)
	{
		(*pos) = 75;
	}
	else
	{
		(*pos)++;
	}
}

void StartFire(int *bullet_pos, int* owner_pos, char* bulletshape, char* ownershape, bool* startFire, bool* bulletright, char* canvas)
{
	//b_bullet_see, pos, bulletowner
	// 예외
	if (*startFire == true) return;
	
	*startFire = true;
	//*bullet_pos = (*owner_pos);

	//draw(canvas, bulletshape, *bullet_pos);
	
	*bullet_pos = strlen(ownershape) -1;

	strncpy(&canvas[*bullet_pos], bulletshape, strlen(bulletshape));

	//그리기 : 캔버스, 발사위치, 방향, 모양, (사거리)
	//draw(char* canvas, char* shape, int pos)
}

//int *bullet_pos, int* owner_pos, char* bulletshape, char* ownershape, bool* startFire, bool* bulletright, char* canvas
//void Input_key(int *bullet_pos, int* owner_pos, char* bulletshape, char* ownershape, bool* startFire, bool* bulletright, char* canvas)
//{
//	if (_kbhit()) // keyboard 받는지 확인.
//	{
//
//		char key = _getch();
//
//		switch (key) {
//		case 'd':
//			MoveRight(owner_pos);
//			break;
//
//		case 'a':
//			MoveLeft(owner_pos);
//			break;
//
//		case ' ':
//			StartFire(bullet_pos, owner_pos, bulletshape, ownershape, startFire, bulletright, canvas);
//			break;
//		}
//
//	}
//}

void Render(char* canvas)
{
	canvas[maxCount] = '\0';
	printf("%s\r", canvas);
}




bool bIsHit(bool bIsDamaged, char* ownerShape, char* damagedShape)
{
	//캐릭터가 맞았는지 판단.
	//b_bullet_damged = false;
	return bIsDamaged;
}

bool BIsFire(bool * isFire)
{
	return *isFire;
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

void UpdateBulletShape(char* shape, int* pos, bool& bPos, bool *bIsFire)
{
	if (*bIsFire == false) return;
	else if (*bIsFire == true)
	{
		if (*pos <= 1 || *pos >= (maxCount - strlen(shape)))
		{
			*bIsFire = false;
		}
		else if (bPos == false)
		{
			(*pos)--;
		}
		else
		{
			(*pos)++;
		}
	}
}
//
//void draw(char* canvas, char* shape, int pos)
//{
//
//	strncpy(&canvas[pos], shape, strlen(shape));
//}



int main()
{

	char canvas[maxCount + 1];

	int player_pos = 0;

	char player_shape[20] = "(o__o)";

	char enemy_shape[20] = "(*____*)";

	char bullet_shape[10] = "==";

	int enemy_pos = maxCount - strlen(enemy_shape);
	//적이 canvas 끝에 도착할때마다 방향 조정.
	bool B_enemy_pos_is = false;

	const int MaxBullet = 80;
	int bullet_pos = 0;
	//bullet방향
	bool b_bullet_right = false;
	//bullet판정 
	bool b_bullet_damged = false;
	//bullet 보여지는지 판정
	bool b_is_fire = false;

	//char key;


	while (1)
	{
		//CanvasCheck(canvas, player_shape, &player_pos, enemy_shape, &enemy_pos, bullet_shape, &bullet_pos);
		//--------------------draw------------------------
		//canvas 그리기.
		Clear(canvas);

		// player 그림을 canvas 공간에 enemy 위치에 복사
		draw(canvas, player_shape, player_pos);

		// enemy 그림을 canvas 공간에 enemy 위치에 복사
		draw(canvas, enemy_shape, enemy_pos);

		if (b_is_fire == true)
		{
			draw(canvas, bullet_shape, bullet_pos);
		}
		//-------------------update----------------------
		Update_shape(enemy_shape, &enemy_pos, B_enemy_pos_is);
		UpdateBulletShape(bullet_shape, &bullet_pos, b_bullet_right, &b_is_fire);
		
			
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
				MoveRight(&player_pos);
				break;

			case 'a':
				MoveLeft(&player_pos);
				break;

			case ' ':
				StartFire(&bullet_pos, &player_pos, bullet_shape, player_shape, &b_is_fire, &b_bullet_right, canvas);
				break;
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