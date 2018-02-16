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
 * @file ZFProtocolZFUIViewCapture.h
 * @brief protocol for #ZFUIViewCapture
 */

#ifndef _ZFI_ZFProtocolZFUIViewCapture_h_
#define _ZFI_ZFProtocolZFUIViewCapture_h_

#include "ZFCore/ZFProtocol.h"
#include "ZFUIKit/ZFUIViewCapture.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief protocol for ZFUIView
 */
ZFPROTOCOL_INTERFACE_BEGIN(ZFUIViewCapture)
public:
    /**
     * @brief see #ZFUIViewCapture
     */
    virtual zfbool viewCapture(ZF_IN ZFUIView *view,
                               ZF_IN_OUT ZFUIImage *image) zfpurevirtual;
ZFPROTOCOL_INTERFACE_END(ZFUIViewCapture)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFProtocolZFUIViewCapture_h_

