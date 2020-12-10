#ifndef LOX_STRING_H
#define LOX_STRING_H
int lox_is_int_number(float f);
char *lox_replace_string(char *src, char *target, char *rep_val);
char *lox_string_repeat(char *src, int cnt);
int lox_string_tolower(char *src);

#endif // LOX_STRING_H
