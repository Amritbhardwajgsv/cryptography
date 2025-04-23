#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long num;
    cin >> num;

    vector<int> digits;
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }

    vector<int> pattern = {1, 10, 9, 12, 3, 4};
    int total = 0;

    for (int i = 0; i < digits.size(); i++) {
        int value = pattern[i % pattern.size()];
        total += digits[i] * value;
    }

    int result = total % 13;
    cout << result << endl;

    return 0;
}