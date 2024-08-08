//中缀表达式转后缀表达式
//洛谷P1175

#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

string get_RPN(string s);
void compute(string s);
int get_top(stack<int>& nums);

int main(){
    string s;
    cin>>s;
    string RPN = get_RPN(s);
    compute(RPN);
    return 0;
}

string get_RPN(string s){
    string res = "";
    stack<char> symbol; //记录运算符号
    for (char c : s)
    {
        // cout<<"Current Character: "<<c<<endl;
        // cout<<"Res: "<<res<<endl;
        if (c>='0' && c<='9')
        {
            res += c;
            res += ' ';
        }
        if (c=='(' || c=='^')
        {
            symbol.push(c);
        }
        if (c==')')
        {
            while (symbol.top()!='(')
            {
                res += symbol.top();
                res += ' ';
                symbol.pop();
            }
            symbol.pop();
        }
        if (c=='+' || c=='-')
        {
            if (!symbol.empty())
            {
                while (!symbol.empty() && symbol.top()!='(')
                {
                    res += symbol.top();
                    res += ' ';
                    if (symbol.empty())
                    {
                        break;
                    }
                    symbol.pop();
                }
            }
            symbol.push(c);
        }
        if (c=='*' || c=='/')
        {
            if (!symbol.empty())
            {
                char x = symbol.top();
                while (x=='*' || x=='/' || x=='^')
                {
                    res += x;
                    res += ' ';
                    symbol.pop();
                    if (symbol.empty())
                    {
                        break;
                    }
                    x = symbol.top();
                }
            }
            symbol.push(c);
        }
    }
    //最后将栈清空
    while (!symbol.empty())
    {
        res += symbol.top();
        res += ' ';
        symbol.pop();
    }
    return res;
}

void compute(string s){
    cout<<s<<endl;
    stack<int> nums;
    int num = 0; //记录当前操作数
    bool is_negative = false;
    for (int i=0; i<s.length(); i++)
    {
        if (s[i]>='0' && s[i]<='9')
        {
            num = num * 10 + s[i] - '0';
        }
        //判断是否为负数
        else if (s[i]=='-' && s[i+1]>='0' && s[i+1]<='9')
        {
            is_negative = true;
        }
        else if (s[i]==' ')
        {
            if (is_negative)
            {
                num *= -1;
            }
            nums.push(num);
            num = 0;
            is_negative = false;
        }
        else
        {
            if (s[i]=='+')
            {
                nums.push(get_top(nums) + get_top(nums));
            }
            if (s[i]=='-')
            {
                int x, y;
                x = get_top(nums);
                y = get_top(nums);
                nums.push(y - x);
            }
            if (s[i]=='*')
            {
                nums.push(get_top(nums) * get_top(nums));
            }
            if (s[i]=='/')
            {
                int x, y;
                x = get_top(nums);
                y = get_top(nums);
                nums.push(y / x);
            }
            if (s[i]=='^')
            {
                int x, y;
                x = get_top(nums);
                y = get_top(nums);
                nums.push(pow(y, x));
            }
            //将字符串s中参与运算的两个操作数和一个运算符替换为运算的结果得到新的字符串
            int cnt = 0;
            for (int j=i; j>=0; j--)
            {
                if (s[j]==' ')
                {
                    cnt ++;
                    if (cnt==3)
                    {
                        s.replace(j+1, i-j, to_string(nums.top()));
                        break;
                    }
                }
            }
            if (cnt<3)
            {
                s.replace(0, i+1, to_string(nums.top()));
            }
            compute(s);
            break;
        }
    }
    return;
}

int get_top(stack<int>& nums){
    int temp = nums.top();
    nums.pop();
    return temp;
}