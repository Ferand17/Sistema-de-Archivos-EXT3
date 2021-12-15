QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        comando_exec.cpp \
        comando_fdisk.cpp \
        comando_mkdisk.cpp \
        comando_mount.cpp \
        comando_rep.cpp \
        comando_rmdisk.cpp \
        comando_unmount.cpp \
        f2_archivo.cpp \
        f2_cat.cpp \
        f2_chgrp.cpp \
        f2_chmod.cpp \
        f2_chown.cpp \
        f2_disco.cpp \
        f2_edit.cpp \
        f2_find.cpp \
        f2_login.cpp \
        f2_mkdir.cpp \
        f2_mkfile.cpp \
        f2_mkfs.cpp \
        f2_mkgrp_rmgrp.cpp \
        f2_mkusr.cpp \
        f2_rem.cpp \
        f2_ren.cpp \
        f2_rmusr.cpp \
        graficar_ast.cpp \
        lista_particiones.cpp \
        main.cpp \
        nodo_arbol.cpp \
        nodo_particiones.cpp \
        obtener_comandos.cpp \
        parser.cpp \
        scanner.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sintactico.y \
    lexico.l

HEADERS += \
    comando_exec.h \
    comando_fdisk.h \
    comando_mkdisk.h \
    comando_mount.h \
    comando_rep.h \
    comando_rmdisk.h \
    comando_unmount.h \
    estructuras.h \
    estructuras_fase2.h \
    f2_archivo.h \
    f2_cat.h \
    f2_chgrp.h \
    f2_chmod.h \
    f2_chown.h \
    f2_disco.h \
    f2_edit.h \
    f2_find.h \
    f2_login.h \
    f2_mkdir.h \
    f2_mkfile.h \
    f2_mkfs.h \
    f2_mkgrp_rmgrp.h \
    f2_mkusr.h \
    f2_rem.h \
    f2_ren.h \
    f2_rmusr.h \
    graficar_ast.h \
    lista_particiones.h \
    nodo_arbol.h \
    nodo_particiones.h \
    obtener_comandos.h \
    parser.h \
    scanner.h

