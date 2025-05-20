#include <iostream>
#include <vector>
#include <string>
using namespace std;

// === Базовый класс ===
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

    virtual string getRole() const {
        return role;
    }
};

// === Администратор ===
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

// === Гость ===
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

    void extendSession(int extraMinutes) {
        sessionDuration += extraMinutes;
    }

    int getDuration() const {
        return sessionDuration;
    }
};

// === Главная функция ===
int main() {
    // === Контейнер из указателей на базовый класс ===
    cout << "\n=== Контейнер vector<User*> ===\n";
    vector<User*> users;

    users.push_back(new Administrator("admin1", "pass1", 5));
    users.push_back(new Guest("guest1", "pass2", 30));
    users.push_back(new Guest("guest2", "pass3", 60));

    cout << "\n→ Просмотр через индекс:\n";
    for (size_t i = 0; i < users.size(); ++i)
        users[i]->display();

    // === Удалим первого пользователя и изменим второго ===
    cout << "\n→ Удаление первого и изменение второго:\n";
    delete users[0];
    users.erase(users.begin());

    Guest* g = dynamic_cast<Guest*>(users[0]);
    if (g) g->extendSession(15);

    // === Просмотр через итератор ===
    cout << "\n→ Просмотр через итераторы:\n";
    for (auto it = users.begin(); it != users.end(); ++it)
        (*it)->display();

    // Очистка памяти
    for (User* u : users) delete u;
    users.clear();

    // === Контейнер объектов одного пользовательского типа ===
    cout << "\n=== Контейнер vector<Guest> ===\n";
    vector<Guest> guestList;
    guestList.emplace_back("guestA", "123", 20);
    guestList.emplace_back("guestB", "456", 45);
    guestList.emplace_back("guestC", "789", 60);

    cout << "\n→ Исходные данные:\n";
    for (const Guest& g : guestList) g.display();

    // Удаление 2-го, изменение 1-го
    guestList.erase(guestList.begin() + 1);
    guestList[0].extendSession(10);

    cout << "\n→ После удаления и изменения:\n";
    for (auto it = guestList.begin(); it != guestList.end(); ++it)
        it->display();

    return 0;
}
