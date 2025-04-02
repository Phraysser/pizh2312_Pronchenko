import json
from typing import List
from linesegment import LineSegment  # Подключаем класс LineSegment

class LineSegmentContainer:
    """Класс-контейнер для хранения объектов LineSegment"""

    def __init__(self):
        """Инициализация контейнера с пустым списком данных"""
        self._data: List[LineSegment] = []

    def __str__(self) -> str:
        """Представление контейнера в строковом виде"""
        return f"LineSegmentContainer({[str(segment) for segment in self._data]})"

    def __getitem__(self, index: int) -> LineSegment:
        """Позволяет получать элементы контейнера по индексу"""
        return self._data[index]

    def add(self, value: LineSegment):
        """Добавляет объект LineSegment в контейнер"""
        if isinstance(value, LineSegment):
            self._data.append(value)
        else:
            raise TypeError("Можно добавлять только объекты LineSegment")

    def remove(self, index: int):
        """Удаляет элемент из контейнера по индексу"""
        if 0 <= index < len(self._data):
            self._data.pop(index)
        else:
            raise IndexError("Индекс вне диапазона")

    def save(self, filename: str):
        """Сохраняет контейнер в JSON-файл"""
        with open(filename, "w") as f:
            json.dump([segment.to_dict() for segment in self._data], f)

    def load(self, filename: str):
        """Загружает контейнер из JSON-файла"""
        with open(filename, "r") as f:
            segments_data = json.load(f)
            self._data = [LineSegment.from_dict(data) for data in segments_data]
