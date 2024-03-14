from cyphers import cesar, replacement, vigenere


def main() -> None:
    print("Добро пожаловать в программу для шифрования текста!")

    isRunning = True
    while isRunning:
        print(
            "Шифрование или дешифрование? (1 - шифрование, 2 - дешифрование, 0 - выход)"
        )
        choose = input()
        crypt = False
        if choose == "1":
            crypt = True
        elif choose == "2":
            crypt = False
        elif choose == "0":
            isRunning = False
            continue
        else:
            print("Неизвестная команда")
            continue

        print("Выберите метод шифрования: (1 - шифр Цезаря, 2 - шифр замены, 3 - шифр Виженера)")
        choose = input()

        result = ""
        match choose:
            case "1":
                text = input("Введите текст для работы:\n")
                shift = int(input("Введите сдвиг для шифра Цезаря: "))
                result = cesar(text, shift if crypt else -shift)
            case "2":
                text = input("Введите текст для работы:\n")
                alph = input("Введите алфавит для шифра замены: ")
                result = replacement(text, alph, crypt)
            case "3":
                text = input("Введите текст для работы:\n")
                key = input("Введите ключ для шифра Виженера: ")
                result = vigenere(text, key, crypt)
            case _:
                print("Неизвестная команда")
                continue

        print("Результат работы алгоритма: ")
        print(result, end="\n\n")


if __name__ == "__main__":
    main()
