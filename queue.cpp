/**
 * Asier Gutierrez <asierguti@gmail.com>
 */

#include "queue.h"

#include <iostream>

void message_queue::push(uint64_t number) {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_queue.push(number);
  m_cond.notify_one();
}

uint64_t message_queue::pop() {
  std::unique_lock<std::mutex> lock(m_mutex);

  while (m_queue.size() == 0) {
    m_cond.wait(lock);

    if (m_done) {
      if (m_queue.size() == 0) {
        return 0;
      } else {
        break;
      }
    }
  }

  auto number = m_queue.front();
  m_queue.pop();

  return number;
}

void message_queue::stop() {
  std::unique_lock<std::mutex> lock(m_mutex);

  m_done = true;

  m_cond.notify_all();
}

bool message_queue::empty() {
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_queue.empty();
}

void message_queue::mergeResult(const std::map<uint64_t, uint64_t> &numbers) {
  std::unique_lock<std::mutex> lock(m_mutex);

  if (m_result.size() == 0) {
    for (auto const &key : numbers) {
      m_result.insert(key);
    }
  }

  for (auto const &key : numbers) {
    auto it = m_result.find(key.first);

    if (it == m_result.end()) {
      m_result.insert(key);
      continue;
    }

    if (key.second > it->second) {
      it->second = key.second;
    }
  }
}

std::map<uint64_t, uint64_t> message_queue::getResult() { return m_result; }
