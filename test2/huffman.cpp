#include <iostream>
#include <cstring>
#include <time.h>
using namespace std;

#define MAX 999999999
typedef struct
{
    int weight;
    char value;
    int parent;
    int lchild;
    int rchild;
} HTNode, *HuffmanTree; //动态分配数组存储霍夫曼树
typedef struct
{
    char *HfmCode; //动态分配数组，存储哈夫曼编码
    char value;
} code, *HuffmanCode;

//选择最小权重的两个树
void select(HuffmanTree &ht, int n, int *s1, int *s2)
{
    /*ht,为树所在数组的头指针,n为允许查找的最大序号,s1,s2,返回最小的两个序号*/
    int p1 = MAX;
    int p2 = MAX; /*p1, p2用来记录最小的两个权, 要求p1<p2*/
    int pn1 = 0;
    int pn2 = 0; /*pn1, pn2 用来记录这两个权的序号*/
    int i;
    for (i = 1; i <= n; i++)
    {
        if (ht[i].weight < p1 && ht[i].parent == 0) //ht[i].parent=0的作用是去掉已经选过的节点
        {
            pn2 = pn1;
            p2 = p1;
            pn1 = i;
            p1 = ht[i].weight;
        }
        else if (ht[i].weight < p2 && ht[i].parent == 0)
        {
            pn2 = i;
            p2 = ht[i].weight;
        }
    }
    *s1 = pn1; //赋值返回
    *s2 = pn2;
}

//创建霍夫曼树
void Creat_HuffmanTree(HuffmanTree &ht, int *w, char *st, int n)
{
    int m = 2 * n - 1;
    ht = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); //0号单元不用
    HuffmanTree p;
    int i;
    w = w + 1; //因为w[]的0号单元没有用
    st = st + 1;
    for (p = ht + 1, i = 1; i <= n; i++, p++, w++, st++) //1-n号放叶子结点，初始化
    {
        (*p).weight = *w;
        (*p).value = *st;
        (*p).parent = 0;
        (*p).lchild = 0;
        (*p).rchild = 0;
    }
    for (; i <= m; i++, p++) //非叶子结点初始化
    {
        (*p).weight = 0;
        (*p).parent = 0;
        (*p).lchild = 0;
        (*p).rchild = 0;
    }

    int s1, s2;                  //在select函数中使用,用来存储最小权的结点的序号
    for (i = n + 1; i <= m; ++i) //创建非叶子结点,建哈夫曼树
    {
        //在ht[1]~ht[i-1]的范围内选择两个parent为0且weight最小的结点，其序号分别赋值给s1、s2返回
        select(ht, i - 1, &s1, &s2);
        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].lchild = s1;
        ht[i].rchild = s2;
        ht[i].weight = ht[s1].weight + ht[s2].weight;
    }
} //哈夫曼树建立完毕

//输出所有节点权重
void outputHuffman(HuffmanTree &ht, int m)
{
    for (int i = 1; i <= m; i++)
        cout << ht[i].weight << " ";
}

//从叶子结点到根，逆向求每个叶子结点对应的哈夫曼编码
void Creat_HuffmanCode(HuffmanTree &ht, HuffmanCode &hc, int n)
{
    char *cd;
    int start;
    int c; //c指向当前节点
    int p; //p指向当前节点的双亲结点
    int i;

    hc = (HuffmanCode)malloc((n + 1) * sizeof(code)); //分配n个编码的头指针
    cd = (char *)malloc(n * sizeof(char));            //分配求当前编码的工作空间
    cd[n - 1] = '\0';                                 //从右向左逐位存放编码，首先存放编码结束符
    for (i = 1; i <= n; i++)                          //求n个叶子结点对应的哈夫曼编码
    {
        hc[i].value = ht[i].value;
        start = n - 1;                                                 //初始化编码起始指针
        for (c = i, p = ht[i].parent; p != 0; c = p, p = ht[p].parent) //从叶子到根结点求编码
        {
            if (ht[p].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            // cout << cd << endl;
        }
        hc[i].HfmCode = (char *)malloc(n * sizeof(char)); //为第i个编码分配空间
        strcpy(hc[i].HfmCode, &cd[start]);
    }
    free(cd);
}

//解码
void Decoding_HuffmanTree(HuffmanTree &ht, char code[], char result[])
{
    int i, k = 0;
    int p = 0, root;
    // 寻找根节点
    for (root = 1; ht[root].parent != 0; root = ht[root].parent); //root是霍夫曼树的根
    for (i = 0, p = root; code[i] != '\0'; i++)
    {
        if (code[i] == '0'){
            p = ht[p].lchild;
            // cout<<code[i];
        }
        else{
            p = ht[p].rchild;
            // cout<<code[i];
        }
        if (ht[p].lchild == NULL && ht[p].rchild == NULL)
        {
            // cout<<code[i]<<endl;
            result[k++] = ht[p].value;
            // cout<<ht[p].value<<endl;
            p = root;
        }
    }
    result[k] = '\0';
}

void preDealStr(char *str, int nums[])
{
    int letNum, blankNum = 0;
    for (long i = 0; str[i] != '\0'; i++)
    {
        if ('A' <= str[i] && str[i] <= 'Z')
        {
            // 大写字母
            str[i] = str[i] + 32;
            letNum++;
            // printf("%d ",letNum);
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            // 小写字母
            letNum++;
            // printf("%d ",letNum);
        }
        // else if(str[i]>'0'&&str[i]<'9'){
        //     //数字
        // }
        else
        {
            // 其他字符
            str[i] = ' ';
            blankNum++;
            // printf("%d ",blankNum);
        }
    }
    nums[0] = letNum;
    nums[1] = blankNum;
}

char *readFile(char *filename, int *length)
{
    FILE *fp;
    char *str;
    long flength;

    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("!!FILE open ERROR \n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    flength = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    *length = flength;
    str = (char *)malloc(flength * sizeof(char));
    // assert(str!=NULL);

    fread(str, flength, 1, fp);
    // printf("%s\n",str);
    fclose(fp);

    return str;
}

void huffman_encode(char *M, int N, char **code, int *code_bits, HuffmanCode &HC)
{
    int length = N * 11;
    *code = (char *)malloc(length * sizeof(char));
    int i;
    *code[0] = NULL;
    printf("%s\n", *code);
    for (i = 0; M[i] != '\0'; i++)
    {
        if (M[i] == ' ')
        {
            // cout<<M[i]<<"  "<<HC[1].HfmCode<<endl;
            strcat(*code, HC[1].HfmCode);
        }
        else
        {
            int order = (M[i] - 'a') + 2;
            // cout<<M[i]<<"  "<<HC[order].HfmCode<<endl;
            strcat(*code, HC[order].HfmCode);
        }
    }
    //    strcat(*code,"\0");
    // printf("%s\n",*code);
    int bits = strlen(*code);
    *code_bits = bits;
    // printf("%d\n",*code_bits);
}

void writeToFile(char *filename, char *str)
{
    FILE *fp;
    long flength;

    fp = fopen(filename, "w+");
    if (!fp)
    {
        printf("!!FILE open ERROR \n");
    }

    fputs(str, fp);

    fclose(fp);
}

int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int *w;   //动态数组，存放各字符的权重
    char *st; //字符串，存放节点的值
    int i, n; //n is the number of elements
    int m;

    // cout<<"input the total number of the Huffman Tree:"<<endl;
    // cin>>n;
    n = 27;

    w = (int *)malloc((n + 1) * sizeof(int));    //0号单元不用
    st = (char *)malloc((n + 1) * sizeof(char)); //0号单元不用

    // FILE *fin=fopen("哈弗曼编码.txt","r");
    // for(i=1;i<=n;i++)
    // {
    //     fscanf(fin,"%c%d",&st[i],&w[i]);
    // }

    //初始化字符串
    st[1] = ' ';
    for (int i = 2; i <= n; i++)
    {
        st[i] = 'a' + (i - 2);
    }
    printf("%s\n", st);

    //初始化w
    w[1] = 67962112;
    w[2] = 24373121;
    w[3] = 4762938;
    w[4] = 8982417;
    w[5] = 10805580;
    w[6] = 37907119;
    w[7] = 7486889;
    w[8] = 5143059;
    w[9] = 18058207;
    w[10] = 21820970;
    w[11] = 474021;
    w[12] = 1720909;
    w[13] = 11730498;
    w[14] = 7391336;
    w[15] = 21402466;
    w[16] = 23215532;
    w[17] = 5719422;
    w[18] = 297237;
    w[19] = 17897352;
    w[20] = 19059775;
    w[21] = 28691274;
    w[22] = 8022379;
    w[23] = 2835696;
    w[24] = 6505294;
    w[25] = 562732;
    w[26] = 5910495;
    w[27] = 93172;

    Creat_HuffmanTree(HT, w, st, n); /*构造H树*/

    m = 2 * n - 1;
    outputHuffman(HT, m); /*显示H树*/
    cout << endl;

    Creat_HuffmanCode(HT, HC, n); /*根据H树,求每个字符的编码,放在HC中*/
    for(i=1;i<=n;i++)        /*输出编码*/
        cout<<HC[i].value<<"  "<<HC[i].HfmCode<<endl;

    char* code;
    char* str;
    int nums[2];
    int length,code_bits;
    str = readFile("Guns of the Gods.txt", &length);
    preDealStr(str, nums);
    // char* test="sasaishda hsdka";
    huffman_encode(str,length,&code,&code_bits,HC);
    // cout<<code<<endl;
    writeToFile("encode.txt", code);

    
    //解码
    // char *code="01101110101010001110110110011100";
    char *result;
    result=(char *)malloc((length+5)*sizeof(char));
    clock_t startTime, endTime;
    startTime = clock(); //计时开始
    Decoding_HuffmanTree(HT,code,result);    //result[]存放解码结果
    endTime = clock(); //计时结束
    // cout<<"result: "<<result<<endl;
    cout<<"The run time is: "<<(double)(endTime - startTime)<<" ms"<<endl;
    writeToFile("decode.txt", result);
    // for(i=0;result[i];i++)
    //     cout<<result[i]<<"  ";
    free(code);
    free(result);
    // free(str);
    return 0;
}