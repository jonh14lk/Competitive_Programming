#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
    string str;
    int n;
    cin >> n;
    while(n--)
    {
        bool can = true;
        cin >> str;
        if(str.size() == 1 && str == "?")
        {
            cout << "a\n";
        }
        else
        {
            for(int i = 0; i < str.size(); i++)
            {
                if(str[i] == '?')
                {
                    if(i >= 1 && i < str.size() - 1)
                    {
                        if(str[i - 1] == 'a' && str[i+1] != 'b')
                        {
                            str[i] = 'b';
                        }
                        else if(str[i-1] == 'a' && str[i+1] != 'c')
                        {
                            str[i] = 'c';
                        }
                        else if(str[i - 1] == 'b' && str[i+1] != 'a')
                        {
                            str[i] = 'a';
                        }
                        else if(str[i-1] == 'b' && str[i+1] != 'c')
                        {
                            str[i] = 'c';
                        }
                        else if(str[i - 1] == 'c' && str[i+1] != 'a')
                        {
                            str[i] = 'a';
                        }
                        else if(str[i-1] == 'c' && str[i+1] != 'b')
                        {
                            str[i] = 'b';
                        }
                        else if(str[i+1] == '?' && str[i-1] != 'a')
                        {
                            str[i] = 'b';
                        }
                        else if(str[i+1] == '?' && str[i-1] != 'b')
                        {
                            str[i] = 'c';
                        }
                        else if(str[i+1] == '?' && str[i-1] != 'c')
                        {
                            str[i] = 'a';
                        }
                    }
                    else if(i >= 1 && i == str.size() - 1)
                    {
                        if(str[i-1] == 'a')
                        {
                            str[i] = 'b';
                        }
                        else if(str[i-1] == 'b')
                        {
                            str[i] = 'c';
                        }
                        else if(str[i-1] == 'c')
                        {
                            str[i] = 'a';
                        }
                    }
                    else if(i == 0)
                    {
                        if(str[i+1] == 'a')
                        {
                            str[i] = 'b';
                        }
                        else if(str[i+1] == 'b')
                        {
                            str[i] = 'c';
                        }
                        else if(str[i+1] == 'c')
                        {
                            str[i] = 'a';
                        } 
                        else if(str[i+1] == '?')
                        {
                            str[i] = 'a';
                        }
                    }
                }
            }
            for(int i = 0; i < str.size() - 1; i++)
            {
                if(str[i] == str[i+1])
                {
                    cout << "-1\n";
                    can = false;
                    break;
                }
            }
            if(can) cout << str << endl;
        }
    }
    return 0 ;
}
