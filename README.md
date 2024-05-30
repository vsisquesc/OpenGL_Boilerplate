# OpenGL_Boilerplate

Boilerplate for the development of OPENGL apps, includes GLFW, GLEW and IMGUI

Compila en una biblioteca estática que expone la clase APP, a esta clase se le pasan callbacks que renderizaran lo que se desee.

Este repo se debe utilizar como un submódulo.

Supongamos la siguiente estructura de ficheros

build
lib
src

Se debe acceder a lib y ejecutar
git submodule add https://github.com/vsisquesc/OpenGL_Boilerplate OpenGL_Boilerplate

Acto seguido se debe ejecutar
git submodule update --init --recursive

Para clonar los submódulos del boilerplate.

El fichero demo.cpp situado en src muestra un ejemplo del fichero main.cpp que debería situarse en src
