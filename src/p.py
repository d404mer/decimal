import ctypes
from decimal import Decimal


lib = ctypes.CDLL('./decimal.so')  



class S21Decimal(ctypes.Structure):
    _fields_ = [("bits", ctypes.c_uint32 * 4)]


lib.wrapper_s21_is_less.argtypes = [S21Decimal, S21Decimal]
lib.wrapper_s21_is_less.restype = ctypes.c_int

lib.wrapper_s21_is_equal.argtypes = [S21Decimal, S21Decimal]
lib.wrapper_s21_is_equal.restype = ctypes.c_int


def decimal_to_s21_decimal(py_decimal):
    """Converts Python Decimal to s21_decimal."""
    
    
    return S21Decimal((0, 0, 0, 0))


if __name__ == '__main__':
    number = Decimal('1234567890123456789012345678')
    add = Decimal('0.12')
    res = number + add
    print("Python Decimal addition result:", res)

    
    a_c = decimal_to_s21_decimal(number)
    b_c = decimal_to_s21_decimal(add)

    
    is_less = lib.wrapper_s21_is_less(a_c, b_c)
    print("C comparison (is_less):", bool(is_less))
