#include "module.h"

struct Date
{
    int day;
    int month;
    int year;
};

struct Music
{
    char* author;
    char* name;
    Date date;
    int rating;
};

/*Music* DefaultMusics(int &Size)
{
    Size = 1;
    Music* musics = new Music[Size];
    musics[0].author = (char*)"author";
    musics[0].date.day = 1;
    musics[0].date.month = 1;
    musics[0].date.year = 1;
    musics[0].name = (char*)"name";
    musics[0].rating = 0;
    return musics;
}*/

Music DefaultMusic()
{
    Music music;
    music.author = (char*)"author";
    music.date.day = 1;
    music.date.month = 1;
    music.date.year = 1;
    music.name = (char*)"name";
    music.rating = 0;
    return music;
}

void FileWrite(Music* musics, int Size)
{
    FILE* fout = fopen("Musics.txt", "w");
    if(Size <= 0 || fout == NULL)
    {
        printf("Ошибка записи в файл.");
    }
    else
    {
        fprintf(fout, "%d\n", Size);
        for(int i = 0; i < Size; i++)
        {
            fprintf(fout, "%s ", musics[i].author);
            fprintf(fout, "%s ", musics[i].name);
            fprintf(fout, "%d %d %d ", musics[i].date.day, musics[i].date.month, musics[i].date.year);
            fprintf(fout, "%d\n", musics[i].rating);
        }
    }
    fclose(fout);
}

char* cstc(string s){
    char *cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());
    return cstr;
}

Music* FileRead(int &Size){
    Music* musics = NULL;
    ifstream f;
    f.open("Musics.txt");
    if(f.is_open())
    {
        string str;
        getline(f, str, '\n');
        Size = atoi(cstc(str))? atoi(cstc(str)) : 0;
        if(Size > 0)
        {
            musics = new Music[Size];
            for(int i = 0; i < Size; i++)
            {
                getline(f, str, ' ');
                musics[i].author = cstc(str);
                getline(f, str, ' ');
                musics[i].name = cstc(str);
                getline(f, str, ' ');
                musics[i].date.day = atoi(cstc(str));
                getline(f, str, ' ');
                musics[i].date.month = atoi(cstc(str));
                getline(f, str, ' ');
                musics[i].date.year = atoi(cstc(str));
                getline(f, str, '\n');
                musics[i].rating = atoi(cstc(str));
            }
        }
    }
    f.close();
    return musics;
}

int Write_int(bool zero)
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
            printf("Введите значение |n| > 0: ");
    }
    return value;
}

Music* Music_Add(Music* musics, int &Size, Music newMusic)
{
    Size++;
    Music* copyMusics = new Music[Size];
    for (int i = 0; i < Size - 1; i++)
        copyMusics[i] = musics[i];
    copyMusics[Size - 1].author = newMusic.author;
    copyMusics[Size - 1].name = newMusic.name;
    copyMusics[Size - 1].date = newMusic.date;
    copyMusics[Size - 1].rating = newMusic.rating;
    delete[] musics;
    return copyMusics;
}

Music* Music_Remove(Music* musics, int &Size, int Index)
{
    Size--;
    Music* copyMusics = new Music[Size];
    for (int i = 0; i < Index; ++i)
        copyMusics[i] = musics[i];
    for (int i = Index; i < Size; ++i)
        copyMusics[i] = musics[i + 1];
    delete[] musics;
    return copyMusics;
}

int DateCmp(Date d1, Date d2)
{
    if(d1.year > d2.year)
        return -1;
    else
        if(d1.year < d2.year)
            return 1;
        else
        {
            if(d1.month > d2.month)
                return -1;
            else
                if(d1.month < d2.month)
                    return 1;
                else
                {
                    if(d1.day > d2.day)
                        return -1;
                    else
                        if(d1.day < d2.day)
                            return 1;
                        else
                            return 0;
                }
        }
}

char* strEdit(bool Number = false)
{
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.Y = 1;
    pos.X = 0;
    char* cloneStr = NULL;
    char* str = NULL;

    printf("Вводите:\n");

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
            str[pos.X] = '_';
            printf("%c", ' ');
            pos.X++;
        }

        if(symbol >= 48 && symbol <= 58 && pos.X < 50 && Number) //Цифры
        {
            str[pos.X] = symbol;
            printf("%c", str[pos.X]);
            pos.X++;
        }

        if (symbol == 8 && pos.X > 0) //Backspace
        {
            str[pos.X] = ' ';
            pos.X--;
            SetConsoleCursorPosition(hConsole, pos); //Функция изменяет позицию курсора в консоли(HANDLE hConsole) на определённую позицию(COORD pos)
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

Date dateEdit()
{
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursor;
    cursor.X = 0;
    cursor.Y = 1;

    char* cloneStr = NULL;
    char* str = NULL;

    printf("[Дата]:\n  /  /");
    SetConsoleCursorPosition(hConsole, cursor);
    while(true)
    {
        int symbol = _getch();

        cloneStr = new char[cursor.X + 1];
        for (int i = 0; i < cursor.X; i++)
            if (str[i] != '\0')
                cloneStr[i] = str[i];
        str = new char[cursor.X + 1];
        for (int i = 0; i < cursor.X; i++)
            str[i] = cloneStr[i];
        delete[] cloneStr;

        if(symbol >= 48 && symbol <= 58 && cursor.X < 10)
        {
            str[cursor.X] = symbol;
            printf("%c", str[cursor.X]);
            cursor.X++;
            if(cursor.X == 2 || cursor.X == 5)
                cursor.X++;
        }

        if (symbol == 8 && cursor.X > 0)
        {
            str[cursor.X] = ' ';
            cursor.X--;
            if(cursor.X == 2 || cursor.X == 5)
                cursor.X--;
            SetConsoleCursorPosition(hConsole, cursor);
            printf("%s", " ");
        }

        SetConsoleCursorPosition(hConsole, cursor);
        if (symbol == 13 && cursor.X == 10)
        {
            str[cursor.X] = '\0';
            break;
        }
    }
    Date date;
    char* temp = new char[3];
    temp[0] = str[0]; temp[1] = str[1]; temp[2] = '\0';
    date.day = atoi(temp);

    temp[0] = str[3]; temp[1] = str[4]; temp[2] = '\0';
    date.month = atoi(temp);

    delete[] temp; temp = new char[5];
    temp[0] = str[6]; temp[1] = str[7]; temp[2] = str[8]; temp[3] = str[9]; temp[4] = '\0';
    date.year = atoi(temp);

    delete[] temp;
    delete[] str;
    return date;
}


Music Music_Edit(Music music, bool isCreated = false)
{
    Music copyMusic;
    if(isCreated)
        copyMusic = music;
    else
        copyMusic = DefaultMusic();
    bool RUN = true;
    while(RUN)
    {
        system("cls");
        printf("[Редактор книг]\n1.Автор\n2.Название\n3.Дата\n4.Рейтинг\n5.Сохранить\n6.Не сохранять.\nВыбор: ");
        switch(Write_int())
        {
            case 1:
                copyMusic.author = strEdit();
                break;
            case 2:
                copyMusic.name = strEdit();
                break;
            case 3:
                copyMusic.date = dateEdit();
                break;
            case 4:
                copyMusic.rating = atoi(strEdit(true));
                break;
            case 5:
                music = copyMusic;
                RUN = false;
                break;
            case 6:
                if(!isCreated)
                    music = DefaultMusic();
                RUN = false;
                break;
            default:
                break;
        }
    }
    return music;
}

Music* InputMusic(Music* musics, int &Size)
{
    bool RUN = true;
    while(RUN){
        system("cls");
        printf("[Редактирование списка]\n1.Добавить\n2.Изменить\n3.Удалить\n4.Назад\nВыбор: ");
        switch(Write_int())
        {
            case 1:
            {
                system("cls");
                Music newMusic = DefaultMusic();
                newMusic = Music_Edit(newMusic);
                musics = Music_Add(musics, Size, newMusic);
                printf("Музыка успешно была добавлена в список музыки.\n");
                printf("Для продолжения нажмите любую клавишу...\n");
                _getch();
                break;
            }
            case 2:
            {
                system("cls");
                printf("[Изменить]\nИндекс: ");
                int index = Write_int(true);
                if(index >= Size)
                {
                    printf("Вы ввели индекс, который привышает размер списка музыки.\n");
                    printf("Для продолжения нажмите любую клавишу...\n");
                    _getch();
                    break;
                }
                musics[index] = Music_Edit(musics[index], true);
                printf("Музыка успешно была изменена в список музыки.\n");
                printf("Для продолжения нажмите любую клавишу...\n");
                _getch();
                break;
            }
            case 3:
            {
                printf("[Удаление]\nВведите индекс:\n");
                int index = Write_int(true);
                if(index >= Size)
                {
                    printf("Вы ввели индекс, который привышает размер списка музыки.\n");
                    printf("Для продолжения нажмите любую клавишу...\n");
                    _getch();
                    break;
                }
                musics = Music_Remove(musics, Size, index);
                printf("Книга удалена.\n");
                printf("Для продолжения нажмите любую клавишу...\n");
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
    return musics;
}

void OutputMusic(Music* musics, int Size)
{
    int* index = new int[Size];
    for(int i = 0; i < Size; i++)
        index[i] = i;
    int temp = 0;
    bool output = false;
    system("cls");
    printf("[Вывод списка]\n1.По индексу\n2.По Автору\n3.По Названию\n4.По Дате\n5.По Рейтингу\nВыбор: ");
    switch(Write_int())
    {
        case 1:
            output = true;
            break;
        case 2:
            for (int i = 0; i < Size - 1; i++)
                for (int j = 0; j < Size - i - 1; j++)
                    if (strcmp(musics[index[j]].author, musics[index[j + 1]].author)> 0)
                    {
                        temp = index[j];
                        index[j] = index[j + 1];
                        index[j + 1] = temp;
                    }
            output = true;
            break;
        case 3:
            for (int i = 0; i < Size - 1; i++)
                for (int j = 0; j < Size - i - 1; j++)
                    if (strcmp(musics[index[j]].name, musics[index[j + 1]].name)> 0)
                    {
                        temp = index[j];
                        index[j] = index[j + 1];
                        index[j + 1] = temp;
                    }
            output = true;
            break;
        case 4:
            for (int i = 0; i < Size - 1; i++)
                for (int j = 0; j < Size - i - 1; j++)
                    if (DateCmp(musics[index[j]].date, musics[index[j + 1]].date) > 0) //Используем вместо strcmp DateCmp, так как нам надо сравнить даты. >(-1) <(1) ==(0)
                    {
                        temp = index[j];
                        index[j] = index[j + 1];
                        index[j + 1] = temp;
                    }
            output = true;
            break;
        case 5:
            for (int i = 0; i < Size - 1; i++)
                for (int j = 0; j < Size - i - 1; j++)
                    if (musics[index[j]].rating > musics[index[j + 1]].rating)
                    {
                        temp = index[j];
                        index[j] = index[j + 1];
                        index[j + 1] = temp;
                    }
            output = true;
            break;
        default:
            break;
    }
    if(output)
    {
        system("cls");
        printf("[Вывод списка/По индексу]\n");
        for (int i = 0; i < Size; i++)
            printf("%d) %s %s %d/%d/%d %d\n", index[i], musics[index[i]].author,
                   musics[index[i]].name, musics[index[i]].date.day,
                   musics[index[i]].date.month, musics[index[i]].date.year,
                   musics[index[i]].rating);
    }
    delete[] index;

    printf("Для продолжения нажмите любую клавишу...\n");
    _getch();
}
