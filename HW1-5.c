#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct Node{
    int node;
    int num;
    int point;
    int old;
    struct Node *nxt;
    struct Node *prev;
}Node;

void destory(Node *tail ){
    if (tail!=NULL){
        destory(tail ->prev );
        memset(tail , 0, sizeof(Node));
        free(tail );
    }
}

int main(){
    int n, m;
    scanf("%d",&n);
    scanf("%d",&m);
    struct Node *current, *previous, *first, *last, *killed; 
    int count = 0;
    struct Node *newer, *king, *warrior;
    int rev=0;
    int crev=0;
    int dead=0;
    for(int i=0;i<n;i++){
        current = malloc(sizeof(Node));
        scanf("%d",&current->node);
        current->num = i+1;
        if(i==0){
            current->old=crev;
            current->prev = NULL;
            previous = current;
            first = current;
            king = current;
        }
        else{
            current->old=crev;
            previous->nxt = current;
            current->prev = previous;
            current->nxt = NULL;
            previous = current;
        }
        if(i==n-1)
            last = current;
        newer = current;    
        if(newer->node > king->node)
            king=newer;
        current->point=m-i+dead;
        warrior = newer->prev;
        count++;
        printf("Round %d:",i+1);
        while(warrior!=NULL){
            if(warrior->node < newer->node){
                dead++;
                newer->point++;
                printf(" %d,%d",warrior->num,(warrior->point)*(i+1-warrior->num)+crev-warrior->old);
                if(warrior->prev!=NULL)
                    warrior->prev->nxt = warrior->nxt;
                warrior->nxt->prev = warrior->prev;
                killed = warrior;
                warrior = warrior->prev;
                count--;
                memset(killed , 0, sizeof(Node));
                free(killed);
            }
            else{
                break;
            }
        }        
        if(count>m){
            rev++;
            printf(" %d,%d",king->num,(king->point)*(i+1-king->num)+crev-king->old);
            if(king->prev!=NULL)
                king->prev->nxt = king->nxt;
            king->nxt->prev = king->prev;
            killed = king;
            king = king->nxt;
            memset(killed , 0, sizeof(Node));
            free(killed);
            count--;
        }
        newer = newer->nxt;
        printf("\n");
        crev+=rev;
    }
    printf("Final:");
    while(last!=NULL){
        printf(" %d,%d",last->num,(last->point)*(n+1-last->num)+crev-last->old);
        last = last->prev;
    }
    destory(last);
    return 0;
}