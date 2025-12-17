#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/* ---------- EMPLOYEE BASE CLASS ---------- */
class Employee {
protected:
    int id;
    string name;
    int leavesTaken;

public:
    Employee(int id, string name) {
        this->id = id;
        this->name = name;
        leavesTaken = 0;
    }

    virtual double calculateSalary() = 0;

    void applyLeave(int days) {
        leavesTaken += days;
    }

    virtual void display() {
        cout << "ID: " << id << " | Name: " << name
             << " | Leaves Taken: " << leavesTaken << endl;
    }

    int getId() { return id; }
};

/* ---------- FULL TIME EMPLOYEE ---------- */
class FullTimeEmployee : public Employee {
    double basicSalary;

public:
    FullTimeEmployee(int id, string name, double salary)
        : Employee(id, name) {
        basicSalary = salary;
    }

    double calculateSalary() override {
        double deduction = leavesTaken * 500;
        return basicSalary - deduction;
    }
};

/* ---------- INTERN ---------- */
class Intern : public Employee {
    double stipend;

public:
    Intern(int id, string name, double stipend)
        : Employee(id, name) {
        this->stipend = stipend;
    }

    double calculateSalary() override {
        return stipend;
    }
};

/* ---------- MAIN ---------- */
int main() {
    vector<Employee*> employees;
    int choice;

    do {
        cout << "\n1. Add Full-Time Employee";
        cout << "\n2. Add Intern";
        cout << "\n3. Apply Leave";
        cout << "\n4. View Employees";
        cout << "\n5. Calculate Payroll";
        cout << "\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            double salary;
            cout << "Enter ID, Name, Salary: ";
            cin >> id >> name >> salary;
            employees.push_back(new FullTimeEmployee(id, name, salary));
        }

        else if (choice == 2) {
            int id;
            string name;
            double stipend;
            cout << "Enter ID, Name, Stipend: ";
            cin >> id >> name >> stipend;
            employees.push_back(new Intern(id, name, stipend));
        }

        else if (choice == 3) {
            int id, days;
            cout << "Enter Employee ID and Leave Days: ";
            cin >> id >> days;
            for (auto emp : employees) {
                if (emp->getId() == id) {
                    emp->applyLeave(days);
                    cout << "Leave applied.\n";
                }
            }
        }

        else if (choice == 4) {
            for (auto emp : employees)
                emp->display();
        }

        else if (choice == 5) {
            for (auto emp : employees) {
                emp->display();
                cout << "Net Salary: " << emp->calculateSalary() << endl;
            }
        }

    } while (choice != 6);

    return 0;
}
