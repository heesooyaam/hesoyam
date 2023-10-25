#include <iostream>
using namespace std;
void tee (std::istream& stream = std::cin)
{
    string s;
    while(stream >> s)
    {
        cout << s << std::endl;
    }
}
void echo(std::istream& stream = std::cin)
{
    string s;
    getline(stream, s);
    cout << s << endl;
}

int main()
{
    tee();
    return 0;
}