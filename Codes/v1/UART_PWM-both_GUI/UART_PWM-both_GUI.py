import sys
import serial
import serial.tools.list_ports
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel,
    QSlider, QSpinBox, QComboBox, QPushButton
)
from PyQt5.QtCore import Qt


class PWMSender(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PWM UART Kontrol (8 Karakter Format)")
        self.setGeometry(200, 200, 400, 300)

        self.serial = None

        self.layout = QVBoxLayout()

        # Serial Port
        port_layout = QHBoxLayout()
        self.port_combo = QComboBox()
        self.refresh_ports()
        self.connect_button = QPushButton("Bağlan")
        self.connect_button.clicked.connect(self.connect_serial)
        port_layout.addWidget(QLabel("Port:"))
        port_layout.addWidget(self.port_combo)
        port_layout.addWidget(self.connect_button)
        self.layout.addLayout(port_layout)

        # Duty Cycle
        duty_layout = QHBoxLayout()
        self.duty_slider = QSlider(Qt.Horizontal)
        self.duty_slider.setRange(0, 100)
        self.duty_spin = QSpinBox()
        self.duty_spin.setRange(0, 100)
        self.duty_slider.valueChanged.connect(self.duty_spin.setValue)
        self.duty_spin.valueChanged.connect(self.duty_slider.setValue)
        duty_layout.addWidget(QLabel("Duty (%)"))
        duty_layout.addWidget(self.duty_slider)
        duty_layout.addWidget(self.duty_spin)
        self.layout.addLayout(duty_layout)

        # Frequency
        freq_layout = QHBoxLayout()
        self.freq_slider = QSlider(Qt.Horizontal)
        self.freq_slider.setRange(310, 9000)  #  Maksimum 9000 Hz
        self.freq_spin = QSpinBox()
        self.freq_spin.setRange(310, 9000)  #  Maksimum 9000 Hz
        self.freq_slider.valueChanged.connect(self.freq_spin.setValue)
        self.freq_spin.valueChanged.connect(self.freq_slider.setValue)
        freq_layout.addWidget(QLabel("Frekans (Hz)"))
        freq_layout.addWidget(self.freq_slider)
        freq_layout.addWidget(self.freq_spin)
        self.layout.addLayout(freq_layout)

        # GÖNDER BUTONU
        self.send_button = QPushButton("Gönder")
        self.send_button.clicked.connect(self.send_pwm_packet)
        self.layout.addWidget(self.send_button)

        self.setLayout(self.layout)

    def refresh_ports(self):
        self.port_combo.clear()
        ports = serial.tools.list_ports.comports()
        for port in ports:
            self.port_combo.addItem(port.device)

    def connect_serial(self):
        if self.serial and self.serial.is_open:
            self.serial.close()
            self.connect_button.setText("Bağlan")
            return
        try:
            port_name = self.port_combo.currentText()
            self.serial = serial.Serial(port_name, baudrate=9600, timeout=1)
            self.connect_button.setText("Bağlantı Kes")
        except Exception as e:
            print(f"Bağlantı hatası: {e}")

    def send_pwm_packet(self):
        if not self.serial or not self.serial.is_open:
            print("UART bağlı değil.")
            return

        duty = self.duty_slider.value()
        freq = self.freq_slider.value()

        duty_str = f"{duty:04d}"  # 4 karakter
        freq_str = f"{freq:04d}"  # 4 karakter
        message = duty_str + freq_str  # Toplam 8 karakter

        try:
            self.serial.write(message.encode())
            print(f"Gönderildi: {message}")
        except Exception as e:
            print(f"UART gönderme hatası: {e}")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = PWMSender()
    window.show()
    sys.exit(app.exec())
