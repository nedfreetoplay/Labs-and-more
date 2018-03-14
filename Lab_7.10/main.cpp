#include <cstdio>
#include <stdio.h>
#include <windows.h>

int Write_int()
{
    char arr[10];
    int value = 0;
    while(true)
    {
        scanf("%s", arr);
        if(atoi(arr))
            value = atoi(arr);
        if(value > 0)
            break;
        else
            printf("������� �������� n > 0: ");
    }
    return value;
}

char** FileRead(int &Size)
{
    char** str = NULL;
    char** copyStr = NULL;
    Size = 0;
    printf("������� �������� �����: ");
    char fileName[100];
    scanf("%s", fileName);
    FILE* f = fopen(fileName, "r");
    if(f != NULL)
    {
        printf("������:\n");
        char buf[1000];
        while(!feof(f))
        {
            if(fscanf(f, "%[^\n]\n", buf))
            {
                char** copyStr = new char*[Size + 1];
                for(int i = 0; i < Size; i++)
                {
                    copyStr[i] = new char[strlen(str[i])];
                    strcpy(copyStr[i], str[i]);
                    delete[] str[i];
                }
                delete[] str;
                str = new char*[Size + 1];
                for(int i = 0; i < Size; i++)
                {
                    str[i] = new char[strlen(copyStr[i])];
                    strcpy(str[i], copyStr[i]);
                    delete[] copyStr[i];
                }
                delete[] copyStr;
                str[Size] = new char[strlen(buf)];
                strcpy(str[Size], buf);
                printf("%s\n", str[Size]);
                Size++;
            }
        }
    }
    else
    {
        printf("������ ������!\n");
    }
    fclose(f);
    return str;
}

void Obrab(char**str, int Size, char glasnie[])
{
    printf("a)\n");
    for(int i = 0; i < Size; i++)
    {
        bool chp = false;

        if(strlen(str[i]) >= 2 && str[i][strlen(str[i]) - 2] == '�' && str[i][strlen(str[i]) - 1] == '�')
            chp = true;
        if(strlen(str[i]) >= 3 && str[i][strlen(str[i]) - 3] == '�' && str[i][strlen(str[i]) - 2] == '�' && str[i][strlen(str[i]) - 1] == '�')
            chp = true;
        if(chp)
            printf("%s\n", str[i]);
    }

    printf("b)\n");
    for(int i = 0; i < Size; i++)
    {
        bool chp = false;
        for(int j = 0; j < 10; j++)
            if(str[i][0] == glasnie[j])
                chp = true;
        if(chp)
            printf("%s\n", str[i]);
    }
}

void Output(char** str, int Size)
{
    printf("�����:\n");
    for(int i = 0; i < Size; i++)
    {
        printf("%s ", str[i]);
    }
    printf("\n");
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Size = 0;
    char** str = NULL;

    char glasnie[11] = "����������";

    bool RUN = true;
    while(RUN)
    {
        printf("---------------\n1.�������� �� �����\n2.��������� ������\n3.����� ���������� �� �����.\n4.�����\n---------------\n�����: ");
        switch(Write_int())
        {
            case 1:
                str = FileRead(Size);
                break;
            case 2:
            {
                Obrab(str, Size, glasnie);
                break;
            }
            case 3:
            {
                Output(str, Size);
                break;
            }
            case 4:
                RUN = false;
                break;
            default:
                break;
        }
    }

    //������ ������
    for(int i = 0; i < Size; i++)
        delete[] str[i];
    delete[] str;

    return 0;
}
