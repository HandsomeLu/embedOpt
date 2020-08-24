#include <iostream>
#include <string>
#include <cstring>
#include <stack>
using namespace std;

const int maxw = 99999999;

class HuffNode
{
public:
    int weight;
    int parent;
    int leftchild;
    int rightchile;
};

class HuffMan
{
private:
    void MakeTree()
    {
        int i, s1, s2;
        for (i = lnum + 1; i <= len; i++)
        {
            SelectMin(i - 1, &s1, &s2);
            hufftree[s1].parent = i;
            hufftree[s2].parent = i;
            hufftree[i].leftchild = s1;
            hufftree[i].rightchile = s2;
            hufftree[i].weight = hufftree[s1].weight + hufftree[s2].weight;
        }
    }
    void SelectMin(int pos, int *s1, int *s2)
    {
        int w1, w2, i;
        w1 = w2 = maxw;
        *s1 = *s2 = 0;
        for (i = 1; i <= pos; i++)
        {
            if (hufftree[i].weight < w1 && hufftree[i].parent == 0)
            {
                *s2 = *s1;
                w2 = w1;
                w1 = hufftree[i].weight;
                *s1 = i;
            }
            else if (hufftree[i].weight < w2 && hufftree[i].parent == 0)
            {
                w2 = hufftree[i].weight;
                *s2 = i;
            }
        }
    }

public:
    int len;
    int lnum;
    HuffNode *hufftree;
    string *huffCode;
    char *message;
    void MakeTree(int n, int wt[], char c[])
    {
        int i;
        lnum = n;
        len = 2 * n - 1;
        hufftree = new HuffNode[2 * n];
        huffCode = new string[lnum + 1];
        message = new char[lnum + 1];
        for (i = 1; i <= n; i++)
            hufftree[i].weight = wt[i - 1];
        for (i = 1; i <= n; i++)
            message[i] = c[i - 1];
        for (i = 1; i <= len; i++)
        {
            if (i > n)
                hufftree[i].weight = 0;
            hufftree[i].parent = 0;
            hufftree[i].leftchild = 0;
            hufftree[i].rightchile = 0;
        }
        MakeTree();
    }
    void Coiding()
    {
        char *cd = new char[lnum];
        int i, c, f, start;
        cd[lnum - 1] = '\0';
        for (i = 1; i <= lnum; i++)
        {
            start = lnum - 1;
            for (c = i, f = hufftree[i].parent; f != 0; c = f, f = hufftree[f].parent)
            {
                if (hufftree[f].leftchild == c)
                    cd[--start] = '0';
                else
                    cd[--start] = '1';
            }
            huffCode[i].assign(&cd[start]);
        }
    }
    void Destory()
    {
        len = 0;
        lnum = 0;
        delete[] hufftree;
        delete[] huffCode;
    }
    int Decode(const string codestr, string &teststr)
    {
        int i, k, c;
        char ch;
        c = len;
        k = 0;
        string a = "";
        for (i = 0; i < codestr.length(); i++)
        {
            ch = codestr[i];
            a += ch;
            if (ch == '0')
                c = hufftree[c].leftchild;
            else if (ch == '1')
                c = hufftree[c].rightchile;
            else
                return 0;
            if (hufftree[c].leftchild == 0 && hufftree[c].rightchile == 0)
            {
                for (int j = 1; j <= lnum; j++)
                    if (hufftree[c].weight == hufftree[j].weight && a == huffCode[j])
                        teststr += message[j];
                c = len;
                a = "";
            }
            else
                ch = '\0';
        }
        if (ch == '\0')
            return 0;
        return 1;
    }
};

int main()
{
    int n, i, j;
    int wt[800];
    char c[800];
    string teststr = "";
    string codestr;
    HuffMan huff;
    n = 27;
    // cin >> n;
    // for (i = 0; i < n; i++) cin >> c[i];
    // for (i = 0; i < n; i++) cin >> wt[i];
    //初始化字符串
    c[0] = ' ';
    for (int i = 1; i < n; i++)
    {
        c[i] = 'a' + (i - 1);
    }

    //初始化w
    wt[0] = 67962112;
    wt[1] = 24373121;
    wt[2] = 4762938;
    wt[3] = 8982417;
    wt[4] = 10805580;
    wt[5] = 37907119;
    wt[6] = 7486889;
    wt[7] = 5143059;
    wt[8] = 18058207;
    wt[9] = 21820970;
    wt[10] = 474021;
    wt[11] = 1720909;
    wt[12] = 11730498;
    wt[13] = 7391336;
    wt[14] = 21402466;
    wt[15] = 23215532;
    wt[16] = 5719422;
    wt[17] = 297237;
    wt[18] = 17897352;
    wt[19] = 19059775;
    wt[20] = 28691274;
    wt[21] = 8022379;
    wt[22] = 2835696;
    wt[24] = 562732;
    wt[25] = 5910495;
    wt[26] = 93172;

    huff.MakeTree(n, wt, c);
    huff.Coiding();
    for (i = 1; i <= n; i++)
    {
        cout << c[i - 1] << " :" << huff.huffCode[i] << endl;
    }
    // cin >> codestr;
    // for (i = 0; i < codestr.length(); i++)
    // {
    // 	for (j = 1; j <= n; j++)
    // 		if (codestr[i] == c[j - 1]) cout << huff.huffCode[j];
    // }
    // cout << endl;
    // cin >> codestr;
    // if (huff.Decode(codestr, teststr)) cout << teststr << endl;
    // else cout << "error!" << endl;
    teststr = "";
    huff.Destory();
    return 0;
}