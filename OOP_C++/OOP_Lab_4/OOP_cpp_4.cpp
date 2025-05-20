#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Чисто виртуальный базовый класс
class User {
protected:
    string login;
    string password;
    string role;

public:
    User() : login(""), password(""), role("User") {
        cout << "[User] Конструктор без параметров\n";
    }

    User(string l, string p, string r) : login(l), password(p), role(r) {
        cout << "[User] Конструктор с параметрами\n";
    }

    User(const User& other) : login(other.login), password(other.password), role(other.role) {
        cout << "[User] Конструктор копирования\n";
    }

    virtual ~User() {
        cout << "[User] Деструктор\n";
    }

    virtual void input() {
        cout << "Логин: "; cin >> login;
        cout << "Пароль: "; cin >> password;
        cout << "Роль: "; cin >> role;
    }

    virtual void display() const {
        cout << "Логин: " << login << ", Пароль: " << password << ", Роль: " << role << endl;
    }

    // Чисто виртуальная функция
    virtual void displayAll() const = 0;
};

// Наследник Administrator
class Administrator : public User {
private:
    int accessLevel;

public:
    Administrator() : User(), accessLevel(0) {
        role = "Administrator";
        cout << "[Administrator] Конструктор без параметров\n";
    }

    Administrator(string l, string p, int level) : User(l, p, "Administrator"), accessLevel(level) {
        cout << "[Administrator] Конструктор с параметрами\n";
    }

    Administrator(const Administrator& other) : User(other), accessLevel(other.accessLevel) {
        cout << "[Administrator] Конструктор копирования\n";
    }

    ~Administrator() override {
        cout << "[Administrator] Деструктор\n";
    }

    void input() override {
        User::input();
        cout << "Уровень доступа: "; cin >> accessLevel;
    }

    void display() const override {
        cout << "[Administrator] "; User::display();
    }

    void displayAll() const override {
        display();
        cout << "Уровень доступа: " << accessLevel << endl;
    }
};

// Наследник Guest
class Guest : public User {
private:
    int sessionDuration;

public:
    Guest() : User(), sessionDuration(0) {
        role = "Guest";
        cout << "[Guest] Конструктор без параметров\n";
    }

    Guest(string l, string p, int duration) : User(l, p, "Guest"), sessionDuration(duration) {
        cout << "[Guest] Конструктор с параметрами\n";
    }

    Guest(const Guest& other) : User(other), sessionDuration(other.sessionDuration) {
        cout << "[Guest] Конструктор копирования\n";
    }

    ~Guest() override {
        cout << "[Guest] Деструктор\n";
    }

    void input() override {
        User::input();
        cout << "Длительность сессии (мин): "; cin >> sessionDuration;
    }

    void display() const override {
        cout << "[Guest] "; User::display();
    }

    void displayAll() const override {
        display();
        cout << "Длительность сессии: " << sessionDuration << " мин\n";
    }
};

// Основной класс "Приложение"
class Application {
private:
    string appName;
    int requiredMemoryMB;
    vector<User*> users; // теперь массив указателей на базовый класс

public:
    Application() : appName(""), requiredMemoryMB(0) {
        cout << "[Application] Конструктор без параметров\n";
    }

    Application(string name, int mem) : appName(name), requiredMemoryMB(mem) {
        cout << "[Application] Конструктор с параметрами\n";
    }

    ~Application() {
        for (auto u : users)
            delete u;
        cout << "[Application] Деструктор\n";
    }

    void setAppInfo(string name, int mem) {
        appName = name;
        requiredMemoryMB = mem;
    }

    void addUser(User* user) {
        users.push_back(user);
    }

    void showAllUsers() const {
        cout << "Приложение: " << appName << " (" << requiredMemoryMB << " МБ)" << endl;
        cout << "Пользователи:\n";
        for (auto u : users)
            u->displayAll();
    }
};

// Главная функция
int main() {
    cout << "\n=== Массив пользователей (User*) ===\n";
    vector<User*> userArray;

    userArray.push_back(new Administrator("adminX", "passX", 7));
    userArray.push_back(new Guest("guestX", "passG", 25));
    userArray.push_back(new Administrator("adminY", "passY", 10));
    userArray.push_back(new Guest("guestY", "passY", 60));

    for (User* u : userArray) {
        u->displayAll(); // Вызов переопределённого метода
    }

    cout << "\n=== Работа с классом Application ===\n";
    Application app("User Manager", 150);
    app.addUser(new Administrator("adminApp", "admin123", 9));
    app.addUser(new Guest("guestApp", "guest123", 45));

    app.showAllUsers();

    // Очистка
    for (User* u : userArray)
        delete u;

    return 0;
}
