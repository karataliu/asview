#include "AsvConfig.h"
#include "AsvLoader.h"
#include "AsvWin.h"

unique_ptr<AsvLoader> GetLoader()
{
    unique_ptr<AsvLoader> loader(new AsvLoader());
    return loader;
}

class AsvCalc : public AsvProtocol
{
public:
    AsvCalc() : AsvProtocol("calc") {}

    vector<shared_ptr<AsvEntry>> Load(string path){
        vector<shared_ptr<AsvEntry>> x;
        for(int i = 0; i <=9; i++) x.push_back(make_shared<AsvEntry>(to_string(9 - i)));
        return x;
    }

    string Jump(string path, string id)
    {
        int val = 0;
        int add = 0;
        try{
            val = stoi(path);
            add = stoi(id);
        }catch (const invalid_argument& ia){
            return "-1";
        }

        return to_string(val + add);
    }

};


int main()
{
    auto loader = GetLoader();
    auto calc = new AsvCalc();
    loader->AddProtocol(calc);

    AsvWin win(loader.get());
    win.Start("calc://0");

    return 0;
}
