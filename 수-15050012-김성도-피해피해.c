#pragma warning(disable:4996)
#include <stdio.h> 
#include <windows.h> 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


//색지정
#define black			0
#define dark_green		2	//	 BLACK,			0 : 까망 				 DARK_BLUE,      1 : 어두운 파랑 
#define dark_red		4
#define dark_yellow		6	//	 DARK_GREEN,    2 : 어두운 초록 		 DARK_SKY_BLUE,  3 : 어두운 하늘
#define dark_gray		8 
#define dark_blue		1	//	 DARK_RED,      4 : 어두운 빨강 		 DARK_VIOLET,    5 : 어두운 보라
#define dark_sky_blue	3
#define dark_violet		5	//	 DARK_YELLOW,   6 : 어두운 노랑			 GRAY,			 7 : 회색 
#define green			10
#define red				12 	//	 DARK_GRAY,     8 : 어두운 회색 		 BLUE,			 9 : 파랑 
#define yellow			14	 
#define gray			7	//	 GREEN,			10 : 초록 				 SKY_BLUE,		 11 : 하늘 
#define blue			9
#define sky_blue		11	//	 RED,			12 : 빨강				 VIOLET,		 13 : 보라
#define violet			13
#define white			15	//	 YELLOW,		14 : 노랑 				 WHITE,			 15 : 하양



//방향키 지정//
#define Up 72
#define Down 80
#define Right 77
#define Left 75
#define ESC 27
#define 적갯수 38


//자주쓰는 함수 지정//
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
#define randomize() srand((unsigned)time(NULL))	//난수발생을 초기화한다.
#define random(n) (rand() % (n))  //0~n까지 난수를 생성해준다.




////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

//쓰고싶은함수 추가//
void setcolor(int bgcolor, int color) // 배경,글자색

{

     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) <<4) | color);

}

// 커서의 y좌표를 조사한다.
int wherex()

{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);

	return BufInfo.dwCursorPosition.X;
}

// 커서의 y좌표를 조사한다.
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);

	return BufInfo.dwCursorPosition.Y;
}
void setcursortype(CURSOR_TYPE c)//커서를 숨긴다.
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

void 지우개()//화면을 지운다

{

	system("cls");

}

void gotoxy(int x,int y)

{

     COORD Cur;

     Cur.X=x;

     Cur.Y=y;

     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);//커서를 원하는위치로변경해주는명령어

}

 struct tag_Enemy

{

     BOOL exist;

     int Type;

     int x,y;

     int 방향;//1=왼쪽시작, -1=오른쪽시작.

     int nFrame;

     int nStay;

} 적[적갯수];

 BOOL 누른키(int Key)

{

     return ((GetAsyncKeyState(Key) & 0x8000) != 0);

}

 void 네모칸()
 {
	 gotoxy(15,2);printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	 gotoxy(15,3);printf("┃                                                          ┃");
	 gotoxy(15,4);printf("┃                                                          ┃");
	 gotoxy(15,5);printf("┃                                                          ┃");
	 gotoxy(15,6);printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////////////////////

char *arEnemy[]={" (>_<) "," (o_o) ", " (O@O) ", " (-=-) "};  //적의 모양

int fx,fy;

int 배경색;

int 난이도;

int main()

{

	////////////////변수 선언////////////////

	char key;

	int count;

	int i,j;

	int 색;

	BOOL bFound;   //불로지정한건 있나 없나만 판별하기 때문임(T/F)

	int y=5;

	int 글씨=0;

	int temp;
	



	start:
	for(i=0;i<64;i++)

	{

	gotoxy(0,i);

	setcolor(black,white); printf("                                                                              ");


	}
	fx=40;//초기 위치지정

	fy=43;//초기 위치지정

	setcursortype(NOCURSOR);//커서 없애기

	randomize();

	system("mode con: cols=78 lines=46");

	gotoxy(30,6);

	printf("★★★피해피해!!★★★");

	gotoxy(10,10);printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(10,11);printf("┃                       ※설명서※                         ┃");
	gotoxy(10,12);printf("┃                                                          ┃");
	gotoxy(10,13);printf("┃   이 게임은 움직일수 있는 ★★ 이 물체를 옮기면서        ┃");
	gotoxy(10,14);printf("┃   움직이는 적들을 닿지 않고 최종 목적지(맨위)까지        ┃");
	gotoxy(10,15);printf("┃   가는 게임입니다.                                       ┃");
	gotoxy(10,16);printf("┃                                                          ┃");
	gotoxy(10,17);printf("┃   재미있게 플레이해주세요~                               ┃");
	gotoxy(10,18);printf("┃                                                          ┃");
	gotoxy(10,19);printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
 
	gotoxy(54,43);

	printf("15050012 김성도");
	for(temp=0;;temp++)
	{
	
	if (kbhit())

		{

		key=getch();

		if (key==0xE0 || key==0) 

			getch();

		if(!(key==1234598172516))//이런키는 없기때문에..(나쁜방법)

		break;

		}
	

	gotoxy(17,40);
	
	if(temp%2==0)

		setcolor(0,15);printf("■□■□■시작하려면 아무키나 쳐주세요!!■□■□■");

	gotoxy(17,40);

	if(temp%2==1)

		setcolor(0,0);printf("■□■□■시작하려면 아무키나 쳐주세요!!■□■□■");

	Sleep(700);
	}
	


	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(15,0); printf("                                                                              ");

	Sleep(50);

	}

	//메뉴
	gotoxy(15,2);printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(15,3);printf("┃                 배경색을 지정해주세요                    ┃");
	gotoxy(15,4);printf("┃                                                          ┃");
	setcolor(15,0);gotoxy(15,5);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,6);printf("                                                          ");
	setcolor(15,1);gotoxy(15,7);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,8);printf("                                                          ");
	setcolor(15,2);gotoxy(15,9);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,10);printf("                                                          ");
	setcolor(15,3);gotoxy(15,11);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,12);printf("                                                          ");
	setcolor(15,4);gotoxy(15,13);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,14);printf("                                                          ");
	setcolor(15,5);gotoxy(15,15);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,16);printf("                                                          ");
	setcolor(15,6);gotoxy(15,17);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,18);printf("                                                          ");
	setcolor(15,7);gotoxy(15,19);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,20);printf("                                                      ");
	setcolor(15,8);gotoxy(15,21);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,22);printf("                                                          ");
	setcolor(15,9);gotoxy(15,23);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,24);printf("                                                          ");
	setcolor(15,10);gotoxy(15,25);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,26);printf("                                                          ");
	setcolor(15,11);gotoxy(15,27);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,28);printf("                                                          ");
	setcolor(15,12);gotoxy(15,29);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,30);printf("                                                          ");
	setcolor(15,13);gotoxy(15,31);printf("                           ■■■■■■■■■■■    ");
	gotoxy(15,32);printf("                                                          ");
	setcolor(15,14);gotoxy(15,33);printf("                           ■■■■■■■■■■■    ");
	setcolor(15,0);gotoxy(15,34);printf("┃                                                          ┃");
	gotoxy(15,35);printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(15,37);printf("고르신 후 a를 두번 눌러주세요");

	while(1)

	{

	gotoxy(23,y);

	printf("☆");

	getch();

	key=getch();

	if(key=='a')

		break;

	if (누른키(VK_UP)) 

		if (y > 5) 

		{
			y=y-2;

			gotoxy(23,y+2);

			printf("  ");

		}

	
	if (누른키(VK_DOWN)) 

		if (y < 33) 

		{
			y=y+2;

			gotoxy(23,y-2);

			printf("  ");
		}
		
	}

	색=(y-5)/2;

	if(색==0);

	글씨=15;

	//배경색 바꾸기
	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(색,글씨); printf("                                                                              ");

	Sleep(50);

	}

	//글씨색 설정

	for(temp=0;;temp++)

	{

	setcolor(색,글씨);gotoxy(10,2);printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	setcolor(색,글씨);gotoxy(10,3);printf("┃         글씨색을 고르세요 (방향키를 이용해서 변경)       ┃");
	setcolor(색,글씨);gotoxy(10,4);printf("┃                                                          ┃");
	setcolor(색,글씨);gotoxy(10,5);printf("┃             흰색                        검정             ┃");
	setcolor(색,글씨);gotoxy(10,6);printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	setcolor(색,글씨);gotoxy(10,8);printf("고르셨으면 a를 두번 쳐주세요");

	getch();

	key=getch();

	if(key=='a')

		break;

	if(temp%2==0)

		글씨=0;

	else

		글씨=15;

	}

	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(색,글씨); printf("                                                                              ");

	}
	fflush(stdin);
	setcolor(색,글씨);gotoxy(10,2);printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	setcolor(색,글씨);gotoxy(10,3);printf("┃                  난이도를 설정해주세요                   ┃");
	setcolor(색,글씨);gotoxy(10,4);printf("┃                                                          ┃");
	setcolor(색,글씨);gotoxy(10,5);printf("┃         [초급]           중급            고급            ┃");
	setcolor(색,글씨);gotoxy(10,6);printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	setcolor(색,글씨);gotoxy(10,8);printf("고르셨으면 a를 두번 쳐주세요");






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

	{setcolor(색,글씨);gotoxy(10,5);printf("┃         [초급]           중급            고급            ┃");난이도=30;}

	if(temp==1)

	{setcolor(색,글씨);gotoxy(10,5);printf("┃          초급           [중급]           고급            ┃");난이도=15;}

	if(temp==2)

	{setcolor(색,글씨);gotoxy(10,5);printf("┃          초급            중급           [고급]           ┃");난이도=3;}
	 

	}


	system("cls");




	//////////////////////게임소스///////////////////////////
	for (count=0;;count++)

	{

		if (count % 5 == 0)//초당 최대 20회 움직인다

		{

		if (누른키(VK_LEFT)) 

			if (fx > 4) fx--;

        if (누른키(VK_RIGHT)) 

			if (fx < 73) fx++;

		if (누른키(VK_UP)) 

			fy--;

		if (누른키(VK_DOWN)) 

			if (fy < 41) fy++;

		}



		if (kbhit())

		{

		key=getch();

		if (key==0xE0 || key==0) 

			getch();

		}
		

		
		gotoxy(fx-2,fy-1);	puts("      ");

		gotoxy(fx-3,fy);    puts(" ★★ ");//지나가는 동물

		gotoxy(fx-2,fy+1);  puts("      ");

		gotoxy(0,42); printf("==============================================================================");
		gotoxy(0,0); printf("▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣");

		//적군생성
		if (random(난이도) == 0) {

              for (i=0;i<적갯수 && 적[i].exist==TRUE;i++) {;}

              if (i != 적갯수) {

                   if (random(4)==1) {//왼쪽과 오른쪽에서 나오는것을 확인해줌

                        적[i].x=5;

                        적[i].방향=1;

                   } else {

                        적[i].x=75;

                        적[i].방향=-1;

                   }

                   for (;;) {

                        적[i].y=random(적갯수)+1;

                        for (bFound=FALSE,j=0;j<적갯수;j++) {

                             if (적[j].exist==TRUE && 적[j].y == 적[i].y) {

                                 bFound=TRUE;

                                 break;

                             }

                        }

                        if (bFound==FALSE) {

                             break;

                        }

                   }

                   적[i].nFrame=적[i].nStay=random(6)+1;

                   적[i].Type=random(sizeof(arEnemy)/sizeof(arEnemy[0]));

                   적[i].exist=TRUE;

              }

		}

		//몹의 이동과 출력(몹의 속도도 랜덤으로)

		for (i=0;i<적갯수;i++) 
		{

              if (적[i].exist==FALSE) continue;

              if (--적[i].nStay == 0) {

                   적[i].nStay=적[i].nFrame;

                   if (적[i].x >= 76 || 적[i].x <= 4) //움직일때 지우기
				   {

                        적[i].exist=FALSE;

                        gotoxy(적[i].x-3,적[i].y);

                        puts("       ");

                   }
				   else //몹의 이동출력
				   {

                        적[i].x += 적[i].방향;

                        gotoxy(적[i].x-3,적[i].y);

                        puts(arEnemy[적[i].Type]);

				   }

			  }

		}


		for (i=0;i<적갯수;i++) {

              if (적[i].exist==FALSE) continue;

              if (적[i].y==fy && abs(적[i].x-fx) <= 2) {

                   gotoxy(fx-12,fy-1);puts("     ☆★☆☆☆☆★☆      ");

				   gotoxy(fx-12,fy);puts("     ☆★☆사망☆★☆      ");

				   gotoxy(fx-12,fy+1);puts("     ☆★☆☆☆☆★☆      ");

				   goto DIE;

              }

          }

		  if(fy==0)

			  goto end;
		  
		Sleep(10);//100프레임

	}

end:

	for(i=0;i<46;i++)

	{

	gotoxy(0,i);

	setcolor(3,white); printf("                                                                              ");

	Sleep(50);

	}

	gotoxy(15,20);printf("┏━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(15,21);printf("┃                축하합니다~~~~              ┃");
	gotoxy(15,22);printf("┃      처음으로 돌아가시겠습니까?  (Y/N)     ┃");
	gotoxy(15,23);printf("┗━━━━━━━━━━━━━━━━━━━━━━┛");
	
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
	
	setcolor(4,15);gotoxy(15,20);printf("┏━━━━━━━━━━━━━━━━━━━━━━┓");
	setcolor(4,15);gotoxy(15,21);printf("┃           다시할래........??????           ┃");
	setcolor(4,15);gotoxy(15,22);printf("┃     처음으로 돌아가시겠습니까?  (Y/N)      ┃");
	setcolor(4,15);gotoxy(15,23);printf("┗━━━━━━━━━━━━━━━━━━━━━━┛");

	key=getchar();

	if(key=='y')

		goto start;

	if(key=='n')

		return 0;

	getchar();

} 

