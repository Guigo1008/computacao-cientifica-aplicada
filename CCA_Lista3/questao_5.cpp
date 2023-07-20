#include <iostream>

using namespace std;

double* cria_matriz_temperaturas();
int* cria_array_mudar();

int main(){
  cout.setf(ios_base::scientific);
  int soma_array_mudar;
  auto* aux = new double[100];
  int* array_mudar = cria_array_mudar();
  double* matriz_temp = cria_matriz_temperaturas();

  while(true){
    for(int i=1; i<9; i++){
      for(int j=1; j<9; j++){
        aux[i*10+j] = (matriz_temp[(i+1)*10 + j] + matriz_temp[(i-1)*10 + j]
        + matriz_temp[i*10 + (j+1)] + matriz_temp[i*10 + (j-1)])/4.;
        if((abs(matriz_temp[i*10+j]-aux[i*10+j]) > 0.001) && (abs(matriz_temp[i*10+j]-100.) > 0.001)){
          array_mudar[i*10+j] = 1;
        } 
        else {
          array_mudar[i*10+j] = 0;
        }
      }
    }

    for(int i=0; i<100; i++){
      if(array_mudar[i] == 1){
        matriz_temp[i] = aux[i];
      }
    }

    for(int i=0; i<100; i++){
      soma_array_mudar += array_mudar[i];
    }

    if (soma_array_mudar==0){
      break;
    }
    soma_array_mudar = 0;
  }

  for(int i=0; i<10; i++){
    cout << "|" << " ";
    cout << matriz_temp[i*10+0] << " ";
    cout << matriz_temp[i*10+1] << " ";
    cout << matriz_temp[i*10+2] << " ";
    cout << matriz_temp[i*10+3] << " ";
    cout << matriz_temp[i*10+4] << " ";
    cout << matriz_temp[i*10+5] << " ";
    cout << matriz_temp[i*10+6] << " ";
    cout << matriz_temp[i*10+7] << " ";
    cout << matriz_temp[i*10+8] << " ";
    cout << matriz_temp[i*10+9] << "|"<< "\n";
  }

  delete[] aux;
  delete[] array_mudar;
  delete[] matriz_temp;
  return 0;
}

double* cria_matriz_temperaturas(){
  auto* matriz = new double[100];
  
  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      matriz[i*10 + j] = 20.;
    }
  }

  matriz[2*10 + 7] = 100.;
  return matriz;
}

int* cria_array_mudar() {
  auto* array = new int[100];

  for(int i=0; i<100; i++){
    array[i] = 0;
  }
  return array;
}
