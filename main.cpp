#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

using namespace std;

struct MainCtx
{
    int id;
    vector<string> times;
    string txt;
};

vector<string> findTime(string src)
{
    vector<string> ret;

    size_t s = src.find(" --> ");

    if (s == string::npos)
    {
        cerr << "line = " << src << endl;

        exit(0);
    }
    assert(s != string::npos);

    ret.push_back(src.substr(0, s));

    src = src.substr(s + 5);
    ret.push_back(src);
    return ret;
}

void show(vector<MainCtx> c)
{
    printf("WEBVTT\n");
    for (int i = 0; i != c.size(); ++i)
    {
        printf("%d\n", c[i].id);

        if (i < c.size() - 1)
        {
            printf("%s --> %s\n", c[i].times[0].c_str(), c[i+1].times[0].c_str());
        }
        else
        {
            printf("%s --> %s\n", c[i].times[0].c_str(), c[i].times[1].c_str());
        }
        printf("%s\n", c[i].txt.c_str());
        printf("\n");

    }

}

int main(int argc, const char * argv[])
{

    vector<MainCtx> ctxes;

    string line;
    int start = 0;

    int st = 0;

    MainCtx ctx;

    while (getline(cin, line))
    {
        if (line == "1")
        {
            start = 1;
        }

        if (start != 1)
            continue;

        if (st == 0)
        {
            ctx.id = atoi(line.c_str());
            ++st;
            continue;
        }
        else if (st == 1)
        {
            ctx.times = findTime(line);
            ++st;
            continue;
        }
        else if (st == 2)
        {
            ctx.txt = line;
            ++st;
            ctxes.push_back(ctx);
        }
        else if (st == 3)
        {
            st = 0;
            continue;

        }

    }

    show(ctxes);
    return 0;
}
