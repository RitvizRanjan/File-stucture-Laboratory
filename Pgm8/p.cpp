#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <iomanip>

using namespace std;

class record
{
public:
    char name[20], usn[20];
} rec[20];

char fname[8][8] = {"1.txt", "2.txt", "3.txt", "4.txt", "5.txt", "6.txt", "7.txt", "8.txt"};
fstream file[8];
int n;

void merge_file(char *fil1, char *fil2, char *fil)
{
    record rcd[20];
    fstream f1(fil1, ios::in);
    fstream f2(fil2, ios::in);
    fstream f3(fil, ios::out);
    int i, j, k = 0, k1;
    record temp;
    while (!f1.eof())
    {
        f1.getline(rcd[k].name, 20, '|');
        f1.getline(rcd[k++].usn, 20);
    }
    while (!f2.eof())
    {
        f2.getline(rcd[k].name, 20, '|');
        f2.getline(rcd[k++].usn, 20);
    }
    k1 = k;
    for (i = 0; i < k - 2; i++)
    {
        for (j = 0; j < k - i - 2; j++)
        {
            if (strcmp(rcd[j].name, rcd[j + 1].name) > 0)
            {
                temp = rcd[j];
                rcd[j] = rcd[j + 1];
                rcd[j + 1] = temp;
            }
            else if (strcmp(rcd[j].name, rcd[j + 1].name) == 0)
            {
                if (strcmp(rcd[j].usn, rcd[j + 1].usn) > 0)
                {
                    temp = rcd[j];
                    rcd[j] = rcd[j + 1];
                    rcd[j + 1] = temp;
                }
                else if (strcmp(rcd[j].usn, rcd[j + 1].usn) == 0)
                {
                    j++;
                    k1--;
                    n--;
                }
            }
        }
    }
    for (i = 1; i < k1 - 1; i++)
    {
        f3 << rcd[i].name << "|" << rcd[i].usn << endl;
    }
    f1.close();
    f2.close();
    f3.close();
}
void k_merge()
{
    char filname[7][20] = {"11.txt", "22.txt", "33.txt", "44.txt", "111.txt", "222.txt", "1111.txt"};
    int i, j = 0;
    for (i = 0; i < 8; i += 2)
        merge_file(fname[i], fname[i + 1], filname[j++]);
    for (i = 0; i < 4; i += 2)
        merge_file(filname[i], filname[i + 1], filname[j++]);
    merge_file(filname[i], filname[i + 1], filname[j]);
}

int main()
{
    int i;
    char name[20], usn[20];
    n = 0;
    for (i = 0; i < 8; i++)
        file[i].open(fname[i], ios::out);
    cout << "Enter number of records: ";
    cin >> n;
    if (n <= 0)
    {
        cout << "No records to sort.Exiting..." << endl;
        return 0;
    };
    cout << "Enter Name and USN:\n";
    for (i = 0; i < n; i++)
    {
        cout << "Student " << i + 1 << " : ";
        cin >> rec[i].name >> rec[i].usn;
        file[i % 8] << rec[i].name << "|" << rec[i].usn << endl;
    }
    for (i = 0; i < 8; i++)
        file[i].close();
    k_merge();
    fstream output("1111.txt", ios::in);
    cout << "\nThe sorted records are:\n";
    cout << left << setw(25) << "NAME"
         << "USN\n";
    for (i = 0; i < n; i++)
    {
        output.getline(name, 20, '|');
        output.getline(usn, 20);
        cout << left << setw(25) << name << usn << endl;
    }
    return 0;
}