a.cpp#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// ===================== STUDENT CLASS =====================
class Stud {
private:
    int roll;
    string name;
    string sub;
    string staff;
    float att;
    float mark;

public:
    Stud* next;
    Stud(int r, string n, string s, string t, float a, float m) {
        roll = r; name = n; sub = s; staff = t; att = a; mark = m; next = NULL;
    }

    int getRoll() { return roll; }
    string getName() { return name; }
    string getSub() { return sub; }
    string getStaff() { return staff; }
    float getAtt() { return att; }
    float getMark() { return mark; }

    void update(float a, float m) { att = a; mark = m; }

    string mood()
    {
        if (mark >= 90 && att >= 90)
            return "Outstanding and Highly Motivated";
        else if (mark >= 80 && att >= 80)
            return "Excellent and Consistent";
        else if (mark >= 70 && att >= 75)
            return "Good and Needs Slight Improvement";
        else if (mark >= 60 && att >= 65)
            return "Average and Can Do Better)";
        else if (mark >= 50 && att >= 60)
            return "Below Average and Irregular";
        else if (mark >= 40 && att >= 50)
            return "Poor and Low Performance";
        else if(mark < 40 && att < 50)
            return "Critical and Needs Attention Immediately";
        else
            return string(""); // fixed: return empty string instead of integer 0
        }
    void show() {
        cout << "Roll No: " << roll << "\nName: " << name
             << "\nSubject: " << sub << "\nStaff: " << staff
             << "\nAttendance: " << att << "\nMarks: " << mark << "\n";
    }
};

// ===================== STUDENT LIST =====================
class StudList {
private:
    Stud* head;

public:
    StudList() { head = NULL; }

    void add(Stud* s) {
        if (!head) head = s;
        else {
            Stud* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = s;
        }
    }

    void del(int r) {
        if (!head) return;
        Stud* temp = head;
        Stud* prev = NULL;
        while (temp && temp->getRoll() != r) {
            prev = temp;
            temp = temp->next;
        }
        if (!temp) return;
        if (!prev) head = head->next;
        else prev->next = temp->next;
        delete temp;
    }

    Stud* getHead() { return head; }

    void save() {
        ofstream fout("students.txt");
        Stud* t = head;
        while (t) {
            fout << t->getRoll() << " " << t->getName() << " "
                 << t->getSub() << " " << t->getStaff() << " "
                 << t->getAtt() << " " << t->getMark() << "\n";
            t = t->next;
        }
        fout.close();
    }

    void load() {
        ifstream fin("students.txt");
        if (!fin) return;
        int r;
        string n, s, st; 
        float a, m;
        while (fin >> r >> n >> s >> st >> a >> m)
            add(new Stud(r, n, s, st, a, m));
        fin.close();
    }
};

// ===================== STAFF CLASS =====================
class Teach {
private:
    string name;
    string sub;
    string dept;
    float classavem;
    float classavea;

public:
    Teach* next;
    Teach(string n, string s, string d) {
        name = n; 
        sub = s; 
        dept = d; 
        classavem=0; 
        classavea=0; 
        next = NULL;
    }

    string getName() { return name; }
    string getSub() { return sub; }
    string getDept() { return dept; }

    bool login(string n, string p) {
         return (name == n && sub == p);
    }

    void show() {
        cout << "Name: " << name << "\nSubject: " << sub
      
        << "\nDepartment: " << dept << "\nAverage students Attendance: "<< classavea << "\nClass Average Marks: "<< classavem <<"\n";
    }
    void class_average()
    {
        float totalm=0.0,totala=0.0;
        int count=0;
        Stud *a = nullptr; // fixed: initialize pointer to avoid using uninitialized memory
        while(a)
        {
            if(a->getStaff()==name)
                totalm = totalm + a->getMark();
                totala = totala + a->getAtt();
                count++;
        }
        if (count > 0) { // guard against division by zero
            classavem=totalm/count;
            classavea=totala/count;
        } else {
            classavem = 0;
            classavea = 0;
        }
    }
    string mood()
    {
        if (classavem >= 90 && classavea >= 90)
            return "Outstanding and Highly Motivated";
        else if (classavem >= 80 && classavea >= 80)
            return "Excellent and Consistent";
        else if (classavem >= 70 && classavea >= 75)
            return "Good and Needs Slight Improvement";
        else if (classavem >= 60 && classavea >= 65)
            return "Average and Can Do Better)";
        else if (classavem >= 50 && classavea >= 60)
            return "Below Average and Irregular";
        else if (classavem >= 40 && classavea >= 50)
            return "Poor and Low Performance";
        else if(classavem < 40 && classavea < 50)
            return "Critical and Needs Attention Immediately";
        else
            return string(""); // fixed: return empty string instead of integer 0
        }
    void save(ofstream& fout) {
        fout << name << " " << sub << " " << dept << "\n";
    }
};

// ===================== STAFF LIST =====================
class TeachList {
private:
    Teach* head;

public:
    TeachList() { head = NULL; }

    void add(Teach* s) {
        if (!head) head = s;
        else {
            Teach* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = s;
        }
    }

    void del(string n) {
        if (!head) return;
        Teach* temp = head;
        Teach* prev = NULL;
        while (temp && temp->getName() != n) {
            prev = temp;
            temp = temp->next;
        }
        if (!temp) {
            cout << "No such staff found!\n";
            return;
        }
        if (!prev) head = head->next;
        else prev->next = temp->next;
        delete temp;
        cout << "Staff deleted successfully!\n";
    }

    Teach* getHead() { return head; }

    void save() {
        ofstream fout("staff.txt");
        Teach* temp = head;
        while (temp) {
            temp->save(fout);
            temp = temp->next;
        }
        fout.close();
    }

    void load() {
        ifstream fin("staff.txt");
        if (!fin) return;
        string n, s, d;
        while (fin >> n >> s >> d)
            add(new Teach(n, s, d));
        fin.close();
    }
};

// ===================== MAIN =====================
int main() 
{
    StudList st;
    TeachList tc;
    int k=0;
    st.load();
    tc.load();
    while(k!=1)
    {
    string role;
    cout << "Login as (principal/staff/student): ";
    cin >> role;

    // -------- PRINCIPAL LOGIN --------
    if (role == "principal") {
        string u, p;
        cout << "Enter username: ";
        cin >> u;
        cout << "Enter password: ";
        cin>>p;

        if (u == "mepco" && p == "msec") {
            cout << "\nWelcome Principal!\n";
            int ch;
            do {
                cout << "\n--- Principal Menu ---\n";
                cout << " 1. Add Staff\n 2. Delete Staff\n 3. Display\n 4. Exit\n Enter choice: ";
                cin >> ch;

                if (ch == 1) {
                    string n, s, d;
                    cout << "Enter Name  of the staff: ";
                    cin>>n;
                    cout<<"Enter the subject taken by the staff: ";
                    cin>>s;
                    cout<<"Enter the Department of the staff:";
                    cin >>d;
                    tc.add(new Teach(n, s, d));
                    cout << "Staff added successfully!\n";
                }
                else if (ch == 2) {
                    string n;
                    cout << "Enter Staff Name to Delete: ";
                    cin >> n;
                    tc.del(n);
                }
                else if(ch==3){
                    cout<<"Staffs:";
                    Teach *ts = tc.getHead();
                    while(ts)
                    {
                        ts->show();
                        ts->class_average();
                        ts->mood();
                        cout<<endl;
                        ts=ts->next;
                    }
                }

            } while (ch != 4);
            tc.save();
        }
        else
            cout << "Invalid principal login!\n";
    }

    // -------- STAFF LOGIN --------
    else if (role == "staff") {
        string u, p;
        cout << "Enter username: ";
        cin >> u;
        cout << "Enter password: ";
        cin >> p;

        Teach* t = tc.getHead();
        while (t && !t->login(u, p))
            t = t->next;

        if (t) {
            cout << "\nWelcome Staff " << u << " (" << t->getSub() << ")!\n";
            int ch;
            do {
                cout << "\n--- Staff Menu ---\n";
                cout << "1. Add Student\n2. Delete Student\n3. Update Student\n4. Search Student\n5. Display My Students\n6. Mood Analysis\n7. Exit\nEnter choice: ";
                cin >> ch;

                if (ch == 1) {
                    int r,la=0; string n; float a, m;
                    cout << "Enter RollNo :";
                    cin>>r;
                    cout<<"Enter the Name: ";
                    cin>>n;
                    while(la!=1){
                    cout<< "Enter the Attendance :";
                    cin>>a;
                    if(a>=0&&a<=100){break;}
                    else{continue;}
                    }
                    la=0;
                    while(la!=1){
                    cout<<"Enter the Marks: ";
                    cin >> m;
                    if(m>=0&&m<=100){break;}
                    else{continue;}
                    }
                    st.add(new Stud(r, n, t->getSub(), u, a, m));
                    cout << "Student added under subject '" << t->getSub() << "'.\n";
                }

                else if (ch == 2) {
                    int r; cout << "Enter RollNo to Delete: "; cin >> r;
                    Stud* s = st.getHead(); bool ok = false;
                    while (s) {
                        if (s->getRoll() == r && s->getSub() == t->getSub() && s->getStaff() == u) {
                            st.del(r); 
                            ok = true; 
                            break;
                        }
                        s = s->next;
                    }
                    if (!ok) cout << "You can only delete your subject students!\n";
                }

                else if (ch == 3) {
                    int r,la=0; float a, m;
                    cout << "Enter RollNo: "; 
                    cin >> r;
                    while(la!=1){
                    cout<< "Enter the Attendance :";
                    cin>>a;
                    if(a>=0&&a<=100){break;}
                    else{continue;}
                    }
                    la=0;
                    while(la!=1){
                    cout<<"Enter the Marks: ";
                    cin >> m;
                    if(m>=0&&m<=100){break;}
                    else{continue;}
                    }
                    Stud* s = st.getHead(); bool ok = false;
                    while (s) {
                        if (s->getRoll() == r && s->getSub() == t->getSub() && s->getStaff() == u) {
                            s->update(a, m);
                            cout << "Updated!\n"; ok = true; break;
                        }
                        s = s->next;
                    }
                    if (!ok) cout << "You can only update your subject students!\n";
                }

                else if (ch == 4) {
                    string n; cout << "Enter Name: "; cin >> n;
                    Stud* s = st.getHead(); bool ok = false;
                    while (s) {
                        if (s->getName() == n && s->getSub() == t->getSub() && s->getStaff() == u) {
                            s->show(); ok = true; break;
                        }
                        s = s->next;
                    }
                    if (!ok) cout << "No such student found in your subject!\n";
                }

                else if (ch == 5) {
                    Stud* s = st.getHead(); bool any = false;
                    cout << "\n--- My Students (" << t->getSub() << ") ---\n";
                    while (s) {
                        if (s->getSub() == t->getSub() && s->getStaff() == u) {
                            s->show(); cout << "------------------\n"; any = true;
                        }
                        s = s->next;
                    }
                    if (!any) cout << "No students assigned yet.\n";
                }

                else if (ch == 6) {
                    Stud* s = st.getHead(); bool any = false;
                    cout << "\n--- Mood Analysis (" << t->getSub() << ") ---\n";
                    while (s) {
                        if (s->getSub() == t->getSub() && s->getStaff() == u) {
                            cout << s->getName() << " (" << s->getRoll() << ") - " << s->mood() << "\n";
                            any = true;
                        }
                        s = s->next;
                    }
                    if (!any) cout << "No students found!\n";
                }

            } while (ch != 7);
            st.save();
        }
        else cout << "Invalid staff login!\n";
    }

    // -------- STUDENT LOGIN --------
    else if (role == "student")
    {
        string n;
        char l;
        int h=0;
        while(h!=1)
        {
            cout << "Student Details(y/n):";
            cin >>l;
            if(l =='n')
            {
                h=1;
            }
            else if(l=='y')
            {
                cout << "Enter your name: ";
                cin >> n;
                Stud* s = st.getHead(); bool found = false;
                while (s) 
                {
                    if (s->getName() == n) 
                    {
                        cout << "\n--- Your Details ---\n";
                        s->show();
                        cout << "Mood: " << s->mood() << "\n";
                        found = true; break;
                    }
                    s = s->next;
                }
                if (!found) cout << "No such student found!\n";
            }
        }
    }
    else if (role=="exit")
    {
        cout<<"Exiting.....\n";
        k=1;
    }
    else
        cout << "Invalid role!\n";
}
    return 0;
}