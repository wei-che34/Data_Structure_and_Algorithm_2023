#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(){
    int m,n;
    scanf("%d %d\n",&n,&m);
    char S[n], P[m];
    for(int i=0;i<n;i++)
        scanf("%c",&S[i]);
    scanf("\n");
    for(int i=0;i<m;i++)
        scanf("%c",&P[i]);
    long long max_1 = 1, max_2=1, max_3=1, max_4=1;
    for(int i=0;i<m-1;i++){
        max_1=(max_1*26)%60000049;
        max_2=(max_2*26)%16785407;
        max_3=(max_3*26)%39916801;
    }
    int map_1[60000049]={0};
    int map_2[16785407]={0};
    int map_3[39916801]={0};
    //int map_4[116101]={0};
    long long hash_1=0,hash_2=0,hash_3=0,hash_4=0;
    for(int i=0;i<m;i++){
        hash_1=((hash_1*26)+((int)P[i]-64))%60000049;
        hash_2=((hash_2*26)+((int)P[i]-64))%16785407;
        hash_3=((hash_3*26)+((int)P[i]-64))%39916801;
        //hash_4=((hash_4*26)+((int)P[i]-64))%116101;
    }
    map_1[hash_1]=1;
    map_2[hash_2]=1;
    map_3[hash_3]=1;
    //map_4[hash_4]=1;
    for(int i=0;i<m;i++){
        hash_1=(26*(hash_1 - max_1*((int)P[i]-64))+((int)P[i]-64))%60000049;
        hash_2=(26*(hash_2 - max_2*((int)P[i]-64))+((int)P[i]-64))%16785407;
        hash_3=(26*(hash_3 - max_3*((int)P[i]-64))+((int)P[i]-64))%39916801;
        //hash_4=(26*(hash_4 - max_4*((int)P[i]-64))+((int)P[i]-64))%116101;
        if(hash_1<0)
            hash_1+=60000049;
        if(hash_2<0)
            hash_2+=16785407;
        if(hash_3<0)
            hash_3+=39916801;
        //if(hash_4<0)
        //    hash_4+=116101;
        map_1[hash_1]=1;
        map_2[hash_2]=1;
        map_3[hash_3]=1;
        //map_4[hash_4]=1;
    }
    int ans = 0;
    hash_1=0, hash_2=0, hash_3=0, hash_4=0;
    for(int i=0;i<m;i++){
        hash_1=((hash_1*26)+((int)S[i]-64))%60000049;
        hash_2=((hash_2*26)+((int)S[i]-64))%16785407;
        hash_3=((hash_3*26)+((int)S[i]-64))%39916801;
        //hash_4=((hash_4*26)+((int)S[i]-64))%116101;
    }
    if(map_1[hash_1]==1){
        if(map_2[hash_2]==1){
            if(map_3[hash_3]==1)
                ans+=1;
        }
    }
    for(int i=1;i<n-m+1;i++){
        hash_1=(26*(hash_1 - max_1*((int)S[i-1]-64))+((int)S[i+m-1]-64))%60000049;
        hash_2=(26*(hash_2 - max_2*((int)S[i-1]-64))+((int)S[i+m-1]-64))%16785407;
        hash_3=(26*(hash_3 - max_3*((int)S[i-1]-64))+((int)S[i+m-1]-64))%39916801;
        //hash_4=(26*(hash_4 - max_4*((int)S[i-1]-64))+((int)S[i+m-1]-64))%116101;
        if(hash_1<0)
            hash_1+=60000049;
        if(hash_2<0)
            hash_2+=16785407;
        if(hash_3<0)
            hash_3+=39916801;
        //if(hash_4<0)
        //    hash_4+=116101;
        if(map_1[hash_1]==1){
            if(map_2[hash_2]==1){
                if(map_3[hash_3]==1)
                    ans+=1;
            }
        }
    }
    printf("%d",ans);
    return 0;
}