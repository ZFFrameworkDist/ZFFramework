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
 * @file ZFProtocolZFLua.h
 * @brief protocol for ZFLua
 */

#ifndef _ZFI_ZFProtocolZFLua_h_
#define _ZFI_ZFProtocolZFLua_h_

#include "ZFCore/ZFProtocol.h"
#include "ZFLua/ZFLuaDef.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief protocol for ZFLua
 *
 * impl must supply all protocol described by #ZFLuaExecute
 */
ZFPROTOCOL_INTERFACE_BEGIN(ZFLua)
public:
    /** @brief see #ZFLuaState */
    virtual void *luaState(void) zfpurevirtual;

    /** @brief see #ZFLuaStateChange */
    virtual void luaStateChange(ZF_IN void *L) zfpurevirtual;

    /** @brief see #ZFLuaStateAttached */
    virtual void luaStateList(ZF_OUT ZFCoreArrayPOD<void *> &ret) zfpurevirtual;

    /** @brief see #ZFLuaStateAttach */
    virtual void luaStateAttach(ZF_IN void *L) zfpurevirtual;

    /** @brief see #ZFLuaStateDetach */
    virtual void luaStateDetach(ZF_IN void *L) zfpurevirtual;

    /** @brief see #ZFLuaExecute */
    virtual zfbool luaExecute(ZF_IN void *L,
                              ZF_IN const ZFPathInfo *pathInfoOrNull,
                              ZF_IN const ZFInputCallback &input,
                              ZF_OUT_OPT zfautoObject *luaResult = zfnull,
                              ZF_IN_OPT const ZFCoreArray<zfautoObject> *luaParams = zfnull,
                              ZF_OUT_OPT zfstring *errorHint = zfnull) zfpurevirtual;

    /** @brief see #ZFLuaGC */
    virtual void luaGC(ZF_IN void *L) zfpurevirtual;
ZFPROTOCOL_INTERFACE_END(ZFLua)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFProtocolZFLua_h_

