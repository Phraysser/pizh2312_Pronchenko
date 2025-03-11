from terminal import Terminal

if __name__ == "__main__":
    terminal = Terminal()

    while True:
        print("\n1 - Сделать заказ")
        print("2 - Показать все заказы")
        print("0 - Выйти")

        choice = input("Выберите действие: ")

        if choice == "1":
            terminal.take_order()
        elif choice == "2":
            terminal.show_orders()
        elif choice == "0":
            print("Выход из программы.")
            break
        else:
            print("Некорректный ввод, попробуйте снова.")
