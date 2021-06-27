#include<iostream>
#include<string.h>
#include<iomanip>
#include<graphics.h>
#include<string>
using namespace std;

void check()
{
    string name,gen,age;
    char yn[5];
    bool temp[7]={false,false,false,false,false,false,false};
    system("color 0D");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n"<<setw(110)<<setfill(' ');
    cout<<"Enter your name : ";
    cin>>name;
    cout<<"\n\n\n\n"<<setw(80)<<setfill(' ')
        <<"\t\t\t\tHello "<<name<<" ...!!!\n";
    delay(2000);
    cout<<"\n\n\n\n\n\n"<<setw(115)<<setfill(' ')
        <<"Enter your gender (M/F) : ";
    cin>>gen;
    cout<<"\n\n\n\n\n\n"<<setw(110)<<setfill(' ')
        <<"Enter your age : ";
    cin>>age;
    cout<<"\n\n\n\n\n\n"<<setw(140)<<setfill(' ')
        <<"For checking symptoms you will have to answer some questions............";
    delay(2000);
    system("cls");
    cout<<"\n\n\n\n\n"<<setw(80)<<setfill(' ')
        <<"1.Do you have any health conditions like asthma,cancer,diabetes ? (Y/N) : ";
    cin>>yn[0];
    cout<<"\n\n\n\n\n"<<setw(80)<<setfill(' ')
        <<"     2.Have you or someone in your family staying with you came in contact with a laboratory confirmed COVID-19 patient in last 14 days ? ";
    cin>>yn[1];
    cout<<"\n\n\n\n\n"<<setw(80)<<setfill(' ')
        <<"     3.Have you oe someone in your family staying with you attended a large gathering / in a migration centre in last 14 days ? ";
    cin>>yn[2];
    cout<<"\n\n\n\n\n"<<setw(80)<<setfill(' ')
        <<"     4.Are you currently working for essential services in public exposed places (such as hospitals,retail outlets) ? ";
    cin>>yn[3];
    cout<<"\n\n\n\n\n"<<setw(80)<<setfill(' ')
        <<"     5.Is someone from your family currently working for essential services in public exposed places (such as hospitals,retail outlets) ? ";
    cin>>yn[4];
    cout<<"\n\n\n\n\n"<<setw(80)<<setfill(' ')
        <<"     6.Are you having one or more of following symptoms ? \n\t1.Fever\n\t2.Dry cough\n\t3.Feeling shortness of breadth\n\t4.Sore throat\n\t5.Hoarseness in voice\n\t6.Headache\n\t7.Running nose\n";
    cout<<"\n\t\t\t\t\tAny of above ? ";
    cin>>yn[5];
    int count1=0,pos;
    string no;
    char srno[7];
    if(yn[5]=='y')
    {
        cout<<"\n\n\n\t\t\t\t\t\t\t\tEnter the serial numbers of symptoms which you are having (Press double enter when finished ): ";
        cin>>srno;
        for(int i=0;srno[i];i++)
        {
            no=srno[i];
            pos=stoi(no);
            temp[pos]=true;
            count1++;
        }
    }
    int cnt=0;
    for(int i=0;yn[i];i++)
    {
        if(yn[i]=='y')
            cnt++;
    }
    system("cls");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n"<<setw(90)<<setfill(' ')
        <<name<<", you are in ";
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
    delay(1500);
    return;
}

int main()
{
    check();
    return 0;
}
