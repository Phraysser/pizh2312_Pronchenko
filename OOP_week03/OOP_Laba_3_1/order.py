from pizza import Pizza
import random

class Order:
    """Класс для представления заказа."""

    def __init__(self, customer_name: str) -> None:
        self.customer_name = customer_name
        self.pizzas: list[Pizza] = []
        self.order_number = random.randint(1000, 9999)

    def add_pizza(self, pizza: Pizza) -> None:
        """Добавляет пиццу в заказ."""
        self.pizzas.append(pizza)

    def get_total_pizzas(self) -> int:
        """Возвращает количество пицц в заказе."""
        return len(self.pizzas)

    def __str__(self) -> str:
        pizza_list = "\n".join([f"- {pizza}" for pizza in self.pizzas])
        return (f"Заказ #{self.order_number} для {self.customer_name}\n"
                f"Пиццы:\n{pizza_list}\n"
                f"Всего пицц: {self.get_total_pizzas()}")