#include<stdio.h>
#include<cs50.h>

int main(void)
{
    string name = get_string("what's your name?\n"); //ask a question to answer
    printf("hello, %s\n", name);//print "hello, my name"
}