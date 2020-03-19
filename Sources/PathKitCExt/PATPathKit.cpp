#include "PATPathKit.h"
#include <string>
#include <vector>
#include <string>
#include <dirent.h>

using namespace std;

static inline void PATFillPathComponentsVector(vector<string> &strings, const char *path) {
    size_t curPos = 0;
    size_t endPos = strlen(path);
    if (path[curPos] == '/') {
        strings.push_back("/");
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
        strings.push_back(str);
        curPos = curEnd;
    }
    if (endPos > 1 && path[endPos - 1] == '/') {
        strings.push_back("/");
    }
}

const char **PATPathComponents(const char *path, size_t *count, void **temp) {
    if (!*path) {
        *count = 0;
        return new const char *[1];
    }
    vector<string> *strings = new vector<string>();
    PATFillPathComponentsVector(*strings, path);
    const char **components = new const char *[strings->size()];
    for (int i = 0; i < strings->size(); i++) {
        components[i] = (*strings)[i].c_str();
    }
    *count = strings->size();
    return components;
}

static inline const char *PATPathFromComponents(const vector<string> &comps) {
    if (comps.empty()) {
        return strdup(".");
    }
    int i = 0;
    int sum = 0;
    string path;
    for (const auto &comp : comps) {
        sum += comp.size() + 1;
    }
    path.reserve(sum);
    for (; i < comps.size(); i++) {
        path.append(comps[i]);
        if (i != comps.size() - 1) {
            path.append("/");
        }
    }
    if (comps.front() == "/" && comps.size() > 1) {
        return strdup(path.c_str() + 1);
    } else {
        return strdup(path.c_str());
    }
}

const char *PATAppend(const char *lhs, const char *rhs) {
    vector<string> lSlice;
    vector<string> rSlice;
    PATFillPathComponentsVector(lSlice, lhs);
    PATFillPathComponentsVector(rSlice, rhs);

    // Get rid of trailing "/" at the left side
    if (lSlice.size() > 1 && lSlice.back() == "/") {
        lSlice.pop_back();
    }

    // Advance after the first relevant "."
    lSlice.erase(remove(lSlice.begin(), lSlice.end(), "."), lSlice.end());
    rSlice.erase(remove(rSlice.begin(), rSlice.end(), "."), rSlice.end());

    // Eats up trailing components of the left and leading ".." of the right side
    while (!lSlice.empty() && lSlice.back() != ".." && !rSlice.empty() && rSlice.front() == "..") {
        if (lSlice.size() > 1 || lSlice.front() != "/") {
            // A leading "/" is never popped
            lSlice.pop_back();
        }
        rSlice.erase(rSlice.begin());
    }
    lSlice.insert(lSlice.end(), rSlice.begin(), rSlice.end());
    return PATPathFromComponents(lSlice);
}

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

__attribute__((constructor)) void asdf() {
    PATAppend("a", ".");
}
