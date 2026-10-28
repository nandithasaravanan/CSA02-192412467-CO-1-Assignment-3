### Task 4: Re-evaluate and Adapt the Design

**Recommendation: Modify the original design.**

The original design uses integer paise, centralized tariff constants, and rollover validation. These features remain useful, but smart-meter billing requires timestamped 15-minute readings, watt-hour energy measurements, time-of-day pricing, and runtime tariff configuration.

**Data types:** Use `uint64_t` for cumulative energy readings and `int64_t` for monetary values. Store energy in watt-hours and convert to kWh during charge calculation. Use integer arithmetic and a documented rounding rule to avoid floating-point money errors.

**Time-of-day tariff:** Apply a 20% surcharge to energy consumed during the 6 PM–10 PM peak period. Each reading must have a valid timestamp so its energy is assigned to the correct tariff period. For interval readings that cross a tariff boundary, the energy must be split or estimated using finer-grained meter data.

**Tariff revision:** Load the base rate and peak surcharge from `tariff.txt` when the program starts. Validate the configuration before processing readings. Tariff changes can then be made without recompiling the program.

**Scalability:** Each household generates 35,040 readings in a non-leap year. For 800,000 households, the system processes 28,032,000,000 readings annually. Process data in batches or streams instead of loading all readings into memory.

**Complexity:** Processing each reading takes O(1) time, so processing n readings takes O(n) time. A streaming implementation uses O(1) auxiliary memory per reading, excluding buffers and stored records. Loading t tariff values takes O(t) startup time and O(t) storage.

**Limitations:** The demonstration processes one interval at a time and does not implement a complete annual billing database. Production software must handle missing readings, time zones, daylight-saving rules where applicable, meter rollover, configuration validation, overflow checks, and auditable tariff effective dates.

**Conclusion:** The original design should be modified rather than completely discarded. Integer monetary calculations remain appropriate, while timestamp-aware billing and validated runtime tariff configuration are necessary for smart-meter operation.
