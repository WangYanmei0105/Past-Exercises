
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
using namespace std;
int* testfunc(int data[3][3]){
    data[0][0]=1;
    return &data[0][0];
}


void new_map(double map[5][5]){
    for (int j=0; j<5; j++){
        for (int i=0; i<5; i++) {
            map[j][i]=0;
        }
    }
    
    int count=-1;
    srand((int)time(NULL));
    for (int i=0; i<7; i++){
        int x=rand()%5, y=rand()%5;
        while (map[x][y]!=0){
            x=rand()%5;
            y=rand()%5;
        }//make sure there is no repeated coords
        count++;
        if (count<4) map[x][y]=2;
        else if (count<6) map[x][y]=4;
        else map[x][y]=8;
    }//set initial numbers
    
}//create a new game map

void print_map(double map[5][5]){
    for (int j=0; j<5; j++){
        for (int i=0; i<5; i++) {
            cout<<map[j][i]<<"\t";
        }
        cout << "\n";
    }
}//print the map

void add_a_number(double map[5][5]){
    srand((int)time(NULL));
    //1: decide the coord that accepts a new unmber
    int x=rand()%5, y=rand()%5;
    while (map[x][y]!=0){
        x=rand()%5;
        y=rand()%5;
    }//make sure there is no repeated coords
    
    //2: find the largest number on the map
    double max=0;
    for (int i=0; i<5; i++){
        for (int j=0; j<5; j++){
            if (map[i][j]>max) max=map[i][j];
        }
    }
    
    //3: random a number that is below the largest
    int times=-1;
    while(max>=2){
        max/=2;
        times++;
    }
    map[x][y]=pow(2, rand()%times+1);
    
    
}

void make_a_move(char coord[5], char dir[5], double map[5][5], int gameStatus){
    int x=(double)atoi(&coord[0]);
    int y=(double)atoi(&coord[2]);
    
    if(x<0 || y<0 || x>4 || y>4){
        gameStatus=-1;
        return;
    }
    
    double originNum=map[x][y];
    double aimNum=0;
    
    if ((*dir=='l' && y-1<0)||(*dir=='r' && y+1>4)||(*dir=='d' && x+1>4)||(*dir=='u' && x-1<0)){
        gameStatus=-1;
    }
    
    
    if (gameStatus==-1) return;
    else{
        if (*dir=='l') aimNum=map[x][y-1];
        else if (*dir=='r') aimNum=map[x][y+1];
        else if (*dir=='d') aimNum=map[x+1][y];
        else aimNum=map[x-1][y];
    }
    
    if (originNum==aimNum){
        map[x][y]=0;
        if (*dir=='l') map[x][y-1]=2*aimNum;
        else if (*dir=='r') map[x][y+1]=2*aimNum;
        else if (*dir=='d') map[x+1][y]=2*aimNum;
        else map[x-1][y]=2*aimNum;
    }else if(aimNum==0){
        map[x][y]=0;
        if (*dir=='l') map[x][y-1]=originNum;
        else if (*dir=='r') map[x][y+1]=originNum;
        else if (*dir=='d') map[x+1][y]=originNum;
        else map[x-1][y]=originNum;
    }else{
        gameStatus=1;
        return;
    }
}

int game_ends_or_not(double map[5][5]){
    for (int j=0; j<5; j++){
        for (int i=0; i<5; i++) {
            if(map[i][j]==2048) return 1;
        }
    }
    
    for (int j=0; j<5; j++){
        for (int i=0; i<5; i++) {
            if(map[i][j]==0) return 0;
        }
    }
    
    return -1;
}


int main() {
    int gameEnds=0;
    int gameStatus=0;
    double map[5][5];
    new_map(map);
    print_map(map);
    while (gameEnds==0){
        char coord[5]="", dir[5]="";
        cout<<"Please enter the coordinate: "<<endl;
        cin>>coord;
        cout<<"Please enter the direction: "<<endl;
        cin>>dir;
        make_a_move(coord, dir, map, gameStatus);
        if (gameStatus==0){
            add_a_number(map);
        }else if(gameStatus==1){
            cout<<"Invalid move!"<<endl;
        }else if(gameStatus==-1){
            cout<<"Out of the map!"<<endl;
        }
        gameEnds=game_ends_or_not(map);
        print_map(map);
    }
    
    if (gameEnds==1) cout<< "You win!!!" << endl;
    else cout<<"You lose!!!"<<endl;
    
    return 0;
}
