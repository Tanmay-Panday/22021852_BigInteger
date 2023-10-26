#include "BigInteger.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node* newnode(int x){
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->data=x;
    temp->next=NULL;
}

struct BigInteger truncate(struct BigInteger big){
    if(big.length==0){ // if number is null
        return big;
    }
    else if(big.length==1 && (big.L->data==0) ){  // if number is only zero
        return big;
    }
    else{
        int arrlen=big.length;
        int arr[arrlen];
        struct node *temP;
        int i;
        for(i=0;i<arrlen;i++){
            arr[i]= (big.L->data);
            big.L = (big.L->next);
        }
        // arr is array repersentation of L
        i=arrlen-1;
        while(i>=0){
            if(arr[i]==0){
                i--;
            }
            else{
                break;  // found last non zero element ka index
            }
        }
        int k;
        free(big.L);
        big.L=NULL;

        for(k=0;k<=i;k++){
            if(big.L==NULL){
                big.L=newnode(arr[k]);
                temP=big.L;
            }
            else
            {
                temP->next=newnode(arr[k]);
                temP=temP->next;
            }
        }
        big.length=k;
        if(big.length==0){  // if the result had become empty
            big.length=1;
            free(big.L);
            big.L=newnode(0);
        }
        free(arr);
        return big;
    }
}

int compareABSP(struct BigInteger a, struct BigInteger b){
    a=truncate(a);
    b=truncate(b);
    if( a.length > b.length ){
        return 1;
    }
    else if( a.length < b.length ){
        return -1;
    }
    else{   // here both are of same length
        int res=0;
        struct node *ptr1=a.L;
        struct node *ptr2=b.L;
        while(ptr1!=NULL){
            if( (ptr1->data) > (ptr2->data)){
                res=1;
            }
            if( (ptr1->data) < (ptr2->data) ){
                res=-1;
            }
            ptr1=ptr1->next;
            ptr2=ptr2->next;
        }
        return res;
    }
}

int compareABSN(struct BigInteger a, struct BigInteger b){
    a=truncate(a);
    b=truncate(b);
    if( a.length > b.length ){
        return -1;
    }
    else if( a.length < b.length ){
        return 1;
    }
    else{   // here both are of same length
        int res=0;
        struct node *ptr1=a.L;
        struct node *ptr2=b.L;
        while(ptr1!=NULL){
            if( (ptr1->data) < (ptr2->data)){
                res=1;
            }
            if( (ptr1->data) > (ptr2->data) ){
                res=-1;
            }
            ptr1=ptr1->next;
            ptr2=ptr2->next;
        }
        return res;
    }
}

int compare(struct BigInteger a,struct BigInteger b){
    int res=0;
    if(a.sign > b.sign){
        return 1;
    }
    else if(a.sign < b.sign){
        return -1;
    }
    else{ // both have same signs
        if(a.sign==-1){  // if signs are negative
            res=compareABSN(a,b);
        }
        else        // if signs are positive
            res=compareABSP(a,b);
    }
    return res;
}

struct BigInteger intitialize(char* s){
    struct BigInteger temp;;
    temp.L=NULL;
    temp.length=0;
    temp.sign=0;
    if(strcmp(s,"")==0){
        return temp;
    }
    struct node *ptr;

    if(s){ // if not empty string
    int i=strlen(s)-1;
    int ending=0;
        if(s[0]=='-'){
            temp.sign=-1;   // negative bigInteger
            ending++;
        }
        else{
            temp.sign=1;    // positive BigInteger
        }
        while(i>=ending){
            if(temp.L==NULL){
                temp.L=newnode(s[i]-48);
                ptr=temp.L;
            }
            else{
                ptr->next=newnode(s[i]-48);
                ptr=ptr->next;
            }
            temp.length++;
            i--;
        }
        if(temp.length==0){     // going in  here means only + pr - sign was entered
            temp.L=newnode(1);
            temp.length=1;
        }
    }
    else{
        printf("\n enter a string please and not a null \n");
    }
    return temp;
}

void display1(struct node* head){
    if(head){
        display1(head->next);
        printf("%d",(head->data));
    }
}
void display(struct BigInteger big){
    printf("\n ");
    if(big.length==0){
        printf(" Empty Big Integer ");
    }
    else{
        if(big.sign==-1){
            printf("-");
        }
        display1(big.L);
    }
    printf("\nsize of number = %d ",big.length);
    printf("\n");
}

struct BigInteger addABS(struct BigInteger a,struct BigInteger b){
    struct BigInteger big,small;
    if(compareABSP(a,b)==1){
        big=a;
        small=b;
    }
    else if(compareABSP(a,b)==-1){
        big=b;
        small=a;
    }
    else{
        big=a;
        small=b;
    }
    struct BigInteger res;
    res.L=NULL;
    res.length=0;
    struct node* resP;

    struct node *ptr1=big.L;
    struct node *ptr2=small.L;
    int sum=0,carry=0,ans;
    
    while(ptr1!=NULL || ptr2!=NULL){
        int d1= (ptr1!=NULL) ? (ptr1->data) : 0;
        int d2= (ptr2!=NULL) ? (ptr2->data) : 0;
        
        sum=d1+d2+carry;
        carry=sum/10;
        ans=sum%10;
        if(res.L==NULL){
            res.L=newnode(ans);
            resP=res.L;
        }
        else{
            (resP->next) = newnode(ans);
            resP = (resP->next);
        }
        res.length++;
        if(ptr1)    ptr1 = ptr1->next;
        if(ptr2)    ptr2 = ptr2->next;
    }
    if(carry!=0){
        resP->next=newnode(carry);
        res.length++;
    }
    res.sign=a.sign;

    return res;
}

struct BigInteger subABS(struct BigInteger a, struct BigInteger b){
    struct BigInteger big,small;
    if(compareABSP(a,b)==1){
        big=a;
        small=b;
    }
    else if(compareABSP(a,b)==-1){
        big=b;
        small=a;
    }
    else{
        big=a;
        small=b;
    }
    struct BigInteger res;
    res.L=NULL;
    res.length=0;
    struct node* resP;

    struct node *ptr1=big.L;
    struct node *ptr2=small.L;
    int diff=0,borrow=0,ans;
    
    while(ptr1!=NULL || ptr2!=NULL){
        int d1= (ptr1!=NULL) ? (ptr1->data) : 0;
        int d2= (ptr2!=NULL) ? (ptr2->data) : 0;
        
        diff=d1 - d2 -borrow;
        if(diff < 0){
            ans=diff+10;
            borrow=1;
        }
        else
        {
            ans=diff;
            borrow=0;
        }

        if(res.L==NULL){
            res.L=newnode(ans);
            resP=res.L;
        }
        else{
            (resP->next) = newnode(ans);
            resP = (resP->next);
        }
        res.length++;
        if(ptr1)    ptr1 = ptr1->next;
        if(ptr2)    ptr2 = ptr2->next;
    }
    res.sign=big.sign;
    res=truncate(res);
    return res;
}
struct BigInteger add(struct BigInteger a,struct BigInteger b){
    if( (a.length==0) && (b.length!=0) ){ // if b is empty
        return b;
    }
    else if( (b.length==0) && (a.length!=0) ){ // if a is empty
        return a;
    }
    else if( (a.length==0) && (b.length==0) ){
        return a;
    }
    // reaching here means both are not null
    struct BigInteger res;
    int k;
    if(compareABSP(a,b) == 1){
        k=a.sign;
    }
    else if(compareABSP(a,b) == -1){
        k=b.sign;
    }
    else{
        k=a.sign;
    }

    // we have sign of expression in k
    if(a.sign==b.sign){     // if signs are same we do addition
        res=addABS(a,b);
    }
    else{
        struct BigInteger b1=a , b2=b;  // if signs are different we do subtraction
        b1.sign=1;
        b2.sign=1;
        res=subABS(b1,b2);
    }    
    res.sign=k;
    return res;    
}

struct BigInteger sub(struct BigInteger a,struct BigInteger b){
    if( (a.length==0) && (b.length!=0) ){ // if b is empty
        return b;
    }
    else if( (b.length==0) && (a.length!=0) ){ // if a is empty
        return a;
    }
    else if( (a.length==0) && (b.length==0) ){
        return a;
    }
    // reaching here means both are not null
    struct BigInteger res;
    int k;
    if(compareABSP(a,b) == 1){
        k=a.sign;
    }
    else if(compareABSP(a,b) == -1){
        k=b.sign;
    }
    else{
        k=a.sign;
    }
    // we have sign of expression in k (jo number ka absolute bada uska sign)

    if(a.sign==b.sign){     // if signs are same we do subtraction
        res=subABS(a,b);
    }
    else{
        struct BigInteger b1=a , b2=b;  // if signs are different we do addition
        b1.sign=1;
        b2.sign=1;
        res=addABS(b1,b2);
    }    
    res.sign=k;
    return res;    
}
void freeBig(struct BigInteger *big){
    struct node *temp=(*big).L;
    free(temp);
    temp=NULL;
    (*big).length=0;
}

struct BigInteger mul(struct BigInteger a,struct BigInteger b){
    if(a.length==1 && a.L->data==0){  //a is zero
        return a;
    }
    else if(b.length==1 && b.L->data==0){ // b is zero
        return b;
    }
    if( (a.length==0) && (b.length!=0) ){ // if b is empty
        return b;
    }
    else if( (b.length==0) && (a.length!=0) ){ // if a is empty
        return a;
    }
    else if( (a.length==0) && (b.length==0) ){ // both are empty
        return a;
    }
    struct BigInteger res,big,small;
    int k;
    if(a.sign==b.sign){
        k=1;
    }
    else {
        k= ( (a.sign==-1) || (b.sign==-1) ) ? -1 : 1;
    }
    res.L=NULL;
    res.length=0;
    res.sign=1;

    big=a;
    small=b;
    big.sign=1;
    small.sign=1;
    struct node *resP;
    struct BigInteger dummy=intitialize("");
    dummy.length=0;
    int product,carry=0,ans;
    int i=0;
    while(small.L!=NULL){

        for(int k=0;k<i;k++){ // skipper
            if(res.L==NULL){
                res.L=newnode(0);
                resP=res.L;
            }
            else{
                resP->next=newnode(0);
                resP=resP->next;
            }
            res.length++;
        }

        while(big.L!=NULL){
            int d1=big.L->data;
            int d2=small.L->data;

            product=d1 * d2 + carry;
            carry=product/10;
            ans=product%10;

            if(res.L==NULL){
                res.L=newnode(ans);
                resP=res.L;
            }
            else{
                resP->next=newnode(ans);
                resP=resP->next;
            }
            res.length++;
            big.L=big.L->next;
        }
        if(carry!=0){
            resP->next=newnode(carry);
            res.length++;
        }
        big.L=a.L;

        dummy=addABS(dummy,res);

        freeBig(&res);
        res.L=NULL;

        small.L=small.L->next;
        i++;
    }
    dummy.sign=k;
    return dummy;
}
int giveCount(int n){       // gives number of digits
    int count=0;
    for(int i=n;i!=0;i=i/10){
        count++;
    }
    return count;
}
char* numberToString(int num,int digits) {
   static char str[9999];  // Assuming a 32-bit integer, so 11 digits plus null-terminator

    // Use sprintf to format the number as a string
    sprintf(str, "%d", num);

    return str;
}
struct BigInteger div1(struct BigInteger a,struct BigInteger b){
    struct BigInteger num1=a,num2=b;
    struct BigInteger res=intitialize("");
    res.L=NULL;


    if(num1.length==0)  return res; // first is null
    if(num2.length==0 || ( (num2.length==1) && (num2.L->data==0) ) )  return res; //second is null or 0

    if(num1.length==1 && num1.L->data==0){ // first is 0
        res=intitialize("0");
        return res;
    }
    // handled cases where data is either null or 0

    int k= (a.sign==b.sign) ? 1 : -1 ;  // same sign become + and different become -
    
    if(b.length==1 && (b.L->data==1)){ // if divide by 1 we get same number
        res=a;
        res.sign=k;
        return res;
    }
    struct BigInteger big=a,small=b;
    big.sign=1;
    small.sign=1;
    if(compareABSP(big,small)==0){ // both are equal
        res=intitialize("1");
        res.sign=k;
        return res;
    }
    // handeled all cases where denominator or numerator is 0 or 1 or both are equal
    
    big=a;
    small=b;
    big.sign=1;
    small.sign=1;


    int i;
    struct BigInteger dig;
    struct BigInteger prod;
    for(i=1;;i++){

        int c=giveCount(i);
        char* temp=numberToString(i,c);
        dig=intitialize(temp);
        prod=mul(small,dig);
        if(compare(prod,big)!=1){
        }
        else{
            break;
        }
    }
    int c=giveCount(i);
    char* temp2=numberToString(i,c);
    struct BigInteger ans=intitialize(temp2);
    struct BigInteger tempMini=intitialize("1");
    prod=mul(ans,small);
    if(compare(prod,big)==1){
        ans=sub(ans,tempMini);
    }
    
    ans.sign=k;
    return ans;    
}
struct BigInteger mod(struct BigInteger a,struct BigInteger b){
    struct BigInteger res=intitialize("");
    res.L=NULL;
    if(a.length==0 || b.length==0){
        printf("\n please enter both values");
        return res;
    }
    if(b.length==1 && b.L->data==0){ // if b is zero
        printf("\n mod by 0 not possible \n");
        return res;
    }
    int k=1;  // mod is never negative
    if(compare(a,b) == 0 || ((b.length==1)&&(b.L->data==1)) || (compare(a,b)==-1) || (a.length==1 && (a.L->data)==0)){
        res=intitialize("0");
        return res;
    } //both are same or mod is 1 or b is bigger than a or a is zero
    
    // reaching here means a>b and b!=0 and a!=0
    struct BigInteger big=a, small=b;
    struct BigInteger subtractant=div1(big,small);
    struct BigInteger mulethi=mul(subtractant,small);
    struct BigInteger adrak=sub(big,mulethi);
    adrak.sign=k;
    return adrak;
}