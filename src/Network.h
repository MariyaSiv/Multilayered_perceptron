#pragma once
#include "Utils.h"
#include "Matrix.h"
#include <fstream>
using namespace std;


/**
\brief Структура для хранения конфигурации для нейросети.
*/
struct data_Network {
  int L; ///< Количество слоев
  int* size; ///< Размеры слоев
};

/**
\brief Основной класс персептрона.
*/
class Network {
  int L; //сколько слоев
  int* size; // сколько нейронов на каждом из слоев [784] [256] [10]
  ActivateFunction actFunc;
  Matrix* weights;
  double** bios;
  double** neurons_val;
  double** neurons_err;
  double* neurons_bios_val;

public:
  string WEIGHTPATH = "../data/weights.txt";
  bool autoset = false;

  void Init(data_Network data);
  void PrintConfig();
  void SetInput(double* values);

  int ForwardFeed();
  int SearchMaxIndex(double* value);
  void PrintValues(int L);

  void BackPropogation(double expect);
  void WeightsUpdate(double lr);

  void SaveWeights();
  void ReadWeights();
};
