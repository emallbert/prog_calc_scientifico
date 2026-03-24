#include <iostream>
#include <cmath>    // per std::sqrt
#include <algorithm> // per std::min e std::max

int main()
{
    static const int N = 10;
    double arr[N] = {3.5, 1.2, 7.8, 4.1, 2.9, 3.3, 4.4, 5.5, 6.6, 7.7};

    // Min e Max
    double min = arr[0];
    double max = arr[0];
    for (int i = 1; i < N; i++) {
        min = std::min(min, arr[i]);
        max = std::max(max, arr[i]);
    }

    // Media
    double sum = 0.0;
    for (int i = 0; i < N; i++)
        sum += arr[i];
    double mean = sum / N;

    // Deviazione standard
    double sq_sum = 0.0;
    for (int i = 0; i < N; i++)
        sq_sum += (arr[i] - mean) * (arr[i] - mean);
    double stddev = std::sqrt(sq_sum / N);

    //bubblesort
    bool ancora = true;
    while (ancora) {
        int scambi = 0;
        for (int i = 0; i < N-1; i++) {
            if (arr[i] > arr[i+1]) {
                double temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp; //oppure std::swap(arr[i], arr[i+1]);
                scambi +=1;
            }
        }            
        if (scambi == 0) {
            ancora = false;
        }
    }
    

    // Stampa
    std::cout << "Min:               " << min    << "\n";
    std::cout << "Max:               " << max    << "\n";
    std::cout << "Media:             " << mean   << "\n";
    std::cout << "Dev. standard:     " << stddev << "\n";
    
    std::cout << "Array ordinato:\n";
    for (int i = 0; i < N; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    return 0;
}