#include <net/event_loop.h>

#include <base/assert.h>
#include <net/connection_impl.h>

namespace dist_clang {
namespace net {

EventLoop::EventLoop(ui32 concurrency)
    : is_running_(IDLE), concurrency_(concurrency) {
}

EventLoop::~EventLoop() {
  DCHECK(!pool_);
}

bool EventLoop::Run() {
  using namespace std::placeholders;

  Status old_running = IDLE;
  if (!is_running_.compare_exchange_strong(old_running, RUNNING)) {
    return false;
  }

  pool_.reset(new base::WorkerPool(true));
  pool_->AddWorker("Listen Worker"_l,
                   std::bind(&EventLoop::DoListenWork, this, _1, _2));
  pool_->AddWorker("Network IO Worker"_l,
                   std::bind(&EventLoop::DoIOWork, this, _1, _2), concurrency_);

  return true;
}

void EventLoop::Stop() {
  Status old_running = RUNNING;
  if (is_running_.compare_exchange_strong(old_running, STOPPED)) {
    pool_.reset();
  }
}

void EventLoop::ConnectionDoRead(ConnectionImplPtr connection) {
  connection->DoRead();
}

void EventLoop::ConnectionDoSend(ConnectionImplPtr connection) {
  connection->DoSend();
}

void EventLoop::ConnectionClose(ConnectionImplPtr connection) {
  connection->Close();
}

}  // namespace net
}  // namespace dist_clang
