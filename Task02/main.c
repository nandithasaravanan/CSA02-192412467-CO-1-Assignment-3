
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>

int main(void)
{
    int counts[] = {4000, 60000, 800000};
    int size = sizeof(counts) / sizeof(counts[0]);

    printf("int: %zu bytes, max = %d\n",
           sizeof(int), INT_MAX);
    printf("long: %zu bytes, max = %ld\n",
           sizeof(long), LONG_MAX);
    printf("long long: %zu bytes, max = %lld\n",
           sizeof(long long), LLONG_MAX);
    printf("float: %zu bytes, precision = %d digits\n",
           sizeof(float), FLT_DIG);
    printf("double: %zu bytes, precision = %d digits\n\n",
           sizeof(double), DBL_DIG);

    for (int i = 0; i < size; i++) {
        int n = counts[i];
        long long paise_total = 0;
        float float_total = 0.0f;
        double double_total = 0.0;

        for (int j = 0; j < n; j++) {
            paise_total += 95000LL;
            float_total += 950.0f;
            double_total += 950.0;
        }

        printf("Bills: %d\n", n);
        printf("Integer paise: %lld\n", paise_total);
        printf("Float total: %.2f\n", float_total);
        printf("Double total: %.2f\n", double_total);
        printf("Float difference: %.2f rupees\n\n",
               (double)float_total - (double)paise_total / 100.0);
    }

    return 0;
}
