from deposit import Deposit, BonusDeposit, CapitalizedDeposit

def main():
    # Создание обычного вклада
    deposit1 = Deposit(amount=1000, interest_rate=5, term=3)
    deposit2 = Deposit(amount=500, interest_rate=4, term=2)

    print(f"Прибыль по обычному вкладу: {deposit1.calculate_profit():.2f}")

    # Использование __str__
    print(f"Информация о вкладе: {deposit1}")

    # Использование сложения и вычитания вкладов
    combined_deposit = deposit1 + deposit2
    print(f"Сложенный вклад: {combined_deposit}")

    reduced_deposit = deposit1 - deposit2
    print(f"Вклад после вычитания: {reduced_deposit}")

    # Использование метода save и load
    deposit1.save("deposit.json")
    loaded_deposit = Deposit.load("deposit.json")
    print(f"Загруженный вклад: {loaded_deposit}")

    # Создание вклада из строки
    new_deposit = Deposit.from_string("1500,3.5,4")
    print(f"Созданный из строки вклад: {new_deposit}")

    # Бонусный вклад
    bonus_deposit = BonusDeposit(amount=2000, interest_rate=5, term=3, bonus_threshold=1500, bonus_rate=10)
    print(f"Прибыль по бонусному вкладу: {bonus_deposit.calculate_profit():.2f}")

    # Вклад с капитализацией процентов
    capitalized_deposit = CapitalizedDeposit(amount=1000, interest_rate=5, term=3)
    print(f"Прибыль по вкладу с капитализацией: {capitalized_deposit.calculate_profit():.2f}")

if __name__ == "__main__":
    main()
