#include <stdio.h>
#include <stdbool.h>

#define BDSZ 15 //boardsize
#define B 1 //black 
#define W 2 //white

short board[BDSZ][BDSZ];
void printbd(short [][BDSZ]);
typedef struct stPoint
{
    short x;
    short y;
    short w;
} pt;
int set_pt(pt);
typedef struct stSat
{
    short h_two;
    short a_two;
    short h_three;
    short a_three;
    short h_four;
    short a_four;
    short h_five;
    short a_five;
} sat;

int main(int argv,char **args)
{
    printf("hello\n");
    pt p1;
    p1.x=0;
    p1.y=0;
    p1.w=W;
    set_pt(p1);
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

int set_pt(pt p1)
{
    short x=p1.x;
    short y=p1.y;
    short who=p1.w;
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
    int last,cnt;
    sat st={0};
    //horizontal
    for(i=0;i<BDSZ;i++)
    {
        cnt=0;
        for(j=0;j<BDSZ;j++)
        {
            if(bd[i][j]==who && cnt==0)   
                cnt=1;
            else if(bd[i][j]==who && cnt>0)
                cnt++;
            else if(bd[i][j]!=who && cnt==0)
                cnt=0;
            else //bd[i][j]!=who && cnt>0
            {
                switch (cnt)
                {
                    case 2:
                        st.a_two++;
                        break;
                    case 3:
                        st.a_three++;
                        break;
                    case 4:
                        st.a_four++;
                        break;
                    case 5:
                        st.a_five++
                        break;
                    default:
                        if(cnt>5)
                            st.a_five++;
                        break;
                }
            }
        }
    }
    return false;
}



