#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define q1 99990001
#define q2 59393339
#define q3 43112609
//#define q4 42643801
//#define q5 39916801

//#define q1 100501
//#define q2 104551
//#define q3 59263

int main(){
    int n,q;
    scanf("%d %d\n",&n,&q);
    int map_1[q1]={0};
    int map_2[q2]={0};
    int map_3[q3]={0};
    //int map_4[q4]={0};
    //int map_5[q5]={0};
    long long count=0;
    for(int i=0;i<n;i++){
        char S[1000002];
        scanf("%s",S);
        long long max_1=1, max_2=1, max_3=1, max_4=1, max_5=1;
        for(int j=0;j<strlen(S)-1;j++){
            max_1=(max_1*26)%q1;
            max_2=(max_2*26)%q2;
            max_3=(max_3*26)%q3;
            //max_4=(max_4*26)%q4;
            //max_5=(max_5*26)%q5;
        }
        long long hash_1=0, hash_2=0, hash_3=0, hash_4=0, hash_5=0;
        for(int j=0;j<strlen(S);j++){
            hash_1=((hash_1*26)+((int)S[j]-96))%q1;
            hash_2=((hash_2*26)+((int)S[j]-96))%q2;
            hash_3=((hash_3*26)+((int)S[j]-96))%q3;
            //hash_4=((hash_4*26)+((int)S[j]-96))%q4;
            //hash_5=((hash_5*26)+((int)S[j]-96))%q5;
        }
        int hit=0;
        for(int j=0;j<strlen(S);j++){
            if(map_1[hash_1]!=0 && map_2[hash_2]!=0 && map_3[hash_3]!=0){ 
				//&& map_4[hash_4]!=0 && map_5[hash_5]!=0
                count+=map_1[hash_1];
                map_1[hash_1]++;
                map_2[hash_2]++;
                map_3[hash_3]++;
                //map_4[hash_4]++;
                //map_5[hash_5]++;
                hit=1;
                break;
            }
            hash_1=(26*(hash_1-max_1*((int)S[j]-96))+((int)S[j]-96))%q1;
            hash_2=(26*(hash_2-max_2*((int)S[j]-96))+((int)S[j]-96))%q2;
            hash_3=(26*(hash_3-max_3*((int)S[j]-96))+((int)S[j]-96))%q3;
            //hash_4=(26*(hash_4-max_4*((int)S[j]-96))+((int)S[j]-96))%q4;
            //hash_5=(26*(hash_5-max_5*((int)S[j]-96))+((int)S[j]-96))%q5;
            if(hash_1<0)
                hash_1+=q1;
            if(hash_2<0)
                hash_2+=q2;
            if(hash_3<0)
                hash_3+=q3;
            //if(hash_4<0)
            //    hash_4+=q4;
            //if(hash_5<0)
            //    hash_5+=q5;
        }
        if(hit==0){
            map_1[hash_1]=1;
            map_2[hash_2]=1;
            map_3[hash_3]=1;
            //map_4[hash_4]=1;
            //map_5[hash_5]=1;
        }
    }
    printf("%lld\n",count);
    for(int i=0;i<q;i++){
        int typ;
        char S[1000002];
        scanf("%d ",&typ);
        scanf("%s",S);
        if(typ==1){
            long long max_1=1, max_2=1, max_3=1, max_4=1, max_5=1;
            for(int j=0;j<strlen(S)-1;j++){
                max_1=(max_1*26)%q1;
                max_2=(max_2*26)%q2;
                max_3=(max_3*26)%q3;
                //max_4=(max_4*26)%q4;
                //max_5=(max_5*26)%q5;
            }
            long long hash_1=0, hash_2=0, hash_3=0, hash_4=0, hash_5=0;
            for(int j=0;j<strlen(S);j++){
                hash_1=((hash_1*26)+((int)S[j]-96))%q1;
                hash_2=((hash_2*26)+((int)S[j]-96))%q2;
                hash_3=((hash_3*26)+((int)S[j]-96))%q3;
                //hash_4=((hash_4*26)+((int)S[j]-96))%q4;
                //hash_5=((hash_5*26)+((int)S[j]-96))%q5;
            }
            int hit=0;
            for(int j=0;j<strlen(S);j++){
                if(map_1[hash_1]!=0 && map_2[hash_2]!=0 && map_3[hash_3]!=0){
					//&& map_4[hash_4]!=0 && map_5[hash_5]!=0
                    count+=map_1[hash_1];
                    map_1[hash_1]++;
                    map_2[hash_2]++;
                    map_3[hash_3]++;
                    //map_4[hash_4]++;
                    //map_5[hash_5]++;
                    hit=1;
                    break;
                }
                hash_1=(26*(hash_1-max_1*((int)S[j]-96))+((int)S[j]-96))%q1;
                hash_2=(26*(hash_2-max_2*((int)S[j]-96))+((int)S[j]-96))%q2;
                hash_3=(26*(hash_3-max_3*((int)S[j]-96))+((int)S[j]-96))%q3;
                //hash_4=(26*(hash_4-max_4*((int)S[j]-96))+((int)S[j]-96))%q4;
                //hash_5=(26*(hash_5-max_5*((int)S[j]-96))+((int)S[j]-96))%q5;
                if(hash_1<0)
                    hash_1+=q1;
                if(hash_2<0)
                    hash_2+=q2;
                if(hash_3<0)
                    hash_3+=q3;
                //if(hash_4<0)
                //    hash_4+=q4;
                //if(hash_5<0)
                //    hash_5+=q5;
            }
            if(hit==0){
                map_1[hash_1]=1;
                map_2[hash_2]=1;
                map_3[hash_3]=1;
                //map_4[hash_4]=1;
                //map_5[hash_5]=1;
            }
        }
        else{
            long long max_1=1, max_2=1, max_3=1, max_4=1, max_5=1;
            for(int j=0;j<strlen(S)-1;j++){
                max_1=(max_1*26)%q1;
                max_2=(max_2*26)%q2;
                max_3=(max_3*26)%q3;
                //max_4=(max_4*26)%q4;
                //max_5=(max_5*26)%q5;
            }
            long long hash_1=0, hash_2=0, hash_3=0, hash_4=0, hash_5=0;
            for(int j=0;j<strlen(S);j++){
                hash_1=((hash_1*26)+((int)S[j]-96))%q1;
                hash_2=((hash_2*26)+((int)S[j]-96))%q2;
                hash_3=((hash_3*26)+((int)S[j]-96))%q3;
                //hash_4=((hash_4*26)+((int)S[j]-96))%q4;
                //hash_5=((hash_5*26)+((int)S[j]-96))%q5;
            }

            for(int j=0;j<strlen(S);j++){
                if(map_1[hash_1]!=0 && map_2[hash_2]!=0 && map_3[hash_3]!=0){
					// && map_4[hash_4]!=0 && map_5[hash_5]!=0
                    count-=(map_1[hash_1]-1);
                    map_1[hash_1]--;
                    map_2[hash_2]--;
                    map_3[hash_3]--;
                    //map_4[hash_4]--;
                    //map_5[hash_5]--;
                    break;
                }
                hash_1=(26*(hash_1-max_1*((int)S[j]-96))+((int)S[j]-96))%q1;
                hash_2=(26*(hash_2-max_2*((int)S[j]-96))+((int)S[j]-96))%q2;
                hash_3=(26*(hash_3-max_3*((int)S[j]-96))+((int)S[j]-96))%q3;
                //hash_4=(26*(hash_4-max_4*((int)S[j]-96))+((int)S[j]-96))%q4;
                //hash_5=(26*(hash_5-max_5*((int)S[j]-96))+((int)S[j]-96))%q5;
                if(hash_1<0)
                    hash_1+=q1;
                if(hash_2<0)
                    hash_2+=q2;
                if(hash_3<0)
                    hash_3+=q3;
                //if(hash_4<0)
                //    hash_4+=q4;
                //if(hash_5<0)
                //    hash_5+=q5;
            }
        }
        printf("%lld\n",count);
    }
    return 0;
}
