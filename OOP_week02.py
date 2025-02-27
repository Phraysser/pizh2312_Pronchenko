class BeeElephant:
    def __init__(self, bee_part: int, elephant_part: int):
        """
        Инициализирует объект BeeElephant с частями пчелы и слона.
        :param bee_part: Часть пчелы (от 0 до 100)
        :param elephant_part: Часть слона (от 0 до 100)
        """
        self.bee_part: int = bee_part
        self.elephant_part: int = elephant_part

    def fly(self):
        """
        Проверяет, может ли объект летать (если часть пчелы больше или равна части слона).
        :return: True, если может летать, иначе False
        """
        return self.bee_part >= self.elephant_part

    def trumpet(self):
        """
        Издает звук, зависящий от пропорций частей пчелы и слона.
        :return: "tu-tu-doo-doo!", если часть слона больше или равна части пчелы, иначе "wzzzzz"
        """
        if self.elephant_part >= self.bee_part:
            return "tu-tu-doo-doo!"
        else:
            return "wzzzzz"

    def eat(self, meal: str, value: int):
        """
        Меняет пропорции частей пчелы и слона в зависимости от съеденной еды.
        :param meal: Тип еды ('nectar' увеличивает часть пчелы, 'grass' увеличивает часть слона)
        :param value: Количество съеденной еды
        """
        if meal == 'nectar':
            self.elephant_part = max(0, self.elephant_part - value)
            self.bee_part = min(100, self.bee_part + value)
        elif meal == 'grass':
            self.bee_part = max(0, self.bee_part - value)
            self.elephant_part = min(100, self.elephant_part + value)

    def get_parts(self):
        """
        Возвращает список с текущими значениями частей пчелы и слона.
        :return: Список из двух элементов: [bee_part, elephant_part]
        """
        return [self.bee_part, self.elephant_part]

# Пример 1
be = BeeElephant(3, 2)
print(be.fly())  # True
print(be.trumpet())  # wzzzzz
be.eat('grass', 4)
print(be.get_parts())  # [0, 6]

# Пример 2
be = BeeElephant(13, 87)
print(be.fly())  # False
print(be.trumpet())  # tu-tu-doo-doo!
be.eat('nectar', 90)
print(be.trumpet())  # wzzzzz
print(be.get_parts())  # [100, 0]
