#include "Utils.h"


void confusion_Matrix::Init() {
  /**
  \brief Инициализация confusion matrix
  */
    for (int i=0; i<10; i++) {
		    for (int j=0; j<10; j++) matrix[i][j] = 0;
	  }
}

int& confusion_Matrix::operator()(int i, int j) {
  /**
  \brief Перезагрузка оператора () для удобного доступа к элементам матрицы.
  
  \param[in] i Номер строки
  \param[in] j Номер столбца

  \return Ссылку на элемент матрицы
  */
  return matrix[i][j];
}

void confusion_Matrix::Print() {
  /**
  \brief Печать confusion matrix
  */
    cout << setw(4) << "0" << setw(4) << "1" << setw(4) << "2" << setw(4);
    cout << "3" << setw(4) << "4" << setw(4) << "5" << setw(4) << "6" << setw(4);
    cout << "7" << setw(4) << "8" << setw(4) << "9" << endl;
	  for (int i=0; i<10; i++){
		  cout << i << ": ";
		  for (int j=0; j<10; j++) {
			  cout << setw(4) << matrix[i][j] << " ";
		  }
		cout << endl;
		}
}


void ActivateFunction::set() {
  /**
  \brief Метод для задания функции активации.
  \warning Реализована только функция ReLu.
  \throw std::runtime_error Значение actFunc не задано.
 */
  std::cout << "Функция активации (2 - ReLU): ";
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

void ActivateFunction::autoset() {
  /**
  \brief Метод для задания функции активации.
  \warning Реализована только функция ReLu.
  \throw std::runtime_error Значение actFunc не задано.
 */
  actFunc = ReLU;
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
