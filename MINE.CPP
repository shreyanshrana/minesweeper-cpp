//Shreyansh

//Basic Minesweeper v1.1.1.1.1.1.1.1
#include<iostream.h>
#include<iomanip.h>
#include<stdio.h>
#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

time_t start,end;
char board_show[6][6],board_play[6][6];
int board_values[6][6] = {0};
int No_of_flag = 9, Correct_flag = 9;
int tries = 1;
double ttaken;



class highscore{
char name[20];															//User Name
int ttries;																//Total Tries
double timetaken;														//Total Time-taken

public:
void enterhigh()
{
cout<<"\nPlease enter your name:";
gets(name);
timetaken=ttaken;
ttries=tries;
}
void showhigh()
{
cout<<"\nName : "<<name<<"\nTime Taken : "<<timetaken<<" seconds"<<"\nTries = "<<ttries;
}};

void Input();
void DrawBoard(char board_disp[6][6]);
void CreateBoard ();
void OpenMine(int x_index,int y_index);
void FlagMine(int x_index,int y_index);
void RemoveFlag(int x_index,int y_index);
void GameOver();
void GameWon();
void Help();

void Header();
void Intro();
void writehigh();
void displayhigh();

void main()
{
    int start_x,start_y;
    char menu;
    CreateBoard();
    Intro();
    for(;;)
    {
	clrscr();
	Header();
	cout<<"Welcome To Minesweeper v1.1.1.1\n";
	cout<<"1. Play Minesweeper\n\n2. Rules\n\n3. Hall Of Fame\n\n4. Exit :\n";
	menu=getch();
	switch(menu)
	    {
	    case '1' :
			DrawBoard(board_show);
			cout<<"Make the starting guess : ";
				cout<<endl<<"X : ";               //Opposite Convention
			cin>>start_y;
			cout<<endl<<"Y : ";
			cin>>start_x;
			DrawBoard(board_play);
			OpenMine(start_x-1,start_y-1);
			start=time(NULL);
			Input();
			break;
	    case '2' :
			Help();
			break;
	    case '3' :
			displayhigh();
		    break;
	    case '4' :
			exit(0);
			break;
	    default :
			cout<<"Please Enter Correctly.. ";
	    }
    }



}

void DrawBoard(char board_disp[6][6])
{
    clrscr();
    Header();
    cout<<endl<<endl<<endl;
    for(int i=0;i<6;i++)
    {
	cout<<setw(10);
	for(int j=0;j<6;j++)
	{
	    cout<<setw(1)<<board_disp[i][j]<<" ";
	    if(i==0&&j==5)
		cout<<setw(50)<<"No Of Tries = "<<tries;
	    if(i==1&&j==5)
		cout<<setw(50)<<"No Of Flags Remaining = "<<No_of_flag;
	}
	cout<<"\n\n";
    }
}

void CreateBoard ()
{
    int a = 1,x,y;
    for(int i = 0;i<6;i++)
    {
	for(int j=0;j<6;j++)
	    {
		board_play[i][j] = 48;
		board_show[i][j] = 219;
	    }
    }
    randomize();
    while(a<=9)
    {
    x = rand() % 6 + 1;
    y = rand() % 6 + 1;
    if(x<=5 && x>=0 && y<=5 && y>=0 && board_play[x][y] != 15)
     {
	board_play[x][y] = 15;
	a++;
     }
    }

    for(i=0;i<6;i++)                    //Fill Neighbours in board
    {
	for(int j=0;j<6;j++)
	{
	    if(board_play[i][j]!=15)
	    {
		for(int i1=i-1;i1<=i+1;i1++)
		{
		    for(int j1=j-1;j1<=j+1;j1++)
		    {
			if(board_play[i1][j1]==15 && 0<=i1 && 0<=j1 &&i1<=5 && j1<=5)
			    board_values[i][j]++;
		    }
		}
		board_play[i][j]=board_values[i][j] + 48; //ASCII (48) == 0

	    }
	}
    }
    DrawBoard(board_play);
}

void Input()
{
    int x,y,x_index,y_index;
    char input;
    do
    {
	cout <<endl<<"Mode : (o - open, f - flag, r - remove flag) - ";
	cin>>input;
	cout<<endl<<"X - ";         //Opposite Convention
	cin>>y;
	cout<<endl<<"Y - ";
	cin>>x;
	tries++;
	x_index = x - 1;
	y_index = y - 1;
	if(x>6 || y>6 || x<1 || y<1)
	    continue;
	switch (input)
	    {
	    case 'o'  :
		OpenMine(x_index,y_index);
		break;
	    case 'f' :
		FlagMine (x_index, y_index);
		break;
	    case 'r' :
		RemoveFlag (x_index, y_index);
		break;
	    default:
		cout<<endl<<"Enter correct output.. \n";

	    }
    }while(input != 81);
}

void OpenMine(int x_index,int y_index)
{
    if(board_play[x_index][y_index]!=15 && board_show[x_index][y_index]!= 70)
    {
	for(int i=x_index-1;i<=x_index+1;i++) //Open and show surroundings
	{
	    for(int j=y_index-1;j<=y_index+1;j++)
	    {
		if(board_play[i][j]!=15)
		    board_show[i][j]=board_play[i][j];
	    }
	}
    DrawBoard(board_show);
    }
    else if(board_play[x_index][y_index]==15)
	GameOver();
}

void FlagMine(int x_index,int y_index)
{
    if((board_show[x_index][y_index] < 48 || board_show[x_index][y_index] > 56) && No_of_flag > 0 )
{
	board_show[x_index][y_index] = 70;
	No_of_flag--;
	if(board_play[x_index][y_index] == 15)
	   Correct_flag--;

	if (Correct_flag == 0)
	   GameWon();
	else
	    DrawBoard(board_show);
}
}

void RemoveFlag(int x_index,int y_index)
{
    if(board_show[x_index][y_index] == 70)
{
	board_show[x_index][y_index] = 219;
	No_of_flag++;

	if(board_play[x_index][y_index] == 15)
	   Correct_flag++;

}
    DrawBoard(board_show);
}

void GameOver()
{
     for(int i=0;i<6;i++)                    //Show All Mines
    {
	for(int j=0;j<6;j++)
	{
	    if(board_play[i][j]==15)
		board_show[i][j] = 15;
	}
    }
    DrawBoard(board_show);
    cout<<setw(40)<<"You Lose";
    getch();
    exit(0);
}

void GameWon()

{   end=time(NULL);
 cout<<setw(55)<<endl<<"You Won in "<<tries<<" tries";

 ttaken=end-start;
cout<<setw(55)<<"\nTime taken:"<<ttaken<<" seconds";
    writehigh();
    cout<<"\n\nCongratulations ! You have been added to our 'Hall Of Fame'. ";
    exit(0);
}



void writehigh()
{
fstream f;
highscore high;
f.open("highscore.txt",ios::app);
high.enterhigh();
f.write((char*)&high,sizeof(high));
f.close();
cout<<"\n\nPress enter to continue.....";
    getch();

}
void displayhigh()
{
fstream f;
highscore high;
f.open("highscore.txt",ios::in);
clrscr();
Header();
cout<<"The following are the users who successfully completed the game : \n";
while(f.read((char*)&high,sizeof(high)))
{
high.showhigh();
cout<<endl;
}
f.close();
 cout<<"\n\nPress enter to continue.....";
    getch();

}

void Help()
{
     clrscr();
	    cout<<setw(55)<<"Rules for minesweeper:\n";
	    cout<<"1. You are in a mine field and you have to successfully flag all the places which have a mine. If you flag all the mines, You win!\n";
	    cout<<"2.In your first turn, you have to choose a starting square. You can open a square by entering its row number(x) and column number(y)\n(Note: row and column number starts from 1)\n";
	    cout<<"3.There are three modes of operation:\n";
	    cout<<"(i) open mode. type 'o' in mode option. This mode lets the user to open a square";
	    cout<<"(ii) flag mode. type 'f' in mode option. This mode lets the user to flag a particular square. Flagged square is denoted by an 'F'\n";
	    cout<<"(iii) remove flag mode. type 'r' in mode option. This mode lets the user to remove a particular flag from a flagged square\n";
	    cout<<"4.If you open a square with a mine, you lose\n";
	    cout<<"5.If you open a square with a number written on it. The number shows that how many mines are there in the adjacent 8 squares\n";
	    cout<<"For eg:\n"<<char(219)<<" "<<char(219)<<" "<<char(219)<<"\n\n"<<char(219)<<" 4 "<<char(219)<<"\n\n"<<char(219)<<" "<<char(219)<<" "<<char(219);
	    cout<<"\nHere 4 denoted that there are 4 mines in the remaining uncovered squares";
	    cout<<"\n\nPress enter to continue.....";
	    getch();
}



void Header()															
{
	cout<<"================================================================================";
	cout<<"                                   MINESWEEPER                                  ";
	cout<<"================================================================================";
}

void Intro()
{
    clrscr();
    cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<setw(45)<<"Shreyansh";
    cout<<endl<<setw(40)<<"Class XII E";
    getch();
}
