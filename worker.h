/**
 * Asier Gutierrez <asierguti@gmail.com>
 */

#ifndef WORKER_H
#define WORKER_H

#include "queue.h"
#include "math.h"

#include <iostream>
#include <memory>
#include <vector>
#include <map>

class worker {
public:
  worker(message_queue &q, std::shared_ptr<primes> p);
  ~worker(){};

  void run();

private:
  void mergeResult(const std::vector<uint64_t> &numbers);

  message_queue &m_queue;
  std::shared_ptr<primes> m_primes;

  std::map<uint64_t, uint64_t> m_localResult;
};

#endif // WORKER_H
