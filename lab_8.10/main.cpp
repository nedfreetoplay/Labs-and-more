#include "module.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Size = 0;
    Music* musics = NULL;

    bool firstRun = true;
    bool RUN = true;
    while(RUN){
        system("cls");
        if(firstRun)
        {
            printf("����� ���������� � ����, ����� ������������!\n���������!\n\n");
            firstRun = false;
        }
        printf("***********************\n");
        printf("[����]\n1.��������� ������\n2.��������� ������\n3.����� ������\n4.�������������� ������\n5.�����\n***********************\n�����: ");
        switch(Write_int()){
            case 1:
            {
                system("cls");
                musics = FileRead(Size);
            }
            case 2:
            {
                system("cls");
                FileWrite(musics, Size);
                break;
            }
            case 3:
            {
                OutputMusic(musics, Size);
                break;
            }
            case 4:
            {
                musics = InputMusic(musics, Size);
                break;
            }
            case 5:
                RUN = false;
                break;
        }
    }

    delete[] musics;
    return 0;
}
