#include "module.h"

struct Avto
{
    char* mark;
    int year;
    float value;
    int probeg;
};

Avto DefaultAvto() //���������� ���� ������ ��� �����������, ������������ ��� �������������� �������, ����� �� �������� ���������.
{
    Avto avtos;
    avtos.mark = (char*)"mark";
    avtos.year = 1111;
    avtos.value = 0;
    avtos.probeg = 1;
    return avtos;
}

Avto* DefaultAvto(int &Size) //������ ������� ������ ��������� ������� �������������� ������, ��� �����������
{
    Size = 1;
    Avto* avtos = new Avto[Size];
    avtos[0] = DefaultAvto();
    return avtos;
}

void FileWrite(Avto* avtos, int Size) //������� ��� ������ � ����.
{
    FILE* fout = fopen("Avtos.txt", "w"); //������� ��������� �� ��������� ���� � ��������� ��� � ������ ������ - "w"
    if(Size <= 0 || fout == NULL) //� ������ �������, ����� ������������ �� ������ � ������.
    {
        printf("������ ������ � ����.");
    }
    else //� ������ �����, ������ ��������� ���� � ����� ����������� �����������...
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
    fclose(fout); //���� ���������� �������, ��� ��� ����� ���� ������ ������...
}

//������� ������������ C++ ������ � C ������, ������ ����������
char* cstc(string s)
{
    char *cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());
    return cstr;
}

Avto* FileRead(int &Size){ //������ ����� � �������������� C++ fstream, ��� ��� �� 2 ���� ������ �� ������� �������� �������, ������� �� ������������ �� C++ fstream
    Avto* avtos = NULL; //������� ������ � ��������� � �� �������������� - NULL
    ifstream f;//������� ��������� �� ��������� ����.
    f.open("Avtos.txt"); //������ ����, � ������ ������ ��� ������/������ � ������ ������������ � ifstream
    if(f.is_open()) //���� ��������� �� �������� �������� �����.
    {
        string str; //������ ����� C++, ��� ��� ������� ������ ������ ������������ � ������� getline
        getline(f, str, '\n'); //������� ����� C++, ��� ��� ��������������� �� �������� C++
        Size = atoi(cstc(str))? atoi(cstc(str)) : 0; //�������� �������(������� if) - ������������ ��� (�������)? ���� ������ : ���� ����;
        if(Size > 0) //����� �� �������� ��������� ������ ����, ������� ���������...
        {
            avtos = new Avto[Size]; //�� ������ �����, ��� ������ ������ 0, ��� ��� ����� �������������� ������ ��������...
            for(int i = 0; i < Size; i++)
            {
                getline(f, str, ' '); //����� ������ �� ����� � ������ ������ ����� �������, �� ������ ������ ������ � ������� getline � ������ � � ������ ��������.
                avtos[i].mark = cstc(str);
                getline(f, str, ' ');
                avtos[i].year = atoi(cstc(str));
                getline(f, str, ' ');
                avtos[i].value = atoi(cstc(str));
                getline(f, str, '\n');  //�����, ����� ��������� ������� �� ������(' '), � ������� �� �������� ������, ��� ��� �� ������ ������ ������ � ����� ����.
                avtos[i].probeg = atoi(cstc(str));
            }
        }
    }
    f.close(); //���� �� ��� �������� �����.
    return avtos;
}

int Write_int(bool zero) //����������� �������, ��� ������������.
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

Avto* Avto_Add(Avto* avtos, int &Size, Avto newAvto) //������ ������� ��������� ������ �������� � � ����� ��������� �����...
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

Avto* Avto_Remove(Avto* avtos, int &Size, int Index) //������� ������� ������ ���� ������ ��� ��������, �������� �� ����� ������� 6-�� �������, ������� ��� 0..5 7..10
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

//�������� ������
char* strEdit(bool Number = false)
{
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ������ ������� � ������� ����� ��������.
    COORD pos; //������� ������� �� ������.
    pos.Y = 1;
    pos.X = 0;
    char* cloneStr = NULL;
    char* str = NULL;

    printf("������:\n");

    while(true)
    {
        int symbol = _getch();

        //����������
        cloneStr = new char[pos.X + 1]; //� ������ ������ ������ ��������� ������ �������� �� 1
        for (int i = 0; i < pos.X; i++)
            if (str[i] != '\0')
                cloneStr[i] = str[i];
        str = new char[pos.X + 1];
        for (int i = 0; i < pos.X; i++)
            str[i] = cloneStr[i];
        delete[] cloneStr; //������, ������ ������� � ������� ���������� ����� ������, �� ��� ����� ����� �����, ��� ��� � ������ ��������������� ������ ���� ������ ���������� �� ���� ����.

        if (symbol >= 97 && symbol <= 122 && !Number && pos.X < 50) //��������� �� ������� ���� ������.
        {
            str[pos.X] = symbol;
            printf("%c", str[pos.X]);
            pos.X++;
        }

        //������
        if(symbol == 32 && !Number && pos.X < 50)
        {
            str[pos.X] = '_';
            printf("%c", ' ');
            pos.X++;
        }

        if((symbol >= 48 && symbol <= 58 || symbol == '.') && pos.X < 50 && Number) //�����
        {
            str[pos.X] = symbol;
            printf("%c", str[pos.X]);
            pos.X++;
        }

        if (symbol == 8 && pos.X > 0) //Backspace
        {
            str[pos.X] = ' ';
            pos.X--;
            SetConsoleCursorPosition(hConsole, pos); //������� �������� ������� ������� � �������(HANDLE hConsole) �� ����������� �������(COORD pos)
            printf("%s", " ");
        }

        SetConsoleCursorPosition(hConsole, pos);
        if (symbol == 13)
        {
            str[pos.X] = '\0';
            break;
        }
    }
    delete[] cloneStr; //������� ������..
    return str;
}

//��������
Avto Avto_Edit(Avto avto, bool isCreated = false)
{
    Avto copyAvto; //������� ������, ������� ����� ������������� � ����������
    if(isCreated) //��� �� �������� ������ �� Avyo avto, ���� ��� ���� ��������.
        copyAvto = avto;
    else
        copyAvto = DefaultAvto(); //��������� ����������� ������
    bool RUN = true;
    while(RUN)
    {
        system("cls"); //���.. ���.. ���.. ����������� ����.
        printf("[�������� ������]\n1.�����\n2.���\n3.�����\n4.������\n5.���������\n6.�� ���������.\n�����: ");
        switch(Write_int())
        {
            case 1:
                copyAvto.mark = strEdit(); //� ������ ������ ������ ���� ������, �� ������� � �������� ������, ������� ��� ������ ����.
                break;
            case 2:
                copyAvto.year = atoi(strEdit(true));
                break;
            case 3:
                copyAvto.value = atof(strEdit(true)); //atof ����������, ������ ��� value - �������� �� �������, � float
                break;
            case 4:
                copyAvto.probeg = atoi(strEdit(true));
                break;
            case 5:
                avto = copyAvto; //��������� ��������� ������
                RUN = false;
                break;
            case 6:
                if(!isCreated)
                    avto = DefaultAvto(); //��� ��������� ����������� � ������� �� ��������� �������.
                RUN = false;
                break;
            default:
                break;
        }
    }
    return avto;
}

Avto* InputAvto(Avto* avtos, int &Size) //������� ��� ������ � ���������...
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
                Avto newAvto = DefaultAvto();
                newAvto = Avto_Edit(newAvto);
                avtos = Avto_Add(avtos, Size, newAvto);
                printf("������ ������� ���� ��������� � ������.\n");
                printf("��� ����������� ������� ����� �������...\n");
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
                    printf("�� ����� ������, ������� ��������� ������ ������.\n");
                    printf("��� ����������� ������� ����� �������...\n");
                    _getch();
                    break;
                }
                avtos[index] = Avto_Edit(avtos[index], true);
                printf("������ ������� ��� �������� � ������.\n");
                printf("��� ����������� ������� ����� �������...\n");
                _getch();
                break;
            }
            case 3:
            {
                printf("[��������]\n������� ������:\n");
                int index = Write_int(true);
                if(index >= Size)
                {
                    printf("�� ����� ������, ������� ��������� ������ ������.\n");
                    printf("��� ����������� ������� ����� �������...\n");
                    _getch();
                    break;
                }
                avtos = Avto_Remove(avtos, Size, index);
                printf("������ �������.\n");
                printf("��� ����������� ������� ����� �������...\n");
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

void OutputAvto(Avto* avtos, int Size){ //������� ���������� � ������ ������������...
    int* index = new int[Size]; //�� ��������� �������, ���� �� ��������� ������ ���� ������ ��� ����������...
    for(int i = 0; i < Size; i++)
        index[i] = i; //������� �� ����� �����������, ��� ��� ��������� �� ��������������� ����������.
    int temp = 0;
    bool output = false;
    system("cls");
    printf("[����� ������]\n1.�� �������\n2.�� �����\n3.�� ����\n4.�� ������\n5.�� �������\n�����: ");
    switch(Write_int())
    {
        case 1:
            output = true;
            break;
        case 2: //���������� �� �����
            for (int i = 0; i < Size - 1; i++) //���������� �� ������������ ���������, ��������� ������...
                for (int j = 0; j < Size - i - 1; j++)
                    if (strcmp(avtos[index[j]].mark, avtos[index[j + 1]].mark)> 0)
                    {
                        temp = index[j]; //������ �������� �������...
                        index[j] = index[j + 1];
                        index[j + 1] = temp;
                    }
            output = true;
            break;
        case 3: //���������� �� ����
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
        case 4: //���������� �� ������
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
        case 5: //���������� �� �������
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
    if(output) //���� �� ������� ���� �� ����� ����������, �� ���������� ��� ������, ������� ������ ������� �� �� ������������� ��������...
    {
        system("cls");
        printf("[����� ������/�� �������]\n");
        char pr[13];
        for (int i = 0; i < Size; i++)
        {
            printf("%d) %s %d %.1f %d", index[i], avtos[index[i]].mark,
                   avtos[index[i]].year, avtos[index[i]].value, avtos[index[i]].probeg);
            printf(" %s\n", avtos[index[i]].probeg >= 100000? "�������� ��!" : " ");
        }
    }
    delete[] index; //������ ������!

    printf("��� ����������� ������� ����� �������...\n");
    _getch();
}
