#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include"infomation.h"

//[�ó�����]
//�÷��̾�� 5��¥�� ������ �����ߴ�.
//�� ������ ���� ���͵��� ��ٸ��� �ִ�.
//
//[�÷��� ���]
//�÷��� ����� �÷��̾�� ���Ͱ�
//���� �ֻ����� ���� ū ���� ������ ����
//�¸��ϸ� �� ���� HP�� �����Ѵ�.
//
//[���� ��]
//- ������ �����ϸ� �� ���� ���� ���� ��ġ
//- �÷��̾� �Ǵ� ���ʹ� HP�� 0�� �Ǹ� ���
//- �� ���� ���͸� ���̸� ���� ������ ����
//- ��� ���� ����ġ�� ���� ó��
//- �÷��� ���� ����ϸ� ���� ó��
//
//[����]
//�÷��̾� ����(�̸�, HP, ���ݷ�, ����)
//���� ����(�̸�, HP, ���ݷ�, ����)
//��(1���� �迭)
//�÷��̾�� ���� ������ �̸� ����

void InitInfomation(Info *_pInfo)
{	
	Info sInfo[MAX_INFO] = {
		{ 2000,200,0,"����" },
		{ 100,60,30,"��ũ" },
		{ 100,100,100,"Ʈ��" },
		{ 100,80,80,"����" },
		{ 100,30,30,"����" },
		{ 100,50,30,"�巡��" }
	};
	memcpy(_pInfo, &sInfo, sizeof(Info) * MAX_INFO);
}
void Update();
void PrintMainMenu(Info *_pInfo);

void Update()
{
	int arrFloor[6] = { 0, }; //�� �迭
	int arrCheck[6] = { 0, };// pInfo�ϰ� 1:1 ��Ī���� ���� �ߺ� üũ
	int nFloorCnt = 0; // �� üũ
	int nRandMonster = 0; // �������� ���� ���� ����
	int nMonsterCnt = MAX_INFO; // ���� �Ѽ�
	int nCheckMonster = 0; //���� �ߺ� üũ
	int nPlayerDice = 0; //�÷��̾� �ֻ�����
	int nMonsterDice = 0; //���� �ֻ��� ��
	Info *pInfo = (Info*)malloc(sizeof(Info) *  MAX_INFO);
	InitInfomation(pInfo);

	int i;
	int nFlag = 0;	

	//PrintMainMenu(pInfo);

NextFloor:
	PrintMainMenu(pInfo);
	printf("1.���� �ϱ�\n");
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
			printf("\t\t%d���� ���� �Ͽ���. \n\n", nFloorCnt);
			printf("\t\t�߻��� %s�� ��Ÿ����.\n", pInfo[nRandMonster].cName);
			printf("\t\t�������� ����. \n");
			printf("\t\t1.�����ϱ�\n");
			scanf_s("%d", &nFlag);

			system("cls");

			PrintMainMenu(pInfo);
			while (nFlag == 1)
			{
				nPlayerDice = ((unsigned)rand() % DICE) + 1;
				srand(time(NULL));
				nMonsterDice = ((unsigned)rand() % DICE) + 1;
				srand(time(NULL));

				printf("\t\t�ֻ����� ��\n");
				printf("\t\t%s : %d  vs %s : %d\n", pInfo[PLAYER].cName, nPlayerDice, pInfo[nRandMonster].cName, nMonsterDice);

				int tempD = 0;								
				if (nPlayerDice > nMonsterDice)
				{
					printf("\t\t%s�� ���� �� ũ�� ���Դ�!\n", pInfo[PLAYER].cName);
					switch (nRandMonster)
					{
					case ORC:
					{
						tempD = pInfo[PLAYER].nDamage - pInfo[ORC].nDef;
						pInfo[ORC].nHp -= tempD;
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[PLAYER].cName, pInfo[ORC].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s�� ���� ü�� : %d\n\n", pInfo[ORC].cName ,pInfo[ORC].nHp);
						if (pInfo[ORC].nHp <= 0)
						{
							printf("\t\t%s�� �����ƴ�! ���� ������ ����\n", pInfo[ORC].cName);
							printf("\t\t\n1.���� ������ ����\n");
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
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[PLAYER].cName, pInfo[TROLL].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s�� ���� ü�� : %d\n\n", pInfo[TROLL].cName, pInfo[TROLL].nHp);
						if (pInfo[TROLL].nHp <= 0)
						{
							printf("\t\t%s�� �����ƴ�! ���� ������ ����\n", pInfo[TROLL].cName);
							printf("\t\t\n1.���� ������ ����\n");
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
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[PLAYER].cName, pInfo[OGRE].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s�� ���� ü�� : %d\n\n", pInfo[OGRE].cName, pInfo[OGRE].nHp);
						if (pInfo[OGRE].nHp <= 0)
						{
							printf("\t\t%s�� �����ƴ�! ���� ������ ����\n", pInfo[OGRE].cName);
							printf("\t\t\n1.���� ������ ����\n");
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
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[PLAYER].cName, pInfo[IMP].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s�� ���� ü�� : %d\n\n", pInfo[IMP].cName, pInfo[IMP].nHp);
						if (pInfo[IMP].nHp <= 0)
						{
							printf("\t\t%s�� �����ƴ�! ���� ������ ����\n", pInfo[IMP].cName);
							printf("\t\t\n1.���� ������ ����\n");
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
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[PLAYER].cName, pInfo[DRAGON].cName, pInfo[PLAYER].nDamage);
						printf("\t\t%s�� ���� ü�� : %d\n\n", pInfo[DRAGON].cName, pInfo[DRAGON].nHp);
						if (pInfo[DRAGON].nHp <= 0)
						{
							printf("\t\t%s�� �����ƴ�! ���� ������ ����\n", pInfo[DRAGON].cName);
							printf("\t\t\n1.���� ������ ����\n");
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
					printf("\t\t%s�� ���� �� ũ�� ���Դ�!\n", pInfo[nRandMonster].cName);
					switch (nRandMonster)
					{
					case ORC:
					{
						tempD = pInfo[ORC].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[ORC].cName, pInfo[PLAYER].cName,  pInfo[ORC].nDamage);
						break;
					}						
					case TROLL:
					{
						tempD = pInfo[TROLL].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[TROLL].cName, pInfo[PLAYER].cName, pInfo[TROLL].nDamage);
						break;
					}
					case OGRE:
					{
						tempD = pInfo[OGRE].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[OGRE].cName, pInfo[PLAYER].cName, pInfo[OGRE].nDamage);
						break;
					}
					case IMP:
					{
						tempD = pInfo[IMP].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[IMP].cName, pInfo[PLAYER].cName, pInfo[IMP].nDamage);
						break;
					}
					case DRAGON:
					{
						tempD = pInfo[DRAGON].nDamage - pInfo[PLAYER].nDef;
						pInfo[PLAYER].nHp -= tempD;
						printf("\t\t%s�� %s���� %d��ŭ�� �������� �־���.\n\n", pInfo[DRAGON].cName, pInfo[PLAYER].cName, pInfo[DRAGON].nDamage);
						break;
					}
					}
				}
				else if (nPlayerDice == nMonsterDice)
				{
					printf("\t\t���� �Ȱ��� ���Դ�! �ٽ� ���� �غ���\n");					
				}

				printf("\n1.�����ϱ�\n");
				scanf_s("%d", &nFlag);
				system("cls");
				PrintMainMenu(pInfo);
				
				if (pInfo[PLAYER].nHp <= 0)
				{
					system("cls");

					printf("\t\t%s�� HP�� 0 �Ǿ ����ߴ�.\n", pInfo[PLAYER].cName);
					printf("\t\tGAME OVER\n");
					printf("\t\t\n1. �����ϱ�\n");
					scanf_s("%d", &nFlag);
					if (nFlag == 1)
					{
						exit(1);
					}					
				}
				if (nFloorCnt > 5)
				{
					printf("Ŭ����!");
					printf("\t\t\n1. �����ϱ�\n");
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

	printf("\t\t\t    5�� ������ � ���ÿ�\t\t\t\n\n");
	printf("\t\t\t       ���� �������ͽ�\t\t\t\n\n");
	printf("\t\t�̸� : %s  HP : %d  ���ݷ� : %d  ���� : %d \n\n", _pInfo[PLAYER].cName, _pInfo[PLAYER].nHp, _pInfo[PLAYER].nDamage, _pInfo[PLAYER].nDef);

}
void Input()
{


}

void main()
{
	
	Update();
	
}
