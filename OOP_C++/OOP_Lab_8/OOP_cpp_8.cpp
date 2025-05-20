#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

// ===== Классы исключений =====
class MyAppException : public std::exception {
    string msg;
public:
    MyAppException(const string& m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class UserLogicError : public logic_error {
public:
    UserLogicError(const string& msg) : logic_error(msg) {}
};

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

    void riskyOperation(int code) {
        if (code == 0) throw 0;
        if (code == 1) throw string("Ошибка типа string");
        if (code == 2) throw invalid_argument("Неверный аргумент");
        if (code == 3) throw length_error("Слишком длинное значение");
        if (code == 4) throw MyAppException("Ошибка приложения");
        if (code == 5) throw UserLogicError("Логическая ошибка пользователя");
        if (code == 6) throw out_of_range("Выход за пределы");
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
        throw out_of_range("Индекс вне диапазона массива пользователей");
    }

    void testExceptions(int code) {
        try {
            riskyOperation(code);
        }
        catch (const invalid_argument& e) {
            cout << "[!] std::invalid_argument: " << e.what() << endl;
        }
        catch (const length_error& e) {
            cout << "[!] std::length_error: " << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cout << "[!] std::out_of_range: " << e.what() << endl;
        }
        catch (const MyAppException& e) {
            cout << "[!] MyAppException: " << e.what() << endl;
        }
        catch (const UserLogicError& e) {
            cout << "[!] UserLogicError: " << e.what() << endl;
        }
        catch (int e) {
            cout << "[!] Исключение типа int: " << e << endl;
        }
        catch (string& e) {
            cout << "[!] Исключение типа string: " << e << endl;
        }
        catch (...) {
            cout << "[!] Неизвестное исключение!" << endl;
        }
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
    try {
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
            try {
                app[i]->displayAll();
            }
            catch (const exception& e) {
                cout << "[!] Ошибка: " << e.what() << endl;
            }
        }

        cout << "\nТестирование исключений:\n";
        for (int code = 0; code <= 6; ++code) {
            cout << "\n[Тест " << code << "]\n";
            app.testExceptions(code);
        }

        cout << "\n[!] Пример глобального перехвата исключения:\n";
        throw out_of_range("Ошибка из main()");
    }
    catch (const out_of_range& e) {
        cout << "[main()] std::out_of_range: " << e.what() << endl;
    }
    catch (...) {
        cout << "[main()] Необработанное исключение в main\n";
    }

    return 0;
}
