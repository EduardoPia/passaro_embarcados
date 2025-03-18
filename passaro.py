import serial
import time

# Configuração da porta serial
porta = "COM6"  # Altere se necessário
baudrate = 115200

try:
    # Abre a conexão serial
    
    ser = serial.Serial(porta, baudrate, timeout=1)
    time.sleep(2)  # Aguarda estabilização da conexão

    print(f"Conectado à {porta} com baud rate {baudrate}")

    # Envia um comando para o ESP32
    ser.write(b"Hello ESP32!\n")

    # Aguarda e lê a resposta do ESP32
    while True:
        if ser.in_waiting > 0:  # Se há dados disponíveis
            resposta = ser.readline().decode().strip()
            print(f"ESP32: {resposta}")

except serial.SerialException as e:
    print(f"Erro ao abrir a porta serial: {e}")

except KeyboardInterrupt:
    print("\nEncerrando comunicação.")

finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Conexão serial fechada.")
