first := 0;
second := 1;
escribir_cadena ('Introduce el número de terminos para Fibonacci: ');
leer(n);
escribir_cadena ('Los primeros ');
escribir (n);
escribir_cadena (' números de la serie son: \n');
para c desde 0 hasta n-1 paso 1 hacer
  si (c <= 1)
    entonces
    next := c;
  si_no
    next := first + second;
    first := second;
    second := next;
  fin_si;
  escribir (next);
  escribir_cadena ('\n');
fin_para;
