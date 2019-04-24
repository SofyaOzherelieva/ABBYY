#pragma once

#include <unordered_map>
#include <functional>
#include <cassert>

enum ClassType : int {
  TBase,
  TDerived
};

#define BASE_VIRTUAL_CLASS(class_name, fields) \
class class_name {                                   \
public:                                                   \
  std::unordered_map<std::string, std::function<void(void*)>> base_v_methods;   \
  std::unordered_map<std::string, std::function<void(void*)>> derived_v_methods;   \
  const static ClassType type = TBase; \
  ClassType real_type; \
  fields;        \


#define BASE_CONSTRUCTOR(class_name, CODE) \
  class_name(ClassType real_type_ = TBase): real_type(real_type_){CODE};                       \

#define ADD_METHOD(class_name, method_name)              \
  if(this->type == TBase){ \
    this->base_v_methods[#method_name] = this->method_name; \
  } else{ \
    this->derived_v_methods[#method_name] = this->method_name; \
  }                                     \

#define DEFINE_METHOD(class_name, method_name, code)                                      \
  static void method_name(void* obj_ptr) {                                               \
    class_name* this_ = static_cast<class_name*>(obj_ptr);                                       \
    std::cout << #class_name << "->" << #method_name << " ";                  \
    code;\
  };

#define CLASS_END };


#define DERIVED_VIRTUAL_CLASS(base_class, derived_class, fields) \
class derived_class: public base_class {          \
public: \
  const static ClassType type = TDerived; \
  fields;            \

#define DERIVED_CONSTRUCTOR(base_class, derived_class, CODE) \
  derived_class(): base_class(type) {CODE};


#define VIRTUAL_CALL(obj_ptr, method_name)                                                          \
  if(obj_ptr->real_type == TBase){                                                                        \
    assert("No such function" && obj_ptr->base_v_methods.find(#method_name) != obj_ptr->base_v_methods.end()); \
    (obj_ptr->base_v_methods[#method_name])(obj_ptr);                                             \
  } else{                                                                                             \
    if(obj_ptr->derived_v_methods.find(#method_name) != obj_ptr->derived_v_methods.end()){            \
      (obj_ptr->derived_v_methods[#method_name])(obj_ptr);                                            \
    }else{                                                                                            \
      assert("No such function" && obj_ptr->base_v_methods.find(#method_name) != obj_ptr->base_v_methods.end());\
      (obj_ptr->base_v_methods[#method_name])(obj_ptr);                                             \
    }                                                                                                 \
  }
