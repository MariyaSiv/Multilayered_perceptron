#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

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
  void autoset();
  void use(double* value, int n);
  double useDer(double value);
};

/*!
	\brief Структура для создания confusion matrix
*/
struct confusion_Matrix {
  int matrix[10][10];

  void Init();
  int& operator()(int i, int j);
  void Print();
};

