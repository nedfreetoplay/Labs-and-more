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
        {
            value = atoi(arr);
            break;
        }
        else
            printf("Введите значение n > 0: ");
    }
    return value;
}

int strSize(char* str)
{
    int i = 0;
    while(str[i] != '\0')
        i++;
    return i;
}

char** FileRead(int &Size)
{
    char** str = NULL;
    char** copyStr = NULL;
    Size = 0;
    printf("Введите название файла: ");
    char fileName[100];
    scanf("%s", fileName);
    FILE* f = fopen(fileName, "r");
    if(f != NULL)
    {
        printf("Чтение:\n");
        char buf[1000];
        while(!feof(f))
        {
            if(fscanf(f, "%s ", buf))
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
        printf("Ошибка чтения!\n");
    }
    fclose(f);
    return str;
}

void Obrab(char** str, int Size)
{
    //Сортировка по алфавиту.
    int* index1 = new int[Size];
    int SizeZ = 0;
    int* index2 = NULL;
    for(int i = 0; i < Size; i++)
        index1[i] = i;
    for(int i = 1; i < Size; i++)
        for(int j = 0; j < (Size-i); j++)
            if(strlen(str[index1[j]]) > strlen(str[index1[j+1]]))
            {
                int cur = index1[j];
                index1[j] = index1[j + 1];
                index1[j + 1] = cur;
            }
    printf("CHP1\n");
    //Слова, встречающиеся в тексте более 1 раза.
    for(int i = 0; i < Size; i++)
    {
        bool chp = false;
        for(int j = i; j < Size; j++)
            if(str[i] == str[j])
            {
                printf("%s - chp\n", str[i]);
                chp = true;
            }

        for(int j = 0; j < SizeZ; j++)
            if(str[i] == str[j])
                chp = false;
        if(chp)
        {
            int* index2Copy = new int[SizeZ + 1];
            for(int k = 0; k < SizeZ; k++)
                index2Copy[k] = index2[k];
            delete[] index2;

            index2 = new int[SizeZ + 1];
            for(int k = 0; k < SizeZ; k++)
                index2[k] = index2Copy[k];
            delete[] index2Copy;
            index2[SizeZ] = i;
            SizeZ++;
        }
    }
    //Вывод
    printf("Пять самых коротких слов:\n");
    for(int i = 0; i < 5; i++)
    {
        if(Size > i)
            printf("%s\n", str[index1[i]]);
    }
    printf("Вывод 2:\n");
    for(int i = 0; i < SizeZ; i++)
    {
        printf("%s\n", str[index2[i]]);
    }
    delete[] index1;
    delete[] index2;
    printf("\n");
}

void Output(char** str, int Size)
{
    printf("Вывод:\n");
    for(int i = 0; i < Size; i++)
    {
        printf("%s\n", str[i]);
    }
    printf("\n");
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Size = 0;
    char** str = NULL;

    bool Exit = false;
    while(!Exit)
    {
        printf("---------------\n1.Загрузка из файла\n2.Обработка данных\n3.Вывод результата на экран.\n4.Выход\n---------------\nВыбор: ");
        switch(Write_int())
        {
            case 1:
                str = FileRead(Size);
                break;
            case 2:
                Obrab(str, Size);
                break;
            case 3:
                Output(str, Size);
                break;
            case 4:
                Exit = true;
                break;
            default:
                break;
        }
    }

    //Чистка данных
    for(int i = 0; i < Size; i++)
        delete[] str[i];
    delete[] str;

    return 0;
}
