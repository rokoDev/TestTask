# TestTask

=============== Существует условный контейнер для записей (строк), который хранит их в сортированном порядке. Записи постоянно добавляются и удаляются. При этом из контейнера с той же периодичностью считываются данные по порядковому номеру. Например добавляем строчку "gs", при считывании элемента по 0 индексу ее же и получим. Затем добавляем "bnj", соответственно в нулевой позиции будет строка "bnj", в первой - "gs". При добавлении "kju" первые две записи не поменяют свое место, а последняя строка будет доступна по индексу 2. Итого необходимо реализовать контейнер, который будет иметь следующее api: - вставить новый элемент (строка), - удалить элемент (строку), - получить элемент по порядковому номеру с учетом сортировки. Контейнер должен успевать обрабатывать 100K операций в секунду. Для проверки алгоритма необходимо использовать приложенные тестовые данные. Файл insert.txt - последовательность рандомных строк. Файл read.txt - последовательность рандомных индексов и соотвествующих строк разделенные пробелом. Алгоритм проверки должен быть итеративным - вставляете один элемент из insert.txt, затем считываете из контейнера запись по индексу из read.txt. Результат должен совпасть с соответствующей строкой из read.txt. =============== 