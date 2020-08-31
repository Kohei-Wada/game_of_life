#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <termios.h>

#define X 100
#define Y 70



int cells[X][Y] = {0};
int nextcells[X][Y] = {0};
int cursorX = X/2, cursorY = Y/2;

static struct termios old, current;





void init_termios(int echo)
{
    tcgetattr(0, &old);
    current = old;
    current.c_lflag &= ~ICANON;

    if(echo)
        current.c_lflag |= ECHO;
    else
        current.c_lflag &= ~ECHO;

    tcsetattr(0, TCSANOW, &current);
}



void restet_termios(void)
{
    tcsetattr(0, TCSANOW, &old);
}


char getch_(int echo)
{
char ch;

    init_termios(echo);
    ch = getchar();
    restet_termios();
    return ch;
}



char getch(void)
{
    return getch_(0);
}



void init_cells(int random)
{
int x, y;

    if(!random){
        for(y = 0; y < Y; ++y){
            for(x = 0; x < X; ++x){
                cells[x][y] = 0;
            }
        }
    }
    else if(random){
        srand((unsigned int)time(NULL));
        for(y = 0; y < Y; ++y){
            for(x = 0; x < X; ++x){
                cells[x][y] = rand()%2;
            }
        }
    }
    else{
        printf("err\n");
        exit(1);
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

    int ch = getch();

    switch(ch){
        case 'e': --cursorY;                       break;
        case 'd': ++cursorY;                       break;
        case 'f': ++cursorX;                       break;
        case 'a': --cursorX;                       break;
        case 'l': cells[cursorX][cursorY] = 1;     break;
        case 'u': cells[cursorX][cursorY] = 0;     break;
        case 'c': ret = 0; cursorX = cursorY = -1; break;
        case 'q': exit(0);
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



void set_cells(void)
{
int active = 1;

    while(active){
        system("clear");
        print_cells();
        active = cursor();
    }
}



void run(void)
{
int time = 1000000 * 0.1;

    while(1){
        system("clear");
        print_cells();
        usleep(time);
        next();
    }
}



int main(int argc, char **argv)
{

    if(argc == 1){

        init_cells(0);
        set_cells();
    }

    else if(argc > 1){
        if(strcmp(argv[1], "-r") == 0){
            init_cells(1);
            cursorX = cursorY = -1;
        }
        else{
            printf("err\n");
            return 1;
        }
    }

    run();

    return 0;
}
