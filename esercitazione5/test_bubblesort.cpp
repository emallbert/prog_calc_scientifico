#include "generic_test.hpp"

int main() {
    return run_sort_tests([](auto& v) { bubble_sort(v); });
}