from abc import ABC, abstractmethod

class MoneyTransfer(ABC):
    """Абстрактный базовый класс для денежных переводов"""

    def __init__(self, amount: float, sender: str, receiver: str):
        """Инициализация перевода"""
        self.amount = amount
        self.sender = sender
        self.receiver = receiver

    @abstractmethod
    def execute(self):
        """Абстрактный метод для выполнения перевода"""
        pass

    def __str__(self) -> str:
        return f"Перевод {self.amount} от {self.sender} к {self.receiver}"


class PostalTransfer(MoneyTransfer):
    """Класс почтового перевода"""

    def execute(self):
        """Реализация выполнения почтового перевода"""
        print(f"📨 Почтовый перевод: {self.amount} RUB отправлен от {self.sender} к {self.receiver}.")


class BankTransfer(MoneyTransfer):
    """Класс банковского перевода"""

    def __init__(self, amount: float, sender: str, receiver: str, bank_name: str):
        """Дополнительный параметр — название банка"""
        super().__init__(amount, sender, receiver)
        self.bank_name = bank_name

    def execute(self):
        """Реализация выполнения банковского перевода"""
        print(f"🏦 Банковский перевод: {self.amount} RUB через {self.bank_name} отправлен от {self.sender} к {self.receiver}.")


class CurrencyTransfer(MoneyTransfer):
    """Класс валютного перевода"""

    def __init__(self, amount: float, sender: str, receiver: str, currency: str, exchange_rate: float):
        """Дополнительные параметры: валюта и курс обмена"""
        super().__init__(amount, sender, receiver)
        self.currency = currency
        self.exchange_rate = exchange_rate

    def execute(self):
        """Реализация выполнения валютного перевода"""
        converted_amount = self.amount * self.exchange_rate
        print(f"💱 Валютный перевод: {self.amount} {self.currency} ({converted_amount:.2f} RUB) отправлен от {self.sender} к {self.receiver}.")
