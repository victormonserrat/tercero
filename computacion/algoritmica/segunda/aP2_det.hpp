#ifndef __AP2_DET_HPP__
#define __AP2_DET_HPP__

#include <vector>
#include <cassert>
#include <cmath>

#include <iostream>

#include "matriz.hpp"

namespace aP2{
  template<class T>
  T determinanteIterativo(Matriz<T> const &m){
    Matriz <T> mAux = m;

  	int NoCero,A,NoReg = 0,Perm=0; //permutaciones
  	double Pivote,V1,Det=1.0;
  	for(int i=1 ; i <= mAux.filas() ; i++){
    	NoCero=0;A=i;

      	while((NoCero==0)&&(A<=mAux.filas())){
        	if((mAux.elemento(A,i)>0.0000001)||((mAux.elemento(A,i)<-0.0000001))){  // Si m[A][i]!=0
          		NoCero=1;
       	 	}
        	else A++;
      	}
      	if (A>mAux.filas()) NoReg=1;
      	if (A!=i) Perm++;

      	if (A>mAux.filas()){
        	cout << "Esta matriz no tiene determinante." << endl;
        	fflush(stdout);
        	return 0;
      	}
      	Pivote=mAux.elemento(A,i);

      	for(int j=1 ; j <= mAux.filas() ; j++){
        	V1 = mAux.elemento(A,j);
        	mAux.elemento(A, j, mAux.elemento(i, j));
        	mAux.elemento(i, j, V1);
      	}
      	for(int k = i+1 ; k <= mAux.filas() ; k++){
      		V1 = mAux.elemento(k,i);
      		for(int j = i ; j <= mAux.filas() ; j++){
          		mAux.elemento(k,j, mAux.elemento(k,j)-((V1/Pivote)*mAux.elemento(i,j)));
        	}
     	}
  	}
  	for(int k = 1 ; k <= mAux.filas() ; k++) Det=Det*mAux.elemento(k,k);

  	A=Perm;
  	if ((A%2)==1) Det=-Det; //Caso de permutaciones impares
  	if (NoReg==1) Det=0;
  	return Det;

    /*Matriz<T> aux = m;

    for(size_t i = 1; i < aux.filas(); i++){
      for(size_t j = i + 1; j <= aux.filas(); j++){
        T ji = aux.elemento(j, i);
        for(size_t k = i; k <= aux.columnas(); k++){
          aux.elemento(j, k, aux.elemento(i, i) * aux.elemento(j, k) - ji * aux.elemento(i, k));
        }
      }
    }
    T det = 1;
    for(size_t i = 1; i <= aux.filas(); i++){
      det *= aux.elemento(i, i);
    }
    return det;*/
  }
  template<class T>
  T determinanteRecursivo(Matriz<T> const &m){
    if(m.filas() == 1){
      return m.elemento(1, 1);
    }else{
      T det = 0;
      Matriz<T> aux = m;
      for(size_t i = 1; i <= m.filas(); i++){
        if(i % 2 != 0){
          det += m.elemento(i, 1) * determinanteRecursivo(aux.eliminarFilaColumna(i, 1));
        }else{
          det -= m.elemento(i, 1) * determinanteRecursivo(aux.eliminarFilaColumna(i, 1));
        }
      }
      return det;
    }
  }
}

#endif
