
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define METER_MAX 65535U
#define SLAB1_UNITS 100U
#define SLAB2_UNITS 200U
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL
#define FIXED_CHARGE_PAISE 5000LL

/* Accept rollover only when the old reading is high
   and the new reading is low. This is a plausibility rule. */
#define ROLLOVER_MIN_PREVIOUS 60000U
#define ROLLOVER_MAX_CURRENT 5535U

int calculate_consumption(uint32_t previous, uint32_t current,
                          uint32_t *units)
{
    if (previous > METER_MAX || current > METER_MAX)
        return 0;

    if (current >= previous) {
        *units = current - previous;
        return 1;
    }

    if (previous >= ROLLOVER_MIN_PREVIOUS &&
        current <= ROLLOVER_MAX_CURRENT) {
        *units = (METER_MAX - previous) + 1U + current;
        return 1;
    }

    return 0;
}

int64_t calculate_bill(uint32_t units)
{
    int64_t paise = FIXED_CHARGE_PAISE;

    if (units > SLAB2_UNITS)
        paise += (int64_t)(units - SLAB2_UNITS) * RATE3_PAISE;

    if (units > SLAB1_UNITS) {
        uint32_t slab_units =
            (units < SLAB2_UNITS ? units : SLAB2_UNITS)
            - SLAB1_UNITS;

        paise += (int64_t)slab_units * RATE2_PAISE;
    }

    return paise;
}

int main(void)
{
    long long p, c;
    uint32_t units;
    int64_t paise;

    printf("Enter previous meter reading (0-65535): ");
    if (scanf("%lld", &p) != 1) {
        printf("Error: enter a valid integer.\n");
        return 1;
    }

    printf("Enter current meter reading (0-65535): ");
    if (scanf("%lld", &c) != 1) {
        printf("Error: enter a valid integer.\n");
        return 1;
    }

    if (p < 0 || p > METER_MAX || c < 0 || c > METER_MAX) {
        printf("Error: readings must be between 0 and 65535.\n");
        return 1;
    }

    if (!calculate_consumption((uint32_t)p, (uint32_t)c, &units)) {
        printf("Error: current reading is lower than previous; "
               "no plausible rollover detected.\n");
        return 1;
    }

    paise = calculate_bill(units);

    printf("Units consumed: %" PRIu32 "\n", units);
    printf("Bill amount: Rs %" PRId64 ".%02" PRId64 "\n",
           paise / 100, paise % 100);

    return 0;
}
