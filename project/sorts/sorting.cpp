#include <iostream>
#include <vector>
#include<map>
#include <string>

using namespace std;



class Task{
    private:
    public:
    int id;
    int learningrate;
    int subjects[4];
    int deadline[3];

    string description;
    User* assignedTo;

    Task(int id, const string& description) : id(id), description(description), assignedTo(nullptr) {}

    int getId() const {
        return id;
    }

    string getDescription() const {
        return description;
    }

    User* getAssignedTo() const {
        return assignedTo;
    }

    void setAssignedTo(User* user) {
        assignedTo = user;
    }
};

class User {
//Task Report function
//Most Urgent Task and Tasks Pending




private:
public:
    int id;
    string name;
    vector<Task*> tasksAssigned;

    User(int id, const string& name) : id(id), name(name) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    vector<Task*> getTasksAssigned() const {
        return tasksAssigned;
    }

    void addTask(Task* task) {
        tasksAssigned.push_back(task);
        task->setAssignedTo(this);
    }

    void removeTask(Task* task) {
        for (auto it = tasksAssigned.begin(); it != tasksAssigned.end(); ++it) {
            if (*it == task) {
                tasksAssigned.erase(it);
                task->setAssignedTo(nullptr);
                break;
            }
        }
    }
};

int main(){
    Task t1(1,"Math subject");
    User u1(1,"Chris");
}