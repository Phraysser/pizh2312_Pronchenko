import math
from typing import Dict

class LineSegment:
    """Класс, представляющий отрезок на плоскости"""

    def __init__(self, x1: float, y1: float, x2: float, y2: float):
        """Инициализация отрезка с координатами (x1, y1) и (x2, y2)"""
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2

    def __str__(self) -> str:
        """Возвращает строковое представление отрезка"""
        return f"LineSegment(({self.x1}, {self.y1}) -> ({self.x2}, {self.y2}))"

    def length(self) -> float:
        """Вычисляет длину отрезка"""
        return math.sqrt((self.x2 - self.x1) ** 2 + (self.y2 - self.y1) ** 2)

    def to_dict(self) -> Dict[str, float]:
        """Конвертирует объект в словарь для сохранения"""
        return {"x1": self.x1, "y1": self.y1, "x2": self.x2, "y2": self.y2}

    @classmethod
    def from_dict(cls, data: Dict[str, float]) -> "LineSegment":
        """Создаёт объект из словаря"""
        return cls(data["x1"], data["y1"], data["x2"], data["y2"])
