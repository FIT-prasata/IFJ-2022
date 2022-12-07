from .utils import execute_programme
import unittest


class ParserTestCases(unittest.TestCase):
    def test_function_definition_and_call(self):
        stdin = """<?php
        declare(strict_types=1);
                function hello_world(int $x): null {
                }
        hello_world(1);
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_undeclared_function_call(self):
        stdin = """<?php
        declare(strict_types=1);
        hello_world(1);
        """
        self.assertEqual(execute_programme(stdin)[0], 3)

    def test_invalid_function_definition_wrong_arg_format(self):
        stdin = """<?php
        declare(strict_types=1);
        function hello_world(int x): null {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_function_definition_wrong_arg_format_2(self):
        stdin = """<?php
        declare(strict_types=1);
        function hello_world($x): null {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_function_definition_wrong_arg_format_3(self):
        stdin = """<?php
        declare(strict_types=1);
        function hello_world(int $x,): null {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_function_definition_no_return_type(self):
        stdin = """<?php
        declare(strict_types=1);
        function hello_world(int $x) {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_function_definition_no_return_type_2(self):
        stdin = """<?php
        declare(strict_types=1);
        function hello_world(int $x): {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_function_definition_wrongly_typed_return_type(self):
        stdin = """<?php
        declare(strict_types=1);
        function hello_world(int $x) int {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_function_definition_missing_rcbracket(self):
        stdin = """<?php
        declare(strict_types=1);
        function hello_world(int $x): null {
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_function_definition_missing_lcbracket(self):
        stdin = """<?php
        declare(strict_types=1);
        function hello_world(int $x): null 
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)
