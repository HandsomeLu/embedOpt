#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

void writeToFile(char *filename, char *str)
{
    FILE *fp;
    long flength;

    fp = fopen(filename, "w+");
    if (!fp)
    {
        printf("!!FILE open ERROR \n");
        return NULL;
    }

    fputs(str, fp);

    fclose(fp);
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

void otherToBlank(char *str)
{
    int count = 0;
    for (long i = 0; str[i] != '\0'; i++)
    {
        if (!(str[i] > 'a' && str[i] < 'z' || str[i] > 'A' && str[i] < 'Z' || str[i] > '0' && str[i] < '9'))
        {
            str[i] = ' ';
            count++;
        }
    }
    printf("%d ", count);
}

typedef struct HuffNode
{
    char index[11];
    char letter;
    int next[2];
} HuffNode, *HuffTree;

void makeTree()
{
    HuffTree htree;
    htree = malloc(54 * sizeof(htree));
    // 初始化所有节点
    for (int i = 0; i < 54; i++)
    {
    }
}

void initHuffmanTable(char *huffmantb[])
{
    // 分配内存
    for (int i = 0; i < 26; i++)
    {
        huffmantb[i] = (char *)malloc(11 * sizeof(char));
    }
    huffmantb[0] = "111";
    huffmantb[1] = "1011";
    huffmantb[2] = "011000";
    huffmantb[3] = "00001";
    huffmantb[4] = "01101";
    huffmantb[5] = "010";
    huffmantb[6] = "110011";
    huffmantb[7] = "011001";
    huffmantb[8] = "0010";
    huffmantb[9] = "1000";
    huffmantb[10] = "1100001011";
    huffmantb[11] = "11000011";
    huffmantb[12] = "10101";
    huffmantb[13] = "110010";
    huffmantb[14] = "0111";
    huffmantb[15] = "1001";
    huffmantb[16] = "101000";
    huffmantb[17] = "11000010101";
    huffmantb[18] = "0001";
    huffmantb[19] = "0011";
    huffmantb[20] = "1101";
    huffmantb[21] = "00000";
    huffmantb[22] = "1100000";
    huffmantb[23] = "110001";
    huffmantb[24] = "110000100";
    huffmantb[25] = "101001";
    huffmantb[26] = "11000010100";
}

void huffman_decode(unsigned char *code, int code_bits, char **M, int **N)
{
    // 按照前序遍历顺序排序huffmantb
    int preorderhuff[27];
    preorderhuff[0] = 21;
    preorderhuff[1] = 3;
    preorderhuff[2] = 18;
    preorderhuff[3] = 8;
    preorderhuff[4] = 19;
    preorderhuff[5] = 5;
    preorderhuff[6] = 2;
    preorderhuff[7] = 7;
    preorderhuff[8] = 4;
    preorderhuff[9] = 14;
    preorderhuff[10] = 9;
    preorderhuff[11] = 15;
    preorderhuff[12] = 16;
    preorderhuff[13] = 25;
    preorderhuff[14] = 12;
    preorderhuff[15] = 1;
    preorderhuff[16] = 22;
    preorderhuff[17] = 24;
    preorderhuff[18] = 26;
    preorderhuff[19] = 17;
    preorderhuff[20] = 10;
    preorderhuff[21] = 11;
    preorderhuff[22] = 23;
    preorderhuff[23] = 13;
    preorderhuff[24] = 6;
    preorderhuff[25] = 20;
    preorderhuff[26] = 0;
    preorderhuff[27] = 21;
    int i = 0;     //遍历code
    int count = 0; //遍历M
    while (code[i] != '\0')
    {
        int left = 0, right = 26;
        char *tempcode = code[i];
        while (left != right)
        {
            int len = strlen(tempcode);
            if (len == 1)
            {
                if (code[i] == '0')
                {
                    right = 8;
                    strcat(tempcode, code[i]);
                }
                else
                {
                    left = 9;
                    strcat(tempcode, code[i]);
                }
            }
            if (len == 2)
            {
                if (code[i] == '0')
                {
                    right = 4;
                    strcat(tempcode, code[i]);
                }
                else
                {
                    left = 5;
                    strcat(tempcode, code[i]);
                }
            }

            i++;
        }
        if (left == 0)
        {
            M[count] = ' ';
        }
        else
        {
            M[count] = 'a' + (left - 1);
        }
    }
}

void huffman_encode(char *M, int N, char **code, int *code_bits)
{
    char *huffmantb[27];
    initHuffmanTable(huffmantb);
    int length = N * 11;
    *code = (char *)malloc(length * sizeof(char));
    int i;
    *code[0] = NULL;
    printf("%s\n", *code);
    for (i = 0; M[i] != '\0'; i++)
    {
        if (M[i] == ' ')
        {
            strcat(*code, huffmantb[0]);
        }
        else
        {
            int order = (M[i] - 'a') + 1;
            // printf("%d %c:%d\n",i,M[i],order);
            strcat(*code, huffmantb[order]);
            // printf("%s\n",code);
        }
    }
    //    strcat(*code,"\0");
    // printf("%s\n",*code);
    int bits = strlen(*code);
    *code_bits = bits;
    // printf("%d\n",*code_bits);
}

int main()
{
    char *str;
    char *code;
    char *test;
    // test= (char*)malloc(20*sizeof(char));
    // test="sasaishda hsdka";
    int length;
    int code_bits;
    clock_t startTime, endTime;
    int nums[2];
    str = readFile("Guns of the Gods.txt", &length);
    preDealStr(str, nums);
    writeToFile("predel.txt", str);
    // otherToBlank(str);
    // printf("%s\n",str);
    printf("%d\n", length);
    printf("letter num: %d\nblank num: %d\n", nums[0], nums[1]);
    // char* huffmantb[27];
    // initHuffmanTable(huffmantb);
    // for(int i=0;i<26;i++){
    //     printf("%s\n",huffmantb[i]);
    // }
    startTime = clock(); //计时开始
    huffman_encode(str, length, &code, &code_bits);
    endTime = clock(); //计时结束
    printf("The run time is: %f ms\n", (double)(endTime - startTime));
    printf("%d\n", code_bits);
    // printf("%s\n",code);
    writeToFile("encode.txt", code);
    free(code);
    // free(str);
}
