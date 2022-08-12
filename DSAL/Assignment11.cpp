#include<iostream>
#include<climits>
using namespace std;
class MinHeap
{
private:
    int *heap;
    int heapSize;
public:
    void inputHeap()
    {
        cout<<" Enter the number of elements of the Min-Heap : ";
        cin>>heapSize;
        heap=new int[heapSize];
        cout<<" Enter "<<heapSize<<" number of elements to sort using Heap Sort : ";
        for(int i=0;i<heapSize;i++)
        {
            cin>>heap[i];
        }

        for(int i=(heapSize-1)/2;i>=0;i--)
        {
            Minheapify(i);
        }
    }

    void display()
    {
        cout<<" The elements in Min-Heap are : ";
        for(int i=0;i<heapSize;i++)
        {
            cout<<heap[i]<<" ";
        }
    }

    void Minheapify(int parent)
    {
        int leftChild=2*parent+1;
        int rightChild=2*parent+2;
        int smallest=parent;
        if((leftChild < heapSize) && (heap[leftChild] < heap[parent]))
        {
            smallest=leftChild;
        }
        if((rightChild < heapSize) && (heap[rightChild] < heap[smallest]))
        {
            smallest=rightChild;
        }

        if(smallest!=parent)
        {
            int temp=heap[smallest];
            heap[smallest]=heap[parent];
            heap[parent]=temp;
            Minheapify(smallest);
        }
    }

    int getMin()
    {
        if(heapSize<=0)
        {
            cout<<" The Min-Heap is Empty !!"<<endl;
            return INT_MAX;
        }

        if(heapSize==1)
        {
            int root=heap[0];
            heapSize--;
            return root;
        }

        int root=heap[0];
        heap[0]=heap[heapSize-1];
        heapSize--;
        Minheapify(0);
        return root;
    }

    void heapSort()
    {
        int sortedArray[heapSize];
        int size=heapSize;
        for(int i=0;i<size;i++)
        {
            sortedArray[i]=getMin();
        }

        cout<<"The sorted array is : ";
        for(int i=0;i<size;i++)
        {
            cout<<sortedArray[i]<<" ";
        }
    }
};
int main()
{
    MinHeap obj;
    int option;
    do
    {
        cout<<"----------------Menu----------------"<<endl;
        cout<<" 1. Create the Min-Heap "<<endl;
        cout<<" 2. Display the Min-Heap "<<endl;
        cout<<" 3. Extract minimum element from Min-Heap "<<endl;
        cout<<" 4. Heap Sort "<<endl;
        cout<<" 5. Exit "<<endl;
        cout<<"Enter the option : ";
        cin>>option;
        switch (option)
        {
        case 1:
            obj.inputHeap();
            break;
        case 2:
            obj.display();
            break;    
        case 3:
            cout<<" The minimum element from Min-Heap is : "<<obj.getMin();
            break;
        case 4:
            obj.heapSort();
            break;  
        case 5:
            exit(0);          
        }
        cout<<endl;
    } while (option>=1 && option<=4);
    
    return 0;
}