class Roman:
    ROMAN_NUMERAL_MAP: dict[str, int] = {
        'I': 1, 'IV': 4, 'V': 5, 'IX': 9, 'X': 10,
        'XL': 40, 'L': 50, 'XC': 90, 'C': 100,
        'CD': 400, 'D': 500, 'CM': 900, 'M': 1000
    }

    def __init__(self, value: str | int):
        """
        Инициализация римского числа.
        :param value: Строка (римское число) или целое число.
        """
        if isinstance(value, str):
            self.value: int = self.roman_to_int(value)
            self.roman: str = value
        elif isinstance(value, int):
            if value <= 0:
                raise ValueError("Римские числа должны быть положительными.")
            self.value: int = value
            self.roman: str = self.int_to_roman(value)
        else:
            raise TypeError("Неверный тип данных. Используйте строку или целое число.")

    @staticmethod
    def roman_to_int(roman: str) -> int:
        """
        Конвертирует римское число в целое.
        :param roman: Строка с римским числом.
        :return: Целое число.
        """
        result: int = 0
        i: int = 0
        numerals: dict[str, int] = Roman.ROMAN_NUMERAL_MAP
        sorted_numerals: list[str] = sorted(numerals.keys(), key=lambda x: -len(x))  # Упорядочиваем ключи по длине

        while i < len(roman):
            for numeral in sorted_numerals:
                if roman[i:i + len(numeral)] == numeral:
                    result += numerals[numeral]
                    i += len(numeral)
                    break
        return result

    @staticmethod
    def int_to_roman(number: int) -> str:
        """
        Конвертирует целое число в римское.
        :param number: Целое число.
        :return: Строка с римским числом.
        """
        result: str = ""
        for numeral, integer in sorted(Roman.ROMAN_NUMERAL_MAP.items(), key=lambda x: -x[1]):
            while number >= integer:
                result += numeral
                number -= integer
        return result

    def __add__(self, other: "Roman") -> "Roman":
        return Roman(self.value + other.value)

    def __sub__(self, other: "Roman") -> "Roman":
        if self.value - other.value <= 0:
            raise ValueError("Результат вычитания должен быть положительным числом.")
        return Roman(self.value - other.value)

    def __mul__(self, other: "Roman") -> "Roman":
        return Roman(self.value * other.value)

    def __floordiv__(self, other: "Roman") -> "Roman":
        if other.value == 0:
            raise ZeroDivisionError("Деление на ноль невозможно.")
        return Roman(self.value // other.value)

    def __truediv__(self, other: "Roman") -> "Roman":
        return self.__floordiv__(other)

    def __repr__(self) -> str:
        return f"Roman('{self.roman}')"

    def __str__(self) -> str:
        return self.roman
