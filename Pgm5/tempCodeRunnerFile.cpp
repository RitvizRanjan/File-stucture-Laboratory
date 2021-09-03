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
    f1.getline(brn, 20, '|');
    f1.getline(sem, 10, '|');
    f1.close();
}
void stud::del()
{
    char usn[10];
    fstream f1("index.txt", ios::out | ios::trunc);
    cout << "\nenter usn to delete:";
    cin >> usn;