SET_MODULE("Utility")

INCLUDE_DIRECTORIES(../Inc ../zlib ../guids ../Igc)

SET(Utility_SRC
    CRC.cpp
    CollisionEntry.cpp
    CollisionQueue.cpp
    Endpoint.cpp
    HitTest.cpp
    KDnode.cpp
    KDroot.cpp
    Messages.cpp
    Utility.cpp
   )

ADD_LIBRARY(Utility ${Utility_SRC})

TARGET_LINK_LIBRARIES(Utility ${Utility_DEPS})
SET_PROPERTY(TARGET Utility PROPERTY CXX_STANDARD 14)
