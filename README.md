# algo
// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Student{
    public:
    string name = "";
    string enrollment;
    int test = 0;
    int matric = 0;
    int inter = 0;
    int total = 0;
    int get_total_marks(){
        return test+matric+inter;
    }
    
    void show(){
        cout<<"\n\n";
        cout<<"Name => "<<name;
        cout<<"\nEnrollment => "<<enrollment;
        if(total == 0)
        {
            total = get_total_marks();
        }
        cout<<"\nMarks => "<<total<<"\n";
    }
};

int student_capacity = 10;
int enrolled_students = 0;
list<Student> students;
list<Student>::iterator reader;


struct StudentComparator
{
    // Compare 2 Player objects using name
    bool operator ()(const Student & st1, const Student & st2)
    {
        if(st1.total == st2.total)
        {
            return st1.name < st2.name;
        }
        return st1.total > st2.total;
    }
};


void add_student(){
    int total_test_marks = 100;
    int total_matric_marks = 1050;
    int total_inter_marks = 1100;
    Student st;
    cout << "\n\n\n Enter student name => ";
    cin >> st.name;
    cout << "\nEnter enrollment => ";
    cin >> st.enrollment;
    cout << "\nEntery test marks => ";
    cin >> st.test;
    cout << "\nMatriculation marks => ";
    cin >> st.matric;
    cout << "\nIntermideate marks => ";
    cin >> st.inter;
    st.total = st.get_total_marks();
    students.insert(students.begin(), st);
    students.sort(StudentComparator());
    enrolled_students += 1;
}


Student get_student(string enrollment){
    Student st;
    int found = 0;
    for (reader = students.begin(); reader != students.end(); ++reader){
        if(reader->enrollment == enrollment){
            st = *reader;
            found = 1;
            break;
        }
    }
    if(found != 1){
        cout<<"\n\nStudnent NOT found by enrollment => "<<enrollment;
        return st;
    }
    cout<<"\n\nStudnent found by enrollment => "<<enrollment;
    st.show();
    return st;
}


void show_top_students(int cnt){
    Student st;
    int found = 0;
    if (cnt > enrolled_students){
        cnt = enrolled_students;
    }
    //students.sort(StudentComparator());
    int i = 1;
    for (reader = students.begin(); reader != students.end(); ++reader){
        if(i > cnt){
            break;
        }
        reader->show();
        i += 1;
    }
    cout<<"\n Stundents shown => "<<enrolled_students;
}

int main() {
    
    int cnt;
    char option;
    string enrollment;
    
    int turns = 1;
    while(option != 'q' && turns < 15){
        cout <<"\n\n Press 1 to Add student";
        cout <<"\n Press 2 to Give number to get top students";
        cout <<"\n Press 3 to Give enrollment to get student";
        cout <<"\n Press q to quit";
        cout <<" => ";
        cin >> option;
        switch(option){
            case '1':
                add_student();
                cout << "\n\n Will add student";
                break;
            case '2':
                cout << "\n\n Enter count of top students => ";
                cin >> cnt;
                show_top_students(cnt);
                break;
            case '3':
                cout << "\n\n Enter enrollment to find student => ";
                cin >> enrollment;
                get_student(enrollment);
                break;
            case 'q':
                cout << "\n\nTerminating Program\n";
                break;
        }
        turns += 1;
    }
    cout << "\n\nProgrm completed!\n";
    return 0;
}


