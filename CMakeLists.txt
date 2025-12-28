cmake_minimum_required(VERSION 3.16)

project(PokemonSimulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui Multimedia Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets  Core Gui Multimedia Sql)

set(PROJECT_SOURCES



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PokemonSimulator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        entity/header/Ability.h entity/header/Field.h entity/header/Item.h entity/header/Move.h entity/header/Nature.h entity/header/Player.h entity/header/Pokemon.h entity/header/Type.h entity/source/Ability.cpp entity/source/Field.cpp entity/source/Item.cpp entity/source/Move.cpp entity/source/Nature.cpp entity/source/Player.cpp entity/source/Pokemon.cpp entity/source/Type.cpp obj/header/BattleButton.h obj/header/CharacterSprite.h obj/header/Display.h obj/header/MoveBattleButton.h obj/header/TextButton.h obj/header/TileSprite.h obj/source/BattleButton.cpp obj/source/CharacterSprite.cpp obj/source/Display.cpp obj/source/MoveBattleButton.cpp obj/source/SceneCreation.cpp obj/source/TextButton.cpp obj/source/TileSprite.cpp src/header/Game.h src/header/MainProcessor.h src/main/main.cpp src/source/Game.cpp src/source/MainProcessor.cpp util/header/Database.h util/header/Utility.h util/source/Database.cpp resources.qrc
        obj/source/HealthBar.cpp
        obj/header/HealthBar.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PokemonSimulator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PokemonSimulator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PokemonSimulator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PokemonSimulator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PokemonSimulator)
endif()
set_target_properties(PokemonSimulator PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PokemonSimulator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PokemonSimulator)
endif()
