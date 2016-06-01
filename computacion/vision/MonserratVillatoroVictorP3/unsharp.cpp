#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "p3_getopt.hpp"
#include "unsharp_mask.hpp"

int channel = 2;

int main(int argc, char *argv[]){
  bool iflag = false, vflag = false, sflag = false, rflag = false, nflag = false, gflag = false, inflag = false, outflag = false, maskflag = false;
  int svalue = 0, nvalue = 2;
  float rvalue = 0.5, gvalue = 1.0;
  std::string invalue, outvalue, maskvalue;
  if(p3::getoptions(argc, argv, iflag, vflag, sflag, svalue, rflag, rvalue, nflag, nvalue, gflag, gvalue, inflag, invalue, outflag, outvalue, maskflag, maskvalue) == EXIT_SUCCESS){




    cv::Mat input = cv::imread(invalue, -1);
    if(!input.data){
      std::cout << "No ha sido posible leer la imagen" << std::endl;
      return EXIT_FAILURE;
    }
    cv::Mat mask;
    if(maskflag){
      mask = cv::imread(maskvalue, 0);
      if(!mask.data){
        std::cout << "No ha sido posible leer la máscara" << std::endl;
        return EXIT_FAILURE;
      }
    }
    //Obtengo el tamaño óptimo para realizar la transformada de Fourier sobre la imagen
    int m = cv::getOptimalDFTSize(input.rows);
    int n = cv::getOptimalDFTSize(input.cols);

    //Convertimos la imagen al espacio de color indicado si la imagen tiene 3 canales
    const int nChannels = input.channels();
    cv::Mat igs, tmp, img, padded;
    std::vector<cv::Mat> channels;
    if(nChannels == 3){
      //En cada caso convierto al espacio de color indicado, divido la imagen en 3 canales y escojo el canal que contiene la intensidad para tratarlo
      cv::cvtColor(input, igs, CV_BGR2HSV);
      cv::split(igs, channels);
      channels[channel].convertTo(tmp, CV_32F, 1.0/255.0);
      cv::copyMakeBorder(tmp, padded, 0, m-tmp.rows, 0, n-tmp.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0)); //Le añado borde a la imagen
    }else if(nChannels == 1){
      input.convertTo(img, CV_32F, 1.0/255.0); //Convierto la imagen a flotante (de 1 a 255 valores posibles)
      cv::copyMakeBorder(img, padded, 0, m-img.rows, 0, n-img.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0)); //Le añado borde a la imagen
    }

    cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)}; //Configuro imagen para aplicar transformada de fourier, la paso a flotante
    cv::Mat complex;
    cv::merge(planes, 2, complex); //Creo la imagen compleja con la que voy a trabajar
    cv::dft(complex, complex); //Hago la transformada de Fourier (con esto, cada punto origen pasa a las esquinas)
    cv::Mat filter = complex.clone(); //Filtro tendrá la imagen una vez aplicada la transformada de fourier
    //
    cv::Mat filterImg = complex.clone();
    //

    shiftDFT(complex); //Reordeno los cuadrantes de una imagen de Fourier de manera que el origen esté en el centro de la imagen (para no trabajar con las esquinas de la imagen)
    float cf = rvalue * sqrt(pow((input.cols), 2) + pow((input.rows), 2))/2;
    create_butterworth_lowpass_filter(filter, cf, nvalue); //Creo el filtro Butterwoth en filter (debe ser del mismo tamaño que la imagen a tratar)
    //
    create_butterworth_lowpass_filter(filterImg, cf, 0);
    //
    //
    cv::Mat complexImg = complex.clone();
    //
    cv::mulSpectrums(complex, filter, complex, 0); //Realizo la convolución en el dominio frecuencial, multiplicando elemento a elemento con el filtro (complexImg = complexImg*filtro)
    //
    /*cv::mulSpectrums(complexImg, filterImg, complexImg, 0);*/ //No hace falta porque la imagen se queda igual.
    //
    shiftDFT(complex); //Vuelvo a reordenar los cuadrantes
    //
    shiftDFT(complexImg);
    //

    cv::Mat spectrum = create_spectrum_magnitude_display(complex, true);
    //
    cv::Mat spectrumImg = create_spectrum_magnitude_display(complexImg, true);
    //

    cv::idft(complex, complex, cv::DFT_SCALE); //Calculo la inversa de la transformada, para volver al dominio espacial
    cv::split(complex, planes);
    cv::Mat imgOutput;
    //Normalizo el rango de valores de la imagen como del filtro
    cv::normalize(planes[0], imgOutput, 0, 1, CV_MINMAX);
    //Trabajo ahora con el plano real
    cv::split(filter, planes);
    cv::Mat filterOutput;
    cv::normalize(planes[0], filterOutput, 0, 1, CV_MINMAX);
    //Normalizo el plano real
    cv::Mat output = img.clone(); //Copio la imagen de entrada en la de salida para que tenga las mismas características

    //Ahora aplico la ganancia a cada píxel de la imagen en el canal indicado y teniendo en cuenta la máscara, en caso de haberla
    if(nChannels == 3){
      channels[channel] = tmp.clone();
      for(int i = 0; i < input.rows; i++){
        for(int j = 0; j < input.cols; j++){
          if(mask.empty() or mask.at<uchar>(i, j) != 0){
            channels[channel].at<float>(i, j) = tmp.at<float>(i, j)*(gvalue+1) - imgOutput.at<float>(i, j)*gvalue;
          }
        }
      }
      //Convierto la imagen a uchar para que se pueda visualizar de manera correcta
      channels[channel].convertTo(channels[channel], CV_8U, 255.0, 0.0);
      cv::merge(channels, igs); //Uno los canales
      cv::cvtColor(igs, output, CV_HSV2BGR); //Deshago el cambio del espacio de color pasando la imagen a BGR
    }else if(nChannels == 1){ //Si es en blanco y negro la imagen, debemos tener en cuenta los pixeles de la mascara (si la hay)
      for(int i = 0; i < input.rows; i++){
        for(int j = 0; j < input.cols; j++){
          if(mask.empty() or mask.at<uchar>(i, j) != 0){
            output.at<float>(i, j) = img.at<float>(i, j)*(gvalue+1) - imgOutput.at<float>(i, j)*gvalue;
          }
        }
      }
    }

    if(iflag){
      int cutoff_frecuency = rvalue * 100;
      int order = nvalue * 5;
      int gain = gvalue * 10;
      cv::namedWindow(outvalue+".png", cv::WINDOW_AUTOSIZE);
      cv::createTrackbar("Orden del filtro (x5)", outvalue+".png", &order, 50);
      cv::createTrackbar("Frecuencia de corte (x100)", outvalue+".png", &cutoff_frecuency, 100);
      cv::createTrackbar("Ganancia (x10)", outvalue+".png", &gain, 50);

      while(true){
        float c = cutoff_frecuency / 100.0;
        int o = order / 5;
        float g = gain / 10.0;







        cv::Mat igs, tmp, img, padded;
        std::vector<cv::Mat> channels;

        if(nChannels == 3){
          //Convertimos la imagen al espacio de color indicado si la imagen tiene 3 canales
          //En cada caso convierto al espacio de color indicado, divido la imagen en 3 canales y escojo el canal que contiene la intensidad para tratarlo
          cv::cvtColor(input, igs, CV_BGR2HSV);
          cv::split(igs, channels);
          channels[channel].convertTo(tmp, CV_32F, 1.0/255.0);
          cv::copyMakeBorder(tmp, padded, 0, m-tmp.rows, 0, n-tmp.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0)); //Le añado borde a la imagen
        }else if(nChannels == 1){
          input.convertTo(img, CV_32F, 1.0/255.0); //Convierto la imagen a flotante (de 1 a 255 valores posibles)
          cv::copyMakeBorder(img, padded, 0, m-img.rows, 0, n-img.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0)); //Le añado borde a la imagen
        }

        cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)}; //Configuro imagen para aplicar transformada de fourier, la paso a flotante
        cv::Mat complex;
        cv::merge(planes, 2, complex); //Creo la imagen compleja con la que voy a trabajar
        cv::dft(complex, complex); //Hago la transformada de Fourier (con esto, cada punto origen pasa a las esquinas)
        cv::Mat filter = complex.clone(); //Filtro tendrá la imagen una vez aplicada la transformada de fourier
        //
        cv::Mat filterImg = complex.clone();
        //

        shiftDFT(complex); //Reordeno los cuadrantes de una imagen de Fourier de manera que el origen esté en el centro de la imagen (para no trabajar con las esquinas de la imagen)
        c = c * sqrt(pow((input.cols), 2) + pow((input.rows), 2))/2;
        create_butterworth_lowpass_filter(filter, c, o); //Creo el filtro Butterwoth en filter (debe ser del mismo tamaño que la imagen a tratar)
        //
        create_butterworth_lowpass_filter(filterImg, c, 0);
        //
        //
        cv::Mat complexImg = complex.clone();
        //
        cv::mulSpectrums(complex, filter, complex, 0); //Realizo la convolución en el dominio frecuencial, multiplicando elemento a elemento con el filtro (complexImg = complexImg*filtro)
        //
        /*cv::mulSpectrums(complexImg, filterImg, complexImg, 0);*/  //No hace falta porque la imagen se queda igual.
        //
        shiftDFT(complex); //Vuelvo a reordenar los cuadrantes
        //
        shiftDFT(complexImg);
        //

        cv::Mat spectrum = create_spectrum_magnitude_display(complex, true);
        //
        cv::Mat spectrumImg = create_spectrum_magnitude_display(complexImg, true);
        //

        cv::idft(complex, complex, cv::DFT_SCALE); //Calculo la inversa de la transformada, para volver al dominio espacial
        cv::split(complex, planes);
        cv::Mat imgOutput;
        //Normalizo el rango de valores de la imagen como del filtro
        cv::normalize(planes[0], imgOutput, 0, 1, CV_MINMAX);
        //Trabajo ahora con el plano real
        cv::split(filter, planes);
        cv::Mat filterOutput;
        //Normalizo el plano real
        cv::normalize(planes[0], filterOutput, 0, 1, CV_MINMAX);
        //Copio la imagen de entrada en la de salida para que tenga las mismas características
        cv::Mat output = img.clone();

        //Ahora aplico la ganancia a cada píxel de la imagen en el canal indicado y teniendo en cuenta la máscara, en caso de haberla
        if(nChannels == 3){
          channels[channel] = tmp.clone();
          for(int i = 0; i < input.rows; i++){
            for(int j = 0; j < input.cols; j++){
              if(mask.empty() or mask.at<uchar>(i, j) != 0){
                channels[channel].at<float>(i, j) = tmp.at<float>(i, j)*(g+1) - imgOutput.at<float>(i, j)*g;
              }
            }
          }
          channels[channel].convertTo(channels[channel], CV_8U, 255.0, 0.0);
          //Convierto la imagen a uchar para que se pueda visualizar de manera correcta
          cv::merge(channels, igs); //Uno los canales
          cv::cvtColor(igs, output, CV_HSV2BGR); //Deshago el cambio del espacio de color pasando la imagen a BGR
        }else if(nChannels == 1){
          //Si es en blanco y negro la imagen, debemos tener en cuenta los pixeles de la mascara (si la hay)
          for(int i = 0; i < input.rows; i++){
            for(int j = 0; j < input.cols; j++){
              if(mask.empty() or mask.at<uchar>(i, j) != 0){
                output.at<float>(i, j) = img.at<float>(i, j)*(g+1) - imgOutput.at<float>(i, j)*g;
              }
            }
          }
        }




        cv::imshow(outvalue+".png", output);
        cv::Mat aux;
        cv::resize(filterOutput, aux, cv::Size(filterOutput.cols/2, filterOutput.rows/2));
        cv::imshow("Butterworth filter.png", aux);
        cv::resize(imgOutput, aux, cv::Size(imgOutput.cols/2, imgOutput.rows/2));
        cv::imshow("Low Pass Image.png", aux);
        cv::resize(spectrum, aux, cv::Size(spectrum.cols/2, spectrum.rows/2));
        cv::imshow("Filtered Spectrum.png", aux);
        cv::resize(spectrumImg, aux, cv::Size(spectrumImg.cols/2, spectrumImg.rows/2));
        cv::imshow("Image Spectrum.png", aux);
        int k = cv::waitKey(1);
        if(k == 10){
          break;
        }else if(k == 27){
          return EXIT_FAILURE;
        }
      }
    }else if(vflag){
      cv::imshow(outvalue+".png", output);
      cv::Mat aux;
      cv::resize(filterOutput, aux, cv::Size(filterOutput.cols/2, filterOutput.rows/2));
      cv::imshow("Butterworth filter.png", aux);
      cv::resize(imgOutput, aux, cv::Size(imgOutput.cols/2, imgOutput.rows/2));
      cv::imshow("Low Pass Image.png", aux);
      cv::resize(spectrum, aux, cv::Size(spectrum.cols/2, spectrum.rows/2));
      cv::imshow("Filtered Spectrum.png", aux);
      cv::resize(spectrumImg, aux, cv::Size(spectrumImg.cols/2, spectrumImg.rows/2));
      cv::imshow("Image Spectrum.png", aux);
      int k = cv::waitKey(0);
      if(k == 27){
        return EXIT_FAILURE;
      }
    }


    cv::imwrite(outvalue+".png", 255*output);
    cv::imwrite("Butterworth filter.png", 255*filterOutput);
    cv::imwrite("Low Pass Image.png", 255*imgOutput);
    cv::imwrite("Filtered Spectrum.png", 255*spectrum);
    cv::imwrite("Image Spectrum.png", 255*spectrumImg);




    return EXIT_SUCCESS;
  }else{
    return EXIT_FAILURE;
  }
}
