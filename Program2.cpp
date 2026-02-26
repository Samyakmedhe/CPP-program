#include<iostream>

using  namespace std;

int Factorial(int iNo)
{
    int iFact = 1 , iCnt = 1;

    while(iCnt <= iNo)
    {   
        iFact = iFact * iCnt;
        iCnt++;
    }
    return iFact;
}
int main()
{

    int iValue = 0, iRet = 0  ;
    cout<<"Enter number :  ";
    cin>>iValue;

    iRet = Factorial(iValue);
    cout<<"Factorial of "<<iValue<<" is : "<<iRet<<"\n";
    return 0 ;
}