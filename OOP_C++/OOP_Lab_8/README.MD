**Задание**
1. Дополнить и при необходимости модифицировать приложение,
разработанное согласно варианту лабораторной работы № 7. 
2. Написать программу, в которой перехватываются исключения типа
int, string. Сгенерировать исключительные ситуации.
3. Добавить к программе перехват любой исключительной ситуации
catch(…).
4. Добавить к программе перехват 2-3 исключительных ситуаций
стандартных типов (std::invalid_argument, std::length_error,
std::out_of_range или др.).
5. Создайть два собственных класса ошибки, наследуемых от стандартного. Добавить к программе перехват исключительных ситуаций созданных типов.
6. Программа должна демонстрировать обработку исключительных
ситуаций на верхнем уровне (функция main), возникающих при вложенных
вызовах методов объектов.
7. Программа должна демонстрировать локальную обработку исключительных ситуаций без передачи ее обработчику более высокого уровня.