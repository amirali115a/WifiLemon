import serial
import time
from serial.tools import list_ports
from colorama import Fore
print(Fore.GREEN,"""

  _                               
 | |    ___ _ __ ___   ___  _ __  
 | |   / _ \ '_ ` _ \ / _ \| '_ \ 
 | |__|  __/ | | | | | (_) | | | |
 |_____\___|_| |_| |_|\___/|_| |_|
                                  

""", Fore.WHITE)
def list_serial_ports():
   
    ports = list_ports.comports()
    if not ports:
        print("No serial ports found!")
        return []
    for i, port in enumerate(ports):
        print(f"{i + 1}: {port.device} - {port.description}")
    return ports

def serial_monitor(port, baudrate):
    try:
        print("Connect to WifiLemon ...")
        time.sleep(2)
        ser = serial.Serial(port, baudrate, timeout=1)
        print(f"Connected to WifiLemon")
        print("Press Ctrl+C to stop \n")
        
        while True:
            if ser.in_waiting > 0:
                data = ser.readline().decode('utf-8', errors='ignore').strip()
                if data:
                    print(f"Received: {data}")
            time.sleep(0.1)
    except serial.SerialException as e:
        print(f"Serial error: {e}")
    except KeyboardInterrupt:
        print("\nSerial monitor stopped.")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print(f"Closed connection to {port}.")

if __name__ == "__main__":

    print("Scanning for serial ports...")
    ports = list_serial_ports()
    
    if not ports:
        print("No serial ports available. Exiting.")
    else:
    
        port_index = int(input("\nSelect a port (enter the number): ")) - 1
        if 0 <= port_index < len(ports):
            selected_port = ports[port_index].device
            serial_monitor(selected_port, 115200)
        else:
            print("Invalid selection. Exiting.")
