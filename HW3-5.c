#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct set{
    int totalatt;
    int totalatted;
    int times;
}set;

typedef struct knights{
    int blood;
    int att;
    int time;
    int life;
}knights;

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    knights** knight = (knights**)malloc(sizeof(knights*)*n);
    set** dj = (set**)malloc(sizeof(set*)*n);
    for(int i=0;i<n;i++){
        knight[i]=(knights*)malloc(sizeof(knights));
        knight[i]->life=1;
        knight[i]->time=0;
        dj[i]=(set*)malloc(sizeof(set));
        dj[i]->totalatt=0;
        dj[i]->totalatted=0;
        dj[i]->times=0;
    }
    for(int i=0;i<n;i++)
        scanf("%d",&knight[i]->blood);
    for(int i=0;i<n;i++){
        scanf("%d",&knight[i]->att);
        dj[i]->totalatt+=knight[i]->att;
    }
    int *setnum=(int*)malloc(sizeof(int)*n);
    int **heap=(int**)malloc(sizeof(int*)*n);
    int *heaplen=(int*)malloc(sizeof(int)*n);
    int *heapsize=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        setnum[i]=i;
        heap[i]=(int*)malloc(sizeof(int)*8);
        heap[i][0]=i;
        heapsize[i]=1;
        heaplen[i]=8;
    }

    for(int i=0;i<m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        int atter=setnum[x-1], atted=setnum[y-1];
        if(atter==atted)
            continue;
        if(knight[x-1]->life==0 || knight[y-1]->life==0 || knight[y-1]->blood-dj[atted]->totalatted<=0)
            continue;
        while(dj[atter]->totalatted >= knight[heap[atter][0]]->blood){
            knight[heap[atter][0]]->life=0;
            knight[heap[atter][0]]->time=knight[heap[atter][0]]->time+dj[setnum[heap[atter][0]]]->times;
            dj[setnum[heap[atter][0]]]->totalatt-=knight[heap[atter][0]]->att;
            int tmp = heap[atter][heapsize[atter]-1];
            heap[atter][heapsize[atter]-1] = heap[atter][0];
            heap[atter][0] = tmp;
            int now = 0;
            heapsize[atter]-=1;
            while((now*2+1)<=heapsize[atter]-1){    
                if((now*2+1)==heapsize[atter]-1){
                    if(knight[heap[atter][now]]->blood > knight[heap[atter][now*2+1]]->blood){
                        tmp = heap[atter][now*2+1];
                        heap[atter][now*2+1] = heap[atter][now];
                        heap[atter][now] = tmp;    
                    }
                    break;
                }
                else{
                    if(knight[heap[atter][now*2+1]]->blood > knight[heap[atter][now*2+2]]->blood){
                        if(knight[heap[atter][now]]->blood > knight[heap[atter][now*2+2]]->blood){
                            tmp = heap[atter][now*2+2];
                            heap[atter][now*2+2] = heap[atter][now];                                
                            heap[atter][now] = tmp;
                            now = now*2+2;
                        }
                        else
                            break;
                    }
                    else{
                        if(knight[heap[atter][now]]->blood > knight[heap[atter][now*2+1]]->blood){
                            tmp = heap[atter][now*2+1];
                            heap[atter][now*2+1] = heap[atter][now];
                            heap[atter][now] = tmp;
                            now = now*2+1;
                        }
                        else
                            break;
                    }
                }
            }
        }
        if(knight[x-1]->life==0 || knight[y-1]->life==0 || knight[y-1]->blood-dj[atted]->totalatted<=0)
            continue;
        if(heapsize[atter]<=heapsize[atted]){
            dj[atted]->totalatted+=dj[atter]->totalatt;
            if(heaplen[atted]<(heapsize[atter]+heapsize[atted])){
                heaplen[atted]*=2;
                heap[atted] = (int*)realloc(heap[atted],heaplen[atted]*sizeof(int));
            }
            for(int j=0;j<heapsize[atter];j++){
                int heapify=heap[atter][j]; 
                knight[heapify]->time+=1;
                knight[heapify]->time+=dj[atter]->times;
                knight[heapify]->time-=dj[atted]->times;
                //dj[atted]->totalatt+=knight[heapify]->att;
                knight[heapify]->blood-=dj[atter]->totalatted;
                knight[heapify]->blood+=dj[atted]->totalatted;
                setnum[heapify]=atted;
                int last = heapsize[atted];
                heap[atted][last]=heapify;
                int compare = -1;
                if(((last-1)) >= 0)
                    compare = heap[atted][(last-1)/2];
                    while(knight[heapify]->blood<knight[compare]->blood){
                        int tmp = heap[atted][last];
                        heap[atted][last] = heap[atted][(last-1)/2];
                        heap[atted][(last-1)/2] = tmp;
                        last = (last-1)/2;
                        if(last<=0)
                            break;
                        compare = heap[atted][(last-1)/2];
                    }
                heapsize[atted]+=1;
            }
            dj[atted]->totalatt+=dj[atter]->totalatt;
            heapsize[atter]=0;
            free(heap[atter]);
        }
        else{
            if(heaplen[atter]<(heapsize[atter]+heapsize[atted])){
                heaplen[atter]*=2;
                heap[atter] = (int*)realloc(heap[atter],heaplen[atter]*sizeof(int));
            }
            dj[atter]->times+=1;
            for(int j=0;j<heapsize[atted];j++){
                int heapify=heap[atted][j];
                knight[heapify]->blood-=dj[atted]->totalatted;
                knight[heapify]->blood-=dj[atter]->totalatt;
                knight[heapify]->blood+=dj[atter]->totalatted;
                knight[heapify]->time+=dj[atted]->times;
                knight[heapify]->time-=dj[atter]->times;
                //dj[atter]->totalatt+=knight[heapify]->att;
                setnum[heapify]=atter;
                int last = heapsize[atter];
                heap[atter][last]=heapify;
                int compare = -1;
                if(((last-1)) >= 0)                  
                    compare = heap[atter][(last-1)/2];
                    while(knight[heapify]->blood < knight[compare]->blood){
                        int tmp = heap[atter][last];
                        heap[atter][last] = heap[atter][(last-1)/2];
                        heap[atter][(last-1)/2] = tmp;
                        last = (last-1)/2;
                        if(last<=0)
                            break;
                        compare = heap[atter][(last-1)/2];
                    }
                heapsize[atter]+=1;
            }
            dj[atter]->totalatt+=dj[atted]->totalatt;
            heapsize[atted]=0;
            free(heap[atted]);
        }
        /*
        for(int w=0;w<n;w++){
            if(knight[w]->life==1){
                int findset = setnum[w];
                printf("%d:%d ",knight[w]->time,dj[findset]->times);
            }
            else{
                printf("%d ",knight[w]->time);
            }
        }
        printf("\n");
        for(int w=0;w<n;w++){
            printf("%d ",setnum[w]);
        }
        printf("\n");
        */
        
    }
    for(int i=0;i<n;i++){
        if(knight[i]->life==1){
            int findset = setnum[i];
            printf("%d ",knight[i]->time+dj[findset]->times);
        }
        else{
            printf("%d ",knight[i]->time);
        }
    }
    return 0;
}