project(AvlTreeLib)

set(HEADER_FILES
        AvlTree.h
        Node.h)

set(SOURCE_FILES
        AvlTree.cpp
        Node.cpp)

add_library(AvlTreeLib STATIC ${SOURCE_FILES} ${HEADER_FILES})
