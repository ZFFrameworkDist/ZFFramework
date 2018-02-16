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
 * @file ZFSynchronize.h
 * @brief type define for synchronize logic in ZFFramework
 */

#ifndef _ZFI_ZFSynchronize_h_
#define _ZFI_ZFSynchronize_h_

#include "ZFObjectCore.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// internal test
#define _ZFP_ZFSYNCHRONIZE_LOG_ENABLE 0

// ============================================================
/**
 * @brief similar to  synchronized in Java
 *
 * usage:
 * @code
 *   ZFObject *obj = ...;
 *   ...
 *   // not mutable
 *   {
 *       zfsynchronizedObject(obj);
 *       // mutable
 *   }
 *   // not mutable
 * @endcode
 */
#if _ZFP_ZFSYNCHRONIZE_LOG_ENABLE
    #define zfsynchronizedObject(obj) \
        _ZFP_ZFSynchronizedObjectContainerWithLog ZFUniqueName(zfsynchronizedObject_holder)(obj \
            , ZFCallerInfoMake())
#else
    #define zfsynchronizedObject(obj) \
        _ZFP_ZFSynchronizedObjectContainer ZFUniqueName(zfsynchronizedObject_holder)(obj)
#endif

/**
 * @brief similar to #zfsynchronizedObject, while you take the responsibility to close it by #zfsynchronizedObjectUnlock
 *
 * usage:
 * @code
 *   zfsynchronizedObjectLock(obj);
 *   // mutable operation
 *   zfsynchronizedObjectUnlock(obj);
 * @endcode
 * it's not necessary to put them in the same code block,
 * but you must ensure the lock and unlock are paired
 * @see zfsynchronizedObject
 */
#if _ZFP_ZFSYNCHRONIZE_LOG_ENABLE
    #define zfsynchronizedObjectLock(obj) _ZFP_ZFSynchronizedObjectLockWithLog(obj \
        , ZFCallerInfoMake())
#else
    #define zfsynchronizedObjectLock(obj) _ZFP_ZFSynchronizedObjectLock(obj)
#endif

/**
 * @brief see #zfsynchronizedObjectLock
 */
#if _ZFP_ZFSYNCHRONIZE_LOG_ENABLE
    #define zfsynchronizedObjectUnlock(obj) _ZFP_ZFSynchronizedObjectUnlockWithLog(obj \
        , ZFCallerInfoMake())
#else
    #define zfsynchronizedObjectUnlock(obj) _ZFP_ZFSynchronizedObjectUnlock(obj)
#endif

/**
 * @brief make current code block mutable
 *
 * usage:
 * @code
 *   void func()
 *   {
 *       zfsynchronize();
 *       // mutable operation
 *       if(condition) {return ;} // safe to return
 *       // still mutable
 *   } // end mutable when brace end
 * @endcode
 * @see zfsynchronizeLock, zfsynchronizeUnlock
 */
#if _ZFP_ZFSYNCHRONIZE_LOG_ENABLE
    #define zfsynchronize() _ZFP_ZFSynchronizeContainerWithLog ZFUniqueName(zfsynchronize)( \
        ZFCallerInfoMake())
#else
    #define zfsynchronize() _ZFP_ZFSynchronizeContainer ZFUniqueName(zfsynchronize)
#endif

/**
 * @brief similar to #zfsynchronize, while you take the responsibility to close it by #zfsynchronizeUnlock
 *
 * usage:
 * @code
 *   zfsynchronizeLock();
 *   // mutable operation
 *   zfsynchronizeUnlock();
 * @endcode
 * it's not necessary to put them in the same code block,
 * but you must ensure the lock and unlock are paired
 * @see zfsynchronize
 */
#if _ZFP_ZFSYNCHRONIZE_LOG_ENABLE
    #define zfsynchronizeLock() _ZFP_ZFSynchronizeLockWithLog(\
        ZFCallerInfoMake())
#else
    #define zfsynchronizeLock() _ZFP_ZFSynchronizeLock()
#endif

/**
 * @brief see #zfsynchronizeLock
 */
#if _ZFP_ZFSYNCHRONIZE_LOG_ENABLE
    #define zfsynchronizeUnlock() _ZFP_ZFSynchronizeUnlockWithLog(\
        ZFCallerInfoMake())
#else
    #define zfsynchronizeUnlock() _ZFP_ZFSynchronizeUnlock()
#endif

// ============================================================
extern ZF_ENV_EXPORT ZFObject *_ZFP_zfsynchronizeObject;

// ============================================================
// no log version
zffinal zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFSynchronizedObjectContainer
{
public:
    _ZFP_ZFSynchronizedObjectContainer(ZF_IN ZFObject *obj)
    : m_obj(obj)
    {
        if(obj == zfnull)
        {
            zfCoreCriticalMessageTrim(zfTextA("[zfsynchronize] try synchronize a null object"));
        }
        else
        {
            zfRetain(m_obj);
            m_obj->_ZFP_ZFObjectLock();
        }
    }
    ~_ZFP_ZFSynchronizedObjectContainer(void)
    {
        m_obj->_ZFP_ZFObjectUnlock();
        zfRelease(m_obj);
    }
private:
    ZFObject *m_obj;
};

inline void _ZFP_ZFSynchronizedObjectLock(ZF_IN ZFObject *obj)
{
    if(obj == zfnull)
    {
        zfCoreCriticalMessageTrim(zfTextA("[zfsynchronize] try lock a null object"));
    }
    else
    {
        zfRetain(obj);
        obj->_ZFP_ZFObjectLock();
    }
}
inline void _ZFP_ZFSynchronizedObjectUnlock(ZF_IN ZFObject *obj)
{
    if(obj == zfnull)
    {
        zfCoreCriticalMessageTrim(zfTextA("[zfsynchronize] try unlock a null object"));
    }
    else
    {
        obj->_ZFP_ZFObjectUnlock();
        zfRelease(obj);
    }
}

zffinal zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFSynchronizeContainer
{
public:
    _ZFP_ZFSynchronizeContainer(void)
    : locked(zffalse)
    {
        if(_ZFP_zfsynchronizeObject)
        {
            zfRetain(_ZFP_zfsynchronizeObject);
            _ZFP_zfsynchronizeObject->_ZFP_ZFObjectLock();
            this->locked = zftrue;
        }
    }
    ~_ZFP_ZFSynchronizeContainer(void)
    {
        if(this->locked && _ZFP_zfsynchronizeObject)
        {
            _ZFP_zfsynchronizeObject->_ZFP_ZFObjectUnlock();
            zfRelease(_ZFP_zfsynchronizeObject);
        }
    }
private:
    zfbool locked;
};

inline void _ZFP_ZFSynchronizeLock(void)
{
    if(_ZFP_zfsynchronizeObject)
    {
        zfRetain(_ZFP_zfsynchronizeObject);
        _ZFP_zfsynchronizeObject->_ZFP_ZFObjectLock();
    }
}
inline void _ZFP_ZFSynchronizeUnlock(void)
{
    if(_ZFP_zfsynchronizeObject)
    {
        _ZFP_zfsynchronizeObject->_ZFP_ZFObjectUnlock();
        zfRelease(_ZFP_zfsynchronizeObject);
    }
}

// ============================================================
// log version
#if _ZFP_ZFSYNCHRONIZE_LOG_ENABLE
zffinal zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFSynchronizedObjectContainerWithLog
{
public:
    _ZFP_ZFSynchronizedObjectContainerWithLog(ZF_IN ZFObject *obj,
                                              ZF_IN const ZFCallerInfo &callerInfo);
    ~_ZFP_ZFSynchronizedObjectContainerWithLog(void);
private:
    ZFObject *m_obj;
    ZFCallerInfo callerInfo;
};

extern ZF_ENV_EXPORT void _ZFP_ZFSynchronizedObjectLockWithLog(ZF_IN ZFObject *obj,
                                                               ZF_IN const ZFCallerInfo &callerInfo);
extern ZF_ENV_EXPORT void _ZFP_ZFSynchronizedObjectUnlockWithLog(ZF_IN ZFObject *obj,
                                                                 ZF_IN const ZFCallerInfo &callerInfo);

zffinal zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFSynchronizeContainerWithLog
{
public:
    _ZFP_ZFSynchronizeContainerWithLog(ZF_IN const ZFCallerInfo &callerInfo);
    ~_ZFP_ZFSynchronizeContainerWithLog(void);
private:
    zfbool locked;
    ZFCallerInfo callerInfo;
};

extern ZF_ENV_EXPORT void _ZFP_ZFSynchronizeLockWithLog(ZF_IN const ZFCallerInfo &callerInfo);
extern ZF_ENV_EXPORT void _ZFP_ZFSynchronizeUnlockWithLog(ZF_IN const ZFCallerInfo &callerInfo);
#endif // #if _ZFP_ZFSYNCHRONIZE_LOG_ENABLE

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFSynchronize_h_

