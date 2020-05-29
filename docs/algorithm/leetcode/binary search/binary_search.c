#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main()
{
    int a[10]={1,2,3,4,6,7,8,9,10,11};
    //         0 1 2 3 4 5 6 7  8  9
    int left=0,right=10;
    int target=1;
    bool find=false;
    
    /******************写法一*******************************/
    while(left<right)
    {   
        int mid = (left+right)/2;
        printf("left %d mid %d right %d\n",left,mid,right);
        if(a[mid]==target)
        {
            printf("find at %d\n",mid);
            find = true;
            break;
        }
        if(a[mid]>target)
            right=mid;
        else
            left=mid+1;
    }
    if(!find)
        printf("not find\n");
    printf("method1 done\n");
/******************写法二***********/
    left=0,right=9;
    find=false;
    while(left<=right)
    {       
        int mid = (left+right)/2;
        printf("left %d mid %d right %d\n",left,mid,right);
        if(a[mid]==target)
        {
            printf("find at %d\n",mid);
            find=true;
            break;
        }
        if(a[mid]>target)
            right=mid-1;
        else
            left=mid+1;
    }
    if(!find)
        printf("not find\n");
    printf("method2 done\n");

    left=1,right=9;
    //寻找第一个1出现的位置
    int b[10]={0,0,1,1,1,1,1,1,1,1};
    while(left<right)
    {      
        int mid = (left+right)/2;
        mid = left + (right - left) / 2; //防止溢出
        printf("enter left %d mid %d right %d\n",left,mid,right);
        if(b[mid]==target)
        {
            printf("find at %d\n",mid);
            right=mid;
        }
        else
        {
            left=mid+1;
        }
        printf("left left %d mid %d right %d\n\n",left,mid,right);
        if (left==right)
        {
            printf("left %d \n",left);
        }
    }
}