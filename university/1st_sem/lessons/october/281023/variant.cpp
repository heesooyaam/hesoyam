#include <iostream>
#include <vector>
#include <variant>
using namespace std;
void ProcessNumbers(vector<variant<int, string, float>>& smth)
{
    int int_sum = 0;
    float float_sum = 0;
    string result_string;
    for(const auto& v : smth)
    {
        if(v.index() == 0)
        {
            int_sum += get<int>(v);
        }
        else if(v.index() == 2)
        {
            float_sum += get<float>(v);
        }
        else
        {
            result_string += get<string>(v);
        }
    }
    cout << "int_sum: " << int_sum << " float_sum: " << float_sum << " res_string: " << result_string << endl;
}
void ProcessNumbers2(vector<variant<int, string, float>>& smth)
{
    int int_sum = 0;
    float float_sum = 0;
    string result_string;
    for(const auto& v : smth)
    {
        if(auto value = get_if<int>(&v))
        {
            int_sum += *value;
        }
        else if(auto value = get_if<float>(&v))
        {
            float_sum += *value;
        }
        else
        {
            result_string += get<string>(v);
        }
        cout << "int_sum: " << int_sum << " float_sum: " << float_sum << " res_string: " << result_string << endl;
    }
}
int main()
{
    vector<variant<int, string, float>> smth = {"str", 1, 5.5f, "res"};
    ProcessNumbers(smth);
    ProcessNumbers2(smth);
}