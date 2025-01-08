# IO(WS)T

This is an IoT device that senses droplets from water tap leakage and informs communicates that through Wi-fi. This was developed pre Covid-19 lockdowns. The water sensing part was very hard to figure out. I tried multiple sensor like force sensors, vibration sensors and flex sensors but none of them were ssensitive enough to detect water droplets. After much brainstorming I planned to use ADXL335 accelerometer sensor aas I remember reading a paper in which it was used to detect pulse froma jugular vein of a person. Henci I stuck a flexible clear plastic sheet to the accelerometer and made my own high sensitive flex sensor. It worked like a dream.

The programs developed use thread based programming to make it more efficient and fast. It is overkill for such a small project but it just felt right. I have attached the 2 programs which are two versions of the same code.

The hardware used are as follows:
1. R5F100LEA - This is a 64 pin, 16-bit microcontroller from Renesas. This was chosen as I had a development kit of it lying around from a previous project.
2. ADXL335 - This is a 3-axis accelerometer. It was chosen due to its high accuracy and low-power operation.
3. Air602 Wi-fi module - This is a low cost wi-fi module.
4. 555 timer IC - Its a timer IC used for timing.
Other than these components some wires and connectors are necessary.

The photo uploaded below showcase the connections (Sorry for the shabiness. I did this project when I didn't know any better).

![WhatsApp Image 2025-01-04 at 09 32 17](https://github.com/user-attachments/assets/3bebcbfe-10c2-4f2d-ae78-2583cc33de1b)

This project was developed for a competition whose final round was about to be held during the March of 2020 (Talk about timing).
