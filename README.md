## ULL - Máster Ingeniería Informática - Sistemas Operativos y Sistemas Empotrados

### Pedro Lagüera Cabrera - alu0100891485@ull.edu.es

## [Proyecto](https://github.com/plaguera/Qt-Embedded)

Este programa simula una calculadora cuyos botones para los números y las operaciones son botones en pantalla táctil de la RaspberryPi, mientras que los botones `'='` y `'CLEAR'` son dos botones físicos en la RaspberryPi. El dispositivo también tiene dos LEDs, uno verde y otro rojo, el verde se enciende al pulsar `'='` y se muestra el resultado correcto, el rojo se enciende al pulsar `'='` y se encuentra un error, como dividir por 0. Se puede cambiar fácilmente en qué pin del dispositivo se encuentra cada LED y cada botón, los pines por defecto son:

 * **LED Verde**              - *27*
 * **LED Rojo**               - *22*
 * **Botón '='**              - *24*
 * **Botón 'Verde'CLEAR'**    - *23*

---

## Instalación

#### Abrir una terminal

##### Ir a `/home/usuario`:

> cd ~

##### Descargar Poky:

> git clone -b fido git://git.yoctoproject.org/poky.git

##### Ir a `/home/usuario/poky`:

> cd poky

##### Descargar Meta-RaspberryPi:

> git clone -b fido git://git.yoctoproject.org/meta-raspberrypi

##### Añadir `oe-init-build-env` al source de la sesión del terminal:

> source oe-init-build-env

##### Editar `local.conf`:

> vi conf/local.conf

##### Añadir:
```
MACHINE ?= "raspberrypi"
MACHINE ?= "qemuarm"
MACHINE ?= "qemux86"
```

##### Editar `bblayers.conf`:

> vi conf/bblayers.conf

##### Añadir:
```
BBLAYERS ?= " \
 /home/usuario/poky/meta \
 /home/usuario/poky/meta-yocto \
 /home/usuario/poky/meta-raspberrypi \
 "
```
##### Si queremos crear nuestra propia imagen, puedes usar hob para añadir dependencias:

> bitbake rpi-hwup-image

##### De lo contrario, podemos usar `qt4e-qemux86.ext3` disponible en el campus virtual. Para ejecutar la imagen:

> runqemu qemux86 /home/usuario/Downloads/qt4e-qemux86.ext3

---

#### Abrir una nueva terminal:

##### Descargar `poky-eglibc-x86_64-i586-toolchain-qte-1.4.4.sh` del campus virtual, añadir permisos de ejecución, ejecutarlo y extraerlo en `/home/usuario/toolchain_qte`. Ejecutar el siguiente comando:

> source /home/usuario/toolchain_qte/enviroment-setup-i586-poky-linux

##### Abrir QtCreator

> qtcreator

---

##### En QtCreator:

##### Ir a `Tools -> Options... -> Devices -> Add... -> Generic Linux Device`:

```
Name: RaspberryPi
IP Address: 192.168.7.2
User Name: root
Password:
```

##### Ir a `Tools -> Options... -> Build & Run -> Qt Versions -> Add...`:

```
Name: Qt 4.8.4 (Embedded)
Location: /home/usuario/toolchain_qte/sysroots/x86_64-pokysdk-linux/usr/bin/qmake2
```

##### Ir a `Tools -> Options... -> Build & Run -> Compilers -> Add... -> GCC`:

```
Name: GCC (Embedded)
Location: /home/usuario/toolchain_qte/sysroots/x86_64-pokysdk-linux/usr/bin/i586-poky-linux/i586-poky-linux-g++
```

##### Ir a `Tools -> Options... -> Build & Run -> Debuggers -> Add`:

```
Name: GDB (Embedded)
Location: /home/usuario/toolchain_qte/sysroots/x86_64-pokysdk-linux/usr/bin/i586-poky-linux/i586-poky-linux-gdb
```

##### Ir a `Tools -> Options... -> build & Run -> Kits -> Add`:

```
Name: RaspberryPi
Device Type: Generic Linux Device
Device: RaspberryPi
Sysroot: /home/usuario/toolchain_qte/sysroots/x86_64-pokysdk-linux
Compiler: GCC (Embedded)
Debugger: GDB (Embedded)
Qt Version: Qt 4.8.4 (Embedded)
```

##### Crear un proyecto usando `RaspberryPi`

##### Añadir argumentos de ejecución `-qws`

##### Abrir `Proyecto.pro` y añadir:
```
TARGET=Proyecto
target.files='archivos del proyecto'
target.path=/
INSTALLS+=target
```
---