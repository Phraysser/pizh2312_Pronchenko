#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===== Базовый класс =====
class User {
private:
    static int objectCount; // Статический счётчик объектов

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

    virtual void displayAll() const = 0; // Чисто виртуальная функция

    static int getObjectCount() {
        return objectCount;
    }
};

int User::objectCount = 0; // Инициализация счётчика

// ===== Класс-наследник Administrator =====
class Administrator : public User {
private:
    int accessLevel;

public:
    Administrator() : User(), accessLevel(0) {
        role = "Administrator";
        cout << "[Administrator] Конструктор\n";
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
        cout << "[Administrator] Логин: " << login
             << ", Пароль: " << password
             << ", Уровень доступа: " << accessLevel << endl;
    }
};

// ===== Класс-наследник Guest =====
class Guest : public User {
private:
    int sessionDuration;

public:
    Guest() : User(), sessionDuration(0) {
        role = "Guest";
        cout << "[Guest] Конструктор\n";
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
        cout << "[Guest] Логин: " << login
             << ", Пароль: " << password
             << ", Длительность сессии: " << sessionDuration << " мин\n";
    }
};

// ===== Основной класс Application =====
class Application {
private:
    string appName;
    int requiredMemory;
    vector<User*> users;

    static int userCountInApp; // Счётчик пользователей в приложении

public:
    Application() : appName(""), requiredMemory(0) {
        cout << "[Application] Конструктор\n";
    }

    Application(string name, int mem) : appName(name), requiredMemory(mem) {
        cout << "[Application] Конструктор с параметрами\n";
    }

    ~Application() {
        for (auto u : users)
            delete u;
        cout << "[Application] Деструктор\n";
    }

    void addUser(User* user) {
        users.push_back(user);
        userCountInApp++;
    }

    static int getUserCountInApp() {
        return userCountInApp;
    }

    void showAllUsers() const {
        cout << "=== Приложение: " << appName << " (" << requiredMemory << " МБ) ===\n";
        for (auto u : users)
            u->displayAll();
    }
};

int Application::userCountInApp = 0; // Инициализация статического поля

// ===== Основная функция main() =====
int main() {
    cout << "1. Объектов User до создания: " << User::getObjectCount() << endl;
    cout << "2. Объектов в приложении: " << Application::getUserCountInApp() << endl;

    // Создаём объект приложения
    Application app("User Manager", 100);

    // Добавляем пользователей
    app.addUser(new Administrator("admin1", "admin123", 10));
    app.addUser(new Guest("guest1", "guest123", 30));
    app.addUser(new Guest("guest2", "guest456", 60));

    // Вывод данных
    app.showAllUsers();

    cout << "\n3. Объектов User после создания: " << User::getObjectCount() << endl;
    cout << "4. Объектов в приложении: " << Application::getUserCountInApp() << endl;

    return 0;
}
