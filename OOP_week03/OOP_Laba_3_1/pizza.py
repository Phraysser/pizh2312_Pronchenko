class Pizza:
    """Базовый класс для представления пиццы."""

    def __init__(self, name: str, dough: str, sauce: str, toppings: list[str]):
        self.name = name
        self.dough = dough
        self.sauce = sauce
        self.toppings = toppings

    def __str__(self) -> str:
        return f"{self.name} (Тесто: {self.dough}, Соус: {self.sauce}, Начинка: {', '.join(self.toppings)})"


class PepperoniPizza(Pizza):
    def __init__(self):
        super().__init__("Пепперони", "Тонкое", "Томатный", ["Пепперони", "Сыр Моцарелла"])


class BBQPizza(Pizza):
    def __init__(self):
        super().__init__("Барбекю", "Классическое", "Барбекю", ["Курица", "Сыр Чеддер", "Лук"])


class SeafoodPizza(Pizza):
    def __init__(self):
        super().__init__("Дары Моря", "Толстое", "Сливочный", ["Креветки", "Мидии", "Кальмары", "Сыр Пармезан"])