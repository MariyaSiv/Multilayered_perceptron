#include "Matrix.h"

void Matrix::Init(int row, int col) {
  /**
  \brief Метод для инициализации матрицы (все заполняется нулями).
  
  \param[in] row Количество строк матрицы
  \param[in] col Количество столбцов
  */
  this->row = row; this->col = col;
  matrix = new double* [row]; // Выделяем память
  for (int i = 0; i < row; i++)
    matrix[i] = new double[col]; //Выделяем память

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i][j] = 0; // Заполняем нулями
    }
  }
}

void Matrix::Rand() {
  /**
  \brief Метод для заполнения матрицы случайными значениями.
  */
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j ++) {
      matrix[i][j] = (rand() % 100) * 0.03 / (row + 35);
      // rand() возвращает случайное число от нуля до RAND_MAX
    }
  }
}

void Matrix::Multi(const Matrix& m, const double* neuron, int n, double* out) {
  /**
  \brief Метод для умножения матрицы на вектор.
  
  \param[in] m Ссылка на матрицы
  \param[in] neuron Указатель на вектор
  \param[in] n Длина вектора 
  \param[out] out Указатель на результат умножения
  */
  if (m.col != n){
    throw std::runtime_error("Error:Multi");
  }

  for (int i = 0; i < m.row; ++i) {
    double tmp = 0;
    for (int j = 0; j < m.col; ++j) {
      tmp += m.matrix[i][j] * neuron[j];
    }

    out[i] = tmp;
  }
}

void Matrix::Multi_T(const Matrix& m, const double* neuron, int n, double* out) {
  /**
  \brief Метод для умножения транспонированной матрицы на вектор.
  
  \param[in] m Ссылка на матрицу
  \param[in] neuron Указатель на вектор
  \param[in] n Длина вектора 
  \param[out] out Указатель на результат умножения
  */
  if (m.row != n){
    throw std::runtime_error("Ошибка Multi_T. Умножение матрицы на вектор неподходящей длинны.\n");
  }

  for (int i = 0; i < m.col; ++i) {
    double tmp = 0;
    for (int j = 0; j < m.row; ++j) {
      tmp += m.matrix[j][i] * neuron[j];
    }
    out[i] = tmp;
  }
}

void Matrix::SumVector(double* a, const double* b, int n) {
  /**
  \brief Метод для суммирования двух векторов (a и b).
  
  \param[out] a Вектора a
  \param[in] b Вектор b
  \param[in] n Длина векторов
  */
  for (int i = 0; i < n; i++) {
    a[i] += b[i];
  }
}

double& Matrix::operator()(int i, int j) {
  /**
  \brief Перезагрузка оператора () для удобного доступа к элементам матрицы..
  
  \param[in] i Номер строки
  \param[in] j Номер столбца

  \return Ссылку на элемент матрицы
  */
  return matrix[i][j];
}

std::ostream& operator << (std::ostream& os, const Matrix& m) {
  for (int i = 0; i < m.row; ++i) {
    for (int j = 0; j < m.col; ++j) {
      os << m.matrix[i][j] << " "; 
    }
  }
  return os;
}

std::istream& operator >> (std::istream& is, Matrix& m) {
  for (int i = 0; i < m.row; ++i) {
    for (int j = 0; j < m.col; ++j) {
      is >> m.matrix[i][j]; 
    }
  }
  return is;
}

