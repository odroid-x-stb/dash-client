LOCAL_PATH := $(call my-dir)

common_SRC_FILES := \
	libxml/SAX.c \
	libxml/entities.c \
	libxml/encoding.c \
	libxml/error.c \
	libxml/parserInternals.c \
	libxml/parser.c \
	libxml/tree.c \
	libxml/hash.c \
	libxml/list.c \
	libxml/xmlIO.c \
	libxml/xmlmemory.c \
	libxml/uri.c \
	libxml/valid.c \
	libxml/xlink.c \
	libxml/HTMLparser.c \
	libxml/HTMLtree.c \
	libxml/debugXML.c \
	libxml/xpath.c \
	libxml/xpointer.c \
	libxml/xinclude.c \
	libxml/nanohttp.c \
	libxml/nanoftp.c \
	libxml/DOCBparser.c \
	libxml/catalog.c \
	libxml/globals.c \
	libxml/threads.c \
	libxml/c14n.c \
	libxml/xmlstring.c \
	libxml/xmlregexp.c \
	libxml/xmlschemas.c \
	libxml/xmlschemastypes.c \
	libxml/xmlunicode.c \
	libxml/xmlreader.c \
	libxml/relaxng.c \
	libxml/dict.c \
	libxml/SAX2.c \
	libxml/legacy.c \
	libxml/chvalid.c \
	libxml/pattern.c \
	libxml/xmlsave.c \
	libxml/xmlmodule.c \
	libxml/xmlwriter.c \
	libxml/schematron.c

common_C_INCLUDES += libxml/include/libxml
	
include $(CLEAR_VARS)
LOCAL_MODULE := libxml2

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_C_INCLUDES += $(common_C_INCLUDES) #libxml/external/icu4c/common
LOCAL_CFLAGS    := -I libxml/include
#LOCAL_SHARED_LIBRARIES += $(common_SHARED_LIBRARIES)
#LOCAL_CFLAGS += -fvisibility=hidden
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libdashjni

LOCAL_SRC_FILES := dash_manager.cpp
LOCAL_SRC_FILES += source/libdash.cpp
LOCAL_SRC_FILES += source/Helper.cpp
LOCAL_SRC_FILES += source/buffer/BlockBuffer.cpp
LOCAL_SRC_FILES += source/adaptationlogic/AbstractAdaptationLogic.cpp
LOCAL_SRC_FILES += source/adaptationlogic/AdaptationLogicFactory.cpp
LOCAL_SRC_FILES += source/adaptationlogic/AlwaysBestAdaptationLogic.cpp
LOCAL_SRC_FILES += source/adaptationlogic/RateBasedAdaptationLogic.cpp
LOCAL_SRC_FILES += source/http/Chunk.cpp
LOCAL_SRC_FILES += source/http/HTTPConnection.cpp
LOCAL_SRC_FILES += source/http/HTTPConnectionManager.cpp
LOCAL_SRC_FILES += source/http/PersistentHTTPConnection.cpp
LOCAL_SRC_FILES += source/manager/DASHManager.cpp
LOCAL_SRC_FILES += source/manager/DASHDownloader.cpp
LOCAL_SRC_FILES += source/mpd/AdaptationSet.cpp
LOCAL_SRC_FILES += source/mpd/BasicCMManager.cpp
LOCAL_SRC_FILES += source/mpd/BasicCMParser.cpp
LOCAL_SRC_FILES += source/mpd/Group.cpp
LOCAL_SRC_FILES += source/mpd/IsoffMainManager.cpp
LOCAL_SRC_FILES += source/mpd/IsoffMainParser.cpp
LOCAL_SRC_FILES += source/mpd/MPD.cpp
LOCAL_SRC_FILES += source/mpd/MPDManagerFactory.cpp
LOCAL_SRC_FILES += source/mpd/Period.cpp
LOCAL_SRC_FILES += source/mpd/Representation.cpp
LOCAL_SRC_FILES += source/mpd/SegmentBase.cpp
LOCAL_SRC_FILES += source/mpd/Segment.cpp
LOCAL_SRC_FILES += source/mpd/SegmentInfo.cpp
LOCAL_SRC_FILES += source/mpd/SegmentList.cpp
LOCAL_SRC_FILES += source/portable/MultiThreading.cpp
LOCAL_SRC_FILES += source/statistics/StatisticsManager.cpp
LOCAL_SRC_FILES += source/xml/DOMHelper.cpp
LOCAL_SRC_FILES += source/xml/DOMParser.cpp
LOCAL_SRC_FILES += source/xml/Node.cpp


LOCAL_CFLAGS    := -I libxml/include
LOCAL_C_INCLUDES += libxml/include/libxml #libxml/external/icu4c/common
LOCAL_STATIC_LIBRARIES := libxml2
include $(BUILD_SHARED_LIBRARY)
