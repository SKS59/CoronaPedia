#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<iomanip>
#define max 26
using namespace std;

class node
{
    public:
    string nameOfState,confirmedCases,recoveredCases,deathsState,activeState;
    node *next;
    node()
    {
        next=NULL;
    }
};
class hashTable
{
    public:
    node *arrayOfStates[max];
    hashTable()
    {
        for(int i=0;i<max;i++)
            arrayOfStates[i]=NULL;
    }
   /* void clearAll()
    {
        for(int i=0;i<max;i++)
        {
            arrayOfStates[i].nameOfState="-";
            arrayOfStates[i].confirmedCases="-";
            arrayOfStates[i].recoveredCases="-";
            arrayOfStates[i].deathsState="-";
            arrayOfStates[i].activeState="-";
        }
    } */
    void construct()
    {
        node *temp;
        temp=new node;
        ifstream infile;
        infile.open("Sample.csv");
        infile.seekg(0);
        while(infile.good())
        {
            getline(infile,temp->nameOfState,',');
            getline(infile,temp->confirmedCases,',');
            getline(infile,temp->recoveredCases,',');
            getline(infile,temp->deathsState,',');
            getline(infile,temp->activeState,'\n');
            temp->next=NULL;
            cout<<"\ntemp node\n";
            cout<<temp->nameOfState<<"\t"<<temp->confirmedCases<<"\t"<<temp->recoveredCases<<"\t"<<temp->deathsState<<"\t"<<temp->activeState<<endl;
            insertNode(temp);
        }

    }
    void insertNode(node *temp)
    {
        int position=hashFn(temp->nameOfState);
        if(arrayOfStates[position]==NULL)
        {
            cout<<"\nit was null so inserted at position ";
            arrayOfStates[position]=temp;
        }
        else
        {
            cout<<"\nit wasnt at null at position";
            temp->next=arrayOfStates[position]->next;
            arrayOfStates[position]->next=temp;
        }
        cout<<"\n"<<temp->nameOfState<<" Inserted at position "<<position<<"\n";
    }
    int hashFn(string tempstring)
    {
        return(tempstring[0]-65);
    }
    int displayAll()
    {
        node *current;
        for(int i=0;i<max;i++)
        {
            current=arrayOfStates[i];
            cout<<"\n"<<i<<" : ";
            while(current!=NULL)
            {
                cout<<current->nameOfState<<"\t"<<current->confirmedCases<<"\t"<<current->recoveredCases<<"\t"<<current->deathsState<<"\t"<<current->deathsState<<endl;
                current=current->next;
            }
        }
    }
};
int main()
{
   /* int choice;
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
    }while(yn=='y'||yn!='Y'); */
    hashTable h;
    h.construct();
    h.displayAll();
    return 0;
}

