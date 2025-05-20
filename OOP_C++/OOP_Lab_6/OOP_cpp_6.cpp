#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===== Базовый класс =====
class User {
private:
    static int objectCount;

protected:
    string login;
    string password;
    string role;

public:
    User() : login(""), password(""), role("User") {
        objectCount++;
        cout << "[User] Конструктор (без параметров)\n";
    }

    User(string l, string p, string r) : login(l), password(p), role(r) {
        objectCount++;
        cout << "[User] Конструктор (с параметрами)\n";
    }

    User(const User& other) : login(other.login), password(other.password), role(other.role) {
        objectCount++;
        cout << "[User] Конструктор копирования\n";
    }

    virtual ~User() {
        objectCount--;
        cout << "[User] Деструктор\n";
    }

    virtual void displayAll() const = 0;
    virtual User* clone() const = 0;

    static int getObjectCount() {
        return objectCount;
    }
};
int User::objectCount = 0;

// ===== Класс Administrator =====
class Administrator : public User {
private:
    int accessLevel;

public:
    Administrator() : User(), accessLevel(0) {
        role = "Administrator";
        cout << "[Administrator] Конструктор (по умолчанию)\n";
    }

    Administrator(string l, string p, int level)
        : User(l, p, "Administrator"), accessLevel(level) {
        cout << "[Administrator] Конструктор с параметрами\n";
    }

    Administrator(const Administrator& other)
        : User(other), accessLevel(other.accessLevel) {
        cout << "[Administrator] Конструктор копирования\n";
    }

    ~Administrator() override {
        cout << "[Administrator] Деструктор\n";
    }

    void displayAll() const override {
        cout << "[Administrator] Логин: " << login << ", Пароль: " << password
             << ", Уровень доступа: " << accessLevel << endl;
    }

    User* clone() const override {
        return new Administrator(*this);
    }
};

// ===== Класс Guest =====
class Guest : public User {
private:
    int sessionDuration;

public:
    Guest() : User(), sessionDuration(0) {
        role = "Guest";
        cout << "[Guest] Конструктор (по умолчанию)\n";
    }

    Guest(string l, string p, int duration)
        : User(l, p, "Guest"), sessionDuration(duration) {
        cout << "[Guest] Конструктор с параметрами\n";
    }

    Guest(const Guest& other)
        : User(other), sessionDuration(other.sessionDuration) {
        cout << "[Guest] Конструктор копирования\n";
    }

    ~Guest() override {
        cout << "[Guest] Деструктор\n";
    }

    void displayAll() const override {
        cout << "[Guest] Логин: " << login << ", Пароль: " << password
             << ", Длительность сессии: " << sessionDuration << " мин\n";
    }

    User* clone() const override {
        return new Guest(*this);
    }
};

// ===== Класс Application =====
class Application {
private:
    string appName;
    int requiredMemory;
    vector<User*> users;

    static int userCountInApp;

    void clearUsers() {
        for (auto u : users)
            delete u;
        users.clear();
    }

    void copyUsers(const vector<User*>& source) {
        for (auto u : source) {
            users.push_back(u->clone());
            userCountInApp++;
        }
    }

public:
    Application() : appName(""), requiredMemory(0) {
        cout << "[Application] Конструктор\n";
    }

    Application(string name, int mem) : appName(name), requiredMemory(mem) {
        cout << "[Application] Конструктор с параметрами\n";
    }

    Application(const Application& other) : appName(other.appName), requiredMemory(other.requiredMemory) {
        copyUsers(other.users);
        cout << "[Application] Конструктор копирования\n";
    }

    Application& operator=(const Application& other) {
        if (this != &other) {
            clearUsers();
            appName = other.appName;
            requiredMemory = other.requiredMemory;
            copyUsers(other.users);
        }
        return *this;
    }

    ~Application() {
        clearUsers();
        cout << "[Application] Деструктор\n";
    }

    void addUser(User* user) {
        users.push_back(user);
        userCountInApp++;
    }

    Application& operator+(User* user) {
        addUser(user);
        return *this;
    }

    Application& operator++() {
        cout << "[++app] Добавление Guest по умолчанию\n";
        addUser(new Guest());
        return *this;
    }

    Application operator++(int) {
        cout << "[app++] Добавление Administrator по умолчанию\n";
        Application temp(*this);
        addUser(new Administrator());
        return temp;
    }

    User* operator[](int index) {
        if (index >= 0 && index < static_cast<int>(users.size()))
            return users[index];
        return nullptr;
    }

    friend ostream& operator<<(ostream& os, const Application& app) {
        os << "=== Приложение: " << app.appName << " (" << app.requiredMemory << " МБ) ===\n";
        for (auto u : app.users)
            u->displayAll();
        return os;
    }

    static int getUserCountInApp() {
        return userCountInApp;
    }
};
int Application::userCountInApp = 0;

// ===== main() =====
int main() {
    cout << "1. Объектов User до создания: " << User::getObjectCount() << endl;
    cout << "2. Объектов в приложении: " << Application::getUserCountInApp() << endl;

    Application app("User Manager", 100);

    app + new Administrator("admin1", "admin123", 10);
    app + new Guest("guest1", "guest123", 30);
    app + new Guest("guest2", "guest456", 60);

    ++app;
    app++;

    cout << app;

    cout << "\n3. Объектов User после создания: " << User::getObjectCount() << endl;
    cout << "4. Объектов в приложении: " << Application::getUserCountInApp() << endl;

    cout << "\nПроверка доступа по индексу:\n";
    for (int i = 0; i < Application::getUserCountInApp(); ++i) {
        cout << "Пользователь [" << i << "]: ";
        User* u = app[i];
        if (u)
            u->displayAll();
        else
            cout << "NULL\n";
    }

    return 0;
}