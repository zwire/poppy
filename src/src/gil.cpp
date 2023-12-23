#include "poppy.h"
#include <Python.h>

namespace poppy {

class GILContextImpl {
public:
  GILContextImpl()
    : locking_(false),
      state_(),
      context_(PyEval_SaveThread()) {}
  ~GILContextImpl() {
    if (locking_) {
      Unlock();
    }
    PyEval_RestoreThread(context_);
  }
  auto Lock() -> void {
    state_ = PyGILState_Ensure();
    locking_ = true;
  }
  auto Unlock() -> void {
    PyGILState_Release(state_);
    locking_ = false;
  }
private:
  PyThreadState* context_;
  PyGILState_STATE state_;
  bool locking_;
};

GILContext::GILContext()
  : released_(false),
    pimpl_(new GILContextImpl()) {}

GILContext::~GILContext() {
  Release();
}

auto GILContext::Release() -> void {
  if (!released_) {
    released_ = true;
    delete pimpl_;
    pimpl_ = nullptr;
  }
}

auto GILContext::Lock() -> void {
  if (released_) {
    throw std::runtime_error("attempt to use the released object");
  }
  pimpl_->Lock();
}

auto GILContext::Unlock() -> void {
  if (released_) {
    throw std::runtime_error("attempt to use the released object");
  }
  pimpl_->Unlock();
}

auto GILContext::Scope(const std::function<void(void)>& func) -> void {
  Lock();
  func();
  Unlock();
}

}
