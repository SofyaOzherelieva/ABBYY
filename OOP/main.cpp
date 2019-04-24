#include <iostream>
#include "oop.h"

// Базовый класс:
BASE_VIRTUAL_CLASS(Base, std::string a = "called from base";)

    DEFINE_METHOD(Base, Both, std::cout << this_->a << "\n";)

    DEFINE_METHOD(Base, OnlyBase, std::cout << "\n";)

    BASE_CONSTRUCTOR(Base,
                     ADD_METHOD(Base, Both)
                       ADD_METHOD(Base, OnlyBase)
    )
CLASS_END

// Наследник:
DERIVED_VIRTUAL_CLASS(Base, Derived, std::string b = "called from derived";)

    DEFINE_METHOD(Derived, Both, std::cout << this_->b << "\n";)

    DEFINE_METHOD(Derived, OnlyDerived, std::cout << "\n";)

    DERIVED_CONSTRUCTOR(Base, Derived,
                        ADD_METHOD(Derived, Both)
                          ADD_METHOD(Derived, OnlyDerived)
    )
CLASS_END


int main() {
  Base    base;
  Derived derived;
  Base *reallyDerived = reinterpret_cast<Base*>(&derived);

  VIRTUAL_CALL((&base), Both);
  VIRTUAL_CALL((&base), OnlyBase);
  //VIRTUAL_CALL((&base), OnlyDerived); //выбрасывает исключение
  std::cout << "---------------------------\n";
  VIRTUAL_CALL((&derived), Both);
  VIRTUAL_CALL((&derived), OnlyBase);
  VIRTUAL_CALL((&derived), OnlyDerived);
  std::cout << "---------------------------\n";
  VIRTUAL_CALL(reallyDerived, Both);
  VIRTUAL_CALL(reallyDerived, OnlyBase);
  VIRTUAL_CALL(reallyDerived, OnlyDerived);
  return 0;
}
