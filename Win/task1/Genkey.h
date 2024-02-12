#include<bits/stdc++.h>
using namespace std;
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count())
randomize;
string CreateKey()
{
    string s;
    for(int i=0;i<=15;i++)
    {
        int type=mt()%2;
        if(!type)
        {
            int value=mt()%10;
            s+=(char)(value+'0');
        }
        else
        {
            int value=mt()%('z'-'a');
            s+=((char)value+'a');
        }
    }
    return s;
}
string GenIV()
{
    string s;
    for(int i=0;i<=15;i++)
    {
        int type=mt()%2;
        if(!type)
        {
            int value=mt()%10;
            s+=(char)(value+'0');
        }
        else
        {
            int value=mt()%('z'-'a');
            s+=((char)value+'a');
        }
    }
    return s;
}
