Sistema operativo maqueta "RageOs"

El objetivo de este proyecto es construir un modelo a escala del funcionamiento real de un sistema operativo.

Para lograr esto, se partirá de un diseño similar a Minix en arquitectura, tratando de hacer que cada una de las partes sea lo más simple posible para cumplir su tarea de la mínima forma posible.

Desde ya, no se contempla hacer una maqueta completamente precisa ni tampoco que sea eficiente o clara en su cometido. Se trata de un proyecto de investigación personal que tiene poco en común con los sistemas operativos reales.

Como se mencionó anteriormente, se partirá desde una arquitectura similar a la propuesta en el sistema operativo Minix, en la cual el kernel es la pieza central encargada de comunicarse con los demás módulos.

Cada uno de estos módulos se concibió como un sistema de servicios que se pueden levantar y bajar acorde a las necesidades del sistema.  Cada uno de ellos opera de forma totalmente independiente a los otros, siendo capaces de comunicarse entre sí únicamente usando mensajes a través del kernel. Dichos mensajes pueden ser tanto de lectura como de escritura, es decir que pueden efectuarse consultas sobre el estado de cada uno de los módulos, así como enviarse órdenes para realizar cambios en los mismos.

Al tomar un esquema de cliente-servidor, se presupone que estos módulos-servicios al ser desplegados se quedan a la espera de que el kernel les envíe mensajes que estos contestarán usando el mismo medio.

Cuando el kernel recibe llamadas del sistema, es éste quien se encarga de enviar los mensajes correspondientes a cada uno de los módulos, lo cual hará cada vez que lo considere oportuno acorde a su planificación.

Es muy importante considerar que el objetivo de este enfoque es favorecer el mantenimiento de cada uno de los módulos de forma independiente, de modo que si se efectuan cambios en uno de ellos, estos no afectan en mayor medida a los demás módulos. Para poder lograr esto es muy importante que la comunicación de los mensajes funcione correctamente y, que todos los mensajes se emitan siguiendo un único estándar, de modo tal que no sea difícil redirigir la comunicación a un tercero.

Observaciones:

- Para la implementación de el kernel es probable que un enfoque de programación orientada a objetos sea la opción más lógica, por lo que es menester asegurarse que la comunicación con los módulos no será un problema.
- Respecto a la comunicación entre los módulos utilizando mensajes, existen dos alternativas: crear un "módulo de comunicación", dependiente pura y exclusivamente del kernel a modo de "cartelera", en donde se encarga de publicar los mensajes vigentes y, cuando este lo considere necesario le indica a cada uno de los módulos que la lea para extraer o publicar la información que necesita. Por otro lado, se podría efectuar de una forma mucho más sencilla si se utiliza la salida estándar del sistema huesped, indicandole explícitamente a cada módulo que tiene que recibir un mensaje.
- Debido al enfoque de este proyecto, se decidió implementar multiproceso, pero no multihilo. Sin embargo, como el concepto de procesos e hilos existen únicamente en el kernel, para poder implementarlo bastaría con efectuar los cambios necesarios en este único.
