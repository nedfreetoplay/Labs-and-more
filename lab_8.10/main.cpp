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
            printf("Добро пожаловать в меню, Денис Владимирович!\nВыбирайте!\n\n");
            firstRun = false;
        }
        printf("***********************\n");
        printf("[Меню]\n1.Загрузить список\n2.Сохранить список\n3.Вывод списка\n4.Редактирование списка\n5.Выход\n***********************\nВыбор: ");
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
