#!/usr/bin/python

import random
import time

def devPalabras(fileName):
    file = open(fileName, "r")
    list = file.read().split(" ")
    file.close()
    return list

def seleccionaElemento(list):
    return list[random.randrange(len(list))]

def introLetra():
    isLetter = False
    while isLetter == False:
        character = raw_input()
        if len(character) == 1 and character.isalpha():
            isLetter = True
            return character

def buscaLetra(string1, string2):
    list = []
    i = 0
    while i < len(string2):
        if string2[i] == string1:
            list.append(i)
        i = i+1
    return list

def rmRepeated(input):
  output = []
  for x in input:
    if x not in output:
      output.append(x)
  return output

palabras = devPalabras("palabras.txt")
palabras = rmRepeated(palabras)
palabra = seleccionaElemento(palabras)
pista = list()
for i in range(0, len(palabra)):
    pista.append('-')
error, success = 0, 0
start = time.time()
while True:
    letra = introLetra()
    listaLetra = buscaLetra(letra, palabra)
    if len(listaLetra) == 0:
        error += 1
    elif len(listaLetra) != 0:
        success += 1
    for i in range(0, len(listaLetra)):
        pista[listaLetra[i]] = letra
    print pista
    end = "".join(pista)
    if error == 11:
        print "Has perdido"
        print "Aciertos: %d" %success
        print "Errores: %d" %error
        print "Tiempo: %d" %(time.time() - start)
        break
    if end == palabra:
        print "Has ganado"
        print "Aciertos: %d" %success
        print "Errores: %d" %error
        print "Tiempo: %d" %(time.time() - start)
        break
