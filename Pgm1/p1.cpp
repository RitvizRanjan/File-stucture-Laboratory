#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>
#include <stdio.h>
using namespace std;
void reverse(char *name)
{
    int i, j, size;
    char temp;
    size = strlen(name);

    for (i = 0, j = size - 1; i < j; i++, j--)
    {
        temp = name[i];
        name[i] = name[j];
        name[j] = temp;
    }
}
int main(int argc, char *argv[])
{
    char name[30];
    if (argc == 1)
    {
        do
        {
            cin >> name;
            reverse(name);
            cout << name;
            if (cin.eof())
                break;
        } while (1);
    }
    else if (argc > 2)
    {
        fstream ip, fp;
        fp.open(argv[1], ios::in);
        ip.open(argv[2], ios::out | ios::app);

        do
        {
            fp >> name;
            reverse(name);
            cout << name << endl;
            ip << name;
            if (fp.eof())
                break;
        } while (1);
        fp.close();
        ip.close();
    }
    else
        cout << "error";
    return 0;
}
