/*Abdullah sonija 24k-0013*/
#include <iostream>
#include <string>
using namespace std;

long hashPassword(const string &password)
{
    long hash = 5381;
        for (char c : password) 
        {
            hash = hash * 33 + c;
        }
        return hash;
}
class User 
{
    protected:
    string name;
    int ID;
    string email;
    long hpassword;
    string permissions[5];  
    public:
    User(string n, int id, string mail, string pass, string perms[], int permSize) 
    {
        name = n;
        ID = id;
        email = mail;
        hpassword = hashPassword(pass);
        for (int i = 0; i < permSize; i++) 
        {
            permissions[i] = perms[i];
        }
    }
    bool authenticate(string password) 
    {
        return hashPassword(password) == hpassword;
    }
    virtual void display() 
    {
        cout << "User: " << name << " | ID: " << ID << " | Email: " << email << endl;
    }
    bool accessLab() 
    {
        for (int i = 0; i < 5; i++) 
        {
            if (permissions[i] == "full_lab_access") 
            {
                cout << name << " has full lab access.\n";
                return true;
            }
        }
        cout << name << " does not have full lab access.\n";
        return false;
    }
    string *getPermissions() { return permissions; }
};
class Student : public User
{
    protected:
    int assignments[5] = {0};  
    public:
    Student(string n, int id, string mail, string pass)
        : User(n, id, mail, pass, new string[1]{"submit_assignment"}, 1) {}
    void submitAssignment(int index) 
    {
        if (index >= 0 && index < 5) 
        {
            assignments[index] = 1;
            cout << name << " submitted assignment " << index + 1 << endl;
        }
    }
    void display() override
    {
        cout << "Student: " << name << " | ID: " << ID << " | Email: " << email << endl;
        cout << "Assignments: ";
        for (int i = 0; i < 5; i++) cout << assignments[i] << " ";
        cout << endl;
    }
};
class TA : public Student 
{
    Student students[10];  
    int num_students = 0;
    string projects[2];    
    int num_projects = 0;
    public:
    TA(string n, int id, string mail, string pass)
        : Student(n, id, mail, pass) {
        string perms[] = {"view_projects", "manage_students"};
        for (int i = 0; i < 2; i++) permissions[i] = perms[i];
    }

    void assignStudent(Student s) {
        if (num_students < 10) {
            students[num_students++] = s;
            cout << s.name << " : assigned to TA : " << name << endl;
        } else {
            cout << "TA : " << name << " cannot manage more than 10 students!\n";
        }
    }
    void addProject(string proj) 
    {
        if (num_projects < 2) 
        {
            projects[num_projects++] = proj;
            cout << "TA : " << name << " is now working on project: " << proj << endl;
        } else 
        {
            cout << "TA : " << name << " cannot work on more than 2 projects!\n";
        }
    }
    void display() override {
        cout << "TA: " << name << " | ID: " << ID << " | Email: " << email << endl;
        cout << "Students managed: " << num_students << " | Projects: " << num_projects << endl;
    }
};
class Professor : public User 
{
    public:
    Professor(string n, int id, string mail, string pass)
        : User(n, id, mail, pass, new string[2]{"assign_projects", "full_lab_access"}, 2) {}
    void assignProject(TA &ta, string project) 
    {
        ta.addProject(project);
        cout << "Professor " << name << " assigned project " << project << " to TA " << ta.name << endl;
    }
    void display() override 
    {
        cout << "Professor: " << name << " | ID: " << ID << " | Email: " << email << endl;
    }
};
void authenticateAndPerformAction(User *user, string password, string action) {
    if (!user->authenticate(password)) 
    {
        cout << "Authentication failed for " << user->name << endl;
        return;
    }
    string *perms = user->getPermissions();
    bool allowed = false;
    for (int i = 0; i < 5; i++) 
    {
        if (perms[i] == action) 
        {
            allowed = true;
            break;
        }
    }
    if (allowed)
    {
        cout << user->name << " successfully performed: " << action << endl;
    } else 
    {
        cout << "Permission denied for action: " << action << endl;
    }
}
int main() {
    Student s1("Ali", 1, "ali@example.com", "pass123");
    TA ta1("Babar", 2, "babar@example.com", "securepass");
    Professor p1("Saeed", 3, "saees@example.com", "profpass");
    s1.display();
    ta1.display();
    p1.display();
    authenticateAndPerformAction(&s1, "pass123", "submit_assignment");
    authenticateAndPerformAction(&ta1, "securepass", "view_projects");
    authenticateAndPerformAction(&p1, "profpass", "assign_projects");
    s1.accessLab();
    p1.accessLab();
    ta1.assignStudent(s1);
    p1.assignProject(ta1, "AI Research");
    s1.submitAssignment(2);
    return 0;
}