#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, no_of_rec, length, len[20];
class student
{
public:
    char usn[20], sem[20], name[20], branch[20];
};
class textbuff
{
public:
    char buff[500];
    void pack(student s[])
    {
        fstream file1;
        file1.open("first.txt", ios::out | ios::app);
        clear_buff();
        for (int i = 0; i < n; i++)
        {
            strcat(buff, s[i].usn);
            strcat(buff, "|");
            strcat(buff, s[i].name);
            strcat(buff, "|");
            strcat(buff, s[i].branch);
            strcat(buff, "|");
            strcat(buff, s[i].sem);
            strcat(buff, "|");
            no_of_rec++;
            len[no_of_rec] = strlen(buff) + length;
        }
        length = strlen(buff);
        file1 << buff;
        file1.close();
    }
    void unpack(student s[])
    {
        fstream file2;
        file2.open("first.txt", ios::in);
        clear_buff();
        for (int i = 0; i < no_of_rec; i++)
        {
            file2.getline(s[i].usn, 20, '|');
            file2.getline(s[i].name, 20, '|');
            file2.getline(s[i].branch, 20, '|');
            file2.getline(s[i].sem, 20, '|');
        }
    }
    void clear_buff()
    {
        for (int i = 0; i < 500; i++)
            buff[i] = NULL;
    }
    void display(student s[])
    {
        char ch;
        if (no_of_rec != 0)
        {
            cout << "USN\tName\tBranch\tSem\n";
            for (int i = 0; i < no_of_rec; i++)
            {
                ch = s[i].usn[0];
                if (ch != '*')
                    cout << s[i].usn << "\t" << s[i].name << "\t" << s[i].branch << "\t" << s[i].sem << endl;
            }
        }
        else
            cout << "No record found\n";
    }
    void search(student s[])
    {
        int flag = 0;
        char key[20];
        clear_buff();
        cout << "Enter the USN for search: ";
        cin >> key;
        for (int i = 0; i < no_of_rec; i++)
        {
            if (strcmp(key, s[i].usn) == 0)
            {
                cout << "Record found!!\n";
                cout << "USN: " << s[i].usn << ", Name: " << s[i].name << ", Branch: " << s[i].branch << ", Sem: " << s[i].sem << endl;
                flag = 1;
            }
        }
        if (!flag)
            cout << "No such USN found\n";
    }
    void modify(student s[])
    {
        char key[20], cvar[20];
        /*int len1[20];*/
        int flag = 0, len_field;
        /*for(int i = 1; i <= no_of_rec; i++)
            len1[i] = len[i] - len[i-1];*/
        cout << "Enter the USN of record to be modified: ";
        cin >> key;
        for (int i = 0; i < no_of_rec; i++)
        {
            if (strcmp(key, s[i].usn) == 0)
            {
                fstream file3;
                file3.open("first.txt", ios::in | ios::out);
                fstream file4;
                file4.open("first.txt", ios::out | ios::app);
                file3.seekg(len[i], ios::beg);
                file3.getline(cvar, 20, '|');
                len_field = strlen(cvar); //length of 1 field
                file3.seekp(len[i], ios::beg);
                for (int j = 0; j < len_field; j++)
                    file3 << '*';
                file3.close();
                cout << "Enter new data:\nEnter USN, name, branch and sem:\n";
                cin >> s[i].usn >> s[i].name >> s[i].branch >> s[i].sem;
                clear_buff();
                strcat(buff, s[i].usn);
                strcat(buff, "|");
                strcat(buff, s[i].name);
                strcat(buff, "|");
                strcat(buff, s[i].branch);
                strcat(buff, "|");
                strcat(buff, s[i].sem);
                strcat(buff, "|");
                no_of_rec++;
                len[no_of_rec] = strlen(buff) + length;
                // file3.seekp(0, ios::end);
                file4 << buff;
                file4.close();
                flag = 1;
            }
        }
        if (!flag)
            cout << "No such USN found\n";
    }
};
int main()
{
    int ch, i;
    student s[20];
    textbuff b;
    cout << "1.Create\n2.Display\n3.Search\n4.Modify\n5.Exit\n";
    do
    {
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter no. of records: ";
            cin >> n;
            for (i = 0; i < n; i++)
            {
                cout << "Enter USN, name, branch and sem of student " << i + 1 << endl;
                cin >> s[i].usn >> s[i].name >> s[i].branch >> s[i].sem;
            }
            b.pack(s);
            break;
        case 2:
            b.unpack(s);
            b.display(s);
            break;
        case 3:
            b.unpack(s);
            b.search(s);
            break;
        case 4:
            b.unpack(s);
            b.modify(s);
            break;
        case 5:
            remove("first.txt");
            break;
        }
    } while (ch != 5);
}
