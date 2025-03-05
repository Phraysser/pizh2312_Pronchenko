from abc import ABC, abstractmethod


class Animal(ABC):
    """Абстрактный базовый класс для всех животных."""
    
    def __init__(self, part: int):
        """Инициализирует объект животного."""
        self._part = max(0, min(100, part))  # Инкапсуляция значения (от 0 до 100)

    @abstractmethod
    def make_sound(self) -> str:
        """Абстрактный метод для создания звука животного."""
        pass

    def get_part(self) -> int:
        """Возвращает текущую часть животного."""
        return self._part

    def set_part(self, value: int) -> None:
        """Устанавливает новую часть животного с ограничением 0-100."""
        self._part = max(0, min(100, value))

    def __str__(self) -> str:
        """Возвращает строковое представление животного."""
        return f"{self.__class__.__name__} with part {self._part}"


class Bee(Animal):
    """Класс Пчела, наследуется от Animal."""
    
    def make_sound(self) -> str:
        return "buzz"

    def __str__(self) -> str:
        return super().__str__() + " and it buzzes"


class Elephant(Animal):
    """Класс Слон, наследуется от Animal."""
    
    def make_sound(self) -> str:
        return "tu-tu-doo-doo!"

    def __str__(self) -> str:
        return super().__str__() + " and it trumpets"


class BeeBlephant:
    """Гибрид пчелы и слона, использующий композицию Bee и Elephant."""
    
    def __init__(self, bee_part: int, elephant_part: int):
        self.bee = Bee(bee_part)
        self.elephant = Elephant(elephant_part)

    def fly(self) -> bool:
        """Может ли гибрид летать? Да, если часть пчелы >= части слона."""
        return self.bee.get_part() >= self.elephant.get_part()

    def trumpet(self) -> str:
        """Какой звук издает гибрид? Зависит от частей животных."""
        return "wizzi" if self.bee.get_part() > self.elephant.get_part() else "tu-tu-doo-doo!"

    def eat(self, meal: str, value: int) -> None:
        """
        Изменяет части пчелы и слона в зависимости от типа пищи.
        
        - 'nectar' увеличивает часть пчелы, уменьшает часть слона.
        - 'grass' уменьшает часть пчелы, увеличивает часть слона.
        """
        if meal == 'nectar':
            self.bee.set_part(self.bee.get_part() + value)
            self.elephant.set_part(self.elephant.get_part() - value)
        elif meal == 'grass':
            self.bee.set_part(self.bee.get_part() - value)
            self.elephant.set_part(self.elephant.get_part() + value)
        else:
            raise ValueError("Unknown meal type")

    def get_parts(self) -> tuple[int, int]:
        """Возвращает кортеж (часть пчелы, часть слона)."""
        return self.bee.get_part(), self.elephant.get_part()

    def __call__(self) -> str:
        """Возвращает строковое представление объекта BeeBlephant."""
        return f"BeeBlephant with bee part {self.bee.get_part()} and elephant part {self.elephant.get_part()}"


# Тестирование
be = BeeBlephant(3, 2)
print(be.fly())  # True
print(be.trumpet())  # wizzi
be.eat('grass', 4)
print(be.get_parts())  # (0, 6)
print(be())  # BeeBlephant with bee part 0 and elephant part 6

be = BeeBlephant(13, 87)
print(be.fly())  # False
print(be.trumpet())  # tu-tu-doo-doo!
be.eat('nectar', 90)
print(be.trumpet())  # wizzi
print(be.get_parts())  # (100, 0)
print(be())  # BeeBlephant with bee part 100 and elephant part 0
