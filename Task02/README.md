### Task 2: Compare Expectations with Execution & Analysis

**Objective:** Compare integer-paise, `float`, and `double` accumulation for 4,000, 60,000, and 800,000 electricity bills.

**Method:** The program adds a bill of ₹950 repeatedly using three representations: integer paise (`long long`), `float` rupees, and `double` rupees. It prints the data-type sizes, ranges or precision indicators, and accumulated totals.

**Expected results:**

| Number of bills | Expected total (rupees) | Expected total (paise) |
|---:|---:|---:|
| 4,000 | ₹3,800,000.00 | 380,000,000 |
| 60,000 | ₹57,000,000.00 | 5,700,000,000 |
| 800,000 | ₹760,000,000.00 | 76,000,000,000 |

**Analysis of data types:**

- **`int`:** On this system, a 32-bit signed `int` cannot store 76 billion paise. Its maximum value is 2,147,483,647.
- **`long`:** On 64-bit Windows using the MinGW-w64 toolchain, `long` is commonly 32 bits, so it also cannot store the district total in paise.
- **`long long`:** A 64-bit signed `long long` can store 76 billion paise safely.
- **`float`:** Has limited precision. Repeated additions can accumulate rounding error, particularly as the total grows.
- **`double`:** Has greater precision than `float` and is expected to represent these totals accurately when adding ₹950 repeatedly. However, binary floating-point cannot represent every decimal fraction exactly.
- **Integer paise:** Is preferred for monetary calculations because the bill is stored in whole paise and the district total fits in `long long`.

**Complexity analysis:**

For \(n\) bills, each approach performs \(n\) additions, so total time complexity is \(O(n)\). Each approach uses a fixed number of accumulator variables, so auxiliary space complexity is \(O(1)\).

| Approach | Time per addition | Typical accumulator size |
|---|---|---:|
| `long long` integer paise | \(O(1)\) | 8 bytes |
| `float` | \(O(1)\) | 4 bytes |
| `double` | \(O(1)\) | 8 bytes |

**Conclusion:** Integer paise with a sufficiently wide integer accumulator is the most reliable option for exact billing. The program's actual output should be recorded and compared with the expected totals to identify floating-point differences. The sizes and ranges should be confirmed using the program's `sizeof` and limits output.

**Compiler:** GCC 16.2.0  
**Compile command:** `gcc -std=c11 -Wall -Wextra task2.c -o task2.exe`  
**Run command:** `./task2.exe`
