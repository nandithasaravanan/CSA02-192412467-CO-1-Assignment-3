
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define PEAK_START_HOUR 18
#define PEAK_END_HOUR 22

int main(void)
{
    FILE *file = fopen("tariff.txt", "r");

    if (file == NULL) {
        printf("Error: cannot open tariff.txt\n");
        return 1;
    }

    int64_t rate_paise;
    int surcharge;

    if (fscanf(file, "%" SCNd64 "%d",
               &rate_paise, &surcharge) != 2) {
        fclose(file);
        printf("Error: invalid tariff file\n");
        return 1;
    }
    fclose(file);

    if (rate_paise < 0 || surcharge < 0 || surcharge > 1000) {
        printf("Error: invalid tariff values\n");
        return 1;
    }

    uint64_t energy_wh;
    int hour, minute;

    printf("Enter energy consumed (Wh): ");
    if (scanf("%" SCNu64, &energy_wh) != 1) {
        printf("Error: invalid energy input\n");
        return 1;
    }

    printf("Enter interval start time (HH MM): ");
    if (scanf("%d %d", &hour, &minute) != 2 ||
        hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        printf("Error: invalid time\n");
        return 1;
    }

    int peak = (hour >= PEAK_START_HOUR &&
                hour < PEAK_END_HOUR);

    /*
       rate_paise is paise per kWh.
       Round the interval charge to the nearest paise.
       Check multiplication bounds before production use.
    */
    int64_t multiplier = peak ? 100 + surcharge : 100;

    if (energy_wh > (uint64_t)INT64_MAX /
                    (uint64_t)rate_paise / (uint64_t)multiplier
                    && rate_paise != 0) {
        printf("Error: energy charge too large\n");
        return 1;
    }

    int64_t numerator = (int64_t)energy_wh
                      * rate_paise * multiplier;
    int64_t charge_paise = (numerator + 50000) / 100000;

    printf("Period: %s\n", peak ? "Peak" : "Off-peak");
    printf("Energy: %" PRIu64 " Wh\n", energy_wh);
    printf("Energy charge: Rs %" PRId64 ".%02" PRId64 "\n",
           charge_paise / 100, charge_paise % 100);

    return 0;
}
