//============================================================================
// Name        : RPG.cpp
// Author      : YuTing-Lai
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <utility>
#include <cstdlib>
using namespace std;

char map[15][15];
pair<int,int> K_pos, M_pos, m_pos, R_pos, r_pos, B_pos;
int K_exist, m_exist, M_exist, R_exist, r_exist, B_exist, T_exist;
int stage;


void printMap(){
	for(int i=1; i<=10; i++){
		for(int j=1; j<=10; j++){
			printf("%c ", map[i][j]);
			if(j==10)
				printf("\n");
		}
	}
}

void setMap(){
	//set the bound of the map
	memset(map,'*',225);
	for(int i=2; i<=9; i++){
		for(int j=2; j<=9; j++){
			map[i][j]=' ';
		}
	}

	//set the trees
	for(int i=0; i<15; i++){
		int x= rand()%8+2;
		int y =rand()%8+2;
		map[x][y] = '#';
	}

	//set the chests
	int chest=0;
	while(chest<2){
		int x= rand()%8+2;
		int y =rand()%8+2;
		if(map[x][y]==' '){
			map[x][y] = '?';
			chest++;
		}
	}

	//set the monsters
	int monster=0;
	while(monster<stage+1){
		int x= rand()%8+2;
		int y =rand()%8+2;
		if(map[x][y] == ' '){
			if(monster==0){
				map[x][y]='M';
				M_exist=1;
			}
			else if(monster==1){
				map[x][y]='m';
				m_exist=1;
			}
			else if(monster==2){
				map[x][y]='R';
				R_exist=1;
			}
			else if(monster==3){
				map[x][y]='r';
				r_exist=1;
			}
			else if(monster==4){
				map[x][y]='B';
				B_exist=1;
			}
			monster++;
		}
	}

	//set the main character
	int MC=0;
	while(MC<1){
		int x= rand()%8+2;
		int y =rand()%8+2;
		if(map[x][y]==' '){
			map[x][y] = 'K';
			MC++;
		}
	}
}

void findAllPosition(){
	int pos;
	for(pos=0; pos<100; pos++){
		if(map[pos/10+1][pos%10+1] == 'K'){
			K_pos.first = pos/10+1;
			K_pos.second = pos%10+1;
		}
	}

	for(pos=0; pos<100; pos++){
		if(map[pos/10+1][pos%10+1] == 'M'){
			M_pos.first = pos/10+1;
			M_pos.second = pos%10+1;
		}
	}

	for(pos=0; pos<100; pos++){
		if(map[pos/10+1][pos%10+1] == 'm'){
			m_pos.first = pos/10+1;
			m_pos.second = pos%10+1;
		}
	}

	for(pos=0; pos<100; pos++){
		if(map[pos/10+1][pos%10+1] == 'R'){
			R_pos.first = pos/10+1;
			R_pos.second = pos%10+1;
		}
	}

	for(pos=0; pos<100; pos++){
		if(map[pos/10+1][pos%10+1] == 'r'){
			r_pos.first = pos/10+1;
			r_pos.second = pos%10+1;
		}
	}

	for(pos=0; pos<100; pos++){
		if(map[pos/10+1][pos%10+1] == 'B'){
			B_pos.first = pos/10+1;
			B_pos.second = pos%10+1;
		}
	}
}

void openChest(){
	int x = rand()%2;
	if(x){
		K_exist++;
		cout << "You get an extra life! Your life now is " << K_exist << endl;
	}
	else{
		cout << "Nothing inside..." << endl;
	}
}

void myMovement(int x, int y){

	switch(map[x][y]){
		case '#':
			//cut the tree
			cout << "You cut the tree!" << endl;
			map[x][y] = ' ';
			break;
		case '*':
			//the stone bound
			printf("You stuck! It is the stone!\n");
			break;
		case ' ':
			//move to here
			map[K_pos.first][K_pos.second] = ' ';
			K_pos.first = x; K_pos.second = y;
			map[x][y] = 'K';
			break;
		case 'm':
			cout << "You killed the melee." << endl;
			m_exist=0;
			map[x][y] = ' ';
			break;
		case 'M':
			cout << "You killed the Melee." << endl;
			M_exist=0;
			map[x][y] = ' ';
			break;
		case 'R':
			cout << "You killed the Ranger." << endl;
			R_exist=0;
			map[x][y]= ' ';
			break;
		case 'r':
			cout << "You killed the ranger." << endl;
			r_exist=0;
			map[x][y]= ' ';
			break;
		case 'B':
			cout << "You killed the Boss!!!" << endl;
			B_exist=0;
			map[x][y]= ' ';
			break;
		case '?':
			cout << "Find a treasure!" << endl;
			openChest();
			map[x][y] = ' ';
			break;
		case 'O':
			stage++;
			if(stage == 5){
				cout << "You win !!!" << endl;
				T_exist=0;
				break;
			}
			cout << "Stage " << stage << endl;
			setMap();
			findAllPosition();
			T_exist=0;
			break;
	}

}

void monsterMovement(char name, int x, int y){
	pair<int,int> *temp;

	switch(name){
		case 'M':
			temp = &M_pos;
			break;
		case 'm':
			temp = &m_pos;
			break;
		case 'R':
			temp = &R_pos;
			break;
		case 'r':
			temp = &r_pos;
			break;
		case 'B':
			temp = &B_pos;
			break;
	}


	switch(map[x][y]){
		case ' ':
			//move to here
			map[temp->first][temp->second] = ' ';
			temp->first = x; temp->second = y;
			map[x][y] = name;
			break;
		case '?':
			cout << name << " steal the chest !" << endl;
			map[x][y] = ' ';
			break;
		default:
			break;
	}

}

void myMove(char dir){
	switch (dir) {
		case 'u':
			myMovement(K_pos.first-1, K_pos.second);
			break;
		case 'd':
			myMovement(K_pos.first+1, K_pos.second);
			break;
		case 'l':
			myMovement(K_pos.first, K_pos.second-1);
			break;
		case 'r':
			myMovement(K_pos.first, K_pos.second+1);
			break;
	}



}

bool monsterNear(char name){
	int role;
	pair<int, int> *melee, *range;

	switch(name){
		case 'M':
			melee = &M_pos;
			role=1;
			break;
		case 'm':
			melee = &m_pos;
			role=1;
			break;
		case 'R':
			range = &R_pos;
			role=2;
			break;
		case 'r':
			range = &r_pos;
			role=2;
			break;
		case 'B':
			melee = &B_pos;
			role=1;
			break;
	}

	if(role==1){
		if(melee->first == K_pos.first){
			if(abs(melee->second - K_pos.second) == 1)
				return true;
		}
		else if(melee->second == K_pos.second){
			if(abs(melee->first - K_pos.first) == 1){
				return true;
			}
		}
	}
	else if(role==2){
		if(range->first == K_pos.first){
			if(abs(range->second - K_pos.second) < 4){
				return true;
			}
		}
		else if(range->second == K_pos.second){
			if(abs(range->first - K_pos.first) < 4){
				return true;
			}
		}
	}



	return false;
}

void monsterMove(){
	if(M_exist){
		if(monsterNear('M')){
			cout << "M attacked you !" << endl;
			K_exist--;
			cout << "Your life now is " << K_exist << endl;
		}
		else{
			char dir = rand()%4 + '0';
			switch (dir) {
				case '0':
					monsterMovement('M', M_pos.first-1, M_pos.second);
					break;
				case '1':
					monsterMovement('M', M_pos.first+1, M_pos.second);
					break;
				case '2':
					monsterMovement('M', M_pos.first, M_pos.second-1);
					break;
				case '3':
					monsterMovement('M', M_pos.first, M_pos.second+1);
					break;
			}
		}

	}

	if(m_exist){
		if(monsterNear('m')){
			cout << "m attacked you !" << endl;
			K_exist--;
			cout << "Your life now is " << K_exist << endl;
		}
		else{
			char dir = rand()%4 + '0';
			switch (dir) {
				case '0':
					monsterMovement('m', m_pos.first-1, m_pos.second);
					break;
				case '1':
					monsterMovement('m', m_pos.first+1, m_pos.second);
					break;
				case '2':
					monsterMovement('m', m_pos.first, m_pos.second-1);
					break;
				case '3':
					monsterMovement('m', m_pos.first, m_pos.second+1);
					break;
			}
		}

	}

	if(R_exist){
		if(monsterNear('R')){
			cout << "R shot you !" << endl;
			K_exist--;
			cout << "Your life now is " << K_exist << endl;
		}
		else{
			char dir = rand()%4 + '0';
			switch (dir) {
				case '0':
					monsterMovement('R', R_pos.first-1, R_pos.second);
					break;
				case '1':
					monsterMovement('R', R_pos.first+1, R_pos.second);
					break;
				case '2':
					monsterMovement('R', R_pos.first, R_pos.second-1);
					break;
				case '3':
					monsterMovement('R', R_pos.first, R_pos.second+1);
					break;
			}
		}

	}

	if(r_exist){
		if(monsterNear('r')){
			cout << "r shot you !" << endl;
			K_exist--;
			cout << "Your life now is " << K_exist << endl;
		}
		else{
			char dir = rand()%4 + '0';
			switch (dir) {
				case '0':
					monsterMovement('r', r_pos.first-1, r_pos.second);
					break;
				case '1':
					monsterMovement('r', r_pos.first+1, r_pos.second);
					break;
				case '2':
					monsterMovement('r', r_pos.first, r_pos.second-1);
					break;
				case '3':
					monsterMovement('r', r_pos.first, r_pos.second+1);
					break;
			}
		}

	}

	if(B_exist){
		//Boss can move twice
		for(int i=0; i<2; i++){
			if(monsterNear('B')){
				cout << "The Boss attacked you !" << endl;
				K_exist--;
				cout << "Your life now is " << K_exist << endl;
			}
			else{
				char dir = rand()%4 + '0';
				switch (dir) {
					case '0':
						monsterMovement('B', B_pos.first-1, B_pos.second);
						break;
					case '1':
						monsterMovement('B', B_pos.first+1, B_pos.second);
						break;
					case '2':
						monsterMovement('B', B_pos.first, B_pos.second-1);
						break;
					case '3':
						monsterMovement('B', B_pos.first, B_pos.second+1);
						break;
				}
			}
		}




	}

}

void setTransport(){
	int T=0;
	while(T<1){
		int x= rand()%8+2;
		int y =rand()%8+2;
		if(map[x][y]==' '){
			map[x][y] = 'O';
			T++;
		}
	}
	T_exist=1;
}

int main() {
	stage =1;
	K_exist=1;

	srand(time(NULL));
	cout << "Stage 1" << endl;
	setMap();
	printMap();
	findAllPosition();

	char move;
	cin>>move;
	while(stage != 5){


		if(move=='u' || move=='d' || move=='l' || move=='r'){
			myMove(move);
			monsterMove();
			if(M_exist==0 && m_exist==0 && R_exist==0 && r_exist==0 && T_exist==0 && B_exist==0){
				cout << "You can move to the next stage." << endl;
				setTransport();
			}
			printMap();
		}
		else{
			printf("Input 'u' or 'd' or 'l' or 'r' please.\n");
		}

		if(K_exist<=0){
			map[K_pos.first][K_pos.second] = 'X';
			cout << "You lose" << endl;
			break;
		}

		while(T_exist==1){
			cin >> move;
			if(move=='u' || move=='d' || move=='l' || move=='r'){
				myMove(move);
				printMap();
			}
			else{
				printf("Input 'u' or 'd' or 'l' or 'r' please.\n");
			}
		}
		if(stage==5){
			break;
		}
		cin>>move;
	}

	return 0;
}
