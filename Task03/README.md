### Task 3: Recommend and Defend the Final Design

**Recommendation:** Use fixed-width integer types for meter readings and monetary calculations. Store meter readings in `uint16_t`, consumption in `uint32_t`, and bill totals in `int64_t`. Represent monetary values in integer paise to avoid floating-point rounding during bill calculation.

**Evidence from experiments:** Task 1 tests showed correct slab billing, including ₹275.00 for 200 units and ₹950.00 for 350 units. The rollover test from 65535 to 0 correctly produced one unit. Invalid letters, negative readings, and an implausible decrease were rejected. Task 2 showed that `int` and `long` on this system cannot hold the district total of 76,000,000,000 paise, while `long long` can. Repeated `float` accumulation differed from the expected total by ₹4,526,016 for 800,000 bills, whereas `double` matched the expected total in the experiment.

**Tariff revision:** With compile-time constants, the tariff values are changed in one place and the program is recompiled and redistributed. Header files, include guards, and `#ifdef DEBUG` improve code organization and testing.

**Limitations:** A 16-bit meter reading alone cannot prove that a rollover occurred; meter event information or additional validation is needed. Integer calculations still require overflow checks. A fixed-slab design also needs modification when new tariff periods or time-of-day rates are introduced.

**District-scale correctness:** The selected 64-bit monetary accumulator can hold the tested district total of 76 billion paise. The program should also validate input, detect arithmetic overflow, and use tests for tariff boundaries before production deployment.

**Alternative: Read tariffs from a configuration file:** The program can load and validate \(t\) tariff values at startup instead of compiling the tariff values into the source code. Reading the file takes \(O(t)\) time and stores \(O(t)\) tariff data. Tariff changes then require updating the configuration file rather than recompiling and redistributing the program. This is easier for frequent revisions, but malformed or inconsistent configuration data must be rejected safely.

**Complexity comparison:** Billing with a fixed number of slabs takes \(O(1)\) time per bill. If the program loops through \(s\) tariff slabs, each bill takes \(O(s)\) time. Configuration loading adds \(O(t)\) startup time and \(O(t)\) storage, while compile-time constants avoid that runtime file-reading cost.

**Conclusion:** Use integer paise and a 64-bit accumulator for billing accuracy and district-scale totals. For a tariff that changes frequently, use a validated configuration file or tariff table so revisions do not require rebuilding and redistributing the executable.
