import serial
import time

edu_ciaa_port = serial.Serial(port='/dev/ttyUSB1', baudrate=115200, timeout=0.5)

if edu_ciaa_port.isOpen():
	edu_ciaa_port.close()

edu_ciaa_port.open()

print("Serial connection with EDU-CIAA opened. \n")

while True:
	try:
		rx_string = ""
		while edu_ciaa_port.in_waiting > 0:
			rx_string = rx_string + edu_ciaa_port.read(1).decode("utf-8")	# read one byte at a time

		if rx_string != "":
			print("[FROM EDU-CIAA] {}".format(rx_string))

		time.sleep(0.2)
	except KeyboardInterrupt:
		print("User pressed ctrl+c to terminate the program.")
		edu_ciaa_port.close()

edu_ciaa_port.close()