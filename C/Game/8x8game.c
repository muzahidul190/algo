#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
int chk=0,gameOver=0,si=0,sj=0,ei=0,ej=0,sum=0,k,back[65];
char dir[9];
void tables(char room[9][9],int n);
void check(char res[9][9],char item);
void goback(char tbl[9][9],int stck[65]);
int main(){         ///By Muzahidul Islam...

    int i,n,m=0,q;
    char table[9][9],p,bck,play,p1[20],p2[20],t[20],winner[20];
    memset(back,0,65*sizeof(back[0]));

    k=0;
    strcpy(table," 123456781        2        3        4        5        6        7        8        ");
    while(k<64){
        if(k==0){
            while(1){
                printf("\n\tEnter game rule (3-8).\n\tinfo: It indicates how many item you need to arrange to win the game.\t");
                chk = (int) getch()-48;
                gameOver=0;
                if(chk<3 || chk>8)
                    system("cls"),printf("\n\aPlease choose one number between 3 to 8.\n");
                else
                    break;
            }
            system("cls");
            printf("\n\tWelcome to the Game.\n\tEnter player 1 name:\t");
            scanf(" %[^\n]s",p1);
            printf("\tEnter player 2 name:\t");
            scanf(" %[^\n]s",p2);
        }
        court:check(table,p);
        system("cls");


        tables(table,back[k]);      ///Prints the board
        if(k<64){
            if(k%2==0){         ///Determines current player
                p = 79;
                strcpy(t,p1);
                strcpy(winner,p2);
            }else{
                p = 254;
                strcpy(t,p2);
                strcpy(winner,p1);
            }
            if(gameOver){       ///Checks if game is over or not
                printf("\n\tGame Over : %s Wins\n\n",winner);
                k=66;
                goto ply;
            }
            entry:printf("\n\tN.B: Press '0' anytime to terminate the game.\n\tAnd 'b' to take a move back.\n\t%s's turn.:\t",t);
            n = getch()-48;         ///Main input from players
            if(n>0&&n<9) m = n;     ///Saves value of n if it is usable
            if(n==0){               ///If 0 is pressed
                system("cls");
                tables(table,back[k]);
                printf("\n\aDo you want to stop the current game?(y/n):\t");
                scanf(" %c",&play);
                if(play=='y'||play=='Y'){
                    printf("\n\t\aGame terminated!\n\n");
                    k=66;
                    goto ply;
                }else{
                    goto entry;
                }
            }
            if(!(n>0&&n<9)){        ///If unusable key is pressed
                system("cls");
                tables(table,back[k]);
                if((char)(n+48)=='b' && k!=0){  ///If b is pressed
                    printf("\n\aPermission needed from %s. Press y/n\t",t);
                    scanf(" %c",&bck);
                    if(bck == 'y'){
                        goback(table,back);
                        strcpy(dir,"         ");
                        dir[back[k]] = 30;
                        k--;
                        dir[back[k]] = 31;
                        goto court;
                    }else{
                        printf("\nPermission not acquired\n");
                    }
                }else if(k==0 && (char)(n+48)=='b'){
                    printf("\n\tNo turn to take back!\n");
                }else{
                    printf("\n\a '%c' is not valid Column number, Please enter correct COLUMN, (1-8).\n",n+48);
                }

                goto entry;
            }

            strcpy(dir,"         ");
            for(q=2;q<9;q++){
                if(table[1][n]!=' '){   ///If column is filled up
                    system("cls");
                    tables(table,back[k]);
                    printf("\n\a%d COLUMN is Filled up! Choose another COLUMN\n",n);
                    goto entry;
                }
                if(table[q][n]!=' '){   ///Creating animation of falling chips/coins
                    for(i=1;i<q;i++){
                        table[i][n] = p;
                        if(i!=1) table[i-1][n] = ' ';
                        system("cls");
                        tables(table,back[k]);
                        sleep(20);
                    }
                    break;
                }else if(table[8][n]==' '){
                    for(i=1;i<9;i++){
                        table[i][n] = p;
                        if(i!=1) table[i-1][n] = ' ';
                        system("cls");
                        tables(table,back[k]);
                        sleep(20);
                    }
                    break;
                }
            }
        }
        ply:k++;        ///Turn count increases
        if(k<66)
            back[k] = m;  ///back STACK is updated
        if(k>63){
            if(k==64){
                goto court;
            }else{
                palyagain:printf("\n\aDo you want to play again?:(y/n)\t");
                scanf(" %c",&play);
                if(play=='y' || play=='Y'){
                    k = 0;
                    strcpy(table," 123456781        2        3        4        5        6        7        8        ");
                    system("cls");
                }
            }
        }
    }

    return 0;
}
void tables(char room[9][9],int n){
    int i,j;
    if(k<64) printf("\n\tGame Rule: \"%d\" tile(s)",chk),printf("\n\tTurn %2d:",k+1);
    else printf("\n\t\t******Game DRAW******");
    dir[back[k-1]] = ' ';
    if(n!=0)
        dir[n] = 31;

    printf("\n\t");
    for(i=0;i<9;i++){
        printf(" %c  ",dir[i]);
    }
        printf("\n");
    for(i=0;i<9;i++){
        printf("\t");
        for(j=0;j<9;j++){
            if(gameOver){
                if(si==ei&&sj<=j&&ej>=j && i==si) printf("(%c)|",room[i][j]);
                else if(sj==ej&&si<=i&&ei>=i && j==sj) printf("(%c)|",room[i][j]);
                else if(si<ei&&i>=si&&i<=ei&&j>=sj&&j<=ej&&i-j==si-sj) printf("(%c)|",room[i][j]);
                else if(si>ei&&i<=si&&i>=ei&&j>=sj&&j<=ej&&i+j==si+sj) printf("(%c)|",room[i][j]);
                else printf(" %c |",room[i][j]);
            }
            else printf(" %c |",room[i][j]);
            if(j==8) printf("\n\t---|___|___|___|___|___|___|___|___|");
        }
        printf("\n");
    }
}
void sleep(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void check(char res[9][9],char p){
    int i,j,r,s,cont=0;
    for(j=0;j<9;j++){       ///Horizontal
        ej=j,ei=8;
        for(i=8;i>0;i--){
            if(res[i][j]==p)
                cont++;
            else
                cont=0,ei=i-1;
            if(chk<=cont){
                si=i,sj=j;
                gameOver=1;
                return;
            }
        }
        cont=0;
    }
    cont=0;
    for(i=8;i>0;i--){       ///Vertical
        si=i,sj=1;
        for(j=1;j<9;j++){
            if(res[i][j]==p)
                cont++;
            else
                cont=0,sj=j+1;
            if(chk<=cont){
                ei=i,ej=j;
                gameOver=1;
                return;
            }
        }
        cont=0;
    }
    cont=0;
    for(i=8;i>0;i--){       ///Secondary Diagonal
        for(j=1;j<9;j++){
            si=i;sj=j;
            for(r=i,s=j;res[r][s]==p;r--,s++){
                cont++;
                if(chk<=cont){
                    ei=r,ej=s;
                    gameOver=1;
                    return;
                }
            }
            cont=0;
        }
    }
    cont=0;
    for(i=8;i>0;i--){       ///Principle Diagonal
        for(j=8;j>0;j--){
            ei=i;ej=j;
            for(r=i,s=j;res[r][s]==p;r--,s--){
                cont++;
                if(chk<=cont){
                    si=r,sj=s;
                    gameOver=1;
                    return;
                }
            }
            cont=0;
        }
    }
}
void goback(char tbl[9][9],int stck[65]){
    int col,i,j=0;
    col = stck[k];

    for(i=0;i<9;i++){
        printf("\t");
        if(tbl[i][col]!=' ' && i!=0){
            tbl[j][col] = ' ';
            break;
        }
        j++;
    }



}



















