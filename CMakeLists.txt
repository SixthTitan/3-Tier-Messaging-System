cmake_minimum_required(VERSION 3.12)
project(Project2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Project2 Application.c BroadcastReceiver.c BroadcastSender.c MulticastSender.c headers/DieWithError.h headers/clear.h MulticastReciever.c headers/SystemLogger.h)