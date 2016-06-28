DESCRIPTION = "qt vsd test program"

LICENSE = "Welch"
SECTION = "spot"
LIC_FILES_CHKSUM = "file://License;md5=58284206eac1d806d3a275ecb64ba9fc"

PR = "r5"

# Inherit from qt4e to setup the QT build environment but we will then 
# override a number of the environment settings for compiling with Arxan
# later on in the recipe.
inherit qt4e

SRC_URI = " \
    file://License \
    file://johns-play.pro \
    file://main.cpp \
    file://mainwindow.cpp \
    file://mainwindow.h \
    file://mainwindow.ui \
"

S = "${WORKDIR}"

TOUCH_CMD="/usr/bin/touch"

###############################################################################
# Arxan conversion
#
# The default do_compile phase is altered below to only produce compiled
# output by modifying the environment variables that are used by the
# standard compilation functions. The clang compiler is a C/C++ front end
# for input into the back end LLVM compiler that is used to produce an 
# optimized intermediate form object file. This is the format that is
# required by the Arxan compiler which is used to apply guards to the 
# software and ouput bitcode files that can then be assembled and linked into
# a binary.
#
# To prevent Arxan binary mangling simply set the variable DISABLE_ARX to
# any value in the local.conf file and the standard cross compile and link
# will be done. This is to enable better debugging and to prevent anyone
# that doesn't have access to an Arxan license or license server from being
# inable to build the software and generate a release for testing. All final
# production builds will include Arxan binary mangling by default.
###############################################################################

DISABLE_ARX="1"

do_compile () {
    if [ -z ${DISABLE_ARX} ]; then
        export EIT_CXX="clang++"
        export TRIPLE="arm-none-linux-gnueabi"

        # Flags
        EIT_CXX_FLAGS="-march=armv7-a -mtune=cortex-a8 -mfpu=neon \
-mfloat-abi=softfp -fvisibility-inlines-hidden \
"

        #
        # Following flags turn off select warnings/errors resulting from the
        # presence of '-Wall' and '-Werror'. Pediavision should remove the following
        # flags and fix associated warnings/errors in product code.
        #
        EIT_CXX_FLAGS+="-Wno-uninitialized \
-Wno-overloaded-virtual \
-Wno-gnu \
-Wno-unused-private-field \
-Wno-unused-value \
-Wno-format-security \
-Wno-return-type \
"

        # Defines
        EIT_COMMON_DEFS="-DQT_QWS_CLIENTBLIT \
-DQT_NO_DEBUG -DQT_PHONON_LIB -DQT_DBUS_LIB \
-DQT_SQL_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB \
-DQT_CORE_LIB -DQT_SHARED -DARXAN \
"

        EIT_DEFS="-Dxdc_target_types__=gnu/targets/arm/std.h \
-Dxdc_target_name__=GCArmv5T \
-DVSD_REVNUM=99999999 -DVSD_VERSION=\"0.0.0\" \
-DVSD_PRODUCT=\"vs100\" -DVSD_TARGET_PLATFORM=\"vs100\" \
-DUSE_CORE -DCODEC_ENGINE_READY -DVSD_DEBUG=1 -DVSD_VS100 \
-DUSE_QT_DISPLAY -DNO_EXAM_SYS_SOUND -DMALLOC_CHECK_=1 \
-D_REENTRANT ${EIT_COMMON_DEFS} \
"

        # Disable assert()'s with this next line.
        # EIT_DEFS+="-DNDEBUG \
        #   -DTRACE_BATTERY_STATE \
        # "

        # Includes
        EIT_INCLUDES="-I${STAGING_LIBDIR_NATIVE}/clang/3.5.0/include \
-I/${STAGING_DIR_TARGET}/usr/include/vsd \
-I${STAGING_DIR_TARGET}/usr/share/qtopia/mkspecs/linux-g++ \
-I. \
-I${STAGING_DIR_TARGET}/usr/include/qtopia/QtCore \
-I${STAGING_DIR_TARGET}/usr/include/qtopia/QtNetwork \
-I${STAGING_DIR_TARGET}/usr/include/qtopia/QtGui \
-I${STAGING_DIR_TARGET}/usr/include/qtopia/QtSql \
-I${STAGING_DIR_TARGET}/usr/include/qtopia/QtDBus \
-I${STAGING_DIR_TARGET}/usr/include/qtopia/phonon \
-I${STAGING_DIR_TARGET}/usr/include/qtopia \
-Iinc \
-Ixml \
-I.objs \
-I${STAGING_DIR_TARGET}/usr/include \
-I${STAGING_DIR_TARGET}/usr/include/c++ \
-I${STAGING_DIR_TARGET}/usr/include/c++/arm-poky-linux-gnueabi \
"

        # compiler flags
        EIT_FLAGS="-O2 -emit-llvm ${EIT_CXX_FLAGS} ${EIT_INCLUDES} \
${EIT_DEFS} -target ${TRIPLE} -c -pipe \
"
        # for verbose ouput add the following flag
        # EIT_FLAGS+="-v \
        # "
        

        OE_QMAKE_CFLAGS=""
        OE_QMAKE_CXXFLAGS="${EIT_FLAGS}"

        # Compiler setup
        # We want to use the clang compiler to generate LLVM object code 
        # but not link. Just clear any variables that may cause us to 
        # compile or link with the our stand host cross compile tools.
        BUILD_CC=""
        BUILD_CXX=""
        CC=""
        CXX=""
        LD=""
        AR=""
        CCACHE=""
        BUILD_LDFLAGS=""
        OE_QMAKE_LDFLAGS=""
        OE_QMAKE_LINK=""
        OE_QMAKE_CFLAGS=""
        OE_QMAKE_LDFLAGS=""
        OE_QMAKE_AR=""
        OE_QMAKE_RPATH=""

        # Now override the compiler with what we've setup to output
        # LLVM object files only.
        OE_QMAKE_CC="${EIT_CXX}"
        OE_QMAKE_CXX="${EIT_CXX}"
    else
        OE_QMAKE_CFLAGS+=" \
-I${STAGING_DIR_TARGET}/${includedir} \
-I${STAGING_DIR_TARGET}/usr/include/vsd \
"
    fi
echo "calling base_do_compile"
pwd
    base_do_compile
}

# addtask do_vdsgui_link after do_compile before do_install

do_install () {
    install -d ${D}/opt/vsd
    install -d ${D}/opt/vsd/lang
    install -m 0755 ${S}/johns-play ${D}/opt/vsd
}

FILES_${PN} = "/opt/vsd/vsdgui \
               /opt/vsd/lang/vsdgui_*.qm \
               /opt/vsd/lang/*.ttf \
               /opt/vsd/*.db"

INSANE_SKIP_vsdgui += "dev-deps"
