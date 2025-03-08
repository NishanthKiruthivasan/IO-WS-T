# **IO(WS)T – Smart Water Leak Detection using IoT**  

## **🌊 Overview**  
IO(WS)T is an IoT-based device designed to detect and report water leakage from taps using **Wi-Fi communication**. This project was developed **before the COVID-19 lockdowns**, and the biggest challenge was identifying a highly **sensitive water droplet sensor**.  

After experimenting with **force, vibration, and flex sensors**—which all proved insufficient—I devised a unique approach. Inspired by a research paper on **jugular vein pulse detection**, I used an **ADXL335 accelerometer** with a **flexible plastic sheet**, effectively creating a **highly sensitive flex sensor**. This unconventional approach worked **flawlessly**.  

---

## **⚡ Technical Highlights**  
- **Multi-threaded programming** for improved efficiency and faster execution (admittedly overkill for this project, but it felt right!).  
- **Two versions of the program** are included in this repository.  
- **Non-traditional sensor approach** using an **accelerometer as a droplet detector**.  

---

## **🛠️ Hardware Components Used**  
1️⃣ **R5F100LEA** – A 64-pin, **16-bit Renesas microcontroller**, chosen because I had a **development kit** from a previous project.  
2️⃣ **ADXL335** – A **3-axis accelerometer**, selected for its **high accuracy** and **low-power operation**.  
3️⃣ **Air602 Wi-Fi module** – A **low-cost** and efficient **Wi-Fi communication module**.  
4️⃣ **555 Timer IC** – Used for **timing operations** in the circuit.  
5️⃣ **Miscellaneous components** – Wires, connectors, and other essential circuit elements.  

---

## **📸 Wiring & Setup**  
*(Apologies for the messy wiring—I built this project before I learned better wiring practices!)*  

![Circuit Image](https://github.com/user-attachments/assets/3bebcbfe-10c2-4f2d-ae78-2583cc33de1b)  

---

## **🏆 Competition & Constraints**  
This project was developed for a **competition** scheduled for **March 2020** (talk about unfortunate timing!).  
The competition imposed strict constraints:  
❌ **No Arduino, Raspberry Pi, TI boards, NodeMCU, or Arduino IDE.**  
✅ Components were chosen based on availability and rule compliance.  

---

## **🚀 Getting Started**  
To run the code on your setup:  
1. **Ensure all hardware connections** are properly made.  
2. Flash the **R5F100LEA microcontroller** with the provided program.  
3. Connect the **Wi-Fi module** to a network for communication.  
4. Run the **thread-based program** for optimal efficiency.  

---

## **📂 Repository Contents**  
- **Two versions of the program** (attached in the repository).  
- **Circuit images** for reference.  

---

## **📬 Feedback & Contributions**  
Feel free to **fork**, **modify**, and **contribute** to this project! If you have any questions, drop a comment or open an **issue**.  

🚀 *Happy Innovating!*  
