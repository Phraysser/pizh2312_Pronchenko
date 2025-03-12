import json
from typing import Type


class Deposit:
    """Базовый класс для банковского вклада"""

    def __init__(self, amount: float, interest_rate: float, term: int):
        """
        :param amount: сумма вклада
        :param interest_rate: процентная ставка (в процентах)
        :param term: срок вклада в годах
        """
        self.amount = amount
        self.interest_rate = interest_rate
        self.term = term

    def calculate_profit(self) -> float:
        """Вычисляет прибыль по вкладу (простые проценты)"""
        return self.amount * (self.interest_rate / 100) * self.term

    def __str__(self) -> str:
        """Представление объекта в строковом виде"""
        return f"Вклад: {self.amount} руб., ставка: {self.interest_rate}%, срок: {self.term} лет"

    def __add__(self, other: "Deposit") -> "Deposit":
        """Позволяет складывать вклады"""
        return Deposit(self.amount + other.amount, (self.interest_rate + other.interest_rate) / 2, max(self.term, other.term))

    def __sub__(self, other: "Deposit") -> "Deposit":
        """Позволяет вычитать вклады"""
        new_amount = max(0, self.amount - other.amount)
        return Deposit(new_amount, self.interest_rate, self.term)

    def save(self, filename: str):
        """Сохраняет объект в JSON-файл"""
        with open(filename, "w") as f:
            json.dump(self.__dict__, f)

    @classmethod
    def load(cls: Type["Deposit"], filename: str) -> "Deposit":
        """Загружает объект из JSON-файла"""
        with open(filename, "r") as f:
            data = json.load(f)
        return cls(**data)

    @classmethod
    def from_string(cls: Type["Deposit"], str_value: str) -> "Deposit":
        """Создает объект из строки формата 'amount,interest_rate,term'"""
        amount, interest_rate, term = map(float, str_value.split(","))
        return cls(amount, interest_rate, int(term))


class BonusDeposit(Deposit):
    """Класс для бонусного вклада"""

    def __init__(self, amount: float, interest_rate: float, term: int, bonus_threshold: float, bonus_rate: float):
        super().__init__(amount, interest_rate, term)
        self.bonus_threshold = bonus_threshold
        self.bonus_rate = bonus_rate

    def calculate_profit(self) -> float:
        """Вычисляет прибыль с учетом бонуса"""
        profit = super().calculate_profit()
        if self.amount >= self.bonus_threshold:
            profit += profit * (self.bonus_rate / 100)
        return profit


class CapitalizedDeposit(Deposit):
    """Класс для вклада с капитализацией процентов"""

    def calculate_profit(self) -> float:
        """Вычисляет прибыль по сложным процентам"""
        return self.amount * ((1 + self.interest_rate / 100) ** self.term - 1)
