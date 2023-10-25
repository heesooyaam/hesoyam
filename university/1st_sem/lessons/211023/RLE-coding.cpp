// run-length encoding
#include <iostream>
#include <string>

std::string RLE_1(std::istream& stream = std::cin)
{
    std::string s;
    stream << s;
    std::string RLEstring;
    int cnt = 1;
    bool in = false;
    for(size_t i = 0; i < s.size(); ++i)
    {
        if((i != s.size() - 1) && in && s[i] == s[i + 1])
        {
            ++cnt;
        }
        else if((i != s.size() - 1) && !in && s[i] == s[i + 1])
        {
            cnt = 2;
            in = true;
        }
        else if((i != s.size() - 1) && in && s[i] != s[i + 1])
        {
            std::string toBeAdded;
            toBeAdded += s[i];
            toBeAdded += std::to_string(cnt);
            RLEstring += toBeAdded;
            cnt = 1;
            in = false;
        }
        else if((i != s.size() - 1) && !in && s[i] != s[i + 1])
        {
            RLEstring.push_back(s[i]);
        }
        
        if(i == s.size() - 1)
        {
            if(in)
        }
    }
}

int main()
{
    return 0;
}