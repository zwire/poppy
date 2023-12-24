#ifndef POPPY_POPPY_H_
#define POPPY_POPPY_H_

#define PY_SSIZE_T_CLEAN
#define PYOBJ_REF(item) reinterpret_cast<PyObject*>((item)->GetRef())

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <typeinfo>
#include <functional>

/**
 * @brief namespace of the C++ API for Python interpreter control
 */
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
 * @brief PyObject wrapper object
 */
class Object {
public:
  /**
   * @brief default constructor
   */
  Object();
  /**
   * @brief copy constructor
   */
  Object(const Object& obj);
  /**
   * @brief destructor
   */
  virtual ~Object();
  /**
   * @brief create new empty object
   * @return Object empty object
   */
  static auto None() -> Object;
  /**
   * @brief operator overload
   */
  auto operator=(const Object& obj) -> Object&;
  /**
   * @brief operator overload
   */
  auto operator==(const Object& obj) const -> bool;
  /**
   * @brief operator overload
   */
  auto operator!=(const Object& obj) const -> bool;
  /**
   * @brief operator overload
   */
  auto operator<(const Object& obj) const -> bool;
  /**
   * @brief operator overload
   */
  auto operator<=(const Object& obj) const -> bool;
  /**
   * @brief operator overload
   */
  auto operator>(const Object& obj) const -> bool;
  /**
   * @brief operator overload
   */
  auto operator>=(const Object& obj) const -> bool;
  /**
   * @brief get internal pointer address of current instance
   * @return void* pointer of PyObject
   */
  auto GetRef() const -> void*;
  /**
   * @brief get type name of current instance
   * @return std::string type name
   */
  auto Type() const -> std::string;
  /**
   * @brief get hash value of current instance
   * @return size_t hash value
   */
  auto Hash() const -> size_t;
  /**
   * @brief get string expression of current instance
   * @return std::string string expression
   */
  auto ToString() const -> std::string;
  /**
   * @brief judge if current instance is none
   * @return bool judgement result
   */
  auto IsNone() const -> bool;
  /**
   * @brief judge if current instance contains specified attribute
   * @param[in] name attribute name
   * @return bool judgement result
   */
  auto ContainsAttribute(const std::string& name) const -> bool;
  /**
   * @brief remove specified attribute from current instance
   * @param[in] name attribute name
   * @return bool status of removing process
   */
  auto RemoveAttribute(const std::string& name) const -> bool;
  /**
   * @brief set specified attribute to current instance
   * @param[in] name attribute name
   * @param[in] obj input attribute object
   * @return bool status of setting process
   */
  auto SetAttribute(const std::string& name, const Object& obj) const -> bool;
  /**
   * @brief set specified attributes to current instance
   * @param[in] dict input Dict attribute
   * @return bool status of setting process
   */
  auto SetAttributes(const Dict& dict) const -> bool;
  /**
   * @brief get specified attribute from current instance
   * @param[in] name attribute name
   * @return Generic acquired object
   */
  auto GetAttribute(const std::string& name) const -> Generic;
  /**
   * @brief get specified attributes from current instance
   * @return Dict acquired objects
   */
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
 * @brief operator
 */
auto operator<<(std::ostream& out, const Object& obj) -> std::ostream&;

/**
 * @brief generic type behavior object
 */
class Generic final : public Object {
public:
  /**
   * @brief judge if current instance is Value type
   * @return bool judgement result
   */
  auto IsValue() const -> bool;
  /**
   * @brief judge if current instance is Tuple type
   * @return bool judgement result
   */
  auto IsTuple() const -> bool;
  /**
   * @brief judge if current instance is List type
   * @return bool judgement result
   */
  auto IsList() const -> bool;
  /**
   * @brief judge if current instance is Dict type
   * @return bool judgement result
   */
  auto IsDict() const -> bool;
  /**
   * @brief judge if current instance is Buffer type
   * @return bool judgement result
   */
  auto IsBuffer() const -> bool;
  /**
   * @brief judge if current instance is Func type
   * @return bool judgement result
   */
  auto IsFunc() const -> bool;
  /**
   * @brief convert into Value object
   * @return Value converted result
   * @exception std::bad_cast failed to interpret
   */
  auto ToValue() const -> Value;
  /**
   * @brief convert into Tuple object
   * @return Tuple converted result
   * @exception std::bad_cast failed to interpret
   */
  auto ToTuple() const -> Tuple;
  /**
   * @brief convert into List object
   * @return List converted result
   * @exception std::bad_cast failed to interpret
   */
  auto ToList() const -> List;
  /**
   * @brief convert into Dict object
   * @return Dict converted result
   * @exception std::bad_cast failed to interpret
   */
  auto ToDict() const -> Dict;
  /**
   * @brief convert into Buffer object
   * @return Buffer converted result
   * @exception std::bad_cast failed to interpret
   */
  auto ToBuffer() const -> Buffer;
  /**
   * @brief convert into Func object
   * @return Func converted result
   * @exception std::bad_cast failed to interpret
   */
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
 * @brief primitive variable behavior object
 */
class Value final : public Object {
public:
  /**
   * @brief create new boolean Value
   * @return Value boolean true value object
   */
  static auto True() -> Value;
  /**
   * @brief create new boolean Value
   * @return Value boolean false value object
   */
  static auto False() -> Value;
  /**
   * @brief create new boolean Value
   * @param[in] value boolean value
   * @return Value boolean value object
   */
  static auto FromBool(const bool& value) -> Value;
  /**
   * @brief create new integer Value
   * @param[in] value integer value
   * @return Value integer value object
   */
  static auto FromInt(const long& value) -> Value;
  /**
   * @brief create new float Value
   * @param[in] value float value
   * @return Value float value object
   */
  static auto FromFloat(const double& value) -> Value;
  /**
   * @brief create new string Value
   * @param[in] value string value
   * @return Value string value object
   */
  static auto FromString(const std::string& value) -> Value;
  /**
   * @brief create new bytes Value
   * @param[in] value bytes value
   * @param[in] size length of input value
   * @return Value bytes value object
   */
  static auto FromBytes(const char* value, const size_t& size) -> Value;
  /**
   * @brief create new bytes Value
   * @param[in] buf bytes array
   * @return Value bytes value object
   */
  static auto FromBytes(const std::vector<char>& buf) -> Value;
  /**
   * @brief create new bytearray Value
   * @param[in] value bytearray value
   * @param[in] size length of input value
   * @return Value bytearray value object
   */
  static auto FromByteArray(const char* value, const size_t& size) -> Value;
  /**
   * @brief create new bytearray Value
   * @param[in] buf bytes array
   * @return Value bytearray value object
   */
  static auto FromByteArray(const std::vector<char>& buf) -> Value;
  /**
   * @brief judge if current instance is boolean true
   * @return bool judgement result
   */
  auto IsTrue() const -> bool;
  /**
   * @brief judge if current instance is boolean false
   * @return bool judgement result
   */
  auto IsFalse() const -> bool;
  /**
   * @brief judge if current instance is boolean type
   * @return bool judgement result
   */
  auto IsBool() const -> bool;
  /**
   * @brief judge if current instance is integer type
   * @return bool judgement result
   */
  auto IsInt() const -> bool;
  /**
   * @brief judge if current instance is float type
   * @return bool judgement result
   */
  auto IsFloat() const -> bool;
  /**
   * @brief judge if current instance is string type
   * @return bool judgement result
   */
  auto IsString() const -> bool;
  /**
   * @brief judge if current instance is bytes type
   * @return bool judgement result
   */
  auto IsBytes() const -> bool;
  /**
   * @brief judge if current instance is bytearray type
   * @return bool judgement result
   */
  auto IsByteArray() const -> bool;
  /**
   * @brief extract boolean object contents
   * @return bool C++ style value
   * @exception std::bad_cast failed to interpret
   */
  auto ToBool() const -> bool;
  /**
   * @brief extract integer object contents
   * @return long C++ style value
   * @exception std::bad_cast failed to interpret
   */
  auto ToInt() const -> long;
  /**
   * @brief extract float object contents
   * @return double C++ style value
   * @exception std::bad_cast failed to interpret
   */
  auto ToFloat() const -> double;
  /**
   * @brief extract string object contents
   * @return std::string C++ style value
   * @exception std::bad_cast failed to interpret
   */
  auto ToString() const -> std::string;
  /**
   * @brief extract bytes object contents
   * @return std::vector<char> C++ style value
   * @exception std::bad_cast failed to interpret
   */
  auto ToBytes() const -> std::vector<char>;
  /**
   * @brief extract bytearray object contents
   * @return std::vector<char> C++ style value
   * @exception std::bad_cast failed to interpret
   */
  auto ToByteArray() const -> std::vector<char>;
private:
  explicit Value(void* ptr);
  friend class Generic;
  friend class Tuple;
  friend class List;
  friend class Dict;
};

/**
 * @brief PyTuple wrapper object
 */
class Tuple final : public Object {
public:
  /**
   * @brief constructor
   * @param[in] initializer tuple elements
   */
  explicit Tuple(const std::vector<Object>& initializer);
  /**
   * @brief constructor
   * @param[in] head first element of input array
   * @param[in] args subsequent elements of input array
   */
  template<typename... Args>
  inline Tuple(const Object& head, const Args&... args)
    : Tuple(std::vector<Object>{ head, args... }) {}
  /**
   * @brief get one element
   * @param[in] index index number
   * @return Generic acquired object
   */
  auto Get(const int& index) const -> Generic;
  /**
   * @brief get length of elements
   * @return size_t length of elements
   */
  auto Size() const -> size_t;
  /**
   * @brief convert into std::vector
   * @return std::vector<Generic> converted object
   */
  auto ToStdVector() const -> std::vector<Generic>;
private:
  static auto Init(const std::vector<Object>& initializer) -> void*;
  explicit Tuple(void* ptr);
  friend class Generic;
  friend class List;
  friend class Dict;
  friend class Func;
};

/**
 * @brief PyList wrapper object
 */
class List final : public Object {
public:
  /**
   * @brief constructor
   * @param[in] initializer list elements
   */
  explicit List(const std::vector<Object>& initializer = std::vector<Object>());
  /**
   * @brief constructor
   * @param[in] head first element of input array
   * @param[in] args subsequent elements of input array
   */
  template<typename... Args>
  inline List(const Object& head, const Args&... args)
    : List(std::vector<Object>{ head, args... }) {}
  /**
   * @brief replace one element
   * @param[in] index index number
   * @param[in] item object to set
   */
  auto Set(const int& index, const Object& item) const -> void;
  /**
   * @brief get one element
   * @param[in] index index number
   * @return Generic acquired object
   */
  auto Get(const int& index) const -> Generic;
  /**
   * @brief insert one element before the specified index number
   * @param[in] index index number
   * @param[in] item object to insert
   */
  auto Insert(const int& index, const Object& item) const -> void;
  /**
   * @brief append one element at the end of the list
   * @param[in] item object to append
   */
  auto Append(const Object& item) const -> void;
  /**
   * @brief sort for all elements
   */
  auto Sort() const -> void;
  /**
   * @brief reverse the list
   */
  auto Reverse() const -> void;
  /**
   * @brief get length of elements
   * @return size_t length of elements
   */
  auto Size() const -> size_t;
  /**
   * @brief convert into Tuple object
   * @return converted object
   */
  auto ToTuple() const -> Tuple;
  /**
   * @brief convert into std::vector
   * @return std::vector<Generic> converted object
   */
  auto ToStdVector() const -> std::vector<Generic>;
private:
  static auto Init(const std::vector<Object>& initializer) -> void*;
  explicit List(void* ptr);
  friend class Generic;
  friend class Dict;
};

/**
 * @brief PyDict wrapper object
 */
class Dict final : public Object {
public:
  /**
   * @brief default constructor
   */
  Dict();
  /**
   * @brief constructor
   * @param[in] initializer dict elements
   */
  explicit Dict(const std::unordered_map<std::string, Object>& initializer);
  /**
   * @brief constructor
   * @param[in] initializer dict elements
   */
  explicit Dict(const std::unordered_map<Object, Object>& initializer);
  /**
   * @brief set one element
   * @param[in] key key
   * @param[in] item object to set
   * @note the element is overwrited when specify existing key
   */
  auto Set(const std::string& key, const Object& item) const -> void;
  /**
   * @brief set one element
   * @param[in] key key
   * @param[in] item object to set
   * @note the element is overwrited when specify existing key
   */
  auto Set(const Object& key, const Object& item) const -> void;
  /**
   * @brief get one element
   * @param[in] key key
   * @return Generic acquired object
   * @exception std::logic_error when nonexistent key is specified
   */
  auto Get(const std::string& key) const -> Generic;
  /**
   * @brief get one element
   * @param[in] key key
   * @return Generic acquired object
   * @exception std::logic_error when nonexistent key is specified
   */
  auto Get(const Object& key) const -> Generic;
  /**
   * @brief delete one element
   * @param[in] key key
   * @exception std::logic_error when nonexistent key is specified
   */
  auto Delete(const std::string& key) const -> void;
  /**
   * @brief delete one element
   * @param[in] key key
   * @exception std::logic_error when nonexistent key is specified
   */
  auto Delete(const Object& key) const -> void;
  /**
   * @brief judge if current instance contains the specified key
   * @param[in] key key
   * @return bool judgement result
   */
  auto Contains(const std::string& key) const -> bool;
  /**
   * @brief judge if current instance contains the specified key
   * @param[in] key key
   * @return bool judgement result
   */
  auto Contains(const Object& key) const -> bool;
  /**
   * @brief get key objects from current instance
   * @return List key objects
   */
  auto GetKeys() const -> List;
  /**
   * @brief get value objects from current instance
   * @return List value objects
   */
  auto GetValues() const -> List;
  /**
   * @brief get length of elements
   * @return size_t length of elements
   */
  auto Size() const -> size_t;
  /**
   * @brief convert into std::vector
   * @return std::vector<std::pair<Generic, Generic>> converted object
   */
  auto ToStdVector() const -> std::vector<std::pair<Generic, Generic>>;
private:
  static auto Init(
    const std::unordered_map<std::string, Object>& initializer) -> void*;
  static auto Init(
    const std::unordered_map<Object, Object>& initializer) -> void*;
  explicit Dict(void* ptr);
  friend class Object;
  friend class Generic;
};

/**
 * @brief Py_buffer wrapper object
 */
class Buffer final : public Object {
public:
  /**
   * @brief copy constructor
   */
  Buffer(const Buffer& obj);
  /**
   * @brief destructor
   */
  ~Buffer();
  /**
   * @brief operator overload
   */
  auto operator=(const Buffer& obj) -> Buffer&;
  /**
   * @brief get raw data pointer from buffer
   * @return void* raw data pointer
   */
  auto Data() const -> void*;
  /**
   * @brief get raw data pointer from buffer
   * @return T* raw data pointer
   */
  template<typename T>
  auto Data() const -> T* {
    return reinterpret_cast<T*>(Data());
  }
  /**
   * @brief get byte count per one element
   * @return size_t byte count per one element
   */
  auto BytesPerUnit() const -> size_t;
  /**
   * @brief get total byte count
   * @return size_t total byte count
   */
  auto Length() const -> size_t;
  /**
   * @brief get format of current buffer
   * @return std::string format
   */
  auto Format() const -> std::string;
  /**
   * @brief get dimension of current tensor
   * @return int dimension count
   */
  auto Dimensions() const -> int;
  /**
   * @brief get element count for each dimension
   * @return std::vector<size_t> element counts
   * @note the vector length should equal to Dimensions()
   */
  auto Shape() const -> std::vector<size_t>;
  /**
   * @brief get byte count to the next iteration for each dimension
   * @return std::vector<size_t> strides (bytes)
   * @note the vector length should equal to Dimensions()
   */
  auto Strides() const -> std::vector<size_t>;
private:
  explicit Buffer(void* ptr);
  class BufferImpl* pimpl_;
  int* ref_;
  friend class Generic;
};

/**
 * @brief functional behavior object
 */
class Func final : public Object {
public:
  /**
   * @brief invoke function
   * @return the result value of function
   * @note void function returns 'None' object
   */
  auto Invoke() const -> Generic;
  /**
   * @brief invoke function
   * @param[in] arg argument object
   * @return the result value of function
   * @note void function returns 'None' object
   */
  auto Invoke(const Object& arg) const -> Generic;
  /**
   * @brief invoke function
   * @param[in] first first element of arguments
   * @param[in] second second element of arguments
   * @param[in] args subsequent element of arguments
   * @return the result value of function
   * @note void function returns 'None' object
   */
  template<typename... Args>
  auto Invoke(
    const Object& first,
    const Object& second,
    const Args&... args) -> Generic {
    return InvokeTuple(Tuple(first, second, args...));
  }
  /**
   * @brief invoke function
   * @return the result value of function
   * @note void function returns 'None' object
   */
  auto operator()() const -> Generic;
  /**
   * @brief invoke function
   * @param[in] arg argument object
   * @return the result value of function
   * @note void function returns 'None' object
   */
  auto operator()(const Object& arg) const -> Generic;
  /**
   * @brief invoke function
   * @param[in] first first element of arguments
   * @param[in] second second element of arguments
   * @param[in] args subsequent element of arguments
   * @return the result value of function
   * @note void function returns 'None' object
   */
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

/**
 * @brief GIL context management object (scoped locking pettern)
 */
class GILContext {
public:
  /**
   * @brief default constructor
   * @note require locking all Python procedures until this instance released
   */
  GILContext();
  /**
   * @brief destructor
   * @note if not released yet, call Release()
   */
  virtual ~GILContext();
  /**
   * @brief release current holding context
   * @note destructor calls this method
   */
  auto Release() -> void;
  /**
   * @brief lock Python procedures
   */
  auto Lock() -> void;
  /**
   * @brief unlock Python procedures
   * @warning if unlock the unlocked context, memory corruption will occur
   */
  auto Unlock() -> void;
  /**
   * @brief lock and unlock before and after processing (scoped locking pettern)
   * @param[in] func any void function to be executed in locked context
   */
  auto Scope(const std::function<void(void)>& func) -> void;
private:
  class GILContextImpl* pimpl_;
  bool released_;
};

/**
 * @brief initialize Python interpreter
 */
auto Initialize() -> void;

/**
 * @brief initialize Python interpreter
 * @param[in] executable_path path to Python executable
 * @param[in] modules_search_path path to search modules
 */
auto Initialize(
  const std::wstring& executable_path, 
  const std::wstring& modules_search_path) -> void;

/**
 * @brief finalize Python interpreter
 */
auto Finalize() -> void;

/**
 * @brief register module loading directory
 * @param[in] target_path the directory path to target module
 */
auto AddModuleDirectory(const std::string& target_path) -> void;

// short-cut functions

/**
 * @brief import Python module
 * @param[in] name module name or script file name (excluding '.py')
 * @return Object acquired module object
 */
inline auto Import(const std::string& name) -> Object {
  return Object::Load(name);
}

/**
 * @brief create new boolean object
 * @param[in] value input boolean value
 * @return Value constructed Python object
 */
inline auto Bool(const bool& value) -> Value {
  return poppy::Value::FromBool(value);
}

/**
 * @brief create new int object
 * @param[in] value input int value
 * @return Value constructed Python object
 */
template<typename T>
inline auto Int(const T& value) -> Value {
  return poppy::Value::FromInt(value);
}

/**
 * @brief create new float object
 * @param[in] value input float value
 * @return Value constructed Python object
 */
template<typename T>
inline auto Float(const T& value) -> Value {
  return poppy::Value::FromFloat(value);
}

/**
 * @brief create new string object
 * @param[in] value input string value
 * @return Value constructed Python object
 */
inline auto Str(const std::string& value) -> Value {
  return poppy::Value::FromString(value);
}

/**
 * @brief create new bytes object
 * @param[in] buf input array
 * @return Value constructed Python object
 */
template<typename T>
inline auto Bytes(const std::vector<T>& buf) -> Value {
  auto data = reinterpret_cast<const char*>(buf.data());
  auto size = buf.size() * sizeof(T);
  return Value::FromBytes(data, size);
}

/**
 * @brief create new bytes object
 * @param[in] head first element of input array
 * @param[in] args subsequent elements of input array
 * @return Value constructed Python object
 */
template<typename T, typename... Args>
inline auto Bytes(const T& head, const Args&... args) -> Value {
  return Bytes(std::vector<T> { head, args... });
}

/**
 * @brief Create Python bytearray object
 * @param[in] buf input array
 * @return Value constructed Python object
 */
template<typename T>
inline auto ByteArray(const std::vector<T>& buf) -> Value {
  auto data = reinterpret_cast<const char*>(buf.data());
  auto size = buf.size() * sizeof(T);
  return Value::FromByteArray(data, size);
}

/**
 * @brief Create Python bytearray object
 * @param[in] head first element of input array
 * @param[in] args subsequent elements of input array
 * @return Value constructed Python object
 */
template<typename T, typename... Args>
inline auto ByteArray(const T& head, const Args&... args) -> Value {
  return ByteArray(std::vector<T> { head, args... });
}

}  // namepsace poppy

namespace std {

template<>
class hash<poppy::Object>{
public:
  auto operator()(const poppy::Object &obj) const -> size_t {
    return obj.Hash();
  }
};

}  // namespace std

#endif  // POPPY_POPPY_H_
