#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <stdarg.h>
#include <stdio.h>


struct node{
    int data;
    struct node *next;
};
struct BigInteger{
    struct node *L;
    int length;
    int sign;
};
struct node* newnode(int x);
struct BigInteger truncate(struct BigInteger big);
int compareABSP(struct BigInteger a, struct BigInteger b);
int compareABSN(struct BigInteger a, struct BigInteger b);
int compare(struct BigInteger a,struct BigInteger b);
struct BigInteger intitialize(char* s);
void display1(struct node* head);
void display(struct BigInteger big);
struct BigInteger addABS(struct BigInteger a,struct BigInteger b);
struct BigInteger subABS(struct BigInteger a, struct BigInteger b);
struct BigInteger add(struct BigInteger a,struct BigInteger b);
struct BigInteger sub(struct BigInteger a,struct BigInteger b);
void freeBig(struct BigInteger *big);
struct BigInteger mul(struct BigInteger a,struct BigInteger b);
int giveCount(int n);
char* numberToString(int num,int digits);
struct BigInteger div1(struct BigInteger a,struct BigInteger b);
struct BigInteger mod(struct BigInteger a,struct BigInteger b);
#endif //BIG_INTEGER_H