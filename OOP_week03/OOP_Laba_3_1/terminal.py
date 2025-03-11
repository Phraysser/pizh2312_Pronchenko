from order import Order
from pizza import PepperoniPizza, BBQPizza, SeafoodPizza

class Terminal:
    """Класс для работы терминала заказов."""

    def __init__(self):
        self.orders: list[Order] = []

    def take_order(self):
        """Создает заказ, добавляет пиццы и сохраняет его."""
        customer_name = input("Введите ваше имя: ")
        order = Order(customer_name)

        while True:
            print("\nВыберите пиццу:")
            print("1 - Пепперони")
            print("2 - Барбекю")
            print("3 - Дары Моря")
            print("0 - Завершить заказ")

            choice = input("Ваш выбор: ")

            if choice == "1":
                order.add_pizza(PepperoniPizza())
                print("Пепперони добавлена в заказ.")
            elif choice == "2":
                order.add_pizza(BBQPizza())
                print("Барбекю добавлена в заказ.")
            elif choice == "3":
                order.add_pizza(SeafoodPizza())
                print("Дары Моря добавлена в заказ.")
            elif choice == "0":
                if order.get_total_pizzas() > 0:
                    self.orders.append(order)
                    print("\nЗаказ оформлен:")
                    print(order)
                else:
                    print("Вы не добавили ни одной пиццы.")
                break
            else:
                print("Некорректный ввод, попробуйте снова.")

    def show_orders(self):
        """Выводит список всех заказов."""
        if not self.orders:
            print("Заказов пока нет.")
        else:
            print("\nВсе заказы:")
            for order in self.orders:
                print(order)
                print("-" * 30)