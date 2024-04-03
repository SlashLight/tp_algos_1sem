Это решения задач по алгоритмам на с++ с курса VK-education по веб-разработке

<h2>1 модуль</h3>

<h3><u>1 задача</u></h3>
Использование арифметических операций запрещено.
Входное число лежит в диапазоне 0..2^32 -1 и вводится в десятичном виде.
Подсчитать кол-во единичных бит в входном числе , стоящих на четных позициях. Позиции битов нумеруются с 0.

<h3><u>2 задача</u></h3>
Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
Требования:  Время работы поиска k для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.

<h3><u>3 задача</u></h3>
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

Реализовать очередь с динамическим зацикленным буфером (на основе динамического массива).
Требования: Очередь должна быть реализована в виде класса.

<h3><u>4 задача</u></h3>
Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..

<h3><u>5 задача</u></h3>
Необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции.
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.

<h3><u>6 задача</u></h3>
Дано множество целых чисел из [0..10^9] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль,
медиана,
90%  перцентиль

Требования: к дополнительной памяти: O(n).
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition.
Рекурсия запрещена.
Решение должно поддерживать передачу функции сравнения снаружи.


Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении
Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
<h3><u>7 задача</u></h3>
Дан массив строк. Количество строк не больше 105. Отсортировать массив методом поразрядной сортировки MSD по символам. Размер алфавита - 256 символов. Последний символ строки = ‘\0’