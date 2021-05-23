#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    string ori, num, tag, resp, oriC, tagC;
    int i;

    while (cin >> ori >> num) {
        bool isTag = false;
        getline(cin >> ws, tag);

        tagC = "";
        for (char j : tag)
            tagC.push_back(toupper(j));

        oriC = "";
        for (char j : ori)
            oriC.push_back(toupper(j));

        resp = "";
        i = 0;
        while (i < tag.size()) {
            if (isTag && strncmp(&tagC[i], &oriC[0], oriC.size()) == 0) {
                resp += num;
                i += (int) ori.size() - 1;
            } else {
                resp.push_back(tag[i]);

                if (tagC[i] == '<')
                    isTag = true;
                else if (tagC[i] == '>')
                    isTag = false;
            }

            i++;
        }

        cout << resp << endl;
    }

    return 0;
}