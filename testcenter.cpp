#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<iomanip>
using namespace std;
string statename,noOfCentres,test[15];
void searchall()
{
    int no;
    ifstream infile;
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<setw(110)<<setfill(' ')
    <<"Enter the name of state : ";
    string name,name1;
        //cin.ignore();
    fflush(NULL);
    getline(cin,name);
    name1=name;
        for(int i=0;name[i]!='\0';i++)
            name[i]=toupper(name[i]);
        int flag=1;
        infile.open("test_centres.txt");
        while(infile.good())
        {
            getline(infile,statename,',');
            for(int i=0;statename[i]!='\0';i++)
                statename[i]=toupper(statename[i]);
            getline(infile,noOfCentres,'\n');
            no=stoi(noOfCentres);
            for(int i=0;i<no;i++)
            {
                getline(infile,test[i],'\n');
            }
            if(name==statename)
            {;
                flag=0;
                break;
            }
        }
        if(!flag)
        {
            cout<<"\n\n\n\n\n\n\t\tTest centres  for "<<name1<<" :- \n\n";
            for(int i=0;i<no;i++)
            {
                cout<<"\t"<<test[i]<<endl<<endl;
            }
        }
        else
            cout<<"\n\n\n\n\n\n\t\tNot found for "<<name1<<endl;
        infile.close();
    }
int displayAllTest()
{
    int no;
    ifstream infile;
    infile.open("test_centres.txt");
    while(infile.good())
    {
        getline(infile,statename,',');
        getline(infile,noOfCentres,'\n');
        cout<<"\n\n-----------------------------------------\n\n";
        cout<<"\nTest centres in "<<statename<<" :- ";
        cout<<"\n\n-----------------------------------------\n\n";
        no=stoi(noOfCentres);
        for(int i=0;i<no;i++)
        {
            getline(infile,test[i],'\n');
            cout<<test[i]<<endl;
        }
    }
    infile.close();
    return 0;
}

