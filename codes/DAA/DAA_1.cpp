#include <iostream>
using namespace std;

int fibonacci_recursive(int n) {
    if (n <= 2)
        return 1;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_iterative(int n) {
    if (n == 1 || n == 2)
        return 1;

    int prev2 = 1, prev1 = 1;
    int fib = 0;

    for (int i = 3; i <= n; i++) {
        fib = prev1 + prev2;
        prev2 = prev1;
        prev1 = fib;
    }

    return fib;
}

int main() {
    int n, choice;

    cout << "Enter the position (1-based index) for Fibonacci calculation: ";
    cin >> n;

    cout << "Choose the method:\n";
    cout << "1. Recursive\n";
    cout << "2. Iterative\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Fibonacci number (Recursive) at position " << n << " is: " << fibonacci_recursive(n) << endl;
    } else if (choice == 2) {
        cout << "Fibonacci number (Iterative) at position " << n << " is: " << fibonacci_iterative(n) << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
