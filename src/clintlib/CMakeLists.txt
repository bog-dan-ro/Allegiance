ADD_DEFINITIONS(-D__MODULE__="ClintLib")

INCLUDE_DIRECTORIES(../Inc ../zlib ../engine  ../soundengine ../guids ../Igc ../lobby
                    ../Lib/steam ../Lib/AllegianceSecurity ../_Utility ../Zone)

SET(ClintLib_SRC
    AutoDownload.cpp
    clintlib.cpp
   )

ADD_LIBRARY(ClintLib ${ClintLib_SRC})
