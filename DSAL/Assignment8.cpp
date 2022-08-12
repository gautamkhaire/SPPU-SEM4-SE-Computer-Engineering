#include <iostream>
using namespace std;
class Node
{
private:
    int vertex;
    Node *link;
public :
    Node()
    {
        vertex = 0;
        link = NULL;
    }
    Node(int vertex)
    {
        this->vertex = vertex;
        link = NULL;
    }
    friend class Graph;
    friend class Queue;
};
class Queue
{
private:
    Node *front;
    Node *rear;
public:
    Queue()
    {
        front=NULL;
        rear=NULL;
    }

    void push(int element)
    {
        Node* newNode=new Node(element);
        if(front==NULL)
        {
            front=newNode;
            rear=newNode;
        }
        else
        {
            rear->link=newNode;
            rear=newNode;
        }
    }
    
    bool isEmpty()
    {
        if(front==NULL)
        {
            return true;
        }
        return false;
    }

    int Front()
    {
        if(isEmpty())
        {
            return -1;
        }
        return front->vertex;
    }

    void pop()
    {
        if(isEmpty())
        {
            return ;
        }
        else
        {
            if(front->link==NULL)
            {
                delete front;
                front=NULL;
                rear=NULL;
            }
            else
            {
                Node* temp=front->link;
                front->link=NULL;
                delete front;
                front=temp;
            }
        }
    }
    friend class Graph;
};
class Graph
{
private:
    Node *head[100];
    int indegreeArray[100];
    int vertices,edges;
public:
    void create_graph()
    {
        cout<<" Enter the number of vertices of the Graph : ";
        cin>>vertices;

        for(int i=0;i<=vertices;i++)
        {
            head[i]=NULL;
            indegreeArray[i]=0;
        }

        cout<<" Enter the number of edges of the Graph : ";
        cin>>edges;
        while(edges--)
        {
            int startVertex,endVertex;
            cout<<" Enter an edge (startVertex,endVertex) : ";
            cin>>startVertex>>endVertex;
            insert_edge(startVertex,endVertex);
        }
        cout<<endl;
    }

    void insert_edge(int startVertex,int endVertex)
    {
        Node* newNode=new Node(endVertex);
        if(head[startVertex]==NULL)
        {
            head[startVertex]=newNode;
        }
        else
        {
            Node* temp=head[startVertex];
            while(temp->link!=NULL)
            {
                temp=temp->link;
            }
            temp->link=newNode;
        }
    }

    void display_graph()
    {
        for(int i=1;i<=vertices;i++)
        {
            cout<<i<<" -> ";
            Node* temp=head[i];
            while(temp!=NULL)
            {
                cout<<temp->vertex;
                if(temp->link!=NULL)
                {
                    cout<<",";
                }
                temp=temp->link;
            }
            cout<<endl;
        }
    }

    void topologicalSort()
    {
        int topologicalOrder[100];

        for(int i=1;i<=vertices;i++)
        {
            Node* temp=head[i];
            while(temp!=NULL)
            {
                indegreeArray[temp->vertex]++;
                temp=temp->link;
            }
        }

        Queue queue;
        for(int i=1;i<=vertices;i++)
        {
            if(indegreeArray[i]==0)
            {
                queue.push(i);
            }
        }

        int count=0;
        while(!queue.isEmpty())
        {
            topologicalOrder[count]=queue.Front();
            Node* current=head[queue.Front()];
            queue.pop();
            count++;
            while(current!=NULL)
            {
                indegreeArray[current->vertex]--;
                if(indegreeArray[current->vertex]==0)
                {
                    queue.push(current->vertex);
                }
                current=current->link;
            }
        }
        cout<<endl;

        if(count==vertices)
        {
            cout<<" The Topological order of the Graph is : ";
            for(int i=0;i<count;i++)
            {
                cout<<topologicalOrder[i]<<" ";
            }
            cout<<endl;
        }
        else
        {
            cout<<" The Graph is not a Directed Acyclic Graph (DAG) , so the Topological order doesn't exist. ";
        }
    }

};
int main()
{
    Graph obj;
    int option;
    do
    {
        cout<<"------------------Menu------------------"<<endl;
        cout<<" 1. Create a Graph "<<endl;
        cout<<" 2. Display the Graph "<<endl;
        cout<<" 3. Topological Sort "<<endl;
        cout<<" 4. Exit "<<endl;
        cout<<"Enter the option : ";
        cin>>option;
        switch(option)
        {
            case 1:
                obj.create_graph();
                break;
            case 2:
                obj.display_graph();
                break;    
            case 3:
                obj.topologicalSort();
                break;    
            case 4:
                exit(0);    
        }
        cout<<endl;
    }while(option>=1 && option<=3);
    return 0;
}