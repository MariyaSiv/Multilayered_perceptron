#include "ActivateFunction.h"
#include <cmath>

void ActivateFunction::set() {
  /**
  \brief Метод для задания функции активации.
  \warning Реализована только функция ReLu.
  \throw std::runtime_error Значение actFunc не задано.
 */
  std::cout << "Функция активации (1 - Sigmoid, 2 - ReLU)\n";
  int tmp;
  std::cin >> tmp;
  switch(tmp) {
    case sigmoid:
      actFunc = sigmoid;
      break;
    case ReLU:
      actFunc = ReLU;
      break;
    default:
      throw std::runtime_error("Error:actFuncInit");
      break;
  }
};

void ActivateFunction::use(double* value, int n) {
  /**
  \brief Метод для использования функции активации.
  \warning Реализована только функция ReLu.
  \throw std::runtime_error Значение actFunc не задано.
  
  \param[out] value целевой вектор
  \param[in] n длина вектора
  */

  switch (actFunc) {
    case activateFunc::sigmoid:
      for (int i = 0; i < n; i++) {
        value[i] = 1 / (1 + std::exp(-value[i]));
      }
      break;

    case activateFunc::ReLU:
      for (int i = 0; i < n; i++) {
        if (value[i] < 0)
          value[i] *= 0.01;
        else if (value[i] > 1) 
          value[i] = 1. + 0.01 * (value[i] - 1.);
      }
      break;

    default:
      throw std::runtime_error("Error:actFuncInit");
      break;
  }
};

double ActivateFunction::useDer (double value) {
  /**
  \brief Метод для использования производной функции активации.
  \warning Реализована только функция ReLu.
  \throw std::runtime_error Значение actFunc не задано.
  
  \param[out] value значение
  */
  switch (actFunc) {
    case activateFunc::sigmoid:
      value = 1/(1 + std::exp(-value));
      break;
    
    case activateFunc::ReLU:
      if (value < 0 || value > 1)
        value = 0.01;
      break;

    default:
      throw std::runtime_error("Ошибка useD. Функция активации не задана! \n");
      break;
  }
  return value;
};
