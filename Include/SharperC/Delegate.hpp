// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#include "ArcObject.hpp"

template <typename Ret, typename... Args>
class Delegate : public virtual Object {
public:
  using StaticMethod = Ret (*)(Args...);

  template <typename T> using MemberMethod = Ret (T::*)(Args...);

protected:
  Delegate() = default;

public:
  virtual Ret Invoke(Args... args) = 0;

  Ret operator()(Args... args) { return Invoke(std::forward<Args>(args)...); }

private:
  class Static : public Delegate {
    StaticMethod _method;

  public:
    Static(StaticMethod method) : _method(method) {}
    ~Static() override = default;

    Ret Invoke(Args... args) override {
      return _method(std::forward<Args>(args)...);
    }
  };

  template <typename T> class Member : public Delegate {
    Pointer<T> _obj;
    MemberMethod<T> _method;

  public:
    Member(T* obj, MemberMethod<T> method) : _obj(obj), _method(method) {}
    ~Member() override = default;

    Ret Invoke(Args... args) override {
      return (*_obj.*_method)(std::forward<Args>(args)...);
    }
  };

public:
  static Delegate* New(StaticMethod method) { return new Static(); }

  template <typename T>
  static Delegate* NewMember(T* obj, MemberMethod<T> method) {
    return new Member<T>(obj, method);
  }
};
