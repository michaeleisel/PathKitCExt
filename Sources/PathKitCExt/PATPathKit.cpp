#include "PATPathKit.h"
#include <string>
#include <vector>
#include <string>
#include <dirent.h>

using namespace std;

const char **PATContentsAt(const char *path, size_t *count, void **temp) {
    vector<string> *paths = new vector<string>;
    *temp = paths;
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] == '.' && (dir->d_name[1] == '\0' || (dir->d_name[1] == '.' && dir->d_name[2] == '\0'))) {
                continue;
            }
            paths->push_back(dir->d_name);
        }
        closedir(d);
    }
    const char **components = new const char *[paths->size()];
    for (int i = 0; i < paths->size(); i++) {
        components[i] = (*paths)[i].c_str();
    }
    *count = paths->size();
    return components;
}

void PATFreePathComponents(const char **components, void *temp) {
    delete components;
    vector<string> *array = (vector<string> *)temp;
    delete array;
}

const char **PATPathComponents(const char *path, size_t *count, void **temp) {
    if (!*path) {
        *count = 0;
        return NULL;
    }
    vector<string> *strings = new vector<string>();
    size_t curPos = 0;
    size_t endPos = strlen(path);
    if (path[curPos] == '/') {
        strings->push_back("/");
    }
    while (curPos < endPos) {
        while (curPos < endPos && path[curPos] == '/') {
            curPos++;
        }
        if (curPos == endPos) {
            break;
        }
        auto curEnd = curPos;
        while (curEnd < endPos && path[curEnd] != '/') {
            curEnd++;
        }
        string str(path + curPos, curEnd - curPos);
        strings->push_back(str);
        curPos = curEnd;
    }
    if (endPos > 1 && path[endPos - 1] == '/') {
        strings->push_back("/");
    }
    const char **components = new const char *[strings->size()];
    for (int i = 0; i < strings->size(); i++) {
        components[i] = (*strings)[i].c_str();
    }
    *count = strings->size();
    return components;
}
