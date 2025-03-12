from linesegment import LineSegmentContainer

def main():
    container = LineSegmentContainer()

    # Добавляем элементы
    container.add("Отрезок A-B")
    container.add("Отрезок C-D")
    container.add("Отрезок E-F")

    print(f"Контейнер после добавления элементов: {container}")

    # Получение элемента по индексу
    print(f"Элемент с индексом 1: {container[1]}")

    # Удаление элемента
    container.remove(1)
    print(f"Контейнер после удаления элемента: {container}")

    # Сохранение в файл
    container.save("container.json")

    # Загрузка из файла
    new_container = LineSegmentContainer()
    new_container.load("container.json")
    print(f"Загруженный контейнер: {new_container}")

if __name__ == "__main__":
    main()
