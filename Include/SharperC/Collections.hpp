
#pragma once

#include "Datatypes.hpp"

template <typename T> class IEnumerator : public virtual _ArcObject {
public:
  virtual bool MoveNext() = 0;
  virtual T &Current() const = 0;
  virtual void Reset() = 0;
};

template <typename T> class IEnumerable : public virtual _ArcObject {
public:
  virtual uintn Size() const = 0;
  virtual Pointer<IEnumerator<T>> GetEnumerator() const = 0;
};

template <typename T>
class IReadonlyCollection : public virtual IEnumerable<T> {
public:
  virtual bool Contains(const T &item) const;
};

template <typename T>
class ICollection : public virtual IReadonlyCollection<T> {
public:
  virtual uintn Add(const T &item) = 0;
};

template <typename T>
class IReadonlyList : public virtual IReadonlyCollection<T> {
public:
};

template <typename T>
class IList : public virtual IReadonlyList<T>, public virtual ICollection<T> {
public:
};

template <typename T>
class IReadonlyArrayList : public virtual IReadonlyList<T> {
public:
  virtual T *Data() const = 0;

  Pointer<IEnumerator<T>> GetEnumerator() const override;
  class Enumerator;
};

template <typename T>
class IArrayList : public virtual IReadonlyArrayList<T>,
                   public virtual IList<T> {};

// Default Implementations

template <typename T>
bool IReadonlyCollection<T>::Contains(const T &item) const {
  auto enumerator = this->GetEnumerator();
  while (enumerator->MoveNext()) {
    if (enumerator->Current() == item)
      return true;
  }
  return false;
}

template <typename T>
class IReadonlyArrayList<T>::Enumerator : public virtual IEnumerator<T> {
  Pointer<IReadonlyArrayList<T>> _list;
  intn _index;

public:
  explicit Enumerator(const Pointer<IReadonlyArrayList<T>> &list)
      : _list(list), _index(-1) {}

  bool MoveNext() override { return ++_index < _list->Count(); }

  T &Current() const override { return _list->At(_index); }

  void Reset() override { _index = -1; }
};

template <typename T>
Pointer<IEnumerator<T>> IReadonlyArrayList<T>::GetEnumerator() const {
  return std::make_shared<Enumerator>(
      this->template ThisAs<IReadonlyArrayList<T>>());
}