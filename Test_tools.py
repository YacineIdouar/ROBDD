import unittest
from code.Tools import *

class Tools_test(unittest.TestCase):
    def test_decomposition(self):
        self.assertEqual(decomposition(38),[False, True, True, False, False, True])
        self.assertEqual(decomposition(12),[False, False, True, True])
        self.assertEqual(decomposition(128),[False, False, False, False, False, False, False, True])

    def test_completion(self):
        self.assertEqual(completion(decomposition(38),2),[False, True])
        self.assertEqual(completion(decomposition(38),6),[False, True, True, False, False, True])
        self.assertEqual(completion(decomposition(38),13),[False, True, True, False, False, True, False, False, False, False, False, False, False])

        
    def test_table(self):
        self.assertEqual(table(38,2),[False, True])
        self.assertEqual(table(38,6),[False, True, True, False, False, True])
        self.assertEqual(table(38,13),[False, True, True, False, False, True, False, False, False, False, False, False, False])



if __name__ == '__main__':
    unittest.main()