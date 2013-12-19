
#include "question.h"



int type_option; //global option variable

void display(vector<Question> v)
{
    for (int i=0; i<v.size(); ++i)
        cout<<v[i]<<endl;
}
void display(list<Question> l)
{
    for(list<Question>::iterator i=l.begin(); i!=l.end(); ++i)
        cout<<*i<<endl;
}
int input(Question q)
{
    int answer;
    cin>>answer;
    if (cin.fail())
    {
        cout<<"oops bad input! try again\n";
        cin.clear();
        cin.ignore();
        answer=input(q);
    }
    if (answer>q.get_size()||answer<1)
    {
        cout<<"oops answer out of range! try again\n";
        answer=input(q);
    }
    return answer;

}

vector<Question> init_vector(ifstream& in)
{
    vector<Question> question_vec(15); //fifteen questions
    Question q1(in);//construct first question with special constructor for testing purposes

    for (int i=0; i<15; ++i)
    {
        question_vec[i]=q1;
        in>>q1;
    }

    return question_vec;
}
list<Question> init_list(vector<Question> v)
{
    list<Question> q_list;
    for (int i=0; i<v.size(); ++i)
        q_list.push_back(v[i]);
    return q_list;
}

void test(int n, vector<Question> v)
{
    int correct=0;
    int answer;
    cout<<"The test has 10 questions and requires 70 percent correct answers to pass\n";
    cout<<"to answer questions input the corresponding number to the correct answer\n";
    cout<<"lets begin our test!\n\n";

    for(int i=0; i<10; ++i)
    {
        cout<<" "<<i+1<<". "<<v[n]<<endl;
        if(input(v[n])==v[n].get_ans())
        {
            cout<<"correct!\n\n";
            ++correct;
        }
        else
            cout<<"sorry but you are incorrect\n\n";

        if (n==14)
            n=0;
        else ++n;
    }

    cout<<"you scored "<<correct<<"out of 10 points\n";
    if (correct<7)
        cout<<"sorry but you failed the test...\n";
    else cout<<"Congratulations you passed the test!!!\n";

}

void test(int n, list<Question> l)
{

    int correct=0;
    int answer;
    cout<<"The test has 10 questions and requires 70 percent correct answers to pass\n";
    cout<<"to answer questions input the corresponding number to the correct answer\n";
    cout<<"lets begin our test!\n\n";
    list <Question>::iterator it=l.begin();
    for(int i=0; i<10; ++i)
    {
        cout<<" "<<i+1<<". "<<*it<<endl;
        if(input(*it)==it->get_ans())
        {
            cout<<"correct!\n\n";
            ++correct;
        }
        else
            cout<<"sorry but you are incorrect\n\n";

        if (n==14)
            n=0;
        else ++n;
        ++it;
    }

    cout<<"you scored "<<correct<<"out of 10 points\n";
    if (correct<7)
        cout<<"sorry but you failed the test...\n";
    else cout<<"Congratulations you passed the test!!!\n";


}



int main()
try
{
    vector<Question> vectQuestions;
    list<Question> listQuestions;
    ifstream infile("Question.txt");    //open file and check if successful
    if (!(infile.is_open()))
        throw 1;
    cout<<"please choose between (1) list or (2) vector implementation input int\n";
    cin>>type_option;
    if (type_option>2||type_option<1)
    {
        string s="Not an option!\n";
        throw s;
    }
    vectQuestions=init_vector(infile); //initialize vector before list because list initializer uses vector
    listQuestions=init_list(vectQuestions);
    srand(type_option+10);
    int q_number=rand()%15;

    if (type_option==1)
        test(q_number,listQuestions);
    else test(q_number,vectQuestions);








    return 0;


}
catch(string& s)
{
    cout<<s;
    return 1;
}
catch(int)
{
    cout<<"error file did not open\n";
    return 2;
}
catch(...)
{

    cout<<"exception occurred!\n";
    return  3;
}
