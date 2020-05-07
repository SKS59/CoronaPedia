#include<iostream>
#include<conio.h>
using namespace std;

void check()
{
    string name,gen,age;
    char yn[5];
    bool temp[7]={false,false,false,false,false,false,false};
    cout<<"\nEnter your name : ";
    cin>>name;
    cout<<"\nHello "<<name<<" ...!!!\n";
    cout<<"\nEnter your gender : ";
    cin>>gen;
    cout<<"\nEnter your age : ";
    cin>>age;
    cout<<"\nDo you have any health conditions like asthma,cancer,diabetes ? (Y/N) : ";
    cin>>yn[0];
    cout<<"\nHave you or someone in your family staying with you came in contact with a laboratory confirmed COVID-19 patient in last 14 days ? ";
    cin>>yn[1];
    cout<<"\nHave you oe someone in your family staying with you attended a large gathering / in a migration centre in last 14 days ? ";
    cin>>yn[2];
    cout<<"\nAre you currently working for essential services in public exposed places (such as hospitals,retail outlets) ? ";
    cin>>yn[3];
    cout<<"\nIs someone from your family currently working for essential services in public exposed places (such as hospitals,retail outlets) ? ";
    cin>>yn[4];
    cout<<"\nAre you having one or more of following symptoms ? \n1.Fever\n2.Dry cough\n3.Feeling shortness of breadth\n4.Sore throat\n5.Hoarseness in voice\n6.Headache\n7.Running nose\n";
    cout<<"\n\t\t\t\t\tAny of above ? ";
    cin>>yn[5];
    int count1=0;
    char ch,srno;
    if(ch=='y')
    {
        cout<<"\nEnter the serial numbers of symptoms which you are having (Press k when finished ): ";
        while(srno!='k')
        {
            srno=getch();
            if(srno=='k')
                break;
            temp[srno-48]=true;
            count1++;
        }
    }
    int cnt=0;
    for(int i=0;yn[i];i++)
    {
        if(yn[i]=='y')
            cnt++;
    }
    cout<<"\ncnt = "<<cnt;
    cout<<"\nCount = "<<count1;
    cout<<"\n"<<name<<", you are in ";
    if(cnt<=2 && count1 <=2)
    {
       // cout<<"1";
        cout<<"LOW RISK......  :)\n";
    }
    else if(cnt<=2 && count1>3)
    {
        //cout<<"2";
        cout<<"MODERATE RISK.....  :(\n";
    }
    else if(cnt>2 && cnt<=4 && count1 <5)
    {
        //cout<<"3";
        cout<<"MODERATE RISK.....  :(\n";
    }
    else if(cnt>4 && cnt <=6 && count1 <7)
    {
       // cout<<"4";
        cout<<"HIGH RISK...!!!! :'\((\n";
    }
    else if(cnt>2 && cnt <=4 && count1 >5)
    {
       // cout<<"5";
        cout<<"HIGH RISK...!!!! :'(\n";
    }
    else if(cnt>4 && cnt <=6 && count1 <4)
    {
       // cout<<"6";
        cout<<"MODERATE RISK.....  :(\n";
    }
    else if(cnt<=2 && count1<=4)
    {
        //cout<<"7";
        cout<<"LOW RISK......  :)\n";
    }
}

int main()
{
    check();
    return 0;
}
