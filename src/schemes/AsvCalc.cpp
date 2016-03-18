#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include "../AsvState.h"
#include "../AsvScheme.h"
#include "AsvCalc.h"

using namespace std;


AsvCalc::AsvCalc(): AsvScheme("calc") {}

vector<shared_ptr<AsvEntry>> AsvCalc::Load(string path) const
{
    vector<shared_ptr<AsvEntry>> x;
    for(int i = 0; i <=9; i++) x.push_back(make_shared<AsvEntry>(to_string(9 - i)));
    return x;
}

string AsvCalc::Jump(string path, string id) const
{
    int val = 0;
    int add = 0;
    try{
        val = stoi(path);
        add = stoi(id);
    }catch (const std::invalid_argument& ia){
        return "-1";
    }

    return to_string(val + add);
}
