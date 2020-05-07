#include<iostream>
#include<graphics.h>
#include<fstream>
using namespace std;

int main()
{
    int gd=DETECT,gm;
    char str[40];
    cout<<"\nEnter the text : ";
    cin.getline(str,40);
    char* ch=str;
    initwindow(600,600,"Testing window");
    readimagefile("a.jpg",0,0,500,500);
    delay(5000);
    closegraph();

}
