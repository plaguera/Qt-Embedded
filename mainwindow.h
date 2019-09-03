#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemWatcher>
#include <QMainWindow>
#include "gpioclass.h"

namespace Ui {
class MainWindow;
}

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
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    // Slot de cada uno de los botones (Incluyendo los Físicos)
    void on_button_0_clicked();
    void on_button_1_clicked();
    void on_button_2_clicked();
    void on_button_3_clicked();
    void on_button_4_clicked();
    void on_button_5_clicked();
    void on_button_6_clicked();
    void on_button_7_clicked();
    void on_button_8_clicked();
    void on_button_9_clicked();
    void on_button_sum_clicked();
    void on_button_difference_clicked();
    void on_button_product_clicked();
    void on_button_division_clicked();
    void on_button_clear_tapped();
    void on_button_equals_tapped();
private:
    QFileSystemWatcher watcher_clear, watcher_equals;   // Vigilan que el valor de cada botón físico cambie
    Ui::MainWindow *ui;                                 // Diseño de la UI
    void append_symbol(char symbol);                    // Añadir un nuevo carácter al final del display
    void clear();                                       // Borrar todos los caracteres del display

    char get();                                         // Devuelve el carácter de la expresión que se está evaluando y avanza al siguiente
    char peek();                                        // Devuelve el carácter de la expresión que se está evaluando
    int number();                                       // Parte del Parser de expresiones Matemáticas: parsea números
    int factor();                                       // Parte del Parser de expresiones Matemáticas: parsea el signo '-' en números negativos
    int term();                                         // Parte del Parser de expresiones Matemáticas: parsea multiplicaciones y divisiones
    int expression();                                   // Parte del Parser de expresiones Matemáticas: parsea sumas y restas
    int parse_index;                                    // Indica el número del carácter de la expresión que se está evaluando
    bool error, showing_result;                         // Booleanos indican si se ha producido un error en el cálculo, y si se está mostrando un resultado

    GPIOClass *led_green;                               // PIN de la RaspberryPi correspondiente al LED Verde
    GPIOClass *led_red;                                 // PIN de la RaspberryPi correspondiente al LED Rojo
    GPIOClass *button_clear;                            // PIN de la RaspberryPi correspondiente al Botón que limpia el display
    GPIOClass *button_equals;                           // PIN de la RaspberryPi correspondiente al Botón que evalua la expresión y muestra el resultado
};

#endif // MAINWINDOW_H
