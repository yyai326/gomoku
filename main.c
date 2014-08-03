#include <stdio.h>

#define BDSZ 15 //boardsize
#define B 1 //black 
#define W 2 //white

short board[BDSZ][BDSZ];
void printbd(short [][BDSZ]);
int set_axis(int,int,int);

int main(int argv,char **args)
{
    printf("hello\n");
    set_axis(0,0,B);
    printbd(board);
}

void printbd(short board[][BDSZ])
{
    int i=0,j=0;
    for(i=0;i<BDSZ;i++)
    {
        for(j=0;j<BDSZ;j++)
            printf("%hd",board[i][j]);
        printf("\n");
    }
}

int set_axis(int x, int y, int who)
{
    if(x<0 || x>=BDSZ)
        return 1;
    if(y<0 || y>=BDSZ)
        return 1;
    if(who != B && who != W)
        return 1;
    board[x][y]=who;
    return 0;
}

bool is_win(short const bd[][BDSZ],int who)
{
    int i,j;
    //horizontal
    for(i=0;i<BDSZ;i++)
    {
        if(is5_inline(&bd[i],BDSZ,who))
            return true;
        for(i=0;i<BDSZ;i++)
            for(j=0;j<BDSZ;j++)
            {
                bd[j][i]
            }
    }
}


bool is5_inline(short const *line, int len, int who)
{
    int i,cnt=0;
    for(i=0;i<len;i++)
    {
        if(line[i]==who)
        {
            if(++cnt==5)
                return true;
        }
        else
            cnt=0;
    }
    return false;
}


