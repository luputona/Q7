#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include"infomation.h"

//[시나리오]
//플레이어는 5층짜리 던전에 도착했다.
//각 층에는 각종 몬스터들이 기다리고 있다.
//
//[플레이 방식]
//플레이 방식은 플레이어와 몬스터가
//각각 주사위를 던져 큰 수가 나오는 쪽이
//승리하며 진 쪽은 HP가 감소한다.
//
//[게임 룰]
//- 게임을 시작하면 각 층에 몬스터 랜덤 배치
//- 플레이어 또는 몬스터는 HP가 0이 되면 사망
//- 각 층의 몬스터를 죽이면 다음 층으로 진행
//- 모든 적을 물리치면 엔딩 처리
//- 플레이 도중 사망하면 엔딩 처리
//
//[참고]
//플레이어 정보(이름, HP, 공격력, 방어력)
//몬스터 정보(이름, HP, 공격력, 방어력)
//맵(1차원 배열)
//플레이어와 몬스터 정보는 미리 설정

void InitInfomation(Info *_pInfo)
{	
	Info sInfo[MAX_INFO] = {
		{ 2000,200,0,"리신" },
		{ 100,60,30,"오크" },
		{ 100,100,100,"트롤" },
		{ 100,80,80,"오거" },
		{ 100,30,30,"임프" },
		{ 100,50,30,"드래곤" }
	};
	memcpy(_pInfo, &sInfo, sizeof(Info) * MAX_INFO);
}
void Update();
void PrintMainMenu(Info *_pInfo);

void Update()
{
	int arrFloor[6] = { 0, }; //층 배열
	int arrCheck[6] = { 0, };// pInfo하고 1:1 매칭으로 몬스터 중복 체크
	int nFloorCnt = 0; // 층 체크
	int nRandMonster = 0; // 랜덤으로 뽑은 몬스터 받음
	int nMonsterCnt = MAX_INFO; // 몬스터 총수
	int nCheckMonster = 0; //몬스터 중복 체크
	int nPlayerDice = 0; //플레이어 주사위값
	int nMonsterDice = 0; //몬스터 주사위 값
	Info *pInfo = (Info*)malloc(sizeof(Info) *  MAX_INFO);
	InitInfomation(pInfo);

	int i;
	int nFlag = 0;	

	//PrintMainMenu(pInfo);

NextFloor:
	PrintMainMenu(pInfo);
	printf("1.입장 하기\n");
	scanf_s("%d", &nFlag);

	if (nFlag == 1)
	{
		while (nFlag == 1)
		{
		
			nFlag = 0;
			nFloorCnt++;
			srand(time(NULL));
			nRandMonster = (rand() % (MAX_INFO)) + 1;

			if (arrCheck[nRandMonster] == nCheckMonster)
			{
				arrCheck[nRandMonster] = 1;
			}
			else if (arrCheck[nRandMonster] != nCheckMonster)
			{
				continue;
			}
			printf("\t\t%d층에 도착 하였다. \n\n", nFloorCnt);
			printf("\t\t야생의 %s가 나타났다.\n", pInfo[nRandMonster].cName);
			printf("\t\t도망따윈 없다. \n");
			printf("\t\t1.공격하기\n");
			scanf_s("%d", &nFlag);

			system("cls");

			PrintMainMenu(pInfo);
			while (nFlag == 1)
			{
				nPlayerDice = ((unsigned)rand() % DICE) + 1;
				srand(time(NULL));
				nMonsterDice = ((unsigned)rand() % DICE) + 1;
				srand(time(NULL));

				printf("\t\t주사위의 값\n");
				printf("\t\t%s : %d  vs %s : %d\n", pInfo[PLAYER].cName, nPlayerDice, pInfo[nRandMonster].cName, nMonsterDice);

				int tempD = 0;								
				if (nPlayerDice > nMonsterDice)
				{
					printf("\t\t%s의 값이 더 크게 나왔다!\n", pInfo[PLAYER].cName);
					switch (nRandMonster)
					{
					case ORC:
					{
						tempD = pInfo[PLAYER].nDamage - pInfo[ORC].nDef;
						pInfo[ORC].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[PLAYER].cName, pInfo[ORC].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s의 남은 체력 : %d\n\n", pInfo[ORC].cName ,pInfo[ORC].nHp);
						if (pInfo[ORC].nHp <= 0)
						{
							printf("\t\t%s를 물리쳤다! 다음 층으로 가자\n", pInfo[ORC].cName);
							printf("\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}
						break;
					}
					case TROLL:
					{
						tempD = pInfo[PLAYER].nDamage - pInfo[TROLL].nDef;
						pInfo[TROLL].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[PLAYER].cName, pInfo[TROLL].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s의 남은 체력 : %d\n\n", pInfo[TROLL].cName, pInfo[TROLL].nHp);
						if (pInfo[TROLL].nHp <= 0)
						{
							printf("\t\t%s를 물리쳤다! 다음 층으로 가자\n", pInfo[TROLL].cName);
							printf("\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}
						break;
					}
					case OGRE:
					{
						tempD = pInfo[PLAYER].nDamage - pInfo[OGRE].nDef;
						pInfo[OGRE].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[PLAYER].cName, pInfo[OGRE].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s의 남은 체력 : %d\n\n", pInfo[OGRE].cName, pInfo[OGRE].nHp);
						if (pInfo[OGRE].nHp <= 0)
						{
							printf("\t\t%s를 물리쳤다! 다음 층으로 가자\n", pInfo[OGRE].cName);
							printf("\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}						
					}
					case IMP:
					{
						tempD = pInfo[PLAYER].nDamage - pInfo[IMP].nDef;
						pInfo[IMP].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[PLAYER].cName, pInfo[IMP].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s의 남은 체력 : %d\n\n", pInfo[IMP].cName, pInfo[IMP].nHp);
						if (pInfo[IMP].nHp <= 0)
						{
							printf("\t\t%s를 물리쳤다! 다음 층으로 가자\n", pInfo[IMP].cName);
							printf("\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}						
					}
					case DRAGON:
					{
						tempD = pInfo[PLAYER].nDamage - pInfo[DRAGON].nDef;
						pInfo[DRAGON].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[PLAYER].cName, pInfo[DRAGON].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s의 남은 체력 : %d\n\n", pInfo[DRAGON].cName, pInfo[DRAGON].nHp);
						if (pInfo[DRAGON].nHp <= 0)
						{
							printf("\t\t%s를 물리쳤다! 다음 층으로 가자\n", pInfo[DRAGON].cName);
							printf("\t\t\n1.다음 층으로 가기\n");
							scanf_s("%d", &nFlag);
							system("cls");
							if (nFlag == 1)
							{
								goto NextFloor;
							}
						}						
					}
					}
				}
				else if (nPlayerDice < nMonsterDice)
				{
					printf("\t\t%s의 값이 더 크게 나왔다!\n", pInfo[nRandMonster].cName);
					switch (nRandMonster)
					{
					case ORC:
					{
						tempD = pInfo[ORC].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[ORC].cName, pInfo[PLAYER].cName,  pInfo[ORC].nDamage);
						break;
					}						
					case TROLL:
					{
						tempD = pInfo[TROLL].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[TROLL].cName, pInfo[PLAYER].cName, pInfo[TROLL].nDamage);
						break;
					}
					case OGRE:
					{
						tempD = pInfo[OGRE].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[OGRE].cName, pInfo[PLAYER].cName, pInfo[OGRE].nDamage);
						break;
					}
					case IMP:
					{
						tempD = pInfo[IMP].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[IMP].cName, pInfo[PLAYER].cName, pInfo[IMP].nDamage);
						break;
					}
					case DRAGON:
					{
						tempD = pInfo[DRAGON].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s는 %s에게 %d만큼의 데미지를 주었다.\n\n", pInfo[DRAGON].cName, pInfo[PLAYER].cName, pInfo[DRAGON].nDamage);
						break;
					}
					}
				}
				else if (nPlayerDice == nMonsterDice)
				{
					printf("\t\t값이 똑같이 나왔다! 다시 공격 해보자\n");					
				}

				printf("\n1.공격하기\n");
				scanf_s("%d", &nFlag);
				system("cls");
				PrintMainMenu(pInfo);
				
				if (pInfo[PLAYER].nHp <= 0)
				{
					system("cls");

					printf("\t\t%s의 HP가 0 되어서 사망했다.\n", pInfo[PLAYER].cName);
					printf("\t\tGAME OVER\n");
					printf("\t\t\n1. 종료하기\n");
					scanf_s("%d", &nFlag);
					if (nFlag == 1)
					{
						exit(1);
					}					
				}
				if (nFloorCnt > 5)
				{
					printf("클리어!");
					printf("\t\t\n1. 종료하기\n");
					scanf_s("%d", &nFlag);
					if (nFlag == 1)
					{
						exit(1);
					}
				}
			}			
		}
	}
		
}
void PrintMainMenu(Info *_pInfo)
{
	char arrMoniter[YC][XC];
	int i, j;
	for (i = 0; i < YC; i++)
	{
		for (j = 0; j< XC; j++)
		{
			arrMoniter[i][j] = '\0';
		}
	}

	for (i = 0; i < YC; i++)
	{
		for (j = 0; j < XC; j++)
		{
			if (i == 0 || i == YC - 1)
			{
				arrMoniter[i][j] = '=';
			}
			else if (j == 0 || j == XC - 1)
			{
				arrMoniter[i][j] = '=';
			}

			if (i == 1 && j == 15 || i == 1 && j == 16 || i == 1 && j == 17 || i == 1 && j == 18 || i == 1 && j == 19 || i == 1 && j == 20 || i == 1 && j == 21 || i == 1 && j == 23 ||
				i == 1 && j == 35 || i == 1 && j == 36 || i == 1 && j == 37 || i == 1 && j == 38 || i == 1 && j == 39 || i == 1 && j == 40 || i == 1 && j == 41 || i == 1 && j == 43 ||
				i == 1 && j == 55 || i == 1 && j == 56 || i == 1 && j == 57 || i == 1 && j == 58 || i == 1 && j == 59 || i == 1 && j == 60 || i == 1 && j == 61 || i == 1 && j == 62  )
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 2 && j == 15 || i == 1 && j == 20 || i == 2 && j == 23 ||
				 i == 2 && j == 38 || i == 2 && j == 43 || 
				 i == 2 && j == 55  )
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 3 && j == 15 || i == 3 && j == 19 || i == 3 && j == 20 || i == 3 && j == 21 || i == 3 && j == 22 || i == 3 && j == 23 ||
				i == 3 && j == 37 || i == 3 && j == 39 || i == 3 && j == 41 || i == 3 && j == 42 || i == 3 && j == 43 || 
				i == 3 && j == 55 )
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 4 && j == 15 || i == 4 && j == 23 || 
				i == 4 && j == 36 || i == 4 && j == 40 || i == 4 && j == 43 ||
				i == 4 && j == 55 || i == 4 && j == 56 || i == 4 && j == 57 || i == 4 && j == 58 || i == 4 && j == 59 || i == 4 && j == 60 || i == 4 && j == 61 || i == 4 && j == 62)
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 5 && j == 15 || i == 5 && j == 16 || i == 5 && j == 17 || i == 5 && j == 18 || i == 5 && j == 19 || i == 5 && j == 20 || i == 5 && j == 21 || i == 5 && j == 23 ||
				i == 5 && j == 35 || i == 5 && j == 41 || i == 5 && j == 43 || 
				i == 5 && j == 62 )
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 6 && j == 23 || i == 6 && j == 43 || i == 6 && j == 62)
			{
				arrMoniter[i][j] = '0';
			}
			else if ( i == 7 && j == 15 || i == 7 && j == 35 || i == 7 && j == 62)
			{
				arrMoniter[i][j] = '0';
			}
			else if (i == 8 && j == 15 || i == 8 && j == 16 || i == 8 && j == 17 || i == 8 && j == 18 || i == 8 && j == 19 || i == 8 && j == 20 || i == 8 && j == 21 || i == 8 && j == 22 || i == 8 && j == 23 ||
				i == 8 && j == 35 || i == 8 && j == 36 || i == 8 && j == 37 || i == 8 && j == 38 || i == 8 && j == 39 || i == 8 && j == 40 || i == 8 && j == 41 || i == 8 && j == 42 || i == 8 && j == 43 ||
				i == 8 && j == 62 || i == 8 && j == 61 || i == 8 && j == 60 || i == 8 && j == 59 || i == 8 && j == 58 || i == 8 && j == 57 || i == 8 && j == 56 || i == 8 && j == 55 )
			{
				arrMoniter[i][j] = '0';
			}
		}		
	}

	
	for (i = 0; i < YC; i++)
	{
		for (j = 0; j< XC; j++)
		{
			printf("%c", arrMoniter[i][j]);
		}
		printf("\n");
	}

	printf("\t\t\t    5층 던전에 어서 오시오\t\t\t\n\n");
	printf("\t\t\t       나의 스테이터스\t\t\t\n\n");
	printf("\t\t이름 : %s  HP : %d  공격력 : %d  방어력 : %d \n\n", _pInfo[PLAYER].cName, _pInfo[PLAYER].nHp, _pInfo[PLAYER].nDamage, _pInfo[PLAYER].nDef);

}
void Input()
{


}

void main()
{
	
	Update();
	
}
