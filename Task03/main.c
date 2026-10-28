
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

#define FIXED_CHARGE_PAISE 5000LL
#define SLAB1_LIMIT 100U
#define SLAB2_LIMIT 200U
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL

int64_t calculate_bill(uint32_t units)
{
    int64_t bill = FIXED_CHARGE_PAISE;

    if (units > SLAB1_LIMIT) {
        uint32_t slab2 = units < SLAB2_LIMIT
                       ? units - SLAB1_LIMIT
                       : SLAB2_LIMIT - SLAB1_LIMIT;
        bill += (int64_t)slab2 * RATE2_PAISE;
    }

    if (units > SLAB2_LIMIT) {
        bill += (int64_t)(units - SLAB2_LIMIT) * RATE3_PAISE;
    }

    return bill;
}

int load_tariff(const char *filename,
                int64_t *fixed, uint32_t *limit1,
                uint32_t *limit2, int64_t *rate2,
                int64_t *rate3)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 0;

    int ok = fscanf(file,
        "%" SCNd64 "\n%" SCNu32 "\n%" SCNu32
        "\n%" SCNd64 "\n%" SCNd64,
        fixed, limit1, limit2, rate2, rate3) == 5;

    fclose(file);

    if (!ok || *fixed < 0 || *rate2 < 0 || *rate3 < 0 ||
        *limit1 >= *limit2)
        return 0;

    return 1;
}

int main(void)
{
    const uint32_t test_units[] = {0, 100, 150, 200, 350};
    const size_t count = sizeof(test_units) / sizeof(test_units[0]);

    printf("Compile-time tariff results:\n");

    int64_t total = 0;

    for (size_t i = 0; i < count; i++) {
        int64_t bill = calculate_bill(test_units[i]);

        printf("%" PRIu32 " units: Rs %" PRId64 ".%02" PRId64 "\n",
               test_units[i], bill / 100, bill % 100);

        if (total > INT64_MAX - bill) {
            printf("Error: total overflow.\n");
            return 1;
        }

        total += bill;
    }

    printf("Five-bill total: Rs %" PRId64 ".%02" PRId64 "\n",
           total / 100, total % 100);

    int64_t fixed, rate2, rate3;
    uint32_t limit1, limit2;

    if (load_tariff("tariff.txt", &fixed, &limit1, &limit2,
                    &rate2, &rate3)) {
        printf("\nConfiguration file loaded successfully.\n");
        printf("Fixed charge: %" PRId64 " paise\n", fixed);
        printf("Slab limits: %" PRIu32 ", %" PRIu32 "\n",
               limit1, limit2);
        printf("Slab rates: %" PRId64 ", %" PRId64 " paise\n",
               rate2, rate3);
    } else {
        printf("\nConfiguration file missing or invalid.\n");
        printf("Using compile-time tariff constants.\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

#define FIXED_CHARGE_PAISE 5000LL
#define SLAB1_LIMIT 100U
#define SLAB2_LIMIT 200U
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL

int64_t calculate_bill(uint32_t units)
{
    int64_t bill = FIXED_CHARGE_PAISE;

    if (units > SLAB1_LIMIT) {
        uint32_t slab2 = units < SLAB2_LIMIT
                       ? units - SLAB1_LIMIT
                       : SLAB2_LIMIT - SLAB1_LIMIT;
        bill += (int64_t)slab2 * RATE2_PAISE;
    }

    if (units > SLAB2_LIMIT) {
        bill += (int64_t)(units - SLAB2_LIMIT) * RATE3_PAISE;
    }

    return bill;
}

int load_tariff(const char *filename,
                int64_t *fixed, uint32_t *limit1,
                uint32_t *limit2, int64_t *rate2,
                int64_t *rate3)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 0;

    int ok = fscanf(file,
        "%" SCNd64 "\n%" SCNu32 "\n%" SCNu32
        "\n%" SCNd64 "\n%" SCNd64,
        fixed, limit1, limit2, rate2, rate3) == 5;

    fclose(file);

    if (!ok || *fixed < 0 || *rate2 < 0 || *rate3 < 0 ||
        *limit1 >= *limit2)
        return 0;

    return 1;
}

int main(void)
{
    const uint32_t test_units[] = {0, 100, 150, 200, 350};
    const size_t count = sizeof(test_units) / sizeof(test_units[0]);

    printf("Compile-time tariff results:\n");

    int64_t total = 0;

    for (size_t i = 0; i < count; i++) {
        int64_t bill = calculate_bill(test_units[i]);

        printf("%" PRIu32 " units: Rs %" PRId64 ".%02" PRId64 "\n",
               test_units[i], bill / 100, bill % 100);

        if (total > INT64_MAX - bill) {
            printf("Error: total overflow.\n");
            return 1;
        }

        total += bill;
    }

    printf("Five-bill total: Rs %" PRId64 ".%02" PRId64 "\n",
           total / 100, total % 100);

    int64_t fixed, rate2, rate3;
    uint32_t limit1, limit2;

    if (load_tariff("tariff.txt", &fixed, &limit1, &limit2,
                    &rate2, &rate3)) {
        printf("\nConfiguration file loaded successfully.\n");
        printf("Fixed charge: %" PRId64 " paise\n", fixed);
        printf("Slab limits: %" PRIu32 ", %" PRIu32 "\n",
               limit1, limit2);
        printf("Slab rates: %" PRId64 ", %" PRId64 " paise\n",
               rate2, rate3);
    } else {
        printf("\nConfiguration file missing or invalid.\n");
        printf("Using compile-time tariff constants.\n");
    }

    return 0;
}
