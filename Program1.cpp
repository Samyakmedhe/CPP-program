#include<iostream>
using namespace std;



bool EvenOdd(int iNo)
{
    if(iNo % 2 == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
int main()
{
    int iValue = 0 ;
    cout<<"Enter Number : ";
    cin>>iValue;

    bool bRet = false;
    bRet = EvenOdd(iValue);
    if(bRet)
    {
        cout<<iValue<<" is Even Number...\n";
    }
    else
    {
        cout<<iValue<<" is Odd Number...\n";
    }

}