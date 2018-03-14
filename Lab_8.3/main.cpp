#include "module.h"

int main()
{
    SetConsoleCP(1251); //Русский язык в консоли. Использовать SetLocale нет смысла, так как он изменяет видимый шрифт, но не вводимые данные...
    SetConsoleOutputCP(1251);

    int Size = 0;
    Avto* avtos = NULL; //Главный массив объектов, который передается куда либо по цепочке...

    bool RUN = true;
    while(RUN){
        system("cls");
        printf("[Меню]\n1.Загрузить список\n2.Сохранить список\n3.Вывод списка\n4.Редактирование списка\n5.Выход\nВыбор: ");
        switch(Write_int()){
            case 1:
            {
                system("cls");
                avtos = FileRead(Size); //Загружаем данные из файла.
            }
            case 2:
            {
                system("cls");
                FileWrite(avtos, Size); //Записываем данные в файл.
                break;
            }
            case 3:
            {
                OutputAvto(avtos, Size); //Выводим данные на экран по определённым полям.
                break;
            }
            case 4:
            {
                avtos = InputAvto(avtos, Size); //Редактируем объекты.
                break;
            }
            case 5:
                RUN = false; //Выход)))
                break;
        }
    }

    delete[] avtos; //Чистим память после работы программы.
    return 0;
}
