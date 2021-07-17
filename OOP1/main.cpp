// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <conio.h>



void printSpaces(int i)

{

	for (int j = 0; j < i; j++)

		printf(" ");

}

void draw()
{

}


int main()

{

	const int maxCount = 80;
	char canvas[maxCount + 1];
	int player_pos = 0;
	/*
		char player_shape[6] = "(o_o)";
		int enemy_pos = 75;
		har enemy_shape[6] = "(*_*)";
	*/
	char player_shape[20] = "(0_0)";
	char enemy_shape[20] = "(*___*)";
	int enemy_pos = maxCount - (int)strlen(enemy_shape);
	

	bool B_enemy_pos_is = false;

	char key;



	while ((player_pos < maxCount - strlen(player_shape)) && enemy_pos >= 0)
	{

		//canvas 그리기.
		for (int i = 0; i < maxCount; i++)
			canvas[i] = ',';

		// player 그림을 canvas 공간에 player 위치에 복사
		for (int i = 0; i < 5; i++)
			canvas[player_pos + i] = player_shape[i];

		for (int i = 0; i < strlen(enemy_shape); i++)
			canvas[enemy_pos + i] = enemy_shape[i];

		// enemy 그림을 canvas 공간에 enemy 위치에 복사
		if (enemy_pos <= 1 && B_enemy_pos_is == false)
		{
			B_enemy_pos_is = true;
		}
		else if (B_enemy_pos_is == true && enemy_pos >= 74)

		{
			enemy_pos = 75;
			B_enemy_pos_is = false;
		}
		else if (B_enemy_pos_is == false)
			enemy_pos--;
		else if (B_enemy_pos_is == true)
			enemy_pos++;





		if (_kbhit()) // keyboard 받는지 확인.

		{

			key = _getch();



			switch (key)

			{
			case 'd':
				player_pos++;
				break;
			case 'a':
				if (player_pos <= 0)
					player_pos = 0;
				else
					player_pos--;
				break;

			}

		}



		canvas[maxCount] = '\0';

		printf("%s\r", canvas);

		Sleep(100);

	}

	printf("\n정상적으로 종료되었습니다.\n");

	return 0;

}