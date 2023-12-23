#include "poppy.h"
#include <Python.h>

namespace poppy {

class BufferImpl {
public:
  BufferImpl(void* ptr) {
    auto p = reinterpret_cast<PyObject*>(ptr);
    PyObject_GetBuffer(p, &buf, PyBUF_STRIDED);
  }
  ~BufferImpl() {
    PyBuffer_Release(&buf);
  }
  Py_buffer buf;
};

Buffer::Buffer(void* ptr)
  : ref_(new int(0)),
    pimpl_(new BufferImpl(ptr)),
    Object(ptr) {}

Buffer::Buffer(const Buffer& obj)
  : ref_(obj.ref_),
    pimpl_(obj.pimpl_),
    Object(obj) {
  (*ref_)++;
}

Buffer::~Buffer() {
  if (*ref_ == 0) {
    delete pimpl_;
    pimpl_ = nullptr;
    delete ref_;
    ref_ = nullptr;
  } else {
    (*ref_)--;
  }
}

auto Buffer::operator=(const Buffer& obj) -> Buffer& {
  ref_ = obj.ref_;
  pimpl_ = obj.pimpl_;
  (*ref_)++;
  return *this;
}

auto Buffer::Data() const -> void* {
  return pimpl_->buf.buf;
}

auto Buffer::BytesPerUnit() const -> size_t {
  return pimpl_->buf.itemsize;
}

auto Buffer::Length() const -> size_t {
  return pimpl_->buf.len;
}

auto Buffer::Format() const -> std::string {
  if (pimpl_->buf.format) {
    return pimpl_->buf.format;
  }
  return "";
}

auto Buffer::Dimensions() const -> int {
  return pimpl_->buf.ndim;
}

auto Buffer::Shape() const -> std::vector<size_t> {
  std::vector<size_t> out;
  for (int i = 0; i < pimpl_->buf.ndim; ++i) {
    out.push_back(pimpl_->buf.shape[i]);
  }
  return out;
}

auto Buffer::Strides() const -> std::vector<size_t> {
  std::vector<size_t> out;
  for (int i = 0; i < pimpl_->buf.ndim; ++i) {
    out.push_back(pimpl_->buf.strides[i]);
  }
  return out;
}

}
