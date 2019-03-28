
#define COMMAND(NUM, NAME, ARGC, CODE)


/// Кладёт аргумент (число) на вершину стека
COMMAND(PUSH, "PUSH", 1, { stack.Push(command.argv_[0]); })

/// Убирает элемент с вершины стека, не читая его
COMMAND(POP, "POP", 0, { stack.Pop(); })

/// Дублирует элемент на вершине стека
COMMAND(DBL, "DBL", 0, {
  auto temp = stack.PeekRemove();
  stack.Push(temp);
  stack.Push(temp);
})

///////////////////////////////////////////////////////////////////////////////////////

///// Арифметические операции над элементами стека:

///// Убирают верхние элементы стека, участвующие в арифметической операции.
///// Кладут на стек результат.

/// Сложение
COMMAND(ADD, "ADD", 0, { stack.Push(stack.PeekRemove() + stack.PeekRemove()); })
/// Умножение
COMMAND(MUL, "MUL", 0, { stack.Push(stack.PeekRemove() * stack.PeekRemove()); })
/// Квадратный корень
COMMAND(SQRT, "SQRT", 0, { stack.Push(sqrt(stack.PeekRemove())); })
/// Вычитание первого сверху элемента из второго сверху
COMMAND(SUB, "SUB", 0, {
  double temp1 = stack.PeekRemove();
  double temp2 = stack.PeekRemove();
  stack.Push(temp2 - temp1);
})
/// Деление первого сверху элемента на второй сверху
COMMAND(DIV, "DIV", 0, {
  double temp1 = stack.PeekRemove();
  double temp2 = stack.PeekRemove();
  stack.Push(temp1 / temp2);
})

///////////////////////////////////////////////////////////////////////////////////////

/// Ввод элемента, его запись на вершину стека
COMMAND(IN, "IN", 0, {
  double temp = NAN;
  std::cin >> temp;
  stack.Push(temp);
})

/// Вывод вершины стека
COMMAND(OUT, "OUT", 0, { std::cout << stack.PeekRemove() << "\n"; })

///////////////////////////////////////////////////////////////////////////////////////

/// Вызов функции
COMMAND(CALL, "CALL", 1, {
return_pos.Push(position);
position = command.argv_[0];
})

/// Возвращение из функции
COMMAND(RET, "RET", 0, {position = return_pos.PeekRemove();})

///////////////////////////////////////////////////////////////////////////////////////

/// Точка перехода (определение фунции или направление <-JUMP)
COMMAND(TO, "->TO", 1, {})

///// Переход на позицию (метку) в программе, указанную в аргументе, при условии:
///// (аналогичная позиция (метка) должна быть прописана в <-TO)

/// в любом случае
COMMAND(JUMP, "<-JUMP", 1, {
  position = command.argv_[0];
})

/// равенства двух верхних элементов стека
COMMAND(JUMPEQ, "<-JUMPEQ", 1, {
  double temp1 = stack.PeekRemove();
  double temp2 = stack.PeekRemove();
  if (fabs(temp1 - temp2) < EPS) {
    //return_pos.Push(position);
    position = command.argv_[0];
  };
  stack.Push(temp2);
})

/// неравенства двух верхних элементов стека
COMMAND(JUMPNEQ, "<-JUMPNEQ", 1, {
  double temp1 = stack.PeekRemove();
  double temp2 = stack.PeekRemove();
  if (fabs(temp1 - temp2) > EPS) {
    //return_pos.Push(position);
    position = command.argv_[0];
  };
  stack.Push(temp2);
})


/// того, что второй сверху на стеке элемент больше первого сверху
COMMAND(JUMPGR, "<-JUMPGR", 1, {
  double temp1 = stack.PeekRemove();
  double temp2 = stack.PeekRemove();
  if (temp2 >= temp1) {
    //return_pos.Push(position);
    position = command.argv_[0];
  };
  stack.Push(temp2);
})

/// того, что стек пуст
COMMAND(JUMPEMPT, "<-JUMPEMPT", 1, {
  if (stack.IsEmpty()) {
    //return_pos.Push(position);
    position = command.argv_[0];
  };
})

///////////////////////////////////////////////////////////////////////////////////////


/// Записывает вершину стека в регистр, указанный в аргументе
/// При этом убирает вершину стека
COMMAND(FSTR, "FSTR", 1, {
  int num = stack.PeekRemove();
  int id = command.argv_[0];
  PushInRam(id, num);
})


/// Записывает значение регистра на вершину стека
/// Аргумент: регистр
COMMAND(FRTS, "FRTS", 1, {
  int id = command.argv_[0];
  int num = GetFromRam(id);
  stack.Push(num);
})

///////////////////////////////////////////////////////////////////////////////////////


/// Вывод текстовых сообщений, прописанных в области статических данных
COMMAND(PRINT, "#PRINT", 1, {
  int to_print = command.argv_[0];
  while(raw_data[to_print] != '\n') {
    fprintf(stdout, "%c", raw_data[to_print]);
    to_print++;
  }
  fprintf(stdout, "\n");
})

/// Конец программы
COMMAND(END, "END", 0, {})

