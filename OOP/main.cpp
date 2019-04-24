#include <iostream>
#include "oop.h"

// Базовый класс:
BASE_VIRTUAL_CLASS(Base, std::string a = "called from base";)

    DEFINE_METHOD(Base, Both, std::cout << this_->a << "\n";)

    DEFINE_METHOD(Base, TrueBase, std::cout << "\n";)

    BASE_CONSTRUCTOR(Base,
                     ADD_METHOD(Base, Both)
                       ADD_METHOD(Base, TrueBase)
    )
CLASS_END

// Наследник:
DERIVED_VIRTUAL_CLASS(Base, Derived, std::string b = "called from derived";)

    DEFINE_METHOD(Derived, Both, std::cout << this_->b << "\n";)

    DEFINE_METHOD(Derived, TrueDerived, std::cout << "\n";)

    DERIVED_CONSTRUCTOR(Base, Derived,
                        ADD_METHOD(Derived, Both)
                          ADD_METHOD(Derived, TrueDerived)
    )
CLASS_END


int main() {
  Base    base;
  Derived derived;
  Base *reallyDerived = new Derived();

  VIRTUAL_CALL((&base), Both);
  VIRTUAL_CALL((&base), TrueBase);
  //VIRTUAL_CALL((&base), TrueDerived); //выбрасывает исключение
  std::cout << "---------------------------\n";
  VIRTUAL_CALL((&derived), Both);
  VIRTUAL_CALL((&derived), TrueBase);
  VIRTUAL_CALL((&derived), TrueDerived);
  std::cout << "---------------------------\n";
  VIRTUAL_CALL(reallyDerived, Both);
  VIRTUAL_CALL(reallyDerived, TrueBase);
  VIRTUAL_CALL(reallyDerived, TrueDerived);

  delete reallyDerived;
  return 0;
}
