/**
 * Asier Gutierrez <asierguti@gmail.com>
*/

#include <thread>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <chrono>

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

  uint64_t number;

  for (auto &w : workers) {
    threads.push_back(std::thread(std::bind(&worker::run, w)));
  }

  while (std::cin >> number) {//num_numbers) {
    q.push(number);
  }

  q.stop();

  std::cout << "Done reading all the numbers" << std::endl;

  for (auto &t : threads) {
    t.join();
  }

  for (auto &w : workers) {
    w.reset();
  }

  m.reset();

  auto map_results = q.getResult();

  if (map_results.size() == 0) {
    std::cerr << "Ooop, there has been a problem. Please try again" << std::endl;
    return -1;
  }

  auto it = map_results.begin();

  for (; it != --map_results.end(); ++it) {
    std::cout << it->first << "^" << it->second << " * ";
  }

  std::cout << it->first << "^" << it->second << std::endl;

  return 1;
}
