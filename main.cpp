#include "mainwindow.h"
#include <QApplication>

/**
 * @author Pedro Lagüera Cabrera
 * @email alu0100891485@ull.edu.es
 * Universidad de La Laguna - Máster en Ingeniería Informártica
 * Sistemas Operativos y Sistemas Empotrados
 * Práctica Final
 *
 * Este programa simula una calculadora cuyos botones para los números
 * y las operaciones son botones en pantalla táctil, mientras que
 * los botones '=' y 'CLEAR' son dos botones físicos en la RaspberryPi.
 * El dispositivo también tiene dos LEDs, uno verde y otro rojo, el verde
 * se enciende al pulsar '=' y se muestra el resultado correcto, el rojo
 * se enciende al pulsar '=' y se encuentra un error, como dividir por 0.
 * Se puede cambiar fácilmente en qué pin del dispositivo se encuentra cada LED
 * y cada botón, los pines por defecto son:
 * - LED Verde              - 27
 * - LED Rojo               - 22
 * - Botón '='              - 24
 * - Botón 'Verde'CLEAR'    - 23
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
