#!/usr/bin/python
#-*-coding: utf-8-*-

import p4_book
import p4_comic

def loadStock(file):
    f = open(file, "r")
    stock = []
    for line in f.readlines():
        lineRead = line.split(",")
        if lineRead[0] == "b":
            stock.append(p4_book.Book(lineRead[1], lineRead[2], lineRead[3], lineRead[4], lineRead[5], lineRead[6]))
        else:
            stock.append(p4_comic.Comic(lineRead[1], lineRead[2], lineRead[3], lineRead[4], lineRead[5], lineRead[6], lineRead[7]))
    return stock

def sell(publication, stock):
    stock.remove(publication)

def add(publication, stock):
    stock.append(publication)

def search(publication, stock):
    for x in stock:
        if publication == x:
            return True
    return False

def saveStock(stock, file):
    f = open(file, "w")
    for publication in stock:
        if publication.__class__.__name__ == "Book":
            f.write("b,")
            f.write(publication._year + ",")
            f.write(publication._place + ",")
            f.write(publication._editorial + ",")
            f.write(publication._name + ",")
            f.write(publication._author + ",")
            f.write(publication._gender)
        elif publication.__class__.__name__ == "Comic":
            f.write("c,")
            f.write(publication._year + ",")
            f.write(publication._place + ",")
            f.write(publication._editorial + ",")
            f.write(publication._name + ",")
            f.write(publication._author + ",")
            f.write(publication._gender + ",")
            f.write(publication._number)

option = ""
stock = []
while option != "0":
    print "SALIR                    - 0"
    print "CARGAR STOCK             - 1"
    print "VENDER PUBLICACIONES     - 2"
    print "AÑADIR PUBLICACIONES     - 3"
    print "BUSCAR PUBLICACIONES     - 4"
    print "ALMACENAR STOCK          - 5"
    print "OPCIÓN:                  [0-5]"
    option = raw_input()
    if option == "1":
        stock = loadStock("p4_stock.txt")
    elif option == "2":
        i = 1
        for publication in stock:
            print publication._name + "\t\t- " + str(i)
            i += 1
        print "OPCIÓN: [1 - %i]" %(i-1)
        index = int(raw_input())
        publication = stock[index - 1]
        sell(publication, stock)
    elif option == "3":
        year = raw_input("Year: ")
        place = raw_input("Place: ")
        editorial = raw_input("Editorial: ")
        name = raw_input("Name: ")
        author = raw_input("Author: ")
        gender = raw_input("Gender: ")
        book = p4_book.Book(year, place, editorial, name, author, gender)
        add(book, stock)
    elif option == "4":
        year = raw_input("Year: ")
        place = raw_input("Place: ")
        editorial = raw_input("Editorial: ")
        name = raw_input("Name: ")
        author = raw_input("Author: ")
        gender = raw_input("Gender: ")
        book = p4_book.Book(year, place, editorial, name, author, gender)
        isPublication = search(book, stock)
        print isPublication
    elif option == "5":
        saveStock(stock, "p4_stock.txt")
