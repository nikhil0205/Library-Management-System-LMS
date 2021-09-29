#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

void initial_setup();

class Book {
        public:
        string     book_name;
        string     book_author;
        int        num_of_copies;
};


class Employee {
        public:
        string  employee_name;
        int     employee_age;
        int     employee_salary;
        string  employee_role;
        string  employee_address;
};

class Employee_database {        
        public:
        fstream employee_record;
        int employee_count = 0;
        Employee employee_array[100];

        void staff_management();
        void create_employee_record();
        void update_employee_record();
        void delete_employee_record();
        void show_all_employee_record();
        void update_employee_catalog();
};

class Library_database {
        public:
        fstream book_record;
        int book_count = 0;
        Book book_array[100];

        public:
        void book_management();
        void book_issue_and_return_interface();
        void check_availability_interface();        
        void calculate_fine_interface();
        void get_book_count();
        void create_book_record();
        void update_book_record();
        void delete_book_record();
        void update_book_catalog();
        void book_issue();
        void book_return();
        void show_book_stock();
};

//Global variables
Library_database library;
Employee_database employee;


void Library_database::show_book_stock() {
        int total_books = 0;
        
        for(int i = 0; i < book_count; i++) {
                total_books += book_array[i].num_of_copies;
        }

        cout << "\n\t\tCurrent book count is: " << book_count << endl;
        cout << "\t\tTotal number of books in the library: " << total_books << endl;
        for (int i = 0; i < book_count; i++) {
                cout << "\t\tBook name:     " << book_array[i].book_name << endl;
                cout << "\t\tAuthor name:   " << book_array[i].book_author << endl;
                cout << "\t\tNum of copies: " << book_array[i].num_of_copies << endl;
                cout << endl;
        }
}
void Library_database::book_management() {        
        cout << "\n\n";
        cout << "\t\tWelcome to book management inteface\n";
        cout << "\t\t-----------------------------------\n";
        cout << "\t\tWhat would you like to do: \n";
        cout << "\t\t1. Create new book record\n";
        cout << "\t\t2. Update existing book record\n";
        cout << "\t\t3. Delete book record\n";
        cout << "\t\t4. Show current books stock\n";
        cout << "\t\t5. Go back to main menu\n";

        int book_management_menu_choice;
        label:
        cout << "\t\tPlease enter your choice by entering the menu number(1-5): ";
        cin >> book_management_menu_choice;
        if (book_management_menu_choice <= 0 || book_management_menu_choice > 5) {
                cout << "\t\tInvalid choice. Please enter a number between 1 to 5\n";
                goto label;
        }

        switch(book_management_menu_choice) {
                case 1: 
                        Library_database::create_book_record();
                        Library_database::book_management();
                        break;
                case 2:
                        Library_database::update_book_record();
                        Library_database::book_management();
                        break;
                case 3:
                        Library_database::delete_book_record();
                        Library_database::book_management();
                        break;
                case 4:
                        Library_database::show_book_stock();
                        Library_database::book_management();
                case 5:
                        initial_setup();
                        break;
                default: 
                        break;
        }    
}

void Library_database::book_issue_and_return_interface() {
        cout << "\n\n";
        cout << "\t\tWelcome to book issue and return inteface\n";
        cout << "\t\t-----------------------------------------\n";
        cout << "\t\tWhat would you like to do: \n";
        cout << "\t\t1. Issue a book\n";
        cout << "\t\t2. Return a book\n";
        cout << "\t\t3. Go back to main menu\n";

        int book_issue_menu_choice;
        label:
        cout << "\t\tPlease enter your choice by entering the menu number(1 to 3): ";
        cin >> book_issue_menu_choice;
        if (book_issue_menu_choice <= 0 || book_issue_menu_choice > 3) {
                cout << "\t\tInvalid choice. Please enter a number between 1 to 3\n";
                goto label;
        }

        switch(book_issue_menu_choice) {
                case 1: 
                        Library_database::book_issue();
                        break;
                case 2:
                        Library_database::book_return();
                        break;
                case 3:
                        initial_setup();
                        break;
                default: 
                        break;
        }
}

void Library_database::check_availability_interface() {
        string sample_book_name;
        findbook:
        cout << "\t\tPlease enter the name of the book you would like to check availability for: ";
        cin >> sample_book_name;
        cout << "\t\tChecking the library database for the availability of this book... \n";

        bool book_found = false;
        for (int i = 0; i < book_count; i++) {
                if (book_array[i].book_name == sample_book_name) {
                        book_found = true;
                        cout << "\t\tBook found in database!!!\n";
                        cout << "\t\tChecking for number of copies available...\n";
                        cout << "\t\tNumber of copies available for this book are: " << book_array[i].num_of_copies << endl;
                        break;
                }
        }
        
        int choice;
        if (!book_found) {
                cout << "\n\t\tSorry! no such book found. Try again/Go back (1/0): ";
                cin >> choice;
                if (choice == 1) goto findbook;
                else initial_setup();
        }
        Library_database::update_book_catalog();
}
        
void Library_database::calculate_fine_interface() {
        string issue_date;
        string return_date;
        string due_date;

        cout << "\n\n";
        cout << "\t\tWelcome to fine calculation inteface\n";
        cout << "\t\t------------------------------------\n";
        label:
        cout << "\t\tEnter issue date(dd/mm/yyyy or dd-mm-yyyy): ";
        cin >> issue_date;
        int issue_d = stoi(issue_date.substr(0, 2));
        int issue_m = stoi(issue_date.substr(3, 2));
        int issue_y = stoi(issue_date.substr(6, 4));

        if (issue_d > 31 || issue_m > 12) {
                cout << "\t\tInvalid date. Try again...\n";
                goto label;
        }
        
        label2:
        cout << "\t\tEnter return date(dd/mm/yyyy or dd-mm-yyyy): ";
        cin >> return_date;
        int return_d = stoi(return_date.substr(0, 2));
        int return_m = stoi(return_date.substr(3, 2));
        int return_y = stoi(return_date.substr(6, 4));

        if (return_d > 31 || return_m > 12) {
                cout << "\t\tInvalid date. Try again...\n";
                goto label2;
        }
        
        int due_d = issue_d + 7;
        int due_m = issue_m;
        int due_y = issue_y;

        long long time_span_1 = ((return_y - 2000) * 365) + ((return_m - 1) * 30) + (return_d - 1);
        long long time_span_2 = ((due_y - 2000) * 365) + ((due_m - 1) * 30) + (due_d - 1);
        long long extra_days = time_span_1 - time_span_2;
        
        if (due_d > 30) {
                due_d = due_d % 30;
                due_m = due_m + 1;
                if (due_m > 12) {
                        due_m = due_m % 12;
                        due_y = due_y + 1;
                }
        }

        due_date = to_string(due_d) + "/" + to_string(due_m) + "/" + to_string(due_y);
        cout << "\t\tYour due date was: " << due_date << endl;
        if (extra_days < 0) {
                cout << "\t\tNumber of extra days: 0";
                cout << "\t\tYou returned the book before the due date. So your fine is Rs. 0\n";
        } else {
                long long fine = extra_days * 15;
                cout << "\t\tNumber of extra days: " << extra_days << endl;
                cout << "\t\tPer day fine = Rs.15. Your total fine is: " << fine << endl;
        }

        int choice;
        cout << "\n\t\tCalculate another fine? Yes/No (1/0): ";
        cin >> choice;
        if (choice == 1) calculate_fine_interface();
        else initial_setup();
}

void Library_database::update_book_catalog() {
        book_record.open("book_record.txt", ios::out);
        for (int i = 0; i < book_count; i++) {
                book_record << "Book name:                  " << book_array[i].book_name;
                book_record << "\n";
                book_record << "Book Author:                " << book_array[i].book_author;
                book_record << "\n";
                book_record << "Number of copies available: " << book_array[i].num_of_copies;
                book_record << "\n";
        }
}
void Library_database::create_book_record() {
        Book b1;
        this->book_count++;
        
        //string x, y;
        cout << "\n\n";
        cout << "\t\tEnter the name of the book you want to add to the Library: ";
        cin >> b1.book_name;
        cout << "\t\tEnter author's name: ";
        cin >> b1.book_author;

        cout << "\t\tEnter the number of copies: ";
        cin >> b1.num_of_copies;
        
        book_array[book_count - 1] = b1;
        Library_database::update_book_catalog();
        //Library_database::show_book_stock();
        cout << "\n";
        cout << "\t\tNew record successfully created for the book " << b1.book_name << "!!!"; 
}

void Library_database::update_book_record() {
        string sample_book_name;
        int target_index;
        bool book_found = false;
        
        findbook:
        cout << "\t\tEnter the name of book you want to update record for: ";
        cin >> sample_book_name;
        for (int i = 0; i < book_count; i++) {
                if (book_array[i].book_name == sample_book_name) {
                        cout << "\t\tBook found in database. Book now in target for making changes...\n";
                        book_found = true;
                        target_index = i;
                        break;
                }
        }
        int choice;
        if (!book_found) {
                cout << "\t\tSorry! no such book found. Try again/Go back (1/0): ";
                cin >> choice;
                if (choice == 1) goto findbook;
                else Library_database::book_management();
        }
        cout << "\t\tWhat changes would you like to make for this book?\n";
        cout << "\t\t1. Change name\n";
        cout << "\t\t2. Change author name\n";
        cout << "\t\t3. Change number of copies\n";
        cout << "\t\t4. Go back\n";

        int update_book_menu_choice;
        label:
        cout << "\t\tPlease enter your choice by entering the menu number(1-4): ";
        cin >> update_book_menu_choice;
        if (update_book_menu_choice <= 0 || update_book_menu_choice > 4) {
                cout << "\t\tInvalid choice. Please enter a number between 1 to 4\n";
                goto label;
        }

        switch(update_book_menu_choice) {
                case 1: 
                        cout << "\t\tEnter new name for the book: ";
                        cin >> book_array[target_index].book_name;
                        break;
                case 2:
                        cout << "\t\tEnter the new author name for the book: ";
                        cin >> book_array[target_index].book_author;
                case 3:
                        cout << "\t\tEnter the new number of copies: ";
                        cin >> book_array[target_index].num_of_copies;
                        break;
                case 4:
                        Library_database::book_management();
                        break;
                default: 
                        break;
        }
        Library_database::update_book_catalog();
}

void Library_database::delete_book_record() {
        string sample_book_name;
        int target_index;
        bool book_found = false;
        
        findbook:
        cout << "\t\tEnter the name of book you want to delete record for: ";
        cin >> sample_book_name;
        int choice;
        for (int i = 0; i < book_count; i++) {
                if (book_array[i].book_name == sample_book_name) {
                        cout << "\n\t\tBook found in database. Book now in target for deleting...\n";
                        cout << "\t\tAre you sure you want to delete record for this book? Yes/No (1/0): ";
                        cin >> choice;
                        if (choice == 1) {
                                cout << "\t\tDeleting book record in progress...\n";
                                cout << "\t\tBook record deleted successfully!!!\n";
                        } else {
                                cout << "\t\tBook record deletion cancelled\n";
                                Library_database::book_management();
                        }
                        book_found = true;
                        target_index = i;
                        break;
                }
        }
        
        if (!book_found) {
                cout << "\t\tSorry! no such book found. Try again/Go back (1/0): ";
                cin >> choice;
                if (choice == 1) goto findbook;
                else Library_database::book_management();
        }

        for (int i = target_index + 1; i < book_count; i++) {
                book_array[i - 1] = book_array[i];
        }
        book_count--;
        Library_database::update_book_catalog();
        Library_database::show_book_stock();
}

void Library_database::book_issue() {
        string sample_book_name;
        findbook:
        cout << "\t\tPlease enter the name of the book you would like to issue: ";
        cin >> sample_book_name;
        cout << "\t\tChecking the library database for the availability of this book... \n";

        bool book_found = false;
        string issuer_name;
        
        for (int i = 0; i < book_count; i++) {
                if (book_array[i].book_name == sample_book_name) {
                        book_found = true;
                        cout << "\t\tBook found in database!!!\n";
                        cout << "\t\tChecking for number of copies available...\n";
                        if (book_array[i].num_of_copies > 0) {
                                cout << "\t\tBook available for issue!\n";
                                cout << "\t\tPlease enter your name: ";
                                cin >> issuer_name;
                                cout << "\t\tIssuing book " << sample_book_name;
                                cout << " (author: " << book_array[i].book_author << ")" << " to " << issuer_name;
                                cout << "\t\t\nBook issued successfully!!!\n";
                                book_array[i].num_of_copies--;
                        } else {
                                cout << "\n\t\tSorry book is currently unavailable... Please come back later!\n"; 
                                Library_database::book_issue_and_return_interface();
                        }
                        break;
                }
        }
        
        int choice;
        if (!book_found) {
                cout << "\n\t\tSorry! no such book found. Try again/Go back (1/0): ";
                cin >> choice;
                if (choice == 1) goto findbook;
                else Library_database::book_issue_and_return_interface();
        }
        Library_database::update_book_catalog();
}

void Library_database::book_return() {
        string sample_book_name;
        findbook:
        cout << "\t\tPlease enter the name of the book you would like to return: ";
        cin >> sample_book_name;
        for (int i = 0; i < book_count; i++) {
                if (book_array[i].book_name == sample_book_name) {
                        book_array[i].num_of_copies++;
                        break;
                }
        }
        cout << "\t\tBook returned to library succesfully!!!\n";
        Library_database::update_book_catalog();
}

void Employee_database::staff_management() {
        cout << "\n\n";
        cout << "\t\tWelcome to Employee management inteface\n";
        cout << "\t\t-----------------------------------\n";
        cout << "\t\tWhat would you like to do: \n";
        cout << "\t\t1. Create new employee record\n";
        cout << "\t\t2. Update existing employee record\n";
        cout << "\t\t3. Delete employee record\n";
        cout << "\t\t4. Show all employee record\n";
        cout << "\t\t5. Go back to main menu\n";

        int employee_management_menu_choice;
        label:
        cout << "\t\tPlease enter your choice by entering the menu number(1-5): ";
        cin >> employee_management_menu_choice;
        if (employee_management_menu_choice <= 0 || employee_management_menu_choice > 5) {
                cout << "\t\tInvalid choice. Please enter a number between 1 to 5\n";
                goto label;
        }

        switch(employee_management_menu_choice) {
                case 1: 
                        Employee_database::create_employee_record();
                        Employee_database::staff_management();
                        break;
                case 2:
                        Employee_database::update_employee_record();
                        Employee_database::staff_management();
                        break;
                case 3:
                        Employee_database::delete_employee_record();
                        Employee_database::staff_management();
                        break;
                case 4:
                        Employee_database::show_all_employee_record();
                        Employee_database::staff_management();
                case 5:
                        initial_setup();
                        break;
                default: 
                        break;
        }
}

void Employee_database::update_employee_catalog() {
        employee_record.open("employee_record.txt", ios::out);
        for (int i = 0; i < employee_count; i++) {
                employee_record << "\t\tEmployee Name:    "  << employee_array[i].employee_name << endl;;
                employee_record << "\t\tEmployee age:     "  << employee_array[i].employee_age << endl;
                employee_record << "\t\tEmployee Address: "  << employee_array[i].employee_address << endl;
                employee_record << "\t\tEmployee Role:    "  << employee_array[i].employee_role << endl;
                employee_record << "\t\tEmployee salary:  "  << employee_array[i].employee_salary << endl;
                employee_record << "\n\n";
        }
}
void Employee_database::create_employee_record() {
        Employee e1;
        this->employee_count++;
        
        cout << "\n\n";
        cout << "\t\tEnter the name of the Employee: ";
        cin >> e1.employee_name;
        cout << "\t\tEnter employees's age: ";
        cin >> e1.employee_age;
        cout << "\t\tEnter employee's address: ";
        cin >> e1.employee_address;
        cout << "\t\tEnter employee's role: ";
        cin >> e1.employee_role;
        cout << "\t\tEnter employee's salary: ";
        cin >> e1.employee_salary;

        
        employee_array[employee_count - 1] = e1;
        Employee_database::update_employee_catalog();
        //Library_database::show_book_stock();
        cout << "\n";
        cout << "\t\tNew record successfully created for the employee " << e1.employee_name << "!!!"; 
}

void Employee_database::show_all_employee_record () {
        int total_employees = 0;
        
        cout << "\t\tTotal number of books in the library: " << total_employees << endl;
        for (int i = 0; i < employee_count; i++) {
                cout << "\t\tEmployee Name:    "  << employee_array[i].employee_name << endl;
                cout << "\t\tEmployee age:     "  << employee_array[i].employee_age << endl;
                cout << "\t\tEmployee Address: "  << employee_array[i].employee_address << endl;
                cout << "\t\tEmployee Role:    "  << employee_array[i].employee_role << endl;
                cout << "\t\tEmployee salary:  "  << employee_array[i].employee_salary << endl;
                cout << "\n\n";
        }
}

void Employee_database::update_employee_record() {
        string sample_employee_name;
        int target_index;
        bool employee_found = false;
        
        findemployee:
        cout << "\t\tEnter the name of employee you want to update record for: ";
        cin >> sample_employee_name;
        for (int i = 0; i < employee_count; i++) {
                if (employee_array[i].employee_name == sample_employee_name) {
                        cout << "\t\tEmployee found in database. Employee now in target for making changes...\n";
                        employee_found = true;
                        target_index = i;
                        break;
                }
        }
        int choice;
        if (!employee_found) {
                cout << "\t\tSorry! no such employee found. Try again/Go back (1/0): ";
                cin >> choice;
                if (choice == 1) goto findemployee;
                else Employee_database::staff_management();
        }
        cout << "\t\tWhat changes would you like to make for this employee?\n";
        cout << "\t\t1. Change employee name\n";
        cout << "\t\t2. Change employee age\n";
        cout << "\t\t3. Change employee address\n";
        cout << "\t\t4. Change employee role\n";
        cout << "\t\t5. Change employee salary\n";
        cout << "\t\t6. Go back\n";

        int update_employee_menu_choice;
        label:
        cout << "\t\tPlease enter your choice by entering the menu number(1-6): ";
        cin >> update_employee_menu_choice;
        if (update_employee_menu_choice <= 0 || update_employee_menu_choice > 6) {
                cout << "\t\tInvalid choice. Please enter a number between 1 to 6\n";
                goto label;
        }

        switch(update_employee_menu_choice) {
                case 1: 
                        cout << "\t\tEnter new name for the employee: ";
                        cin >> employee_array[target_index].employee_name;
                        break;
                case 2:
                        cout << "\t\tEnter new age for employee: ";
                        cin >> employee_array[target_index].employee_age;
                case 3:
                        cout << "\t\tEnter new adress for employee: ";
                        cin >> employee_array[target_index].employee_address;
                        break;
                case 4:
                        cout << "\t\tEnter new job role for employee: ";
                        cin >> employee_array[target_index].employee_role;
                        break;
                case 5: 
                        cout << "\t\tEnter new salary for the employee: ";
                        cin >> employee_array[target_index].employee_salary;
                        break;
                case 6:
                        Employee_database::staff_management();
                        break;
                default: 
                        break;
        }
        Employee_database::update_employee_catalog();
}

void Employee_database::delete_employee_record() {
        string sample_employee_name;
        int target_index;
        bool employee_found = false;
        
        findemployee:
        cout << "\t\tEnter the name of employee you want to delete record for: ";
        cin >> sample_employee_name;
        int choice;
        for (int i = 0; i < employee_count; i++) {
                if (employee_array[i].employee_name == sample_employee_name) {
                        cout << "\n\t\tEmployee found in database. Employee now in target for deleting...\n";
                        cout << "\t\tAre you sure you want to delete record for this employee? Yes/No (1/0): ";
                        cin >> choice;
                        if (choice == 1) {
                                cout << "\t\tDeleting employee record in progress...\n";
                                cout << "\t\temployee record deleted successfully!!!\n";
                        } else {
                                cout << "\t\temployee record deletion cancelled\n";
                                Employee_database::staff_management();
                        }
                        employee_found = true;
                        target_index = i;
                        break;
                }
        }
        
        if (!employee_found) {
                cout << "\t\tSorry! no such employee found. Try again/Go back (1/0): ";
                cin >> choice;
                if (choice == 1) goto findemployee;
                else Employee_database::staff_management();
        }

        for (int i = target_index + 1; i < employee_count; i++) {
                employee_array[i - 1] = employee_array[i];
        }
        employee_count--;
        Employee_database::update_employee_catalog();
        Employee_database::show_all_employee_record();
}

void initial_setup() {
        int menu_choice;
        cout << "\n\n\n";
        cout << "\t\t-------------------------------------------------------\n";
        cout << "\t\t|             Welcome to Library Manager              |\n";
        cout << "\t\t-------------------------------------------------------\n";

        cout << "\n\n";
        cout << "\t\tMENU: \n\n";
        cout << "\t\t1. Library books management\n";
        cout << "\t\t2. Access the employee database\n";
        cout << "\t\t3. Issue & return books \n";
        cout << "\t\t4. Library Stock Database\n";
        cout << "\t\t5. Check availability of a book or novel\n";
        cout << "\t\t6. Calculate your fine(New feature!!!)\n";
        cout << "\t\t7. Exit\n";
        cout << "\n\n";

        label:
        cout << "\t\tPlease enter your choice by entering the menu number(1-7): ";
        cin >> menu_choice;
        if (menu_choice <= 0 || menu_choice > 7) {
                cout << "\t\tInvalid choice. Please enter a number between 1 to 7\n";
                goto label;
        }
        switch(menu_choice) {
                case 1: 
                        library.book_management();
                        break;
                case 2:
                        employee.staff_management();
                        break;
                case 3:
                        library.book_issue_and_return_interface();
                        break;
                case 4:
                        library.show_book_stock();
                        break;
                case 5:
                        library.check_availability_interface();
                        break;
                case 6: 
                        library.calculate_fine_interface();
                        break;
                case 7:
                        cout << "\n\n\t\tThank you for using Library Manager. Now Exiting...\n\n";
                        return;
                        break;
                default: 
                        break;
        }
}

int main() {        
        initial_setup();
        return 0;
}
