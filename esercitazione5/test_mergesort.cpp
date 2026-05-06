#include "generic_test.hpp"

int main() {
    return run_sort_tests([](auto& v) { merge_sort(v); }); 
}
//ho usato claude per capire il funzionamento delle lambda