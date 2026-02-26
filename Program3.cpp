#include<iostream>
using namespace std;


int SumDigit(int iNo)
{
    int iSum = 0;
    while(iNo != 0 )
    {
        iSum += iNo % 10;
        iNo = iNo / 10;
    }   

    return iSum;
}
int main()
{
    int iValue = 0 , iRet = 0 ;

    cout<<"Enter Number : ";
    cin>>iValue;

    iRet = SumDigit(iValue);
    cout<<"Summation of "<<iValue<<" is : "<<iRet<<"\n";


    return 0;
}