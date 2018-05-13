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
 * @file ZFIdMap.h
 * @brief id to string map util, useful to define extendable string enum
 */

#ifndef _ZFI_ZFIdMap_h_
#define _ZFI_ZFIdMap_h_

#include "../ZFCoreDef.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
extern ZF_ENV_EXPORT const zfidentity *_ZFP_ZFIdMapRegister(ZF_IN zfbool *ZFCoreLibDestroyFlag, ZF_IN const zfchar *idName);
extern ZF_ENV_EXPORT void _ZFP_ZFIdMapUnregister(ZF_IN zfbool *ZFCoreLibDestroyFlag, ZF_IN zfidentity idValue);
/**
 * @brief see #ZFIDMAP
 *
 * get id name from id value, or null if no such id
 * @note can be found only if accessed or registered by #ZFIDMAP_REGISTER
 */
extern ZF_ENV_EXPORT const zfchar *ZFIdMapGetName(ZF_IN const zfidentity &idValue);
/**
 * @brief see #ZFIDMAP
 *
 * get id value from id name, or #zfidentityInvalid if no such id name
 * @note can be found only if accessed or registered by #ZFIDMAP_REGISTER
 */
extern ZF_ENV_EXPORT zfidentity ZFIdMapGetId(ZF_IN const zfchar *idName);

/**
 * @brief see #ZFIDMAP
 *
 * get all registered id data, for debug use only
 * @note can be found only if accessed or registered by #ZFIDMAP_REGISTER
 */
extern ZF_ENV_EXPORT void ZFIdMapGetAll(ZF_OUT ZFCoreArrayPOD<zfidentity> &idValues, ZF_OUT ZFCoreArrayPOD<const zfchar *> &idNames);

zfclassLikePOD ZF_ENV_EXPORT _ZFP_ZFIdMapHolder
{
public:
    _ZFP_ZFIdMapHolder(ZF_IN const zfchar *idName);
    ~_ZFP_ZFIdMapHolder(void);

public:
    zfbool ZFCoreLibDestroyFlag;
    zfstring idName;
    const zfidentity *idValue;
};
/**
 * @brief declare an id within ZFObject class scope
 *
 * usage:
 * @code
 *   zfclass YourClass ...
 *   {
 *       ZFIDMAP(YourSth)
 *   };
 *
 *   // optional, in cpp files only, required only if you need ZFIdMapGetId/ZFIdMapGetName
 *   ZFIDMAP_REGISTER(YourClass, YourSth)
 * @endcode
 * declared id can be accessed by:
 * @code
 *   zfidentity idValue = YourClass::IdYourSth();
 *   const zfchar *idName = YourClass::IdYourSth_name();
 * @endcode
 * note that subclass may declare an id same as parent,
 * while the final id name is different:\n
 *   ParentClass::IdYourSth() => "ParentClass::IdYourSth"\n
 *   ChildClass::IdYourSth() => "ChildClass::IdYourSth"\n
 * \n
 * @note we declare the id as int types for performance,
 *   it's ensured each id has different value,
 *   but it's only ensured while app is running,
 *   after relaunching the app,
 *   the id value is not ensured the same,
 *   you should use the name of the id to store or pass between apps,
 *   and you can use #ZFIdMapGetId or #ZFIdMapGetName
 *   to convert them easily
 */
#define ZFIDMAP(YourIdName) \
    ZFIDMAP_DETAIL(Id, YourIdName)
/** @brief see #ZFIDMAP */
#define ZFIDMAP_DETAIL(prefix, YourIdName) \
    public: \
        /** \n */ \
        static zfidentity prefix##YourIdName(void) \
        { \
            return *(_ZFP_IM_##prefix##YourIdName().idValue); \
        } \
        /** @brief see @ref prefix##YourIdName */ \
        static const zfchar *prefix##YourIdName##_name(void) \
        { \
            return _ZFP_IM_##prefix##YourIdName().idName; \
        } \
        static _ZFP_ZFIdMapHolder &_ZFP_IM_##prefix##YourIdName(void) \
        { \
            static _ZFP_ZFIdMapHolder d( \
                    zfsConnectLineFree(zfself::ClassData()->className(), zfText("::"), ZFM_TOSTRING_DIRECT(prefix), ZFM_TOSTRING_DIRECT(YourIdName)) \
                ); \
            return d; \
        }

/**
 * @brief declare an id in global scope, see #ZFIDMAP
 *
 * usage:
 * @code
 *   // in header files
 *   ZF_NAMESPACE_BEGIN(YourNamespace)
 *   / ** @brief you can add doxygen docs here * /
 *   ZFIDMAP_GLOBAL(YourNamespace, YourSth)
 *   ZF_NAMESPACE_END(YourNamespace)
 *
 *   // optional, in cpp files only, required only if you need ZFIdMapGetId/ZFIdMapGetName
 *   ZFIDMAP_GLOBAL_REGISTER(YourNamespace, YourSth)
 *
 *   // use the id
 *   zfidentity idValue = YourNamespace::IdYourSth();
 * @endcode
 * unlike #ZFIDMAP, this macro would declare id outside of class scope
 */
#define ZFIDMAP_GLOBAL(YourNamespace, YourIdName) \
    ZFIDMAP_GLOBAL_DETAIL(YourNamespace, Id, YourIdName)
/** @brief see #ZFIDMAP_GLOBAL */
#define ZFIDMAP_GLOBAL_DETAIL(GlobalNamespace, prefix, YourIdName) \
    /** @cond ZFPrivateDoc */ \
    zfclass ZF_ENV_EXPORT _ZFP_ZFIdMapHolder_##GlobalNamespace##_##prefix##_##YourIdName \
    { \
    public: \
        static zfidentity idValue(void) \
        { \
            static _ZFP_ZFIdMapHolder d(idName()); \
            return *(d.idValue); \
        } \
        static const zfchar *idName(void) \
        { \
            return ZFM_TOSTRING_DIRECT(GlobalNamespace) zfText("::") ZFM_TOSTRING_DIRECT(prefix) ZFM_TOSTRING_DIRECT(YourIdName); \
        } \
    }; \
    /** @endcond */ \
    /** \n see #ZFIDMAP_GLOBAL */ \
    inline zfidentity prefix##YourIdName(void) \
    { \
        return _ZFP_ZFIdMapHolder_##GlobalNamespace##_##prefix##_##YourIdName::idValue(); \
    } \
    /** @brief see @ref prefix##YourIdName, @ref ZFIDMAP_GLOBAL */ \
    inline const zfchar *prefix##YourIdName##_name(void) \
    { \
        return _ZFP_ZFIdMapHolder_##GlobalNamespace##_##prefix##_##YourIdName::idName(); \
    }

/** @brief see #ZFIDMAP */
#define ZFIDMAP_REGISTER(Scope, YourIdName) \
    ZFIDMAP_DETAIL_REGISTER(Scope, Id, YourIdName)
/** @brief see #ZFIDMAP */
#define ZFIDMAP_DETAIL_REGISTER(Scope, prefix, YourIdName) \
    ZF_STATIC_REGISTER_INIT(ZFIdMap_##Scope##_##YourIdName) \
    { \
        (void)Scope::prefix##YourIdName(); \
        \
        { \
            ZFMethodUserRegisterDetail_0(resultMethod, &i_id, Scope::ClassData(), \
                public, ZFMethodTypeStatic, \
                zfidentity, ZFM_TOSTRING(prefix##YourIdName)); \
            this->m_id = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_0(resultMethod, &i_idName, Scope::ClassData(), \
                public, ZFMethodTypeStatic, \
                const zfchar *, ZFM_TOSTRING(prefix##YourIdName##_name)); \
            this->m_idName = resultMethod; \
        } \
    } \
    const ZFMethod *m_id; \
    static zfidentity i_id(ZF_IN const ZFMethod *method, ZF_IN ZFObject *obj) \
    {return Scope::prefix##YourIdName();} \
    \
    const ZFMethod *m_idName; \
    static const zfchar *i_idName(ZF_IN const ZFMethod *method, ZF_IN ZFObject *obj) \
    {return Scope::prefix##YourIdName##_name();} \
    ZF_STATIC_REGISTER_DESTROY(ZFIdMap_##Scope##_##YourIdName) \
    { \
        ZFMethodUserUnregister(this->m_id); \
        ZFMethodUserUnregister(this->m_idName); \
    } \
    ZF_STATIC_REGISTER_END(ZFIdMap_##Scope##_##YourIdName)

/** @brief see #ZFIDMAP */
#define ZFIDMAP_GLOBAL_REGISTER(Scope, YourIdName) \
    ZFIDMAP_GLOBAL_DETAIL_REGISTER(Scope, Id, YourIdName)
/** @brief see #ZFIDMAP */
#define ZFIDMAP_GLOBAL_DETAIL_REGISTER(Scope, prefix, YourIdName) \
    ZF_STATIC_REGISTER_INIT(ZFIdMap_##Scope##_##YourIdName) \
    { \
        (void)Scope::prefix##YourIdName(); \
        \
        { \
            ZFMethodFuncUserRegisterDetail_0(resultMethod, &i_id, ZFM_TOSTRING(Scope), \
                zfidentity, ZFM_TOSTRING(prefix##YourIdName)); \
            this->m_id = resultMethod; \
        } \
        { \
            ZFMethodFuncUserRegisterDetail_0(resultMethod, &i_idName, ZFM_TOSTRING(Scope), \
                const zfchar *, ZFM_TOSTRING(prefix##YourIdName##_name)); \
            this->m_idName = resultMethod; \
        } \
    } \
    ZF_STATIC_REGISTER_DESTROY(ZFIdMap_##Scope##_##YourIdName) \
    { \
        ZFMethodFuncUserUnregister(this->m_id); \
        ZFMethodFuncUserUnregister(this->m_idName); \
    } \
    const ZFMethod *m_id; \
    static zfidentity i_id(ZF_IN const ZFMethod *method, ZF_IN ZFObject *obj) \
    {return Scope::prefix##YourIdName();} \
    \
    const ZFMethod *m_idName; \
    static const zfchar *i_idName(ZF_IN const ZFMethod *method, ZF_IN ZFObject *obj) \
    {return Scope::prefix##YourIdName##_name();} \
    ZF_STATIC_REGISTER_END(ZFIdMap_##Scope##_##YourIdName) \

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFIdMap_h_

