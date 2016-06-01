escribir_cadena ('Introduce el número de términos para hacer la media: ');
leer(n);
valorFinal := 0;
para i desde 1 hasta n paso 1 hacer
  escribir_cadena ('elemento ');
  escribir (i);
  escribir_cadena (': ');
  leer(valor);
  valorFinal := valorFinal + valor;
fin_para;
escribir_cadena ('La media de tus elementos es ');
escribir (valorFinal/n);
escribir_cadena ('\n');
