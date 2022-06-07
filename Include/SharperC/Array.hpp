
#pragma once

#include <vector>

#include "Collections.hpp"

template <typename T> class Array : public virtual IReadonlyArrayList<T> {
  std::vector<T> _vec;

public:
  explicit Array(uintn size) : _vec(size) {}

  virtual ~Array() = default;

  uintn Size() const override { return _vec.size(); }

  T *Data() const override { return const_cast<T *>(_vec.data()); }

  T &At(intn index) const override { return Data()[index]; }

  static Pointer<Array<T>> New(uintn size) { return new Array(size); }

  static Pointer<Array<T>> From(const Pointer<IEnumerable<T>> &enumerable);
};

template <typename T>
Pointer<Array<T>> Array<T>::From(const Pointer<IEnumerable<T>> &enumerable) {
  auto size = enumerable->Size();

  auto array = Array<T>::New(size);

  auto enumerator = enumerable->GetEnumerator();
  for (intn i = 0; i < size && enumerator->MoveNext(); ++i) {
    array.At(i) = enumerator->Current();
  }

  return array;
}