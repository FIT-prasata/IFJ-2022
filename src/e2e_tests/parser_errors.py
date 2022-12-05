from .utils import execute_programme
import unittest

class ParserTestCases(unittest.TestCase):
    def test_missig_dollar_sign_in_variable(self):
        stdin = """
            <?php
            declare(strict_types=1);
            x = "Hello world"
        """
        self.assertEqual(execute_programme(stdin)[0], 2)