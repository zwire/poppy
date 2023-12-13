#ifndef POPPY_POPPY_H_
#define POPPY_POPPY_H_
#define PY_SSIZE_T_CLEAN
#define PYOBJ_PTR(item) reinterpret_cast<PyObject*>((item)->GetAddress())

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <typeinfo>
#include <functional>

namespace poppy {

// declaration
class Generic;
class Value;
class Tuple;
class List;
class Dict;
class Buffer;
class Func;

/**
 * @brief PyObject wrapper
 */
class Object {
public:
  Object(const Object& obj);
  virtual ~Object();
  static auto None() -> Object;
  auto operator=(const Object& obj) -> Object&;
  auto GetAddress() const -> void*;
  auto Type() const -> std::string;
  auto IsNone() const -> bool;
  auto ContainsAttribute(const std::string& name) const -> bool;
  auto RemoveAttribute(const std::string& name) const -> bool;
  auto SetAttribute(const std::string& name, const Object& obj) const -> bool;
  auto SetAttributes(const Dict& dict) const -> bool;
  auto GetAttribute(const std::string& name) const -> Generic;
  auto GetAttributes() const -> Dict;
protected:
  explicit Object(void* ptr);
private:
  const class ObjectImpl* pimpl_;
  int* ref_;
  static auto Load(const std::string& file_name) -> Object;
  friend auto Import(const std::string& name) -> Object;
};

/**
 * @brief Behave as generic type object
 */
class Generic final : public Object {
public:
  auto IsValue() const -> bool;
  auto IsTuple() const -> bool;
  auto IsList() const -> bool;
  auto IsDict() const -> bool;
  auto IsBuffer() const -> bool;
  auto IsFunc() const -> bool;
  auto ToValue() const -> Value;
  auto ToTuple() const -> Tuple;
  auto ToList() const -> List;
  auto ToDict() const -> Dict;
  auto ToBuffer() const -> Buffer;
  auto ToFunc() const -> Func;
protected:
  explicit Generic(void* ptr);
private:
  friend class Object;
  friend class Value;
  friend class Tuple;
  friend class List;
  friend class Dict;
  friend class Buffer;
  friend class Func;
};

/**
 * @brief Behave as primitive value
 */
class Value final : public Object {
public:
  static auto True() -> Value;
  static auto False() -> Value;
  static auto FromBool(const bool& value) -> Value;
  static auto FromInt(const long& value) -> Value;
  static auto FromFloat(const double& value) -> Value;
  static auto FromString(const std::string& value) -> Value;
  static auto FromBytes(const char* value, const size_t& size) -> Value;
  static auto FromBytes(const std::vector<char>& buf) -> Value;
  static auto FromByteArray(const char* value, const size_t& size) -> Value;
  static auto FromByteArray(const std::vector<char>& buf) -> Value;
  auto IsTrue() const -> bool;
  auto IsFalse() const -> bool;
  auto IsBool() const -> bool;
  auto IsInt() const -> bool;
  auto IsFloat() const -> bool;
  auto IsString() const -> bool;
  auto IsBytes() const -> bool;
  auto IsByteArray() const -> bool;
  auto ToBool() const -> bool;
  auto ToInt() const -> long;
  auto ToFloat() const -> double;
  auto ToString() const -> std::string;
  auto ToBytes() const -> std::vector<char>;
  auto ToByteArray() const -> std::vector<char>;
private:
  explicit Value(void* ptr);
  friend class Generic;
  friend class Tuple;
  friend class List;
  friend class Dict;
};

/**
 * @brief PyTuple wrapper
 */
class Tuple final : public Object {
public:
  explicit Tuple(const std::vector<Object>& initializer);
  template<typename... Args>
  inline Tuple(const Object& head, const Args&... args)
    : Tuple(std::vector<Object>{ head, args... }) {}
  auto Set(const int& index, const Object& item) const -> void;
  auto Get(const int& index) const -> Generic;
  auto Get(const int& start, const int& end) const -> Generic;
  auto Size() const -> size_t;
private:
  static auto Init(const std::vector<Object>& initializer) -> void*;
  explicit Tuple(void* ptr);
  friend class Generic;
  friend class List;
  friend class Dict;
  friend class Func;
};

/**
 * @brief PyList wrapper
 */
class List final : public Object {
public:
  explicit List(const std::vector<Object>& initializer = std::vector<Object>());
  template<typename... Args>
  inline List(const Object& head, const Args&... args)
    : List(std::vector<Object>{ head, args... }) {}
  auto Set(const int& index, const Object& item) const -> void;
  auto Get(const int& index) const -> Generic;
  auto Get(const int& start, const int& end) const -> List;
  auto Insert(const int& index, const Object& item) const -> void;
  auto Append(const Object& item) const -> void;
  auto Sort() const -> void;
  auto Reverse() const -> void;
  auto Size() const -> size_t;
  auto ToTuple() const -> Tuple;
private:
  static auto Init(const std::vector<Object>& initializer) -> void*;
  explicit List(void* ptr);
  friend class Generic;
  friend class Dict;
};

/**
 * @brief PyDict wrapper
 */
class Dict final : public Object {
public:
  explicit Dict(const std::map<std::string, Object>& initializer);
  explicit Dict(const std::map<Object, Object>& initializer
    = std::map<Object, Object>());
  auto Set(const std::string& key, const Object& item) const -> void;
  auto Set(const Object& key, const Object& item) const -> void;
  auto Get(const std::string& key) const -> Generic;
  auto Get(const Object& key) const -> Generic;
  auto Delete(const std::string& key) const -> void;
  auto Delete(const Object& key) const -> void;
  auto Contains(const std::string& key) const -> bool;
  auto Contains(const Object& key) const -> bool;
  auto GetKeys() const -> List;
  auto GetValues() const -> List;
  auto Size() const -> size_t;
private:
  static auto Init(
    const std::map<std::string, Object>& initializer) -> void*;
  static auto Init(
    const std::map<Object, Object>& initializer) -> void*;
  explicit Dict(void* ptr);
  friend class Object;
  friend class Generic;
};

/**
 * @brief Py_buffer wrapper
 */
class Buffer final : public Object {
public:
  Buffer(const Buffer& obj);
  virtual ~Buffer();
  auto operator=(const Buffer& obj) -> Buffer&;
  auto Data() const -> void*;
  template<typename T>
  auto Data() const -> T* {
    return reinterpret_cast<T*>(Data());
  }
  auto UnitSize() const -> size_t;
  auto Length() const -> size_t;
  auto Format() const -> std::string;
  auto Dimensions() const -> int;
  auto Shape() const -> std::vector<size_t>;
  auto Strides() const -> std::vector<size_t>;
private:
  explicit Buffer(void* ptr);
  class BufferImpl* pimpl_;
  int* ref_;
  friend class Generic;
};

/**
 * @brief Manage functional behavior
 */
class Func final : public Object {
public:
  auto Invoke() const -> Generic;
  auto Invoke(const Object& arg) const -> Generic;
  template<typename... Args>
  auto Invoke(
    const Object& first,
    const Object& second,
    const Args&... args) -> Generic {
    return InvokeTuple(Tuple(first, second, args...));
  }
  auto operator()() const -> Generic;
  auto operator()(const Object& arg) const -> Generic;
  template<typename... Args>
  auto operator()(
    const Object& first,
    const Object& second,
    const Args&... args) -> Generic {
    return InvokeTuple(Tuple(first, second, args...));
  }
private:
  explicit Func(void* ptr);
  auto InvokeTuple(const Tuple& args) const -> Generic;
  friend class Generic;
};


class GILContext {
public:
  static auto Acquire() -> GILContext;
  auto Release() -> void;
  virtual ~GILContext();
  auto Lock() -> void;
  auto Unlock() -> void;
  auto Scope(const std::function<void(void)>& func) -> void;
private:
  GILContext(void* context);
  class GILContextImpl* pimpl_;
  void* context_;
};

/**
 * @brief Initialize Python interpreter
 */
auto Initialize() -> void;

/**
 * @brief Finalize Python interpreter
 */
auto Finalize() -> void;

/**
 * @brief Register module loading directory
 */
auto AddModuleDirectory(const std::string& target_path) -> void;

// short-cut functions

/**
 * @brief Import Python module
 */
inline auto Import(const std::string& name) -> Object {
  return Object::Load(name);
}

/**
 * @brief Create Python boolean object
 */
inline auto Bool(const bool& value) -> Value {
  return poppy::Value::FromBool(value);
}

/**
 * @brief Create Python int object
 */
template<typename T>
inline auto Int(const T& value) -> Value {
  return poppy::Value::FromInt(value);
}

/**
 * @brief Create Python float object
 */
template<typename T>
inline auto Float(const T& value) -> Value {
  return poppy::Value::FromFloat(value);
}

/**
 * @brief Create Python string object
 */
inline auto Str(const std::string& value) -> Value {
  return poppy::Value::FromString(value);
}

/**
 * @brief Create Python bytes object
 */
template<typename T>
inline auto Bytes(const std::vector<T>& buf) -> Value {
  auto data = reinterpret_cast<const char*>(buf.data());
  auto size = buf.size() * sizeof(T);
  return Value::FromBytes(data, size);
}

/**
 * @brief Create Python bytes object
 */
template<typename T, typename... Args>
inline auto Bytes(const T& head, const Args&... args) -> Value {
  return Bytes(std::vector<T> { head, args... });
}

/**
 * @brief Create Python bytearray object
 */
template<typename T>
inline auto ByteArray(const std::vector<T>& buf) -> Value {
  auto data = reinterpret_cast<const char*>(buf.data());
  auto size = buf.size() * sizeof(T);
  return Value::FromByteArray(data, size);
}

/**
 * @brief Create Python bytearray object
 */
template<typename T, typename... Args>
inline auto ByteArray(const T& head, const Args&... args) -> Value {
  return ByteArray(std::vector<T> { head, args... });
}

}  // namepsace poppy

#endif  // POPPY_POPPY_H_
