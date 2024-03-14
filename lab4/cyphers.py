ALPHABET = "abcdefghijklmnopqrstuvwxyz"


def cesar(text: str, shift: int) -> str:
    text = text.lower()
    shift = shift % len(ALPHABET)

    result = ""
    for char in text:
        if char.isalpha() and char in ALPHABET:
            ascii_number = (ord(char) - ord("a") + shift) % len(ALPHABET) + ord("a")
            result += chr(ascii_number)
        else:
            result += char

    return result


def replacement(text: str, key: str, is_crypted: bool = True) -> str:
    text = text.lower()
    key = key.lower()

    result = ""

    for char in text:
        if char.isalpha() and char in ALPHABET:
            if is_crypted:
                index = ALPHABET.index(char)
                result += key[index].lower()
            else:
                index = key.index(char)
                result += ALPHABET[index].lower()
        else:
            result += char

    return result


def vigenere(text: str, key: str, is_crypted: bool = True) -> str:
    text = text.lower()
    key = key.lower()

    repeated_key = (key * (len(text) // len(key))) + key[: len(text) % len(key)]

    result = ""
    index = 0
    for char in text:
        if char.isalpha() and char in ALPHABET:
            shift = ord(repeated_key[index].lower()) - ord("a")
            if is_crypted:
                result += chr((ord(char) - ord("a") + shift) % 26 + ord("a"))
            else:
                result += chr((ord(char) - ord("a") - shift) % 26 + ord("a"))
            index += 1
        else:
            result += char

    return result
