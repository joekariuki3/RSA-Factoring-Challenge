<div align="center">

# RSA Factoring Challenge

Small command‑line utilities written in C for factoring semi-primes (numbers that are the product of two integers) as part of the ALX/Holberton RSA factoring challenge.

</div>

## 1. Background & Objective

The security of RSA public key cryptography is based (in part) on the practical difficulty of factoring the product of two large primes. This repository contains straightforward brute‑force style factorization programs used for an educational challenge. They read integers (one per line) from a file and output a factorization in the canonical form:

```
N=p*q
```

Where `p` and `q` are integers (> 1) such that `p * q = N`.

## 2. Features Summary

- Accepts an input file with one positive integer per line (values currently handled fit in signed 64‑bit range as implemented: `long long int`).
- For each integer, finds the first non‑trivial factor `i` by trial division starting at 2 and prints `N=N/i*i`.
- Stops searching once the first factor is found (not necessarily prime or the smallest in terms of prime factorization depth just the first divisor encountered in the linear scan).

## 3. Repository Structure

```
.
├── factors.c          # Simple factoring utility (trial division)
├── rsa.c              # Duplicate factoring approach (could diverge later)
├── factors.h          # Common headers
├── tests/
│   ├── test00         # Sample input set (mixed small & large numbers)
│   ├── test01         # Sample input set (variant)
│   └── rsa-1          # Another sample input set
├── README.md          # This documentation
└── resources.md       # Supplemental notes / references
```

## 4. Build Instructions

These are minimal single‑file C programs with no external dependencies beyond the standard C library.

### 4.1. Compile

```bash
gcc -O2 -std=c99 -Wall -Wextra -Werror -pedantic factors.c -o factors
gcc -O2 -std=c99 -Wall -Wextra -Werror -pedantic rsa.c -o rsa
```

You may relax warnings or standard selection depending on your environment. (The current code uses `long long int` and straightforward loops compatible with older standards as well.)

### 4.2. Clean

```bash
rm -f factors rsa
```

## 5. Usage

Each executable expects exactly one argument: the path to an input file containing one integer per line. Blank lines should be avoided (no trimming currently implemented). Example:

```bash
./factors tests/test00
```

### 5.1. Example Output

Given an input line `12`, output might be:

```
12=6*2
```

Because the program discovers the first divisor `i = 2` and prints `N=(N/i)*i` i.e. `12=(12/2)*2 = 6*2`.

For a larger composite like `1718944270642558716715` (example in `tests/test00`), the program will attempt trial division up to `N/2` (which is extremely inefficient for very large values and may take a long time). If a factor is found early, it returns quickly; otherwise it can run for a very long time.

### 5.2. Error Handling

- If the number of arguments ≠ 2, prints: `Usage: factors <file>` and exits with failure.
- If the file cannot be opened, prints: `Error: can't open <filename>` and exits with failure.
- Lines not conforming to a valid 64‑bit integer may yield undefined behavior (no robust validation presently).

## 6. Implementation Details

Core logic (from `factors.c` / `rsa.c`):

```c
for (i = 2; i <= num / 2; i++) {
	if (num % i == 0) {
		printf("%lld=%lld*%d\n", num, num / i, i);
		return;
	}
}
```

Notes:

- Complexity: Worst‑case O(N) trial divisions up to N/2. For primes or products of two large primes near sqrt(N), this is impractical for big N.
- The search could terminate at `i <= sqrt(num)`; continuing to `num/2` is unnecessary work (future optimization).
- `rsa.c` currently repeats the same algorithm (with a redundant condition `i % i == 0 && i % 1 == 0`). It can be consolidated or extended (e.g., to implement a better algorithm specifically for RSA semi‑primes).
- No multi‑precision support: limited by the width of `long long int` (typically 64 bits). Large RSA moduli (1024 bits and beyond) are far outside scope of this implementation.

## 7. Performance Considerations & Potential Optimizations

Current approach: naive trial division starting at 2.

Suggested improvements:

1. Stop at `i * i <= num` (saves roughly half the work for many inputs).
2. Handle even numbers specially (check 2, then skip all even divisors).
3. Use 6k ± 1 wheel to reduce candidate set further.
4. Implement Pollard's Rho algorithm for significantly faster factoring of large composites.
5. Add Miller–Rabin primality test to quickly skip primes (optional—if number is prime, report maybe `N=N*1` or skip printing per challenge spec if only composites expected).
6. Support big integers via a library (GMP) for realistic RSA‑sized moduli.
7. Parallelize trial division across cores.

## 8. Testing & Examples

You can run the included sample inputs:

```bash
./factors tests/test00 > out00.txt
./factors tests/test01 > out01.txt
./factors tests/rsa-1  > out_rsa1.txt
```

Inspect the outputs to verify factor pairs. You can compare with a quick Python script (not included) to validate correctness for moderate numbers.

## 9. Limitations

- Not suitable for genuinely large RSA modulus factoring; purely educational.
- No input sanitization beyond `fscanf` pattern.
- Only first found factorization printed (order may differ from canonical `p*q` where `p <= q`).
- Potential performance issues for large primes or near‑prime numbers (could run for minutes/hours depending on CPU and size).

## 10. Extending the Project

Possible future additions:

- Refactor common code into a reusable factoring module.
- Add `Makefile` with targets: `all`, `clean`, `test`, `opt`.
- Implement faster algorithms (Pollard's Rho, Fermat, Quadratic Sieve scaffolding).
- Add unit tests and benchmarking harness.
- Provide Python or Rust re‑implementations for comparison.
- Add GitHub Actions CI to build & run small correctness tests.

## 11. Contributing

1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/improve-factor`.
3. Commit changes with clear messages.
4. Open a Pull Request describing: motivation, changes, performance impact (if any).

Please keep code style simple and consistent (K&R / ANSI C). Avoid unnecessary global state.

## 12. License

MIT LICENSE

## 13. References & Further Reading

- Rivest, Shamir, Adleman. A Method for Obtaining Digital Signatures and Public-Key Cryptosystems (1978).
- Pollard's Rho Algorithm: https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
- Integer Factorization Overview: https://en.wikipedia.org/wiki/Integer_factorization
- Miller–Rabin Primality Test: https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
- GMP Library: https://gmplib.org/

## 14. Quick Start (TL;DR)

```bash
git clone https://github.com/joekariuki3/RSA-Factoring-Challenge.git
cd RSA-Factoring-Challenge
gcc -O2 factors.c -o factors
./factors tests/test00
```

## 15. Disclaimer

This code is intentionally naive and for learning purposes only. Do NOT use it for real cryptographic workloads.

---

Feel free to open issues for clarifications or improvement ideas.
