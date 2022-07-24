// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

//
// Created by jacob on 6/6/2022.
//

#pragma once

#include <atomic>

#include "Datatypes.hpp"

template <class T, class U>
concept Derived = std::is_base_of_v<U, T>;

class Object {
  std::atomic_int_fast16_t _strong;
  // std::atomic_int16_t _weak;

public:
  Object() : _strong(0) /*, _weak(0) */ {}

  virtual ~Object() = default;

private:
  void Deconstruct() { this->~Object(); }
  void DeleteThis() { operator delete(this); }

  // TODO : Ref and Unref functions are probably not thread safe

  void AddRef() { auto strongRefs = _strong++; }

  void UnRef() {
    auto strongRefs = --_strong;
    if (strongRefs < 1) {
      // auto weakRefs = _weak.load();
      delete this;
    }
  }

  /*
  void WeakAddRef() { auto weakRefs = _weak++; }

  void WeakUnRef() {
    auto strongRefs = _strong.load();
    auto weakRefs = --_weak;
    if (weakRefs < 1 && strongRefs < 1) {
      // DeleteThis();
    }
  }
   */

  template <typename T> friend class Pointer;
};

template <typename T> class Pointer final {
private:
  T* _ptr;

public:
  Pointer() : _ptr(null) {}

  Pointer(T* ptr) : _ptr(ptr) {
    if (_ptr != null)
      _ptr->AddRef();
  }

  Pointer(Pointer&& ptr) : _ptr(ptr._ptr) { ptr._ptr = null; }

  Pointer(const Pointer& ptr) : _ptr(ptr._ptr) {
    if (_ptr != null)
      _ptr->AddRef();
  }

  ~Pointer() {
    if (_ptr != null)
      _ptr->UnRef();
  }

  void operator=(T* ptr) {
    if (_ptr != null)
      _ptr->UnRef();

    _ptr = ptr;
    if (_ptr != null)
      _ptr->AddRef();
  }

  void operator=(const Pointer& ptr) { *this = ptr._ptr; }

  void operator=(Pointer&& ptr) {
    if (_ptr != null)
      _ptr->UnRef();

    _ptr = ptr;
    ptr._ptr = null;
  }

  T& operator*() const noexcept { return *_ptr; }
  T* operator->() const noexcept { return _ptr; }

  operator T*() const noexcept { return _ptr; }
  operator T* const*() const noexcept { return &_ptr; }
  operator bool() const noexcept { return _ptr != null; }

  template <typename... Args> static Pointer New(Args&&... args) {
    auto t = new T(std::forward<Args>(args)...);
    return t;
  }
};
