import json
from typing import List, Any


class LineSegmentContainer:
    """Класс-контейнер для хранения объектов"""

    def __init__(self):
        """Инициализация контейнера с пустым списком данных"""
        self._data: List[Any] = []

    def __str__(self) -> str:
        """Представление объекта в строковом виде"""
        return f"LineSegmentContainer({self._data})"

    def __getitem__(self, index: int):
        """Позволяет получать элементы контейнера по индексу"""
        return self._data[index]

    def add(self, value: Any):
        """Добавляет элемент в контейнер"""
        self._data.append(value)

    def remove(self, index: int):
        """Удаляет элемент по индексу"""
        if 0 <= index < len(self._data):
            self._data.pop(index)
        else:
            raise IndexError("Индекс вне диапазона")

    def save(self, filename: str):
        """Сохраняет контейнер в JSON-файл"""
        with open(filename, "w") as f:
            json.dump([str(item) for item in self._data], f)

    def load(self, filename: str):
        """Загружает контейнер из JSON-файла"""
        with open(filename, "r") as f:
            self._data = json.load(f)
