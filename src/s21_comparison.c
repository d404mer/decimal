#include "binary.h"
#include "decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  int result = 0;

  if (s21_valid_decimal(&a) && s21_valid_decimal(&b)) {
    dec_map *a_map = (dec_map *)&a;
    dec_map *b_map = (dec_map *)&b;

    if (a_map->sign != b_map->sign) {
      result = a_map->sign > b_map->sign;
    } else {
      dec_map a_copy = *a_map;
      dec_map b_copy = *b_map;

      level_decimals((s21_decimal *)&a_copy, (s21_decimal *)&b_copy);

      if (!decimal_is_zero(&a_copy) || !decimal_is_zero(&b_copy)) {
        dec_map diff = sub_mantisses(b_copy, a_copy);
        result = (a_map->sign) ? !diff.sign : diff.sign;
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

    if (a_map->sign == b_map->sign) {
      dec_map a_copy = *a_map;
      dec_map b_copy = *b_map;

      level_decimals((s21_decimal *)&a_copy, (s21_decimal *)&b_copy);
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