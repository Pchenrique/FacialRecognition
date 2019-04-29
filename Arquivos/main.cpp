#include "projeto.h"

int main(){

    Mat img, img2;
    int coluna=0, coluna2=0, linha=0, linha2=0;
    string nome[19] = {"alisson.jpg","anderson.jpg","caline.jpg","caline2.jpg","evelin.jpg","felipe.jpg","felipe2.jpg"
                       ,"geovanio.jpg","geovanio2.jpg","ingride.jpg","joaquim.jpg","leticia.jpg","leticia2.jpg",
                       "marcos.jpg","mateus.jpg","paulo.jpg","samuel.jpg","tiago.jpg","vinicius.jpg"};

    string destino = "c:\\pdi\\projetofinal\\processada\\";

    for(int cont=0; cont<19; cont++){

        //as proximas linhas comentadas referesse a se a webcam não estiver funcionando, pode upa imagens e teste o algoritmo

       /* img = imread("C:\\pdi\\projetofinal\\"+nome[cont], 1);
        img2 = retornaCinza(img);
       */


       VideoCapture cap(0); // abre a camera padrão
        if(!cap.isOpened()){  // verifica se a ouve sucesso ao abrir
            cout<<"CAMERA NAO ENCONTRADA";
           return -1;
        }
           namedWindow("processada", 1);
           for(;;){
               Mat img;
               cap >> img;
               img2 = retornaCinza(img);

               coluna = primeiroPicoColuna(img2);
               coluna2 = segundoPicoColuna(img2);
               linha = primeiroPicoLinha(img2);
               linha2 = segundoPicolinha(img2);

               int aux;
               if(coluna > coluna2){
                   aux = coluna2;
                   coluna2 = coluna;
                   coluna = aux;
               }
               if(linha > linha2){
                   aux = linha2;
                   linha2 = linha;
                   linha = aux;
               }

               for(int i=linha; i<linha2;i++){
                   img.at<Vec3b>(i,coluna)[0] = 0;
                   img.at<Vec3b>(i,coluna)[1] = 0;
                   img.at<Vec3b>(i,coluna)[2] = 255;
                   img.at<Vec3b>(i,coluna2)[0] = 0;
                   img.at<Vec3b>(i,coluna2)[1] = 0;
                   img.at<Vec3b>(i,coluna2)[2] = 255;
               }
               for(int j=coluna; j<coluna2; j++){
                   img.at<Vec3b>(linha,j)[0] = 0;
                   img.at<Vec3b>(linha,j)[1] = 0;
                   img.at<Vec3b>(linha,j)[2] = 255;
                   img.at<Vec3b>(linha2,j)[0] = 0;
                   img.at<Vec3b>(linha2,j)[1] = 0;
                   img.at<Vec3b>(linha2,j)[2] = 255;
               }

               imshow("processada",img);
               if(waitKey(30) >= 0){

               };
            }

        coluna = primeiroPicoColuna(img2);
        coluna2 = segundoPicoColuna(img2);
        linha = primeiroPicoLinha(img2);
        linha2 = segundoPicolinha(img2);

        int aux;
        if(coluna > coluna2){
            aux = coluna2;
            coluna2 = coluna;
            coluna = aux;
        }
        if(linha > linha2){
            aux = linha2;
            linha2 = linha;
            linha = aux;
        }

        for(int i=linha; i<linha2;i++){
            img.at<Vec3b>(i,coluna)[0] = 0;
            img.at<Vec3b>(i,coluna)[1] = 0;
            img.at<Vec3b>(i,coluna)[2] = 255;
            img.at<Vec3b>(i,coluna2)[0] = 0;
            img.at<Vec3b>(i,coluna2)[1] = 0;
            img.at<Vec3b>(i,coluna2)[2] = 255;
        }
        for(int j=coluna; j<coluna2; j++){
            img.at<Vec3b>(linha,j)[0] = 0;
            img.at<Vec3b>(linha,j)[1] = 0;
            img.at<Vec3b>(linha,j)[2] = 255;
            img.at<Vec3b>(linha2,j)[0] = 0;
            img.at<Vec3b>(linha2,j)[1] = 0;
            img.at<Vec3b>(linha2,j)[2] = 255;
        }

        imwrite(destino+"RecF_"+nome[cont], img);
    }

    return 0;
}
