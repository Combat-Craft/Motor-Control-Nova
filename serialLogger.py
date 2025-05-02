import serial
import csv
import time

# === CONFIGURATION ===
PORT = 'COM3'           # Change this to your Arduino's COM port
BAUDRATE = 9600         # Match your Serial.begin() in Arduino
CSV_FILENAME = 'motor_rpm_log.csv'

# === INITIALIZE SERIAL PORT ===
ser = serial.Serial(PORT, BAUDRATE, timeout=1)
time.sleep(2)  # Wait for Arduino to reset

print(f"Logging data from {PORT} to {CSV_FILENAME}... Press Ctrl+C to stop.")

# === OPEN CSV FILE FOR LOGGING ===
with open(CSV_FILENAME, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['PWM_Value', 'RPM'])  # header

    try:
        while True:
            line = ser.readline().decode().strip()
            if line:
                print(line)
                try:
                    pwm, rpm = line.split(',')
                    writer.writerow([int(pwm), float(rpm)])
                except ValueError:
                    print(f"Invalid line: {line}")
    except KeyboardInterrupt:
        print("\nLogging stopped by user.")
    finally:
        ser.close()
