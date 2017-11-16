SET_MODULE("Ui")

INCLUDE_DIRECTORIES(../zlib ../engine ../soundengine
                    ../Lib/lua/include ../Lib/sol/include
                    )

SET(ui_SRC
    UiEngine.cpp
    UiState.cpp
    )

ADD_LIBRARY(ui ${ui_SRC})
SET_PROPERTY(TARGET ui PROPERTY CXX_STANDARD 17)
