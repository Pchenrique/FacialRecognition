#include "projeto.h"

Mat convoluir(Mat& img, float masc[][3]){
    float output;
    Mat resp = img.clone();

    for(int x=0;x<img.rows;x++){
        for(int y=0;y<img.cols;y++){
            resp.at<uchar>(x,y) = 0;
        }
    }
    for(int x=1;x<img.rows-1;x++){
        for(int y=1;y<img.cols-1;y++){
            output = 0;
            for(int ml=-1;ml<2;ml++){
                for(int mc=-1;mc<2;mc++){
                    output = output + masc[mc+1][ml+1]*img.at<uchar>(x-mc,y-ml);
                }
            }
            resp.at<uchar>(x,y) = output;
        }
    }
    return (resp);
}

int trunca (int valor){
    if (valor>255){
        valor = 255;
    }
    if (valor<0){
        valor =0;
    }

    return valor;
}

int primeiroPicoColuna(Mat img){
    Mat gy;
    int indice_maior, maior = -1, colunas;

    img = gaussiana(img);

    gy = convoluirGy(img);

    threshold(gy,gy,0,255,THRESH_OTSU);

    int offset = 10;
    for(int j=offset; j<gy.cols-offset; j++){
        colunas=0;
        for(int i=offset; i<gy.rows-offset; i++){
            if(gy.at<uchar>(i,j) == 255){
                colunas++;
            }
        }
        if(colunas > maior){
            maior=colunas;
            indice_maior = j;
        }
    }
    return indice_maior;
}

int segundoPicoColuna(Mat img){
    int primeiro,k, *h, maior=-1, indeceMaior;
    primeiro = primeiroPicoColuna(img);

    Mat img2 = gaussiana(img);
    Mat gy2 = convoluirGy(img2);
    threshold(gy2,gy2,0,255,THRESH_OTSU);

    h = (int*) malloc(gy2.cols * sizeof(int));

    int offset=10;
    for(int j=offset; j<gy2.cols-offset; j++){
        h[j]=0;
        for(int i=offset; i<gy2.rows-offset; i++){
            if(gy2.at<uchar>(i,j) == 255){
                h[j]++;
            }
        }
    }
    int val;
    for(k=offset;k<gy2.cols-offset;k++){
        val = (k-primeiro)*(k-primeiro)*h[k];
        if(val>maior){
            maior = val;
            indeceMaior = k;
        }
    }
    return indeceMaior;
}

int primeiroPicoLinha(Mat img){
    Mat gx;
    int indice_maior, maior = -1, linhas;

    img = gaussiana(img);

    gx = convoluirGx(img);

    threshold(gx,gx,0,255,THRESH_OTSU);

    int offset = 10;
    for(int i=offset; i<gx.rows-offset; i++){
        linhas=0;
        for(int j=offset; j<gx.cols-offset; j++){
            if(gx.at<uchar>(i,j) == 255){
                linhas++;
            }
        }
        if(linhas > maior){
            maior=linhas;
            indice_maior = i;
        }
    }
    return indice_maior;
}

int segundoPicolinha(Mat img){
    int primeiro,k, *g, maior=-1, indeceMaior;
    primeiro = primeiroPicoLinha(img);

    Mat img2 = gaussiana(img);

    Mat gx2 = convoluirGx(img2);

    threshold(gx2,gx2,0,255,THRESH_OTSU);

    g = (int*) malloc(gx2.rows * sizeof(int));

    int offset=10;
    for(int i=offset; i<gx2.rows-offset; i++){
        g[i]=0;
        for(int j=offset; j<gx2.cols-offset; j++){
            if(gx2.at<uchar>(i,j) == 255){
                g[i]++;
            }
        }
    }
    int val;
    for(k=offset;k<gx2.rows-offset;k++){
        val = (k-primeiro)*(k-primeiro)*g[k];
        if(val>maior){
            maior = val;
            indeceMaior = k;
        }
    }
    return indeceMaior;
}

Mat retornaCinza(Mat img){
   Mat imgC = Mat(img.rows, img.cols, CV_8UC1);

   for(int i=0; i<img.rows; i++){
       for(int j=0; j<img.cols; j++){
           imgC.at<uchar>(i,j) = 0.3*img.at<Vec3b>(i,j)[2] + 0.59*img.at<Vec3b>(i,j)[1] + 0.11*img.at<Vec3b>(i,j)[0];
       }
   }
   return imgC;
}

Mat gaussiana(Mat img){
    float mask[3][3] = {{1/16.0,2/16.0,1/16.0},
                       {2/16.0,4/16.0,2/16.0},
                       {1/16.0,2/16.0,1/16.0}};
    Mat aux;
    aux = img.clone();

    int n,s,l,o,ne,no,se,so,p;
    for(int i=1; i<img.rows-1; i++){
        for(int j=1; j<img.cols-1; j++){
            p = img.at<uchar>(i,j);
            n = img.at<uchar>(i-1,j);
            s = img.at<uchar>(i+1,j);
            l = img.at<uchar>(i,j+1);
            o = img.at<uchar>(i,j-1);
            ne = img.at<uchar>(i-1,j+1);
            no = img.at<uchar>(i-1,j-1);
            se= img.at<uchar>(i+1,j+1);
            so = img.at<uchar>(i+1,j-1);
            aux.at<uchar>(i,j) = trunca((no*mask[2][2])+(n*mask[2][1])+(ne*mask[2][0])+(o*mask[1][2])+(p*mask[1][1])
                    +(l*mask[1][0])+(so*mask[0][2])+(s*mask[0][1])+(se*mask[0][0]));
        }
    }
    return aux;
}

Mat convoluirGy(Mat img){
    float mask[3][3] = {{-1,0,1},
                       {-2,0,2},
                       {-1,0,1}};
    Mat aux;
    aux = img.clone();

    int n,s,l,o,ne,no,se,so,p;
    for(int i=1; i<img.rows-1; i++){
        for(int j=1; j<img.cols-1; j++){
            p = img.at<uchar>(i,j);
            n = img.at<uchar>(i-1,j);
            s = img.at<uchar>(i+1,j);
            l = img.at<uchar>(i,j+1);
            o = img.at<uchar>(i,j-1);
            ne = img.at<uchar>(i-1,j+1);
            no = img.at<uchar>(i-1,j-1);
            se= img.at<uchar>(i+1,j+1);
            so = img.at<uchar>(i+1,j-1);
            aux.at<uchar>(i,j) = trunca((no*mask[2][2])+(n*mask[2][1])+(ne*mask[2][0])+(o*mask[1][2])+(p*mask[1][1])
                    +(l*mask[1][0])+(so*mask[0][2])+(s*mask[0][1])+(se*mask[0][0]));
        }
    }
    return aux;
}

Mat convoluirGx(Mat img){
    float mask[3][3] = {{-1,0,-1},
                       {0,0,0},
                       {1,0,1}};
    Mat aux;
    aux = img.clone();

    int n,s,l,o,ne,no,se,so,p;
    for(int i=1; i<img.rows-1; i++){
        for(int j=1; j<img.cols-1; j++){
            p = img.at<uchar>(i,j);
            n = img.at<uchar>(i-1,j);
            s = img.at<uchar>(i+1,j);
            l = img.at<uchar>(i,j+1);
            o = img.at<uchar>(i,j-1);
            ne = img.at<uchar>(i-1,j+1);
            no = img.at<uchar>(i-1,j-1);
            se= img.at<uchar>(i+1,j+1);
            so = img.at<uchar>(i+1,j-1);
            aux.at<uchar>(i,j) = trunca((no*mask[2][2])+(n*mask[2][1])+(ne*mask[2][0])+(o*mask[1][2])+(p*mask[1][1])
                    +(l*mask[1][0])+(so*mask[0][2])+(s*mask[0][1])+(se*mask[0][0]));
        }
    }
    return aux;
}
