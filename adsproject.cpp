#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<iomanip>
using namespace std;
int main()
{
    int choice;
    string stateName,confirmed,recovered,deaths,active,temp;
    bool flag;
    char yn;
    ifstream infile;

    do
    {
        cout<<"\n1.Display all records\n2.Search record for State / Union territory\nEnter choice : ";
        cin>>choice;
        cout<<"\n\n\n";
        switch(choice)
        {
            case 1:
            infile.open("Sample.csv");
            cout<<"\n-----------------------------------------------------------------------------------------------------------\n";
            cout<<"            STATE                        Confirmed          RECOVERED          DEATHS          ACTIVE                       ";
            cout<<"\n-----------------------------------------------------------------------------------------------------------\n";
            infile.seekg(0);
            while(infile.good())
            {
                getline(infile,stateName,',');
                if(stateName=="state")
                {
                    getline(infile,confirmed,',');
                    getline(infile,recovered,',');
                    getline(infile,deaths,',');
                    getline(infile,active,'\n');
                    continue;
                }
                getline(infile,confirmed,',');
                getline(infile,recovered,',');
                getline(infile,deaths,',');
                getline(infile,active,'\n');
                cout<<left<<setw(25)<<stateName<<"\t\t"<<setw(8)<<confirmed<<setw(8)<<"\t"<<recovered<<"\t\t"<<setw(8)<<deaths<<"\t"<<setw(8)<<active<<endl;
            }
            infile.close();
            break;
            case 2:
            cout<<"\nEnter the State : ";
            cin.ignore();
            getline(cin,temp);
            infile.open("Sample.csv");
            infile.seekg(0);
            flag=false;
            while(getline(infile,stateName,',') && !flag)
            {
                if(stateName=="state")
                {
                    getline(infile,confirmed,',');
                    getline(infile,recovered,',');
                    getline(infile,deaths,',');
                    getline(infile,active,'\n');
                    continue;
                }
                getline(infile,confirmed,',');
                getline(infile,recovered,',');
                getline(infile,deaths,',');
                getline(infile,active,'\n');
                cout<<stateName;
                if(temp==stateName)
                {
                    cout<<"\nSTATE : "<<stateName<<"\nCONFIRMED : "<<confirmed<<"\nRECOVERED : "<<recovered<<"\nDEATHS : "<<deaths<<"\nACTIVE : "<<active<<endl;
                    flag=true;
                }
            }
            infile.close();
            break;
        }
        cout<<"\nDo you want to continue ? ";
        cin>>yn;
    }while(yn=='y'||yn!='Y');
}
