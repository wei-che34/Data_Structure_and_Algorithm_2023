#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct Cat{
    int appetite;
    int color;
    struct Cat *next;
    struct Cat *prev;
}Cat;

int cmpfunc (const void *a,const void *b){
    return (*(Cat**)a)->color - (*(Cat**)b)->color;
}

int cmpapp (const void *a,const void *b){
    return (*(Cat**)a)->appetite - (*(Cat**)b)->appetite;
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    Cat **DSA = (Cat**)malloc(sizeof(Cat*)*n);
    for(int i=0;i<n;i++){       
        DSA[i]=(Cat*)malloc(sizeof(Cat));
        DSA[i]->next=NULL;
        DSA[i]->prev=NULL;
    }
    Cat **inDSA = (Cat**)malloc(sizeof(Cat*)*n);
    for(int i=0;i<n;i++)
        inDSA[i]=DSA[i];
    for(int i=0;i<n;i++)
        scanf("%d",&DSA[i]->appetite);        
    for(int i=0;i<n;i++)
        scanf("%d",&DSA[i]->color);
    qsort(DSA,n,sizeof(DSA[0]),cmpfunc);
    int colorCount=1;
    for(int i=0;i<n-1;i++){
        if(DSA[i+1]->color!=DSA[i]->color)
            colorCount+=1;
    }
    Cat ***unDSA = (Cat***)malloc(sizeof(Cat**)*colorCount);
    int *color = (int*)malloc(sizeof(int)*colorCount);
    int eachCount=1;
    int cursor=0;  
    for(int i=0;i<colorCount;i++){
        cursor++;
        if(cursor<n){
            while(DSA[cursor]->color==DSA[cursor-1]->color){
                cursor++;
                eachCount++;
                if(cursor>=n)
                    break;
            }
        }
        unDSA[i]=(Cat**)malloc(sizeof(Cat*)*eachCount);
        color[i]=eachCount;
        eachCount=1;
    }
    cursor=0;
    for(int i=0;i<colorCount;i++){
        for(int j=0;j<color[i];j++){
            unDSA[i][j]=DSA[cursor];
            cursor++;
        }
    }
    for(int i=0;i<colorCount;i++)
        qsort(unDSA[i],color[i],sizeof(unDSA[0][0]),cmpapp);
    qsort(DSA,n,sizeof(DSA[0]),cmpapp);
    Cat *min = DSA[0];
    for(int i=1;i<n;i++){
        DSA[i]->prev = min;
        min->next=DSA[i];
        min = DSA[i];
    }
    Cat *max = DSA[n-1];
    min = DSA[0];
    int *magic = calloc(colorCount,sizeof(int));
    int count=0;
    int event;
    for(int i=0;i<m;i++){
        scanf("%d ",&event);
        if(event==1){
            int c,l,r;
            scanf("%d %d %d",&c,&l,&r);
            int a=0;
            int b=colorCount-1;
            int mid;
            int key=-1;
            while(a<=b){
                mid=(a+b)/2;
                if(unDSA[mid][0]->color==c){
                    key=mid;
                    break;
                }
                else if(unDSA[mid][0]->color>c)
                    b=mid-1;
                else
                    a=mid+1;
            }
            if(key==-1){
                printf("%d\n",0);
                continue;
            }
            a=magic[key];
            b=color[key]+magic[key]-1;
            int lkey=-1, rkey=-1;
            int re;
            while(a<=b){    
                mid=(a+b)/2;
                re = mid%color[key];
                if(re<0)
                    re+=color[key];
                if(unDSA[key][re]->appetite==l){
                    lkey=mid;
                    break;
                }
                else if(unDSA[key][re]->appetite>l)
                    b=mid-1;
                else
                    a=mid+1;
            }
            if(lkey==-1)
                lkey=a;
            a=magic[key];
            b=color[key]+magic[key]-1;
            while (a<=b){
               mid=(a+b)/2;
               re = mid%color[key];
               if(re<0)
                    re+=color[key];
               if(unDSA[key][re]->appetite==r){
                    rkey=mid;
                    break;
                }
                else if(unDSA[key][re]->appetite>r)
                    b=mid-1;
                else
                    a=mid+1;
            }
            if(rkey==-1)
                rkey=b;
            printf("%d\n",rkey-lkey+1);
            count=0;
        }
        if(event==2){
            int k;
            scanf("%d",&k);
            int tmp;
            Cat *tmpcat;
            if(inDSA[k]->next!=NULL){
                if(inDSA[k]->color==inDSA[k]->next->color){
                    int a=0;
                    int b=colorCount-1;
                    int mid, key;
                    while(a<=b){
                        mid=(a+b)/2;
                        if(unDSA[mid][0]->color==inDSA[k]->color){
                            key=mid;
                            break;
                        }
                        else if(unDSA[mid][0]->color>inDSA[k]->color)
                            b=mid-1;
                        else
                            a=mid+1;
                    }
                    a=magic[key];
                    b=color[key]+magic[key]-1;
                    int re;
                    int swap;
                    while(a<=b){                    
                        mid=(a+b)/2;
                        re=mid%color[key];
                        if(re<0)
                            re+=color[key];
                        if(unDSA[key][re]->appetite==inDSA[k]->appetite){
                            swap=mid;
                            break;
                        }
                        else if(unDSA[key][re]->appetite>inDSA[k]->appetite)
                            b=mid-1;
                        else
                            a=mid+1;
                    }
                    re = swap%color[key];
                    if(re<0)
                        re+=color[key];
                    int re2 = (swap+1)%color[key];
                    if(re2<0)
                        re2+=color[key];
                    tmpcat=unDSA[key][re2];
                    unDSA[key][re2]=unDSA[key][re];
                    unDSA[key][re]=tmpcat;
                }
                tmp = inDSA[k]->appetite;
                inDSA[k]->appetite=inDSA[k]->next->appetite;
                inDSA[k]->next->appetite=tmp;
                tmpcat = inDSA[k]->next;
                if(inDSA[k]->prev!=NULL)                
                    inDSA[k]->prev->next = tmpcat;
                inDSA[k]->next->prev = inDSA[k]->prev;
                inDSA[k]->next=tmpcat->next;
                inDSA[k]->prev=tmpcat;   
                if(tmpcat->next!=NULL)
                    tmpcat->next->prev=inDSA[k];
                tmpcat->next=inDSA[k];
                if(max->next!=NULL)
                    max = max->next;
                if(min->prev!=NULL)
                    min = min->prev;
            }
        }
        if(event==3){
            int c,s,t;
            scanf("%d %d %d",&c,&s,&t);
            int a=0;
            int b=colorCount-1;
            int mid;
            int key=-1;
            while(a<=b){
                mid=(a+b)/2;
                if(unDSA[mid][0]->color==c){
                    key=mid;
                    break;
                }
                else if(unDSA[mid][0]->color>c)
                    b=mid-1;
                else
                    a=mid+1;
            }
            if(s==1 && t==1){
                int index = (color[key]+magic[key]-1)%color[key];
                if(index<0)
                    index+=color[key];
                unDSA[key][index]->appetite = max->appetite+1;
                if(unDSA[key][index]!=max){
                    unDSA[key][index]->prev->next = unDSA[key][index]->next;
                    unDSA[key][index]->next->prev = unDSA[key][index]->prev;
                    unDSA[key][index]->next=NULL;
                    unDSA[key][index]->prev=max;
                    max->next = unDSA[key][index];
                    max = unDSA[key][index];
                }
            }
            else if(s==1 && t==0){
                int index = (color[key]+magic[key]-1)%color[key];
                if(index<0)
                    index+=color[key];
                unDSA[key][index]->appetite = min->appetite-1;
                if(unDSA[key][index]!=min && unDSA[key][index]!=max){
                    unDSA[key][index]->prev->next = unDSA[key][index]->next;
                    unDSA[key][index]->next->prev = unDSA[key][index]->prev;
                    unDSA[key][index]->next=min;
                    unDSA[key][index]->prev=NULL;
                    min->prev = unDSA[key][index];
                    min = unDSA[key][index];
                }
                else if(unDSA[key][index]!=min && unDSA[key][index]==max){
                    unDSA[key][index]->prev->next = unDSA[key][index]->next;
                    max = unDSA[key][index]->prev;
                    unDSA[key][index]->next=min;
                    unDSA[key][index]->prev=NULL;
                    min->prev = unDSA[key][index];
                    min = unDSA[key][index];
                }
                magic[key]-=1;
            }
            else if(s==0 && t==1){
                int index = magic[key]%color[key];
                if(index<0)
                    index+=color[key];
                unDSA[key][index]->appetite = max->appetite+1;
                if(unDSA[key][index]!=max && unDSA[key][index]!=min){
                    unDSA[key][index]->prev->next = unDSA[key][index]->next;
                    unDSA[key][index]->next->prev = unDSA[key][index]->prev;
                    unDSA[key][index]->next=NULL;
                    unDSA[key][index]->prev=max;
                    max->next = unDSA[key][index];
                    max = unDSA[key][index];
                }
                else if(unDSA[key][index]!=max && unDSA[key][index]==min){
                    unDSA[key][index]->next->prev = unDSA[key][index]->prev;
                    min = unDSA[key][index]->next;
                    unDSA[key][index]->next=NULL;
                    unDSA[key][index]->prev=max;
                    max->next = unDSA[key][index];
                    max = unDSA[key][index];
                }
                magic[key]+=1;
            }
            else if(s==0 && t==0){
                int index = magic[key]%color[key];
                if(index<0)
                    index+=color[key];
                unDSA[key][index]->appetite = min->appetite-1;
                if(unDSA[key][index]!=min){
                    unDSA[key][index]->prev->next = unDSA[key][index]->next;
                    unDSA[key][index]->next->prev = unDSA[key][index]->prev;
                    unDSA[key][index]->next=min;
                    unDSA[key][index]->prev=NULL;
                    min->prev = unDSA[key][index];
                    min = unDSA[key][index];
                }
            }
        }
    }    
    return 0;
}