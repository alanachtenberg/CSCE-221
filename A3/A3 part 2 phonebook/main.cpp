#include "std_lib_facilities_3.h"
#include "Record.h"
#include "TemplateDoublyLinkedList.h"
void display(vector<DoublyLinkedList<Record>> & v)
{
    for (int i=0; i<v.size(); ++i)
    {
        cout<<"LIST:"<<i<<"\n"<<v[i];
        cout<<endl<<endl;
    }
}

void insert_record(vector<DoublyLinkedList<Record>>& v, Record r)
{
    char temp='0';
    stringstream ss;
    ss<<r.last;
    ss>>temp; //get first letter
    int index=temp-65;//shift index for ascill
    if (index<0)
    {
        cout<<"ksdafksdf\n";
        throw "range error, check capital letter on name input";
    }
    v[index].insert(r); //insert into sorted list
}

Record* search_pb(vector<DoublyLinkedList<Record>>& v, Record r)
{
    Record* result= new Record;
    char temp='0';
    stringstream ss;
    ss<<r.last;
    ss>>temp; //get first letter
    int index=temp-65;//shift index for ascill
    if (index<0)
    {
        throw "range error, check capital letter on name input";
    }
    DoublyLinkedList<Record> temp_list1,temp_list2; //create two temp lists to narrow down into a new list

    DListNode<Record>* it=v[index].getFirst();
    int counter=0;

    while(it!=v[index].getAfterLast())
    {
        if (it->getElem().last==r.last)
        {
            *result=it->getElem();
            temp_list1.insert(*result);
            ++counter;
        }
        it=it->getNext();
    }
    if (counter==0)
        return NULL;
    if (counter==1)
        return result;
    cout<<"sorry there are "<<counter<<" people that have the last name "
        <<r.last<<"\nplease input their first name, first letter must be CAPS\n";
    cin>>r.first;
    counter=0;

    it=temp_list1.getFirst();
    while(it!=temp_list1.getAfterLast())
    {
        if (it->getElem().first==r.first)
        {
            *result=it->getElem();
            temp_list2.insert(*result);
            ++counter;
        }
        it=it->getNext();
    }
    if (counter==0)
        return NULL;
    if (counter==1)
        return result;
    cout<<"sorry there are "<<counter<<" people that have the last name "
        <<r.last<<" and the first name "<<r.first<<"\nplease input their UIN\n";
    cin>>r.first;
    counter=0;

    it=temp_list2.getFirst();
    while(it!=temp_list2.getAfterLast())
    {
        if (it->getElem().UIN==r.UIN)
        {
            *result=it->getElem();
            ++counter;
        }
        it=it->getNext();
    }
    if (counter==0)
        return NULL;
    if (counter==1)
        return result;

    return  result;
}

int main()
try

{

    Record temp;
    vector<DoublyLinkedList<Record>> PhoneBook (26);
    ifstream in("phonebook.txt");
    if(!in.is_open())
        throw 1;

    while (!in.eof())
    {
        in>>temp;
        insert_record(PhoneBook, temp);
    }
    display(PhoneBook);

    string name;
    cout<<"please input last name to search, first letter must be CAPS\n";
    cin>>name;
    Record input;
    input.last=name;
    Record* result=search_pb(PhoneBook,input);
    if (result==NULL)
        cout<<"sorry match not found in phonebook\n";
    else
        cout<<"match found!:\n"<<*result;
    in.close();

    if (cin.fail())
        throw 2;
    return 0;

}

catch(int & e)
{
    if (e==1)
        cout<<"error could not open file\n";
    if (e==2)
        cout<<"error input fail, check UIN for correct input\n";
    if(e!=1||e!=2)
        cout<<"int exception, error unknown\n";
}
catch(string & s)
{
    cout<<s;
}

catch(...)
{

    cout<<"range error on vector check capital letter on name input\n";
}
