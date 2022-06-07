
#pragma once

#include <vector>

#include "Collections.hpp"

template <typename T>
class List : public virtual IArrayList<T> {
  std::vector<T> _vec;

 public:
  explicit List() : _vec() {}

  uintn Size() const override { return _vec.size(); }

  uintn Add(const T& item) override { return _vec.push_back(item); }

  T* Data() const override { return _vec.data(); }

  static Pointer<List<T>> From(const Pointer<IEnumerable<T>>& enumerable);
};

template <typename T>
Pointer<List<T>> List<T>::From(const Pointer<IEnumerable<T>>& enumerable) {
  auto size = enumerable->Size();

  auto list = std::make_shared<List<T>>();

  for (auto enumerator = enumerable->GetEnumerator(); enumerator->MoveNext();) {
    list.Add(enumerator->Current());
  }

  return list;
}