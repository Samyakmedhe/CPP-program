#include<iostream>

using namespace std;

class ReverseString 
{
    public :
        string Reverse(const string& str)
        {
            string reverse = "";

            for(int i = str.length()-1 ; i >= 0 ; i--)
            {
                reverse = reverse + str[i];
            }
            return reverse;
        }
};
int main()
{
    ReverseString Reverse;
    string input; 

    cout<<"Enter String :";
    getline(cin , input);

    string sret = Reverse.Reverse(input);
    cout << "Reversed string: " << sret << endl;


    return 0;
}