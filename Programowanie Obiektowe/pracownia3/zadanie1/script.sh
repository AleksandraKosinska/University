##!/bin/bash
mcs -target:library zad1_f.cs
mcs zad1_m.cs -reference:zad1_f.dll
mono zad1_m.exe
rm -f zad1_m.exe