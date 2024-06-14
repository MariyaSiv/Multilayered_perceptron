#pragma once
#include <iostream>
#include <sstream>
#include "Network.h"

  /**
  \brief Структура для хранения пар (значения пикселей, цифра)
  */
struct data_info {
  double* pixels; ///< Значения пикселей изображения 28x28 = 784
  int digit; ///< Значение цифры, которая соотвествует изображению
};

data_Network ReadDataNetwork(string path);
data_info* ReadData(string path, const data_Network& data_NW, int &len);
