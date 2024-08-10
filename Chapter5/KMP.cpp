//KMP
//洛谷P3375

#include <iostream>
#include <string>

using namespace std;

void get_next(string& s, int* next);
void get_nextval(string& s, int* nextval);
void kmp(string& s, string& pattern, int* next);

int main(){
    string s, pattern;
    cin>>s>>pattern;
    int next[pattern.length()+1], nextval[pattern.length()+1];
    get_next(pattern, next);
    get_nextval(pattern, nextval);
    kmp(s, pattern, next);
    kmp(s, pattern, nextval);
    for (int i=1;i<=pattern.length(); i++)
    {
        cout<<next[i]<<' ';
    }
    cout<<endl;
    for (int i=0;i<=pattern.length(); i++)
    {
        cout<<nextval[i]<<' ';
    }
    return 0;
}

void get_next(string& s, int* next){
    int i = 0, j = -1;
    next[0] = -1;
    while (i<s.length())
    {
        if (j==-1 || s[i]==s[j])
        {
            i ++;
            j ++;
            next[i] = j;
        }
        else j = next[j];
    }
}

void get_nextval(string& s, int* next){
    int i = 0, j = -1;
    next[0] = -1;
    while (i<s.length())
    {
        if (j==-1 || s[i]==s[j])
        {
            i ++;
            j ++;
            if (s[i]==s[j]) next[i] = next[j];
            else next[i] = j;
        }
        else j = next[j];
    }
}

void kmp(string& s, string& pattern, int* next){
    int i = 0, j = 0;
    while (i<s.length())
    {
        if (s[i]==pattern[j] || j==-1)
        {
            if (j==pattern.length()-1) //成功匹配
            {
                cout<<i-j+1<<endl;
                i++;
                j = next[j+1]; //当前字符已经成功匹配，下一轮循环时去匹配下一个字符
            }
            else
            { 
                j ++;
                i ++;
            }
        }
        else j = next[j];
    }
}