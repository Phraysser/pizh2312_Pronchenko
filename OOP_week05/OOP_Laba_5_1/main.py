from linesegment import LineSegment
from linesegment_container import LineSegmentContainer

def main():
    # Создаем контейнер
    container = LineSegmentContainer()

    # Добавляем отрезки
    segment1 = LineSegment(0, 0, 3, 4)
    segment2 = LineSegment(1, 2, 5, 6)
    
    container.add(segment1)
    container.add(segment2)

    print(f"Контейнер после добавления элементов: {container}")

    # Получаем элемент по индексу
    print(f"Первый отрезок: {container[0]}")

    # Удаляем элемент
    container.remove(1)
    print(f"Контейнер после удаления второго отрезка: {container}")

    # Сохраняем в файл
    container.save("segments.json")

    # Загружаем из файла
    new_container = LineSegmentContainer()
    new_container.load("segments.json")
    print(f"Загруженный контейнер: {new_container}")

if __name__ == "__main__":
    main()
