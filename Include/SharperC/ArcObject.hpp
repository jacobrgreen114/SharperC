//
// Created by jacob on 6/6/2022.
//

#pragma once

#include <atomic>

#include "Datatypes.hpp"

template <class T, class U>
concept Derived = std::is_base_of<U, T>::value;

class _ArcObject {
  std::atomic_int16_t _strong;
  std::atomic_int16_t _weak;

public:
  _ArcObject() : _strong(0), _weak(0) {}

  virtual ~_ArcObject() = default;

private:
  void Deconstruct() { this->~_ArcObject(); }
  void DeleteThis() { operator delete(this); }

  void AddRef() { auto strongRefs = _strong++; }

  void UnRef() {
    auto strongRefs = --_strong;
    if (strongRefs < 1) {
      Deconstruct();

      auto weakRefs = _weak.load();
      if (weakRefs < 1) {
        DeleteThis();
      }
    }
  }

  void WeakAddRef() { auto weakRefs = _weak++; }

  void WeakUnRef() {
    auto strongRefs = _strong.load();
    auto weakRefs = --_weak;
    if (weakRefs < 1 && strongRefs < 1) {
      DeleteThis();
    }
  }

  template <Derived<_ArcObject> T> friend class Strong;
};

template <Derived<_ArcObject> T> class _StrongArcPointer final {
private:
  T *_ptr;

  explicit _StrongArcPointer(T *ptr) : _ptr(ptr) {
    if (_ptr != null)
      _ptr->AddRef();
  }

  ~_StrongArcPointer() {
    if (_ptr != null)
      _ptr->UnRef();
  }

public:
  template <typename... Args> static _StrongArcPointer<T> New(Args &&...args) {
    auto t = new T(std::forward<Args>(args)...);
    return t;
  }
};

using Object = _ArcObject;

template <typename T> using Pointer = _StrongArcPointer<T>;
