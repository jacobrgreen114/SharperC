
#pragma once

#include <vector>

#include "Collections.hpp"

template <typename T>
class Array : public virtual IReadonlyArrayList<T> {
  std::vector<T> _vec;

 public:
  explicit Array(uintn size) : _vec(size) {}

  uintn Size() const override { return _vec.size(); }

  T* Data() const override { return _vec.data(); }

  static Pointer<Array<T>> From(const Pointer<IEnumerable<T>>& enumerable);
};

template <typename T>
Pointer<Array<T>> Array<T>::From(const Pointer<IEnumerable<T>>& enumerable) {
  auto size = enumerable->Size();

  auto array = std::make_shared<Array<T>>(size);

  auto enumerator = enumerable->GetEnumerator();
  for (intn i = 0; i < size && enumerator->MoveNext(); ++i) {
    array.At(i) = enumerator->Current();
  }

  return array;
}