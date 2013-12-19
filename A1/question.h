#include "std_lib_facilities_3.h"



class Question
{
    int ans;
    int size;
    string quest;
    vector<string> q_vec;

public:

    Question():ans(0),size(0),q_vec() {} //default constructor

    Question(ifstream& in)  //useful constructor like input operator but can access members directly
    {
        string temp;
        in.ignore(50,'.');
        in.ignore(1);//ignore leading white space
        getline(in,quest);
        in>>size;
        in.ignore();
        for (int i=0; i<size; ++i)
        {
            getline(in,temp);
            q_vec.push_back(temp);
        }
        in>>ans;
    }

    Question(const Question& q)  //copy constructor
    {
        ans=q.ans;
        size=q.size;
        quest=q.quest;
        q_vec=q.q_vec;
    }
    Question& operator =(Question& q)
    {
        //useful constructor like input operator but can access members directly
        ans=q.get_ans();
        size=q.get_size();
        quest=q.get_quest();
        q_vec=q.get_vec();
    }


    int get_ans()
    {
        return ans;
    }
    int get_size()
    {
        return size;
    }
    string get_quest()
    {
        return quest;
    }
    vector<string> get_vec()
    {
        return q_vec;
    }
    void set_ans(int n)
    {
        ans=n;
    }
    void set_size(int n)
    {
        size=n;
    }
    void set_quest(string s)
    {
        quest=s;
    }
    void set_vec(vector<string> v)
    {
        q_vec=v;
    }

};



ostream& operator<< (ostream& os, Question& q)
{
    vector<string> temp=q.get_vec();
    os<<q.get_quest()<<endl;
    for (int i=0; i<q.get_size(); ++i)
        os<<i+1<<": "<<temp[i]<<endl;
    return os;
}

istream& operator>> (istream& is, Question& q)
{
    vector<string> temp_vec; //declare temporary variables
    string temp;
    int sz=0;
    int answer=0;

    is.ignore(50,'.');
    is.ignore(1);//ignore leading white space
    getline(is,temp);
    q.set_quest(temp);
    is>>sz;
    q.set_size(sz);
    is.ignore();
    for (int i=0; i<sz; ++i)
    {
        getline(is,temp);
        temp_vec.push_back(temp);
    }
    q.set_vec(temp_vec);
    is>>answer;
    q.set_ans(answer);
    return is;
}

bool operator==(Question& q1,Question& q2)
{
    if((q1.get_quest()==q2.get_quest())&&(q1.get_vec()==q2.get_vec()))
        return 1;
    else return 0;
}

