#include "module.h"

struct Avto
{
    char* mark;
    int year;
    float value;
    int probeg;
};

Avto DefaultAvto() //Возвращает один объект как стандартный, используется при редактировании объекта, когда мы отменяем изменения.
{
    Avto avtos;
    avtos.mark = (char*)"mark";
    avtos.year = 1111;
    avtos.value = 0;
    avtos.probeg = 1;
    return avtos;
}

Avto* DefaultAvto(int &Size) //Данная функция просто возращает заранее подготовленный массив, как стандартный
{
    Size = 1;
    Avto* avtos = new Avto[Size];
    avtos[0] = DefaultAvto();
    return avtos;
}

void FileWrite(Avto* avtos, int Size) //Функция для записи в файл.
{
    FILE* fout = fopen("Avtos.txt", "w"); //Создаем указатель на потоковый файл и загружаем его в режиме чтения - "w"
    if(Size <= 0 || fout == NULL) //В случае неудачи, пишем пользователь об ошибке с файлам.
    {
        printf("Ошибка записи в файл.");
    }
    else //В случае удачи, просто заполняем файл в цикле необходимой информацией...
    {
        fprintf(fout, "%d\n", Size);
        for(int i = 0; i < Size; i++)
        {
            fprintf(fout, "%s ", avtos[i].mark);
            fprintf(fout, "%d ", avtos[i].year);
            fprintf(fout, "%f ", avtos[i].value);
            fprintf(fout, "%d\n", avtos[i].probeg);
        }
    }
    fclose(fout); //Файл необходимо закрыть, так как могут быть потери данных...
}

//Функция конвертирует C++ строки в C строки, ничего особенного
char* cstc(string s)
{
    char *cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());
    return cstr;
}

Avto* FileRead(int &Size){ //Чтение файла с использованием C++ fstream, так как за 2 часа опытов не удалось написать функцию, которая не использовала бы C++ fstream
    Avto* avtos = NULL; //Создаем массив с объектами и не инициализируем - NULL
    ifstream f;//Создаем указатель на потоковый файл.
    f.open("Avtos.txt"); //Читаем файл, в данном случае тип чтения/записи с файлом определяется в ifstream
    if(f.is_open()) //Надо проверить на успешное открытие файла.
    {
        string str; //Строки языка C++, так как обычные строки нельзя использовать в функции getline
        getline(f, str, '\n'); //Функция языка C++, так как взаимодействует со строками C++
        Size = atoi(cstc(str))? atoi(cstc(str)) : 0; //Линейное условие(ленивый if) - определяется как (Условие)? если правда : если ложь;
        if(Size > 0) //Вдруг мы пытаемся прочитать пустой файл, следует исключить...
        {
            avtos = new Avto[Size]; //Мы теперь знаем, что размер больше 0, так что смело инициализируем массив объектов...
            for(int i = 0; i < Size; i++)
            {
                getline(f, str, ' '); //Схема чтения из файла в данном случае очень простая, мы просто читаем строку с помощью getline и вносим её в массив объектов.
                avtos[i].mark = cstc(str);
                getline(f, str, ' ');
                avtos[i].year = atoi(cstc(str));
                getline(f, str, ' ');
                avtos[i].value = atoi(cstc(str));
                getline(f, str, '\n');  //Важно, здесь требуется указать не пробел(' '), а переход на следущую строку, так как мы храним данные именно в таком виде.
                avtos[i].probeg = atoi(cstc(str));
            }
        }
    }
    f.close(); //куда же без закрытия файла.
    return avtos;
}

int Write_int(bool zero) //Стандартная функция, без комментариев.
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

Avto* Avto_Add(Avto* avtos, int &Size, Avto newAvto) //Данная функция расширяет массив объектов и в конец добавляет новый...
{
    Size++;
    Avto* copyAvtos = new Avto[Size];
    for (int i = 0; i < Size - 1; i++)
        copyAvtos[i] = avtos[i];
    copyAvtos[Size - 1].mark = newAvto.mark;
    copyAvtos[Size - 1].year = newAvto.year;
    copyAvtos[Size - 1].value = newAvto.value;
    copyAvtos[Size - 1].probeg = newAvto.probeg;
    delete[] avtos;
    return copyAvtos;
}

Avto* Avto_Remove(Avto* avtos, int &Size, int Index) //Функция удаляет объект путём обхода его стороной, например мы хотим удалить 6-ой элемент, сделаем это 0..5 7..10
{
    Size--;
    Avto* copyAvtos = new Avto[Size];
    for (int i = 0; i < Index; ++i)
        copyAvtos[i] = avtos[i];
    for (int i = Index; i < Size; ++i)
        copyAvtos[i] = avtos[i + 1];
    delete[] avtos;
    return copyAvtos;
}

//Редактор строки
char* strEdit(bool Number = false)
{
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Получаем объект консоли с которой будем работать.
    COORD pos; //Позиция курсора на экране.
    pos.Y = 1;
    pos.X = 0;
    char* cloneStr = NULL;
    char* str = NULL;

    printf("Строка:\n");

    while(true)
    {
        int symbol = _getch();

        //Расширение
        cloneStr = new char[pos.X + 1]; //В данном случае просто расширяем массив символов на 1
        for (int i = 0; i < pos.X; i++)
            if (str[i] != '\0')
                cloneStr[i] = str[i];
        str = new char[pos.X + 1];
        for (int i = 0; i < pos.X; i++)
            str[i] = cloneStr[i];
        delete[] cloneStr; //Кстати, данной команды в прошлых редакторах строк небыло, но она здесь очень важна, так как с каждым редактированием строки наша память засерается на пару байт.

        if (symbol >= 97 && symbol <= 122 && !Number && pos.X < 50) //Проверяем на нажатие англ клавиш.
        {
            str[pos.X] = symbol;
            printf("%c", str[pos.X]);
            pos.X++;
        }

        //Пробел
        if(symbol == 32 && !Number && pos.X < 50)
        {
            str[pos.X] = '_';
            printf("%c", ' ');
            pos.X++;
        }

        if((symbol >= 48 && symbol <= 58 || symbol == '.') && pos.X < 50 && Number) //Цифры
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
    delete[] cloneStr; //Удаляем лишнее..
    return str;
}

//Редактор
Avto Avto_Edit(Avto avto, bool isCreated = false)
{
    Avto copyAvto; //Создаем объект, который будем редактировать в дальнейшем
    if(isCreated) //Тут мы копируем данные из Avyo avto, если они были переданы.
        copyAvto = avto;
    else
        copyAvto = DefaultAvto(); //загружаем стандартный объект
    bool RUN = true;
    while(RUN)
    {
        system("cls"); //бла.. бла.. бла.. стандартное меню.
        printf("[Редактор машины]\n1.Марка\n2.Год\n3.Объем\n4.Пробег\n5.Сохранить\n6.Не сохранять.\nВыбор: ");
        switch(Write_int())
        {
            case 1:
                copyAvto.mark = strEdit(); //В случае выбора именно этой строки, мы перейдём в редактор строки, который был описан выше.
                break;
            case 2:
                copyAvto.year = atoi(strEdit(true));
                break;
            case 3:
                copyAvto.value = atof(strEdit(true)); //atof используем, потому что value - является не строкой, а float
                break;
            case 4:
                copyAvto.probeg = atoi(strEdit(true));
                break;
            case 5:
                avto = copyAvto; //Сохраняем изменённые данные
                RUN = false;
                break;
            case 6:
                if(!isCreated)
                    avto = DefaultAvto(); //или загружаем стандартные и выходим из редактора объекта.
                RUN = false;
                break;
            default:
                break;
        }
    }
    return avto;
}

Avto* InputAvto(Avto* avtos, int &Size) //Функция для работы с объектами...
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
                Avto newAvto = DefaultAvto();
                newAvto = Avto_Edit(newAvto);
                avtos = Avto_Add(avtos, Size, newAvto);
                printf("Машина успешно была добавлена в список.\n");
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
                    printf("Вы ввели индекс, который привышает размер списка.\n");
                    printf("Для продолжения нажмите любую клавишу...\n");
                    _getch();
                    break;
                }
                avtos[index] = Avto_Edit(avtos[index], true);
                printf("Машина успешно был изменена в списке.\n");
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
                    printf("Вы ввели индекс, который привышает размер списка.\n");
                    printf("Для продолжения нажмите любую клавишу...\n");
                    _getch();
                    break;
                }
                avtos = Avto_Remove(avtos, Size, index);
                printf("Машина удалена.\n");
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
    return avtos;
}

void OutputAvto(Avto* avtos, int Size){ //Функция сортировки и вывода одновременно...
    int* index = new int[Size]; //Мы сортеруем индексы, дабы не создавать разные типы данных для сортировки...
    for(int i = 0; i < Size; i++)
        index[i] = i; //Индексы не могут повторяться, так что заполняем их индивидуальными значениями.
    int temp = 0;
    bool output = false;
    system("cls");
    printf("[Вывод списка]\n1.По индексу\n2.По марке\n3.По году\n4.По объему\n5.По пробегу\nВыбор: ");
    switch(Write_int())
    {
        case 1:
            output = true;
            break;
        case 2: //Сортировка по Марке
            for (int i = 0; i < Size - 1; i++) //Сортировка по пузырьковому алгоритму, расказать нечего...
                for (int j = 0; j < Size - i - 1; j++)
                    if (strcmp(avtos[index[j]].mark, avtos[index[j + 1]].mark)> 0)
                    {
                        temp = index[j]; //замена индексов местами...
                        index[j] = index[j + 1];
                        index[j + 1] = temp;
                    }
            output = true;
            break;
        case 3: //Сортировка по году
            for (int i = 0; i < Size - 1; i++)
                for (int j = 0; j < Size - i - 1; j++)
                    if (avtos[index[j]].year > avtos[index[j + 1]].year)
                    {
                        temp = index[j];
                        index[j] = index[j + 1];
                        index[j + 1] = temp;
                    }
            output = true;
            break;
        case 4: //Сортировка по объему
            for (int i = 0; i < Size - 1; i++)
                for (int j = 0; j < Size - i - 1; j++)
                    if (avtos[index[j]].value > avtos[index[j + 1]].value)
                    {
                        temp = index[j];
                        index[j] = index[j + 1];
                        index[j + 1] = temp;
                    }
            output = true;
            break;
        case 5: //Сортировка по пробегу
            for (int i = 0; i < Size - 1; i++)
                for (int j = 0; j < Size - i - 1; j++)
                    if (avtos[index[j]].probeg > avtos[index[j + 1]].probeg)
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
    if(output) //если мы выбрали один из типов сортировки, то сортировка уже прошла, остаётся только вывести их по сортированным индексам...
    {
        system("cls");
        printf("[Вывод списка/По индексу]\n");
        char pr[13];
        for (int i = 0; i < Size; i++)
        {
            printf("%d) %s %d %.1f %d", index[i], avtos[index[i]].mark,
                   avtos[index[i]].year, avtos[index[i]].value, avtos[index[i]].probeg);
            printf(" %s\n", avtos[index[i]].probeg >= 100000? "Пройдите ТО!" : " ");
        }
    }
    delete[] index; //Чистим память!

    printf("Для продолжения нажмите любую клавишу...\n");
    _getch();
}
