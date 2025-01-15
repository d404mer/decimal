#include "binary.h"
#include "decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  int result = 0;

  if (s21_valid_decimal(&a) && s21_valid_decimal(&b)) {
    int sign_a = (a.bits[3] >> 31) & 1;
    int sign_b = (b.bits[3] >> 31) & 1;

    if (sign_a != sign_b) {
      result = sign_a > sign_b;
    } else {
      s21_decimal a_copy = a;
      s21_decimal b_copy = b;
      int last_digit = 0;

      level_decimals(&a_copy, &b_copy, &last_digit);

      int i = 2;
      while (i >= 0 && a_copy.bits[i] == b_copy.bits[i]) {
        i--;
      }

      if (i >= 0) {
        if (!sign_a) {
          result = a_copy.bits[i] < b_copy.bits[i];
        } else {
          result = a_copy.bits[i] > b_copy.bits[i];
        }
      }
    }
  }
  return result;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int result = 0;

  if (s21_valid_decimal(&a) && s21_valid_decimal(&b)) {
    dec_map *a_map = (dec_map *)&a;
    dec_map *b_map = (dec_map *)&b;

    if (decimal_is_zero(a_map) && decimal_is_zero(b_map)) {
      result = 1;
    } else if (a_map->sign == b_map->sign) {
      dec_map a_copy = *a_map;
      dec_map b_copy = *b_map;
      int last_digit = 0;

      level_decimals((s21_decimal *)&a_copy, (s21_decimal *)&b_copy,
                     &last_digit);

      dec_map diff = sub_mantisses(b_copy, a_copy);
      result = decimal_is_zero(&diff);
    }
  }

  return result;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int result = !s21_is_equal(a, b);
  return result;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int result = s21_is_less(a, b) || s21_is_equal(a, b);
  return result;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int result = s21_is_less(b, a);
  return result;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int result = !s21_is_less(a, b);
  return result;
}