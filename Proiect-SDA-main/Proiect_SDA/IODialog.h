#ifndef IODIALOG_H_
#define IODIALOG_H_

#include <iostream>
#include <sstream>
#include <list>
#include "Heap.h"

using namespace std;


  namespace IODialog
{


void showTreeOperation()
{
    cout << " 1. Adaugare  noduri" << endl
         << " 2. Stergere noduri" << endl
         << " 3. Vizualizare arbore" << endl
         << " 4. Iesire" << endl
         << "Alege optiunea (1-4): ";
}

int getTreeOperation()
{
    int option = 0;
    while (true)
    {
        showTreeOperation();
        if (!(cin >> option))
        {
            cout << "Unknown option. Try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (option < 1 || option > 4)
        {
            cout << "Alege alta optiune." << endl;
        }
        else
        {

            cin.ignore(10000, '\n');
            break;
        }
    }
    return option;
}


void showHeapOperation()
{
    cout << " 1. Adaugare  noduri" << endl
         //<< " 2. Stergere noduri" << endl
         << " 2. Vizualizare binary heap" << endl
         << " 3. Iesire" << endl
         << "Alege optiunea (1-3): ";

}


void getNodeKeys(list<int>& nodeKeys)
{
    cout << "Nodurile: " << flush;
    int key;
    string line;
    if (getline(cin,line))
    {
        istringstream iss(line);
        while (iss >> key)
        {
            nodeKeys.push_back(key);
        }
    }
}

int getNodeKey()
{
    cout << "Nodurile: ";
    int k;
    cin >> k;
    return k;
}
}

#endif /* IODIALOG_H_ */

