#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define X 100
#define Y 50


int cells[X][Y];
int nextcells[X][Y];
int cursorX = 50, cursorY = 25;


void init_cells(void)
{
int x, y;
    for(y = 0; y < Y; ++y){
        for(x = 0; x < X; ++x){
            cells[x][y] = 0;
        }
    }
}


void print_cells(void)
{
int x, y;
    for(y = 0; y < Y; ++y){
        for(x = 0; x < X; ++x){
            if(x == cursorX && y == cursorY)
                printf("+");
            else if(cells[x][y])
                printf("o");
            else
                printf(" ");
        }
        printf("\n");
    }
}


int search(int x, int y)
{
int counter = 0;
    for(int j = y-1; j < y+2; ++j){
        for(int i = x-1; i < x+2; ++i){
            if(cells[i][j])
                ++counter;
            }
        }

    if(cells[x][y])
        --counter;

    return counter;
}



int cursor(void)
{
int ret = 1;

    int ch = getchar();
    switch(ch){
        case 'e': --cursorY; break;
        case 'd': ++cursorY; break;
        case 'f': ++cursorX; break;
        case 'a': --cursorX; break;
        case 'l': cells[cursorX][cursorY] = 1; break;
        case 'u': cells[cursorX][cursorY] = 0; break;
        case 'q': ret = 0; cursorX = -1; cursorY = -1; break;
    }
    return ret;
}



void next(void)
{
int ret, x, y;
    for(x = 1; x < X-1; ++x){
        for(y = 1; y < Y-1; ++y){
            ret = search(x, y);

            if(!cells[x][y] && ret == 3)
                nextcells[x][y] = 1;
            else if(cells[x][y] && (ret == 2 || ret == 3))
                nextcells[x][y] = 1;
            else if(cells[x][y] && ret <= 1)
                nextcells[x][y] = 0;
            else if(cells[x][y] && ret >= 4)
                nextcells[x][y] = 0;
        }
    }

    for(x = 1; x < X; ++x){
        for(y = 1; y < Y; ++y){
            cells[x][y] = nextcells[x][y];
        }
    }
}



int main(void)
{
int time = 1000000 * 0.1;
int active = 1;

    init_cells();
    while(active){
        printf("\033[2J");
        print_cells();
        active = cursor();

    }


    while(1){
        printf("\033[2J");
        print_cells();
        usleep(time);
        next();
    }

    return 0;
}
