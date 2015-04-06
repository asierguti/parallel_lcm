/**
 * Asier Gutierrez <asierguti@gmail.com>
 */

#include "worker.h"

worker::worker(message_queue &q, std::shared_ptr<primes> p)
    : m_queue(q), m_primes(p) {}

void worker::run() {
  while (!m_queue.m_done) {
    auto number = m_queue.pop();

    if (number == 0) {
      break;
    }

    if (number == 1) {
      continue;
    }
    
    auto primes = m_primes->factor_primes(number);
    mergeResult(primes);
  }
  m_queue.mergeResult(m_localResult);
}

void worker::mergeResult(const std::vector<uint64_t> &numbers) {
  uint64_t previous = numbers.front();
  uint64_t count = 1;

  std::vector<uint64_t>::const_iterator i;

  for (i = numbers.begin() + 1; i != numbers.end(); ++i) {
    if (*i == previous) {
      ++count;
    } else {
      if (m_localResult.size() == 0) {
        m_localResult.insert(std::pair<uint64_t, uint64_t>(previous, count));
      } else {

        auto it = m_localResult.find(previous);

        if (it == m_localResult.end()) {
          m_localResult.insert(std::pair<uint64_t, uint64_t>(previous, count));
        } else {

          if (count > it->second) {
            it->second = count;
          }
        }
      }
      previous = *i;
      count = 1;
    }
  }

  auto it = m_localResult.find(previous);

  if (it == m_localResult.end()) {
    m_localResult.insert(std::pair<uint64_t, uint64_t>(previous, count));
  } else {

    if (count > it->second) {
      it->second = count;
    }
  }
}
