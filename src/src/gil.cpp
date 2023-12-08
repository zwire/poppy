#include "poppy.h"
#include <Python.h>

namespace poppy {

class GILContextImpl {
public:
  auto Lock() -> void {
    state_ = PyGILState_Ensure();
  }
  auto Unlock() -> void {
    PyGILState_Release(state_);
  }
private:
  PyGILState_STATE state_;
};


GILContext::GILContext(void* context)
  : context_(context), pimpl_(new GILContextImpl()) {}

GILContext::~GILContext() {
  delete pimpl_;
}

auto GILContext::Lock() -> void {
  pimpl_->Lock();
}

auto GILContext::Unlock() -> void {
  pimpl_->Unlock();
}

auto GILContext::Scope(const std::function<void(void)>& func) -> void {
  Lock();
  func();
  Unlock();
}

auto GILContext::Acquire() -> GILContext {
  return GILContext(reinterpret_cast<void*>(PyEval_SaveThread()));
}

auto GILContext::Release() -> void {
  PyEval_RestoreThread(reinterpret_cast<PyThreadState*>(context_));
}

}
