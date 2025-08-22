#Version minimum autorisée de CMake
cmake_minimum_required(VERSION 2.8)

#NOM du projet
project(Puissance_4)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

#Lien/chemin pour retrouver mon projet
link_directories(${CMAKE_SOURCE_DIR})
#Commande permettant d'ajouter les fonctionnalités de test
enable_testing()

#Création de l'éxécutable principal+tests
add_executable(puissance_4 puissance_4.c)
add_executable(test_game_puissance_4 game_test_puissance_4.c)

#Création d'une librairie
add_library(puiss game_puissance_4.c)

# Besoin nécessaire au bon fonctionnement des exécutables
target_link_libraries(test_game_puissance_4 puiss m)

#Ajout des tests...