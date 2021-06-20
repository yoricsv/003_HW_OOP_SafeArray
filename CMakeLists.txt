cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

    set (${PROJECT_NAME} HW-003_OOP_SafeArray)
project (HW-003_OOP_SafeArray LANGUAGES CXX)

    set (CMAKE_CXX_STANDARD          14)
    set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (${PROJECT_NAME}
         src/main.cpp        inc/main.h 
		 src/menu.cpp        inc/menu.h
		 src/safearray.cpp   inc/safearray.h 
)
