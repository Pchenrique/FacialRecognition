#ifndef PROJETO_H
#define PROJETO_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;


Mat convoluir(Mat& img, float masc[][3]);
int trunca (int valor);
int primeiroPicoColuna(Mat img);
Mat retornaCinza(Mat img);
Mat gaussiana(Mat img);
Mat convoluirGy(Mat img);
int segundoPicoColuna(Mat img);
Mat convoluirGx(Mat img);
int primeiroPicoLinha(Mat img);
int segundoPicolinha(Mat img);

#endif // PROJETO_H
