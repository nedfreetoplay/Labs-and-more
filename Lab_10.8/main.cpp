#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

struct Book
{
    char* author;
    char* name;
    int pages;
    int price;
};

Book DefaultBook()
{
    Book book;
    book.author = (char*)"author";
    book.name = (char*)"name";
    book.pages = 0;
    book.price = 0;
    return book;
}

Book* DefaultBook(int &Size)
{
    Size = 1;
    Book* books = new Book[Size];
    books[0] = DefaultBook();
    return books;
}

///////////////////////////////////////////
//���������� ������� strcpy � ������ ����//
///////////////////////////////////////////
char* myStrCpy(char* str, int &start, char symbol_stop) //������ ������� ������, ������� � ������� ���������� �������, ������ �� ������� ������ ����� ���������
{
    char* buffer = NULL;
    int bufferSize = 0;
    while(str[start + bufferSize] != symbol_stop)
    {
        bufferSize++;
    }
    buffer = new char[bufferSize + 1];
    for(int currentCursor = 0; currentCursor < bufferSize; currentCursor++)
        buffer[currentCursor] = str[start + currentCursor];
    buffer[bufferSize] = '\0';
    start += bufferSize + 1;
    return buffer;
}

int LengthNumber(int a)
{
    int length = 0;
    while(a){
        a/=10;
        length++;
    }
    return length;
}

Book* FileRead(int &booksSize, char* fileName)
{
    FILE* f = fopen(fileName, "rb"); //��������� ���� � �������� ����
    char* buffer = NULL;
    int bufferSize = 0;

    ////////////////////////////
    //������ �� ����� � ������//
    ////////////////////////////
    if(f == NULL)
        fputs("������ �����", stderr);
    else
    {
        fseek(f, 0, SEEK_END); // ����������� ���������� ��������� � ����� �����
        long lSize = ftell(f); // ������� ������� ��������� ����������� ���������
        rewind(f); // ���������� ���������� ��������� ����� � ������

        bufferSize = sizeof(char) * lSize; // ��������� ������ ������� ������ ��� �������� ������ �� �����
        buffer = new char[bufferSize];
        if(buffer == NULL)
            fputs("������ ������", stderr);
        else
        {
            size_t result = fread(buffer, 1, lSize, f); // ��������� ���� � �����
            if(result != lSize)
                fputs("������ ������", stderr);
        }
    }
    fclose(f);

    //////////////////////////////////
    //���������� ������ �� ���������//
    //////////////////////////////////
    booksSize = 0;
    for(int i = 0; i < bufferSize; i++) //������� ������� ���������� �������� ���� Book
        if(buffer[i] == '\n')
            booksSize++;
    Book* books = new Book[booksSize];
    printf("��������� ������:\n");
    int start = 0;
    for(int i = 0; i < booksSize; i++)
    {
        books[i].author = myStrCpy(buffer, start, ',');
        books[i].name = myStrCpy(buffer, start, ',');
        books[i].pages = atoi(myStrCpy(buffer, start, ','));
        books[i].price = atoi(myStrCpy(buffer, start, '\n'));
        printf("[%d] %s %s %d %d\n", i, books[i].author, books[i].name, books[i].pages, books[i].price);
    }

    delete buffer;
    printf("��� ����������� ������� ����� �������...\n");
    _getch();
    return books;
}

int FileWrite(char* fileName, Book* books, int Size)
{
    if(Size <= 0)
    {
        printf("������ ���� ���� - ��� ������ ���������� ������.\n��� ����������� ������� ����� �������...\n");
        _getch();
        return 0;
    }
    //��������� ������
    int bufferSize = 0;
    for(int i = 0; i < Size; i++)
        bufferSize += strlen(books[i].author) + strlen(books[i].name) + LengthNumber(books[i].pages) + LengthNumber(books[i].price) + 6;
    char* buffer = new char[bufferSize + 1];
    for(int i = 0; i < Size; i++)
    {
        char* temp = new char[strlen(books[i].author) + strlen(books[i].name) + LengthNumber(books[i].pages) + LengthNumber(books[i].price) + 4];
        sprintf(temp, "%s,%s,%d,%d\n", books[i].author, books[i].name, books[i].pages, books[i].price);
        strcat(buffer, temp);
        delete[] temp;
    }
    buffer[bufferSize] = '\0';

    //������
    FILE* f = fopen(fileName, "wb");
    rewind(f);
    fwrite(buffer, sizeof(char), sizeof(char) * bufferSize, f);
    fclose(f);
    printf("� ���� � ������ %s ���� ��������:\n%s\n��� ����������� ������� ����� �������...\n", fileName, buffer);
    _getch();
    delete[] buffer;
    return 1;
}

int Write_int(bool zero = false)
{
    char str[10];
    int value;
    while(true)
    {
        scanf("%s", str);
        value = abs(atoi(str))? abs(atoi(str)) : 0;
        if (zero) break;
        if (!zero && value > 0)
            break;
        else
            printf("������� �������� |n| > 0: ");
    }
    return value;
}

Book* Book_Add(Book* books, int &Size, Book newBook)
{
    Size++;
    Book* copyBooks = new Book[Size];
    for (int i = 0; i < Size - 1; i++)
        copyBooks[i] = books[i];
    copyBooks[Size - 1].author = newBook.author;
    copyBooks[Size - 1].name = newBook.name;
    copyBooks[Size - 1].pages = newBook.pages;
    copyBooks[Size - 1].price = newBook.price;
    delete[] books;
    return copyBooks;
}

Book* Book_Remove(Book* books, int &Size, int Index)
{
    Size--;
    Book* copyBooks = new Book[Size];
    for (int i = 0; i < Index; ++i)
        copyBooks[i] = books[i];
    for (int i = Index; i < Size; ++i)
        copyBooks[i] = books[i + 1];
    delete[] books;
    return copyBooks;
}

//�������� ������
char* strEdit(bool Number = false)
{
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.Y = 1;
    pos.X = 0;
    char* cloneStr = NULL;
    char* str = NULL;

    printf("������:\n");

    while(true)
    {
        int symbol = _getch();

        cloneStr = new char[pos.X + 1];
        for (int i = 0; i < pos.X; i++)
            if (str[i] != '\0')
                cloneStr[i] = str[i];
        str = new char[pos.X + 1];
        for (int i = 0; i < pos.X; i++)
            str[i] = cloneStr[i];
        delete[] cloneStr;

        if (symbol >= 97 && symbol <= 122 && !Number && pos.X < 50)
        {
            str[pos.X] = symbol;
            printf("%c", str[pos.X]);
            pos.X++;
        }

        if(symbol == 32 && !Number && pos.X < 50)
        {
            str[pos.X] = ' ';
            printf("%c", ' ');
            pos.X++;
        }

        if(symbol >= 48 && symbol <= 58 && pos.X < 50 && Number)
        {
            str[pos.X] = symbol;
            printf("%c", str[pos.X]);
            pos.X++;
        }

        if (symbol == 8 && pos.X > 0)
        {
            str[pos.X] = ' ';
            pos.X--;
            SetConsoleCursorPosition(hConsole, pos);
            printf("%s", " ");
        }

        SetConsoleCursorPosition(hConsole, pos);
        if (symbol == 13)
        {
            str[pos.X] = '\0';
            break;
        }
    }
    delete[] cloneStr;
    return str;
}

//��������
Book Book_Edit(Book book, bool isCreated = false)
{
    Book copyBook;
    if(isCreated)
        copyBook = book;
    else
        copyBook = DefaultBook();
    bool RUN = true;
    while(RUN)
    {
        system("cls");
        printf("[�������� ����]\n1.�����\n2.��������\n3.���. ���.\n4.����\n5.���������\n6.�� ���������.\n�����: ");
        switch(Write_int())
        {
            case 1:
                copyBook.author = strEdit();
                break;
            case 2:
                copyBook.name = strEdit();
                break;
            case 3:
                copyBook.pages = atoi(strEdit(true));
                break;
            case 4:
                copyBook.price = atoi(strEdit(true));
                break;
            case 5:
                book = copyBook;
                RUN = false;
                break;
            case 6:
                if(!isCreated)
                    book = DefaultBook();
                RUN = false;
                break;
            default:
                break;
        }
    }
    return book;
}

Book* InputBook(Book* books, int &Size)
{
    bool RUN = true;
    while(RUN){
        system("cls");
        printf("[�������������� ������]\n1.��������\n2.��������\n3.�������\n4.�����\n�����: ");
        switch(Write_int())
        {
            case 1:
            {
                system("cls");
                Book newBook = DefaultBook();
                newBook = Book_Edit(newBook);
                books = Book_Add(books, Size, newBook);
                printf("����� ������� ���� ��������� � ������ ����.\n��� ����������� ������� ����� �������...\n");
                _getch();
                break;
            }
            case 2:
            {
                system("cls");
                printf("[��������]\n������: ");
                int index = Write_int(true);
                if(index >= Size)
                {
                    printf("�� ����� ������, ������� ��������� ������ ������ ����.\n��� ����������� ������� ����� �������...\n");
                    _getch();
                    break;
                }
                books[index] = Book_Edit(books[index], true);
                printf("����� ������� ���� �������� � ������ ����.\n��� ����������� ������� ����� �������...\n");
                _getch();
                break;
            }
            case 3:
            {
                printf("[��������]\n������� ������:\n");
                int index = Write_int(true);
                if(index >= Size)
                {
                    printf("�� ����� ������, ������� ��������� ������ ������ ����.\n��� ����������� ������� ����� �������...\n");
                    _getch();
                    break;
                }
                books = Book_Remove(books, Size, index);
                printf("����� ���� �������.\n��� ����������� ������� ����� �������...\n");
                _getch();
                break;
            }
            case 4:
                RUN = false;
                break;
            default:
                break;
        }
    }
    return books;
}

void OutputBooks(Book* books, int Size)
{
    int* index = new int[Size];
    for(int i = 0; i < Size; i++)
        index[i] = i;
    int temp = 0; //��������� ����������, ����� ������ ������� �������
    bool RUN = true, output = false;
    while(RUN)
    {
        system("cls");
        printf("[����� ������ ����]\n1.�� �������\n2.�� ������\n3.�� ��������\n4.�� ���. ���.\n5.�� ����\n6.�����\n�����: ");
        switch(Write_int())
        {
            case 1:
                RUN = false;
                output = true;
                break;
            case 2: //���������� �� ������
                for (int i = 0; i < Size - 1; i++)
                    for (int j = 0; j < Size - i - 1; j++)
                        if (strcmp(books[index[j]].author, books[index[j + 1]].author)> 0)
                        {
                            temp = index[j];
                            index[j] = index[j + 1];
                            index[j + 1] = temp;
                        }
                RUN = false;
                output = true;
                break;
            case 3: //���������� �� ��������
                for (int i = 0; i < Size - 1; i++)
                    for (int j = 0; j < Size - i - 1; j++)
                        if (strcmp(books[index[j]].name, books[index[j + 1]].name)> 0)
                        {
                            temp = index[j];
                            index[j] = index[j + 1];
                            index[j + 1] = temp;
                        }
                RUN = false;
                output = true;
                break;
            case 4: //���������� �� ���������� �������
                for (int i = 0; i < Size - 1; i++)
                    for (int j = 0; j < Size - i - 1; j++)
                        if (books[index[j]].pages > books[index[j + 1]].pages)
                        {
                            temp = index[j];
                            index[j] = index[j + 1];
                            index[j + 1] = temp;
                        }
                RUN = false;
                output = true;
                break;
            case 5: //���������� �� ����
                for (int i = 0; i < Size - 1; i++)
                    for (int j = 0; j < Size - i - 1; j++)
                        if (books[index[j]].price > books[index[j + 1]].price)
                        {
                            temp = index[j];
                            index[j] = index[j + 1];
                            index[j + 1] = temp;
                        }
                RUN = false;
                output = true;
                break;
            case 6:
                RUN = false;
                break;
            default:
                break;
        }
        if(output)
        {
            system("cls");
            printf("[����� ������/�� �������]\n");
            for (int i = 0; i < Size; i++)
                printf("[%d] %s %s %d %d\n", index[i], books[index[i]].author,
                       books[index[i]].name, books[index[i]].pages, books[index[i]].price);
        }
    delete[] index;
    }
    printf("��� ����������� ������� ����� �������...\n");
    _getch();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Size = 0;
    Book* books = NULL;

    bool RUN = true;
    while(RUN){
        system("cls");
        printf("[����]\n1.��������� ������\n2.��������� ������\n3.����� ������\n4.�������������� ������\n5.�����\n�����: ");
        switch(Write_int()){
            case 1:
            {
                system("cls");
                books = FileRead(Size, "test.txt"); //��������� ������ �� �����.
                break;
            }
            case 2:
            {
                system("cls");
                FileWrite("test.txt", books, Size);
                break;
            }
            case 3:
            {
                OutputBooks(books, Size);
                break;
            }
            case 4:
            {
                books = InputBook(books, Size);
                break;
            }
            case 5:
                RUN = false;
                break;
            case 6:
                printf("���� ������� lengthNumber:\n");
                printf("1234 - %d\n", LengthNumber(1234));
                printf("12345 - %d\n", LengthNumber(12345));
                printf("1234567 - %d\n", LengthNumber(1234567));
                _getch();
                break;
        }
    }

    delete[] books;
    return 0;
}
