#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

struct Music;
int Write_int(bool zero = false);
Music* FileRead(int &Size);
void FileWrite(Music* musics, int Size);
void OutputMusic(Music* musics, int Size);
Music* InputMusic(Music* musics, int &Size);
