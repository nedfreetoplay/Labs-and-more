#include "module.h"

int main()
{
    SetConsoleCP(1251); //������� ���� � �������. ������������ SetLocale ��� ������, ��� ��� �� �������� ������� �����, �� �� �������� ������...
    SetConsoleOutputCP(1251);

    int Size = 0;
    Avto* avtos = NULL; //������� ������ ��������, ������� ���������� ���� ���� �� �������...

    bool RUN = true;
    while(RUN){
        system("cls");
        printf("[����]\n1.��������� ������\n2.��������� ������\n3.����� ������\n4.�������������� ������\n5.�����\n�����: ");
        switch(Write_int()){
            case 1:
            {
                system("cls");
                avtos = FileRead(Size); //��������� ������ �� �����.
            }
            case 2:
            {
                system("cls");
                FileWrite(avtos, Size); //���������� ������ � ����.
                break;
            }
            case 3:
            {
                OutputAvto(avtos, Size); //������� ������ �� ����� �� ����������� �����.
                break;
            }
            case 4:
            {
                avtos = InputAvto(avtos, Size); //����������� �������.
                break;
            }
            case 5:
                RUN = false; //�����)))
                break;
        }
    }

    delete[] avtos; //������ ������ ����� ������ ���������.
    return 0;
}
