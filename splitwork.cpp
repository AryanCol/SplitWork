#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Task;
class User;

class User
{
private:
    int id;
    string name;
    vector<Task *> tasksAssigned;

public:
    User(int id, const string &name) : id(id), name(name) {}

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    vector<Task *> &getTasksAssigned()
    {
        return tasksAssigned;
    }

    void addTask(Task *task);
    void removeTask(Task *task);
};

class Task
{
private:
    int id;
    string description;
    User *assignedTo;
    float workload;
    string deadline;
    string relevance;

public:
    Task(int id, const string &description) : id(id), description(description), assignedTo(nullptr), workload(0.0) {}

    int getId() const
    {
        return id;
    }

    string getDescription() const
    {
        return description;
    }

    User *getAssignedTo() const
    {
        return assignedTo;
    }

    void setAssignedTo(User *user)
    {
        assignedTo = user;
    }

    float getWorkload() const
    {
        return workload;
    }

    void setWorkload(float w)
    {
        workload = w;
    }

    string getDeadline() const
    {
        return deadline;
    }

    void setDeadline(const string &d)
    {
        deadline = d;
    }

    string getRelevance() const
    {
        return relevance;
    }

    void setRelevance(const string &r)
    {
        relevance = r;
    }
};

void User::addTask(Task *task)
{
    tasksAssigned.push_back(task);
    task->setAssignedTo(this);
}

void User::removeTask(Task *task)
{
    for (auto it = tasksAssigned.begin(); it != tasksAssigned.end(); ++it)
    {
        if (*it == task)
        {
            tasksAssigned.erase(it);
            task->setAssignedTo(nullptr);
            break;
        }
    }
}

class Group
{
private:
    int id;
    string name;
    vector<User *> users;
    vector<Task *> tasks;

public:
    Group(int id, const string &name) : id(id), name(name) {}

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    vector<User *> getUsers() const
    {
        return users;
    }

    vector<Task *> getTasks() const
    {
        return tasks;
    }

    void addUser(User *user)
    {
        users.push_back(user);
    }

    void removeUser(User *user)
    {
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if (*it == user)
            {
                users.erase(it);
                break;
            }
        }
    }

    User *findUserById(int id)
    {
        for (User *user : users)
        {
            if (user->getId() == id)
                return user;
        }
        return nullptr;
    }

    void addTask(Task *task)
    {
        tasks.push_back(task);
    }

    void removeTask(Task *task)
    {
        for (auto it = tasks.begin(); it != tasks.end(); ++it)
        {
            if (*it == task)
            {
                tasks.erase(it);
                break;
            }
        }
    }

    Task *findTaskById(int id)
    {
        for (Task *task : tasks)
        {
            if (task->getId() == id)
                return task;
        }
        return nullptr;
    }

    void assignTask(Task *task, User *user)
    {
        user->addTask(task);
    }

    void unassignTask(Task *task, User *user)
    {
        user->removeTask(task);
    }

    void displayUsers()
    {
        for (User *user : users)
        {
            cout << "User ID: " << user->getId() << ", Name: " << user->getName() << endl;
        }
    }

    void displayTasks()
    {
        for (Task *task : tasks)
        {
            cout << "Task ID: " << task->getId() << ", Description: " << task->getDescription() << ", Assigned to: ";
            if (task->getAssignedTo())
            {
                cout << task->getAssignedTo()->getName() << endl;
            }
            else
            {
                cout << "None" << endl;
            }
        }
    }
};

class SplitWork
{
private:
    vector<Group *> groups;

public:
    void addGroup(Group *group)
    {
        for (auto &grp : groups)
        {
            if (grp->getId() == group->getId())
            {
                cout << "Group ID already in use. Enter a different ID." << endl;
                return;
            }
        }
        groups.push_back(group);
    }

    void removeGroup(Group *group)
    {
        for (auto it = groups.begin(); it != groups.end(); ++it)
        {
            if (*it == group)
            {
                groups.erase(it);
                break;
            }
        }
    }

    Group *findGroupById(int id)
    {
        for (Group *group : groups)
        {
            if (group->getId() == id)
                return group;
        }
        return nullptr;
    }

    void saveData()
    {
        ofstream groupsFile("groups.txt", ios::out);
        ofstream usersFile("users.txt", ios::out);
        ofstream tasksFile("tasks.txt", ios::out);

        for (auto *group : groups)
        {
            // Save group
            groupsFile << group->getId() << "," << group->getName() << endl;

            // Save users in this group
            for (auto *user : group->getUsers())
            {
                usersFile << group->getId() << "," << user->getId() << "," << user->getName() << endl;
            }

            // Save tasks in this group
            for (auto *task : group->getTasks())
            {
                tasksFile << group->getId() << "," << task->getId() << "," << task->getDescription() << ","
                          << (task->getAssignedTo() ? task->getAssignedTo()->getId() : -1) << ","
                          << task->getWorkload() << "," << task->getDeadline() << "," << task->getRelevance() << endl;
            }
        }

        groupsFile.close();
        usersFile.close();
        tasksFile.close();
    }

    void loadData()
    {
        ifstream groupsFile("groups.txt", ios::in);
        ifstream usersFile("users.txt", ios::in);
        ifstream tasksFile("tasks.txt", ios::in);

        int groupId, userId, taskId, assignedUserId;
        string groupName, userName, taskDesc, deadline, relevance;
        float workload;

        while (groupsFile >> groupId >> groupName)
        {
            Group *group = new Group(groupId, groupName);
            addGroup(group);
        }

        while (usersFile >> groupId >> userId >> userName)
        {
            Group *group = findGroupById(groupId);
            if (group)
            {
                group->addUser(new User(userId, userName));
            }
        }

        string line;
        while (getline(tasksFile, line))
        {
            stringstream ss(line);
            string value;
            vector<string> taskData;
            while (getline(ss, value, ','))
            {
                taskData.push_back(value);
            }
            if (taskData.size() == 7)
            {
                groupId = stoi(taskData[0]);
                taskId = stoi(taskData[1]);
                taskDesc = taskData[2];
                assignedUserId = stoi(taskData[3]);
                workload = stof(taskData[4]);
                deadline = taskData[5];
                relevance = taskData[6];

                Group *group = findGroupById(groupId);
                if (group)
                {
                    Task *task = new Task(taskId, taskDesc);
                    task->setWorkload(workload);
                    task->setDeadline(deadline);
                    task->setRelevance(relevance);
                    group->addTask(task);
                    if (assignedUserId != -1)
                    {
                        User *user = group->findUserById(assignedUserId);
                        if (user)
                        {
                            group->assignTask(task, user);
                        }
                    }
                }
            }
        }

        groupsFile.close();
        usersFile.close();
        tasksFile.close();
    }

    void displayGroups()
    {
        for (Group *group : groups)
        {
            cout << "Group ID: " << group->getId() << ", Name: " << group->getName() << endl;
        }
    }
};

int main()
{
    SplitWork splitWork;
    splitWork.loadData();

    Group *group;
    User *user;
    Task *task;
    int choice, groupId, userId, taskId;
    string groupName, userName, taskDesc;

    while (true)
    {
        cout << "1. Add Group\n2. Remove Group\n3. Add User to Group\n4. Remove User from Group\n5. Add Task to Group\n6. Assign Task to User\n7. Unassign Task from User\n8. Display Groups\n9. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Group ID and Name: ";
            cin >> groupId >> groupName;
            group = new Group(groupId, groupName);
            if (!splitWork.findGroupById(groupId))
            {
                splitWork.addGroup(group);
                splitWork.saveData();
            }
            else
            {
                cout << "Group ID already exists. Please try a different ID." << endl;
            }
            break;
        case 2:
            cout << "Enter Group ID to remove: ";
            cin >> groupId;
            group = splitWork.findGroupById(groupId);
            if (group != nullptr)
            {
                splitWork.removeGroup(group);
                splitWork.saveData();
            }
            else
            {
                cout << "Group not found." << endl;
            }
            break;
        case 3:
            cout << "Enter Group ID, User ID, and Name to add: ";
            cin >> groupId >> userId >> userName;
            group = splitWork.findGroupById(groupId);
            if (group != nullptr)
            {
                if (!group->findUserById(userId))
                {
                    user = new User(userId, userName);
                    group->addUser(user);
                    splitWork.saveData();
                }
                else
                {
                    cout << "User ID already exists. Please try a different ID." << endl;
                }
            }
            else
            {
                cout << "Group not found." << endl;
            }
            break;
        case 4:
            cout << "Enter Group ID and User ID to remove: ";
            cin >> groupId >> userId;
            group = splitWork.findGroupById(groupId);
            if (group != nullptr)
            {
                user = group->findUserById(userId);
                if (user != nullptr)
                {
                    group->removeUser(user);
                    splitWork.saveData();
                }
                else
                {
                    cout << "User not found." << endl;
                }
            }
            else
            {
                cout << "Group not found." << endl;
            }
            break;
        case 5:
            cout << "Enter Group ID, Task ID, and Description: ";
            cin >> groupId >> taskId >> taskDesc;
            group = splitWork.findGroupById(groupId);
            if (group != nullptr)
            {
                if (!group->findTaskById(taskId))
                {
                    task = new Task(taskId, taskDesc);
                    group->addTask(task);
                    splitWork.saveData();
                }
                else
                {
                    cout << "Task ID already exists. Please try a different ID." << endl;
                }
            }
            else
            {
                cout << "Group not found." << endl;
            }
            break;
        case 6:
            cout << "Enter Group ID, User ID, and Task ID to assign: ";
            cin >> groupId >> userId >> taskId;
            group = splitWork.findGroupById(groupId);
            if (group != nullptr)
            {
                user = group->findUserById(userId);
                task = group->findTaskById(taskId);
                if (user != nullptr && task != nullptr)
                {
                    group->assignTask(task, user);
                    splitWork.saveData();
                }
                else
                {
                    cout << "User or task not found." << endl;
                }
            }
            else
            {
                cout << "Group not found." << endl;
            }
            break;
        case 7:
            cout << "Enter Group ID, User ID, and Task ID to unassign: ";
            cin >> groupId >> userId >> taskId;
            group = splitWork.findGroupById(groupId);
            if (group != nullptr)
            {
                user = group->findUserById(userId);
                task = group->findTaskById(taskId);
                if (user != nullptr && task != nullptr)
                {
                    group->unassignTask(task, user);
                    splitWork.saveData();
                }
                else
                {
                    cout << "User or task not found." << endl;
                }
            }
            else
            {
                cout << "Group not found." << endl;
            }
            break;
        case 8:
            splitWork.displayGroups();
            break;
        case 9:
            splitWork.saveData();
            cout << "Exiting program and saving data..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    return 0;
}