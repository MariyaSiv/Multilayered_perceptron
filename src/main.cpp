#include "Network.h"
#include "Reader.h"
#include <cmath>
#include <iomanip>
#include <chrono>

const int N_EPOCH        = 10;
const int N_TRAINDATASET = 60000;
const int N_TESTDATASET  = 10000;
const int N_MYDATASET    = 10;

int main() {
  Network NW{}; // Перспетрон
  data_Network NW_config; // Конфигурация
  double ra = 0; // Правильный ответы
  int right = 0; // Правильная цифра
  int predict = 0; // Предсказанный ответ
  double maxra = 0;
  int epoch = 0;
  bool study, repeat = true;
  chrono::duration<double> time;

  NW_config = ReadDataNetwork("../data/config.txt");
  NW.Init(NW_config);
  NW.PrintConfig();

  while (repeat) {
    cout << "STUDY? (1/0) ";
    cin >> study;
    if (study) {
      data_info* data; int N = N_TRAINDATASET;
      data = ReadData("../training/mnist_train_N.csv", NW_config, N);

      auto begin = chrono::steady_clock::now();
      while (ra / N * 100 < 100) {
        ra = 0;

        auto epoch_start = chrono::steady_clock::now();
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
        auto epoch_end = chrono::steady_clock::now();
        
        time = epoch_end - epoch_start;
        if (ra > maxra) maxra = ra;
        cout << "Accuracy %: " << ra/N * 100;
        cout << "\t MAX RA: " << maxra/N * 100;
        cout << "\t Time: " << time.count() << " s" <<endl;

        epoch++;
        if (epoch == N_EPOCH) break;
      }
      auto end = chrono::steady_clock::now();
      time = end - begin;
      cout << "Total time: " << time.count() << endl;
      NW.SaveWeights();
      delete data; 

    } else {
      NW.ReadWeights();
    }

    cout << "TEST? (1/0) ";
    bool test_flag;
    cin >> test_flag;
    if (test_flag) {
      int ex_tests = N_TESTDATASET;
      data_info* data_test;
      data_test = ReadData("../training/mnist_test_N.csv", NW_config, ex_tests);
      
      confusion_Matrix CM;
      CM.Init();

      ra = 0;
      for (int i = 0; i < ex_tests; i++) {
        NW.SetInput(data_test[i].pixels);
        predict = NW.ForwardFeed();
        CM(data_test[i].digit, predict)++;
        right = data_test[i].digit;
        if (right == predict)
          ra++;
      }

      cout << "RA (TEST): " << ra/ex_tests * 100 << endl;
      CM.Print();
		}

    // My test
    cout << "TEST ON YOUR IMAGE? (1/0)" << endl;
    bool my_test_flag;
    cin >> my_test_flag;
    if (my_test_flag) {
      int my_tests = N_MYDATASET;
      data_info* data_test;
      data_test = ReadData("../data/my_test.csv", NW_config, my_tests);
      for (int i = 0; i < my_tests; i++) {
        NW.SetInput(data_test[i].pixels);
        predict = NW.ForwardFeed();
        cout << "PREDICTION: " << predict << endl;
        NW.PrintValues(NW_config.L-1); // Последний слой
      }
    }

    cout << "Repeat? (1/0)" << endl;
    cin >> repeat;
  }
  return 0;
}
