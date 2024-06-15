#include "Network.h"

void Network::Init(data_Network data) {
  /**
  \brief Инициализация персептрона случайными значениями.
  Значения  bios инициализируются единицами.
  
  \param[in] data Параметры конфигурации персептрона (количество слоев и их размеры)
  */
  if (autoset) {
    actFunc.autoset();
  } else {
    actFunc.set();
  }
  srand(time(NULL));
  L = data.L;
  size = new int[L];
  for (int i = 0; i < L; i++) {
    size[i] = data.size[i];
  }

  weights = new Matrix[L-1];
  bios = new double* [L-1];
  for (int i = 0; i < L - 1; i++) {
    weights[i].Init(size[i+1], size[i]);
    bios[i] = new double[size[i+1]];
    weights[i].Rand();
    for (int j = 0; j < size[i+1]; j++){
      bios[i][j] = (rand() % 50) * 0.06 / (size[i] + 15);
    }
  }

  neurons_val = new double* [L]; 
  neurons_err = new double* [L];
  for (int i = 0; i < L; i++) {
    neurons_val[i] = new double[size[i]];
    neurons_err[i] = new double[size[i]];
  }

  neurons_bios_val = new double [L-1];
  for (int i = 0; i < L-1; i++){
    neurons_bios_val[i] = 1;
  }
}

void Network::PrintConfig() {
  /**
  \brief Печать конфигурации нейросети.
  */
  cout << "********************************\n";
  cout << "Network Config\n";
  cout << "Слои (Layers) = " << L << "\nРазмер (Size):";
  for (int i = 0; i < L; i++) {
    cout << size[i] << " ";
  }
  cout << "\n********************************\n";
}

void Network::SetInput(double* values) {
  /**
  \brief Метод для подачи сигнала на вход сети.

  \param[in] values Вектор с сигналом, который подается на вход. 
  */
  for (int i = 0; i < size[0]; i++) {
    neurons_val[0][i] = values[i];
  }
}

int Network::ForwardFeed() {
  /**
  \brief Проход вперед. Передача сигнала от первого слоя к последнему.
  
  \return Возвращает индекс максимального значения с последнего слоя (т.е. наиболее
  вероятный ответ)
  */
  for (int k = 1; k < L; ++k) {
    Matrix::Multi(weights[k-1], neurons_val[k-1], size[k-1], neurons_val[k]);
    Matrix::SumVector(neurons_val[k], bios[k-1], size[k]);
    actFunc.use(neurons_val[k], size[k]);
  }

  int predict = SearchMaxIndex(neurons_val[L-1]);
  return predict;
}

int Network::SearchMaxIndex(double* value) {
  /**
  \brief Поиск максимального значения в векторе.
  \param[in] value Вектор значений 
  \return Возвращает индекс максимального значения вектора.
  */
  double max = value[0];
  int prediction = 0;
  double tmp = 0;
  for (int i = 1; i < size[L-1]; i++) {
    tmp = value[i];
    if (tmp > max) {
      prediction = i;
      max = tmp;
    }
  }
  return prediction;
}

void Network::PrintValues(int L) {
  /**
  \brief Метод для печати значений нейронов на слое L.
  \param[in] L Номер слоя
  */
  for (int i = 0; i < size[L]; i++) {
    cout << i << " " << neurons_val[L][i] << endl;
  }
}

void Network::BackPropogation(double expect) {
  /**
  \brief Алгоритм обратного распространения ошибки.
  \param[in] expect Правильное значение
  */
  for (int i = 0; i < size[L-1]; i++) {
    if (i != int(expect)) {
      neurons_err[L-1][i] = - neurons_val[L-1][i] * actFunc.useDer(neurons_val[L-1][i]);
    } else {
      neurons_err[L-1][i] = (1.0 - neurons_val[L-1][i]) * actFunc.useDer(neurons_val[L-1][i]);
    }
  }

  for (int k = L - 2; k > 0; k--) {
    Matrix::Multi_T(weights[k], neurons_err[k+1], size[k+1], neurons_err[k]);
    for (int j = 0; j < size[k]; j++) {
      neurons_err[k][j] *= actFunc.useDer(neurons_val[k][j]);
    }
  }
}

void Network::WeightsUpdate(double lr) {
  /**
  \brief Обновление весов.
  \param[in] lr Значение learning rate.
  */
  for (int i = 0; i < L-1; ++i) {
    for (int j = 0; j < size[i+1]; ++j) {
      for (int k = 0; k < size[i]; ++k) {
        weights[i](j, k) += neurons_val[i][k] * neurons_err[i+1][j] * lr;
      }
    }
  }

  for (int i = 0; i < L-1; i++) {
    for (int k = 0; k < size[i+1]; k++){
      bios[i][k] += neurons_err[i+1][k] * lr;
    }
  }
}

void Network::SaveWeights() {
  /**
  \brief Запись значений весов.
  */
  ofstream fout; 
  fout.open(WEIGHTPATH);
  if (!fout.is_open()) {
    cout << "Ошибка чтения файла\n";
    system("pause");
  }

  for (int i = 0; i < L-1; i++) {
    fout << weights[i] << " ";
  }

  for (int i = 0; i < L-1; ++i) {
    for (int j = 0; j < size[i+1]; ++j) {
      fout << bios[i][j] << " ";
    }
  }
  cout << "Веса сохранены.\n";
  fout.close();
}

void Network::ReadWeights() {
  /**
  \brief Чтение значений весов.
  */
  ifstream fin; 
  fin.open(WEIGHTPATH);
  if (!fin.is_open()) {
    cout << "Ошибка записи в файла\n";
    system("pause");
  }
  for (int i = 0; i < L-1; ++i) {
    fin >> weights[i];
  }
  for (int i = 0; i < L-1; ++i) {
    for (int j = 0; j < size[i+1]; ++j) {
      fin >> bios[i][j];
    }
  }
  cout << "Веса взяты из последнего сохранения.\n";
  fin.close();
}
