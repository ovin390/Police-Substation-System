#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const char DELIMITER = '|';

class officer {
public:
    string ssid;
    string oid;
    string name;
    int age;
    string rank;
    string dob;


    officer() {}

    officer(const string& oid, const string& ssid, const string& name, int age, const string& rank, const string& dob)
        : oid(oid), ssid(ssid), name(name), age(age), rank(rank), dob(dob) {}

    void display() const {
        cout << "Substation id: " << ssid << endl;
        cout << "Officer id: " << oid << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Rank: " << rank << endl;
        cout << "DOB: " << dob << endl;
    }
};

class substation {
public:
    string sid;
    string sname;


    substation() {}

    substation(const string& sid, const string& sname)
        : sid(sid), sname(sname) {}

    void display() const {
        cout << "Substation id: " << sid << endl;
        cout << "Name: " << sname << endl;
    }
};

class Database {
private:
    string filename;

public:
    Database(const string& filename) : filename(filename) {}

    void addRecord(const string& serializedRecord) {
        fstream file(filename, ios::app);
        if (!file) {
            
            cout << "Error opening file." << endl;
            return;
            
        }

        file << serializedRecord << endl;
        

        cout << "Record added successfully!" << endl;
        file.close();
    }
    bool isDuplicateSid(const string& sid) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);//A stringstream associates a string object with a stream allowing you to read from the string 
        string token;

        getline(ss, token, DELIMITER);
        if (token == sid) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
bool isDuplicateOid(const string& oid){
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return false;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, DELIMITER);
        if (token == oid) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;

}


    void searchRecord(int rrn) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        int currentRRN = 1;
        bool found = false;

        while (getline(file, line)) {
            if (currentRRN == rrn) {
                found = true;
                break;
            }
            currentRRN++;
        }

        if (found) {
            cout << "Record Details:" << endl;
            cout << line << endl;
        } else {
            cout << "Record not found." << endl;
        }

        file.close();
    }

    void displayAllRecords() {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        int currentRRN = 1;

        while (getline(file, line)) {
            cout << "RRN: " << currentRRN << endl;
            cout << "Record Details:" << endl;
            cout << line << endl;
            currentRRN++;
        }

        file.close();
    }

    void deleteRecord(int rrn) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        int currentRRN = 1;
        bool found = false;

        ofstream tempFile("temp.txt", ios::out);
        if (!tempFile) {
            cout << "Error opening file." << endl;
            file.close();
            return;
        }

        while (getline(file, line)) {
            if (currentRRN != rrn) {
                tempFile << line << endl;
            } else {
                found = true;
            }
            currentRRN++;
        }

        file.close();
        tempFile.close();

        if (found) {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            cout << "Record deleted successfully!" << endl;
        } else {
            cout << "Record not found." << endl;
        }
    }

    void modifyOfficer(int rrn) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        int currentRRN = 1;
        bool found = false;

        ofstream tempFile("temp.txt", ios::out);
        if (!tempFile) {
            cout << "Error opening file." << endl;
            file.close();
            return;
        }

        while (getline(file, line)) {
            if (currentRRN == rrn) {
                found = true;
                officer of;
                stringstream ss(line);
                string token;

                getline(ss, token, DELIMITER);
                of.ssid = token;

                getline(ss, token, DELIMITER);
                of.oid = token;

                getline(ss, token, DELIMITER);
                of.name = token;

                getline(ss, token, DELIMITER);
                of.age = stoi(token);

                getline(ss, token, DELIMITER);
                of.rank = token;

                getline(ss, token, DELIMITER);
                of.dob = token;

                string ssid, oid, name, rank, dob;
                int age;

                cout << "\nCurrent Substation id: " << of.ssid << endl;
                cout << "Enter new Substation id: ";
                cin.ignore();
                getline(cin, ssid);

                cout << "\nCurrent Officer id: " << of.oid << endl;
                cout << "Enter new officer id: ";
                getline(cin, oid);

                cout << "\nCurrent Name: " << of.name << endl;
                cout << "Enter new Name: ";
                getline(cin, name);

                cout << "Current Age: " << of.age << endl;
                cout << "Enter new Age: ";
                cin >> age;

                cout << "\nCurrent Rank : " << of.rank << endl;
                cout << "Enter new Rank : ";
                cin.ignore();
                getline(cin, rank);

                cout << "Current Dob: " << of.dob << endl;
                cout << "Enter new Dob: ";
                getline(cin, dob);

                of = officer(ssid, oid, name, age, rank, dob);
                line = of.ssid + DELIMITER + of.oid + DELIMITER + of.name + DELIMITER + to_string(of.age) +
                       DELIMITER + of.rank + DELIMITER + of.dob;
            }
            tempFile << line << endl;
            currentRRN++;
        }

        file.close();
        tempFile.close();

        if (found) {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            cout << "Record modified successfully!" << endl;
        } else {
            cout << "Record not found." << endl;
        }
    }

    void modifySubstation(int rrn) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        int currentRRN = 1;
        bool found = false;

        ofstream tempFile("temp.txt", ios::out);
        if (!tempFile) {
            cout << "Error opening file." << endl;
            file.close();
            return;
        }

        while (getline(file, line)) {
            if (currentRRN == rrn) {
                found = true;
                substation sb;
                stringstream ss(line);
                string token;

                getline(ss, token, DELIMITER);
                sb.sid = token;

                getline(ss, token, DELIMITER);
                sb.sname = token;

                string sid, sname;

                cout << "\nCurrent substation id: " << sb.sid << endl;
                cout << "Enter new substation id: ";
                cin.ignore();
                getline(cin, sid);

                cout << "Current name: " << sb.sname << endl;
                cout << "Enter new name: ";
                getline(cin, sname);

                sb = substation(sid, sname);
                line = sb.sid + DELIMITER + sb.sname;
            }
            tempFile << line << endl;
            currentRRN++;
        }

        file.close();
        tempFile.close();

        if (found) {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            cout << "Record modified successfully!" << endl;
        } else {
            cout << "Record not found." << endl;
        }
    }
};

int main() {
    Database officerDB("officer.txt");// class and object
    Database substationDB("substation.txt");

    while (true) {
        cout << "\n*** Menu ***" << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. Add officer" << endl;
        cout << "2. Search officer" << endl;
        cout << "3. Display All officer" << endl;
        cout << "4. Delete officer" << endl;
        cout << "5. Modify officer" << endl;
        cout << "-------------------------------------" << endl;
        cout << "6. Add substation" << endl;
        cout << "7. Search substation" << endl;
        cout << "8. Display All substation" << endl;
        cout << "9. Delete substation" << endl;
        cout << "10. Modify substation" << endl;
        cout << "-------------------------------------" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n*** Add officer ***" << endl;

                cout << "Enter officer id: ";
                string oid;
                cin.ignore();//used to clear one or more characther from input buffer
                getline(cin, oid);

                

                if (officerDB.isDuplicateOid(oid)) {
        cout << "Error: Duplicate officer id found." << endl;
    }else{
        cout << "Enter substation id: ";
                string ssid;
                getline(cin, ssid);
        cout << "Enter officer name: ";
                string name;
                // cin.ignore();
                getline(cin, name);

                cout << "Enter officer age: ";
                int age;
                cin >> age;

                cout << "Enter officer rank: ";
                string rank;
                cin.ignore();
                getline(cin, rank);

                cout << "Enter officer Dob: ";
                string dob;
                /*cin.ignore();*/
                getline(cin, dob);
                 officer of(oid, ssid, name, age, rank, dob);
                officerDB.addRecord(of.oid + DELIMITER + of.ssid + DELIMITER + of.name + DELIMITER +to_string(of.age) + DELIMITER + of.rank + DELIMITER + of.dob);

    }
     
                break;
            }
            case 2: {
                cout << "\n*** Search officer ***" << endl;
                cout << "Enter RRN (Relative Record Number) of the officer: ";
                int rrn;
                cin >> rrn;

                officerDB.searchRecord(rrn);
                break;
            }
            case 3: {
                cout << "\n*** Display All officer ***" << endl;
                officerDB.displayAllRecords();
                break;
            }
            case 4: {
                cout << "\n*** Delete officer ***" << endl;
                cout << "Enter RRN (Relative Record Number) of the officer to delete: ";
                int rrn;
                cin >> rrn;

                officerDB.deleteRecord(rrn);
                break;
            }
            case 5: {
                cout << "\n*** Modify officer ***" << endl;
                cout << "Enter RRN (Relative Record Number) of the officer to modify: ";
                int rrn;
                cin >> rrn;

                officerDB.modifyOfficer(rrn);
                break;
            }
            case 6: {
                cout << "\n*** Add substation ***" << endl;

    cout << "Enter substation id: ";
    string sid;
    cin.ignore();
    getline(cin, sid);

    if (substationDB.isDuplicateSid(sid)) {
        cout << "Error: Duplicate substation id found." << endl;
    } else {
        cout << "Enter substation name: ";
        string sname;
        getline(cin, sname);

        substation sb(sid, sname);
        substationDB.addRecord(sb.sid + DELIMITER + sb.sname);
    }
    break;
            }
            case 7: {
                cout << "\n*** Search substation ***" << endl;
                cout << "Enter RRN (Relative Record Number) of the substation: ";
                int rrn;
                cin >> rrn;

                substationDB.searchRecord(rrn);
                break;
            }
            case 8: {
                cout << "\n*** Display All substation ***" << endl;
                substationDB.displayAllRecords();
                break;
            }
            case 9: {
                cout << "\n*** Delete substation ***" << endl;
                cout << "Enter RRN (Relative Record Number) of the substation to delete: ";
                int rrn;
                cin >> rrn;

                substationDB.deleteRecord(rrn);
                break;
            }
            case 10: {
                cout << "\n*** Modify substation ***" << endl;
                cout << "Enter RRN (Relative Record Number) of the substation to modify: ";
                int rrn;
                cin >> rrn;

                substationDB.modifySubstation(rrn);
                break;
            }
            case 11: {
                cout << "\nExiting the program..." << endl;
                return 0;
            }
            default:
                cout << "\nInvalid choice. Please try again." << endl;
                break;
        }
    }
}
