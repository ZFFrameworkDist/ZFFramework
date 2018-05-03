/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
/**
 * @file ZFPropertyType_CoreType.h
 * @brief type define for #ZFPROPERTY_TYPE_DECLARE
 */

#ifndef _ZFI_ZFPropertyType_CoreType_h_
#define _ZFI_ZFPropertyType_CoreType_h_

#include "ZFPropertyType_spec.h"
#include "ZFFilterForZFClass.h"
#include "ZFFilterForZFObject.h"
#include "ZFFilterForZFMethod.h"
#include "ZFFilterForZFProperty.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// string conversion spec
/** @cond ZFPrivateDoc */
inline zfbool zfstringToString(ZF_IN_OUT zfstring &s,
                               ZF_IN const zfchar *v)
{
    s += v;
    return zftrue;
}
inline zfstring zfstringToString(ZF_IN const zfchar *v)
{
    return zfstring(v);
}
inline zfbool zfstringFromString(ZF_OUT const zfchar *&v,
                                 ZF_IN const zfchar *src,
                                 ZF_IN_OPT zfindex srcLen = zfindexMax())
{
    if(srcLen != zfindexMax() && src[srcLen] != '\0')
    {
        return zffalse;
    }
    v = src;
    return zftrue;
}
/** @endcond */

/**
 * @brief see #zfstringFromData, designed for performance
 *
 * returned (const zfchar *) propertyValue is the pointer to serializableData's value,
 * you should ensure it's alive while using the propertyValue
 */
extern ZF_ENV_EXPORT zfbool zfstringFromData(ZF_OUT const zfchar * &propertyValue,
                                             ZF_IN const ZFSerializableData &serializableData,
                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                             ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
/**
 * @brief see #zfstringToData, designed for performance
 */
extern ZF_ENV_EXPORT zfbool zfstringToData(ZF_OUT ZFSerializableData &serializableData,
                                           ZF_IN const zfchar * const &propertyValue,
                                           ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */);

/**
 * @brief convert flags to string using flagList and nameList
 *
 * result would be like "Flag0|Flag1|0x123ABC"\n
 * if flags is 0 and there's no 0 value in flagList, or error occurred, "0x0" would be returned
 * params:
 * -  includeNotConverted
 *   if true, values not recognized would be appended to result as HEX value
 * -  exclusiveMode if true, when a flag recognized,
 *   flags would be unset and can't be recognized any more\n
 *   for example, if we have two flag 0101 and 0011 in flagList which shares 0001 bit,
 *   then if we are converting 0111, since 0101 would be recognized first
 *   and leave 0010, 0011 won't be recognized any more
 * -  notConverted if all value recognized, notConverted would be set to 0,
 *   otherwise, the not converted value would be set
 */
extern ZF_ENV_EXPORT zfbool zfflagsToString(ZF_IN_OUT zfstring &ret,
                                            ZF_IN const zfflags *flagList,
                                            ZF_IN const zfchar **nameList,
                                            ZF_IN zfindex listCount,
                                            ZF_IN zfflags const &value,
                                            ZF_IN_OPT zfbool includeNotConverted = zftrue,
                                            ZF_IN_OPT zfbool exclusiveMode = zffalse,
                                            ZF_OUT_OPT zfflags *notConverted = zfnull,
                                            ZF_IN_OPT zfchar separatorToken = '|');
/** @brief see #zfflagsToString */
inline zfstring zfflagsToString(ZF_IN const zfflags *flagList,
                                ZF_IN const zfchar **nameList,
                                ZF_IN zfindex listCount,
                                ZF_IN zfflags const &value,
                                ZF_IN_OPT zfbool includeNotConverted = zftrue,
                                ZF_IN_OPT zfbool exclusiveMode = zffalse,
                                ZF_OUT_OPT zfflags *notConverted = zfnull,
                                ZF_IN_OPT zfchar separatorToken = '|')
{
    zfstring ret;
    zfflagsToString(ret, flagList, nameList, listCount, value, includeNotConverted, exclusiveMode, notConverted, separatorToken);
    return ret;
}

/**
 * @brief convert string to zfflags
 *
 * params:
 * -  pErrPos pointer to first char where error occurred,
 *   a non converted format is not regarded as error
 */
extern ZF_ENV_EXPORT zfbool zfflagsFromString(ZF_OUT zfflags &ret,
                                              ZF_IN const zfflags *flagList,
                                              ZF_IN const zfchar **nameList,
                                              ZF_IN zfindex listCount,
                                              ZF_IN const zfchar *src,
                                              ZF_IN_OPT zfindex srcLen = zfindexMax(),
                                              ZF_IN_OPT zfchar separatorToken = '|',
                                              ZF_OUT_OPT const zfchar **outErrorPos = zfnull);

// ============================================================
// property type
/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfbool value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zfbool, zfbool)
ZFOUTPUT_TYPE(zfbool, {output.execute(v ? ZFTOKEN_zfbool_zftrue : ZFTOKEN_zfbool_zffalse);})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfbyte value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zfbyte, zfbyte)
ZFOUTPUT_TYPE(zfbyte, {output.execute(zfbyteToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfchar value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zfchar, zfchar)
ZFOUTPUT_TYPE(zfchar, {output.execute(zfcharToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfstring value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zfstring, zfstring)
ZFOUTPUT_TYPE(zfstring, {output.execute(zfstringToString(v));})

ZFPROPERTY_TYPE_ALIAS_DECLARE(zfstring, zfstring, cString, const zfchar *)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfint value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zfint, zfint)
ZFOUTPUT_TYPE(zfint, {output.execute(zfintToString(v));})
ZFPROPERTY_PROGRESS_DECLARE_BY_VALUE(zfint)
/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfuint value="value" />
 * @endcode
 * @note for portability of unsigned types,
 *   we'll use "-1" to store max unsigned value
 */
ZFPROPERTY_TYPE_DECLARE(zfuint, zfuint)
ZFOUTPUT_TYPE(zfuint, {output.execute(zfuintToString(v));})
ZFPROPERTY_PROGRESS_DECLARE_BY_VALUE(zfuint)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfindex value="value" />
 * @endcode
 * @note for portability of unsigned types,
 *   we'll use "-1" to store max unsigned value
 */
ZFPROPERTY_TYPE_DECLARE(zfindex, zfindex)
ZFOUTPUT_TYPE(zfindex, {output.execute(zfindexToString(v));})
ZFPROPERTY_PROGRESS_DECLARE_BY_VALUE(zfindex)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zffloat value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zffloat, zffloat)
ZFOUTPUT_TYPE(zffloat, {output.execute(zffloatToString(v));})
ZFPROPERTY_PROGRESS_DECLARE_BY_VALUE(zffloat)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfdouble value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zfdouble, zfdouble)
ZFOUTPUT_TYPE(zfdouble, {output.execute(zfdoubleToString(v));})
ZFPROPERTY_PROGRESS_DECLARE_BY_VALUE(zfdouble)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zflongdouble value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zflongdouble, zflongdouble)
ZFOUTPUT_TYPE(zflongdouble, {output.execute(zflongdoubleToString(v));})
ZFPROPERTY_PROGRESS_DECLARE_BY_VALUE(zflongdouble)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zftimet value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zftimet, zftimet)
ZFOUTPUT_TYPE(zftimet, {output.execute(zftimetToString(v));})
ZFPROPERTY_PROGRESS_DECLARE_BY_VALUE(zftimet)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfflags value="value" />
 * @endcode
 * @note for portability of unsigned types,
 *   we'll use "-1" to store max unsigned value
 */
ZFPROPERTY_TYPE_DECLARE(zfflags, zfflags)
ZFOUTPUT_TYPE(zfflags, {output.execute(zfflagsToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfidentity value="value" />
 * @endcode
 * @note for portability of unsigned types,
 *   we'll use "-1" to store max unsigned value
 */
ZFPROPERTY_TYPE_DECLARE(zfidentity, zfidentity)
ZFOUTPUT_TYPE(zfidentity, {output.execute(zfidentityToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFCompareResult value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFCompareResult, ZFCompareResult)
ZFOUTPUT_TYPE(ZFCompareResult, {output.execute(ZFCompareResultToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFSeekPos value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFSeekPos, ZFSeekPos)
ZFOUTPUT_TYPE(ZFSeekPos, {output.execute(ZFSeekPosToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <zfindexRange
 *       value="(0, 0)" // optional, 0 by default
 *   />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(zfindexRange, zfindexRange)
ZFOUTPUT_TYPE(zfindexRange, {output.execute(zfindexRangeToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFLevel value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFLevel, ZFLevel)
ZFOUTPUT_TYPE(ZFLevel, {output.execute(ZFLevelToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFFrameworkState value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFFrameworkState, ZFFrameworkState)
ZFOUTPUT_TYPE(ZFFrameworkState, {output.execute(ZFFrameworkStateToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFFilterType value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFFilterType, ZFFilterType)
ZFOUTPUT_TYPE(ZFFilterType, {output.execute(ZFFilterTypeToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFFilterCallbackResult value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFFilterCallbackResult, ZFFilterCallbackResult)
ZFOUTPUT_TYPE(ZFFilterCallbackResult, {output.execute(ZFFilterCallbackResultToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFPathInfo value="pathType|pathData" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFPathInfo, ZFPathInfo)
ZFOUTPUT_TYPE(ZFPathInfo, {output.execute(ZFPathInfoToString(v));})
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFPathInfo_separator zfText("|")

/**
 * @brief util method to parse path info for performance
 */
extern ZF_ENV_EXPORT zfbool ZFPathInfoParse(ZF_IN const zfchar *pathInfo,
                                            ZF_OUT zfstring &pathType,
                                            ZF_OUT const zfchar *&pathData);

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFTokenForContainer // all tokens are optional
 *       tokenLeft=""
 *       tokenRight=""
 *       tokenSeparator=""
 *       tokenValueLeft=""
 *       tokenValueRight=""
 *       tokenEtc=""
 *   />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFTokenForContainer, ZFTokenForContainer)
ZFOUTPUT_TYPE(ZFTokenForContainer, {output.execute(ZFTokenForContainerToString(v));})
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForContainer_tokenLeft zfText("tokenLeft")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForContainer_tokenRight zfText("tokenRight")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForContainer_tokenSeparator zfText("tokenSeparator")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForContainer_tokenValueLeft zfText("tokenValueLeft")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForContainer_tokenValueRight zfText("tokenValueRight")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForContainer_tokenEtc zfText("tokenEtc")

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFTokenForKeyValueContainer // all tokens are optional
 *       tokenLeft=""
 *       tokenRight=""
 *       tokenSeparator=""
 *       tokenPairLeft=""
 *       tokenPairRight=""
 *       tokenPairSeparator=""
 *       tokenKeyLeft=""
 *       tokenKeyRight=""
 *       tokenValueLeft=""
 *       tokenValueRight=""
 *       tokenEtc=""
 *   />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainer)
ZFOUTPUT_TYPE(ZFTokenForKeyValueContainer, {output.execute(ZFTokenForKeyValueContainerToString(v));})
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenLeft zfText("tokenLeft")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenRight zfText("tokenRight")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenSeparator zfText("tokenSeparator")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairLeft zfText("tokenPairLeft")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairRight zfText("tokenPairRight")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairSeparator zfText("tokenPairSeparator")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenKeyLeft zfText("tokenKeyLeft")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenKeyRight zfText("tokenKeyRight")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenValueLeft zfText("tokenValueLeft")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenValueRight zfText("tokenValueRight")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenEtc zfText("tokenEtc")

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFFilterForZFClassType value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFFilterForZFClassType, ZFFilterForZFClassType)
ZFOUTPUT_TYPE(ZFFilterForZFClassType, {output.execute(ZFFilterForZFClassTypeToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFMethodPrivilegeType value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFMethodPrivilegeType, ZFMethodPrivilegeType)
ZFOUTPUT_TYPE(ZFMethodPrivilegeType, {output.execute(ZFMethodPrivilegeTypeToString(v));})

ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFComparer_ZFObject, ZFComparer<ZFObject *>::Comparer)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFObjectInstanceState value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFObjectInstanceState, ZFObjectInstanceState)
ZFOUTPUT_TYPE(ZFObjectInstanceState, {output.execute(ZFObjectInstanceStateToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFCallbackType value="value" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFCallbackType, ZFCallbackType)
ZFOUTPUT_TYPE(ZFCallbackType, {output.execute(ZFCallbackTypeToString(v));})

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFSerializableData />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFSerializableData, ZFSerializableData)
ZFOUTPUT_TYPE_DECLARE(ZFSerializableData)

// ============================================================
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFuncAddrType, ZFFuncAddrType)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(zfiterator, zfiterator)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFBuffer, ZFBuffer)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFilterForNumber, ZFFilterForNumber)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFilterForIndex, ZFFilterForIndex)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFilterForIdentity, ZFFilterForIdentity)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFilterForString, ZFFilterForString)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFIdentityGenerator, ZFIdentityGenerator)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFListenerData, ZFListenerData)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFObserverAddParam, ZFObserverAddParam)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFObserverHolder, ZFObserverHolder)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFilterForZFClass, ZFFilterForZFClass)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFilterForZFMethod, ZFFilterForZFMethod)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFilterForZFProperty, ZFFilterForZFProperty)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFFilterForZFObject, ZFFilterForZFObject)
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFMethodGenericInvoker, ZFMethodGenericInvoker)

// ============================================================
// void *
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(VoidPointer, void *)
ZFPROPERTY_TYPE_ALIAS_DECLARE(VoidPointer, void *, VoidPointerConst, const void *)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFPropertyType_CoreType_h_

