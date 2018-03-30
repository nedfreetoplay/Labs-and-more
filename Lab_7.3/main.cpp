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

int MyToLower( char r)
{
     switch (r)
     {
         case 'А': r = 'а'; break;
         case 'Б': r = 'б'; break;
         case 'В': r = 'в'; break;
         case 'Г': r = 'г'; break;
         case 'Д': r = 'д'; break;
         case 'Е': r = 'е'; break;
         case 'Ё': r = 'ё'; break;
         case 'Ж': r = 'ж'; break;
         case 'З': r = 'з'; break;
         case 'И': r = 'и'; break;
         case 'Й': r = 'й'; break;
         case 'К': r = 'к'; break;
         case 'Л': r = 'л'; break;
         case 'М': r = 'м'; break;
         case 'Н': r = 'н'; break;
         case 'О': r = 'о'; break;
         case 'П': r = 'п'; break;
         case 'Р': r = 'р'; break;
         case 'С': r = 'с'; break;
         case 'Т': r = 'т'; break;
         case 'У': r = 'у'; break;
         case 'Ф': r = 'ф'; break;
         case 'Х': r = 'х'; break;
         case 'Ц': r = 'ц'; break;
         case 'Ч': r = 'ч'; break;
         case 'Ш': r = 'ш'; break;
         case 'Щ': r = 'щ'; break;
         case 'Ъ': r = 'ъ'; break;
         case 'Ы': r = 'ы'; break;
         case 'Ь': r = 'ь'; break;
         case 'Э': r = 'э'; break;
         case 'Ю': r = 'ю'; break;
         case 'Я': r = 'я'; break;
     }
     return (r);
}

void Obrab(char** str, int Size)
{
    char glasnie[]("аоуыэяёюие");
    char soglasnie[]("бвгджзйклмнпрстфхцчшщ");
    printf("Вывод:\nС заглавной:\n");
    for(int i = 0; i < Size; i++)
        if(str[i][0] > 'А' && str[i][0] < 'Я')
        {
            printf("%s ", str[i]);
            break;
        }

    printf("\nС гласной:\n");
    for(int i = 0; i < Size; i++)
        for(int j = 0; j < 10; j++)
            if(MyToLower(str[i][0]) == glasnie[j])
            {
                printf("%s ", str[i]);
                break;
            }

    printf("\nС согласной:\n");
    for(int i = 0; i < Size; i++)
        for(int j = 0; j < 21; j++)
            if(MyToLower(str[i][0]) == soglasnie[j])
            {
                printf("%s ", str[i]);
                break;
            }
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
