#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std; //������������ ��� ��������� ��� ������� FileRead, ��� ��� ��� ������������ fstream

struct Avto;
int Write_int(bool zero = false);
Avto* FileRead(int &Size);
void FileWrite(Avto* avtos, int Size);
void OutputAvto(Avto* avtos, int Size);
Avto* InputAvto(Avto* avtos, int &Size);
