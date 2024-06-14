#include "Network.h"
#include "Reader.h"
#include <cmath>
//#include <chrono>

int main() {
  Network NW{};
  data_Network NW_config;
  data_info* data;
  double ra = 0; 
  double right = 0; 
  double predict = 0;
  double maxra = 0;
  int epoch = 0;
  bool study, repeat = true;
  //chrono::duration<double> time;

  NW_config = ReadDataNetwork("../data/config.txt");
  NW.Init(NW_config);
  NW.PrintConfig();

  while (repeat) {
    cout << "STUDY? (1/0)" << endl;
    cin >> study;
    if (study) {
      int examples = 60000;
      data = ReadData("../training/mnist_train_N.csv", NW_config, examples);
      while (ra / examples * 100 < 100) {
        ra = 0;
        for (int i = 0; i < examples; i++) {
          NW.SetInput(data[i].pixels);
          right = data[i].digit;
          predict = NW.ForwardFeed();
          if (predict != right) {
            NW.BackPropogation(right);
            NW.WeightsUpdate(0.1 * exp(-epoch / 20.));
          } else
            ra++;
        }
        if (ra > maxra) maxra = ra;
        cout << "Правильные ответы: " << ra/ examples * 100 << "\t maxra: " << maxra/examples * 100 << endl;
        epoch++;

        if (epoch == 13) break;
      }
      NW.SaveWeights(); 
    } else {
      NW.ReadWeights();
    }

    cout << "TEST? (1/0)" << endl;
    bool test_flag;
    cin >> test_flag;
    if (test_flag) {
      int ex_tests = 10000;
      data_info* data_test;
      data_test = ReadData("../training/mnist_test_N.csv", NW_config, ex_tests);
      ra = 0;
      for (int i = 0; i < ex_tests; i++) {
        NW.SetInput(data_test[i].pixels);
        predict = NW.ForwardFeed();
        right = data_test[i].digit;
        if (right == predict)
          ra++;
      }
      cout << "RA (TEST): " << ra/ex_tests * 100 << endl;
    }

    // My test
    cout << "TEST ON YOUR IMAGE? (1/0)" << endl;
    bool my_test_flag;
    cin >> my_test_flag;
    if (my_test_flag) {
      int my_tests = 10;
      data_info* data_test;
      data_test = ReadData("../data/my_test.csv", NW_config, my_tests);
      for (int i = 0; i < my_tests; i++) {
        NW.SetInput(data_test[i].pixels);
        predict = NW.ForwardFeed();
        cout << "PREDICTION: " << predict << endl;
        NW.PrintValues(2); // Последний слой
      }
    }

    cout << "Repeat? (1/0)" << endl;
    cin >> repeat;
  }
  return 0;
}
