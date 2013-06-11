Compilar con:
  g++ GraphicPipeline/*.cpp GraphicPipeline/textParser/*.cpp -o app -std=c++0x

Modo de empleo:
  ./app <Ruta del archivo input> <Ruta del archivo output>

En main.cpp puede modificarse la posición/rotación del objeto y de la cámara, así como añadir más objetos para poder renderizarlos. También es posible pedir a la cámara que invierta las normales de los polígonos mediante el último argumento de su constructor.