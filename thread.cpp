#include <iostream>
#include <thread>  
#include <chrono>    
#include <vector>    

using namespace std;  

// Функция для вычисления факториала числа n
unsigned long long Factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Функция для вычисления и вывода факториала числа с использованием заданного количества потоков
void threadFactorial(int n, int counter) {
    auto start = chrono::high_resolution_clock::now();  // Запуск таймера
    
    vector<thread> threads;  // Вектор потоков
    vector<unsigned long long> results (counter);  // Вектор для хранения результатов
    
    for (int i = 0; i < counter; ++i) {
        // Создание потоков для вычисления факториала
        threads.emplace_back([i, n, &results]() {
            results[i] = Factorial(n);
        });
    }
    
    for (auto& thread : threads) {
        thread.join();  // Ожидание завершения всех потоков
    }
    
    auto end = chrono::high_resolution_clock::now();  // Остановка таймера
    chrono::duration<double> duration = end - start;  // Вычисление времени выполнения
    
    // Вывод результата и времени выполнения
    cout << "Factorial of " << n << " with " << counter << " threads: " << results[0] << endl;
    cout << "Time taken: " << duration.count() << " seconds" << endl;
}

int main() {
    int n;
    cout << "Enter a number to calculate its factorial: ";
    cin >> n;  // Ввод числа с клавиатуры
    
    // Вызов функции для вычисления и вывода факториала с разным количеством потоков
    threadFactorial(n, 1);
    threadFactorial(n, 2);
    threadFactorial(n, 3);
    threadFactorial(n, 4);
    
    return 0; 
}