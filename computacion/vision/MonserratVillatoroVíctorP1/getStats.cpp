#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>

#include "p1_getopt.hpp"
#include "p1_mousehandler.hpp"
#include "p1_stats.hpp"
#include "p1_mask.hpp"

int main(int argc, char *argv[]){
  bool iflag = false;
  bool wflag = false;
  bool imgflag = false;
  bool mflag = false;
  std::vector<int> wvalues;
  std::string imgName, maskName;
  if(getoptions(argc, argv, iflag, wflag, wvalues, imgflag, mflag, imgName, maskName) == EXIT_SUCCESS){
    cv::Mat mask, roi_img;
    _img = cv::imread(imgName, -1);
    if(!_img.data){
      std::cout << "No se puede abrir la imagen" << std::endl;
      return EXIT_FAILURE;
    }
    if(mflag){
      mask = cv::imread(maskName, 0);
      if(!mask.data){
        std::cout << "No se puede abrir la máscara" << std::endl;
        return EXIT_FAILURE;
      }
    }
    if(iflag){
      if(mflag){
        _img = applyMask(_img, mask);
      }
      cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
      cv::imshow("Image", _img);
      int k;
      while(true){
        cv::setMouseCallback("Image", mouseHandler, NULL);
        k = cv::waitKey(0);
        if(k == 10 or k == 1048586){
          break;
        }else if(k == 27 or k == 1048603){
          return EXIT_SUCCESS;
        }
      }
      cv::Rect rect;
      if(_p1.x < _p2.x){
        if(_p1.y < _p2.y){
          rect = cv::Rect(_p1.x, _p1.y, _p2.x-_p1.x, _p2.y-_p1.y);
        }else{
          rect = cv::Rect(_p1.x, _p2.y, _p2.x-_p1.x, _p1.y-_p2.y);
        }
      }else{
        if(_p1.y < _p2.y){
          rect = cv::Rect(_p2.x, _p1.y, _p1.x-_p2.x, _p2.y-_p1.y);
        }else{
          rect = cv::Rect(_p2.x, _p2.y, _p1.x-_p2.x, _p1.y-_p2.y);
        }
      }
      roi_img = _img(rect);
      if(mflag){
        mask = mask(rect);
      }
    }else if(wflag){
      roi_img = _img(cv::Rect(wvalues[0], wvalues[1], wvalues[2], wvalues[3]));
      if(mflag){
        mask = mask(cv::Rect(wvalues[0], wvalues[1], wvalues[2], wvalues[3]));
      }
    }else{
      roi_img = _img.clone();
    }
    stats(roi_img, mflag, mask);
  }else{
    return EXIT_FAILURE;
  }
}
