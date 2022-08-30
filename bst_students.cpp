// I have chosen BST, rather than heap
// Because
// BST is ordered, but the Heap is not. As in our case order matters,
// so it is better to use BST. We could choose heap if order would not be the prioirity 
// and we just need to be sure that insert and remove takes O(log(n)) time,
// then the Heap guarantees to achieve this time but order also has been a priority in our case.
// In a Binary Search Tree, this may take up to O(n) time for searching a node in worst case,
// but still choosing it because we can have unbalanced tree and order is a priority.
// Also
// We have to make a little change to BST while inserting nodes in tree that
// we need to reverse the comparison while inserting element to the tree like

// struct StructNode *insertElementInTree(struct StructNode *node, Student student) {
//     // Return a new node if the tree is empty
//     if (node == NULL) return createNode(student);
//     // Traverse to the right place and insert the node
//     if (student.total > node->student.total) //this comparison is changed => reversed
//     {
//         // putting the higher total marks student at left
//         // so in order retrieval will bring up the highest marks student first (on top)
//         node->left = insertElementInTree(node->left, student);
//     }
//     else
//     {
//         node->right = insertElementInTree(node->right, student);
//     }
//     return node;
// }




#include <iostream>
#include <string>
#include <list>
using namespace std;

class Student{
    public:
    int test = 0;
    int inter = 0;
    int matric = 0;
    
    int total = 0;
    string name = "";
    string enrollment;
    int get_total_marks(){
        return test+matric+inter;
    }
    
    void show(){
        cout<<"\n\n";
        cout<<"Name => "<<name;
        cout<<"\nEnrollment => "<<enrollment;
        if(total == 0)
        {
            //will be called only once when instance is created
            total = get_total_marks();
        }
        cout<<"\nMarks => "<<total<<"\n";
    }
};

int student_capacity = 10;
int enrolled_students = 0;
list<Student> students;
list<Student>::iterator reader;

struct StructNode {
    Student key;
    struct StructNode *left, *right;
};

// Create a node
struct StructNode *createNode(Student item) {
    struct StructNode *temp = new StructNode;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert a node
struct StructNode *insertElementInTree(struct StructNode *node, Student key) {
    // Return a new node if the tree is empty
    if (node == NULL) return createNode(key);
    // Traverse to the right place and insert the node
    if (key.total > node->key.total)
    {
        node->left = insertElementInTree(node->left, key);
    }
    else
    {
        node->right = insertElementInTree(node->right, key);
    }
    return node;
}

struct StructNode *add_student(struct StructNode *root){
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
    root = insertElementInTree(root, st);
    enrolled_students += 1;
    return root;
}

// Inorder Traversal
void read_bst_inorder(struct StructNode *root) {
    if (root != NULL) {
        // Traverse left
        read_bst_inorder(root->left);
        // Traverse root
        root->key.show();
        // Traverse right
        read_bst_inorder(root->right);
    }
}

void find_student(struct StructNode *root, string enrollment, int cnt) {
    if (root != NULL) {
        // Traverse left
        cnt += 1;
        find_student(root->left, enrollment, cnt);
        // Traverse root
        if(root->key.enrollment == enrollment)
        {
            cout<<"Student found in "<<cnt<< " operations, with enrollment => "<<enrollment;
            root->key.show();
            return;
        }
        // Traverse right
        find_student(root->right, enrollment, cnt);
    }
}


int main() {
    
    int cnt;
    char option;
    string enrollment;
    struct StructNode *root = NULL;
    int turns = 1;
    cout <<"\n\n*****************************************";
    cout <<"\n\tWelcome to Student management system";
    cout <<"\n*****************************************";
    
    while(option != 'q' && turns < 15){
        cout <<"\n\n Press 1 to add student";
        cout <<"\n Press 2 to show list of students";
        cout <<"\n Press 3 to find a student";
        cout <<"\n Press q to quit";
        cout <<" => ";
        cin >> option;
        switch(option){
            case '1':
                root = add_student(root);
                cout << "\n\n Student inserted";
                break;
            case '2':
                read_bst_inorder(root);
                cout<<"\n Number of enrolled/shown students => "<<enrolled_students;
                break;
            case '3':
                if(enrolled_students == 0){
                    cout<<"No students enrolled yet";
                }
                else{
                    cout << "\n\n Enter enrollment to find student => ";
                    cin >> enrollment;
                    find_student(root, enrollment, 0);    
                }
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

