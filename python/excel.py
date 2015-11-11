#!/usr/bin/python
import sys
#sys.path.append("/usr/local/lib/python3.2/dist-packages/")
# Importamos la libreira de PySerial
#import serial
import xlrd  
 
# Abrimos el puerto del arduino a 9600
#PuertoSerie = serial.Serial('/dev/ttyUSB0', 9600)
# Creamos un buble sin fin
#while True:
    # leemos hasta que encontarmos el final de linea
 #   sArduino = PuertoSerie.readline()
    # Mostramos el valor leido y eliminamos el salto de linea del final
#    print sArduino.rstrip('\n')
dni = "09728479"
book = xlrd.open_workbook("basedata.xls")
print "The number of worksheets is", book.nsheets
print "Worksheet name(s):", book.sheet_names()
sh = book.sheet_by_index(0)
print sh.name, sh.nrows, sh.ncols
print "Cell (2,0) is: ", sh.cell_value(rowx=2, colx=0)
for rx in range(sh.nrows):
	if dni == sh.cell_value(rowx=rx, colx=3):
		print sh.row(rx)