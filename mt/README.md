### Mersenne Twister Pseudorandom Number Generator

An implementation of the Mersenne Twister pseudorandom number generator, as originally described by [Matsumoto and Nishimura](http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/mt.pdf). 

The implementation allows for parametrization of the PRNG. Currently, the parameters defined in `mt.c` implement the popular MT19337 variant of the Mersenne Twister. 

### Build

For a standard test run:

```
$ make
```

To clean up after yourself:

```
$ make clean
```

### Correctness

This implementation produces a sequence of pseudorandom values that is identical to that produced by the original implementation, under the same seed. 
