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

    def test_valid_funcdef_2(self):
        stdin = """<?php
            declare(strict_types=1);
            function hello_world(int $x, int $z): null {
                }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_if_statement(self):
        stdin = """<?php
        declare(strict_types=1);
        if (1) {
        }
        else {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_nested_if_statement(self):
        stdin = """<?php
        declare(strict_types=1);
        if (1) {
            if (1) {
            }
            else {}
        }
        else {}
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_nested_if_statement_2(self):
        stdin = """<?php
        declare(strict_types=1);
        if (1) {
            if (1) {
             if (1) {
             }
                else {}
            }
            else {}
        }
        else {
            if (1) {
            }
            else {}
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_invalid_if_statement(self):
        stdin = """<?php
        declare(strict_types=1);
        if (1) {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_if_statement_2(self):
        stdin = """<?php
        declare(strict_types=1);
        if (1) {
        }
        else
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_if_statement_3(self):
        stdin = """<?php
        declare(strict_types=1);
        if (1) {
        
        else {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_if_statement_4(self):
        stdin = """<?php
        declare(strict_types=1);
        if (1) {
        }
        else {
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_if_statement_5(self):
        stdin = """<?php
        declare(strict_types=1);
        if () {
        }
        else {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)


    def test_invalid_if_statement_6(self):
        stdin = """<?php
        declare(strict_types=1);
        if (1) {
        }
         {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_if_statement_complex_expression(self):
        stdin = """<?php
        declare(strict_types=1);
        if ((1 + 1)===((2*2)-2)) {
        }
        else {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_while_statement(self):
        stdin = """<?php
        declare(strict_types=1);
        while (1) {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_while_statement_nested(self):
        stdin = """<?php
        declare(strict_types=1);
        while (1) {
            while (1) {
             while (1) {
             }
            }
            while (1) {
            }
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_invalid_while_statement(self):
        stdin = """<?php
        declare(strict_types=1);
        while (1) {
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_while_statement_2(self):
        stdin = """<?php
        declare(strict_types=1);
        while (1) 
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_while_statement_3(self):
        stdin = """<?php
        declare(strict_types=1);
        while (1) {
        while (1) {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_while_statement_4(self):
        stdin = """<?php
        declare(strict_types=1);
        while () {}
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_while_statement_complex_expression(self):
        stdin = """<?php
        declare(strict_types=1);
        while ((1 + 1)===((2*2)-2)) {
        }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_func_def_with_return_and_params(self):
        stdin = """<?php
            declare(strict_types=1);
            function hello_world(int $x, int $z): int {
                return $x + $z + 2 * 10;
            }
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_func_def_with_return_and_params_invalid(self):
        stdin = """<?php
            declare(strict_types=1);
            function hello_world(int $x,): int {
                return $x + 2 * 10;
            }
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_func_def_with_return_and_params_undef_param(self):
        stdin = """<?php
            declare(strict_types=1);
            function hello_world(int $x): int {
                return $x + $y + 2 * 10;
            }
        """
        self.assertEqual(execute_programme(stdin)[0], 5)