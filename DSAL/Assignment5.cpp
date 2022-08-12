#include<iostream>
using namespace std;
class Node
{
private:
    string key;
    string value;
    Node* link;
public:
    Node()
    {
        key=" ";
        value=" ";
        link=NULL;
    }    

    Node(string key,string value)
    {
        this->key=key;
        this->value=value;
        link=NULL;
    }

    friend class Dictionary;
};

class Dictionary
{
private:
    Node **hashTable;

    int hashingFunction(string& keyword)
    {
        int count=0;
        int len=keyword.length();
        for(int i=0;i<len;i++)
        {
            keyword[i]=char(tolower(keyword[i]));
            count+=(keyword[i]-'a');
        }

        return (count%100);
    }
public:
    Dictionary()
    {
        hashTable=new Node*[100];
        for(int i=0;i<100;i++)
        {
            hashTable[i]=NULL;
        }
    }  

    void insert_word()
    {
        string keyword;
        cout<<" Enter the Keyword : ";
        cin>>keyword;
        cin.ignore(100,'\n');
        string meaning;
        cout<<" Enter the meaning for the keyword "<<keyword<<" : ";
        getline(cin,meaning);

        int index=hashingFunction(keyword);

        Node *previous=NULL;
        Node *current=hashTable[index];
        Node* newNode=new Node(keyword,meaning);
        while(current!=NULL && current->key!=keyword)
        {
            previous=current;
            current=current->link;
        }

        if(current==NULL)
        {
            current=newNode;
            if(previous==NULL)
            {
                hashTable[index]=current;
                cout<<" Word inserted Successfully in the Dictionary !!"<<endl;
            }
            else
            {
                previous->link=current;
            }
        }
        else
        {
            cout<<" The keyword : "<<keyword<<" already exist's in the Dictionary with the meaning : "<<current->value<<endl;
            char ch='n';
            cout<<" Do you want to update the meaning of "<<keyword<<" ? (y/n)"<<endl;
            cin>>ch;
            if(ch=='y')
            {
                current->value=meaning;
                cout<<" Meaning updated Successfully !! "<<endl;
            }
        } 
    }  

    void search_word()
    {
        string keyword;
        cout<<" Enter the Keyword : ";
        cin>>keyword;
        
        int index=hashingFunction(keyword);
        Node *current=hashTable[index];
        if(current==NULL)
        {
            cout<<" The Word doesn't exist in the Dictionary. "<<endl;
            return ;
        }
        else
        {
            while(current!=NULL)
            {
                if(current->key==keyword)
                {
                    cout<<" The Meaning of keyword "<<keyword<<" is : "<<current->value<<endl;
                    return ;
                }
                current=current->link;
            }
            cout<<" The Word doesn't exist in the Dictionary. "<<endl; 
        }
    }

    void delete_word()
    {
        string keyword;
        cout<<" Enter the keyword you want to delete from the Dictionary : ";
        cin>>keyword;

        int index=hashingFunction(keyword);
        Node *previous=NULL;
        Node *current=hashTable[index];
        if(current==NULL)
        {
            cout<<" The Word doesn't exist in the Dictionary. "<<endl;
            return ;
        }
        else
        {
            while(current->link!=NULL && current->key!=keyword)
            {
                previous=current;
                current=current->link;
            }

            if(current->link==NULL && current->key!=keyword)
            {
                cout<<" The Word doesn't exist in the Dictionary. "<<endl;
            }
            if(previous!=NULL)
            {
                previous->link=current->link;
            }
            delete current;
            cout<<" Word deleted Successfully from the Dictionary. "<<endl;
        }
    }
};
int main()
{
    Dictionary obj;
    int option;
    do
    {
        cout<<endl;
        cout<<" ------------------- Menu ------------------- "<<endl;
        cout<<" 1. Insert the Keyword & it's Meaning in the Dictionary "<<endl;
        cout<<" 2. Search the Meaning for a Keyword "<<endl;
        cout<<" 3. Delete the Keyword & it's Meaning from the Dictionary "<<endl;
        cout<<" 4. Exit "<<endl;
        cout<<"Enter the option : ";
        cin>>option;
        switch(option)
        {
            case 1:
                obj.insert_word();
                break;
            case 2:
                obj.search_word();
                break;
            case 3:
                obj.delete_word();
                break;
            case 4:
                exit(0);            
        }
        cout<<endl;
    }while(option>=1 && option<=3);
    return 0;
}