/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFImpl_sys_Android_ZFUIKit_impl.h"
#include "ZFUIKit/protocol/ZFProtocolZFUIViewFocus.h"
#include "ZFUIKit/protocol/ZFProtocolZFUIView.h"

#if ZF_ENV_sys_Android

ZF_NAMESPACE_GLOBAL_BEGIN

#define ZFImpl_sys_Android_JNI_ID_ZFUIViewFocus ZFImpl_sys_Android_JNI_ID(ZFUIKit_1impl_ZFUIViewFocus)
#define ZFImpl_sys_Android_JNI_NAME_ZFUIViewFocus ZFImpl_sys_Android_JNI_NAME(ZFUIKit_impl.ZFUIViewFocus)

ZFPROTOCOL_IMPLEMENTATION_BEGIN(ZFUIViewFocusImpl_sys_Android, ZFUIViewFocus, ZFProtocolLevel::e_SystemNormal)
    ZFPROTOCOL_IMPLEMENTATION_PLATFORM_HINT(zfText("Android:View"))
    ZFPROTOCOL_IMPLEMENTATION_PLATFORM_DEPENDENCY_BEGIN()
    ZFPROTOCOL_IMPLEMENTATION_PLATFORM_DEPENDENCY_ITEM(ZFUIView, zfText("Android:View"))
    ZFPROTOCOL_IMPLEMENTATION_PLATFORM_DEPENDENCY_END()

public:
    zfoverride
    virtual void protocolOnInit(void)
    {
        zfsuper::protocolOnInit();
        JNIEnv *jniEnv = JNIGetJNIEnv();
        jobject tmp = zfnull;

        tmp = JNIUtilFindClass(jniEnv, JNIConvertClassNameForFindClass(ZFImpl_sys_Android_JNI_NAME_ZFUIViewFocus).c_str());
        this->jclsOwner = (jclass)JNIUtilNewGlobalRef(jniEnv, tmp);
        JNIUtilDeleteLocalRef(jniEnv, tmp);
    }
    zfoverride
    virtual void protocolOnDealloc(void)
    {
        JNIEnv *jniEnv = JNIGetJNIEnv();
        JNIUtilDeleteGlobalRef(jniEnv, this->jclsOwner);
        zfsuper::protocolOnDealloc();
    }
public:
    virtual void viewFocusableSet(ZF_IN ZFUIView *view,
                                  ZF_IN zfbool viewFocusable)
    {
        JNIEnv *jniEnv = JNIGetJNIEnv();
        static jmethodID jmId = JNIUtilGetStaticMethodID(jniEnv, this->jclsOwner, zfTextA("native_viewFocusableSet"),
            JNIGetMethodSig(JNIType::S_void, JNIParamTypeContainer()
                .add(JNIType::S_object(ZFImpl_sys_Android_JNI_NAME_Object))
                .add(JNIType::S_boolean)
            ).c_str());
        JNIUtilCallStaticVoidMethod(jniEnv, this->jclsOwner, jmId,
            ZFCastStatic(jobject, view->nativeView()),
            viewFocusable);
    }
    virtual zfbool viewFocused(ZF_IN ZFUIView *view)
    {
        JNIEnv *jniEnv = JNIGetJNIEnv();
        static jmethodID jmId = JNIUtilGetStaticMethodID(jniEnv, this->jclsOwner, zfTextA("native_viewFocused"),
            JNIGetMethodSig(JNIType::S_boolean, JNIParamTypeContainer()
                .add(JNIType::S_object(ZFImpl_sys_Android_JNI_NAME_Object))
            ).c_str());
        return JNIUtilCallStaticBooleanMethod(jniEnv, this->jclsOwner, jmId, ZFCastStatic(jobject, view->nativeView()));
    }
    virtual ZFUIView *viewFocusFind(ZF_IN ZFUIView *view)
    {
        JNIEnv *jniEnv = JNIGetJNIEnv();
        static jmethodID jmId = JNIUtilGetStaticMethodID(jniEnv, this->jclsOwner, zfTextA("native_viewFocusFind"),
            JNIGetMethodSig(JNIType::S_long, JNIParamTypeContainer()
                .add(JNIType::S_object(ZFImpl_sys_Android_JNI_NAME_Object))
            ).c_str());
        JNIPointer zfjniPointerFocusedChild = JNIUtilCallStaticLongMethod(jniEnv, this->jclsOwner, jmId, ZFCastStatic(jobject, view->nativeView()));
        return ZFCastZFObject(ZFUIView *, JNIConvertZFObjectFromJNIType(jniEnv, zfjniPointerFocusedChild));
    }
    virtual void viewFocusRequest(ZF_IN ZFUIView *view,
                                  ZF_IN zfbool viewFocus)
    {
        JNIEnv *jniEnv = JNIGetJNIEnv();
        static jmethodID jmId = JNIUtilGetStaticMethodID(jniEnv, this->jclsOwner, zfTextA("native_viewFocusRequest"),
            JNIGetMethodSig(JNIType::S_void, JNIParamTypeContainer()
                .add(JNIType::S_object(ZFImpl_sys_Android_JNI_NAME_Object))
                .add(JNIType::S_boolean)
            ).c_str());
        JNIUtilCallStaticVoidMethod(jniEnv, this->jclsOwner, jmId,
            ZFCastStatic(jobject, view->nativeView()),
            viewFocus);
    }

private:
    jclass jclsOwner;
ZFPROTOCOL_IMPLEMENTATION_END(ZFUIViewFocusImpl_sys_Android)
ZFPROTOCOL_IMPLEMENTATION_REGISTER(ZFUIViewFocusImpl_sys_Android)

ZF_NAMESPACE_GLOBAL_END

JNI_METHOD_DECLARE(void, ZFImpl_sys_Android_JNI_ID_ZFUIViewFocus, native_1notifyViewFocusChanged,
                   JNIEnv *jniEnv, jclass jniCls,
                   JNIPointer zfjniPointerOwnerZFUIView)
{
    ZFUIView *view = ZFCastZFObject(ZFUIView *, JNIConvertZFObjectFromJNIType(jniEnv, zfjniPointerOwnerZFUIView));
    if(!ZFBitTest(view->objectInstanceState(), ZFObjectInstanceStateOnDealloc))
    {
        ZFPROTOCOL_ACCESS(ZFUIViewFocus)->notifyViewFocusChanged(view);
    }
}

#endif // #if ZF_ENV_sys_Android

