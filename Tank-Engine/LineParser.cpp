#include "LineParser.h"
#include<vector>

LineParser::LineParser() {}
LineParser::~LineParser() {}

vector<double> LineParser::readValues(string command)
{
    istringstream is(command);
    string str;
    bool is_first_word = true;
    vector<double> values;
    while (is >> str)
    {
        if (is_first_word)
        {
            is_first_word = false;
            continue;
        }
        values.push_back(stod(str));
    }
    return values;
}