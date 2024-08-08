//计算逆波兰表达式结果
//洛谷P1449

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int get_top(stack<int>& nums);

int main(){
    string s;
    cin>>s;
    int num = 0; //记录当前操作数
    stack<int> nums;
    for (char c : s)
    {
        if (c>='0' && c<='9')
        {
            num = num * 10 + c - '0';
        }
        if (c=='.')
        {
            nums.push(num);
            num = 0;
        }
        if (c=='+')
        {
            nums.push(get_top(nums) + get_top(nums));
        }
        if (c=='-')
        {
            int x, y;
            x = get_top(nums);
            y = get_top(nums);
            nums.push(y - x);
        }
        if (c=='*')
        {
            nums.push(get_top(nums) * get_top(nums));
        }
        if (c=='/')
        {
            int x, y;
            x = get_top(nums);
            y = get_top(nums);
            nums.push(y / x);
        }
        if (c=='@')
        {
            cout<<get_top(nums)<<endl;
            break;
        }
    }
    return 0;
}

int get_top(stack<int>& nums){
    int temp = nums.top();
    nums.pop();
    return temp;
}