<h1>QMC5883L Sensor Library for STM32</h1>

<p>This repository contains a library for interfacing with the QMC5883L magnetometer sensor using STM32 microcontrollers. The library provides a straightforward API to read magnetic field data and compute azimuth and bearing from the sensor.</p>

<h2>Table of Contents</h2>
<ul>
    <li><a href="#introduction">Introduction</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
    <li><a href="#examples">Examples</a></li>
    <li><a href="#api-reference">API Reference</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
</ul>

<h2 id="introduction">Introduction</h2>
<p>The QMC5883L is a three-axis digital magnetometer that can measure the magnetic field in the X, Y, and Z axes. This library simplifies the process of interfacing with the QMC5883L sensor by providing functions to initialize the sensor and retrieve measurements.</p>

<h2 id="features">Features</h2>
<ul>
    <li>Easy-to-use API for reading magnetic field data.</li>
    <li>Supports I2C communication with STM32.</li>
    <li>Functions to calculate azimuth and bearing based on the magnetic field data.</li>
</ul>

<h2 id="getting-started">Getting Started</h2>

<h3 id="prerequisites">Prerequisites</h3>
<ul>
    <li>STM32 microcontroller (e.g., STM32F4 series).</li>
    <li>STM32 HAL library.</li>
    <li>QMC5883L sensor module.</li>
    <li>I2C support on your STM32.</li>
</ul>

<h3 id="installation">Installation</h3>
<ol>
    <li>Clone this repository:
        <pre><code>git clone https://github.com/SoorajR-ai/STM32F411_QMC5883L.git</code></pre>
    </li>
    <li>Include the <code>qmc.c</code> and <code>qmc.h</code> files in your STM32 project.</li>
    <li>Ensure the I2C peripheral is properly configured in your STM32 project settings.</li>
</ol>

<h3 id="usage">Usage</h3>
<ol>
    <li>Initialize the HAL and configure the system clock in your <code>main.c</code>.</li>
    <li>Initialize the I2C peripheral and the QMC5883L sensor:
        <pre><code>uint8_t status = QMC_init(&hi2c1);</code></pre>
    </li>
    <li>Read the magnetic field data and compute azimuth and bearing in your main loop:
        <pre><code>while (1) {
    xyz data = QMC_readXYZ();        // Access data.x, data.y, data.z
    int azimuth = QMC_getAzimuth();  // 0 = North
    int bearing = QMC_getBearing();   // 0 = North, 15 = South-West
    HAL_Delay(100);
}</code></pre>
    </li>
</ol>

<h2 id="examples">Examples</h2>
<p>Here's a simple example of how to use the library in your <code>main.c</code> file:</p>
<pre><code>#include "main.h"
#include "../QMC5883L/qmc.h"

I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    uint8_t status = QMC_init(&hi2c1);

    while (1)
    {
        xyz data = QMC_readXYZ();
        int azimuth = QMC_getAzimuth();
        int bearing = QMC_getBearing();
        HAL_Delay(100);
    }
}

// Remaining configuration and initialization code...
</code></pre>

<h2 id="api-reference">API Reference</h2>

<h3>uint8_t QMC_init(I2C_HandleTypeDef *hi2c_device)</h3>
<p>Initializes the QMC5883L sensor. Returns <code>1</code> if successful, <code>0</code> otherwise.</p>

<h3>xyz QMC_readXYZ()</h3>
<p>Reads and returns the magnetic field data in X, Y, and Z axes.</p>

<h3>int16_t QMC_getAzimuth()</h3>
<p>Calculates and returns the azimuth in degrees (0 = North).</p>

<h3>uint8_t QMC_getBearing()</h3>
<p>Calculates and returns the bearing as an index (0-15) representing the compass direction.</p>

<table border="1" cellpadding="5" cellspacing="0">
    <thead>
        <tr>
            <th>Segment</th>
            <th>Bearing Value</th>
            <th>Direction</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>0</td>
            <td>0°</td>
            <td>North</td>
        </tr>
        <tr>
            <td>1</td>
            <td>22.5°</td>
            <td>North-East</td>
        </tr>
        <tr>
            <td>2</td>
            <td>45°</td>
            <td>East</td>
        </tr>
        <tr>
            <td>3</td>
            <td>67.5°</td>
            <td>South-East</td>
        </tr>
        <tr>
            <td>4</td>
            <td>90°</td>
            <td>South</td>
        </tr>
        <tr>
            <td>5</td>
            <td>112.5°</td>
            <td>South-West</td>
        </tr>
        <tr>
            <td>6</td>
            <td>135°</td>
            <td>West</td>
        </tr>
        <tr>
            <td>7</td>
            <td>157.5°</td>
            <td>North-West</td>
        </tr>
        <tr>
            <td>8</td>
            <td>180°</td>
            <td>South</td>
        </tr>
        <tr>
            <td>9</td>
            <td>202.5°</td>
            <td>South-East</td>
        </tr>
        <tr>
            <td>10</td>
            <td>225°</td>
            <td>East</td>
        </tr>
        <tr>
            <td>11</td>
            <td>247.5°</td>
            <td>North-East</td>
        </tr>
        <tr>
            <td>12</td>
            <td>270°</td>
            <td>North</td>
        </tr>
        <tr>
            <td>13</td>
            <td>292.5°</td>
            <td>North-West</td>
        </tr>
        <tr>
            <td>14</td>
            <td>315°</td>
            <td>West</td>
        </tr>
        <tr>
            <td>15</td>
            <td>337.5°</td>
            <td>South-West</td>
        </tr>
    </tbody>
</table>


<h2 id="contributing">Contributing</h2>
<p>Contributions are welcome! If you have improvements, bug fixes, or new features, please submit a pull request.</p>

<h2 id="license">License</h2>
<p>This project is licensed under the MIT License.</p>
