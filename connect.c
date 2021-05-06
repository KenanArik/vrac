
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUFFERSIZE 1000
 
typedef struct t_param {
    int w;
    int h;
    char p1;
    char p2;
    char a;
}t_param;

void write_board(char **board,struct t_param param);
int is_full(char **board,struct t_param param);
int get_move(int player,struct t_param param,int is_file);
int valid_move(char **board, int column,struct t_param param);
int make_move(char **board, int player, int column,struct t_param param);
int win(char **board, int move,struct t_param param);
 


 
void write_board(char **board,struct t_param param)
{
    int i;
    int j;
 
    for(i = 0; i < param.w+2; i++)
        printf("+");
 
    printf("\n");
    for(i = 0; i < param.h; i++) {
        printf("|");
        for(j = 0; j < param.w; j++)
            printf("%c", board[i][j]);
        printf("|\n");
    }
    for(i = 0; i < param.w+2; i++)
        printf("+");
    printf("\n");
}
 
int is_full(char **board,struct t_param param)
{
    int i;
    int j;
    //printf("is_full test BEFORE\n");
    for(i = 0; i < (param.h); i++) {
        for(j = 0; j < param.w; j++)
            if(board[i][j] == '.')
                return 0;
    }
    //printf("is_full AFTER\n");
    return 1;
}
 
int get_move(int player,struct t_param param,int is_file)
{
    int column;
    
    if(player == 1){
        printf("Player %c, where do you want to play: ", param.p1);
    }else{
        printf("Player %c, where do you want to play: ", param.p2);
    }
 
    if(is_file != 1)
        scanf("%d", &column);
 
    return column;
}
 
int valid_move(char **board, int column,struct t_param param)
{
    int i;
    int is_occup = 1;
    
    //printf("valid_move FLAG 1\n");
 
    if(column > param.w || column <0 ) {
        printf("\nInvalid move\n");
        return 0;
    }
 //printf("valid_move FLAG 2\n");
    for(i = 0; i < param.h; i++) {
       // printf("BEFORE is_occup=%d,board[%d][%d]=%c\n",is_occup,i,column - 1,board[i][column - 1]);
        
        if(board[i][column-1] != '.'){
            is_occup++;
        }
       // printf("AFTER is_occup=%d,board[%d][%d]=%c\n",is_occup,i,column - 1,board[i][column - 1]);
        
    }
    //printf("valid_move FLAG 3\n");
    //printf("\nvalid_move column=%d,param.h=%d,is_occup=%d\n",column,param.h,is_occup);
    if(is_occup == param.h+1 ) {
        printf("\nInvalid move is_occup\n");
        return 0;
    }
    else
        return 1;
}
 
int make_move(char **board, int player, int column,struct t_param param)
{
    int i,ret=0;
    char ch;
 
    if(player == 1)
        ch = param.p1;
    else
        ch = param.p2;
 
    //printf("FLAG 0 column=%d make_move\n",column);
    
    for(i = (param.h -1); i >= 0; i--) {
        //printf("FLAG 0 BIS i=%d,column=%d , ch=%c, (param.h)=%d,make_move\n",i,column,ch,(param.h));
        if(board[i][column] == '.') {
            board[i][column] = ch;
            break;
        }
    }
    //printf("FLAG 1 column=%d make_move\n",column);
    ret = win(board, column,param);
    //printf("FLAG 2 column=%d make_move\n",column);
    write_board(board,param);
   // printf("FLAG 3 column=%d make_move\n",column);
    
    
    return ret;
}
 
int win(char **board, int move,struct t_param param)
{
    int i;
    int line;
    int column;
    int counter;
    char player = '\0';
 
    for(i = 0; i < param.h; i++) {
        if(board[i][move] != '.') {
            player = board[i][move];
            break;
        }
    }
    //printf("win 1 player=%c \n",player);
 
    counter = 0;
    line = i;
  
    column = move;
    while((counter < 5) && (board[line][column] == player)) {
        counter++;
        column--;
 
        if(counter == 5){
            board[line][column+1] = param.a;
            board[line][column+2] = param.a;
            board[line][column+3] = param.a;
            board[line][column+4] = param.a;
            return 1;
        }
    }
   // printf("win 2 line=%d \n",line);
 
    column = move;
    while((counter < 5) && (board[line][column] == player)) {
        counter++;
        column++;
 
        if(counter == 5){
            board[line][column-1] = param.a;
            board[line][column-2] = param.a;
            board[line][column-3] = param.a;
            board[line][column-4] = param.a;
            return 1;
        }
    }
    //printf("win 3 line=%d \n",line);
    counter = 0;
    column = move;
 
    while( line<param.h && line>=0 && column<param.w && column>=0 &&(counter < 5) && (board[line][column] == player) ) {
        counter++;
        line--;
        //printf("win 3 BIS line=%d \n",line);
        if(counter == 5){
            board[line+1][column] = param.a;
            board[line+2][column] = param.a;
            board[line+3][column] = param.a;
            board[line+4][column] = param.a;
            return 1;
        }
    }
 
    line = i;
   //printf("win 4 line=%d \n",line);
 
    while( line<param.h && line>=0 && column<param.w && column>=0 &&(counter < 5) && (board[line][column] == player) ) {
        counter++;
        line++;
 
        if(counter == 5){
            board[line-1][column] = param.a;
            board[line-2][column] = param.a;
            board[line-3][column] = param.a;
            board[line-4][column] = param.a;
            return 1;
        }
    }
 
    counter = 0;
 
    line = i;
    column = move;
    //printf("win 5 line=%d \n",line);
 
    while( line<param.h && line>=0 && column<param.w && column>=0 &&(counter < 4) && (board[line][column] == player) ) {
        counter++;
        line++;
        column--;
 
        if(counter == 4){
            board[line-1][column+1] = param.a;
            board[line-2][column+2] = param.a;
            board[line-3][column+3] = param.a;
            board[line-4][column+4] = param.a;
            return 1;
        }
    }
 
    line = i;
    column = move;
    //printf("win 6 line=%d \n",line);
 
    while( line<param.h && line>=0 && column<param.w && column>=0 &&(counter < 5) && (board[line][column] == player) ) {
        counter++;
        line--;
        column++;
 
        if(counter == 5){
            board[line+1][column-1] = param.a;
            board[line+2][column-2] = param.a;
            board[line+3][column-3] = param.a;
            board[line+4][column-4] = param.a;
            return 1;
        }
    }
 
    counter = 0;
 
    line = i;
    column = move;
    //printf("win 7 line=%d \n",line);
 
    while( line<param.h && line>=0 && column<param.w && column>=0 &&(counter < 4) && (board[line][column] == player) ) {
        counter++;
        line++;
        column++;
 
        if(counter == 4){
            board[line-1][column-1] = param.a;
            board[line-2][column-2] = param.a;
            board[line-3][column-3] = param.a;
            board[line-4][column-4] = param.a;
            return 1;
        }
    }
 
    line = i;
    column = move;
    //printf("win 8 line=%d \n",line);
    while( line<param.h && line>=0 && column<param.w && column>=0 &&(counter < 5) && (board[line][column] == player) ) {
        counter++;
        line--;
        column--;
 
        if(counter == 5){
            board[line+1][column+1] = param.a;
            board[line+2][column+2] = param.a;
            board[line+3][column+3] = param.a;
            board[line+4][column+4] = param.a;
            return 1;
        }
    }
    //printf("win 9 line=%d \n",line);
    return 0;
}
int is_number(char *p){
    while (*p != '\0')
    {
        if (*p<'0' || *p>'9')
        {
            return 0;
        }
        p++;
    }
    return 1;
    
}
//./connect4 -p2 ‘@’ -w 18 -p1 ‘#’ -h 3 -a ’*'
int set_param(int ac, char **av,struct t_param* param){
    for(int i=1;i<ac;i++){
        if (strcmp(av[i],"-p2") == 0){
            if(i<ac && strlen(av[i+1])==1){
                param->p2 = av[i+1][0];
            }
            else{
                return 84;
            }
        }
        if (strcmp(av[i],"-p1") == 0){
            if(i<ac && strlen(av[i+1])==1){
                param->p1 = av[i+1][0];
            }
            else{
                return 84;
            }
        }
        if (strcmp(av[i],"-a") == 0){
            if(i<ac && strlen(av[i+1])==1){
                param->a = av[i+1][0];
            }
            else{
                return 84;
            }
        }
        if (strcmp(av[i],"-w") == 0){
            if(i<ac && is_number(av[i+1])==1){
                param->w = atoi(av[i+1]);
            }
            else{
                return 84;
            }
        }
        if (strcmp(av[i],"-h") == 0){
            if(i<ac && is_number(av[i+1])==1){
                param->h = atoi(av[i+1]);
            }
            else{
                return 84;
            }
        }
    }
    return 1;
}

int play_without_file(char **board, struct t_param param){
    int i;
    int j;
    int move;
    int player;
    int winner = 0;
    do {
        player = 1; 
  
        do {
            move = get_move(player,param,0);
        }while(valid_move(board, move,param) == 0);
        
        move -= 1;
        //printf("move 1=%d\n",move);
         
        if(make_move(board, player, move,param) == 1) {
            winner = 1;
            printf("Congrats, player %c won!\n",param.p1);
            //write_board(board,param);
            break;
        }
        if(is_full(board,param) == 1){
            printf("It’s a tie, nobody wins.\n");
            return 0;
        }
 
        //printf("\n");
 
        player = 2;
        
 
        do {
            move = get_move(player,param,0);
        }while(valid_move(board, move,param) == 0);
         
        move -= 1;
        printf("move 2=%d\n",move);
 
        if(make_move(board, player, move,param) == 1) {
            winner = 2;
            printf("Congrats, player %c won!\n",param.p2);
            //write_board(board,param);
            break;
        }
 
        //printf("\n");
 
    }while(is_full(board,param) == 0);
 
    if(winner != 1 && winner != 2){
        printf("It’s a tie, nobody wins.\n");
        return 0;
    }
    return 1;
}

int play_with_file(char **board, struct t_param param,int line,int column){
    int i;
    int j;
    int move;
    int player;
    int winner = 0;
    
    player = (line%2==1)?1:2 ;
  
    do {
        get_move(player,param,1);
        move = column;
        if(column == -1)
            return 0;
    }while(valid_move(board, move,param) == 0);
    
    move -= 1;
    //printf("move 1=%d\n",move);
     
    if(make_move(board, player, move,param) == 1) {
        winner = 1;
        printf("Congrats, player %c won!\n",param.p1);
        //write_board(board,param);
        return 1;
    }
    if(is_full(board,param) == 1){
        printf("It’s a tie, nobody wins.\n");
        return 1;
    }
    
   
    return 0;
}

char** ini_mat(struct t_param param){
    int i,j;
    char **board = malloc(((param.h ))*sizeof(char*));
    
    for(i=0;i<(param.h);i++)
    {
        board[i] = malloc((param.w )*sizeof(char));
    }
 
 
    for(i = 0; i < (param.h); i++) {
        
        for(j = 0; j < (param.w); j++){
            board[i][j] = '.';
            //printf("board[%d][%d] =%c\n",i,j,board[i][j]);
        }
            
    }
    return board;
}


int main(int ac, char **av)
{
    
    int w = 7;
    int h = 6;
    char p1 = 'X';
    char p2 = 'O';
    char a = '#';
    
    int i;
    int j;
    int move;
    int player;
    int winner = 0;
    
    struct t_param param={w,h,p1,p2,a};
    
    if(set_param(ac, av,&param) != 1)
        return 84;
    //./connect4 -p2 ‘@’ -w 18 -p1 ‘#’ -h 3 -a ’*'
    //printf("ac=%d,p1=%c,p2=%c,a=%c,h=%d,w=%d\n",ac,param.p1,param.p2,param.a,param.h,param.w);
    
    char **board = ini_mat(param);
    /*char **board = malloc(((param.h ))*sizeof(char*));
    for(i=0;i<(param.h);i++)
    {
        board[i] = malloc((param.w )*sizeof(char));
    }
 
 
    for(i = 0; i < (param.h); i++) {
        
        for(j = 0; j < (param.w); j++){
            board[i][j] = '.';
            //printf("board[%d][%d] =%c\n",i,j,board[i][j]);
        }
            
    }*/
    
 //write_board(board,param);
    if (!isatty(STDIN_FILENO)) //if stdin is not a terminal (a file was provided)
    {
         char buffer[BUFFERSIZE];
         int counter = 0;
         int ret = 0;
         while( fgets(buffer, BUFFERSIZE , stdin) && ret!=1) /* break with ^D or ^Z */
         {
            counter++;
            //printf("buffer=%s\n", buffer);
            //printf("buffer atoi =%d,counter=%d, mod=%d\n", atoi(buffer),counter,(counter%2==1)?1:2);
            ret = play_with_file(board,param,counter,atoi(buffer));
            
         }
         if(ret == 0){
             play_with_file(board,param,counter+1,-1);
         }
    }
    else { //if stdin is a terminal (no file provided)
        play_without_file(board,param);
    } 
    
 
 
    return 0;
}
