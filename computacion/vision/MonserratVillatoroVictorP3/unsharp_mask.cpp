#include "unsharp_mask.hpp"

//Reordena los cuadrantes de una imagen de Fourier de manera que el origen esté en el centro de la imagen
void shiftDFT(cv::Mat &fImage){
  cv::Mat tmp, q0, q1, q2, q3;

  int cx = fImage.cols/2;
  int cy = fImage.rows/2;

  q0 = fImage(cv::Rect(0, 0, cx, cy));
  q1 = fImage(cv::Rect(cx, 0, cx, cy));
  q2 = fImage(cv::Rect(0, cy, cx, cy));
  q3 = fImage(cv::Rect(cx, cy, cx, cy));

  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);

  q1.copyTo(tmp);
  q2.copyTo(q1);
  tmp.copyTo(q2);
}

//Función que crea un filtro Butterworth de paso baja de 2 canales con radio D (frecuencia de corte) y orden n
void create_butterworth_lowpass_filter(cv::Mat &dft_Filter, float D, int n){
  cv::Mat tmp = cv::Mat(dft_Filter.rows, dft_Filter.cols, CV_32F); //Guardo la imagen en un auxiliar

  cv::Point centre = cv::Point(dft_Filter.rows / 2, dft_Filter.cols / 2); //Almaceno el punto central de la imagen para trabajar con el radio desde el centro de la imagen

  double radius;
  for(int i = 0; i < dft_Filter.rows; i++){
    for(int j = 0; j < dft_Filter.cols; j++){
      radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
      tmp.at<float>(i, j) = (float) ( 1 / (1 + pow( (double) (radius / D), (double) (2 * n))));
    }
  }

  cv::Mat toMerge[] = {tmp, tmp};
  cv::merge(toMerge, 2, dft_Filter);
}

cv::Mat create_spectrum_magnitude_display(cv::Mat &complexImg, bool rearrange){
  cv::Mat planes[2];

  cv::split(complexImg, planes);
  cv::magnitude(planes[0], planes[1], planes[0]);

  cv::Mat mag = (planes[0]).clone();
  mag += cv::Scalar::all(1);
  log(mag, mag);

  if(rearrange){
    //rearreglar los cuadrantes
    shiftDFT(mag);
  }

  cv::normalize(mag, mag, 0, 1, CV_MINMAX);

  return mag;
}
