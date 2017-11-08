SET_MODULE("ClintLib")

INCLUDE_DIRECTORIES(../Inc ../zlib ../engine  ../soundengine ../guids ../Igc
                    ../lobby ../Lib/AllegianceSecurity ../_Utility ../Zone)

SET(ClintLib_SRC
    AutoDownload.cpp
    appmsg.cpp
    badwords.cpp
    clintlib.cpp
   )

ADD_LIBRARY(ClintLib ${ClintLib_SRC})
