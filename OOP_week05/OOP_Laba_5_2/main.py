from transfer import PostalTransfer, BankTransfer, CurrencyTransfer

def main():
    # Почтовый перевод
    postal = PostalTransfer(5000, "Иван", "Петр")
    print(postal)
    postal.execute()

    # Банковский перевод
    bank = BankTransfer(15000, "Анна", "Сергей", "Сбербанк")
    print(bank)
    bank.execute()

    # Валютный перевод
    currency = CurrencyTransfer(200, "Екатерина", "Дмитрий", "USD", 92.5)
    print(currency)
    currency.execute()

if __name__ == "__main__":
    main()
