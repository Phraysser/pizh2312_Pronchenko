from deposit import Deposit, BonusDeposit, CapitalizedDeposit

def main():
    # Обычный вклад
    deposit1 = Deposit(1000, 5, 3)
    deposit2 = Deposit(500, 4, 2)

    print(f"Прибыль по обычному вкладу: {deposit1.calculate_profit():.2f}")
    print(f"Сложение вкладов: {(deposit1 + deposit2)}")
    print(f"Вычитание вкладов: {(deposit1 - deposit2)}")

    # Сохранение и загрузка объекта
    deposit1.save("deposit.json")
    loaded_deposit = Deposit.load("deposit.json")
    print(f"Загруженный вклад: {loaded_deposit}")

    # Создание объекта из строки
    new_deposit = Deposit.from_string("1500,3.5,4")
    print(f"Созданный из строки вклад: {new_deposit}")

if __name__ == "__main__":
    main()
