#include "Reader.h"

data_Network ReadDataNetwork(string path) {
  data_Network data{};
  ifstream fin;
  fin.open(path);
  if (!fin.is_open()) {
    cout << "Error\n"; 
  } else {
    cout << path << " загрузка...\n";
  }
  string tmp;
  int L;
  while (!fin.eof()) {
    fin >> tmp;
    if (tmp == "Network") {
      fin >> L;
      data.L = L;
      data.size = new int[L];
      for (int i = 0; i < L; i++){
        fin >> data.size[i];
      }
    }
  }
  fin.close();
  return data;
}

data_info* ReadData(string path, const data_Network& data_NW, int &examples){
  data_info* data;
  data = new data_info[examples];
  ifstream csvread;
  csvread.open(path, ios::in);
  if(csvread){
    string s;
    int data_pt = 0;
    while(getline(csvread, s)) {
      stringstream ss(s);
      int pxl = 0;
      while(ss.good()){
        string substr;
        getline(ss, substr, ',');
        if (pxl == 0) {
          data[data_pt].digit = stoi(substr);
          data[data_pt].pixels = new double [data_NW.size[0]];
        } else {
          data[data_pt].pixels[pxl-1] = stof(substr);
        }
        pxl++;
      }
      data_pt++;
    }
    csvread.close();
    cout << path << " загружен.." << endl;
  } else {
    cout << "Ошибка!!" << endl;
  }
  return data;
}

