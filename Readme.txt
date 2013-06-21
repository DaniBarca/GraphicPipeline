Puedes usar este código o parte de él para lo que te de la gana cuando te de la gana con la única condición de que me des algún crédito con un enlace a este repositorio si publicas tu trabajo. ;)

Compilar con:
  g++ GraphicPipeline/*.cpp GraphicPipeline/textParser/*.cpp -o app -std=c++0x
  
En Mac puede que funcione mejor el siguiente comando:
  g++ GraphicPipeline/*.cpp GraphicPipeline/textParser/*.cpp -o app -std=c++98

Modo de empleo:
  ./app <Ruta del archivo input> <Ruta del archivo output>

En main.cpp puede modificarse la posición/rotación del objeto y de la cámara, así como añadir más objetos para poder renderizarlos. También es posible pedir a la cámara que invierta las normales de los polígonos mediante el último argumento de su constructor.

El formato de los archivos .txt es el siguiente:

<vertex number> <polygon number>
<vertex1 x> <vertex1 y> <vertex1 z>
<vertex2 x> <vertex2 y> <vertex2 z>
...
<vertexN x> <vertexN y> <vertexN z>
<number of vertexs at polygon 1> <vertex number 1> <vertex number 2> ... <vertex number N>
<number of vertexs at polygon 2> <vertex number 1> <vertex number 2> ... <vertex number N>
...
<number of vertexs at polygon N> <vertex number 1> <vertex number 2> ... <vertex number N>


Por ejemplo:
5 5
0 0 0
0 1 0
1 1 0
1 0 0
0.5 0.5 1
4 1 2 3 4
3 1 4 5
3 4 3 5
3 3 2 5
3 2 1 5

En el futuro tengo la intención de que lea formate ASE.
