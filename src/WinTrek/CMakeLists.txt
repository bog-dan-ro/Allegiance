SET_MODULE("WinTrek")

ADD_DEFINITIONS(-DSTRSAFE_NO_DEPRECATE -DEnablePerformanceCounters
                -DNO_CLUB_SERVER_CONNECTION -DSTEAM_APP_ID=700480)

INCLUDE_DIRECTORIES(../Inc ../Igc ../engine ../effect ../zlib
                    ../soundengine ../guids ../Zone ../training
                    ../clintlib ../lobby ../_Utility ..)

SET(Allegiance_SRC
    CallsignTagInfo.cpp
    CharInfoScreen.cpp
    PostTrainingSlideshow.cpp
    Slideshow.cpp
    SquadsScreen.cpp
    SteamClans.cpp
    TrainingSlideshow.cpp
    WinTrek.cpp
    ZoneClubScreen.cpp
    ZoneSquad.cpp
    cdkeydialog.cpp
    chatpane.cpp
    cmdview.cpp
    console.cpp
    consoledata.cpp
    ddstream.cpp
    ddvideo.cpp
    gameoverscreen.cpp
    gamescreen.cpp
    gamestartingscreen.cpp
    gametypes.cpp
    hangarscreen.cpp
    indicator.cpp
    introscreen.cpp
    inventoryimage.cpp
    leaderboardscreen.cpp
    load.cpp
    loadout.cpp
    logon.cpp
    mappreview.cpp
    mappvmaker.cpp
    netinfo.cpp
    newgamescreen.cpp
    passworddialog.cpp
    radarimage.cpp
    sectormap.cpp
    selpane.cpp
    soundinit.cpp
    splashscreen.cpp
    teampane.cpp
    teamscreen.cpp
    teleportpane.cpp
    trainingscreen.cpp
    trekapp.cpp
    trekctrls.cpp
    trekigc.cpp
    trekinput.cpp
    trekmdl.cpp
    treksound.cpp
    videoscreen.cpp
    zoneeventsscreen.cpp
   )

SET(Allegiance_DEPS
    training
    Igc
    ClintLib
    Utility
    Engine
    effect
    SoundEngine
    Zlib
   )

IF(UNIX)
    SET(PLATFORM_LIBS)
ELSEIF(WIN32)
    SET(PLATFORM_LIBS ${CMAKE_SOURCE_DIR}/src/Lib/OggVorbis/file.lib
        ${CMAKE_SOURCE_DIR}/src/Lib/OggVorbis/vorbis.lib
        ${CMAKE_SOURCE_DIR}/src/Lib/OggVorbis/ogg.lib
        -lwininet -lwinmm -lstrmiids -ldxguid -ld3d9 -ld3dx9 -ldsound
        -ldinput8 -ldbghelp -lntdll -lversion
        )
ELSE()
    MESSAGE(FATAL_ERROR "Unhandled platform")
ENDIF()

IF (USE_STEAM)
    SET(PLATFORM_LIBS ${PLATFORM_LIBS} ${CMAKE_SOURCE_DIR}/src/Lib/steam/lib/win32/sdkencryptedappticket.lib)
ENDIF()

ADD_EXECUTABLE(Allegiance ${Allegiance_SRC})
TARGET_LINK_LIBRARIES(Allegiance ${Allegiance_DEPS} ${PLATFORM_LIBS})
SET_PROPERTY(TARGET Allegiance PROPERTY CXX_STANDARD 14)
