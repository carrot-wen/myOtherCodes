#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>
#define MAX_VALUE 10000
#define DATA_NUMBER 10

using namespace std;
typedef int TYPE;
typedef vector<TYPE> ARRAY;
typedef ARRAY::iterator ITERATOR;
typedef void (*sortFun)(ITERATOR ,ITERATOR);


void Swap(ITERATOR a,ITERATOR b){
    TYPE temp = *a;
    *a = *b;
    *b = temp;
}
int random(int first=0,int last=10){
    return first + (last - first)*rand()/(RAND_MAX+1);
}
void input(ARRAY& arr,int num){
    if(!arr.empty()){
        arr.clear();
    }
    while(num--){
        arr.push_back(random(0,MAX_VALUE));
    }
}
void output(ITERATOR first,ITERATOR last){
    for(ITERATOR i=first; i<last; i++){
        cout<<*i<<" ";
    }
    cout<<endl;
}
//简单插入排序
void insertSort(ITERATOR first,ITERATOR last){
    ITERATOR i,j;
    for(i=first; i<last; i++){
        TYPE k=*i;
        for(j=i-1; j>=first&&*j>k; j--){
            *(j+1)= *j;
        }
        *(j+1)=k;
    }
}

//冒泡排序
void bubbleSort(ITERATOR first,ITERATOR last){
    ITERATOR i,j;
    for(i=first; i<last; i++){
        for(j=i+1; j<last; j++){
            if(*i>*j){
                Swap(i,j);
            }
        }
    }
}

//选择排序
void selectSort(ITERATOR first,ITERATOR last){
    ITERATOR i,j,maxVal;
    for(i=first; i<last; i++){
        maxVal=i;
        for(j=i; j<last; j++){
            if(*maxVal>*j){
                maxVal=j;
            }
        }
        Swap(i,maxVal);
    }
}

//希尔排序
void shellSort(ITERATOR first,ITERATOR last){
    int gap =(last-first)/2;
    ITERATOR i,j;
    TYPE k;
    while(gap){
       for(i=first; i<last; i++){
            k = *i;
            for(j=i-gap; j>=first&&*j>k; j-=gap){
               *(j+gap) = *j;
            }
            *(j+gap) = k;
       }
       gap = gap/2;
    }

}

//快速排序
ITERATOR partition(ITERATOR first,ITERATOR last){
    TYPE val = *first;
    last--;
    while(first < last){
        while(val<=*last && first<last){
            last--;
        }
        *first = *last;
        while(val>=*first && first<last){
            first++;
        }
        *last = *first;
    }
    *first = val;
    return first;
}
void quickSort(ITERATOR first,ITERATOR last){
    if(last - first <=1){
        return ;
    }
    ITERATOR middle = partition(first,last);
    quickSort(first,middle);
    quickSort(middle+1,last);
}

//堆排序
void heapAdjust(ITERATOR root,int index,int last){
    ITERATOR maxVal = root;
    int left = index*2 + 1;
    int right = index*2 +2;
    int childIndex = index;
    if(left<last && *maxVal<*(root+left-index)){
        maxVal =root+left-index;
        childIndex =left;
    }
    if(right<last && *maxVal<*(root+right-index)){
        maxVal = root+right-index;
        childIndex =right;
    }
    if(maxVal != root){
        Swap(root,maxVal);
        heapAdjust(maxVal,childIndex,last);

    }
}
void heapBuild(ITERATOR first,ITERATOR last){
    int len = last - first;
    int index =len/2-1;
    for(auto iter=first+index; iter>=first;iter--){
        heapAdjust(iter,index--,len);
    }
}
void heapSort(ITERATOR first,ITERATOR last){
    heapBuild(first,last);
    int index = last - first -1;//iter = first + index?
    for(ITERATOR iter=last-1; iter>first; iter--){
        Swap(first,iter);
        heapAdjust(first,0,index--);
    }
}

//归并排序
void marge(ITERATOR first,ITERATOR last){
    ARRAY arr(first,last);
    ITERATOR low1 =arr.begin();
    ITERATOR high2 = arr.end();
    ITERATOR high1 = low1 + (high2 - low1)/2;
    ITERATOR low2 = high1;
    ITERATOR maxVal = low1;

    while(low1<high1 && low2<high2){
        if(*low1>*low2){
            *(first++) = *(low2++);
        } else {
            *(first++) = *(low1++);
        }
    }

    while(low1<high1){
        *(first++) = *(low1++);
    }
    while(low2<high2){
        *(first++) = *(low2++);
    }
}
void margeSort(ITERATOR first,ITERATOR last){
    int size = last - first;
    if(size<=1){
        return ;
    }
    ITERATOR middle = first + size/2;
    margeSort(first,middle);
    margeSort(middle,last);
    marge(first,last);
}

//基数排序
int maxBit(ITERATOR first,ITERATOR last){
    int maxVal = 10;
    int radix = 1;
    for(auto iter=first; iter<last; iter++){
        while(*iter>=maxVal){
            maxVal*=10;
            radix++;
        }
    }
    return radix;
}

void radixSort(ITERATOR first,ITERATOR last){
    int radix = maxBit(first,last);
    int num[10],sum[10];
    ARRAY temp(last-first);
    int pow = 1;
    for(int i=1; i<=radix; i++,pow*=10){

        for(int j=0;j<10;j++){
            num[j]=0;sum[j]=0;
        }
        for(auto iter=first; iter<last; iter++){
            int k = (*iter/pow)%10;
            num[k]++;
        }
        for(int j=1;j<10;j++){
            sum[j]=sum[j-1]+num[j-1];
        }
        for(auto iter=first; iter<last; iter++){
            int k = (*iter/pow)%10;
            temp[sum[k]++] =*iter;
        }
        for(auto iter1=first,iter2=temp.begin(); iter1<last;){
            *(iter1++) = *(iter2++);
        }
    }
}

void test(int num,sortFun fun){
    ARRAY arr;
    while(num>0){
       input(arr,DATA_NUMBER);
       output(arr.begin(),arr.end());
       fun(arr.begin(),arr.end());
       output(arr.begin(),arr.end());
       for(auto iter=arr.begin()+1; iter!=arr.end();iter++){
            if(*iter<*(iter-1)){
                cout<<"error! "<<*iter<<endl;
                num=0;
                break;
            }
       }
       num--;
    }
}
int main()
{
    srand( (unsigned)time( NULL ) );
    sortFun fun=radixSort;
    test(100,fun);
    return 0;
}
