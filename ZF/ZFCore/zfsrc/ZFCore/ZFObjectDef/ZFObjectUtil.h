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
 * @file ZFObjectUtil.h
 * @brief utilities for ZFObject
 */

#ifndef _ZFI_ZFObjectUtil_h_
#define _ZFI_ZFObjectUtil_h_

#include "ZFObjectCore.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// to object
/**
 * @brief util method to convert to #ZFObject
 */
template<typename T_ZFObject>
inline ZFObject *ZFObjectToObject(ZF_IN T_ZFObject *obj)
{
    return (obj ? obj->toObject() : zfnull);
}

// ============================================================
// compare
/**
 * @brief util method to compare two ZFObject,
 *   return #ZFCompareTheSame if both null,
 *   return #ZFCompareUncomparable if one null but the other is not null,
 *   return compare result by #ZFObject::objectCompare if both not null
 */
template<typename T_ZFObject0, typename T_ZFObject1>
inline ZFCompareResult ZFObjectCompare(ZF_IN T_ZFObject0 * const &e0, ZF_IN T_ZFObject1 * const &e1)
{
    if(e0 == zfnull)
    {
        if(e1 == zfnull)
        {
            return ZFCompareTheSame;
        }
        else
        {
            return ZFCompareUncomparable;
        }
    }
    else
    {
        if(e1 == zfnull)
        {
            return ZFCompareUncomparable;
        }
        else
        {
            return e0->toObject()->objectCompare(e1->toObject());
        }
    }
}
/**
 * @brief default comparer for ZFObject types, compare by #ZFObjectCompare, see #ZFComparer
 */
#define ZFComparerForZFObject ZFObjectCompare

// ============================================================
/**
 * @brief util method to get info of object
 *   or return ZFTOKEN_zfnull if obj is null
 * @see ZFObject::objectInfoOfInstance
 */
inline void ZFObjectInfoOfInstanceT(ZF_IN_OUT zfstring &ret,
                                    ZF_IN ZFObject *obj)
{
    if(obj == zfnull)
    {
        ret += ZFTOKEN_zfnull;
    }
    else
    {
        obj->objectInfoOfInstanceT(ret);
    }
}
/**
 * @brief util method to get info of object
 *   or return ZFTOKEN_zfnull if obj is null
 * @see ZFObject::objectInfoOfInstance
 */
inline zfstring ZFObjectInfoOfInstance(ZF_IN ZFObject *obj)
{
    return ((obj == zfnull) ? zfstring(ZFTOKEN_zfnull) : obj->objectInfoOfInstance());
}
/**
 * @brief util method to get info of object
 *   or return ZFTOKEN_zfnull if obj is null
 * @see ZFObject::objectInfo
 */
inline void ZFObjectInfoT(ZF_IN_OUT zfstring &ret,
                          ZF_IN ZFObject *obj)
{
    if(obj == zfnull)
    {
        ret += ZFTOKEN_zfnull;
    }
    else
    {
        obj->objectInfoT(ret);
    }
}
/**
 * @brief util method to get info of object
 *   or return ZFTOKEN_zfnull if obj is null
 * @see ZFObject::objectInfo
 */
inline zfstring ZFObjectInfo(ZF_IN ZFObject *obj)
{
    return ((obj == zfnull) ? zfstring(ZFTOKEN_zfnull) : obj->objectInfo());
}

/**
 * @brief util method to calculate hash of object,
 *   or return #zfidentityInvalid if null
 */
inline zfidentity ZFObjectHash(ZF_IN ZFObject *obj)
{
    return ((obj == zfnull) ? zfidentityInvalid() : obj->objectHash());
}

// ============================================================
// ZFPointerHolder
/**
 * @brief used to hold a non ZFObject type for performance
 */
zffinal zfclass ZF_ENV_EXPORT ZFPointerHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE_WITH_CUSTOM_CTOR(ZFPointerHolder, ZFObject)

protected:
    ZFPointerHolder(void) : holdedData(zfnull) {}

protected:
    /**
     * @brief init with pointer
     */
    virtual void objectOnInit(ZF_IN const void *holdedData)
    {
        this->objectOnInit();
        this->holdedData = holdedData;
    }
    zfoverride
    virtual void objectOnInit(void)
    {
        zfsuper::objectOnInit();
    }

public:
    /**
     * @brief used to hold the raw pointer,
     *   you must ensure it's valid during the holder object's life cycle
     */
    const void *holdedData;

public:
    /** @brief util method to cast #holdedData */
    template<typename T_RawType>
    inline T_RawType holdedDataPointer(void)
    {
        return ZFCastStatic(T_RawType, this->holdedData);
    }
    /** @brief util method to cast #holdedData */
    template<typename T_RawType>
    inline T_RawType holdedDataRef(void)
    {
        typedef typename zftTraits<T_RawType>::TrConstPtr T_RawTypeConstPointer;
        return *ZFCastStatic(T_RawTypeConstPointer, this->holdedData);
    }

public:
    /**
     * @brief access cached object for performance
     *
     * should be paired with #cacheAdd
     */
    static ZFPointerHolder *cacheGet(void);
    /**
     * @brief release the cached object
     *
     * after calling this method, you must not access the obj any more by any chances
     */
    static void cacheAdd(ZF_IN ZFPointerHolder *obj);

protected:
    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);
public:
    zfoverride
    virtual zfidentity objectHash(void);
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);
};

// ============================================================
// ZFTypeHolder
zfclassFwd ZFTypeHolder;
/**
 * @brief type for #ZFTypeHolder
 *
 * to achieve #ZFTypeHolder, supply a function with following proto type,
 * which cleanup the internal #ZFTypeHolder::holdedData:
 * @code
 *   void type(ZF_IN ZFTypeHolder *holder);
 * @endcode
 */
typedef void (*ZFTypeHolderType)(ZF_IN ZFTypeHolder *holder);
/**
 * @brief used to hold a non ZFObject type for performance
 */
zffinal zfclass ZF_ENV_EXPORT ZFTypeHolder : zfextends ZFObject
{
    // ============================================================
public:
    ZFOBJECT_DECLARE_WITH_CUSTOM_CTOR(ZFTypeHolder, ZFObject)

protected:
    ZFTypeHolder(void) : holdedData(zfnull), holderType(zfnull) {}

protected:
    /**
     * @brief init with object
     */
    virtual void objectOnInit(ZF_IN void *holdedData,
                              ZF_IN ZFTypeHolderType holderType)
    {
        this->objectOnInit();
        this->holdedData = holdedData;
        this->holderType = holderType;
    }
    zfoverride
    virtual void objectOnInit(void)
    {
        zfsuper::objectOnInit();
    }
    zfoverride
    virtual void objectOnDeallocPrepare(void)
    {
        if(this->holdedData && this->holderType)
        {
            this->holderType(this);
        }
        this->holdedData = zfnull;
        this->holderType = zfnull;
        zfsuper::objectOnDeallocPrepare();
    }

public:
    /**
     * @brief used to hold the raw pointer
     *
     * you must ensure it's valid during the holder object's life cycle,
     * would be cleared by #holderType when the holder object deallocated
     */
    void *holdedData;
    /**
     * @brief delete callback to clear the #holdedData
     */
    ZFTypeHolderType holderType;

public:
    /** @brief util method to cast #holdedData */
    template<typename T_RawType>
    inline T_RawType holdedDataPointer(void)
    {
        return ZFCastStatic(T_RawType, this->holdedData);
    }
    /** @brief util method to cast #holdedData */
    template<typename T_RawType>
    inline T_RawType holdedDataRef(void)
    {
        typedef typename zftTraits<T_RawType>::TrPtr T_RawTypePointer;
        return *ZFCastStatic(T_RawTypePointer, this->holdedData);
    }

protected:
    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);
public:
    zfoverride
    virtual zfidentity objectHash(void);
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);
};
zfclassNotPOD _ZFP_ZFTypeHolderType
{
public:
    static void TypePointerRef(ZF_IN ZFTypeHolder *holder)
    {
    }
    static void TypePOD(ZF_IN ZFTypeHolder *holder)
    {
        zffree(holder->holdedData);
    }
    template<typename T_Object>
    static void TypeObject(ZF_IN ZFTypeHolder *holder)
    {
        zfdelete(ZFCastStatic(T_Object, holder->holdedData));
    }
};
/** @brief see #ZFTypeHolderType */
#define ZFTypeHolderTypePointerRef _ZFP_ZFTypeHolderType::TypePointerRef
/** @brief see #ZFTypeHolderType */
#define ZFTypeHolderTypePOD _ZFP_ZFTypeHolderType::TypePOD
/** @brief see #ZFTypeHolderType */
#define ZFTypeHolderTypeObject _ZFP_ZFTypeHolderType::TypeObject

// ============================================================
// special fix for ZFObject types
/** @cond ZFPrivateDoc */
template<typename T0, typename T1>
zfclassNotPOD ZFComparerDefaultHolder<T0, T1
    , void, void
    , typename zftEnableIf<zftIsZFObject(typename zftTraits<T0>::TrType)>::EnableIf
    , typename zftEnableIf<zftIsZFObject(typename zftTraits<T1>::TrType)>::EnableIf
    >
{
public:
    static ZFCompareResult comparer(ZF_IN T0 const &e0, ZF_IN T1 const &e1)
    {
        return ZFComparerForZFObject(e0, e1);
    }
};
/** @endcond */

/** @cond ZFPrivateDoc */
template<typename T_ZFObject>
zfclassNotPOD ZFCoreElementInfoGetter<T_ZFObject
        , typename zftEnableIf<zftIsZFObject(typename zftTraits<T_ZFObject>::TrType)>::EnableIf
    >
{
public:
    static void elementInfoGetter(ZF_IN_OUT zfstring &ret, ZF_IN T_ZFObject const &v)
    {
        ZFObjectInfoT(ret, ZFObjectToObject(v));
    }
};
/** @endcond */

// ============================================================
ZFCOMPARER_DEFAULT_DECLARE(zfautoObject, zfautoObject, {
        return ZFObjectCompare(v0.toObject(), v1.toObject());
    })

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFObjectUtil_h_

