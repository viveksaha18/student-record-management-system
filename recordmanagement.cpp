#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Class for Student Record
class Student {
    int rollNo;
    string name;
    string className;
    float marks;

public:
    void inputData();    // Input student data
    void displayData();  // Display student data
    int getRollNo();     // Get Roll Number

    // File Operations
    void addRecord();
    void displayAllRecords();
    void searchRecord(int roll);
    void modifyRecord(int roll);
    void deleteRecord(int roll);
};

void Student::inputData() {
    cout << "Enter Roll Number: ";
    cin >> rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Class: ";
    cin >> className;
    cout << "Enter Marks: ";
    cin >> marks;
}

void Student::displayData() {
    cout << "Roll Number: " << rollNo << endl;
    cout << "Name: " << name << endl;
    cout << "Class: " << className << endl;
    cout << "Marks: " << marks << endl;
    cout << "---------------------------" << endl;
}

int Student::getRollNo() {
    return rollNo;
}

// Add a record to the file
void Student::addRecord() {
    ofstream file("students.dat", ios::binary | ios::app);
    inputData();
    file.write((char *)this, sizeof(*this));
    file.close();
    cout << "Record added successfully!" << endl;
}

// Display all records
void Student::displayAllRecords() {
    ifstream file("students.dat", ios::binary);
    if (!file) {
        cout << "No records found!" << endl;
        return;
    }
    while (file.read((char *)this, sizeof(*this))) {
        displayData();
    }
    file.close();
}

// Search for a record
void Student::searchRecord(int roll) {
    ifstream file("students.dat", ios::binary);
    bool found = false;
    while (file.read((char *)this, sizeof(*this))) {
        if (getRollNo() == roll) {
            cout << "Record Found:" << endl;
            displayData();
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Record not found!" << endl;
    file.close();
}

// Modify a record
void Student::modifyRecord(int roll) {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    while (file.read((char *)this, sizeof(*this))) {
        if (getRollNo() == roll) {
            cout << "Record Found. Enter new details:" << endl;
            inputData();
            int pos = -1 * static_cast<int>(sizeof(*this));
            file.seekp(pos, ios::cur);
            file.write((char *)this, sizeof(*this));
            found = true;
            cout << "Record updated successfully!" << endl;
            break;
        }
    }
    if (!found)
        cout << "Record not found!" << endl;
    file.close();
}

// Delete a record
void Student::deleteRecord(int roll) {
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read((char *)this, sizeof(*this))) {
        if (getRollNo() == roll) {
            found = true;
        } else {
            outFile.write((char *)this, sizeof(*this));
        }
    }
    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully!" << endl;
    else
        cout << "Record not found!" << endl;
}

int main() {
    Student student;
    int choice, roll;

    do {
        cout << "\nStudent Record Management System\n";
        cout << "1. Add Record\n";
        cout << "2. Display All Records\n";
        cout << "3. Search Record\n";
        cout << "4. Modify Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                student.addRecord();
                break;
            case 2:
                student.displayAllRecords();
                break;
            case 3:
                cout << "Enter Roll Number to search: ";
                cin >> roll;
                student.searchRecord(roll);
                break;
            case 4:
                cout << "Enter Roll Number to modify: ";
                cin >> roll;
                student.modifyRecord(roll);
                break;
            case 5:
                cout << "Enter Roll Number to delete: ";
                cin >> roll;
                student.deleteRecord(roll);
                break;
            case 6:
                cout << "Exiting the system." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}
