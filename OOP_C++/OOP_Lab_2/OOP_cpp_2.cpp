#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Класс Пользователь
class User {
private:
    string login;
    string password;
    string role;

public:
    // Конструктор по умолчанию
    User() : login(""), password(""), role("user") {
        cout << "Вызван конструктор без параметров класса User" << endl;
    }

    // Конструктор с параметрами
    User(string l, string p, string r) : login(l), password(p), role(r) {
        cout << "Вызван конструктор с параметрами класса User" << endl;
    }

    // Конструктор копирования
    User(const User& other) : login(other.login), password(other.password), role(other.role) {
        cout << "Вызван конструктор копирования класса User" << endl;
    }

    // Деструктор
    ~User() {
        cout << "Вызван деструктор класса User (пользователь: " << login << ")" << endl;
    }

    void display() const {
        cout << "Логин: " << login << ", Пароль: " << password << ", Роль: " << role << endl;
    }
};

// Класс Приложение
class Application {
private:
    string name;
    int sizeMb;
    vector<User> users;

public:
    // Конструктор по умолчанию
    Application() : name(""), sizeMb(0) {
        cout << "Вызван конструктор без параметров класса Application" << endl;
    }

    // Конструктор с параметрами
    Application(string n, int s) : name(n), sizeMb(s) {
        cout << "Вызван конструктор с параметрами класса Application" << endl;
    }

    // Конструктор копирования
    Application(const Application& other) : name(other.name), sizeMb(other.sizeMb), users(other.users) {
        cout << "Вызван конструктор копирования класса Application" << endl;
    }

    // Деструктор
    ~Application() {
        cout << "Вызван деструктор класса Application (приложение: " << name << ")" << endl;
    }

    void addUser(const User& u) {
        users.push_back(u);
    }

    // Метод: создать пользователя с параметрами и добавить
    void createAndAddUser(string l, string p, string r) {
        User newUser(l, p, r); // вызов конструктора с параметрами
        users.push_back(newUser);
    }

    // Метод: добавить N копий пользователя
    void addCopiesOfUser(const User& u, int count) {
        for (int i = 0; i < count; ++i) {
            User copy(u); // вызов конструктора копирования
            users.push_back(copy);
        }
    }

    void display() const {
        cout << "\nНазвание приложения: " << name << endl;
        cout << "Размер: " << sizeMb << " Мб" << endl;
        cout << "Список пользователей:" << endl;
        for (const auto& u : users) {
            u.display();
        }
    }
};

// Основная программа
int main() {
    // Используем конструкторы
    Application app1; // по умолчанию
    app1 = Application("User Manager", 150); // с параметрами

    // Пользователь через параметрический конструктор
    User u1("admin", "admin123", "admin");

    // Пользователь через копирование
    User u2(u1);

    // Пользователь по умолчанию
    User u3;

    // Добавляем пользователей
    app1.addUser(u1);             // добавляем напрямую
    app1.createAndAddUser("guest", "guest123", "guest"); // через метод с параметрами
    app1.addCopiesOfUser(u2, 2);  // создаем копии и добавляем

    // Вывод информации
    app1.display();

    return 0;
}
