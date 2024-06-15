#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../src/Network.h"
#include "../src/Reader.h"

const int N_TRAINDATASET = 60000;

TEST(NetworkTest, RAGT20) {
	Network NW{}; // Перспетрон
  data_Network NW_config; // Конфигурация
  double ra = 0; // Правильный ответы
  int right = 0; // Правильная цифра
  int predict = 0; // Предсказанный ответ
  int epoch = 0;
  bool study, repeat = true;

  NW_config = ReadDataNetwork("../data/config.txt");
  NW.autoset = true;
  NW.Init(NW_config);

  data_info* data; int N = N_TRAINDATASET;
  data = ReadData("../training/mnist_train_N.csv", NW_config, N);
  for (int i = 0; i < N; i++) {
    NW.SetInput(data[i].pixels);
  	right = data[i].digit;
    predict = NW.ForwardFeed();
    if (predict != right) {
      NW.BackPropogation(right);
      NW.WeightsUpdate(0.1 * exp(-epoch / 20.));
    } else
      ra++;
  }
  delete data;
  EXPECT_TRUE((ra/N * 100 > 20));
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
