#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct Price{
    long long price;
    long long day;
}Price;

typedef struct Node{
    Price **heap;
    struct Node *child;
    struct Node *sibling;
    struct Node *end;
}Node;

long long max;

long long* traverse(Node *root, int c){
    long long *total = calloc(2,sizeof(long long));
    if(root==NULL)
        return total;
    total[0] = root->heap[0]->price;
    total[1] = 1;
    long long* add = traverse(root->child,c);
    total[0] += add[0];
    total[1] += add[1];
    if(total[0]<=c && total[1]>max)
        max=total[1];
    add = traverse(root->sibling,c);
    total[0] += add[0];
    total[1] += add[1];
    printf("%lld %lld",total[0],total[1]);
    return total;
}

int main(){
    Price *tmp;
    long long n, m, c;
    scanf("%lld %lld %lld",&n,&m,&c);
    Node **tree = (Node**)malloc(sizeof(Node*)*n);
    for(int i=0;i<n;i++){
        tree[i]=(Node*)malloc(sizeof(Node));
        tree[i]->heap=(Price**)malloc(sizeof(Price*)*m);
        for(int j=0;j<m;j++)
            tree[i]->heap[j]=(Price*)malloc(sizeof(Price));
        tree[i]->child=NULL;
        tree[i]->sibling=NULL;
    }
    long long num;
    Node *current;
    for(int i=1;i<n;i++){  
        scanf("%lld",&num);
        if(tree[num-1]->child==NULL){
            tree[num-1]->child=tree[i];
            tree[num-1]->end=tree[i];
        }
        else{
            tree[num-1]->end->sibling=tree[i];
            tree[num-1]->end=tree[i];
        }
    }

    long long e,d;
    long long *cou;
    cou = calloc(n,sizeof(long long));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%lld %lld",&e,&d);
            tree[j]->heap[i]->price = e;
            tree[j]->heap[i]->day = i+d;
            if(i!=0){
                long long cn = i;
                if(cou[j]!=0){
                    cn = i-cou[j];
                    tmp = tree[j]->heap[cn];
                    tree[j]->heap[cn] = tree[j]->heap[i];
                    tree[j]->heap[i] = tmp;
                }
                while(tree[j]->heap[cn]->price < tree[j]->heap[(cn-1)/2]->price){
                    tmp = tree[j]->heap[cn];
                    tree[j]->heap[cn] = tree[j]->heap[(cn-1)/2];
                    tree[j]->heap[(cn-1)/2] = tmp;
                    cn = (cn-1)/2;
                    if(cn==0)
                        break;
                }
            }
            long long ct;
            while(tree[j]->heap[0]->day<i){
                tree[j]->heap[0]->price=10000000000;
                ct = i-cou[j];
                tmp = tree[j]->heap[ct];
                tree[j]->heap[ct] = tree[j]->heap[0];
                tree[j]->heap[0] = tmp;
                ct = 0;
                while((ct+1)*2-1 <= i){
                    if((ct+1)*2-1 == i){
                        if(tree[j]->heap[ct]->price>tree[j]->heap[(ct+1)*2-1]->price){
                            tmp = tree[j]->heap[ct];
                            tree[j]->heap[ct] = tree[j]->heap[(ct+1)*2-1];
                            tree[j]->heap[(ct+1)*2-1] = tmp;
                        }
                        break;
                    }
                    else{
                        if(tree[j]->heap[(ct+1)*2-1]->price>tree[j]->heap[(ct+1)*2]->price){
                            if(tree[j]->heap[ct]->price>tree[j]->heap[(ct+1)*2]->price){
                                tmp = tree[j]->heap[ct];
                                tree[j]->heap[ct] = tree[j]->heap[(ct+1)*2];
                                tree[j]->heap[(ct+1)*2] = tmp;
                                ct = (ct+1)*2;
                            }
                            else
                                break;
                        }
                        else{
                            if(tree[j]->heap[ct]->price>tree[j]->heap[(ct+1)*2-1]->price){
                                tmp = tree[j]->heap[ct];
                                tree[j]->heap[ct] = tree[j]->heap[(ct+1)*2-1];
                                tree[j]->heap[(ct+1)*2-1] = tmp;
                                ct = (ct+1)*2-1;
                            }
                            else
                                break;
                        }
                    }
                }
                cou[j]+=1;    
            }
        }
        max=0;
        traverse(tree[0],c);
        printf("%d\n",max);
    }
    free(cou);
    return 0;
}