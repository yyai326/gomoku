#include <stdio.h>
#include <stdbool.h>

#define BDSZ 15 //boardsize
#define B 1 //black
#define W 2 //white

/*
   struct Point
   board point with position and black/white
*/
typedef struct stPoint
{
    short x;
    short y;
    short w;
} pt;
/*
   statistics of the board
   how many half two or alive two
*/
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

short board[BDSZ][BDSZ];
void printbd(short [][BDSZ]); //print board
int put_pt(pt);//put single point
sat get_sta(short [][BDSZ], int ); //get board statistics
void cnt_line(short const *, int , int ,sat *);  //submethord for get_sta
void setpt(pt *,int,int,int);
void printsat(sat );

void test()
{
    pt p1;
    setpt(&p1,0,0,W);
    put_pt(p1);
    setpt(&p1,0,1,W);
    put_pt(p1);
    setpt(&p1,1,1,W);
    put_pt(p1);
    setpt(&p1,1,2,W);
    put_pt(p1);
    setpt(&p1,2,3,W);
    put_pt(p1);
    setpt(&p1,1,1,W);
    put_pt(p1);
    setpt(&p1,1,3,W);
    put_pt(p1);
    setpt(&p1,1,2,W);
    put_pt(p1);
    //int i,j;
    //int k=0;
    //for(i=0;i<BDSZ;i++)
    //    for(j=0;j<BDSZ;j++)
    //        board[i][j]=k++;
    printbd(board);
    sat st;
    st=get_sta(board,(int)W);
    printsat(st);

}

void play()
{
    int x,y;
    int who=B;
    printf("Black(1) turn(x,y):");
    while(scanf("%d,%d",&x,&y)!=0)
    {
        pt p1;
        setpt(&p1,x,y,who);
        put_pt(p1);
        printbd(board);
        sat st;
        st=get_sta(board,(int)who);
        printsat(st);
        who=who==W?B:W;
        if(who==W)
            printf("White(2) turn(x,y):");
        else
            printf("Black(1) turn(x,y):");
    }
}

int main(int argv,char **args)
{
    printf("hello\n");
    play();
}

void setpt(pt * p,int x,int y,int who)
{
    p->x=x;
    p->y=y;
    p->w=who;
}

void printbd(short board[][BDSZ])
{
    int i=0,j=0;
    printf("YY:0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|\n");
    printf("---------------------------------\n");
    for(i=0;i<BDSZ;i++)
    {
        printf("%2d:",i);
        for(j=0;j<BDSZ;j++)
            printf("%hd|",board[i][j]);
        printf("\n");
    }
}

int put_pt(pt p1)
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

sat get_sta(short bd[][BDSZ],int who)
{
    int i,j,k;
    int last,cnt;
    sat st={0};
    short vert[BDSZ]={0};
    //horizontal
    for(i=0;i<BDSZ;i++)
    {
        cnt_line((short *)bd[i],BDSZ,who,&st);
    }
    //vertical
    for(i=0;i<BDSZ;i++)
    {
        for(j=0;j<BDSZ;j++)
        {
            vert[j]=bd[j][i];
        }
        cnt_line((short *)vert,BDSZ,who,&st);
    }
    //blackslash
    for(k=-BDSZ+1;k<=0;k++)
    {
        for(i=0;i<k+BDSZ;i++)
        {
            vert[i]=bd[i-k][i];
        }
        cnt_line((short *)vert,k+BDSZ,who,&st);
    }
    for(k=1;k<BDSZ;k++)
    {
        for(i=k;i<BDSZ;i++)
        {
            vert[i-k]=bd[i-k][i];
        }
        cnt_line((short *)vert,BDSZ-k,who,&st);
    }
    //slash
    for(k=2-2*BDSZ;k<1-BDSZ;k++)
    {
        for(i=BDSZ-1;i>-BDSZ-k;i--)
        {
            vert[BDSZ-1-i]=bd[-i-k][i];
        }
        cnt_line((short *)vert,BDSZ-1+BDSZ+k,who,&st);
    }
    for(k=1-BDSZ;k<1;k++)
    {
        for(i=-k;i>=0;i--)
        {
            vert[-i-k]=bd[-i-k][i];
        }
        cnt_line((short *)vert,1-k,who,&st);
    }
    return st;
}

void printsat(sat s)
{
    printf("a_two:%d\n",s.a_two);
    printf("a_three:%d\n",s.a_three);
    printf("a_four:%d\n",s.a_four);
    printf("a_five:%d\n",s.a_five);
    printf("h_two:%d\n",s.h_two);
    printf("h_three:%d\n",s.h_three);
    printf("h_four:%d\n",s.h_four);
    printf("h_five:%d\n",s.h_five);
}



void cnt_line(short const *line, int size, int who,sat *st)
{
    int i;
    int cnt=0;
    int opp=who==W?B:W;
    int isHalf=0;
    for (i=0;i<size;i++)
    {
        if(i==size-1 || (line[i]!=who && cnt>0)){
            if(i==size-1 || line[i+1] ==opp )
                isHalf=1;
            if(isHalf==0){
                switch (cnt)
                {
                    case 2:
                        st->a_two++;
                        break;
                    case 3:
                        st->a_three++;
                        break;
                    case 4:
                        st->a_four++;
                        break;
                    case 5:
                        st->a_five++;
                        break;
                    default:
                        if(cnt>5)
                            st->a_five++;
                        break;
                }
            }
            else{
                switch (cnt)
                {
                    case 2:
                        st->h_two++;
                        break;
                    case 3:
                        st->h_three++;
                        break;
                    case 4:
                        st->h_four++;
                        break;
                    case 5:
                        st->a_five++;
                        break;
                    default:
                        if(cnt>5)
                            st->a_five++;
                        break;
                }
            }
            cnt=0;
            isHalf=0;
        }
        //printf("%d,",line[i]);
        else if(line[i]==who && cnt==0){
            cnt=1;
            if(i==0 || line[i-1] == opp)
                isHalf=1;
        }
        else if(line[i]==who && cnt>0)
            cnt++;
        else if(line[i]!=who && cnt==0){
            cnt=0;
            isHalf=0;
        }

    }
    //printf("\n");
}

