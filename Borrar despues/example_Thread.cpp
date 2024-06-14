#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx;

void printThread(int id) {
    // Bloquear el mutex
    // std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Hilo " << id << " esta corriendo.\n";
}

int main() {
    const int numThreads = 5;
    std::vector<std::thread> hola;
    

    for (int i = 0; i < numThreads; ++i) {
        hola.push_back(std::thread(printThread, i));
    }

    for (auto& t : hola) {
        t.join();
    }

    return 0;
}