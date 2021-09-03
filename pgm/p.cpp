#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>
#include <stdio.h>
using namespace std;
class FLB;
class person
{
    char usn[30], name[30], addr[30], branch[30], colg[30];

public:
    void input();
    void output();
    void search(char *fname);
    void modify(char *fname);
    friend class FLB;
};
class FLB
{
    char buff[160];

public:
    FLB()
    {
        for (int i = 0; i < 160; i++)
            buff[i] = '\0';
    }
    void pack(person &p);
    void unpack(person &p);
    void read(fstream &fs);
    void write(char *fname);
};
void person::input()
{
    cout << "\nEnter USN,Name,Address,Branch and College:\n";
    cin >> usn >> name >> addr >> branch >> colg;
}
void person::output() { cout << "\nUSN : " << usn << "\nName : " << name << "\nAddress: " << addr << "\nBranch :" << branch << "\nCollege : " << colg << endl; }
void FLB::pack(person &p)
{
    strcpy(buff, p.usn);
    strcat(buff, "|");
    strcat(buff, p.name);
    strcat(buff, "|");
    strcat(buff, p.addr);
    strcat(buff, "|");
    strcat(buff, p.branch);
    strcat(buff, "|");
    strcat(buff, p.colg);
    strcat(buff, "\0");
}
void FLB::unpack(person &p)
{
    char *ptr = buff;
    while (*ptr)
    {
        if (*ptr == '|')
            *ptr = '\0';
        ptr++;
    }
    ptr = buff;
    strcpy(p.usn, ptr);
    ptr += strlen(ptr) + 1;
    strcpy(p.name, ptr);
    ptr += strlen(ptr) + 1;
    strcpy(p.addr, ptr);
    ptr += strlen(ptr) + 1;
    strcpy(p.branch, ptr);
    ptr += strlen(ptr) + 1;
    strcpy(p.colg, ptr);
}
void FLB::read(fstream &fs) { fs.read(buff, sizeof(buff)); }
void FLB::write(char *fname)
{
    fstream os(fname, ios::app);
    os.write(buff, sizeof(buff));
    os.close();
}
void person::search(char *fname)
{
    int found = 0;
    person p;
    FLB b;
    char key[30];
    fstream is(fname, ios::in);
    if (is.is_open() == false)
    {
        cout << "\nInsert records to search!\n";
        return;
    }
    cout << "\nEnter the USN to be searched :\n";
    cin >> key;
    while ((!is.eof()) && (!found))
    {
        b.read(is);
        b.unpack(p);
        if (strcmp(p.usn, key) == 0)
        {
            cout << "\nRecord found!!\n";
            p.output();
            found = 1;
        }
    }
    if (!found)
        cout << "\nRecord with given USN does't exist\n";
    is.close();
}
void person::modify(char *fname)
{
    int found = 0;
    person p;
    FLB b;
    char key[30], tname[] = "temp.txt";
    fstream is(fname, ios::in);
    if (is.is_open() == false)
    {
        cout << "\nInsert records to modify!\n";
        return;
    }
    fstream tfile(tname, ios::out | ios::app);
    cout << "\nEnter the USN of record to be modified :\n";
    cin >> key;
    while ((!is.eof()))
    {
        b.read(is);
        if (is.eof())
            break;
        b.unpack(p);
        if (strcmp(p.usn, key) == 0 && !found)
        {
            cout << "\nRecord found!!\n";
            p.input();
            found = 1;
        }
        b.pack(p);
        b.write(tname);
    }
    if (!found)
        cout << "\nRecord with given USN does't exist\n";
    is.close();
    tfile.close();
    remove(fname);
    rename(tname, fname);
}
int main()
{
    int ch;
    person p;
    char fname[] = "prg2.txt";
    do
    {
        cout << "\nMENU\n\n1:Insert\n2:Search\n3:Modify\n4:Exit\n\nEnteryour choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            p.input();
            FLB b;
            b.pack(p);
            b.write(fname);
            break;
        }
        case 2:
            p.search(fname);
            break;
        case 3:
            p.modify(fname);
            break;
        case 4: //remove(fname);
            break;
        }
    } while (ch != 4);
}
