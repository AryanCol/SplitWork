#include <iostream>
#include <vector>
#include<map>
#include <string>

using namespace std;

class User;
class Task;
class Group;

class SplitWork {   
private:
    vector<Group*> groups;

public:
    void addGroup(Group* group) {
        groups.push_back(group);
    }

    void removeGroup(Group* group) {
        for (auto it = groups.begin(); it != groups.end(); ++it) {
            if (*it == group) {
                groups.erase(it);
                break;
            }
        }
    }

    void displayGroups() {
        for (Group* group : groups) {
            cout << "Group ID: " << group->getId() << ", Name: " << group->getName() << endl;
        }
    }
};

class Task {
private:
    int id;
    int learningrate;
    vector<string> subjects;
    int deadline[3];

    string description;
    User* assignedTo;

public:
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
    int id;
    string name;
    vector<Task*> tasksAssigned;

public:
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

class Group {
private:
    int id;
    string name;
    vector<User*> users;
    vector<Task*> tasks;

public:
    Group(int id, const string& name) : id(id), name(name) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    void addUser(User* user) {
        users.push_back(user);
    }

    void removeUser(User* user) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (*it == user) {
                users.erase(it);
                break;
            }
        }
    }

    void addTask(Task* task) {
        tasks.push_back(task);
    }

    void removeTask(Task* task) {
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (*it == task) {
                tasks.erase(it);
                break;
            }
        }
    }

    void assignTask(Task* task, User* user) {
        user->addTask(task);
    }

    void displayUsers() {
        for (User* user : users) {
            cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
        }
    }

    void displayTasks() {
        for (Task* task : tasks) {
            cout << "Task ID: " << task->getId() << ", Description: " << task->getDescription() << ", Assigned to: ";
            if (task->getAssignedTo()) {
                cout << task->getAssignedTo()->getName() << endl;
            } else {
                cout << "None" << endl;
            }
        }
    }
};