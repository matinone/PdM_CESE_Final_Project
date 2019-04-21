import serial
import time
import threading

# global serial port object
edu_ciaa_port = serial.Serial(port='/dev/ttyUSB1', baudrate=115200, timeout=0.5)
arduino_port = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=0.5)


def clear_screen():
    print(chr(27) + "[2J")
    print(chr(27) + "[H")

# this function will run in a separate thread, constantly reading values from the EDU-CIAA serial port
def read_edu_ciaa_port():
    while True:
        bytes_to_read = edu_ciaa_port.in_waiting
        data_received = edu_ciaa_port.read(bytes_to_read).decode("utf-8");
        
        if len(data_received) > 0:
            data_received_lines = data_received.split('\r\n')

            for line in data_received_lines:
                if len(line) > 0:
                    if line.startswith("A_"):
                        device_header, message = line.split('_')
                        print("[FROM EDU-CIAA TO ARDUINO] {}".format(message))
                        arduino_port.write(message.encode())
                    else:
                        print("[FROM EDU-CIAA TO PC] {}".format(line))

        time.sleep(0.1)


# this function will run in a separate thread, constantly reading values from the ARDUINO serial port
def read_arduino_port():
    while True:
        bytes_to_read = arduino_port.in_waiting
        data_received = arduino_port.read(bytes_to_read).decode("utf-8");
        
        if len(data_received) > 0:
            data_received_lines = data_received.split('\r\n')

            for line in data_received_lines:
                if len(line) > 0:
                    if line.startswith("E_"):
                        device_header, message = line.split('_')
                        message = 'A' + message
                        print("[FROM ARDUINO TO EDU-CIAA] {}".format(message))
                        edu_ciaa_port.write(message.encode())
                    else:
                        print("[FROM ARDUINO TO PC] {}".format(line))

        time.sleep(0.1)


def main():
    # close serial port if it is opened, and the open it
    if edu_ciaa_port.isOpen():
        edu_ciaa_port.close()
    edu_ciaa_port.open()
    print("Serial connection with EDU-CIAA opened. \n")

    if arduino_port.isOpen():
        arduino_port.close()
    arduino_port.open()
    print("Serial connection with ARDUINO opened. \n")

    arduino_port.flush()
    edu_ciaa_port.flush()

    # create and start thread to read the EDU-CIAA and ARDUINO serial ports
    thread_read_edu_ciaa = threading.Thread(target=read_edu_ciaa_port, args=())
    thread_read_arduino = threading.Thread(target=read_arduino_port, args=())

    # stop the threads once the main program finishes
    thread_read_edu_ciaa.setDaemon(True)
    thread_read_arduino.setDaemon(True)

    thread_read_edu_ciaa.start()
    thread_read_arduino.start()

    while True:
        try:
            data_to_send = input("")
            if data_to_send == "exit":
                print("Closing program.")
                break
            try:
                device_header, message = data_to_send.split('_')
            except:
                print("Invalid command format. Must be A_[number] or E_[number].")
                continue
            
            if device_header == 'A':
                print("[FROM PC TO ARDUINO] {}".format(message))
                arduino_port.write(message.encode())
            elif device_header == 'E':
                message = device_header + message
                print("[FROM PC TO EDU_CIAA] {}".format(message))
                edu_ciaa_port.write(message.encode())

        except KeyboardInterrupt:
            print("User pressed ctrl+c to terminate the program.")
            edu_ciaa_port.close()
            arduino_port.close()

    edu_ciaa_port.close()
    arduino_port.close()


if __name__ == "__main__":
    main()
