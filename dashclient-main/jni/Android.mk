LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES += libunicode/cmemory.c
LOCAL_SRC_FILES += libunicode/cstring.c
LOCAL_SRC_FILES += libunicode/cwchar.c
LOCAL_SRC_FILES += libunicode/icudataver.c
LOCAL_SRC_FILES += libunicode/icuplug.c
LOCAL_SRC_FILES += libunicode/locmap.c
LOCAL_SRC_FILES += libunicode/propsvec.c
LOCAL_SRC_FILES += libunicode/uarrsort.c
LOCAL_SRC_FILES += libunicode/ubidi.c
LOCAL_SRC_FILES += libunicode/ubidiln.c
LOCAL_SRC_FILES += libunicode/ubidi_props.c
LOCAL_SRC_FILES += libunicode/ubidiwrt.c
LOCAL_SRC_FILES += libunicode/ucat.c
LOCAL_SRC_FILES += libunicode/uchar.c
LOCAL_SRC_FILES += libunicode/ucln_cmn.c
LOCAL_SRC_FILES += libunicode/ucmndata.c
LOCAL_SRC_FILES += libunicode/ucnv.c
LOCAL_SRC_FILES += libunicode/ucnv_cb.c
LOCAL_SRC_FILES += libunicode/ucnv_cnv.c
LOCAL_SRC_FILES += libunicode/ucnv_ct.c
LOCAL_SRC_FILES += libunicode/ucnvdisp.c
LOCAL_SRC_FILES += libunicode/ucnv_err.c
LOCAL_SRC_FILES += libunicode/ucnvhz.c
LOCAL_SRC_FILES += libunicode/ucnvisci.c
LOCAL_SRC_FILES += libunicode/ucnvlat1.c
LOCAL_SRC_FILES += libunicode/ucnv_lmb.c
LOCAL_SRC_FILES += libunicode/ucnvmbcs.c
LOCAL_SRC_FILES += libunicode/ucnvscsu.c
LOCAL_SRC_FILES += libunicode/ucnv_set.c
LOCAL_SRC_FILES += libunicode/ucnv_u16.c
LOCAL_SRC_FILES += libunicode/ucnv_u32.c
LOCAL_SRC_FILES += libunicode/ucnv_u7.c
LOCAL_SRC_FILES += libunicode/ucnv_u8.c
LOCAL_SRC_FILES += libunicode/udatamem.c
LOCAL_SRC_FILES += libunicode/udataswp.c
LOCAL_SRC_FILES += libunicode/uenum.c
LOCAL_SRC_FILES += libunicode/uhash.c
LOCAL_SRC_FILES += libunicode/uinit.c
LOCAL_SRC_FILES += libunicode/uinvchar.c
LOCAL_SRC_FILES += libunicode/ulist.c
LOCAL_SRC_FILES += libunicode/uloc_tag.c
LOCAL_SRC_FILES += libunicode/umapfile.c
LOCAL_SRC_FILES += libunicode/umath.c
LOCAL_SRC_FILES += libunicode/umutex.c
LOCAL_SRC_FILES += libunicode/unorm_it.c
LOCAL_SRC_FILES += libunicode/ures_cnv.c
LOCAL_SRC_FILES += libunicode/uresdata.c
LOCAL_SRC_FILES += libunicode/usc_impl.c
LOCAL_SRC_FILES += libunicode/uscript.c
LOCAL_SRC_FILES += libunicode/ustr_cnv.c
LOCAL_SRC_FILES += libunicode/ustrfmt.c
LOCAL_SRC_FILES += libunicode/utf_impl.c
LOCAL_SRC_FILES += libunicode/utrace.c
LOCAL_SRC_FILES += libunicode/utypes.c
LOCAL_SRC_FILES += libunicode/wintz.c
LOCAL_SRC_FILES += libunicode/appendable.cpp
LOCAL_SRC_FILES += libunicode/bmpset.cpp
LOCAL_SRC_FILES += libunicode/brkeng.cpp
LOCAL_SRC_FILES += libunicode/brkiter.cpp
LOCAL_SRC_FILES += libunicode/bytestream.cpp
LOCAL_SRC_FILES += libunicode/bytestriebuilder.cpp
LOCAL_SRC_FILES += libunicode/bytestrie.cpp
LOCAL_SRC_FILES += libunicode/bytestrieiterator.cpp
LOCAL_SRC_FILES += libunicode/caniter.cpp
LOCAL_SRC_FILES += libunicode/chariter.cpp
LOCAL_SRC_FILES += libunicode/charstr.cpp
LOCAL_SRC_FILES += libunicode/dictbe.cpp
LOCAL_SRC_FILES += libunicode/dtintrv.cpp
LOCAL_SRC_FILES += libunicode/errorcode.cpp
LOCAL_SRC_FILES += libunicode/filterednormalizer2.cpp
LOCAL_SRC_FILES += libunicode/locavailable.cpp
LOCAL_SRC_FILES += libunicode/locbased.cpp
LOCAL_SRC_FILES += libunicode/locdispnames.cpp
LOCAL_SRC_FILES += libunicode/locid.cpp
LOCAL_SRC_FILES += libunicode/loclikely.cpp
LOCAL_SRC_FILES += libunicode/locresdata.cpp
LOCAL_SRC_FILES += libunicode/locutil.cpp
LOCAL_SRC_FILES += libunicode/messagepattern.cpp
LOCAL_SRC_FILES += libunicode/mutex.cpp
LOCAL_SRC_FILES += libunicode/normalizer2.cpp
LOCAL_SRC_FILES += libunicode/normalizer2impl.cpp
LOCAL_SRC_FILES += libunicode/normlzr.cpp
LOCAL_SRC_FILES += libunicode/parsepos.cpp
LOCAL_SRC_FILES += libunicode/patternprops.cpp
LOCAL_SRC_FILES += libunicode/propname.cpp
LOCAL_SRC_FILES += libunicode/punycode.cpp
LOCAL_SRC_FILES += libunicode/putil.cpp
LOCAL_SRC_FILES += libunicode/rbbi.cpp
LOCAL_SRC_FILES += libunicode/rbbidata.cpp
LOCAL_SRC_FILES += libunicode/rbbinode.cpp
LOCAL_SRC_FILES += libunicode/rbbirb.cpp
LOCAL_SRC_FILES += libunicode/rbbiscan.cpp
LOCAL_SRC_FILES += libunicode/rbbisetb.cpp
LOCAL_SRC_FILES += libunicode/rbbistbl.cpp
LOCAL_SRC_FILES += libunicode/rbbitblb.cpp
LOCAL_SRC_FILES += libunicode/resbund_cnv.cpp
LOCAL_SRC_FILES += libunicode/resbund.cpp
LOCAL_SRC_FILES += libunicode/ruleiter.cpp
LOCAL_SRC_FILES += libunicode/schriter.cpp
LOCAL_SRC_FILES += libunicode/serv.cpp
LOCAL_SRC_FILES += libunicode/servlk.cpp
LOCAL_SRC_FILES += libunicode/servlkf.cpp
LOCAL_SRC_FILES += libunicode/servls.cpp
LOCAL_SRC_FILES += libunicode/servnotf.cpp
LOCAL_SRC_FILES += libunicode/servrbf.cpp
LOCAL_SRC_FILES += libunicode/servslkf.cpp
LOCAL_SRC_FILES += libunicode/stringpiece.cpp
LOCAL_SRC_FILES += libunicode/stringtriebuilder.cpp
LOCAL_SRC_FILES += libunicode/triedict.cpp
LOCAL_SRC_FILES += libunicode/ubrk.cpp
LOCAL_SRC_FILES += libunicode/ucase.cpp
LOCAL_SRC_FILES += libunicode/ucasemap.cpp
LOCAL_SRC_FILES += libunicode/ucasemap_titlecase_brkiter.cpp
LOCAL_SRC_FILES += libunicode/ucharstriebuilder.cpp
LOCAL_SRC_FILES += libunicode/ucharstrie.cpp
LOCAL_SRC_FILES += libunicode/ucharstrieiterator.cpp
LOCAL_SRC_FILES += libunicode/uchriter.cpp
LOCAL_SRC_FILES += libunicode/ucnv2022.cpp
LOCAL_SRC_FILES += libunicode/ucnv_bld.cpp
LOCAL_SRC_FILES += libunicode/ucnvbocu.cpp
LOCAL_SRC_FILES += libunicode/ucnv_ext.cpp
LOCAL_SRC_FILES += libunicode/ucnv_io.cpp
LOCAL_SRC_FILES += libunicode/ucnvsel.cpp
LOCAL_SRC_FILES += libunicode/ucol_swp.cpp
LOCAL_SRC_FILES += libunicode/udata.cpp
LOCAL_SRC_FILES += libunicode/uhash_us.cpp
LOCAL_SRC_FILES += libunicode/uidna.cpp
LOCAL_SRC_FILES += libunicode/uiter.cpp
LOCAL_SRC_FILES += libunicode/uloc.cpp
LOCAL_SRC_FILES += libunicode/unames.cpp
LOCAL_SRC_FILES += libunicode/unifilt.cpp
LOCAL_SRC_FILES += libunicode/unifunct.cpp
LOCAL_SRC_FILES += libunicode/uniset_closure.cpp
LOCAL_SRC_FILES += libunicode/uniset.cpp
LOCAL_SRC_FILES += libunicode/uniset_props.cpp
LOCAL_SRC_FILES += libunicode/unisetspan.cpp
LOCAL_SRC_FILES += libunicode/unistr_case.cpp
LOCAL_SRC_FILES += libunicode/unistr_case_locale.cpp
LOCAL_SRC_FILES += libunicode/unistr_cnv.cpp
LOCAL_SRC_FILES += libunicode/unistr.cpp
LOCAL_SRC_FILES += libunicode/unistr_props.cpp
LOCAL_SRC_FILES += libunicode/unistr_titlecase_brkiter.cpp
LOCAL_SRC_FILES += libunicode/unormcmp.cpp
LOCAL_SRC_FILES += libunicode/unorm.cpp
LOCAL_SRC_FILES += libunicode/uobject.cpp
LOCAL_SRC_FILES += libunicode/uprops.cpp
LOCAL_SRC_FILES += libunicode/uresbund.cpp
LOCAL_SRC_FILES += libunicode/uset.cpp
LOCAL_SRC_FILES += libunicode/usetiter.cpp
LOCAL_SRC_FILES += libunicode/uset_props.cpp
LOCAL_SRC_FILES += libunicode/ushape.cpp
LOCAL_SRC_FILES += libunicode/usprep.cpp
LOCAL_SRC_FILES += libunicode/ustack.cpp
LOCAL_SRC_FILES += libunicode/ustrcase.cpp
LOCAL_SRC_FILES += libunicode/ustrcase_locale.cpp
LOCAL_SRC_FILES += libunicode/ustrenum.cpp
LOCAL_SRC_FILES += libunicode/ustring.cpp
LOCAL_SRC_FILES += libunicode/ustr_titlecase_brkiter.cpp
LOCAL_SRC_FILES += libunicode/ustrtrns.cpp
LOCAL_SRC_FILES += libunicode/ustr_wcs.cpp
LOCAL_SRC_FILES += libunicode/utext.cpp
LOCAL_SRC_FILES += libunicode/util.cpp
LOCAL_SRC_FILES += libunicode/util_props.cpp
LOCAL_SRC_FILES += libunicode/utrie2_builder.cpp
LOCAL_SRC_FILES += libunicode/utrie2.cpp
LOCAL_SRC_FILES += libunicode/utrie.cpp
LOCAL_SRC_FILES += libunicode/uts46.cpp
LOCAL_SRC_FILES += libunicode/uvector.cpp
LOCAL_SRC_FILES += libunicode/uvectr32.cpp
LOCAL_SRC_FILES += libunicode/uvectr64.cpp
LOCAL_SRC_FILES += libunicode/stubdata.c

#c_includes := \
#	$(LOCAL_PATH) \
#	$(LOCAL_PATH)/../i18n

# We make the ICU data directory relative to $ANDROID_ROOT on Android, so both
# device and sim builds can use the same codepath, and it's hard to break one
# without noticing because the other still works.
#local_cflags := '-DICU_DATA_DIR_PREFIX_ENV_VAR="ANDROID_ROOT"'
#local_cflags += '-DICU_DATA_DIR="/usr/icu"'

# bionic doesn't have <langinfo.h>.
local_cflags += -DU_HAVE_NL_LANGINFO_CODESET=0
# bionic has timezone instead of __timezone.
local_cflags += -DU_TIMEZONE=timezone
local_cflags += -D_REENTRANT -DU_COMMON_IMPLEMENTATION
LOCAL_CFLAGS := $(local_cflags) -frtti -DPIC -fPIC
#local_cflags += -O3 -fvisibility=hidden

#local_ldlibs := -ldl -lm -lpthread
#LOCAL_RTTI_FLAG := -frtti
LOCAL_SHARED_LIBRARIES += libgabi++ libdl
#LOCAL_LDLIBS += $(local_ldlibs)
LOCAL_MODULE := libicuuc
LOCAL_C_INCLUDES += libunicode
include $(BUILD_STATIC_LIBRARY)


############################################################################################################



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

common_C_INCLUDES += libxml/include
	
include $(CLEAR_VARS)
LOCAL_MODULE := libxml2

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_C_INCLUDES += $(common_C_INCLUDES) #$(ANDROID_SOURCE_ROOT)/external/icu4c/common
LOCAL_SHARED_LIBRARIES += $(common_SHARED_LIBRARIES) 
LOCAL_STATIC_LIBRARIES := libicuuc
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


#LOCAL_CFLAGS    := -I libxml/include
LOCAL_C_INCLUDES += libxml/include #libxml/external/icu4c/common
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := libxml2
include $(BUILD_SHARED_LIBRARY)
