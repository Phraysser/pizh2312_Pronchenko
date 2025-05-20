#include <iostream>
#include <string>
using namespace std;

// Базовый класс
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
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;
        cout << "Введите роль: ";
        cin >> role;
    }

    virtual void display() const {
        cout << "Логин: " << login << ", Пароль: " << password << ", Роль: " << role << endl;
    }
};

// Класс-наследник Administrator
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
        cout << "[Administrator] Ввод данных:\n";
        User::input();
        cout << "Введите уровень доступа: ";
        cin >> accessLevel;
    }

    void display() const override {
        cout << "[Administrator] ";
        User::display();
        cout << "Уровень доступа: " << accessLevel << endl;
    }
};

// Класс-наследник Guest
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
        cout << "[Guest] Ввод данных:\n";
        User::input();
        cout << "Введите длительность сессии (в минутах): ";
        cin >> sessionDuration;
    }

    void display() const override {
        cout << "[Guest] ";
        User::display();
        cout << "Длительность сессии: " << sessionDuration << " мин\n";
    }
};

// Главная функция
int main() {
    cout << "\n=== Создание объектов ===\n";

    User user1("login1", "pass1", "User");
    Administrator admin1("admin1", "admin123", 5);
    Guest guest1("guest1", "guest123", 60);

    user1.display();
    admin1.display();
    guest1.display();

    cout << "\n=== Массив объектов базового класса (User*) ===\n";

    const int SIZE = 4;
    User* users[SIZE];
    users[0] = new User("base", "basepass", "User");
    users[1] = new Administrator("admin2", "adminpass", 10);
    users[2] = new Guest("guest2", "guestpass", 30);
    users[3] = new Administrator("admin3", "pass3", 8);

    for (int i = 0; i < SIZE; i++) {
        users[i]->display();
    }

    // Освобождение памяти
    for (int i = 0; i < SIZE; i++) {
        delete users[i];
    }

    cout << "\n=== Массив объектов одного класса-наследника (Guest) ===\n";

    const int GSIZE = 2;
    Guest guestArray[GSIZE] = {
        Guest("guestA", "passA", 20),
        Guest("guestB", "passB", 45)
    };

    for (int i = 0; i < GSIZE; i++) {
        guestArray[i].display();
    }

    return 0;
}
