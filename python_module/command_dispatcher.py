import serial
import time
import threading

edu_ciaa_port = serial.Serial(port='/dev/ttyUSB1', baudrate=115200, timeout=0.5)


def clear_screen():
    print(chr(27) + "[2J")
    print(chr(27) + "[H")

def read_edu_ciaa_port():
    while True:
        bytes_to_read = edu_ciaa_port.in_waiting
        data_received = edu_ciaa_port.read(bytes_to_read).decode("utf-8");
        
        if len(data_received) > 0:
            clear_screen()
            print("[FROM EDU-CIAA] {}".format(data_received))

        time.sleep(0.1)


def main():
    if edu_ciaa_port.isOpen():
        edu_ciaa_port.close()
    edu_ciaa_port.open()
    print("Serial connection with EDU-CIAA opened. \n")

    thread_read = threading.Thread(target=read_edu_ciaa_port, args=())
    thread_read.start()

    while True:
        try:
            data_to_send = input(">> ")
            edu_ciaa_port.write(data_to_send.encode())

        except KeyboardInterrupt:
            print("User pressed ctrl+c to terminate the program.")
            edu_ciaa_port.close()

    edu_ciaa_port.close()

main()