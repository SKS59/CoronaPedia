#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<iomanip>
#include<graphics.h>
#include<windows.h>
#include<conio.h>
#include<dos.h>
#include<limits>
#include<vector>
#include<algorithm>
#include"sym_check.h"
#include"testcenter.cpp"
#define max1 26
using namespace std;
int globalFlag=1;

class countryNode
{
public:
    string nameOfCountry,confirmedCountry,recoveredCountry,deathsCountry,activeCountry;
    countryNode *left;
    countryNode *right;
    int height;
    double ActiveRate;
    double RecoverRate;

    countryNode()
    {
        ActiveRate=RecoverRate=0;
        height=1;
        left=right=NULL;

    }
};

class stateNode
{
    public:
    string nameOfState,confirmedState,recoveredState,deathsState,activeState;
    double ActiveRate;
    double RecoverRate;
    stateNode *next;
    stateNode*left,*right;
    int height;
    stateNode()
    {
        height=1;
        left=right=NULL;
        ActiveRate=RecoverRate=0;
    }
};
class hashTable
{
    public:
    stateNode *arrayOfStates[max1];
    countryNode *arrayOfCountries[max1];
    int ind;
     vector <stateNode*> Statearr;
     vector<countryNode*>Countryarr;
//  vector<stateNode*> States;
   // vector <CountryNode*> Countries;
    hashTable()
    {
        for(int i=0;i<max1;i++)
        {
            arrayOfStates[i]=NULL;
            arrayOfCountries[i]=NULL;
        }
    }

    void constructState()
    {
        stateNode *temp;

        ifstream infile;
        infile.open("Sample.csv");
        infile.seekg(0);
        while(infile.good())
        {
            if(infile.tellg()==ios::beg)
            {
                infile.ignore(numeric_limits<streamsize>::max(),'\n');
            }
            temp=new stateNode;
            getline(infile,temp->nameOfState,',');
            getline(infile,temp->confirmedState,',');
            getline(infile,temp->recoveredState,',');
            getline(infile,temp->deathsState,',');
            getline(infile,temp->activeState,'\n');
            //temp->next=NULL;
            for(int i=0;temp->nameOfState[i];i++)
                temp->nameOfState[i]=toupper(temp->nameOfState[i]);

            if(!infile.eof())
                {insertNodeState(temp);
                Statearr.push_back(temp);
                }
        }
        infile.close();

        Statearr.pop_back();
         for(int i=0;i<Statearr.size();i++)
          {
                         stateNode*p=Statearr[i];

            if(stoi(Statearr[i]->confirmedState)!=0)
                Statearr[i]->ActiveRate= ((double)stoi(Statearr[i]->activeState)/(double)stoi(Statearr[i]->confirmedState))*100;
          }

          for(int i=0;i<Statearr.size();i++)
          {
            stateNode*p=Statearr[i];
            if(stoi(Statearr[i]->confirmedState)!=0)
                Statearr[i]->RecoverRate= ((double)stoi(Statearr[i]->recoveredState)/(double)stoi(Statearr[i]->confirmedState))*100;
          }

    }
    static bool ComparatorA(stateNode* a,stateNode* b)
    {
        return(stoi(a->activeState)>stoi(b->activeState));
    }
    static bool ComparatorR(stateNode* a,stateNode* b)
    {
        return(stoi(a->recoveredState)>stoi(b->recoveredState));

    }
    static bool ComparatorAR(stateNode* a,stateNode* b)
    {

        if((a->ActiveRate>b->ActiveRate))
            {if(stoi(a->activeState)>stoi(b->activeState))
                return true;
            else if(stoi(a->deathsState)>stoi(b->deathsState))
                return true;
            }
        else if(stoi(a->confirmedState)>stoi(b->confirmedState))
                return true;
        else
            return false;


    }




   static bool ComparatorRR(stateNode* a,stateNode* b)
    {

        if(a->RecoverRate>b->RecoverRate)
           {if(stoi(a->recoveredState)>stoi(b->recoveredState))
                return true;

           }
        else if(stoi(a->confirmedState)>stoi(b->confirmedState))
        {
            if(stoi(a->activeState)<stoi(b->activeState))
                return true;
        }
          //  return true;
        else if (stoi(a->confirmedState)>stoi(b->confirmedState))
        {
                           return true;
        }

        else
            return false;
    }
     void ActiveCasesSort()
    {
          sort(Statearr.begin(),Statearr.end(),ComparatorA);
        cout<<"#-------------------------------MAXIMUM ACTIVE CASES STATE------------------------------------------#"<<endl;

        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<left<<setw(40)<<"   STATE                                                       ACTIVE CASES            "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
         for(int i=0;i<Statearr.size();i++)
          {
            stateNode*p=Statearr[i];
            cout<<left<<setw(40)<<Statearr[i]->nameOfState<<setw(15)<<"\t\t"<<Statearr[i]->activeState<<endl;
          }
    }
    void RecoveryCaseSort()
    {

          sort(Statearr.begin(),Statearr.end(),ComparatorR);
        cout<<"#-------------------------------MAXIMUM RECOVERY CASES STATE------------------------------------------#"<<endl;

        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<left<<setw(40)<<"   STATE                                                       RECOVERED CASES         "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
         for(int i=0;i<Statearr.size();i++)
          {
            stateNode*p=Statearr[i];
            cout<<left<<setw(40)<<Statearr[i]->nameOfState<<setw(15)<<"\t\t"<<Statearr[i]->recoveredState<<endl;
          }
    }
    void MaxActiveRateSort()
    {
          sort(Statearr.begin(),Statearr.end(),ComparatorAR);
        cout<<"#-------------------------------SEVERITY OF STATES IN DECREASING ORDER------------------------------------------#"<<endl;

        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<left<<setw(40)<<"   STATE                                                       ACTIVE CASE RATE        "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
         for(int i=0;i<Statearr.size();i++)
          {
            stateNode*p=Statearr[i];
            cout<<left<<setw(40)<<Statearr[i]->nameOfState<<setw(15)<<"\t\t"<<Statearr[i]->ActiveRate<<endl;
          }
    }
    void MaxRecoveryRateSort()
    {

          sort(Statearr.begin(),Statearr.end(),ComparatorRR);
        cout<<"#-------------------------------RECOVERY RATE OF STATES IN DECREASING ORDER------------------------------------------#"<<endl;

        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<left<<setw(40)<<"   STATE                                                       RECOVERY RATE        "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
         for(int i=0;i<Statearr.size();i++)
          {
            stateNode*p=Statearr[i];
            cout<<left<<setw(40)<<Statearr[i]->nameOfState<<setw(15)<<"\t\t"<<Statearr[i]->RecoverRate<<endl;
          }
    }




    //NEW ADDED FROM AVL HASHING
    int getMax(int a,int b)
    {
        return (a>b)?a:b;
    }
    int height(stateNode *N)
    {
    if (N == NULL)
        return 0;
    return N->height;
    }
    int getBalance(stateNode *N)
    {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
    }
    stateNode* rightRotate(stateNode* oldR)
    {
        stateNode* newR=oldR->left;
        stateNode* temp=newR->right;
        newR->right=oldR;
        oldR->left=temp;
        oldR->height=(getMax(height(oldR->left),height(oldR->right))+1);
        newR->height=(getMax(height(newR->left),height(newR->right))+1);
        return newR;

    }
    stateNode* leftRotate(stateNode* oldR)
    {
        stateNode* newR=oldR->right;
        stateNode* temp=newR->left;
        newR->left=oldR;
        oldR->right=temp;
        oldR->height=(getMax(height(oldR->left),height(oldR->right))+1);
        newR->height=(getMax(height(newR->left),height(newR->right))+1);
        return newR;
    }


    stateNode* insertstateNode(stateNode* root,stateNode *temp)
    {

    if (root == NULL)
        return(temp);

    if (temp->nameOfState < root->nameOfState)
        root->left =insertstateNode(root->left, temp);
    else if (temp->nameOfState > root->nameOfState)
        root->right = insertstateNode(root->right, temp);
    else // Equal keys are not allowed in BST
        return root;


    root->height = 1 + getMax(height(root->left),
                        height(root->right));

    int balance = getBalance(root);


    if (balance > 1 && temp->nameOfState < root->left->nameOfState)
        return rightRotate(root);

    if (balance < -1 && temp->nameOfState > root->right->nameOfState)
        return leftRotate(root);

    if (balance > 1 && temp->nameOfState > root->left->nameOfState)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }


    if (balance < -1 && temp->nameOfState < root->right->nameOfState)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

    void insertNodeState(stateNode *temp)
    {
        stateNode *temp1;
        int position=hashFn(temp->nameOfState);
        if(arrayOfStates[position]==NULL)
        {

            arrayOfStates[position]=temp;
        }
        else
        {
           arrayOfStates[position]= insertstateNode(arrayOfStates[position],temp);

           /* temp1=arrayOfStates[position];
            while(temp1->next!=NULL)
            {
                temp1=temp1->next;
            }
            temp1->next=temp;*/

        }
    }
    int hashFn(string tempstring)
    {
        if(tempstring[0]=='"')
            return(toupper(tempstring[1])-65);
        return(toupper(tempstring[0])-65);
    }
    void searchState()
    {
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<setw(110)<<setfill(' ')
        <<"Enter the name of state : ";
        string name,name1;
        //cin.ignore();
        fflush(NULL);
        getline(cin,name);
        name1=name;
        int pos=hashFn(name);
        stateNode *temp;
        for(int i=0;name[i]!='\0';i++)
            name[i]=toupper(name[i]);
        stateNode *current;
        int flag=1;
        /*for(int i=0;i<max1;i++)
        {
            current=arrayOfStates[i];
            while(current!=NULL)
            {
                if(name==current->nameOfState)
                {
                    cout<<"\n\t\tRECORD FOUND.........!!!!!\n\n";
                    cout<<"\t\tSTATE\t\t\t\tCONFIRMED\t\tRECOVERED\t\tDEATHS\t\tACTIVE\n";

                   cout<<left<<setw(40)<<current->nameOfState<<"\t\t"<<setw(15)<<current->confirmedState<<setw(8)<<"\t"<<current->recoveredState<<"\t\t"<<setw(8)<<current->deathsState<<"\t"<<setw(8)<<current->activeState<<endl;
                    break;
                }
                else
                    current=current->next;
            }
        }*/
        current=arrayOfStates[pos];
        while(current)
        {
            if(name==current->nameOfState)
            {
                cout<<"\n\n\n\n\t\t\t\t\t\tRecord Found .....  :)  !!!! \n";
                cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
                cout<<"             STATE                                    Confirmed          RECOVERED          DEATHS          ACTIVE                       ";
                cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
                cout<<setw(40)<<left<<current->nameOfState<<"\t\t"<<left<<setw(7)<<current->confirmedState<<"\t\t"<<left<<current->recoveredState<<"\t\t  "<<left<<current->deathsState<<"\t\t  "<<left<<current->deathsState<<endl;

                flag=0;
                break;
            }
            //else
            //{
                    else if(name<current->nameOfState)
                                current=current->left;
                    else if(name>current->nameOfState)
                                current=current->right;
               /* current=current->next;
                if(current==NULL)
                {
                    flag=1;
                    break;
                }*/
            //}
        }
        if(flag)
            cout<<"NO record found for "<<name1<<" :( "<<endl;
    }
    int displayAll()
    {
        stateNode *current;
        stateNode *total;
        this->ind=1;
        cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
            cout<<"             STATE                                    Confirmed          RECOVERED          DEATHS          ACTIVE                       ";
            cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
        for(int i=0;i<max1;i++)
        {
            current=arrayOfStates[i];
           // cout<<"\n"<<i<<" : ";
                    INorder(arrayOfStates[i]);
           /* while(current!=NULL)
            {
                cout<<current->nameOfState<<"\t"<<current->confirmedCases<<"\t"<<current->recoveredCases<<"\t"<<current->deathsState<<"\t"<<current->deathsState<<endl;
               // current=current->next;
            }*/
        }
        DisplayTotalS();
       // cout<<ind<<":"<<setw(40)<<left<<total->nameOfState<<"\t\t"<<total->confirmedState<<"\t\t"<<total->recoveredState<<"\t\t"<<total->deathsState<<"\t\t"<<total->deathsState<<endl;

    }
     void DisplayTotalS()
    {
        string total="TOTAL";
        int pos =hashFn(total);

        stateNode* current=arrayOfStates[pos];
        while(current)
        {
            if(total==current->nameOfState)
            {
                cout<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                cout<<"--:"<<setw(40)<<left<<current->nameOfState<<"\t\t"<<current->confirmedState<<"\t\t"<<current->recoveredState<<"\t\t"<<current->deathsState<<"\t\t"<<current->activeState<<endl;
                break;
            }
            else if(total>current->nameOfState)
                current=current->right;
            else if(total<current->nameOfState)
                current=current->left;
        }
    }

    stateNode* INorder(stateNode* current)
    {
        stateNode* tot=NULL;
    if(current)
    {
        INorder(current->left);
        if(current->nameOfState=="TOTAL")
            tot=current;
        if(current->nameOfState!="TOTAL" )
        {


            cout<<ind<<":"<<setw(40)<<left<<current->nameOfState<<"\t\t"<<current->confirmedState<<"\t\t"<<current->recoveredState<<"\t\t"<<current->deathsState<<"\t\t"<<current->activeState<<endl;
            this->ind ++;
        }
        INorder(current->right);
        if(tot)
            return tot;

    }

    }


    /*int displayAllState()
    {
        stateNode *current;
        for(int i=0;i<max1;i++)
        {
            current=arrayOfStates[i];
            cout<<"\n"<<i<<" : ";
            while(current!=NULL)
            {
                cout<<current->nameOfState<<"\t"<<current->confirmedState<<"\t"<<current->recoveredState<<"\t"<<current->deathsState<<"\t"<<current->deathsState<<endl;
                current=current->next;
            }
        }
    }*/
    void constructCountry()
    {
        countryNode *temp;
        string stringforbreak,t; char string1[100];
        int i;
        ifstream infile;

        infile.open("Countries.csv");
        infile.seekg(0);

        getline(infile,t,'\n');
        while(infile.good())
        {
             if(infile.tellg()==ios::beg)
            {
                infile.ignore(numeric_limits<streamsize>::max(),'\n');
            }
            temp=new countryNode;
            getline(infile,temp->nameOfCountry,',');
            if(temp->nameOfCountry[0]=='"')
            {
                i=0;
                getline(infile,stringforbreak,',');
                for(int j=1;temp->nameOfCountry[j];j++)
                {
                    string1[i++]=temp->nameOfCountry[j];
                }
                for(int j=0;stringforbreak[j]!='"';j++)
                {
                    string1[i++]=stringforbreak[j];
                }
                string1[i]='\0';
                temp->nameOfCountry=string1;
            }
            getline(infile,temp->confirmedCountry,',');
            getline(infile,temp->recoveredCountry,',');
            getline(infile,temp->deathsCountry,',');
            getline(infile,temp->activeCountry,'\n');
            //temp->next=NULL;
            for(int i=0;temp->nameOfCountry[i];i++)
                temp->nameOfCountry[i]=toupper(temp->nameOfCountry[i]);
            if(!infile.eof())
             {
                insertNodeCountry(temp);
                Countryarr.push_back(temp);
             }
        }
        infile.close();

     Countryarr.pop_back();
         for(int i=0;i<Countryarr.size();i++)
          {
                         countryNode*p=Countryarr[i];

            if(stol(Countryarr[i]->confirmedCountry)!=0)
                Countryarr[i]->ActiveRate= ((double)stol(Countryarr[i]->activeCountry)/(double)stol(Countryarr[i]->confirmedCountry))*100;
          }

          for(int i=0;i<Countryarr.size();i++)
          {
            countryNode*p=Countryarr[i];
            if(stol(Countryarr[i]->confirmedCountry)!=0)
                Countryarr[i]->RecoverRate= ((double)stol(Countryarr[i]->recoveredCountry)/(double)stol(Countryarr[i]->confirmedCountry))*100;
          }

    }
    static bool ComparatorAC(countryNode* a,countryNode* b)
    {
        return(stol(a->activeCountry)>stol(b->activeCountry));
    }
    static bool ComparatorRC(countryNode* a,countryNode* b)
    {
        return(stol(a->recoveredCountry)>stol(b->recoveredCountry));

    }
    static bool ComparatorARC(countryNode* a,countryNode* b)
    {

        if((a->ActiveRate>b->ActiveRate))
            {if(stol(a->activeCountry)>stol(b->activeCountry))
                return true;
            else if(stol(a->deathsCountry)>stol(b->deathsCountry))
                return true;
            }
        else if(stol(a->confirmedCountry)>stol(b->confirmedCountry))
                return true;
        else
            return false;


    }




   static bool ComparatorRRC(countryNode* a,countryNode* b)
    {

        if(a->RecoverRate>b->RecoverRate)
           {if(stol(a->recoveredCountry)>stol(b->recoveredCountry))
                return true;

           }
        else if(stol(a->confirmedCountry)>stol(b->confirmedCountry))
        {
            if(stol(a->activeCountry)<stol(b->activeCountry))
                return true;
        }
          //  return true;
        else if (stol(a->confirmedCountry)>stol(b->confirmedCountry))
        {
                           return true;
        }

        else
            return false;
    }
     void ActiveCasesSortC()
    {
          sort(Countryarr.begin(),Countryarr.end(),ComparatorAC);
        cout<<"#-------------------------------MAXIMUM ACTIVE CASES COUNTRIES------------------------------------------#"<<endl;

        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<left<<setw(40)<<"   COUNTRIES                                                       ACTIVE CASES            "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
         for(int i=0;i<Countryarr.size();i++)
          {
            countryNode*p=Countryarr[i];
            cout<<left<<setw(40)<<Countryarr[i]->nameOfCountry<<setw(15)<<"\t\t"<<Countryarr[i]->activeCountry<<endl;
          }
    }
    void RecoveryCaseSortC()
    {

          sort(Countryarr.begin(),Countryarr.end(),ComparatorRC);
        cout<<"#-------------------------------MAXIMUM RECOVERY CASES COUNTRIES------------------------------------------#"<<endl;

        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<left<<setw(40)<<"   COUNTRIES                                                       RECOVERED CASES         "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
         for(int i=0;i<Countryarr.size();i++)
          {
            countryNode*p=Countryarr[i];
            cout<<left<<setw(40)<<Countryarr[i]->nameOfCountry<<setw(15)<<"\t\t"<<Countryarr[i]->recoveredCountry<<endl;
          }
    }
    void MaxActiveRateSortC()
    {
          sort(Countryarr.begin(),Countryarr.end(),ComparatorARC);
        cout<<"#-------------------------------SEVERITY OF COUNTRIES IN DECREASING ORDER------------------------------------------#"<<endl;

        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<left<<setw(40)<<"   COUNTRIES                                                       ACTIVE CASE RATE        "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
         for(int i=0;i<Countryarr.size();i++)
          {
            countryNode*p=Countryarr[i];
            cout<<left<<setw(40)<<Countryarr[i]->nameOfCountry<<setw(15)<<"\t\t"<<Countryarr[i]->ActiveRate<<endl;
          }
    }
    void MaxRecoveryRateSortC()
    {

          sort(Countryarr.begin(),Countryarr.end(),ComparatorRRC);
        cout<<"#-------------------------------RECOVERY RATE OF COUNTRIES IN DECREASING ORDER------------------------------------------#"<<endl;

        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<left<<setw(40)<<"   COUNTRIES                                                       RECOVERY RATE        "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
         for(int i=0;i<Countryarr.size();i++)
          {
            countryNode*p=Countryarr[i];
            cout<<left<<setw(40)<<Countryarr[i]->nameOfCountry<<setw(15)<<"\t\t"<<Countryarr[i]->RecoverRate<<endl;
          }
    }



    void insertNodeCountry(countryNode *temp)
    {
        countryNode *temp1;
        int position=hashFn(temp->nameOfCountry);
        cout<<position<<endl;
        if(arrayOfCountries[position]==NULL)
        {
           // cout<<"1\n";
            arrayOfCountries[position]=temp;
        }
        else
        {
            arrayOfCountries[position]=insertcountryNode(arrayOfCountries[position],temp);
        }
        //cout<<temp->nameOfCountry<<" "<<position<<endl;
    }
    int height(countryNode *N)
    {
    if (N == NULL)
        return 0;
    return N->height;
    }
    int getBalance(countryNode *N)
    {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
    }
    countryNode* rightRotate(countryNode* oldR)
    {
        countryNode* newR=oldR->left;
        countryNode* temp=newR->right;
        newR->right=oldR;
        oldR->left=temp;
        oldR->height=(getMax(height(oldR->left),height(oldR->right))+1);
        newR->height=(getMax(height(newR->left),height(newR->right))+1);
        return newR;

    }
    countryNode* leftRotate(countryNode* oldR)
    {
        countryNode* newR=oldR->right;
        countryNode* temp=newR->left;
        newR->left=oldR;
        oldR->right=temp;
        oldR->height=(getMax(height(oldR->left),height(oldR->right))+1);
        newR->height=(getMax(height(newR->left),height(newR->right))+1);
        return newR;
    }


    countryNode* insertcountryNode(countryNode* root,countryNode *temp)
    {

    if (root == NULL)
        return(temp);

    if (temp->nameOfCountry < root->nameOfCountry)
        root->left =insertcountryNode(root->left, temp);
    else if (temp->nameOfCountry > root->nameOfCountry)
        root->right = insertcountryNode(root->right, temp);
    else // Equal keys are not allowed in BST
        return root;


    root->height = 1 + getMax(height(root->left),
                        height(root->right));

    int balance = getBalance(root);


    if (balance > 1 && temp->nameOfCountry < root->left->nameOfCountry)
        return rightRotate(root);

    if (balance < -1 && temp->nameOfCountry > root->right->nameOfCountry)
        return leftRotate(root);

    if (balance > 1 && temp->nameOfCountry > root->left->nameOfCountry)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }


    if (balance < -1 && temp->nameOfCountry < root->right->nameOfCountry)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
 int displayAllCountries()
    {
        countryNode *current;
        countryNode *total;
        this->ind=1;
        cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
            cout<<"             COUNTRIES                                  CONFIRMED        RECOVERED       DEATHS       ACTIVE                       ";
            cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
        for(int i=0;i<max1;i++)
        {
            current=arrayOfCountries[i];
           // cout<<"\n"<<i<<" : ";
                    INorderC(arrayOfCountries[i]);
           /* while(current!=NULL)
            {
                cout<<current->nameOfState<<"\t"<<current->confirmedCases<<"\t"<<current->recoveredCases<<"\t"<<current->deathsState<<"\t"<<current->deathsState<<endl;
               // current=current->next;
            }*/
        }
        DisplayTotalC();
       // cout<<ind<<":"<<setw(40)<<left<<total->nameOfState<<"\t\t"<<total->confirmedState<<"\t\t"<<total->recoveredState<<"\t\t"<<total->deathsState<<"\t\t"<<total->deathsState<<endl;

    }
    void DisplayTotalC()
    {
        string total="TOTAL";
        int pos =hashFn(total);

        countryNode* current=arrayOfCountries[pos];
        while(current)
        {
            if(total==current->nameOfCountry)
            {
                cout<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                cout<<"--:"<<setw(40)<<left<<current->nameOfCountry<<"\t\t"<<current->confirmedCountry<<"\t\t"<<current->recoveredCountry<<"\t\t"<<current->deathsCountry<<"\t\t"<<current->activeCountry<<endl;
                break;
            }
            else if(total>current->nameOfCountry)
                current=current->right;
            else if(total<current->nameOfCountry)
                current=current->left;
        }
    }
    countryNode* INorderC(countryNode* current)
    {
        countryNode* tot=NULL;
    if(current)
    {
        INorderC(current->left);
        if(current->nameOfCountry=="TOTAL")
            tot=current;
        if(current->nameOfCountry!="TOTAL" )
        {


            cout<<ind<<":"<<setw(40)<<left<<current->nameOfCountry<<"\t\t"<<current->confirmedCountry<<"\t\t"<<current->recoveredCountry<<"\t\t"<<current->deathsCountry<<"\t\t"<<current->activeCountry<<endl;
            this->ind ++;
        }
        INorderC(current->right);
       } //if(tot)
          //  return tot;

    }

   /* void displayAllCountry()
    {
        countryNode *current;
        for(int i=0;i<max1;i++)
        {
            current=arrayOfCountries[i];
            cout<<"\n"<<i<<" : ";
            while(current!=NULL)
            {
                cout<<current->nameOfCountry<<"\t"<<current->confirmedCountry<<"\t"<<current->recoveredCountry<<"\t"<<current->deathsCountry<<"\t"<<current->deathsCountry<<endl;
               // current=current->next;
            }
        }
    }*/
    void searchCountry()
    {
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<setw(110)<<setfill(' ')
        <<"Enter the name of Country : ";
        string name,name1;
        //cin.ignore();
        fflush(NULL);
        getline(cin,name);
        name1=name;
        int pos=hashFn(name);
        countryNode *temp;
        for(int i=0;name[i]!='\0';i++)
            name[i]=toupper(name[i]);
        countryNode *current;
        int flag=0;
        /*for(int i=0;i<max1;i++)
        {
            current=arrayOfCountries[i];
            while(current!=NULL)
            {
                if(name==current->nameOfCountry)
                {
                    cout<<"\n\t\tRECORD FOUND.........!!!!!\n\n";
                    cout<<"\t\tCOUNTRY\t\t\t\tCONFIRMED\t\tRECOVERED\t\tDEATHS\t\tACTIVE\n";


                    break;
                }
                else
                    current=current->next;
            }
        }*/
        current=arrayOfCountries[pos];
        while(current)
        {

            if(name==current->nameOfCountry)
            {
                cout<<"Record Found .....    :) !!!! \n";
                 cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
                cout<<"             COUNTRIES                                  CONFIRMED        RECOVERED         DEATHS        ACTIVE                       ";
                cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
                cout<<left<<setw(40)<<current->nameOfCountry<<"\t\t"<<setw(15)<<current->confirmedCountry<<setw(8)<<"\t"<<current->recoveredCountry<<"\t\t"<<setw(8)<<current->deathsCountry<<"\t"<<setw(8)<<current->activeCountry<<endl;
                flag=1;
                break;

            }

            else if(name<current->nameOfCountry)
                current=current->left;
            else if(name>current->nameOfCountry)
                current=current->right;
               // current=current->next;


        }
        if(flag==0)
            cout<<"NO record found for "<<name1<<"   :(...."<<endl;
    }
};
bool pointer(int real,int current)
{
    if(real==current)
    {
        cout<<" >> ";
        return true;
    }
    else{
        cout<<"    ";
        return false;
    }
}
class Node
{
    public: string state,city,organz,phnumber;
    int height;
    Node* left,*right;
    Node()
    {   height=1;
        //phnumber="No number found";
        left=right=NULL;
    }

};
class AVl_For_TestLabs
{
    public: Node* root;
    AVl_For_TestLabs()
    {
        root=NULL;
    }
    void Create()
    {
        ifstream infile;
        infile.open("Testlab.csv");
        infile.seekg(0);
        while(infile.good())
        {
            if(infile.tellg()==ios::beg)
            {
                 infile.ignore(numeric_limits<streamsize>::max(),'\n');

            }
            string stringforbreak;
            Node* temp=new Node;
            getline(infile,temp->state,',');
            getline(infile,temp->city,',');
            getline(infile,temp->organz,'\n');
            /*if(temp->organz[0]=='"')
            {
                i=0;
                getline(infile,stringforbreak,'"');
                for(int j=1;temp->nameOfCountry[j];j++)
                {
                    string1[i++]=temp->organz[j];
                }
                for(int j=0;stringforbreak[j]!='"';j++)
                {
                    string1[i++]=stringforbreak[j];
                }
                string1[i]='\0';
                temp->nameOfCountry=string1;
            }*/
            //getline(infile,temp->phnumber,'\n');
            for(int i=0;temp->city[i];i++)
                temp->city[i]=toupper(temp->city[i]);

            if(!infile.eof())
               {
                root=insertNode(root,temp);
                //DisplayNode(temp);

               }
        }

        infile.close();
         fflush(NULL);
    }

     void DisplayNode()
    {
        //cout<<temp->state<<"\t\t"<<temp->city<<"\t\t"<<temp->organz<<"\t\t"<<temp->phnumber<<endl;
        cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
        cout<<"    STATE                          CITY                                             ORGANIZATION                                                 ";
        cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
        Inorder(this->root);
    }
     int getMax(int a,int b)
    {
        return (a>b)?a:b;
    }
    int height(Node *N)
    {
    if (N == NULL)
        return 0;
    return N->height;
    }
    int getBalance(Node *N)
    {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
    }
    Node* rightRotate(Node* oldR)
    {
        Node* newR=oldR->left;
        Node* temp=newR->right;
        newR->right=oldR;
        oldR->left=temp;
        oldR->height=(getMax(height(oldR->left),height(oldR->right))+1);
        newR->height=(getMax(height(newR->left),height(newR->right))+1);
        return newR;

    }
    Node* leftRotate(Node* oldR)
    {
        Node* newR=oldR->right;
        Node* temp=newR->left;
        newR->left=oldR;
        oldR->right=temp;
        oldR->height=(getMax(height(oldR->left),height(oldR->right))+1);
        newR->height=(getMax(height(newR->left),height(newR->right))+1);
        return newR;
    }


    Node* insertNode(Node* root,Node *temp)
    {

    if (root == NULL)
        return(temp);

    if (temp->city < root->city)
        root->left =insertNode(root->left, temp);
    else if (temp->city > root->city)
        root->right = insertNode(root->right, temp);
    else // Equal keys are not allowed in BST
        return root;


    root->height = 1 + getMax(height(root->left),
                        height(root->right));

    int balance = getBalance(root);


    if (balance > 1 && temp->city < root->left->city)
        return rightRotate(root);

    if (balance < -1 && temp->city > root->right->city)
        return leftRotate(root);

    if (balance > 1 && temp->city > root->left->city)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }


    if (balance < -1 && temp->city < root->right->city)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
  void Inorder(Node* temp)
  {
      if(temp)
      {
          Inorder(temp->left);

          cout<<setw(32)<<left<<temp->state<<setw(16)<<temp->city<<"\t\t"<<setw(16)<<temp->organz<<"\t\t"<<endl;
          Inorder(temp->right);

      }
  }
    void Search()
    {
        string name;
        cout<<"\n\n\n\n\n\n\n";
        cout<<"Enter Your City name"<<endl;
        cin>>name;
        string name1=name;
        for(int i=0;name[i];i++)
                name[i]=toupper(name[i]);
        Node* current=root;
        int flag=0;
        while(current)
        {

            if(name==current->city)
            {
                cout<<"Record Found .....    :) !!!! \n";
                 cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
                cout<<"        STATE                       CITY                                       ORGANIZATION                                                 ";
                cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
                cout<<setw(32)<<left<<current->state<<setw(16)<<current->city<<"\t\t"<<setw(16)<<current->organz<<endl;
                flag=1;
                break;

            }

            else if(name<current->city)
                current=current->left;
            else if(name>current->city)
                current=current->right;
               // current=current->next;


        }
        if(flag==0)
            cout<<"NO record found for "<<name1<<"   :(...."<<endl;
    }




};
int main()
{
    //int choice;
   /* string stateName,confirmed,recovered,deaths,active,temp;
    bool flag;
    //char yn;
    ifstream infile;

    hashTable h;
    int choice;
    char yn='y';
    h.constructState();
    while(yn!='n')
    {
        cout<<"\n\n\t\t----------Corona Stats--------\n";
        cout<<"\n\t\t1.Records of all statesn\n\t\t2.Records for particular state\n\n\t\tEnter choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            infile.open("Sample.csv");
                cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
                cout<<"             STATE                                    Confirmed          RECOVERED          DEATHS          ACTIVE                       ";
                cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
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
                    if(!infile.eof())
                        cout<<left<<setw(40)<<stateName<<"\t\t"<<setw(15)<<confirmed<<setw(8)<<"\t"<<recovered<<"\t\t"<<setw(8)<<deaths<<"\t"<<setw(8)<<active<<endl;

                }
                infile.close();
                break;
        case 2:
            h.searchState();

            break;

        }
        cout<<"\nDo you want to continue ? ";
        cin>>yn;
    } */


  //  system("cls");
   // system("color 02");
   // cout<<"\n\n\n\n\n\t\t\t\t-------<<<Welcome to CoronaPedia>>>-------";
   // delay(2000);
   string t1="python Cov.py";
   system(t1.c_str());
   string t2="python councov.py";

   system(t2.c_str());
//   string t3="python Testinglab.py";
  // system(t3.c_str());
    hashTable h;
   //h.constructState();
 //  h.constructCountry();
        initwindow(1000,400,"CoronaPedia");
        settextstyle(5,0,6);
        rectangle(60,150,940,260);
        rectangle(30,120,970,290);
        setfillstyle(7,14);
        floodfill(35,125,15);
        setcolor(15);
        setbkcolor(2);
        outtextxy(80,180,"WELCOME TO CORONAPEDIA");
        settextstyle(1,0,3);
        setcolor(15);
        setbkcolor(0);
        outtextxy(300,320,"Loading");
        //for(int i=0;i<7;i++)
        //
            for(int j=0;j<20;j++)
            {
                outtextxy(435+(j*10),320,"..");
                delay(300);
            }
        //}
        //delay(3000);
        closegraph();
        h.constructState();
   h.constructCountry();
    char getinput,getinputth,getinputgr,ynmainst,ynth,yngr,getinputmain,ynmainmenu,ynmaincr,ynmaint,getinputt;
    int position=1,thposition=1,grposition=1,positionmain=1,positiont=1;
    do{
        position=1,thposition=1,grposition=1,positionmain=1,positiont=1;
        getinput=getinputth=getinputgr=getinputmain=48,getinputt=48;
        while(getinputmain!=13)
        {
            system("cls");
            system("color 03");
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t   ==========< MAIN MENU >==========\n\n";
            cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(1,positionmain); cout<<"1.STATES' DATA             |\n\n";
            cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(2,positionmain); cout<<"2.COUNTRIES' DATA          |\n\n";
            cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(3,positionmain); cout<<"3.SYMPTOM CHECKER          |\n\n";
            cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(4,positionmain); cout<<"4.TEST LABS IN INDIA       |\n\n";
            cout<<"\t\t\t\t\t\t\t\t\t\t   =================================\n\n\n";
            getinputmain=_getch();
            if(getinputmain==80 && positionmain!=4)
                    positionmain++;
                else if(getinputmain== 72 && positionmain!=1)
                    positionmain--;
                else
                    positionmain=positionmain;
        }

        switch(positionmain)
        {
            case 1:
                statelabel:
                system("cls");
                while(getinput!=13)
                {
                    system("cls");
                    system("color 06");
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t   ==========< STATE DATA MENU >==========\n\n";
                    cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(1,position); cout<<"1.Theoretical Database           |\n\n";
                    cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(2,position); cout<<"2.Graphical Database             |\n\n";
                    cout<<"\t\t\t\t\t\t\t\t\t\t   =======================================\n\n\n";
                    getinput=_getch();
                    cout.flush();
                    fflush(stdin);
                    if(getinput==80 && position!=2)
                        position++;
                    else if(getinput== 72 && position!=1)
                        position--;
                    else
                        position=position;
                }
                if(getinput==13)
                {
                    switch(position)
                    {
                        case 1:
                        thlabel:
                        system("cls");
                        while(getinputth!=13)
                        {
                            system("cls");
                            system("color E5");
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t     -----------------<<< Theoretical Database  >>>----------------\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(1,thposition); cout<<"1.All States                                        |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(2,thposition); cout<<"2.Search State                                      |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(3,thposition); cout<<"3.Maximum active cases state                        |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(4,thposition); cout<<"4.Show states with severity rate                    |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(5,thposition); cout<<"5.State with maximum recovery                       |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(6,thposition); cout<<"6.Show states with recovery rate                    |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t\t-----------------------------------------------------------\n\n\n";
                            getinputth=_getch();
                           cout.flush();
                           fflush(stdin);
                            if(getinputth==80 && thposition!=6)
                                thposition++;
                            else if(getinputth== 72 && thposition!=1)
                                thposition--;
                            else
                                thposition=thposition;
                        }
                        if(getinputth==13)
                        {
                            switch(thposition)
                            {
                                case 1:
                                    system("cls");
                                    system("color 0C");
                                    h.displayAll();

                                   // delay(10000);
                                    break;
                                case 2:
                                    system("cls");
                                    system("color 0C");
                                    h.searchState();
                                    //delay(10000);
                                //fun
                                break;
                                case 3:
                                    system("cls");
                                    system("color 0C");
                                    h.ActiveCasesSort();

                                    //fun
                                break;
                                case 4:
                                    system("cls");
                                    system("color 0C");
                                    h.MaxActiveRateSort();
                                    //fun
                                break;
                                case 5:system("cls");
                                    system("color 0C");
                                    h.RecoveryCaseSort();
                                    break;
                                case 6:
                                    system("cls");
                                    system("color 0C");
                                    h.MaxRecoveryRateSort();
                                    break;
                            }
                        }
                        getinputth='0';
                        //system("cls");
                        //system("color 0C");
                        cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tDo you want to go to theoretical data menu ? ";
                        cin>>ynth;
                        if(ynth=='y')
                            goto thlabel;

                        break;
                        case 2:
                        system("cls");
                        while(getinputgr!=13)
                        {
                            grlabel:
                            system("cls");
                            system("color E5");
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t       ----------<<< Graphical Database >>>-----------\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(1,grposition); cout<<"1.All cases caparison                   |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(2,grposition); cout<<"2.Active case Comparison                |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(3,grposition); cout<<"3.Recovery rate comparison              |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(4,grposition); cout<<"4.Death case comparison                 |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(5,grposition); cout<<"5.Confirmed case comparison             |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t\t----------------------------------------------\n\n\n";
                            getinputgr=_getch();
                            cout.flush();
                            fflush(stdin);
                            if(getinputgr==80 && grposition!=5)
                                grposition++;
                            else if(getinputgr== 72 && grposition!=1)
                                grposition--;
                            else
                                grposition=grposition;
                        }
                        if(getinputgr==13)
                        {
                            switch(grposition)
                            {
                                case 1:
                                    system("python Pythonchi.py o");
                                    // fun
                                break;
                                case 2:
                                    system("python Pythonchi.py a");
                                    //fun
                                break;
                                case 3:system("python Pythonchi.py r");
                                    //fun
                                break;
                                case 4:system("python Pythonchi.py d");
                                    //fun
                                break;
                                case 5:
                                    system("python Pythonchi.py c");
                                    //fun
                                break;
                            }
                        }
                        getinputgr='0';
                       // system("cls");
                       // system("color 0C");
                        cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tDo you want to access more from graphical data menu ? ";
                        cin>>yngr;
                        if(yngr=='y')
                            goto grlabel;
                        break;
                    }

                }
                    getinput='0';
                    system("cls");
                    system("color 02");
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tDo you want to goto state data menu ? ";
                    cin>>ynmainst;
                    if(ynmainst=='y')
                        goto statelabel;
                    break;
            case 2:
                countrylabel:
                    getinput='0';
                system("cls");
                while(getinput!=13)
                {
                    system("cls");
                    system("color 06");
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t   s========< COUNTRY DATA MENU >========\n\n";
                    cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(1,position); cout<<"1.Theoretical Database        |\n\n";
                    cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(2,position); cout<<"2.Graphical Database          |\n\n";
                    cout<<"\t\t\t\t\t\t\t\t\t\t   ====================================\n\n\n";
                    getinput=_getch();
                    cout.flush();
                    fflush(stdin);
                    if(getinput==80 && position!=2)
                        position++;
                    else if(getinput== 72 && position!=1)
                        position--;
                    else
                        position=position;
                }
                if(getinput==13)
                {
                    switch(position)
                    {
                        case 1:
                        thlabelcr:
                        system("cls");
                        while(getinputth!=13)
                        {
                            system("cls");
                            system("color E5");
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t   ------------<<< Theoretical Database  >>>-------------\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(1,thposition); cout<<"1.All countries                                        |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(2,thposition); cout<<"2.Search country                                       |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(3,thposition); cout<<"3.Maximum active cases country                         |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(4,thposition); cout<<"4.Show counytry with severity rate                     |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(5,thposition); cout<<"5.Country with maximum recovery                        |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(6,thposition); cout<<"6.Show country with recovery rate                      |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t\t    ----------------------------------------------------\n\n\n";
                            getinputth=_getch();
                            cout.flush();
                            fflush(stdin);
                            if(getinputth==80 && thposition!=6)
                                thposition++;
                            else if(getinputth== 72 && thposition!=1)
                                thposition--;
                            else
                                thposition=thposition;
                        }
                        if(getinputth==13)
                        {
                            switch(thposition)
                            {
                                case 1:
                                    system("cls");
                                    system("color 0C");
                                    h.displayAllCountries();
                                // fun
                                break;
                                case 2:
                                    system("cls");
                                    system("color 0C");
                                    h.searchCountry();
                                //fun
                                break;
                                case 3:
                                    system("cls");
                                    system("color 0C");
                                    h.ActiveCasesSortC();
                                    //fun
                                break;
                                case 4:
                                    system("cls");
                                    system("color 0C");
                                    h.MaxActiveRateSortC();
                                    //fun
                                break;
                                case 5:
                                    system("cls");
                                    system("color 0C");
                                    h.RecoveryCaseSortC();
                                    break;

                                case 6:
                                    system("cls");
                                    system("color 0C");
                                    h.MaxRecoveryRateSortC();
                                    break;
                            }
                        }
                        getinputth='0';

                        cout<<"\n\n\n\n\n\n\n\n\\n\t\t\t\t\t\t\t\tDo you want to go to theoretical data menu ? ";
                        cin>>ynth;
                        if(ynth=='y')
                            goto thlabelcr;

                        break;
                        case 2:
                        system("cls");
                        while(getinputgr!=13)
                        {
                            grlabelcr:
                            system("cls");
                            system("color E5");
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t-------<<< Graphical Database >>>------\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(1,grposition); cout<<"1.All cases caparison            |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(2,grposition); cout<<"2.Active case Comparison         |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(3,grposition); cout<<"3.Recovery rate comparison       |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(4,grposition); cout<<"4.Death case comparison          |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t       |  "; pointer(5,grposition); cout<<"5.Confirmed case comparison      |\n\n";
                            cout<<"\t\t\t\t\t\t\t\t\t\t---------------------------------------\n\n\n";
                            getinputgr=_getch();
                            cout.flush();
                            fflush(stdin);
                            if(getinputgr==80 && grposition!=5)
                                grposition++;
                            else if(getinputgr== 72 && grposition!=1)
                                grposition--;
                            else
                                grposition=grposition;
                        }
                        if(getinputgr==13)
                        {
                            switch(grposition)
                            {
                                case 1:
                                    system("python CountriesGraph.py o");
                                    // fun
                                break;
                                case 2:
                                    system("python CountriesGraph.py a");
                                    //fun
                                break;
                                case 3:
                                    system("python CountriesGraph.py r");
                                    //fun
                                break;
                                case 4:
                                    system("python CountriesGraph.py d");
                                    //fun
                                break;
                                case 5:
                                    system("python CountriesGraph.py c");
                                    //fun
                                break;
                            }
                        }
                        getinputgr='0';
                        //system("cls");
                      //  system("color 0C");
                        cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tDo you want access more from graphical data menu ? ";
                        cin>>yngr;
                        if(yngr=='y')
                            goto grlabelcr;
                        break;

                    }

                }
                    system("cls");
                    system("color 02");
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tDo you want to goto country data menu ? ";
                    cin>>ynmaincr;
                    if(ynmaincr=='y')
                        goto countrylabel;
                    break;
                case 3:
                system("cls");
                check();
                break;
                case 4:
                    AVl_For_TestLabs a;
                    a.Create();
                    testlabel:
                        getinputt=48;
                    while(getinputt!=13)
                    {
                        system("cls");
                        system("color 02");
                        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t   =========< TEST LABS >==========\n\n";
                        cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(1,positiont); cout<<"1.Display all test Labs     |\n\n";
                        cout<<"\t\t\t\t\t\t\t\t\t          |  "; pointer(2,positiont); cout<<"2.Search test labs in city |\n\n";
                        cout<<"\t\t\t\t\t\t\t\t\t\t   =====================================\n\n\n";
                        getinputt=_getch();
                        cout.flush();
                        fflush(stdin);
                        if(getinputt==80 && positiont!=2)
                            positiont++;
                        else if(getinputt== 72 && positiont!=1)
                            positiont--;
                        else
                            positiont=positiont;
                    }
                    switch(positiont)
                    {
                        case 1:
                            system("cls");
                                    system("color 0C");
                            a.DisplayNode();
                        break;
                        case 2:
                            system("cls");

                                    system("color 0C");
                            a.Search();
                        break;

                    }
                    cout<<"\n\n\n\n\n\t\t\t\t\t\t\t\t\t  Do you want to go to test centre menu ? ";
                    cin>>ynmaint;
                    if(ynmaint=='y')
                        goto testlabel;
                break;

        }

        system("color 02");
        cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tDo you want to go to main menu ? ";
        cin>>ynmainmenu;
        cout<<"\n\n\n\n\\n\n\n\\n\n\n\n\n\\n\n\\n\n\n\n\\n\n\n\n";
    }while(ynmainmenu=='y');


    //hashTable h1;
   // h1.constructCountry();
    //h1.displayAllCountry();
    //h1.searchCountry();
    return 0;
}



