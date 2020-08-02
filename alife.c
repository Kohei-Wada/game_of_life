#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define SIZE_X 100
#define SIZE_Y 50



int cell[SIZE_X][SIZE_Y];
int nextcell[SIZE_X][SIZE_Y];
int sample(char *ex);



void init_cell(void)
{
    srand((unsigned int)time(NULL));
    for(int x = 0; x < SIZE_X; ++x){
        for(int y = 0; y < SIZE_Y; ++y){
            cell[x][y] = rand()%2;
            nextcell[x][y] = 0;
        }
    }

}

int search(int x, int y)
{
int counter = 0;
    for(int j = y-1; j < y+2; ++j){
        for(int i = x-1; i < x+2; ++i){
            if(cell[i][j])
                ++counter;
        }
    }

    if(cell[x][y])
        --counter;
    return counter;
}



void next(void)
{
int ret, x, y;
    for(x = 1; x < SIZE_X-1; ++x){
        for(y = 1; y < SIZE_Y-1; ++y){
            ret = search(x, y);

            if(!cell[x][y] && ret == 3)
                nextcell[x][y] = 1;
            else if(cell[x][y] && (ret == 2 || ret == 3))
                nextcell[x][y] = 1;
            else if(cell[x][y] && ret <= 1)
                nextcell[x][y] = 0;
            else if(cell[x][y] && ret >= 4)
                nextcell[x][y] = 0;
        }
    }

    for(x = 1; x <SIZE_X; ++x){
        for(y = 1; y < SIZE_Y; ++y){
            cell[x][y] = nextcell[x][y];
        }
    }
}


void print_stage(void)
{
    for(int y = 1; y < SIZE_Y-1; ++y){
        for(int x = 1; x < SIZE_X-1; ++x){
            if(cell[x][y])
                printf("o");
            else
                printf(" ");
        }
        printf("\n");
    }
}




int main(int argc, char **argv)
{


    int time = 1000000 * 0.1;
    init_cell();

    if(argc > 1)
        sample(argv[1]);

    while(1){
        system("clear");
        print_stage();
        next();
        usleep(time);
    }

    return 0;
}


int sample(char *ex)
{
    for(int x = 0; x < SIZE_X; ++x){
        for(int y = 0; y < SIZE_Y; ++y){
            cell[x][y] = 0;
        }
    }
    
//graider gun
    if(strcmp(ex, "gg") == 0){
        cell[2][6] = 1;
        cell[2][7] = 1;
        cell[3][6] = 1;
        cell[3][7] = 1;
        cell[12][6] = 1;
        cell[12][7] = 1;
        cell[12][8] = 1;
        cell[13][5] = 1;
        cell[13][9] = 1;
        cell[14][4] = 1;
        cell[14][10] = 1;
        cell[15][4] = 1;
        cell[15][10] = 1;
        cell[16][7] = 1;
        cell[17][5] = 1;
        cell[17][9] = 1;
        cell[18][6] = 1;
        cell[18][7] = 1;
        cell[18][8] = 1;
        cell[19][7] = 1;
        cell[22][4] = 1;
        cell[22][5] = 1;
        cell[22][6] = 1;
        cell[23][4] = 1;
        cell[23][5] = 1;
        cell[23][6] = 1;
        cell[24][3] = 1;
        cell[24][7] = 1;
        cell[26][2] = 1;
        cell[26][3] = 1;
        cell[26][7] = 1;
        cell[26][8] = 1;
        cell[36][4] = 1;
        cell[36][5] = 1;
        cell[37][4] = 1;
        cell[37][5] = 1;
    }

    else{
        fprintf(stderr, "Usage: ./alife [ex]\n");
        fprintf(stderr, "  gg -> graider gun\n");
        exit(1);
    }

    return 0;
}
