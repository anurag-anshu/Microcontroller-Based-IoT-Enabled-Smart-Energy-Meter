# Microcontroller-Based-IoT-Enabled-Smart-Energy-Meter
🔍 Project Overview:

This project focuses on designing and implementing an IoT-enabled Smart Energy Meter using a NodeMCU (ESP8266) microcontroller and a PZEM-004T v3.0 sensor. The system is capable of real-time monitoring and analysis of electrical parameters such as voltage, current, power, energy consumption, frequency, and power factor.
The collected data is displayed locally on an I2C-based LCD and simultaneously transmitted to the ThingSpeak Cloud for remote monitoring and visualization.

⚙️ Key Features:

📊 Real-Time Monitoring – Measures and displays electrical parameters on an LCD screen.

🌐 IoT Integration – Sends live energy data to ThingSpeak for remote access and analytics.

⚡ Accurate Measurement – Uses PZEM-004T sensor for precise voltage, current, and power readings.

🔌 Microcontroller-Based Design – Powered by NodeMCU (ESP8266) for seamless cloud connectivity.

🧾 Compact & Cost-Effective – Designed as a low-cost, scalable solution for home or industrial energy monitoring.

🧩 Components Used

NodeMCU (ESP8266)

PZEM-004T v3.0 Sensor

I2C LCD Display (16x2)

Jumper Wires and Breadboard

USB Power Supply

🔌 Working Principle

The PZEM-004T sensor continuously measures voltage, current, power, and energy usage from the load.

The NodeMCU reads these values through serial communication.

The readings are displayed on a 16x2 I2C LCD for real-time local monitoring.

Simultaneously, the data is sent to ThingSpeak using Wi-Fi, where it is logged and visualized in charts and graphs.

📡 ThingSpeak Integration

The system uses the ThingSpeak API to upload data fields (Voltage, Current, Power, Energy, etc.) every few seconds.
This enables remote tracking of energy consumption trends and performance analysis from anywhere in the world.


