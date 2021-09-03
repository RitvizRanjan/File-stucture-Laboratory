#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
char index[100][50], indexadd[100][50];
int nor;
void smi()
{
    char temp[100], temp1[100];
    for (int i = 0; i < nor; i++)
    {
        for (int j = i + 1; j < nor; j++)
        {
            if (strcmp(index[i], index[j]) > 0)
            {
                strcpy(temp, index[i]);
                strcmp(index[i], index[j]);
                strcmp(index[j], temp);
                strcmp(temp1, indexadd[i]);
                strcmp(indexadd[i], indexadd[j]);
                strcmp(indexadd[j], temp1);
            }
        }
    }
}
class stud
{
public:
    char usn[10], name[30], brn[30], sem[10];
    void unpack(int);
    void add();
    void del();
    void search();
    void disp();
};
void stud::add()
{
    char buf[100], sadd[50];
    cout << "\n enter usn,name,branch,and sem:\n";
    cin >> usn >> name >> brn >> sem;
    for (int i = 0; i < nor; i++)
    {
        if (strcmp(usn, index[i]) == 0)
        {
            cout << "\nduplicate entry\n";
            return;
        }
    }
    strcpy(buf, usn);
    strcat(buf, "|");
    strcat(buf, name);
    strcat(buf, "|");
    strcat(buf, brn);
    strcat(buf, "|");
    strcat(buf, sem);
    strcat(buf, "|");
    fstream f1("index.txt", ios::app);
    fstream f2("rec.txt", ios::app);
    f2.seekp(0, ios::end);
    strcpy(index[nor], usn);
    itoa(f2.tellp(), sadd, 10);
    strcpy(indexadd[nor], sadd);
    f1 << usn << '|' << f2.tellp() << '\n';
    f2 << buf;
    nor++;
    smi();
    f1.close();
    f2.close();
}
void stud::search()
{
    char usn[10];
    stud s;
    cout << "\nenter usn for search:";
    cin >> usn;
    int max = nor - 1, min = 0, flag = 0, add, mid;
    while (min <= max && flag == 0)
    {
        mid = (min + max) / 2;
        if (strcmp(usn, index[mid]) == 0)
        {
            flag = 1;
            add = atoi(indexadd[mid]);
            s.unpack(add);
            cout << "record found\n";
            cout << "usn:" << s.usn << "\tname:" << s.name << "\tbranch:" << s.brn << "\tsem:" << s.sem << endl;
        }
        else if (strcmp(usn, index[mid]) > 0)
            min = mid + 1;
        else
            max = mid - 1;
    }
    if (!flag)
        cout << "\nsearch failed!!\n";
}
void stud::unpack(int add)
{
    fstream f1("rec.txt", ios::in);
    f1.seekg(add);
    f1.getline(usn, 10, '|');
    f1.getline(name, 30, '|');
    f1.getline(brn, 30, '|');
    f1.getline(sem, 10, '|');
    f1.close();
}
void stud::del()
{
    char usn[10];
    fstream f1("index.txt", ios::out | ios::trunc);
    cout << "\nenter usn to delete:";
    cin >> usn;
    int max = nor - 1, min = 0, flag = 0, mid;
    while (min <= max && flag == 0)
    {
        mid = (min + max) / 2;
        if (strcmp(usn, index[mid]) == 0)
        {
            flag = 1;
            cout << "\nrecord delated\n";
            for (int i = mid; i < nor; i++)
            {
                strcpy(index[i], index[i + 1]);
                strcpy(indexadd[i], indexadd[i + 1]);
            }
            nor--;
        }
        else if (strcmp(usn, index[mid]) > 0)
            min = mid + 1;
        else
            max = mid - 1;
    }
    for (int i = 0; i < nor; i++)
    {
        f1.write(index[i], strlen(index[i]));
        f1.write("|", 1);
        f1.write(indexadd[i], strlen(indexadd[i]));
        f1.write("|\n", 2);
    }
    f1.close();
    if (!flag)
        cout << "\ndeletion failed\n";
}
void stud::disp()
{
    stud s;
    int add;
    cout << "usn\tname\tbranch\tsem\n";
    for (int i = 0; i < nor; i++)
    {
        add = atoi(indexadd[i]);
        s.unpack(add);
        cout << s.usn << "\t" << s.name << "\t" << s.brn << "\t" << s.sem << endl;
    }
}
int main()
{
    stud s;
    int ch;
    cout << "1 add\n2 search\n3 delete\n4 display\n5 exit\n";
    do
    {
        cout << "enter your choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            s.add();
            break;
        case 2:
            s.search();
            break;
        case 3:
            s.del();
            break;
        case 4:
            s.disp();
            break;
            // case 5:
            //     remove("index.txt");
            //     remove("rec.txt");
            break;
        }
    } while (ch != 5);
}
