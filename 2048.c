#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
   
int rand_gen(int n) {
    return (rand()%n);
}
   
int new_tile() {
    if(!rand_gen(8))
        return 4;
    return 2;
}
   
void reset_game(int grid[4][4][2], int *score) {
    int x, y, l;
       
    srand(time(NULL));
       
    for(y=0;y<4;y++)
        for(x=0;x<4;x++)
            for(l=0;l<2;l++)
                grid[x][y][l]=0;
       
    *score=0;
       
    for(l=0;l<2;l++) {
        x=rand_gen(4);
        y=rand_gen(4);
        grid[x][y][0]=new_tile();
    }
}
   
void start_screen() {
    int f;
       
    for(f=0;f<7;f++) {
        usleep(f>5?1000000:500000);
        system("clear");
        printf("\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""      ""%s""    ""\x1b[43m""   ""%s""    ""\x1b[43m""     ""%s""  ""\x1b[43m""   ""%s""    ""\x1b[43m""      \n", (f>0?"\x1b[47m":"\0"), (f>1?"\x1b[47m":"\0"), (f>2?"\x1b[47m":"\0"), (f>3?"\x1b[47m":"\0"));
        printf("\x1b[37;43m""     ""%s"" ""\x1b[43m""    ""%s"" ""\x1b[43m"" ""%s"" ""\x1b[43m""    ""%s"" ""\x1b[43m""   ""%s"" ""\x1b[43m"" ""%s"" ""\x1b[43m""  ""%s"" ""\x1b[43m""    ""%s"" ""\x1b[43m""     \n", (f>0?"\x1b[47m":"\0"), (f>0?"\x1b[47m":"\0"), (f>1?"\x1b[47m":"\0"), (f>1?"\x1b[47m":"\0"), (f>2?"\x1b[47m":"\0"), (f>2?"\x1b[47m":"\0"), (f>3?"\x1b[47m":"\0"), (f>3?"\x1b[47m":"\0"));
        printf("\x1b[37;43m""        ""%s""  ""\x1b[43m""  ""%s"" ""\x1b[43m""    ""%s"" ""\x1b[43m""  ""%s"" ""\x1b[43m""  ""%s"" ""\x1b[43m""   ""%s""    ""\x1b[43m""      \n", (f>0?"\x1b[47m":"\0"), (f>1?"\x1b[47m":"\0"), (f>1?"\x1b[47m":"\0"), (f>2?"\x1b[47m":"\0"), (f>2?"\x1b[47m":"\0"), (f>3?"\x1b[47m":"\0"));
        printf("\x1b[37;43m""      ""%s""  ""\x1b[43m""    ""%s"" ""\x1b[43m""    ""%s"" ""\x1b[43m"" ""%s""      ""\x1b[43m"" ""%s"" ""\x1b[43m""    ""%s"" ""\x1b[43m""     \n", (f>0?"\x1b[47m":"\0"), (f>1?"\x1b[47m":"\0"), (f>1?"\x1b[47m":"\0"), (f>2?"\x1b[47m":"\0"), (f>3?"\x1b[47m":"\0"), (f>3?"\x1b[47m":"\0"));
        printf("\x1b[37;43m""     ""%s""      ""\x1b[43m""  ""%s""    ""\x1b[43m""      ""%s"" ""\x1b[43m""   ""%s""    ""\x1b[43m""      \n", (f>0?"\x1b[47m":"\0"), (f>1?"\x1b[47m":"\0"), (f>2?"\x1b[47m":"\0"), (f>3?"\x1b[47m":"\0"));
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[30;43m""   %s   ""\x1b[0m""\n", (f>5?"Pressione [ENTER para continuar":"                               "));
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
        printf("\x1b[37;43m""                                     ""\x1b[0m""\n");
    }
       
    while(getchar()!='\n');
}
   
void print_menu(int *highscore) {
    system("clear");
    printf("  _____________________________________\n");
    printf(" |                                     |\n");
    printf(" |                 Menu                |\n");
    printf(" |     ___________________________     |\n");
    printf(" |    |                           |    |\n");
    printf(" |    |                           |    |\n");
    printf(" |    |        1 - PLAY           |    |\n");
    printf(" |    |                           |    |\n");
    printf(" |    |___________________________|    |\n");
    printf(" |    |                           |    |\n");
    printf(" |    |   Highscore - %7d     |    |\n", *highscore);
    printf(" |    |___________________________|    |\n");
    printf(" |         ___________________         |\n");
    printf(" |        |                   |        |\n");
    printf(" |        |    0 - Sair       |        |\n");
    printf(" |        |___________________|        |\n");
    printf(" |                                     |\n");
    printf(" |_____________________________________|\n");
       
       
}
   
void print_number(int t) {
    int a=0, n, c;
   
    n=t;
    do {
        a++;
        n/=10;
    } while(n);
       
    for(c=0;c<3-(a%2==0?(a/2):((a+1)/2));c++)
        printf(" ");
    printf("%s%d", (a%2==0?"":" "), t);
    for(c=0;c<3-(a%2==0?(a/2):((a+1)/2));c++)
        printf(" ");
}
   
void print_tile(int t, int l) {
    if(!t)
        printf("         ");
    else
        switch(l) {
            case 0: printf(" ______  ");
                    break;
            case 1: printf("|      | ");
                    break;
            case 2: printf("|");
                    print_number(t);
                    printf("| ");
                    break;
            case 3: printf("|______| ");
                    break;       
        }
}
   
void print_grid(int grid[4][4][2], int *score, int *highscore) {
    int x, y, l;
       
    system("clear");
   
    printf("           HIGHSCORE:%d\n", *highscore);
    printf("               SCORE:%d\n", *score);
   
    printf("  _____________________________________\n");
    for(y=0;y<4;y++)
        for(l=0;l<4;l++) {
            printf(" | ");
            for(x=0;x<4;x++)
                print_tile(grid[x][y][0], l);
            printf("|\n");
        }
    printf(" |_____________________________________|\n");
   
}
   
int getch(void) {
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
    newt = oldt; /* copy old settings to new settings */
    newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
    ch = getchar(); /* standard getchar call */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
    return ch; /*return received char */
}
   
int move_tiles(int grid[4][4][2], int direction) {
    int x, y, l, move=0;
   
    switch(direction) {
        case 0: for(x=0;x<4;x++)
                    for(y=1;y<=3;y++)
                        for(l=0;l<y;l++)
                            if(grid[x][y-l][0]) {
                                if(!grid[x][y-l-1][0]){
                                    grid[x][y-l-1][0]=grid[x][y-l][0];
                                    grid[x][y-l][0]=0;
                                    move=1;
                                }
                                else if(grid[x][y-l-1][0]==grid[x][y-l][0]&&!grid[x][y-l][1]&&!grid[x][y-l-1][1]) {
                                    grid[x][y-l-1][1]=grid[x][y-l][0];
                                    grid[x][y-l-1][0]+=grid[x][y-l][0];
                                    grid[x][y-l][0]=0;
                                    move=1;
                                }
                            }
                break;
        case 1: for(y=0;y<4;y++)
                    for(x=1;x<=3;x++)
                        for(l=0;l<x;l++)
                            if(grid[x-l][y][0]) {
                                if(!grid[x-l-1][y][0]){
                                    grid[x-l-1][y][0]=grid[x-l][y][0];
                                    grid[x-l][y][0]=0;
                                    move=1;
                                }
                                else if(grid[x-l-1][y][0]==grid[x-l][y][0]&&!grid[x-l][y][1]&&!grid[x-l-1][y][1]) {
                                    grid[x-l-1][y][1]=grid[x-l][y][0];
                                    grid[x-l-1][y][0]+=grid[x-l][y][0];
                                    grid[x-l][y][0]=0;
                                    move=1;
                                }
                            }
                break;
        case 2: for(x=0;x<4;x++)
                    for(y=2;y>=0;y--)
                        for(l=0;l<3-y;l++)
                            if(grid[x][y+l][0]) {
                                if(!grid[x][y+l+1][0]){
                                    grid[x][y+l+1][0]=grid[x][y+l][0];
                                    grid[x][y+l][0]=0;
                                    move=1;
                                }
                                else if(grid[x][y+l+1][0]==grid[x][y+l][0]&&!grid[x][y+l][1]&&!grid[x][y+l+1][1]) {
                                    grid[x][y+l+1][1]=grid[x][y+l][0];
                                    grid[x][y+l+1][0]+=grid[x][y+l][0];
                                    grid[x][y+l][0]=0;
                                    move=1;
                                }
                            }
                break;
        case 3: for(y=0;y<4;y++)
                    for(x=2;x>=0;x--)
                        for(l=0;l<3-x;l++)
                            if(grid[x+l][y][0]) {
                                if(!grid[x+l+1][y][0]){
                                    grid[x+l+1][y][0]=grid[x+l][y][0];
                                    grid[x+l][y][0]=0;
                                    move=1;
                                }
                                else if(grid[x+l+1][y][0]==grid[x+l][y][0]&&!grid[x+l][y][1]&&!grid[x+l+1][y][1]) {
                                    grid[x+l+1][y][1]=grid[x+l][y][0];
                                    grid[x+l+1][y][0]+=grid[x+l][y][0];
                                    grid[x+l][y][0]=0;
                                    move=1;
                                }
                            }
                break;
    }                                    
    return move;
}
  
int possible_moves(int grid[4][4][2]) {
    int x, y;
  
    for(y=0;y<4;y++)
        for(x=0;x<4;x++) {
            if(!grid[x][y][0])
                return 1;
            else {
                if(x>0?(grid[x][y][0]==grid[x-1][y][0]):0)
                    return 1;
                if(x<3?(grid[x][y][0]==grid[x+1][y][0]):0)
                    return 1;
                if(y>0?(grid[x][y][0]==grid[x][y-1][0]):0)
                    return 1;
                if(y<3?(grid[x][y][0]==grid[x][y+1][0]):0)
                    return 1;
            }
        }
    return 0;
}
  
void game_over(int grid[4][4][2], int *score, int *highscore) {
    char input;
     
    print_grid(grid, score, highscore);
      
    printf("\x1b[31m""GAME OVER!""\x1b[0m");
    printf("Deseja iniciar um novo jogo?\n");
    printf("(s/n)>> ");
    while(input!='s'&&input!='n')
        input=getchar();
    if(input=='s')
        reset_game(grid, score);
	while(getchar()!='\n');
}
   
void swipe(int grid[4][4][2], int *score, int *highscore, int direction) {
    int x, y;
   
    if(move_tiles(grid, direction)) {
        for(y=0;y<4;y++)
            for(x=0;x<4;x++) {
                *score+=grid[x][y][1];
                grid[x][y][1]=0;
            }
               
        *highscore=(*highscore<=*score?*score:*highscore);
           
        print_grid(grid, score, highscore);
                   
        do {
            x=rand_gen(4);
            y=rand_gen(4);
        } while(grid[x][y][0]);
        grid[x][y][0]=new_tile();
          
        if(!possible_moves(grid))
            game_over(grid, score, highscore);
           
        usleep(100000);
    }
}
   
void restart(int grid[4][4][2],  int *score) {
    char input;
      
    printf("Você tem certeza que deseja reiniciar o jogo?\n");
    printf("(s/n)>> ");
    while(input!='s'&&input!='n')
        input=getchar();
    if(input=='s')
        reset_game(grid, score);
	while(getchar()!='\n');
}
   
void play(int grid[4][4][2], int *score, int *highscore) {
    char input;
       
    do{
        print_grid(grid, score, highscore);
           
        input=getch();
           
        switch(input) {
            case 'w':   swipe(grid, score, highscore, 0);
                        break;
            case 'a':   swipe(grid, score, highscore, 1);
                        break;
            case 's':   swipe(grid, score, highscore, 2);
                        break;
            case 'd':   swipe(grid, score, highscore, 3);
                        break;
            case 'r':   restart(grid, score);
                        break;
        }
    } while(input!='q');
}
   
void menu(int grid[4][4][2], int *score, int *highscore) {
    char input;
       
    do{
        print_menu(highscore);
           
        input=getchar();
        while(getchar()!='\n');
           
        switch(input) {
            case '1':   play(grid, score, highscore);
                        break;
        }
    } while(input!='0');
}
   
int main() {
    int grid[4][4][2], score=0, highscore=0;
       
    reset_game(grid, &score);
       
    start_screen();
   
    menu(grid, &score, &highscore);
   
    return 0;
}