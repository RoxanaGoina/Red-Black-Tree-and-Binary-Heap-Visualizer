#include<iostream>
#include<cmath>
using namespace std;
class heap
{
public:
    int arr[100];
    int size;
    heap()
    {
        arr[0]=-1;
        size=0;
    }
    void inser(int val)
    {
        size=size+1;
        int index=size;
        arr[index]=val;
        while(index>1)
        {
            int parent=i/2;
            if(arr[parent]<arr[index])
            {
                swap(arr[parent],arr[index]);
                index=parent;
            }
            else
            {
                return;

            }
        }

    }
    void print()
    {
        string indent1="           ";
        int i=1;
        cout<<indent1;
        cout<<arr[0]<<endl;
        string indent="               ";
        int nivel=2;
        while(i<size)
        {
            int half=indent.size()/2+0.5;
            indent=indent=indent.substr(0,half) ;
            //indent="     ";
            for(int j=0; j<pow(2,nivel-1); j++)
            {
                cout<<indent<<arr[i];
                i++;
                if(i>=size)
                    return;

            }
            cout<<endl;
            nivel++;
        }
    }




};

void delete()
{
    if(size==0)
    {
        cout<<"Binary Heap empty";
        return;
    }
    arr[1]=arr[size];
    size--;
    int i=0;
    while(i<size)
    {

        int leftIndex=2*i;
        int rightIndex=2*i+1;
        if(leftIndex<size && arr[i]<arr[leftIndex])
        {
            swap(arr[i],arr[leftIndex]);


        }
    }


}
int main()
{
    heap h;
    h.insert(50);
    h.insert(55);
    h.insert(53);
    h.inser(30);
    h.print();
}
