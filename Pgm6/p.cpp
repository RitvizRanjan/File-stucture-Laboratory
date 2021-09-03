#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <filesystem>

using namespace std;

class record
{
public:
    char usn[10], name[20], branch[10], sem[2];
} rec[20], found[20];

int m = 0, n;

void add()
{
    int i;
    cout << "Enter number of students: ";
    cin >> n;
    cout << "Enter Name, USN, Branch and Sem\n";
    n = m + n;
    for (i = m; i < n; i++)
    {
        cout << "Student " << i + 1 << " :\n";
        cin >> rec[i].name >> rec[i].usn >> rec[i].branch >> rec[i].sem;
        m++;
    }
}

void sort_records()
{
    int i, j;
    record temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (strcmp(rec[j].name, rec[j + 1].name) > 0)
            {
                temp = rec[j];
                rec[j] = rec[j + 1];
                rec[j + 1] = temp;
            }
            else if (strcmp(rec[j].name, rec[j + 1].name) == 0)
            {
                if (strcmp(rec[j].usn, rec[j + 1].usn) > 0)
                {
                    temp = rec[j];
                    rec[j] = rec[j + 1];
                    rec[j + 1] = temp;
                }
            }
        }
    }
}

void create_file()
{
    fstream index("secindex.txt", ios::out);
    fstream file("record.txt", ios::out);
    for (int i = 0; i < n; i++)
    {
        index << rec[i].name << "|" << rec[i].usn << "|" << i << "\n";
        file << i << "|" << rec[i].usn << "|" << rec[i].name << "|" << rec[i].branch << "|" << rec[i].sem << "\n";
    }
    index.close();
    file.close();
}

void retrieve_record(char *index)
{
    fstream f1("record.txt", ios::in);
    int i;
    char ind[3], usn[10], name[20], branch[10], sem[2];
    for (i = 0; i < n; i++)
    {
        f1.getline(ind, 3, '|');
        f1.getline(usn, 10, '|');
        f1.getline(name, 20, '|');
        f1.getline(branch, 10, '|');
        f1.getline(sem, 2, '\n');
        if (strcmp(index, ind) == 0)
            cout << "USN: " << usn << " Name: " << name << " Branch: " << branch << " Sem: " << sem << endl;
    }
    f1.close();
}

void search()
{
    int k = 0, i, flag;
    fstream f1("secindex.txt", ios::in);
    char name[20], usn[10], ind[3], key_usn[10], key_name[20];
    char index[20][20];
    cout << "Enter the name for search: ";
    cin >> key_name;
    for (i = 0; i < n; i++)
    {
        f1.getline(name, 20, '|');
        f1.getline(usn, 10, '|');
        f1.getline(ind, 3, '\n');
        if (strcmp(key_name, name) == 0)
        {
            strcpy(found[k].name, name);
            strcpy(found[k].usn, usn);
            strcpy(index[k], ind);
            k++;
        }
    }
    f1.close();
    if (k == 0)
        cout << "Search failed!!\n";
    else if (k == 1)
        retrieve_record(index[0]);
    else
    {
        cout << "Choose USN from the list:\n";
        for (i = 0; i < k; i++)
            cout << found[i].usn << endl;
        cin >> key_usn;
        flag = 0;
        for (i = 0; i < k; i++)
        {
            if (strcmp(key_usn, found[i].usn) == 0)
            {
                retrieve_record(index[i]);
                flag = 1;
            }
        }
        if (!flag)
            cout << "Invalid entry!!\n";
    }
}

void delete_record(char *indx)
{
    int i, flag;
    char ch;
    fstream f1("record.txt", ios::in);
    char index[20][20];
    for (i = 0; i < n; i++)
    {
        f1.getline(index[i], 3, '|');
        f1.getline(rec[i].usn, 10, '|');
        f1.getline(rec[i].name, 20, '|');
        f1.getline(rec[i].branch, 10, '|');
        f1.getline(rec[i].sem, 2, '\n');

        cout << f1.tellg() << endl;
    }
    flag = -1;
    for (i = 0; i < n; i++)
        if (strcmp(index[i], indx) == 0)
            flag = i;
    if (flag != n - 1)
    {
        for (i = flag; i < n; i++)
            rec[i] = rec[i + 1];
    }
    n--;
    cout << "Record deleted!!\n";
    f1.close();
    f1.open("secindex.txt", ios::out);
    fstream f2("record.txt", ios::out);
    for (i = 0; i < n; i++)
    {
        f1 << rec[i].name << "|" << rec[i].usn << "|" << i << "\n";
        f2 << i << "|" << rec[i].usn << "|" << rec[i].name << "|" << rec[i].branch << "|" << rec[i].sem << "\n";
    }
    f1.close();
    f2.close();
}
void del()
{
    int k = 0, i, flag;
    fstream f1("secindex.txt", ios::in);
    char name[20], usn[10], ind[3], key_usn[10], key_name[20];
    char index[20][20];
    cout << "Enter the name to delete: ";
    cin >> key_name;
    for (i = 0; i < n; i++)
    {
        f1.getline(name, 20, '|');
        f1.getline(usn, 10, '|');
        f1.getline(ind, 3, '\n');
        if (strcmp(key_name, name) == 0)
        {
            strcpy(found[k].name, name);
            strcpy(found[k].usn, usn);
            strcpy(index[k], ind);
            k++;
        }
    }
    f1.close();
    if (k == 0)
        cout << "Deletion failed!!\n";
    else if (k == 1)
        delete_record(index[0]);
    else
    {
        cout << "Choose USN from the list:\n";
        for (i = 0; i < k; i++)
            cout << found[i].usn << endl;
        cin >> key_usn;
        flag = 0;
        for (i = 0; i < k; i++)
        {
            if (strcmp(key_usn, found[i].usn) == 0)
            {
                delete_record(index[i]);
                flag = 1;
            }
        }
        if (!flag)
            cout << "Invalid entry!!\n";
    }
}
int main()
{
    int ch;
    cout << "1:Add\n2:Search\n3:Delete\n4:Exit\n";
    do
    {
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            add();
            sort_records();
            create_file();
            break;

        case 2:
            search();
            break;

        case 3:
            del();
            break;

        case 4:
            remove("secindex.txt");
            remove("record.txt");
            break;
        }
    } while (ch != 4);
    return 0;
}
