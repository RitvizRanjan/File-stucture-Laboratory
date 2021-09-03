#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;
class delimtextbuffer;

class person
{
    char usn[20];
    char name[18];
    char address[20];
    char branch[20];
    char college[20];

public:
    void input();
    void output();
    friend class delimtextbuffer;
};
class delimtextbuffer
{
    char buffer[160];
    char delim;

public:
    void pack(person &p);
    void unpack(person &p);
    void Read(fstream &fs);
    int Write(char *filename);
    delimtextbuffer();
};
class operations
{
    char *rrnfilename;
    char *recordfilename;

public:
    int maxrecords();
    operations(char *rrnfile, char *recordfile);
    void search();
    void insert();
};
operations::operations(char *rrnfile, char *recordfile)
{
    rrnfilename = rrnfile;
    recordfilename = recordfile;
}
int operations::maxrecords()
{
    fstream file(rrnfilename, ios::in);
    int pos;
    file.seekg(0, ios::end);
    pos = file.tellg();
    return (pos / (sizeof(int)));
}
void person::input()
{
    cout << "Enter usn" << endl;
    cin >> usn;
    cout << "Enter name" << endl;
    cin >> name;
    cout << "Enter address" << endl;
    cin >> address;
    cout << "Enter branch" << endl;
    cin >> branch;
    cout << "Enter college" << endl;
    cin >> college;
}
void person::output()
{
    cout << "USN:";
    puts(usn);
    cout << "Name:";
    puts(name);
    cout << "Address:";
    puts(address);
    cout << "Branch:";
    puts(branch);
    cout << "College:";
    puts(college);
}
delimtextbuffer::delimtextbuffer()
{
    for (int i = 0; i < 160; i++)
        buffer[i] = '\0';
    delim = '|';
}
void delimtextbuffer::pack(person &p)
{
    strcpy(buffer, p.usn);
    strcat(buffer, "|");
    strcat(buffer, p.name);
    strcat(buffer, "|");
    strcat(buffer, p.address);
    strcat(buffer, "|");
    strcat(buffer, p.branch);
    strcat(buffer, "|");
    strcat(buffer, p.college);
    strcat(buffer, "|");
    strcat(buffer, "*");
}
void delimtextbuffer::unpack(person &p)
{
    char *ptr = buffer;
    while (*ptr)
    {
        if (*ptr == '|')
            *ptr = '\0';
        ptr++;
    }
    ptr = buffer;
    strcpy(p.usn, ptr);
    ptr += strlen(ptr) + 1;
    strcpy(p.name, ptr);
    ptr += strlen(ptr) + 1;
    strcpy(p.address, ptr);
    ptr += strlen(ptr) + 1;
    strcpy(p.branch, ptr);
    ptr += strlen(ptr) + 1;
    strcpy(p.college, ptr);
}
void delimtextbuffer::Read(fstream &fs)
{
    fs.getline(buffer, 160, '*');
}
int delimtextbuffer::Write(char *filename)
{
    fstream os(filename, ios::out | ios::app);
    os.seekg(0, ios::end);
    int offset = os.tellp();
    os.write(buffer, strlen(buffer));
    os.close();
    return offset;
}
void operations::search()
{
    int rrn;
    cout << "enter the RRN of the record to be searched(1 - based)";
    cin >> rrn;
    if (rrn > maxrecords() || rrn <= 0)
    {
        cout << "record not found!!!" << endl;
        return;
    }
    delimtextbuffer b;
    person p;
    int offset = 8;
    fstream file(rrnfilename, ios::in);

    file.seekg((rrn - 1) * sizeof(int), ios::beg);
    file.read((char *)&offset, sizeof(offset));

    file.close();
    cout << "record found!!" << endl;
    fstream file1(recordfilename, ios::in);
    file1.seekg(offset, ios::beg);
    b.Read(file1);
    b.unpack(p);
    p.output();
    file1.close();
}
void operations::insert()
{
    person ob;
    delimtextbuffer b;
    int offset;
    fstream file, file2;
    ob.input();
    b.pack(ob);
    offset = b.Write(recordfilename);
    file.open(rrnfilename, ios::out | ios::app);
    file2.open("rr.txt", ios::out | ios::app);
    file2 << offset;
    file.write((char *)&offset, sizeof(int));
    file.close();
}
int main()
{
    int choice = 1;
    fstream file, file1;
    person ob;
    delimtextbuffer b;
    char filename[20] = "name.txt";
    char rrnfilename[20] = "rrn.txt";
    operations o(rrnfilename, filename);
    while (choice < 3)
    {
        cout << "1:Insert a Record" << endl;
        cout << "2:Search for a Record" << endl;
        cout << "3:exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            o.insert();
            break;
        case 2:
            o.search();
            break;
        }
    }
    return 0;
}
