#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void printMap(int n, int m, int map[n][m]){ //function for printing the map
	printf("\n");
	for(int i = 0; i < n;i++)
		printf("______");	
	
	printf("\n");
	
	for(int i = 0; i < n;i++){
		printf("|");
		
		for(int i = 0; i < n;i++)
			printf("     |");
		
		printf("\n|");
		
		for(int j = 0; j < m;j++){
			if(map[i][j] == -1)
				printf("     |");
			else if (map[i][j] == -10)
				printf("  *  |");
			else if (map[i][j] == -2)
				printf("  T  |");
			else
				printf(" D%d  |" , map[i][j]);
		}

	
		printf("\n|");
	
		for(int j = 0; j < n;j++)
			printf("_____|");
		
		printf("\n");
	}
}

int sign(int a , int b){ //comparing the cop and robber coordinates and then changing the cop position
	if(a > b) 
		return 1;
	if(a < b)
		return -1;
	return 0;
}

int main(){
	int x,y,countpolice=0,countrobber=0;
	
	printf ("Enter rows and columns : ");
	scanf ("%d%d",&x,&y);
	
	int car[x][y]; //car= Cops And Robber
	int station,police;
	
	printf ("Enter number of stations : ");
	scanf ("%d",&station);
	
	bool awareness[station];

	for (int i=0;i<station;i++){ //the walkie-talkie system between the cops in their stations
		awareness[i]=false;
	}
	
	srand(time(NULL));
	
	for (int i=0;i<x;i++){
		for (int j=0;j<y;j++){
		car [i][j]= -1;
		}
	}
	
	int robberx = rand()%x;
	int robbery = rand()%y;
	car[robberx][robbery] = -2;
	
	for (int i=0;i<station;i++){
	printf ("Enter number of police in sation (%d) : ",i);
	scanf ("%d",&police);
//	int sheriff[1000][1000][2];
	countpolice++;
		for (int j=0;j<police;j++){
			int randx = rand()%x;
			int randy = rand()%y;
			
			while (car[randx][randy] != -1){
				randx = rand()%x;
				randy = rand()%y;
			}
			car[randx][randy] = i;
		}
		
	}
	bool moved[x][y];
	bool wanted = false;

	while (wanted == false){ //chase game starts from here
		printMap(x,y,car);
		
		for (int i=0;i<station;i++){
		awareness[i]=false;
		}
		int backUpX = robberx;
		int backUpY = robbery;
		
		for (int i=-2;i<=2;i++){ //checking the area that the robber could be seen from
			for (int j=-2;j<=2;j++){
				if(i+robberx < x && i+robberx >= 0 && j+robbery < y && j + robbery >= 0)
					if (car[i+robberx][j+robbery] >= 0)
						awareness[car[i+robberx][j+robbery]] = true; 
			}
		}
		//moving the robber
		int randrx = rand()%3 -1;
		int randry = rand()%3 -1;
		
		while (robberx+randrx<0 || robberx+randrx>=x || robbery+randry<0 || robbery+randry>=y){
			randrx = rand()%3 -1;
			randry = rand()%3 -1;
		}
		car[robberx][robbery] = -1;
		robberx += randrx;
		robbery += randry;
		
		if (car[robberx][robbery] >= 0){
			wanted =true;
			car[robberx][robbery] = -10;
			continue;
		}
		else
			car[robberx][robbery] = -2;
		countrobber++;
		//moving cops
		int car2[x][y];
		for(int i = 0 ; i < x;i++){//making a copy of the original table for mthe moves
			for(int j = 0 ; j < y;j++){
				car2[i][j] = -1;
			}
		}
		for (int i=0;i<x;i++){
			for (int j=0;j<y;j++){
				if (car[i][j] >= 0){
					int changex;
					int changey;
					if (awareness[car[i][j]]){ //when the cops know where the robber is
						changex = sign(backUpX, i);
						changey = sign(backUpY, j);
						if(car2[changex+i][changey+j] >=0){ //if the cop couldnt do his best move, the cop will do another move
							if(changex == 0 && car2[i][j-1] < 0){
								changey = -1;
							}
							else if(changey == 0 && car2[i-1][j] < 0){
								changex = -1;
							}
							else if(changex == 0 && car2[i][j+1] < 0){
								changey = 1;
							}
							else if(changey == 0 && car2[i+1][j] < 0){
								changex = 1;
							}
							else if(car2[i+changex][j] < 0){
								changey = 0;
							}
							else if(car2[i][j+changey] < 0){
								changex = 0;
							}
							else{
								changex = 0;
								changey= 0;
							}
						}
						car2[changex+i][changey+j] = car[i][j];
						car[i][j] = -1;		
					}
					else{//when the cop doesnt know where the robber is
						changex = rand()%3 -1;
						changey = rand()%3 -1;	
						while (changex+i<0 || changex+i>=x || changey+j<0 || changey+j>=y || car[changex+i][changey+j] >= 0 || car2[changex+i][changey+j] != -1){
							changex = rand()%3 -1;
							changey = rand()%3 -1;
						}
						car2[changex+i][changey+j] = car[i][j];
						car[i][j] = -1;
					}
					if(car[changex+i][changey+j] == -2){//when a cop catches the robber
						car[changex+i][changey+j] = -10;
					}
				}
			}
		}
		for (int i=0;i<x;i++){//copy the table to the original table
			for (int j=0;j<y;j++){
				if (car[i][j] != (-2) && car[i][j] != -10){
					car[i][j] = car2[i][j];
				}
			}
		}
		for(int i=0;i<x;i++){
			for(int j=0;j<y;j++){
				if(car[i][j] == -10){
					wanted =true;
					car[robberx][robbery] = -10;
					continue;
				}
			}
		}
		Sleep(1000);
		system("cls");
	}
	system("cls");
	printMap(x,y,car);
	printf("Number of police movements: %d\nNumber of robber movements: %d\n" ,countpolice*countrobber,countrobber);
}
