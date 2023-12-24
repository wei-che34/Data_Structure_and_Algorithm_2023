#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct BigInt{
    int array[300];
    int length;
};

void read_from_string(struct BigInt* big, char* str)
{
    int i=0;
    size_t len=strlen(str);
    memset(big->array, 0, sizeof(int)*300);
    for(i=len-1; i>=0; --i){
        big->array[len - i - 1] = str[i] - '0';}
    big->length = strlen(str);
}

int GetTwo(struct BigInt num){
    if(num.array[0]%2==0)
        return 0;
    else
        return 1;
};

struct BigInt Sub(struct BigInt num1, struct BigInt num2){
    int borrow=0;
    struct BigInt num3; 
    for(int i=0;i<300;i++){
        num3.array[i] = num1.array[i]-num2.array[i]-borrow;
        if(num3.array[i]<0){
            borrow=1;
            num3.array[i]+=10;
        }
        else
            borrow=0;
    }
    return num3;
};

struct BigInt DivTwo(struct BigInt num){
    int remain=0;
    struct BigInt renum;
    int i=299;
    for(i=299; i>=0 && num.array[i]==0; --i){
        renum.array[i]=0;
    }
    while(i>=0){
        if((num.array[i]+remain)%2==1){
            renum.array[i] = (num.array[i]+remain-1)/2;
            remain=10;
        }
        else{
            renum.array[i] = (num.array[i]+remain)/2;
            remain=0;
        }       
        --i;
    }
    return renum;
}

struct BigInt MulTwo(struct BigInt num){
    struct BigInt renum;
    int carry=0;
    for(int i=0;i<300;i++){
        if((num.array[i]*2+carry)>=10){
            renum.array[i] = (num.array[i]*2+carry-10);
            carry = 1;
        }
        else{
            renum.array[i] = (num.array[i]*2);
            carry = 0;
        }
    }
    return renum;
}

struct BigInt Mul(struct BigInt num1, struct BigInt num2){
    struct BigInt renum;
    int carry=0;
    memset(renum.array, 0, sizeof(int)*300);
    for(int i=0;i<300;i++){
        if(num1.array[i]==0)
            continue;
        for(int j=0;j<300;j++)
            renum.array[i+j]+=num1.array[i]*num2.array[j];
    }
    for(int i=0; i<300; ++i) {
        renum.array[i]+=carry;
        carry = renum.array[i] / 10;
        renum.array[i] %= 10;
    }
    return renum;
}

int Compare(struct BigInt num1, struct BigInt num2){
    for(int i=299;i>=0;i--){
        if(num1.array[i]!=num2.array[i]){
            if(num1.array[i]>num2.array[i])
                return 1;
            else
                return 0;
        }
    }
}

void BigPrint(struct BigInt num){
    int i=300-1;
    for(i=300-1; i>=0 && num.array[i]==0; --i);
    while(i>=0){
        printf("%d", num.array[i]), --i;
    }
}

int IsZero(struct BigInt num){
    for(int i=0;i<300;i++){
        if(num.array[i]!=0){
            return 1;
        }       
    } 
    return 0;
}

struct BigInt GCD(struct BigInt num1,struct BigInt num2);

int main(void){
    struct BigInt num1;
    struct BigInt num2;
    char *str1 = malloc(sizeof(char)*300);
    scanf("%s", str1);
    char *str2 = malloc(sizeof(char)*300);
    scanf("%s", str2);
    read_from_string(&num1,str1);
    read_from_string(&num2,str2);
    BigPrint(GCD(num1,num2));
    
    return 0;
    }

struct BigInt GCD(struct BigInt num1,struct BigInt num2){
    //struct BigInt ans;
    struct BigInt ins;
    int ans=1;
    //read_from_string(&ans,"1");
    while(IsZero(num1)!=0 && IsZero(num2)!=0){
        if(GetTwo(num1) == 0 && GetTwo(num2) ==0){
            num1 = DivTwo(num1);
            num2 = DivTwo(num2);
            //ans = MulTwo(ans);
            ans = ans*2;
        }
        else if(GetTwo(num1) == 0 && GetTwo(num2) ==1){
            num1 = DivTwo(num1);
        }
        else if(GetTwo(num1) == 1 && GetTwo(num2) ==0){
            num2 = DivTwo(num2);
        }
        if(Compare(num1,num2)==1){
            ins = num2;
            num2 = num1;
            num1 = ins;
        }
        num2 = Sub(num2,num1);
        //BigPrint(ans);
        //printf("\n");
    }
    char strans[100];
    sprintf(strans, "%d", ans);
    struct BigInt bigAns;
    read_from_string(&bigAns,strans);
    return Mul(bigAns,num1);
}
