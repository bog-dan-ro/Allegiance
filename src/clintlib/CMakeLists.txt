ADD_DEFINITIONS(-D__MODULE__="ClintLib")

INCLUDE_DIRECTORIES(../Inc ../zlib ../engine  ../soundengine ../guids ../Igc ../lobby)

SET(ClintLib_SRC
    clintlib.cpp
   )

ADD_LIBRARY(ClintLib ${ClintLib_SRC})
