#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include "../AsvState.h"
#include "../AsvScheme.h"
#include "AsvFile.h"
#include <dirent.h>
using namespace std;

AsvFile::AsvFile(): AsvScheme("file") {}

vector<shared_ptr<AsvEntry>> AsvFile::Load(string path) const
{
    vector<shared_ptr<AsvEntry>> x;

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (path.c_str())) != NULL) {        
      while ((ent = readdir (dir)) != NULL) {
        x.push_back(make_shared<AsvEntry>(string(ent->d_name)));
      }
      closedir(dir);
    } else {
      exit(errno);
    }

    return x;
}
