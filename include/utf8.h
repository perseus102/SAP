#pragma once
/* Convert the multibyte character at S, which is no longer
   than N characters, to its `wchar_t' representation, placing
   this in *USTR and returning the length of the multibyte character.  */
int utf8_mbtowc (wchar_t *ustr, const char *s, size_t n);

/* Convert UC into its multibyte character representation,
   putting this in S and returning the multibyte character length.  */
int utf8_wctomb (char *s, const wchar_t uc);

/* Return the length of the multibyte character (if there is one)
   at S which is no longer than N characters.  */
int utf8_mblen(const char *s, size_t n);

/* Convert the string of multibyte characters in S to `wchar_t's in
   USTR, writing no more than N wchar_t's.  Return the number of Unicode
   characters, or (size_t) -1 if an invalid multibyte character is
   encountered.  */
size_t utf8_mbstowcs(register wchar_t *ustr, register const char *s, register size_t n);

/* Convert the `wchar_t' string in USTR to a multibyte character string
   in S, writing no more than N bytes.  Return the number of bytes
   written (process until the end of USTR, or the first invalid
   `wchar_t' found.)  */
size_t utf8_wcstombs(register char *s, register const wchar_t *ustr, register size_t n);

char *wchar_to_utf8(const wchar_t *wchar_str);
wchar_t *utf8_to_wchar(const char *utf8_str);