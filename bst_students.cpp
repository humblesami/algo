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

struct StructNode {
    Student key;
    struct StructNode *left, *right;
};

// Create a node
struct StructNode *newNode(Student item) {
    struct StructNode *temp = (struct StructNode *)malloc(sizeof(struct StructNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
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

// Insert a node
struct StructNode *insertElementInTree(struct StructNode *node, Student key) {
    // Return a new node if the tree is empty
    if (node == NULL) return newNode(key);
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

// Find the inorder successor
struct StructNode *minValueNode(struct StructNode *node) {
    struct StructNode *current = node;
    // Find the leftmost leaf
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// Deleting a node
struct StructNode *deleteNode(struct StructNode *root, Student key) {
    // Return if the tree is empty
    if (root == NULL) return root;
    // Find the node to be deleted
    if (key.total < root->key.total)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key.total > root->key.total)
    {
        root->right = deleteNode(root->right, key);
    }
    else {
        // If the node is with only one child or no child
        if (root->left == NULL) {
            struct StructNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct StructNode *temp = root->left;
            free(root);
            return temp;
        }
        // If the node has two children
        struct StructNode *temp = minValueNode(root->right);
        // Place the inorder successor in position of the node to be deleted
        root->key = temp->key;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    enrolled_students -= 1;
    return root;
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
                cout << "\n\n Will add student";
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

