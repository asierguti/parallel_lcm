/**
 * Asier Gutierrez <asierguti@gmail.com>
*/

#include <thread>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "worker.h"
#include "queue.h"
#include "math.h"

int main() {
  auto number_thread_pool = std::thread::hardware_concurrency() - 1;

  message_queue q;

  auto m = std::make_shared<primes>();
  std::vector<std::thread> threads;

  std::cout << "Initializing the thread" << std::endl;

  std::vector<std::shared_ptr<worker>> workers;

  for (unsigned int i = 0; i < number_thread_pool; ++i) // number_thread_pool; ++i)
  {
    workers.emplace_back(std::make_shared<worker>(q, m));
  }

  std::cout << "Please enter the number of numbers to process" << std::endl;

  int num_numbers;
  std::cin >> num_numbers;

  std::cout << "OK, we are going to calculate the LCM for " << num_numbers << " numbers. Please, enter the numbers now" << std::endl;

  uint64_t number;

  for (auto &w : workers) {
    threads.push_back(std::thread(std::bind(&worker::run, w)));
  }

  while (num_numbers) {
    std::cin >> number;
    q.push(number);

    --num_numbers;
  }

  q.stop();

  std::cout << "Done factorizing" << std::endl;

  for (auto &t : threads) {
    t.join();
  }

  for (auto &w : workers) {
    w.reset();
  }

  m.reset();

  auto map_results = q.getResult();

  //  uint64_t result = 1;

  auto it = map_results.begin();

  for (; it != --map_results.end(); ++it) {
    std::cout << it->first << "^" << it->second << " * ";
  }

  std::cout << it->first << "^" << it->second << std::endl;

  return 1;
}
