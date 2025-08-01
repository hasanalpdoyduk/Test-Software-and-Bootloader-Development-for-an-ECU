import sys
import time
import serial
import serial.tools.list_ports
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel,
    QSlider, QSpinBox, QComboBox, QPushButton, QTextEdit
)
from PyQt5.QtCore import Qt


class PWMSender(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PWM UART Controller + Bootloader Trigger")
        self.setGeometry(200, 200, 500, 400)

        self.serial = None

        self.layout = QVBoxLayout()

        # Serial Port
        port_layout = QHBoxLayout()
        self.port_combo = QComboBox()
        self.refresh_ports()
        self.connect_button = QPushButton("Connect")
        self.connect_button.clicked.connect(self.connect_serial)
        self.status_label = QLabel("Not connected")
        port_layout.addWidget(QLabel("Port:"))
        port_layout.addWidget(self.port_combo)
        port_layout.addWidget(self.connect_button)
        port_layout.addWidget(self.status_label)
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
        self.freq_slider.setRange(310, 9000)
        self.freq_spin = QSpinBox()
        self.freq_spin.setRange(310, 9000)
        self.freq_slider.valueChanged.connect(self.freq_spin.setValue)
        self.freq_spin.valueChanged.connect(self.freq_slider.setValue)
        freq_layout.addWidget(QLabel("Frequency (Hz)"))
        freq_layout.addWidget(self.freq_slider)
        freq_layout.addWidget(self.freq_spin)
        self.layout.addLayout(freq_layout)

        # Buttons
        self.send_button = QPushButton("Send PWM")
        self.send_button.clicked.connect(self.send_uart_data)
        self.boot_button = QPushButton("Enter Bootloader")
        self.boot_button.clicked.connect(self.trigger_bootloader)
        self.layout.addWidget(self.send_button)
        self.layout.addWidget(self.boot_button)

        # Terminal
        self.terminal = QTextEdit()
        self.terminal.setReadOnly(True)
        self.layout.addWidget(QLabel("Terminal Output:"))
        self.layout.addWidget(self.terminal)

        self.setLayout(self.layout)

    def refresh_ports(self):
        ports = serial.tools.list_ports.comports()
        self.port_combo.clear()
        for port in ports:
            self.port_combo.addItem(port.device)

    def connect_serial(self):
        try:
            self.serial = serial.Serial(self.port_combo.currentText(), 9600, timeout=1)
            self.status_label.setText("Connected")
            self.terminal.append(f"[INFO] Connected to {self.serial.port}")
        except Exception as e:
            self.status_label.setText("Error")
            self.terminal.append(f"[ERROR] Connection failed: {str(e)}")

    def send_uart_data(self):
        if self.serial and self.serial.is_open:
            duty = f"{self.duty_spin.value():04d}D"
            freq = f"{self.freq_spin.value():04d}F"
            self.serial.write(duty.encode())
            time.sleep(0.05)
            self.serial.write(freq.encode())
            self.terminal.append(f"[SEND] {duty} + {freq}")
        else:
            self.terminal.append("[ERROR] Serial not connected.")

    def trigger_bootloader(self):
        if self.serial and self.serial.is_open:
            self.serial.write(b'b')
            self.terminal.append("[SEND] 'b' (trigger reset)")
            time.sleep(0.5)
            self.serial.write(b'b')
            self.terminal.append("[SEND] 'b' (enter bootloader)")
        else:
            self.terminal.append("[ERROR] Serial not connected.")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = PWMSender()
    window.show()
    sys.exit(app.exec_())
