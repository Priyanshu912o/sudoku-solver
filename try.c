#include <stdio.h>
void func();
int main()
{
    int array[10][9][9]={0};
    func(array);
    printf("%d",array[0][9][9]); 
}
void func(int array[10][9][9])
{
    *(*(*array+9)+9)=5;
}