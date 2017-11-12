SET_MODULE("ClintLib")

ADD_DEFINITIONS(-DINITGUID)

INCLUDE_DIRECTORIES(../Inc ../zlib ../engine  ../soundengine ../guids ../Igc
                    ../lobby ../Lib/AllegianceSecurity ../_Utility ../Zone)

SET(ClintLib_SRC
    AutoDownload.cpp
    appmsg.cpp
    badwords.cpp
    clintlib.cpp
   )

ADD_LIBRARY(ClintLib ${ClintLib_SRC})
SET_PROPERTY(TARGET ClintLib PROPERTY CXX_STANDARD 14)
