#pragma once
#include <iostream>

enum activateFunc {sigmoid = 1, ReLU};
//Перечисление (на будущее)

/*!
	\brief Класс для задания функции активации
*/
class ActivateFunction
{
public:
  /// \brief Поле для перечисления функции активации.
  activateFunc actFunc; 
  void set();
  void use(double* value, int n);
  double useDer(double value);
};
