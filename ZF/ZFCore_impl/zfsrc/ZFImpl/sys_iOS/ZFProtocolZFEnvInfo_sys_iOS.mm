/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFImpl_sys_iOS_ZFCore_impl.h"
#include "ZFCore/protocol/ZFProtocolZFEnvInfo.h"

#if ZF_ENV_sys_iOS

#import <UIKit/UIKit.h>

ZF_NAMESPACE_GLOBAL_BEGIN

ZFPROTOCOL_IMPLEMENTATION_BEGIN(ZFEnvInfo_systemInfoImpl_sys_iOS, ZFEnvInfo_systemInfo, ZFProtocolLevel::e_SystemNormal)
public:
    virtual void systemName(ZF_IN_OUT zfstring &ret)
    {
        ret += zfsCoreA2Z([[UIDevice currentDevice] systemName].UTF8String);
    }
    virtual void systemVersion(ZF_IN_OUT zfstring &ret)
    {
        ret += zfsCoreA2Z([[UIDevice currentDevice] systemVersion].UTF8String);
    }
ZFPROTOCOL_IMPLEMENTATION_END(ZFEnvInfo_systemInfoImpl_sys_iOS)
ZFPROTOCOL_IMPLEMENTATION_REGISTER(ZFEnvInfo_systemInfoImpl_sys_iOS)

ZFPROTOCOL_IMPLEMENTATION_BEGIN(ZFEnvInfo_frameworkInfoImpl_sys_iOS, ZFEnvInfo_frameworkInfo, ZFProtocolLevel::e_SystemNormal)
public:
    virtual void frameworkName(ZF_IN_OUT zfstring &ret)
    {
        ret += zfsCoreA2Z([[UIDevice currentDevice] systemName].UTF8String);
    }
    virtual void frameworkVersion(ZF_IN_OUT zfstring &ret)
    {
        ret += zfsCoreA2Z([[UIDevice currentDevice] systemVersion].UTF8String);
    }
ZFPROTOCOL_IMPLEMENTATION_END(ZFEnvInfo_frameworkInfoImpl_sys_iOS)
ZFPROTOCOL_IMPLEMENTATION_REGISTER(ZFEnvInfo_frameworkInfoImpl_sys_iOS)

ZF_NAMESPACE_GLOBAL_END
#endif // #if ZF_ENV_sys_iOS
