#include<iostream>
#include<thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Printer {
public:
    void display(const std::string& message) {
        std::lock_guard<std::mutex> guard(mutex_);
        std::cout << message << "\n";
    }
private:
    std::mutex mutex_;
};
void sortandDisplay(Printer& printer, std::vector<int>data) {
    std::sort(data.begin(), data.end());
    printer.display("Sorted data:");
    for (const auto& num : data)
    {
        printer.display(std::to_string(num));
    }
}

int main() {
    Printer printer;
    std::vector<int> collection1(10);
    std::vector<int> collection2(10);
    std::generate(collection1.begin(), collection1.end(), []() { return rand() % 100; });
    std::generate(collection2.begin(), collection2.end(), []() { return rand() % 100; });
    std::thread thread1(sortandDisplay, std::ref(printer), collection1);
    std::thread thread2(sortandDisplay, std::ref(printer), collection2);
    thread1.join();
    thread2.join();
    return 0;
}
