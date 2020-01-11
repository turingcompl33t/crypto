## RSA Cryptosystem, in Python

I caved. It is trivial to implement RSA when the language handles arbitrary precision arithmetic for you.

### Padding Schemes

PKCS#1 v1.5 padding is implemented in accordance with the specification in [RFC 2313](https://tools.ietf.org/html/rfc2313).
