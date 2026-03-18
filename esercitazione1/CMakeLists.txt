# In un file CMakeLists.txt si deve innanzitutto specificare la versione
# minima di CMake necessaria per compilare il progetto. Nel nostro caso
# specifichiamo 3.20
cmake_minimum_required(VERSION 3.20)

# Successivamente il file CMakeLists.txt deve specificare il nome del
# progetto software
project(esercitazione1) 

# In seguito dobbiamo specificare la versione di C++ che vogliamo
# sia usata per la compilazione. Utilizziamo C++20, ovvero la versione
# standardizzata nel 2020
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# A lezione abbiamo visto che possiamo specificare al compilatore delle
# opzioni per incrementare il livello di warning, in modo da avvisarci
# se nel programma vengono riscontrati dei costrutti potenzialmente
# problematici. Le opzioni devono essere aggiunte alla variabile di CMake
# chiamata CMAKE_CXX_FLAGS nel seguente modo
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")

# A questo punto siamo pronti a dichiarare l'eseguibile che vogliamo produrre.
# Con il comando add_executable chiediamo di creare un eseguibile chiamato
# passo1 a partire dal file sorgente passo2.cpp. In qualche modo questo genererà
# una chiamata al compilatore simile a quanto discusso a lezione
#    g++ -o passo2 passo2.cpp
add_executable(prova6es1eseg prova6es1.cpp)
add_executable(prova7es1eseg prova7es1.cpp)
#Il prossimo comando (preso da Claude) mi porta il file di input dentro la cartella build in cui produco gli eseguibili
configure_file(input_es1.txt ${CMAKE_BINARY_DIR}/input_es1.txt COPYONLY)

