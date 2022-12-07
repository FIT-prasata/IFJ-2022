from .utils import execute_programme
import unittest


class ExprTestCases(unittest.TestCase):
    def test_valid_assignment(self):
        stdin = """<?php
        declare(strict_types=1);
        $x = 1+1;
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_valid_complex_assignment(self):
        stdin = """<?php
        declare(strict_types=1);
        $x = ((1)+1);
        $y = $x + 1;
        """
        self.assertEqual(execute_programme(stdin)[0], 0)

    def test_invalid_assignment(self):
        stdin = """<?php
        declare(strict_types=1);
        $x = 1++;
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_invalid_complex_assignment(self):
        stdin = """<?php
        declare(strict_types=1);
        $x = ((1)+1)));
        """
        self.assertEqual(execute_programme(stdin)[0], 2)

    def test_undefined_variable(self):
        stdin = """<?php
        declare(strict_types=1);
        $x = $y;
        """
        self.assertEqual(execute_programme(stdin)[0], 5)