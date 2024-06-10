t = int(input())  # Количество наборов входных данных

for _ in range(t):
    m, x = map(int, input().split())  # Количество месяцев и ежемесячная зарплата
    happiness = [tuple(map(int, input().split())) for _ in range(m)]  # Список кортежей: (стоимость, счастье)

    # Сортируем список кортежей по стоимости
    happiness.sort()

    max_happiness = [0] * (m + 1)  # Массив для хранения максимального счастья для каждого месяца

    # Проходим по каждому месяцу и рассматриваем возможные варианты потратить деньги
    for cost, happy in happiness:
        for i in range(m, 0, -1):
            # Если Чарли может себе позволить это счастье в текущем месяце
            # и если оно больше, чем уже полученное счастье в более поздних месяцах
            if cost <= x and happy > max_happiness[i]:
                max_happiness[i] = happy

    # Суммируем максимальное счастье для каждого месяца
    total_happiness = sum(max_happiness)

    print(total_happiness)