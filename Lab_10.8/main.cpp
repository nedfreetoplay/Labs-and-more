#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <windows.h>

struct Book
{
    char* author;
    char* name;
    int paperCount;
    int price;
};

///////////////////////////////////////////
//Перегрузка функции strcpy в другом виде//
///////////////////////////////////////////
char* strcpy(char* str, int start, char symbol_stop)
{
    char* cpy = NULL;
    int i = 0;
    while(str[start + i] != symbol_stop)
    {
        i++;
    }
    cpy = new char[i];
    for(int j = 0; i < j; j++)
        cpy[j] = str[j + start];
    start = start + i;
    //Size = i;
    return cpy;
}

Book* FileRead(int &booksSize, char* fileName)
{
    FILE* f = fopen(fileName, "rb"); //Открываем файл в бинарном виде
    char* buffer = NULL;
    int bufferSize = 0;

    ////////////////////////////
    //Чтение из файла в строку//
    ////////////////////////////
    if(f == NULL)
        fputs("Ошибка файла", stderr);
    else
    {
        fseek(f, 0, SEEK_END);
        long lSize = ftell(f);
        rewind(f);

        bufferSize = sizeof(char) * lSize;
        buffer = new char[bufferSize];
        if(buffer == NULL)
            fputs("Ошибка памяти", stderr);
        else
        {
            size_t result = fread(buffer, 1, lSize, f);
            if(result != lSize)
                fputs("Ошибка чтения", stderr);
        }
    }
    fclose(f);
    printf("Считанные данные:\n%s\n", buffer);

    //////////////////////////////////
    //Разбивание строки на структуры//
    //////////////////////////////////
    booksSize = 0;
    for(int i = 0; i < bufferSize; i++)
        if(buffer[i] == '\n')
            booksSize++;
    Book* books = new Book[booksSize];
    /*int start = 0;
    int Size = 0;
    for(int i = 0; i < booksSize; i++)
    {
        books[i].author = strcpy(buffer, Size, start, ',');
        printf("%s ", books[i].author);
        books[i].name = strcpy(buffer, start, ',');
        books[i].paperCount = atoi(strcpy(buffer, start, ','));
        books[i].price = atoi(strcpy(buffer, start, '\n'));
    }*/

    return books;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int Size = 0;
    Book* books = NULL;
    //books = FileRead(Size, "test.txt");
    char test[100] = "JOPA POPA TRALALA";
    printf("%s", strcpy(test, 0, ' '));
    return 0;
}
