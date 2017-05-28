# <a href='http://www.BlackDolphin.csta.mx'><img src='http://www.csta.mx/ima/BlackDolphin_github_150.png' height='100'></a>

**BlackDolphin** es una herramienta que te permite personalizar las JumpList de Windows 7, 8, 8.1 y 10. 


**BlackDolphin** te permite editar el número de elementos de las Jumplist directamente y en todas las versiones de Windows.

**BlackDolphin** te permite personalizar su propio icono para tener uno representativo por cada Jumplist.

**BlackDolphin** te da control total sobre cada entrada de la Jumplist, puedes elegir el grupo al que pertenece, el título, el icono representativo, el path a ejecutar, los parámetros de ejecución, etc.

**BlackDolphin** te permite ejecutar una o más aplicaciones como acción directa al dar click sobre el botón en la barra de tareas, cada ejecución con parámetros personalizados e independientes de los de la ejecución por entrada de Jumplist, incluso puedes ejecutar entradas que no estén en la Jumplist, dándote la posibilidad de iniciar todo tu espacio de trabajo con un click.


## Inicio

En este apartado se explica cómo se puede obtener una compilación funcional de la aplicación para efecto de pruebas.

### Requisitos Previos

Esta aplicación está desarrollada en C++ con el IDE C++Builder XE7 y una librería propietaria y no publica de CSTA. Por ende, se requiere de la instalación de [C++Builder XE7](https://www.embarcadero.com/home) (o superior) en el equipo.

### Instalación

Identifique los archivos:

```.\[OUT]\BlackOcean_early.bpl```<br/>
```.\[OUT]\BlackOcean.bpl```<br/>
```.\[OUT]\BlackOcean_fmx.bpl```

Abra el IDE C++Builder.

Abra la opción del menú: ```Component > Install Packages...```

Ya en la ventana ```Install Packages``` presione el botón ```Add...``` y diríjase al archivo ```.\[OUT]\BlackOcean_early.bpl```

En la ventana ```Install Packages``` presione el botón ```Add...``` y diríjase al archivo ```.\[OUT]\BlackOcean.bpl```

En la ventana ```Install Packages``` presione el botón ```Add...``` y diríjase al archivo ```.\[OUT]\BlackOcean_fmx.bpl```

Presiona el botón ```ok```, y con esto habremos instalado los paquetes necesarios de CSTA.

Abra el archivo ```.\BlackPolp\BlackPolp.cbproj```

A disfrutar.


## Marcos de Trabajo Usados

* [Firemonkey](https://www.embarcadero.com/products/rad-studio/fm-application-platform) - Framework para el pintado de Shape's (formas), d2d.
* [BlackOcean](http://csta.mx) - Framework para el pintado de interfaces enriquecidas, animaciones y otras funciones.


## Autores

* Jesús E. Aldréte Hernández - CSTA


## License

Este proyecto está licenciado bajo la Licencia APACHE 2.0 - Véase el archivo [LICENSE](LICENSE) para más detalles.