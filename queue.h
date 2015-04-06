/**
 * Asier Gutierrez <asierguti@gmail.com>
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <utility>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <atomic>

class message_queue {
public:
  message_queue() : m_done(false) {}
  ~message_queue(){};

  void push(uint64_t number);
  uint64_t pop();

  void stop();
  bool empty();

  void mergeResult(const std::map<uint64_t, uint64_t> &factors);
  std::map<uint64_t, uint64_t> getResult();

  std::atomic<bool> m_done;

private:
  std::queue<uint64_t> m_queue;
  std::mutex m_mutex;
  std::condition_variable m_cond;

  std::map<uint64_t, uint64_t> m_result;
};

#endif // QUEUE_H