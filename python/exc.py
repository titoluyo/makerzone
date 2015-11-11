#!/usr/bin/python
import sys
sys.path.append("/usr/local/lib/python3.2/dist-packages/")
sys.path.append("/usr/lib/python2.7/dist-packages/")
import xlwt
import serial
import xlrd  
import time
localtime = time.asctime( time.localtime(time.time()) )

PuertoSerie = serial.Serial('/dev/ttyUSB0', 9600)
book = xlrd.open_workbook("basedata2.xls")

sh = book.sheet_by_index(0)

sArduino = (PuertoSerie.readline(8))

dni = str(sArduino)
for rx in range(sh.nrows):
	if dni == sh.cell_value(rowx=rx, colx=3):
		print sh.row(rx)
		print localtime
		fila=rx
		nombre=sh.cell_value(rowx=rx, colx=0)
		apellido=sh.cell_value(rowx=rx, colx=1)
style1 = xlwt.easyxf('',num_format_str='DD-MMM-YY')
wb = xlwt.Workbook()
ws = wb.add_sheet('A Test Sheet',cell_overwrite_ok=True)
ws.write(fila, 4,localtime,style1)
ws.write(fila, 2,nombre,style1)
ws.write(fila, 3,apellido,style1)

wb.save('example.xls')
