#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showing_result = false;
    error = false;

    // Inicializar el objeto de cada PIN
    led_green = new GPIOClass("27");
    led_red = new GPIOClass("22");
    button_clear = new GPIOClass("23");
    button_equals = new GPIOClass("24");

    // Exportar cada PIN
    led_green->export_gpio();
    led_red->export_gpio();
    button_clear->export_gpio();
    button_equals->export_gpio();

    // Establecer cada PIN como entrada o salida
    led_green->setdir_gpio("out");
    led_red->setdir_gpio("out");
    button_clear->setdir_gpio("in");
    button_equals->setdir_gpio("in");

    // Crear Watchers para monitorizar si los botones han sido pulsados
    watcher_clear.addPath(QString::fromStdString("/sys/class/gpio/gpio" + button_clear->get_gpionum() + "/value"));
    QObject::connect(&watcher_clear, SIGNAL(fileChanged(QString)), this, SLOT(on_button_clear_tapped));
    watcher_equals.addPath(QString::fromStdString("/sys/class/gpio/gpio" + button_equals->get_gpionum() + "/value"));
    QObject::connect(&watcher_equals, SIGNAL(fileChanged(QString)), this, SLOT(on_button_equals_tapped));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Añadir un nuevo carácter al final del display
 * @brief MainWindow::append_symbol
 * @param symbol
 */
void MainWindow::append_symbol(char symbol)
{
    if (showing_result)
        clear();
    string text;
    text = ui->result->text().toUtf8().constData() + string(1, symbol);
    ui->result->setText(QString::fromStdString(text));
}

/**
 * Devuelve el carácter de la expresión que se está evaluando y avanza al siguiente
 * @brief MainWindow::get
 * @return
 */
char MainWindow::get()
{
    return ui->result->text().toUtf8().constData()[parse_index++];
}

/**
 * Devuelve el carácter de la expresión que se está evaluando
 * @brief MainWindow::peek
 * @return
 */
char MainWindow::peek()
{
    return ui->result->text().toUtf8().constData()[parse_index];
}

/**
 * Parte del Parser de expresiones Matemáticas: parsea números
 * @brief MainWindow::number
 * @return
 */
int MainWindow::number()
{
    int result = get() - '0';
    while (peek() >= '0' && peek() <= '9')
    {
        result = 10*result + get() - '0';
    }
    return result;
}

/**
 * Parte del Parser de expresiones Matemáticas: parsea el signo '-' en números negativos
 * @brief MainWindow::factor
 * @return
 */
int MainWindow::factor()
{
    if (peek() >= '0' && peek() <= '9')
        return number();
    else if (peek() == '-')
    {
        get();
        return -factor();
    }
    error = true;
    return 0; // error
}

/**
 * Parte del Parser de expresiones Matemáticas: parsea multiplicaciones y divisiones
 * @brief MainWindow::term
 * @return
 */
int MainWindow::term()
{
    int result = factor();
    while (peek() == '*' || peek() == '/')
        if (get() == '*')
            result *= factor();
        else {
            int aux = factor();
            if (aux != 0)
                result /= aux;
            else
                error = true;
        }
    return result;
}

/**
 * Parte del Parser de expresiones Matemáticas: parsea sumas y restas
 * @brief MainWindow::expression
 * @return
 */
int MainWindow::expression()
{
    int result = term();
    while (peek() == '+' || peek() == '-')
        if (get() == '+')
            result += term();
        else
            result -= term();
    return result;
}

/**
 * Borrar todos los caracteres del display
 * @brief MainWindow::clear
 */
void MainWindow::clear()
{
    showing_result = false;
    error = false;
    ui->result->setText(QString::fromStdString(""));
    led_green->setval_gpio("0");
    led_red->setval_gpio("0");
}

/**
 * Slot para el botón '='
 * @brief MainWindow::on_button_equals_tapped
 */
void MainWindow::on_button_equals_tapped()
{
    parse_index = 0;
    ui->result->setText(QString::fromStdString(error ? "ERROR" : std::string(ui->result->text().toUtf8().constData()) + " = " + std::to_string(expression())));
    if (!error)
        led_green->setval_gpio("1");
    else
        led_red->setval_gpio("1");
    showing_result = true;
}

/**
 * Slot para el botón 'CLEAR'
 * @brief MainWindow::on_button_clear_tapped
 */
void MainWindow::on_button_clear_tapped()
{
    clear();
}

/**
 * Slot para el botón '0'
 * @brief MainWindow::on_button_0_clicked
 */
void MainWindow::on_button_0_clicked()
{
    append_symbol('0');
}

/**
 * Slot para el botón '1'
 * @brief MainWindow::on_button_1_clicked
 */
void MainWindow::on_button_1_clicked()
{
    append_symbol('1');
}

/**
 * Slot para el botón '2'
 * @brief MainWindow::on_button_2_clicked
 */
void MainWindow::on_button_2_clicked()
{
    append_symbol('2');
}

/**
 * Slot para el botón '3'
 * @brief MainWindow::on_button_3_clicked
 */
void MainWindow::on_button_3_clicked()
{
    append_symbol('3');
}

/**
 * Slot para el botón '4'
 * @brief MainWindow::on_button_4_clicked
 */
void MainWindow::on_button_4_clicked()
{
    append_symbol('4');
}

/**
 * Slot para el botón '5'
 * @brief MainWindow::on_button_5_clicked
 */
void MainWindow::on_button_5_clicked()
{
    append_symbol('5');
}

/**
 * Slot para el botón '6'
 * @brief MainWindow::on_button_6_clicked
 */
void MainWindow::on_button_6_clicked()
{
    append_symbol('6');
}

/**
 * Slot para el botón '7'
 * @brief MainWindow::on_button_7_clicked
 */
void MainWindow::on_button_7_clicked()
{
    append_symbol('7');
}

/**
 * Slot para el botón '8'
 * @brief MainWindow::on_button_8_clicked
 */
void MainWindow::on_button_8_clicked()
{
    append_symbol('8');
}

/**
 * Slot para el botón '9'
 * @brief MainWindow::on_button_9_clicked
 */
void MainWindow::on_button_9_clicked()
{
    append_symbol('9');
}

/**
 * Slot para el botón '+'
 * @brief MainWindow::on_button_sum_clicked
 */
void MainWindow::on_button_sum_clicked()
{
    append_symbol('+');
}

/**
 * Slot para el botón '-'
 * @brief MainWindow::on_button_difference_clicked
 */
void MainWindow::on_button_difference_clicked()
{
    append_symbol('-');
}

/**
 * Slot para el botón '*'
 * @brief MainWindow::on_button_product_clicked
 */
void MainWindow::on_button_product_clicked()
{
    append_symbol('*');
}

/**
 * Slot para el botón '/'
 * @brief MainWindow::on_button_division_clicked
 */
void MainWindow::on_button_division_clicked()
{
    append_symbol('/');
}
