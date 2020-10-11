# Parallel Perceptron Neural Network
Desenvolvimento de uma rede neural 
Inspired by https://www.codeproject.com/Articles/1237026/Simple-MLP-Backpropagation-Artificial-Neural-Netwo

#### Compilar e executar

    $ g++ back.cpp -o back.exe -fopenmp && time ./back.exe

#### Compilar e executar versão otimizada por vetorização

    $ g++ -O3 back.cpp -o back.exe -fopenmp && time ./back.exe

O QUE FIZEMOS:
Nesse primeiro momento, paralelizamos o treinamento da rede neural. 

**Tempos paralelos por número de threads (1,2,4,8)**
Sequencial:
  real    0m10,942s
  user    0m0,015s
  sys     0m0,015s
Paralelo (2 threads):
  real    0m6,033s
  user    0m0,000s
  sys     0m0,000s
Paralelo (4 threads):
  real    0m3,779s
  user    0m0,000s
  sys     0m0,031s
Paralelo (8 threads):
  real    0m3,716s
  user    0m0,000s
  sys     0m0,047s
|                     | 1 thread  | 2 threads | 4 threads | 8 threads |
| ------------------- | --------- | --------- | --------- | --------- |
| Tempo               | 0m10,942s | 0m6,033s  | 0m3,779s  | 0m3,716s  |
