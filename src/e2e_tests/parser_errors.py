from .utils import execute_programme
import unittest


class ParserTestCases(unittest.TestCase):
    def test_good_code(self):
        """Tests that good code is accepted"""
        stdin = """<?php
        declare(strict_types=1);

        $x = "Hello world";
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_missing_dollar_sign_in_variable(self):
        stdin = """<?php
            declare(strict_types=1);
            x = "Hello world"
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_missing_semicolon(self):
        stdin = """<?php
            declare(strict_types=1);
            $x = "Hello world"
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_wrong_function_definition(self):
        stdin = """<?php
            declare(strict_types=1);
            function hello_world( {
                $x = "Hello world";
            }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_wrong_function_definition_2(self):
        stdin = """<?php
            declare(strict_types=1);
            function hello_world) {
                $x = "Hello world";
            }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_wrong_function_definition_3(self):
        stdin = """<?php
            declare(strict_types=1);
            function hello_world(x) {
                $x = "Hello world";
            }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_proper_function_definition(self):
        stdin = """<?php
                declare(strict_types=1);
                function hello_world(int $x): int {
                    return $x;
                }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_function_call(self):
        stdin = """<?php
            declare(strict_types=1);
            
            function bar(string $x): string {
                return $x;
            }
            
            function foo(string $x):string {
                return bar($x");
            }
            
            foo("Hello world");
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_factorial_code(self):
        stdin = """<?php
                    declare(strict_types=1);
                    // Program 1: Vypocet faktorialu (iterativne)
                    // Hlavni telo programu
                    write("Zadejte cislo pro vypocet faktorialu\n");
                    $a = readi();
                    if ($a === null) {
                    write("Chyba pri nacitani celeho cisla!\n");
                    } else {}
                    if ($a < 0) {
                    write("Faktorial nelze spocitat\n");
                    } else {
                    $vysl = 1;
                    while ($a > 0) {
                    11
                    $vysl = $vysl * $a;
                    $a = $a - 1;
                    }
                    write("Vysledek je: ", $vysl, "\n");
                    }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)