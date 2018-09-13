#include <iostream>
#include "List.h"
#include <random>
#include <time.h>

using namespace::std;

long distIt(int min,int max){
    return (min+(rand()<<16|rand())%max);
}

long distInd(int number){
    return ((rand()<<16|rand())%number);
}

void testComplexity(int number, int min, int max){
    List<int> test;
    test.CleanList();
    srand((unsigned int)time(NULL));
    /*random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<> distItem(min,max);
    uniform_int_distribution<> distIndex(0,number);*/

    for(int i=0;i<number;i++){
        test.AddItem(distIt(min,max));
    }
    long long d=0, ins=0, f=0;
    for(int i=0;i<number;i++){
        test.DeleteByNumber(distInd(number));
        d+=test.GetOperations();

        test.AddItemByNumber(distIt(min,max), distInd(number));
        ins+=test.GetOperations();

        test.FindItem(distIt(min,max));
        f+=test.GetOperations();
    }


    cout<<"Time complexity"<<endl;
    cout<<"Delete: "<<endl;
    cout<<"Theoretical: "<<(float)number/2<<" Practical: "<<(float)d/number<<endl;
    cout<<"Insert: "<<endl;
    cout<<"Theoretical: "<<(float)number/2<<" Practical: "<<(float)ins/number<<endl;
    cout<<"Find: "<<endl;
    cout<<"Theoretical: "<<(float)number/2<<" Practical: "<<(float)f/number<<endl;
    cout<<"------------------------------"<<endl;
    cout<<"List size: "<< test.GetSize();
}

void showMenu(){
    cout << endl;

    cout << "1. Watch list" << endl;
    cout << "2. Clear list" << endl;
    cout << "3. Empty check" << endl;
    cout << "4. Check for a presence of a value in list" << endl;
    cout << "5. Search by index" << endl;
    cout << "6. Change by index" << endl;
    cout << "7. Find by value" << endl;
    cout << "8. Add new value" << endl;
    cout << "9. Add new value by index" << endl;
    cout << "10. Delete by value" << endl;
    cout << "11. Delete by index" << endl;
    cout << "12. Iterator to first position" << endl;
    cout << "13. Change value at iterator's position" << endl;
    cout << "14. Show value at iterator's position" << endl;
    cout << "15. Shift iterator" << endl;
    cout << "16. List size" << endl;
    cout << "17. Test" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    List<int> testList;
    List<int>::Iterator iter(testList);

    showMenu();

    bool exit= false;
    int com;
    while (!exit){
        cout<<"input command:";
        cin>>com;
        cout<< endl;
        try{
            switch (com){
                case 0: exit= true;
                    break;
                default: cout << "No such command exist"<<endl;
                    break;

                case 1:{
                    if(!iter.begin())cout<<"List is empty!"<<endl;
                    else{
                        cout<<"List contains:"<<endl;
                        for(int i=0;i<testList.GetSize();i++, iter++){
                            //cout<<"Position: "<<i<<" Value: " << *iter<<endl;
                            cout<<*iter<<" ";
                        }
                        cout<<endl;
                    }
                    break;
                }

                case 2:{
                    testList.CleanList();
                    cout<<"Cleaned"<<endl;
                    break;
                }

                case 3:{
                    cout<<"List status: ";
                    (testList.isEmpty())? cout<<"empty"<<endl:cout<<"not empty"<<endl;
                    break;
                }

                case 4:{
                    int value;
                    cout<<"Input value";
                    cin>>value;
                    cout<<endl;
                    (testList.FindItem(value))? cout<<"List contains this value"<<endl:cout<<"List does not contain this value"<<endl;
                    break;
                }

                case 5:{
                    int index;
                    cout<<"Input index";
                    cin>>index;
                    cout<<endl;
                    cout<<"Position value: "<<testList.FindItemByNumber(index)<<endl;
                    break;
                }

                case 6:{
                    int ind;
                    cout<<"Input index";
                    cin>>ind;
                    cout<<endl;
                    int val;
                    cout<<"Input value";
                    cin>>val;
                    cout<<endl;
                    (testList.ChangeValue(val,ind))? cout<<"Value successfully changed"<<endl:cout<<"Can't change value"<<endl;
                    break;
                }

                case 7:{
                    int vl;
                    cout<<"Input value";
                    cin>>vl;
                    cout<<endl;
                    int posIt=testList.GetPos(vl);
                    (posIt==-1)? cout<<"List does not contain such value"<<endl:cout<<"Value position: "<<posIt<<endl;
                    break;
                }

                case 8:{
                    int val1;
                    cout<<"Input value:";
                    cin>>val1;
                    cout<<endl;
                    testList.AddItem(val1);
                    cout<<"Item added"<<endl;
                    break;
                }

                case 9:{
                    int indx;
                    cout<<"Input index";
                    cin>>indx;
                    cout<<endl;
                    int val2;
                    cout<<"Input value";
                    cin>>val2;
                    cout<<endl;
                    (testList.AddItemByNumber(val2,indx))? cout<<"Successfully added"<<endl:cout<<"Cannot add value in this position"<<endl;
                    break;
                }

                case 10:{
                    int val3;
                    cout<<"Input value";
                    cin>>val3;
                    cout<<endl;
                    (testList.DeleteByValue(val3))? cout<<"Successfully deleted"<<endl:cout<<"Cannot delete"<<endl;
                    break;
                }

                case 11:{
                    int indx1;
                    cout<<"Input index";
                    cin>>indx1;
                    cout<<endl;
                    (testList.DeleteByNumber(indx1))? cout<<"Successfully deleted"<<endl:cout<<"Cannot delete"<<endl;
                    break;
                }

                case 12:{
                    (iter.begin())? cout<<"Iterator successfully moved at beginning of list"<<endl:cout<<"Empty list"<<endl;
                    break;
                }

                case 13:{
                    int newVal;
                    cout<<"Input value";
                    cin>>newVal;
                    cout<<endl;
                    *iter=newVal;
                    break;
                }

                case 14:{
                    cout<<"Current value at iterator's position: "<<*iter<<endl;
                    break;
                }

                case 15:{
                    //(iter++)? cout<<"Iterator moved to next element"<<endl:cout<<"List is empty"<<endl;
                    cout<<iter++<<endl;
                    break;
                }

                case 16:{
                    cout<<"List size: "<<testList.GetSize()<<endl;
                    break;
                }

                case 17:{
                    int number, min, max;
                    cout<<"Input list length: ";
                    cin>>number;
                    cout<<endl;
                    cout<<"Input minimum value: ";
                    cin>>min;
                    cout<<endl;
                    cout<<"Input maximum value: ";
                    cin>>max;
                    cout<<endl;
                    testComplexity(number,min,max);
                    break;
                }
            }
        }catch (int code){
            cout<<"Error: ";
            switch (code){
                case INVALID_INDEX: cout<<"invalid index"<<endl;
                    break;
                case EMPTY_LIST: cout<<"List is empty"<<endl;
                    break;
                case ITERATOR_END: cout<<"Iterator is out of list"<<endl;
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}