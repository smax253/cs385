/*******************************************************************************
 * Name    : student.cpp
 * Author  : Max Shi
 * Version : 1.0
 * Date    : September 4, 2019
 * Description : Stores and displays student and class info.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Student{
public:
    Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

    string full_name() const{
        return first_ + " " + last_;
    }
    int id() const{
        return id_;
    }
    float gpa() const{
        return gpa_;
    }
    void print_info() const{
        cout << first_ << " " << last_ << ", GPA: " << fixed << setprecision(2) << 
                gpa_ << ", ID: " << id_ << endl;
    }
private:
    string first_, last_;
    float gpa_;
    int id_;
};

/**
 * Takes a vector of Student objects, and returns a new vector with 
 * all Students whose GPA is < 1.0.
 */
vector<Student> find_failing_students(const vector<Student> &students){
    vector<Student> failing_students;
    for(auto it = students.cbegin(); it != students.cend(); ++it){
        if(it->gpa() < 1.0){
            failing_students.push_back(*it);
        }
    }
    return failing_students;
}

/**
 * Takes a vector of Student objects and prints them to the screen.
 */
void print_students(const vector<Student> &students){
    for (size_t i = 0; i<students.size(); i++){
        students[i].print_info();
    }
}
/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen.
*/
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:";
    vector<Student> failing_students = find_failing_students(students);
    if(failing_students.size() == 0) cout << " None";
    else{
        cout << endl;
        print_students(failing_students);
    } 
    
    return 0;
}