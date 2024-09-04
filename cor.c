#include <stdio.h>
#include <math.h>

double getMean(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;
}

double calcCorr(int arr1[], int arr2[], int n)
{
    double mean1 = getMean(arr1, n);
    double mean2 = getMean(arr2, n);

    double numerator = 0.0, denominator1 = 0.0, denominator2 = 0.0;

    for (int i = 0; i < n; i++) {
        numerator += (arr1[i] - mean1) * (arr2[i] - mean2);
        denominator1 += pow(arr1[i] - mean1, 2);
        denominator2 += pow(arr2[i] - mean2, 2);
    }

    double correlation = numerator / sqrt(denominator1 * denominator2);

    return correlation;
}

int main()
{
    // Example sequences, replace with your own data
    int sequence1[] = {1, 2, 3, 4, 5};
    int sequence2[] = {5, 4, 3, 2, 1};

    // Calculate correlation
    int n = sizeof(sequence1) / sizeof(sequence1[0]);
    double correlation = calcCorr(sequence1, sequence2, n);

    // Display the result
    printf("Correlation: %.4lf\n", correlation);

    return 0;
}
