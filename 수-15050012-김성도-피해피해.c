#pragma warning(disable:4996)
#include <stdio.h> 
#include <windows.h> 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


//������
#define black			0
#define dark_green		2	//	 BLACK,			0 : ��� 				 DARK_BLUE,      1 : ��ο� �Ķ� 
#define dark_red		4
#define dark_yellow		6	//	 DARK_GREEN,    2 : ��ο� �ʷ� 		 DARK_SKY_BLUE,  3 : ��ο� �ϴ�
#define dark_gray		8 
#define dark_blue		1	//	 DARK_RED,      4 : ��ο� ���� 		 DARK_VIOLET,    5 : ��ο� ����
#define dark_sky_blue	3
#define dark_violet		5	//	 DARK_YELLOW,   6 : ��ο� ���			 GRAY,			 7 : ȸ�� 
#define green			10
#define red				12 	//	 DARK_GRAY,     8 : ��ο� ȸ�� 		 BLUE,			 9 : �Ķ� 
#define yellow			14	 
#define gray			7	//	 GREEN,			10 : �ʷ� 				 SKY_BLUE,		 11 : �ϴ� 
#define blue			9
#define sky_blue		11	//	 RED,			12 : ����				 VIOLET,		 13 : ����
#define violet			13
#define white			15	//	 YELLOW,		14 : ��� 				 WHITE,			 15 : �Ͼ�



//����Ű ����//
#define Up 72
#define Down 80
#define Right 77
#define Left 75
#define ESC 27
#define ������ 38


//���־��� �Լ� ����//
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
#define randomize() srand((unsigned)time(NULL))	//�����߻��� �ʱ�ȭ�Ѵ�.
#define random(n) (rand() % (n))  //0~n���� ������ �������ش�.




////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

//��������Լ� �߰�//
void setcolor(int bgcolor, int color) // ���,���ڻ�

{

     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) <<4) | color);

}

// Ŀ���� y��ǥ�� �����Ѵ�.
int wherex()

{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);

	return BufInfo.dwCursorPosition.X;
}

// Ŀ���� y��ǥ�� �����Ѵ�.
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);

	return BufInfo.dwCursorPosition.Y;
}
void setcursortype(CURSOR_TYPE c)//Ŀ���� �����.
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) 

	{

	case NOCURSOR:

		CurInfo.dwSize=1;

		CurInfo.bVisible=FALSE;

		break;

	case SOLIDCURSOR:

		CurInfo.dwSize=100;

		CurInfo.bVisible=TRUE;

		break;

	case NORMALCURSOR:

		CurInfo.dwSize=20;

		CurInfo.bVisible=TRUE;

		break;

	}

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);

}

void ���찳()//ȭ���� �����

{

	system("cls");

}

void gotoxy(int x,int y)

{

     COORD Cur;

     Cur.X=x;

     Cur.Y=y;

     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);//Ŀ���� ���ϴ���ġ�κ������ִ¸�ɾ�

}

 struct tag_Enemy

{

     BOOL exist;

     int Type;

     int x,y;

     int ����;//1=���ʽ���, -1=�����ʽ���.

     int nFrame;

     int nStay;

} ��[������];

 BOOL ����Ű(int Key)

{

     return ((GetAsyncKeyState(Key) & 0x8000) != 0);

}

 void �׸�ĭ()
 {
	 gotoxy(15,2);printf("��������������������������������������������������������������");
	 gotoxy(15,3);printf("��                                                          ��");
	 gotoxy(15,4);printf("��                                                          ��");
	 gotoxy(15,5);printf("��                                                          ��");
	 gotoxy(15,6);printf("��������������������������������������������������������������");
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////////////////////

char *arEnemy[]={" (>_<) "," (o_o) ", " (O@O) ", " (-=-) "};  //���� ���

int fx,fy;

int ����;

int ���̵�;

int main()

{

	////////////////���� ����////////////////

	char key;

	int count;

	int i,j;

	int ��;

	BOOL bFound;   //�ҷ������Ѱ� �ֳ� ������ �Ǻ��ϱ� ������(T/F)

	int y=5;

	int �۾�=0;

	int temp;
	



	start:
	for(i=0;i<64;i++)

	{

	gotoxy(0,i);

	setcolor(black,white); printf("                                                                              ");


	}
	fx=40;//�ʱ� ��ġ����

	fy=43;//�ʱ� ��ġ����

	setcursortype(NOCURSOR);//Ŀ�� ���ֱ�

	randomize();

	system("mode con: cols=78 lines=46");

	gotoxy(30,6);

	printf("�ڡڡ���������!!�ڡڡ�");

	gotoxy(10,10);printf("��������������������������������������������������������������");
	gotoxy(10,11);printf("��                       �ؼ�����                         ��");
	gotoxy(10,12);printf("��                                                          ��");
	gotoxy(10,13);printf("��   �� ������ �����ϼ� �ִ� �ڡ� �� ��ü�� �ű�鼭        ��");
	gotoxy(10,14);printf("��   �����̴� ������ ���� �ʰ� ���� ������(����)����        ��");
	gotoxy(10,15);printf("��   ���� �����Դϴ�.                                       ��");
	gotoxy(10,16);printf("��                                                          ��");
	gotoxy(10,17);printf("��   ����ְ� �÷������ּ���~                               ��");
	gotoxy(10,18);printf("��                                                          ��");
	gotoxy(10,19);printf("��������������������������������������������������������������");
 
	gotoxy(54,43);

	printf("15050012 �輺��");
	for(temp=0;;temp++)
	{
	
	if (kbhit())

		{

		key=getch();

		if (key==0xE0 || key==0) 

			getch();

		if(!(key==1234598172516))//�̷�Ű�� ���⶧����..(���۹��)

		break;

		}
	

	gotoxy(17,40);
	
	if(temp%2==0)

		setcolor(0,15);printf("����������Ϸ��� �ƹ�Ű�� ���ּ���!!������");

	gotoxy(17,40);

	if(temp%2==1)

		setcolor(0,0);printf("����������Ϸ��� �ƹ�Ű�� ���ּ���!!������");

	Sleep(700);
	}
	


	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(15,0); printf("                                                                              ");

	Sleep(50);

	}

	//�޴�
	gotoxy(15,2);printf("��������������������������������������������������������������");
	gotoxy(15,3);printf("��                 ������ �������ּ���                    ��");
	gotoxy(15,4);printf("��                                                          ��");
	setcolor(15,0);gotoxy(15,5);printf("                           ������������    ");
	gotoxy(15,6);printf("                                                          ");
	setcolor(15,1);gotoxy(15,7);printf("                           ������������    ");
	gotoxy(15,8);printf("                                                          ");
	setcolor(15,2);gotoxy(15,9);printf("                           ������������    ");
	gotoxy(15,10);printf("                                                          ");
	setcolor(15,3);gotoxy(15,11);printf("                           ������������    ");
	gotoxy(15,12);printf("                                                          ");
	setcolor(15,4);gotoxy(15,13);printf("                           ������������    ");
	gotoxy(15,14);printf("                                                          ");
	setcolor(15,5);gotoxy(15,15);printf("                           ������������    ");
	gotoxy(15,16);printf("                                                          ");
	setcolor(15,6);gotoxy(15,17);printf("                           ������������    ");
	gotoxy(15,18);printf("                                                          ");
	setcolor(15,7);gotoxy(15,19);printf("                           ������������    ");
	gotoxy(15,20);printf("                                                      ");
	setcolor(15,8);gotoxy(15,21);printf("                           ������������    ");
	gotoxy(15,22);printf("                                                          ");
	setcolor(15,9);gotoxy(15,23);printf("                           ������������    ");
	gotoxy(15,24);printf("                                                          ");
	setcolor(15,10);gotoxy(15,25);printf("                           ������������    ");
	gotoxy(15,26);printf("                                                          ");
	setcolor(15,11);gotoxy(15,27);printf("                           ������������    ");
	gotoxy(15,28);printf("                                                          ");
	setcolor(15,12);gotoxy(15,29);printf("                           ������������    ");
	gotoxy(15,30);printf("                                                          ");
	setcolor(15,13);gotoxy(15,31);printf("                           ������������    ");
	gotoxy(15,32);printf("                                                          ");
	setcolor(15,14);gotoxy(15,33);printf("                           ������������    ");
	setcolor(15,0);gotoxy(15,34);printf("��                                                          ��");
	gotoxy(15,35);printf("��������������������������������������������������������������");
	gotoxy(15,37);printf("���� �� a�� �ι� �����ּ���");

	while(1)

	{

	gotoxy(23,y);

	printf("��");

	getch();

	key=getch();

	if(key=='a')

		break;

	if (����Ű(VK_UP)) 

		if (y > 5) 

		{
			y=y-2;

			gotoxy(23,y+2);

			printf("  ");

		}

	
	if (����Ű(VK_DOWN)) 

		if (y < 33) 

		{
			y=y+2;

			gotoxy(23,y-2);

			printf("  ");
		}
		
	}

	��=(y-5)/2;

	if(��==0);

	�۾�=15;

	//���� �ٲٱ�
	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(��,�۾�); printf("                                                                              ");

	Sleep(50);

	}

	//�۾��� ����

	for(temp=0;;temp++)

	{

	setcolor(��,�۾�);gotoxy(10,2);printf("��������������������������������������������������������������");
	setcolor(��,�۾�);gotoxy(10,3);printf("��         �۾����� ������ (����Ű�� �̿��ؼ� ����)       ��");
	setcolor(��,�۾�);gotoxy(10,4);printf("��                                                          ��");
	setcolor(��,�۾�);gotoxy(10,5);printf("��             ���                        ����             ��");
	setcolor(��,�۾�);gotoxy(10,6);printf("��������������������������������������������������������������");
	setcolor(��,�۾�);gotoxy(10,8);printf("�������� a�� �ι� ���ּ���");

	getch();

	key=getch();

	if(key=='a')

		break;

	if(temp%2==0)

		�۾�=0;

	else

		�۾�=15;

	}

	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(��,�۾�); printf("                                                                              ");

	}
	fflush(stdin);
	setcolor(��,�۾�);gotoxy(10,2);printf("��������������������������������������������������������������");
	setcolor(��,�۾�);gotoxy(10,3);printf("��                  ���̵��� �������ּ���                   ��");
	setcolor(��,�۾�);gotoxy(10,4);printf("��                                                          ��");
	setcolor(��,�۾�);gotoxy(10,5);printf("��         [�ʱ�]           �߱�            ���            ��");
	setcolor(��,�۾�);gotoxy(10,6);printf("��������������������������������������������������������������");
	setcolor(��,�۾�);gotoxy(10,8);printf("�������� a�� �ι� ���ּ���");






	for(temp=0;;)

	{

		key=getch();

		if (key==0xE0 || key==0) 

			getch();

	if(key=='a')

		break;

		if (key==Left) 

			if (temp>0) 
			
			{ 
				
				temp--; 
			
			}

        if (key==Right) 

			if (temp<2) 
			
			{ 
				
				temp++; 
			
			}
		
	if(temp==0)

	{setcolor(��,�۾�);gotoxy(10,5);printf("��         [�ʱ�]           �߱�            ���            ��");���̵�=30;}

	if(temp==1)

	{setcolor(��,�۾�);gotoxy(10,5);printf("��          �ʱ�           [�߱�]           ���            ��");���̵�=15;}

	if(temp==2)

	{setcolor(��,�۾�);gotoxy(10,5);printf("��          �ʱ�            �߱�           [���]           ��");���̵�=3;}
	 

	}


	system("cls");




	//////////////////////���Ӽҽ�///////////////////////////
	for (count=0;;count++)

	{

		if (count % 5 == 0)//�ʴ� �ִ� 20ȸ �����δ�

		{

		if (����Ű(VK_LEFT)) 

			if (fx > 4) fx--;

        if (����Ű(VK_RIGHT)) 

			if (fx < 73) fx++;

		if (����Ű(VK_UP)) 

			fy--;

		if (����Ű(VK_DOWN)) 

			if (fy < 41) fy++;

		}



		if (kbhit())

		{

		key=getch();

		if (key==0xE0 || key==0) 

			getch();

		}
		

		
		gotoxy(fx-2,fy-1);	puts("      ");

		gotoxy(fx-3,fy);    puts(" �ڡ� ");//�������� ����

		gotoxy(fx-2,fy+1);  puts("      ");

		gotoxy(0,42); printf("==============================================================================");
		gotoxy(0,0); printf("�ââââââââââââââââââââââââââââââââââââââ�");

		//��������
		if (random(���̵�) == 0) {

              for (i=0;i<������ && ��[i].exist==TRUE;i++) {;}

              if (i != ������) {

                   if (random(4)==1) {//���ʰ� �����ʿ��� �����°��� Ȯ������

                        ��[i].x=5;

                        ��[i].����=1;

                   } else {

                        ��[i].x=75;

                        ��[i].����=-1;

                   }

                   for (;;) {

                        ��[i].y=random(������)+1;

                        for (bFound=FALSE,j=0;j<������;j++) {

                             if (��[j].exist==TRUE && ��[j].y == ��[i].y) {

                                 bFound=TRUE;

                                 break;

                             }

                        }

                        if (bFound==FALSE) {

                             break;

                        }

                   }

                   ��[i].nFrame=��[i].nStay=random(6)+1;

                   ��[i].Type=random(sizeof(arEnemy)/sizeof(arEnemy[0]));

                   ��[i].exist=TRUE;

              }

		}

		//���� �̵��� ���(���� �ӵ��� ��������)

		for (i=0;i<������;i++) 
		{

              if (��[i].exist==FALSE) continue;

              if (--��[i].nStay == 0) {

                   ��[i].nStay=��[i].nFrame;

                   if (��[i].x >= 76 || ��[i].x <= 4) //�����϶� �����
				   {

                        ��[i].exist=FALSE;

                        gotoxy(��[i].x-3,��[i].y);

                        puts("       ");

                   }
				   else //���� �̵����
				   {

                        ��[i].x += ��[i].����;

                        gotoxy(��[i].x-3,��[i].y);

                        puts(arEnemy[��[i].Type]);

				   }

			  }

		}


		for (i=0;i<������;i++) {

              if (��[i].exist==FALSE) continue;

              if (��[i].y==fy && abs(��[i].x-fx) <= 2) {

                   gotoxy(fx-12,fy-1);puts("     �١ڡ١١١١ڡ�      ");

				   gotoxy(fx-12,fy);puts("     �١ڡٻ���١ڡ�      ");

				   gotoxy(fx-12,fy+1);puts("     �١ڡ١١١١ڡ�      ");

				   goto DIE;

              }

          }

		  if(fy==0)

			  goto end;
		  
		Sleep(10);//100������

	}

end:

	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(3,white); printf("                                                                              ");

	Sleep(50);

	}

	gotoxy(15,20);printf("������������������������������������������������");
	gotoxy(15,21);printf("��                �����մϴ�~~~~              ��");
	gotoxy(15,22);printf("��      ó������ ���ư��ðڽ��ϱ�?  (Y/N)     ��");
	gotoxy(15,23);printf("������������������������������������������������");
	
	key=getchar();

	if(key=='y')

		goto start;

	if(key=='n')

		return 0;

DIE:

	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(4,black); printf("                                                                              ");

	Sleep(50);

	}
	
	setcolor(4,15);gotoxy(15,20);printf("������������������������������������������������");
	setcolor(4,15);gotoxy(15,21);printf("��           �ٽ��ҷ�........??????           ��");
	setcolor(4,15);gotoxy(15,22);printf("��     ó������ ���ư��ðڽ��ϱ�?  (Y/N)      ��");
	setcolor(4,15);gotoxy(15,23);printf("������������������������������������������������");

	key=getchar();

	if(key=='y')

		goto start;

	if(key=='n')

		return 0;

	getchar();

} 

