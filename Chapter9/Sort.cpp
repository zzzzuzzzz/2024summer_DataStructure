//排序
//洛谷P1177

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> num;

void swap(int i, int j);
void BubbleSort();
void SelectSort();
void InsertSort();
void ShellSort();
void HeapSort();
void HeapAdjust(int index, int length);
void MergeSort1(vector<int>& temp, int start, int end);
void MergeSort2();
void Merge(vector<int>& src, vector<int>& res, int start, int end, int mid);
void MergePass(vector<int>& src, vector<int>& res, int step);
void QuickSort(int start, int end);
int Partion(int low, int high);

int main(){
    cin>>n;
    num.resize(n);
    for (int i=0; i<n; i++)
        cin>>num[i];
    // BubbleSort();
    // SelectSort();
    // InsertSort();
    // ShellSort();
    // HeapSort();
    // MergeSort1(num, 0, n-1);
    // MergeSort2();
    QuickSort(0, n-1);
    for (int i=0; i<n; i++)
        cout<<num[i]<<' ';
    return 0;
}

void swap(int i, int j){
    int temp = num[i];
    num[i] = num[j];
    num[j] = temp;
}

void BubbleSort(){
    for (int i=0; i<n; i++)
    {
        for (int j=n-1; j>=i+1; j--)
        {
            if (num[j-1]>num[j])
            {
                swap(j-1, j);
            }
        }
    }
}

void SelectSort(){
    int minimum;
    for (int i=0; i<n-1; i++)
    {
        minimum = i;
        for (int j=i+1; j<n; j++)
        {
            if (num[j]<num[minimum])
            {
                minimum = j;
            }
        }
        if (minimum!=i)
        {
            swap(minimum, i);
        }
    }
}

void InsertSort(){
    for (int i=1; i<n; i++)
    {
        if (num[i]<num[i-1])
        {
            int temp = num[i];
            int j;
            for (j=i-1;j>=0 && num[j]>temp; j--)
            {
                num[j+1] = num[j];
            }
            num[j+1] = temp;
        }
    }
}

void ShellSort(){
    int increacement = n;
    do
    {
        increacement = increacement/3 + 1;
        for (int i=increacement; i<n; i++)
        {
            if (num[i]<num[i-increacement])
            {
                int temp = num[i];
                int j;
                for (j=i-increacement; j>=0 && num[j]>temp; j-=increacement)
                {
                    num[j+increacement] = num[j];
                }
                num[j+increacement] = temp;
            }
        }
    } while (increacement>1);
}

void HeapSort(){
    for (int i=n/2; i>=0; i--)
    {
        HeapAdjust(i, n);
    }
    for (int i=n-1; i>0; i--)
    {
        swap(0, i);
        HeapAdjust(0,i);
    }
}

void HeapAdjust(int index, int length){
    int temp = num[index];
    for (int i=2*index+1; i<length; i = i*2 + 1)
    {
        if (i+1<length && num[i+1]>num[i])
        {
            i ++;
        }
        if (num[i]>temp)
        {
            num[index] = num[i];
            index = i;
        }
        else break;
    }
    num[index] = temp;
}

void MergeSort1(vector<int>& temp, int start, int end){
    vector<int> temp2(n);
    if (start==end) temp[start] = num[start];
    else
    {
        int mid = (start + end) / 2;
        MergeSort1(temp2, start, mid);
        MergeSort1(temp2, mid+1, end);
        Merge(temp2, temp, start, end, mid);
    }
}

void MergeSort2(){
    vector<int> temp(n);
    int k = 1;
    while (k<n)
    {
        MergePass(num, temp, k);
        k *= 2;
        MergePass(temp, num, k);
        k *= 2;
    }
}

void Merge(vector<int>& src, vector<int>& res, int start, int end, int mid){
    int i = start, j = mid + 1, k = start;
    for (; i<=mid && j<=end; k++)
    {
        if (src[i]<src[j]) res[k] = src[i++];
        else res[k] = src[j++];
    }
    while (i<=mid)
    {
        res[k++] = src[i++];
    }
    while (j<=end)
    {
        res[k++] = src[j++];
    }
}

void MergePass(vector<int>& src, vector<int>& res, int step){
    int i;
    for (i=0; i<n-2*step+1; i+=2*step)
    {
        Merge(src, res, i, i+2*step-1, i+step-1);
    }
    if (i<n-step)
    {
        Merge(src, res, i, n-1, i+step-1);
    }
    else
    {
        while (i<n)
        {
            res[i] = src[i];
            i ++;
        }
    }
}

void QuickSort(int start, int end){
    if (start>=end) return;
    int pivot = Partion(start, end);
    QuickSort(start, pivot-1);
    QuickSort(pivot+1, end);
}

int Partion(int low, int high){
    int pivotkey = num[low];
    while (low<high)
    {
        while (low<high && pivotkey<=num[high])
        {
            high --;
        }
        num[low] = num[high];
        while (low<high && pivotkey>=num[low])
        {
            low ++;
        }
        num[high] = num[low];
    }
    num[low] = pivotkey;
    return low;
}