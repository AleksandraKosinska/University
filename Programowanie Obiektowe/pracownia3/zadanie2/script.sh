##!/bin/bash
mcs -target:library zad2_f.cs
mcs zad2_m.cs -reference:zad2_f.dll
mono zad2_m.exe
rm -f zad2_m.exe