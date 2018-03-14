#include <stdio.h>
#include <windows.h>

using namespace std;

int WriteInt()
{
    char buf[10];
    int value = 0;
    while(true)
    {
        scanf("%s", buf);
        value = (atoi(buf))? atoi(buf) : 0;
        if(value > 0)
            break;
        else
            printf("Введите значение n > 0: ");
    }
    return value;
}

char** AddString(char** str, int &Size, char* buf)
{
    char** copyStr = new char*[Size + 1];
    for(int i = 0; i < Size; i++)
    {
        copyStr[i] = new char[strlen(str[i])];
        strcpy(copyStr[i], str[i]);
    }
    delete[] str;
    str = new char*[Size + 1];
    for(int i = 0; i < Size; i++)
    {
        str[i] = new char[strlen(copyStr[i])];
        strcpy(str[i], copyStr[i]);
    }
    delete[] copyStr;
    str[Size] = new char[strlen(buf)];
    strcpy(str[Size], buf);
    Size++;
    return str;
}

char** FileRead(int &Size, char fileName[], bool success = true)
{
    char** str = NULL;
    Size = 0;
    FILE* f = fopen(fileName, "r");
    if(f != NULL)
    {
        char buf[1000];
        while(!feof(f))
        {
            if(fscanf(f, "%s ", buf))
            {
                str = AddString(str, Size, (char*)buf);
            }
        }
    }
    else
    {
        printf("Ошибка чтения файла!\n");
        success = false;
    }
    fclose(f);
    return str;
}

void FileWrite(char** str, char fileName[], int Size)
{
    FILE* f = fopen(fileName, "w");
    for(int i = 0; i < Size; i++)
        fprintf(f, "%s\n", str[i]);
    fclose(f);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Size = 0;
    char** str = NULL;

    int Sizer = 0;
    char** strr = NULL;
    char glasnie[7] = "aeiuyo";

    char buf[100] = "\0";
    printf("Данная программа удаляет из файла слова содержащие N-ое количество гласных\n");
    bool run = true;
    while(run)
    {
        printf("Для начала введите файл который будет использован:\nFileName: ");
        scanf("%s", buf);
        bool suc = true;
        str = FileRead(Size, buf, suc);
        if(suc)
        {
            printf("Введите количество гласных N: ");
            int N = WriteInt();
            int glasnih = 0;
            for(int i = 0; i < Size; i++)
            {
                glasnih = 0;
                for(int j = 0; j < strlen(str[i]); j++)
                    for(int k = 0; k < 6; k++)
                        if(str[i][j] == glasnie[k])
                            glasnih++;
                if(glasnih != N)
                {
                    strr = AddString(strr, Sizer, str[i]);
                }
            }
            run = false;
        }
    }

    FileWrite(strr, "out.txt", Sizer);
    printf("В файл out.txt было записано всё, кроме слов содержащих N-ое количество гласных:\n");
    for(int i = 0; i < Sizer; i++)
        printf("%s\n", strr[i]);

    //Delete
    for(int i = 0; i < Sizer; i++)
        delete[] strr[i];
    delete[] strr;
    for(int i = 0; i < Size; i++)
        delete[] str[i];
    delete[] str;

    return 0;
}
