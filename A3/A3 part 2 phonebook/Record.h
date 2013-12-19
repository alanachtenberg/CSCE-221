#include "std_lib_facilities_3.h"

class Record{

    public:
    string last;
    string first;
    int UIN;
    long phone;

    Record& operator =(const Record& r){
        last=r.last;
        first=r.first;
        UIN=r.UIN;
        phone=r.phone;

    }

    bool operator <(const Record& r){
        if (last<r.last)
            return true;
        if (last==r.last&&first<r.first)
            return true;
        if (last==r.last&&first==r.first&&UIN<r.UIN)
            return true;
        return false;
    }

};



ostream& operator <<(ostream& os, Record& r){
    os<<r.last<<", "
    <<r.first<<"\nUIN: "
    <<r.UIN<<", Phone#: "
    <<r.phone<<endl;
    return os;
}

istream& operator >>(istream& is, Record& r){
    string temp;
    getline(is,temp);
    r.last=temp;
    getline(is,temp);
    r.first=temp;
    getline(is,temp);
    r.UIN=atoi(temp.c_str());
    getline(is,temp);
    r.phone=atol(temp.c_str());
    is.ignore();
    return is;
}
