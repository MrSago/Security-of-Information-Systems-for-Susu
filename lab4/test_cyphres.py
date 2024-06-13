import unittest
from cyphers import cesar, replacement, vigenere


class TestCyphers(unittest.TestCase):
    def test_cesar_encrypt(self):
        self.assertEqual(cesar("hello world", 3), "khoor zruog")
        self.assertEqual(cesar("the quick brown fox", 13), "gur dhvpx oebja sbk")

    def test_cesar_decrypt(self):
        self.assertEqual(cesar("khoor zruog", -3), "hello world")
        self.assertEqual(cesar("gur dhvpx oebja sbk", -13), "the quick brown fox")

    def test_replacement_encrypt(self):
        self.assertEqual(
            replacement("hello world", "zyxwvutsrqponmlkjihgfedcba", True),
            "svool dliow",
        )
        self.assertEqual(
            replacement("the quick brown fox", "qwertyuiopasdfghjklzxcvbnm", True),
            "zit jxoea wkgvf ygb",
        )

    def test_replacement_decrypt(self):
        self.assertEqual(
            replacement("svool dliow", "zyxwvutsrqponmlkjihgfedcba", False),
            "hello world",
        )

        self.assertEqual(
            replacement("zit jxoea wkgvf ygb", "qwertyuiopasdfghjklzxcvbnm", False),
            "the quick brown fox",
        )

    def test_vigenere_encrypt(self):
        self.assertEqual(vigenere("hello world", "key", True), "rijvs uyvjn")
        self.assertEqual(
            vigenere("the quick brown fox", "cipher", True), "vpt xyzes qysnp nde"
        )

    def test_vigenere_decrypt(self):
        self.assertEqual(vigenere("rijvs uyvjn", "key", False), "hello world")
        self.assertEqual(
            vigenere("vpt xyzes qysnp nde", "cipher", False), "the quick brown fox"
        )


if __name__ == "__main__":
    unittest.main()
