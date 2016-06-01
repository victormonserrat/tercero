#!/usr/bin/python

import p4_publication

class Book(p4_publication.Publication):

    def __init__(self, initY, initP, initE, initN, initA, initG):
        p4_publication.Publication.__init__(self, initY, initP, initE)
        self._name = initN
        self._author = initA
        self._gender = initG
