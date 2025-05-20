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
    // Конструкторы
    User() : login(""), password(""), role("") {}

    void setUser(string l, string p, string r) {
        login = l;
        password = p;
        role = r;
    }

    void setUser(string l, string p) {
        login = l;
        password = p;
        role = "user"; // по умолчанию
    }

    void setUser(string l) {
        login = l;
        password = "1234"; // по умолчанию
        role = "user";
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
    vector<User> users; // Массив пользователей (доп. класс)

public:
    Application() : name(""), sizeMb(0) {}

    void setName(string n) {
        name = n;
    }

    void setSize(int size) {
        sizeMb = size;
    }

    void addUser(User u) {
        users.push_back(u);
    }

    void display() const {
        cout << "Название приложения: " << name << endl;
        cout << "Размер: " << sizeMb << " Мб" << endl;
        cout << "Пользователи:" << endl;
        for (const auto& u : users) {
            u.display();
        }
    }
};

// Основная функция
int main() {
    // Создание объекта приложения
    Application app;
    app.setName("User Manager");
    app.setSize(150);

    // Создание пользователей
    User u1, u2, u3;
    u1.setUser("admin", "admin123", "admin");
    u2.setUser("guest", "guest123");
    u3.setUser("testuser");

    // Добавление пользователей в приложение
    app.addUser(u1);
    app.addUser(u2);
    app.addUser(u3);

    // Вывод информации
    app.display();

    return 0;
}
