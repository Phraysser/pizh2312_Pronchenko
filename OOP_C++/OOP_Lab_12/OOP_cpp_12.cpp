#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class User {
protected:
    string login;
    string password;
    string role;

public:
    User() : login(""), password(""), role("User") {}
    User(string l, string p, string r) : login(l), password(p), role(r) {}
    virtual ~User() {}

    virtual void display() const {
        cout << "Логин: " << login << ", Пароль: " << password << ", Роль: " << role << endl;
    }
};

class Guest : public User {
private:
    int sessionDuration;

public:
    Guest() : User(), sessionDuration(0) {
        role = "Guest";
    }

    Guest(string l, string p, int duration) : User(l, p, "Guest"), sessionDuration(duration) {}

    void display() const override {
        cout << "[Guest] ";
        User::display();
        cout << "Длительность сессии: " << sessionDuration << " мин\n";
    }

    int getDuration() const {
        return sessionDuration;
    }

    // Для сортировки по возрастанию
    bool operator<(const Guest& other) const {
        return sessionDuration < other.sessionDuration;
    }
};

int main() {
    list<Guest> guestList = {
        Guest("guest1", "pass1", 45),
        Guest("guest2", "pass2", 25),
        Guest("guest3", "pass3", 60),
        Guest("guest4", "pass4", 15),
        Guest("guest5", "pass5", 35)
    };

    cout << "\n→ Список гостей (исходный):\n";
    for (const auto& g : guestList)
        g.display();

    // Сортировка по убыванию с помощью лямбды
    guestList.sort([](const Guest& a, const Guest& b) {
        return a.getDuration() > b.getDuration();
    });

    cout << "\n→ Отсортировано по убыванию (длительность):\n";
    for (const auto& g : guestList)
        g.display();

    // Поиск первого гостя с длительностью > 30 с помощью лямбды
    auto found = find_if(guestList.begin(), guestList.end(), [](const Guest& g) {
        return g.getDuration() > 30;
    });

    if (found != guestList.end()) {
        cout << "\n→ Найден первый с длительностью > 30:\n";
        found->display();
    }

    // Перенос в другой контейнер (vector) гостей с длительностью > 30 с помощью лямбды
    vector<Guest> selectedGuests;
    copy_if(guestList.begin(), guestList.end(), back_inserter(selectedGuests), [](const Guest& g) {
        return g.getDuration() > 30;
    });

    cout << "\n→ Новый контейнер (vector), гости с >30 минут:\n";
    for (const auto& g : selectedGuests)
        g.display();

    // Сортировка обоих контейнеров по возрастанию с использованием operator<
    guestList.sort(); // сортировка list по возрастанию (operator<)

    sort(selectedGuests.begin(), selectedGuests.end()); // vector

    cout << "\n→ Список гостей (list), отсортирован по возрастанию:\n";
    for (const auto& g : guestList)
        g.display();

    cout << "\n→ Второй контейнер (vector), отсортирован по возрастанию:\n";
    for (const auto& g : selectedGuests)
        g.display();

    return 0;
}
