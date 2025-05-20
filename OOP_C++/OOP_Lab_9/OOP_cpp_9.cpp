#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

// ===== Базовый класс =====
class User {
protected:
    string login;
    string password;
    string role;

public:
    User() : login(""), password(""), role("User") {
        cout << "[User] Конструктор (без параметров)\n";
    }

    User(string l, string p, string r) : login(l), password(p), role(r) {
        cout << "[User] Конструктор (с параметрами)\n";
    }

    User(const User& other) : login(other.login), password(other.password), role(other.role) {
        cout << "[User] Конструктор копирования\n";
    }

    virtual ~User() {
        cout << "[User] Деструктор\n";
    }

    virtual void displayAll() const = 0;
    virtual User* clone() const = 0;

    friend ostream& operator<<(ostream& os, const User& u) {
        os << u.role << " " << u.login << " " << u.password;
        return os;
    }

    friend istream& operator>>(istream& is, User& u) {
        is >> u.role >> u.login >> u.password;
        return is;
    }

    string getRole() const { return role; }
    string getLogin() const { return login; }
    string getPassword() const { return password; }
};

// ===== Класс Administrator =====
class Administrator : public User {
    int accessLevel;

public:
    Administrator() : User(), accessLevel(0) {
        role = "Administrator";
        cout << "[Administrator] Конструктор (по умолчанию)\n";
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

    void displayAll() const override {
        cout << "[Administrator] Логин: " << login
             << ", Пароль: " << password
             << ", Уровень доступа: " << accessLevel << endl;
    }

    User* clone() const override {
        return new Administrator(*this);
    }

    friend ostream& operator<<(ostream& os, const Administrator& a) {
        os << "Administrator " << a.login << " " << a.password << " " << a.accessLevel;
        return os;
    }

    friend istream& operator>>(istream& is, Administrator& a) {
        is >> a.login >> a.password >> a.accessLevel;
        return is;
    }
};

// ===== Класс Guest =====
class Guest : public User {
    int sessionDuration;

public:
    Guest() : User(), sessionDuration(0) {
        role = "Guest";
        cout << "[Guest] Конструктор (по умолчанию)\n";
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

    void displayAll() const override {
        cout << "[Guest] Логин: " << login
             << ", Пароль: " << password
             << ", Длительность сессии: " << sessionDuration << " мин\n";
    }

    User* clone() const override {
        return new Guest(*this);
    }

    friend ostream& operator<<(ostream& os, const Guest& g) {
        os << "Guest " << g.login << " " << g.password << " " << g.sessionDuration;
        return os;
    }

    friend istream& operator>>(istream& is, Guest& g) {
        is >> g.login >> g.password >> g.sessionDuration;
        return is;
    }
};

// ===== Класс Application =====
class Application {
    string appName;
    int requiredMemory;
    vector<User*> users;

    void clearUsers() {
        for (auto u : users) delete u;
        users.clear();
    }

public:
    Application() : appName(""), requiredMemory(0) {
        cout << "[Application] Конструктор\n";
    }

    Application(string name, int mem) : appName(name), requiredMemory(mem) {
        cout << "[Application] Конструктор с параметрами\n";
    }

    Application(const Application& other) {
        appName = other.appName;
        requiredMemory = other.requiredMemory;
        for (auto u : other.users) users.push_back(u->clone());
        cout << "[Application] Конструктор копирования\n";
    }

    Application& operator=(const Application& other) {
        if (this != &other) {
            clearUsers();
            appName = other.appName;
            requiredMemory = other.requiredMemory;
            for (auto u : other.users) users.push_back(u->clone());
        }
        return *this;
    }

    ~Application() {
        clearUsers();
        cout << "[Application] Деструктор\n";
    }

    void addUser(User* user) {
        users.push_back(user);
    }

    void saveToFile(const string& filename) {
        ofstream out(filename);
        if (!out) throw runtime_error("Ошибка открытия файла для записи");

        out << appName << " " << requiredMemory << " " << users.size() << "\n";
        for (User* u : users) {
            if (u->getRole() == "Administrator") {
                out << *(dynamic_cast<Administrator*>(u)) << "\n";
            } else if (u->getRole() == "Guest") {
                out << *(dynamic_cast<Guest*>(u)) << "\n";
            }
        }
        out.close();
    }

    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) throw runtime_error("Ошибка открытия файла для чтения");

        clearUsers();
        int count;
        in >> appName >> requiredMemory >> count;
        for (int i = 0; i < count; ++i) {
            string role;
            in >> role;
            if (role == "Administrator") {
                auto* a = new Administrator();
                in >> *a;
                addUser(a);
            } else if (role == "Guest") {
                auto* g = new Guest();
                in >> *g;
                addUser(g);
            }
        }
        in.close();
    }

    void showUsers() const {
        cout << "\n=== Приложение: " << appName << " (" << requiredMemory << " МБ) ===\n";
        for (auto u : users) u->displayAll();
    }
};

// ===== main =====
int main() {
    try {
        Application app("UserManager", 100);
        app.addUser(new Administrator("admin", "1234", 5));
        app.addUser(new Guest("guest1", "guest123", 30));
        app.addUser(new Guest("guest2", "guest456", 45));

        app.showUsers();

        cout << "\n→ Сохраняем в файл 'data.txt'\n";
        app.saveToFile("data.txt");

        cout << "\n→ Загружаем из файла в новый объект\n";
        Application loadedApp;
        loadedApp.loadFromFile("data.txt");
        loadedApp.showUsers();

    } catch (exception& e) {
        cerr << "[!] Исключение: " << e.what() << endl;
    }

    return 0;
}
