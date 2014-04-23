#include<stdio.h>
#include<time.h>
#include<dos.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
union REGS in,out;
int c,mark[16][16],mark1[16][16],minx,miny,maxx,maxy,mines,grid,flag1,flag2=0,count,a[30][2],xpos=100,ypos=100,click;
char ch,ch1;
void callmouse()
{       in.x.ax=1;
	int86(51,&in,&out);
}
void mousepos(int &xpos,int &ypos,int &click)
{       in.x.ax=3;
	int86(51,&in,&out);
	click=out.x.bx;
	xpos=out.x.cx;
	ypos=out.x.dx;
}
void setpos(int x,int y)
{       in.x.ax=4;
	in.x.cx=x;
	in.x.dx=y;
	int86(51,&in,&out);
}
void hide()
{	in.x.ax=2;
	int86(51,&in,&out);
}
void restrict()
{       in.x.ax=7;
	in.x.cx=0;
	in.x.dx=640;
	int86(51,&in,&out);
	in.x.ax=8;
	in.x.cx=0;
	in.x.dx=640;
	int86(51,&in,&out);
}
void minegen()
{       count=0;
	randomize();
	while(count<mines)
	{	int p=minx+(rand()%(mines-1))*40;
		int q=miny+(rand()%(mines-1))*30;
		if(p<=maxx&&q<=maxy)
		{	for(int i=0;i<count ;i++)
				if(a[i][1]==p&&a[i][2]==q)
					goto end;
			a[count][1]=p;
			a[count][2]=q;
			count++;
//		printf("\n%d %d",p,q);//mines
		}
		end:
}	}
int check(int x,int y,int c)
{	for(int i=0;i<mines;i++)
		if(a[i][1]==x&&a[i][2]==y)
			c++;
	return(c);
}
int numgen(int x,int y,int c)
{	c=check(x-40,y,c);
	c=check(x-40,y-30,c);
	c=check(x-40,y+30,c);
	c=check(x,y-30,c);
	c=check(x,y+30,c);
	c=check(x+40,y,c);
	c=check(x+40,y-30,c);
	c=check(x+40,y+30,c);
	setfillstyle(SOLID_FILL,11);
	bar(x+7,y+7,x+33,y+23);
	setcolor(8);
	switch(c)
	{	case 0:outtextxy(x+15,y+10," ");break;
		case 1:outtextxy(x+15,y+10,"1");break;
		case 2:outtextxy(x+15,y+10,"2");break;
		case 3:outtextxy(x+15,y+10,"3");break;
		case 4:outtextxy(x+15,y+10,"4");break;
		case 5:outtextxy(x+15,y+10,"5");break;
		case 6:outtextxy(x+15,y+10,"6");break;
		case 7:outtextxy(x+15,y+10,"7");break;
		case 8:outtextxy(x+15,y+10,"8");break;
	}	return(c);

}
void game(int f);
void open(int x,int y)
{    if(x>=minx&&x<=maxx&&y>=miny&&y<=maxy)
     {  int c=0;
	if(mark[(x-minx)/40][(y-miny)/30]==1)
			mark1[(x-minx)/40][(y-miny)/30]=1;
	if(mark1[(x-minx)/40][(y-miny)/30]==0&&mark[(x-minx)/40][(y-miny)/30]==0)//correction made
	{	for(int i=0;i<mines;i++)
			if(a[i][1]==x&&a[i][2]==y)
			{ 	setcolor(5);
				setfillstyle(SOLID_FILL,10);
				for(int i=0;i<mines;i++)
				{      bar(a[i][1]+7,a[i][2]+7,a[i][1]+33,a[i][2]+23);
				       outtextxy(a[i][1]+12,a[i][2]+10,"$$");
				}
				settextstyle(TRIPLEX_FONT,0,4);
				setcolor(4);
				outtextxy(165,240,"$$$  YOU LOSE  $$$");
				game(0);
			}
		numgen(x,y,c);
		mark1[(x-minx)/40][(y-miny)/30]=1;
		if(numgen(x,y,c)==0)
		{   if(mark[(x-minx-40)/40][(y-miny)/30]!=1)
			open(x-40,y);
		    if(mark[(x-minx-40)/40][(y-miny-30)/30]!=1)
			open(x-40,y-30);
		    if(mark[(x-minx-40)/40][(y-miny+30)/30]!=1)
			open(x-40,y+30);
		    if(mark[(x-minx+40)/40][(y-miny)/30]!=1)
			open(x+40,y);
		    if(mark[(x-minx+40)/40][(y-miny-30)/30]!=1)
			open(x+40,y-30);
		    if(mark[(x-minx+40)/40][(y-miny+30)/30]!=1)
			open(x+40,y+30);
		    if(mark[(x-minx)/40][(y-miny-30)/30]!=1)
			open(x,y-30);
		    if(mark[(x-minx)/40][(y-miny+30)/30]!=1)
			open(x,y+30);
}   }	}	}
void flag(int x,int y,int f)
{    if(x>=minx&&x<=maxx&&y>=miny&&y<=maxy)
     {	if(mark[(x-minx)/40][(y-miny)/30]==0&&mark1[(x-minx)/40][(y-miny)/30]==0)
	{       mark[(x-minx)/40][(y-miny)/30]=1;
		mark1[(x-minx)/40][(y-miny)/30]=1;
		setfillstyle(SOLID_FILL,14);
		bar(x+7,y+7,x+33,y+23);
		outtextxy(x+15,y+10,"*");
		flag1--;
		for(int i=0;i<mines;i++)
		{	if(a[i][1]==x&&a[i][2]==y)
				flag2++;
	}	}
	else if(mark[(x-minx)/40][(y-miny)/30]==1)
	{       mark[(x-minx)/40][(y-miny)/30]=0;
		mark1[(x-minx)/40][(y-miny)/30]=0;
		setfillstyle(SOLID_FILL,15);
		bar(x+7,y+7,x+33,y+23);
		flag1++;
		for(int i=0;i<mines;i++)
		{	if(a[i][1]==x&&a[i][2]==y)
				flag2--;
	}	}		//printf("\n%d \t%d",flag1,flag2);
	if(flag2==mines&&flag1==0)
	{    	settextstyle(TRIPLEX_FONT,0,4);
		setcolor(4);
		outtextxy(165,240,"$$$  YOU  WON  $$$");
		game(f);
}    }	}
void main()
{	int gdriver=DETECT,gmode,errorcode;
	FILE *f;
	initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");
	setbkcolor(9);
	for(int k=0;k<25;k+=2)
	{	delay(70);
		ellipse(320,240,0,360,200+k+2,50);
	}
	settextstyle(GOTHIC_FONT,0,4);
	outtextxy(170,220,"MINE-RIDDANCER");
	delay(1000);
	restrict();
	callmouse();
	setpos(0,0);
a:	clearviewport();
	settextstyle(0,0,2);
	outtextxy(110,100,"BEGINNER: 9%9 GRID 10 MINES");
	outtextxy(85,190,"INTERMEDIATE:10%10 GRID 16 MINES");
	outtextxy(105,270,"ADVANCED: 13%13 GRID 30 MINES");
	outtextxy(10,410,"press F1 for game help");
	outtextxy(10,440,"press ESC to exit");
	rectangle(105,95,540,135);
	rectangle(80,185,600,225);
	rectangle(100,265,570,305);
	delay(100);
	do
	{       if(kbhit())
		{       clearviewport();
			if(getche()==27)
				exit(1);
			if(getche()==';')
			{	f=fopen("c:\\turboc3\\mr\\sp.txt","r");
				while((ch1=fgetc(f))!= EOF)
				printf("%c",ch1);
				printf("press any key to exit");
				getch();
			}
			goto a;
		}
		int t1=xpos,t2=ypos;
		mousepos(xpos,ypos,click);
		if(click==0)
			continue;
		if(xpos>105&&xpos<510&&ypos>95&&ypos<135&&click==1)
		{	minx=140;miny=120;mines=flag1=10;grid=9;
				break;
		}
		else if(xpos>80&&xpos<570&&ypos>185&&ypos<225&&click==1)
		{	minx=120;miny=110;flag1=mines=16;grid=10;
			break;
		}
		else if(xpos>100&&xpos<540&&ypos>265&&ypos<3055&&click==1)
		{	minx=60;miny=70;mines=flag1=30;grid=13;
			break;
		}
		printf("%d,%d",t1,t2);
		setpos(t1,t2);
	}while(1);
	setpos(0,0);
	clearviewport();
	maxx=minx+(grid-1)*40;
	maxy=miny+(grid-1)*30;
	setbkcolor(9);
	setcolor(8);//box colour
	for(int i=0;i<grid;i++)
		for(int j=0;j<grid;j++)
		{	rectangle(minx+i*40,miny+j*30,minx+(i+1)*40,miny+(j+1)*30);
			setfillstyle(SOLID_FILL,15);
			bar(minx+5+i*40,miny+5+j*30,minx+35+i*40,miny+25+j*30);
			rectangle(minx+5+i*40,miny+5+j*30,minx+35+i*40,miny+25+j*30);
		}
	settextstyle(TRIPLEX_FONT,0,5);
	setcolor(4);
	outtextxy(160,10,"MINE-RIDDANCER");
	settextstyle(DEFAULT_FONT,0,1);
	minegen();
	time_t a=time(NULL);
	do
	{       if(kbhit())
		{	if(getche()==27)
				exit(1);
		}
		int t1=xpos,t2=ypos;
		time_t b=time(NULL);
		gotoxy(5,3);
		printf("TIME: %d",(int)difftime(b,a)+1) ;
		mousepos(xpos,ypos,click);
		if(click==0)
			continue;
		hide();
		int x=minx+((xpos-minx)/40)*40;
		int y=miny+((ypos-miny)/30)*30;
		if(xpos>=minx&&ypos>=miny&&click==2)
			flag(x,y,(int)difftime(b,a));
		else if(xpos>=minx&&ypos>=miny&&click==1)
			open(x,y);
		callmouse();
		setpos(t1,t2);
		delay(100);
	}while(1);
}
void game(int f)
{	delay(2000);
	setpos(0,0);
	clearviewport();
	setbkcolor(9);
	outtextxy(200,200,"RESTART GAME");
	settextstyle(0,0,1);
	rectangle(250,260,300,280);
	outtextxy(265,265,"YES");
	rectangle(330,260,380,280);
	outtextxy(350,265,"NO");
	printf("YOUR TIME: %d",f);
	do
	{       callmouse();
		int m=xpos,n=ypos;
		mousepos(xpos,ypos,click);
		if(click==0)
			continue;
		if(xpos>250&&xpos<300&&ypos>260&&ypos<280&&click==1)
		{	for(int i=0;i<=grid;i++)
			{	for(int j=0;j<=grid;j++)
					mark[i][j]=mark1[i][j]=0;
				for(int k=0;k<2;k++)
					a[i][k]=0;
			}
			flag2=0;
			main();
		}
		else if(xpos>330&&xpos<380&&ypos>260&&ypos<280&&click==1)
			exit(1);
		setpos(m,n);
	}while(1);
}