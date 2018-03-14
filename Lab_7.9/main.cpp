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
        printf("Ошибка чтения!\n");
    }
    fclose(f);
    return str;
}

void Obrab(char**str, int Size)
{

    char** copyStr = new char*[Size];
    char** tokStr = new char*[Size];

    //Удаление первого слова в строке
    for(int i = 0; i < Size; i++)
    {
        copyStr[i] = new char[strlen(str[i])];
        strcpy(copyStr[i], str[i]);
        tokStr[i] = strchr(copyStr[i], ' ');
    }
    //Сортировка по алфавиту.
    int cur = 0;
    int* index = new int[Size];
    for(int i = 0; i < Size; i++)
        index[i] = i;
    for(int i = 0; i < Size; i++)
        for(int j = i + 1; j < Size; j++)
            if(strcmp(tokStr[i], tokStr[j]) > 0)
            {
                cur = index[i];
                index[i] = index[j];
                index[j] = cur;
            }

    //Вывод
    printf("Сортировка:\n");
    for(int i = 0; i < Size; i++)
    {
        printf("%s\n", str[index[i]]);
        delete[] copyStr[i];
        delete[] tokStr[i];
    }
    delete[] copyStr;
    delete[] tokStr;
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
