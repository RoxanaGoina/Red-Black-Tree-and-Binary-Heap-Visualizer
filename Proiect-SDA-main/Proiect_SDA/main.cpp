#include <cstdlib>
#include "RBNode.h"
#include "IODialog.h"
#include "Heap.h"
//const int CAPACITY =100;
void startProcessing(RBTree*);
void showMenuOption();
 list<int>keys;
void getKeys(list<int>& keys){
    cout<<"Nodurile: ";
    int cheie;
    while(cin>>cheie){
        keys.push_back(cheie);
    }
    cin.clear();
    cin.ignore();
}
void HeapMenu()
{
    int b=0;
    cout<<"Alege optiunea"<<endl;
    cout<<" 1. Adaugare noduri"<<endl;
    cout<<" 2. Vizualizare Min Heap"<<endl;
    cout<<" 3. Vizualizare Max Heap"<<endl;
    cout<<" 4. Inapoi"<<endl;
    cout<<" Alegerea ta este :";

    do
    {
        cin>>b;

        if(b==1)
        {

            getKeys(keys);
            cout<<endl<<endl;
            HeapMenu();
            cout<<endl;
        }
        if(b==2)

        {   Heap h;
            for(auto i=keys.begin();i!=keys.end(); i++)
            {     h.insert(*i,1);
            }
            h.displayHeap();

            cout<<endl<<endl;

            HeapMenu();
            cout<<endl;
        }
        if(b==3)
        { Heap h;
            for(auto i=keys.begin();i!=keys.end(); i++)
            {     h.insert(*i,2);
            }
            cout<<"Vizualizare Max Heap :"<<endl;
            h.displayHeap();
            cout<<endl<<endl;
            HeapMenu();
            cout<<endl;
        }
        if(b==4){
            showMenuOption();
            cout<<endl<<endl;
            HeapMenu();

        }


    }
    while(b!=1 || b!=2 || b!=3 || b!=4);
}
void showMenuOption()
{
    int optiune=0;
    cout<<"Alege o optiune "<<endl<<endl;
    cout<<" 1. Vizualizator Binary Heap "<<endl;
    cout<<" 2. Vizualizator Red Black Tree"<<endl;
    cout<<" 3. Iesire"<<endl<<endl;
    cout<<"Alegerea ta este: ";
    do
    {
        cin>>optiune;
        if(optiune==1)
        {   Heap h;
           // Heap h(CAPACITY);
            HeapMenu();
        }
        else if(optiune==2)
        {
            RBTree* RB = new RBTree();
            startProcessing(RB);
            delete RB;
        }
        else if(optiune==3)
            exit(0);
    }
    while(optiune!=1 || optiune!=2 || optiune!=3);



}

int main()
{
    showMenuOption();
    //RBTree* RB = new RBTree();
    //startProcessing(RB);
    //delete RB;
}

void perform(RBTree*, int);

void startProcessing(RBTree* RB)
{
    int o;
    while (true)
    {
        o = IODialog::getTreeOperation();
        perform(RB, o);
    }
}

void perform(RBTree* RB, int o)
{
    list<int> nodeKeys;
    RBNode* rbn;
    int skey;
    switch (o)
    {
    case 1: // Add nodes
        IODialog::getNodeKeys(nodeKeys);
        for (list<int>::iterator it = nodeKeys.begin();
                it !=nodeKeys.end(); it++)
            RB->RBInsert(RB->createNode(*it));
        break;
    case 2: // Delete node
        skey = IODialog::getNodeKey();
        rbn = RB->search(RB->root, skey);
        if (!RB->isNil(rbn)) RB->del(rbn);
        else cout << "RB: Nodul nu a fost gasit" << endl;
        break;
    case 3: // Get minimum node
        RB->indentedDisplay();
        break;
    case 4: // Get maximum node
        delete RB;
        // cout << "Bye!" << endl;
        exit (0);
    }
    }




