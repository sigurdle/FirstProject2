#ifndef jni_h
#define jni_h

namespace System
{
namespace javavm
{

#define JNICALL __stdcall
#define JNIEXPORT __declspec(dllexport)
#define JNIIMPORT __declspec(dllimport)

typedef bool jboolean;
typedef uint16 jchar;
typedef int8 jbyte;
typedef int16 jshort;
typedef int32 jint;
typedef int64 jlong;
typedef jint jsize;
typedef float jfloat;
typedef double jdouble;

class _jobject {};
class _jclass : public _jobject {};
class _jthrowable : public _jobject {};
class _jstring : public _jobject {};
class _jarray : public _jobject {};
class _jbooleanArray : public _jarray {};
class _jbyteArray : public _jarray {};
class _jcharArray : public _jarray {};
class _jshortArray : public _jarray {};
class _jintArray : public _jarray {};
class _jlongArray : public _jarray {};
class _jfloatArray : public _jarray {};
class _jdoubleArray : public _jarray {};
class _jobjectArray : public _jarray {};

typedef _jobject* jobject;
typedef _jclass* jclass;
typedef _jthrowable* jthrowable;
typedef _jstring* jstring;
typedef _jarray* jarray;
typedef _jbooleanArray* jbooleanArray;
typedef _jobjectArray* jobjectArray;
typedef _jbyteArray* jbyteArray;
typedef _jcharArray* jcharArray;
typedef _jintArray* jintArray;
typedef _jshortArray* jshortArray;
typedef _jfloatArray* jfloatArray;
typedef _jdoubleArray* jdoubleArray;
typedef _jlongArray* jlongArray;

typedef struct _jmethodID {} *jmethodID;
typedef struct _jfieldID {} *jfieldID;

typedef jobject jweak;

union jvalue
{
	jboolean z;
	jbyte    b;
	jchar    c;
	jshort   s;
	jint     i;
	jlong    j;
	jfloat   f;
	jdouble  d;
	jobject  l;
};

/*
 * used in RegisterNatives to describe native method name, signature,
 * and function pointer.
 */
struct JNINativeMethod
{
	char *name;
	char *signature;
	void *fnPtr;
};

interface JavaVM;

interface JNIEnv
{
	virtual void JNICALL reserved0() = 0;
	virtual void JNICALL reserved1() = 0;
	virtual void JNICALL reserved2() = 0;
	virtual void JNICALL reserved3() = 0;

	virtual jint JNICALL GetVersion() = 0;
	
	virtual jclass JNICALL DefineClass(const char *name, jobject loader, const jbyte* buf, jsize len) = 0;
	virtual jclass JNICALL FindClass(const char *name) = 0;
	
	virtual jmethodID JNICALL FromReflectedMethod(jobject method) = 0;
	virtual jfieldID JNICALL FromReflectedField(jobject field) = 0;
	
	virtual jobject JNICALL ToReflectedMethod(jclass cls, jmethodID methodID, jboolean isStatic) = 0;
	
	virtual jclass JNICALL GetSuperclass(jclass sub) = 0;
	virtual jboolean JNICALL IsAssignableFrom(jclass sub, jclass sup) = 0;
	
	virtual jobject JNICALL ToReflectedField(jclass cls, jfieldID fieldID, jboolean isStatic) = 0;
	
	virtual jint JNICALL Throw(jthrowable obj) = 0;
	virtual jint JNICALL ThrowNew(jclass clazz, const char *msg) = 0;
	virtual jthrowable JNICALL ExceptionOccurred() = 0;
	virtual void JNICALL ExceptionDescribe() = 0;
	virtual void JNICALL ExceptionClear() = 0;
	virtual void JNICALL FatalError(const char *msg) = 0;
	
	virtual jint JNICALL PushLocalFrame(jint capacity) = 0;
	virtual jobject JNICALL PopLocalFrame(jobject result) = 0;
	
	virtual jobject JNICALL NewGlobalRef(jobject lobj) = 0;
	virtual void JNICALL DeleteGlobalRef(jobject gref) = 0;
	virtual void JNICALL DeleteLocalRef(jobject obj) = 0;
	virtual jboolean JNICALL IsSameObject(jobject obj1, jobject obj2) = 0;
	virtual jobject JNICALL NewLocalRef(jobject ref) = 0;
	virtual jint JNICALL EnsureLocalCapacity(jint capacity) = 0;
	
	virtual jobject JNICALL AllocObject(jclass clazz) = 0;
	virtual jobject JNICALL NewObject(jclass clazz, jmethodID method_ID, ...) = 0;
	virtual jobject JNICALL NewObjectV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jobject JNICALL NewObjectA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jclass JNICALL GetObjectClass(jobject obj) = 0;
	virtual jboolean JNICALL IsInstanceOf(jobject obj, jclass clazz) = 0;
	
	virtual jmethodID JNICALL GetMethodID(jclass clazz, const char *name, const char *sig) = 0;
	
	virtual jobject JNICALL CallObjectMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual jobject JNICALL CallObjectMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual jobject JNICALL CallObjectMethodA(jobject obj, jmethodID methodID, const jvalue * args) = 0;
	
	virtual jboolean JNICALL CallBooleanMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual jboolean JNICALL CallBooleanMethodV(jobject obj, jmethodID methodID, va_list args)  = 0;
	virtual jboolean JNICALL CallBooleanMethodA(jobject obj, jmethodID methodID, const jvalue * args)  = 0;
	
	virtual jbyte JNICALL CallByteMethod(jobject obj, jmethodID methodID, ...)  = 0;
	virtual jbyte JNICALL CallByteMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual jbyte JNICALL CallByteMethodA(jobject obj, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jchar JNICALL CallCharMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual jchar JNICALL CallCharMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual jchar JNICALL CallCharMethodA(jobject obj, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jshort JNICALL CallShortMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual jshort JNICALL CallShortMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual jshort JNICALL CallShortMethodA(jobject obj, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jint JNICALL CallIntMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual jint JNICALL CallIntMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual jint JNICALL CallIntMethodA(jobject obj, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jlong JNICALL CallLongMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual jlong JNICALL CallLongMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual jlong JNICALL CallLongMethodA(jobject obj, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jfloat JNICALL CallFloatMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual jfloat JNICALL CallFloatMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual jfloat JNICALL CallFloatMethodA(jobject obj, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jdouble JNICALL CallDoubleMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual jdouble JNICALL CallDoubleMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual jdouble JNICALL CallDoubleMethodA(jobject obj, jmethodID methodID, const jvalue *args) = 0;
	
	virtual void JNICALL CallVoidMethod(jobject obj, jmethodID methodID, ...) = 0;
	virtual void JNICALL CallVoidMethodV(jobject obj, jmethodID methodID, va_list args) = 0;
	virtual void JNICALL CallVoidMethodA(jobject obj, jmethodID methodID, const jvalue * args) = 0;
	
	virtual jobject JNICALL CallNonvirtualObjectMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jobject JNICALL CallNonvirtualObjectMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jobject JNICALL CallNonvirtualObjectMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue * args) = 0;
	
	virtual jboolean JNICALL CallNonvirtualBooleanMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jboolean JNICALL CallNonvirtualBooleanMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jboolean JNICALL CallNonvirtualBooleanMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue * args) = 0;
	
	virtual jbyte JNICALL CallNonvirtualByteMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jbyte JNICALL CallNonvirtualByteMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jbyte JNICALL CallNonvirtualByteMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jchar JNICALL CallNonvirtualCharMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jchar JNICALL CallNonvirtualCharMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jchar JNICALL CallNonvirtualCharMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jshort JNICALL CallNonvirtualShortMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jshort JNICALL CallNonvirtualShortMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jshort JNICALL CallNonvirtualShortMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jint JNICALL CallNonvirtualIntMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jint JNICALL CallNonvirtualIntMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jint JNICALL CallNonvirtualIntMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jlong JNICALL CallNonvirtualLongMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jlong JNICALL CallNonvirtualLongMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jlong JNICALL CallNonvirtualLongMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jfloat JNICALL CallNonvirtualFloatMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jfloat JNICALL CallNonvirtualFloatMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jfloat JNICALL CallNonvirtualFloatMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jdouble JNICALL CallNonvirtualDoubleMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual jdouble JNICALL CallNonvirtualDoubleMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jdouble JNICALL CallNonvirtualDoubleMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual void JNICALL CallNonvirtualVoidMethod(jobject obj, jclass clazz, jmethodID methodID, ...) = 0;
	virtual void JNICALL CallNonvirtualVoidMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual void JNICALL CallNonvirtualVoidMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue * args) = 0;
	
	virtual jfieldID JNICALL GetFieldID(jclass clazz, const char *name, const char *sig) = 0;
	
	virtual jobject JNICALL GetObjectField(jobject obj, jfieldID fieldID) = 0;
	virtual jboolean JNICALL GetBooleanField(jobject obj, jfieldID fieldID) = 0;
	virtual jbyte JNICALL GetByteField(jobject obj, jfieldID fieldID) = 0;
	virtual jchar JNICALL GetCharField(jobject obj, jfieldID fieldID) = 0;
	virtual jshort JNICALL GetShortField(jobject obj, jfieldID fieldID) = 0;
	virtual jint JNICALL GetIntField(jobject obj, jfieldID fieldID) = 0;
	virtual jlong JNICALL GetLongField(jobject obj, jfieldID fieldID) = 0;
	virtual jfloat JNICALL GetFloatField(jobject obj, jfieldID fieldID) = 0;
	virtual jdouble JNICALL GetDoubleField(jobject obj, jfieldID fieldID) = 0;
	
	virtual void JNICALL SetObjectField(jobject obj, jfieldID fieldID, jobject val) = 0;
	virtual void JNICALL SetBooleanField(jobject obj, jfieldID fieldID, jboolean val) = 0;
	virtual void JNICALL SetByteField(jobject obj, jfieldID fieldID, jbyte val) = 0;
	virtual void JNICALL SetCharField(jobject obj, jfieldID fieldID, jchar val) = 0;
	virtual void JNICALL SetShortField(jobject obj, jfieldID fieldID, jshort val) = 0;
	virtual void JNICALL SetIntField(jobject obj, jfieldID fieldID, jint val) = 0;
	virtual void JNICALL SetLongField(jobject obj, jfieldID fieldID, jlong val) = 0;
	virtual void JNICALL SetFloatField(jobject obj, jfieldID fieldID, jfloat val) = 0;
	virtual void JNICALL SetDoubleField(jobject obj, jfieldID fieldID, jdouble val) = 0;
	
	virtual jmethodID JNICALL GetStaticMethodID(jclass clazz, const char *name, const char *sig) = 0;
	
	virtual jobject JNICALL CallStaticObjectMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jobject JNICALL CallStaticObjectMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jobject JNICALL CallStaticObjectMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jboolean JNICALL CallStaticBooleanMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jboolean JNICALL CallStaticBooleanMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jboolean JNICALL CallStaticBooleanMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jbyte JNICALL CallStaticByteMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jbyte JNICALL CallStaticByteMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jbyte JNICALL CallStaticByteMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jchar JNICALL CallStaticCharMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jchar JNICALL CallStaticCharMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jchar JNICALL CallStaticCharMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jshort JNICALL CallStaticShortMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jshort JNICALL CallStaticShortMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jshort JNICALL CallStaticShortMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jint JNICALL CallStaticIntMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jint JNICALL CallStaticIntMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jint JNICALL CallStaticIntMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jlong JNICALL CallStaticLongMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jlong JNICALL CallStaticLongMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jlong JNICALL CallStaticLongMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jfloat JNICALL CallStaticFloatMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jfloat JNICALL CallStaticFloatMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jfloat JNICALL CallStaticFloatMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual jdouble JNICALL CallStaticDoubleMethod(jclass clazz, jmethodID methodID, ...) = 0;
	virtual jdouble JNICALL CallStaticDoubleMethodV(jclass clazz, jmethodID methodID, va_list args) = 0;
	virtual jdouble JNICALL CallStaticDoubleMethodA(jclass clazz, jmethodID methodID, const jvalue *args) = 0;
	
	virtual void JNICALL CallStaticVoidMethod(jclass cls, jmethodID methodID, ...) = 0;
	virtual void JNICALL CallStaticVoidMethodV(jclass cls, jmethodID methodID, va_list args) = 0;
	virtual void JNICALL CallStaticVoidMethodA(jclass cls, jmethodID methodID, const jvalue * args) = 0;
	
	virtual jfieldID JNICALL GetStaticFieldID(jclass clazz, const char *name, const char *sig) = 0;
	virtual jobject JNICALL GetStaticObjectField(jclass clazz, jfieldID fieldID) = 0;
	virtual jboolean JNICALL GetStaticBooleanField(jclass clazz, jfieldID fieldID) = 0;
	virtual jbyte JNICALL GetStaticByteField(jclass clazz, jfieldID fieldID) = 0;
	virtual jchar JNICALL GetStaticCharField(jclass clazz, jfieldID fieldID) = 0;
	virtual jshort JNICALL GetStaticShortField(jclass clazz, jfieldID fieldID) = 0;
	virtual jint JNICALL GetStaticIntField(jclass clazz, jfieldID fieldID) = 0;
	virtual jlong JNICALL GetStaticLongField(jclass clazz, jfieldID fieldID) = 0;
	virtual jfloat JNICALL GetStaticFloatField(jclass clazz, jfieldID fieldID) = 0;
	virtual jdouble JNICALL GetStaticDoubleField(jclass clazz, jfieldID fieldID) = 0;
	
	virtual void JNICALL SetStaticObjectField(jclass clazz, jfieldID fieldID, jobject value) = 0;
	virtual void JNICALL SetStaticBooleanField(jclass clazz, jfieldID fieldID, jboolean value) = 0;
	virtual void JNICALL SetStaticByteField(jclass clazz, jfieldID fieldID, jbyte value) = 0;
	virtual void JNICALL SetStaticCharField(jclass clazz, jfieldID fieldID, jchar value) = 0;
	virtual void JNICALL SetStaticShortField(jclass clazz, jfieldID fieldID, jshort value) = 0;
	virtual void JNICALL SetStaticIntField(jclass clazz, jfieldID fieldID, jint value) = 0;
	virtual void JNICALL SetStaticLongField(jclass clazz, jfieldID fieldID, jlong value) = 0;
	virtual void JNICALL SetStaticFloatField(jclass clazz, jfieldID fieldID, jfloat value) = 0;
	virtual void JNICALL SetStaticDoubleField(jclass clazz, jfieldID fieldID, jdouble value) = 0;
	
	virtual jstring JNICALL NewString(const jchar *unicode, jsize len) = 0;
	virtual jsize JNICALL GetStringLength(jstring str) = 0;
	virtual const jchar *JNICALL GetStringChars(jstring str, jboolean *isCopy) = 0;
	virtual void JNICALL ReleaseStringChars(jstring str, const jchar *chars) = 0;
	
	virtual jstring JNICALL NewStringUTF(const char *utf) = 0;
	virtual jsize JNICALL GetStringUTFLength(jstring str) = 0;
	virtual const char* JNICALL GetStringUTFChars(jstring str, jboolean *isCopy) = 0;
	virtual void JNICALL ReleaseStringUTFChars(jstring str, const char* chars) = 0;
	
	virtual jsize JNICALL GetArrayLength(jarray _array) = 0;
	
	virtual jobjectArray JNICALL NewObjectArray(jsize len, jclass clazz, jobject init) = 0;
	virtual jobject JNICALL GetObjectArrayElement(jobjectArray _array, jsize index) = 0;
	virtual void JNICALL SetObjectArrayElement(jobjectArray _array, jsize index, jobject val) = 0;
	
	virtual jbooleanArray JNICALL NewBooleanArray(jsize len) = 0;
	virtual jbyteArray JNICALL NewByteArray(jsize len) = 0;
	virtual jcharArray JNICALL NewCharArray(jsize len) = 0;
	virtual jshortArray JNICALL NewShortArray(jsize len) = 0;
	virtual jintArray JNICALL NewIntArray(jsize len) = 0;
	virtual jlongArray JNICALL NewLongArray(jsize len) = 0;
	virtual jfloatArray JNICALL NewFloatArray(jsize len) = 0;
	virtual jdoubleArray JNICALL NewDoubleArray(jsize len) = 0;
	
	virtual jboolean* JNICALL GetBooleanArrayElements(jbooleanArray _array, jboolean *isCopy) = 0;
	virtual jbyte* JNICALL GetByteArrayElements(jbyteArray _array, jboolean *isCopy) = 0;
	virtual jchar* JNICALL GetCharArrayElements(jcharArray _array, jboolean *isCopy) = 0;
	virtual jshort* JNICALL GetShortArrayElements(jshortArray _array, jboolean *isCopy) = 0;
	virtual jint* JNICALL GetIntArrayElements(jintArray _array, jboolean *isCopy) = 0;
	virtual jlong* JNICALL GetLongArrayElements(jlongArray _array, jboolean *isCopy) = 0;
	virtual jfloat* JNICALL GetFloatArrayElements(jfloatArray _array, jboolean *isCopy) = 0;
	virtual jdouble* JNICALL GetDoubleArrayElements(jdoubleArray _array, jboolean *isCopy) = 0;
	
	virtual void JNICALL ReleaseBooleanArrayElements(jbooleanArray _array, jboolean *elems, jint mode) = 0;
	virtual void JNICALL ReleaseByteArrayElements(jbyteArray _array, jbyte *elems, jint mode) = 0;
	virtual void JNICALL ReleaseCharArrayElements(jcharArray _array, jchar *elems, jint mode) = 0;
	virtual void JNICALL ReleaseShortArrayElements(jshortArray _array, jshort *elems, jint mode) = 0;
	virtual void JNICALL ReleaseIntArrayElements(jintArray _array, jint *elems, jint mode) = 0;
	virtual void JNICALL ReleaseLongArrayElements(jlongArray _array, jlong *elems, jint mode) = 0;
	virtual void JNICALL ReleaseFloatArrayElements(jfloatArray _array, jfloat *elems, jint mode) = 0;
	virtual void JNICALL ReleaseDoubleArrayElements(jdoubleArray _array, jdouble *elems, jint mode) = 0;
	
	virtual void JNICALL GetBooleanArrayRegion(jbooleanArray _array, jsize start, jsize l, jboolean *buf) = 0;
	virtual void JNICALL GetByteArrayRegion(jbyteArray _array, jsize start, jsize len, jbyte *buf) = 0;
	virtual void JNICALL GetCharArrayRegion(jcharArray _array, jsize start, jsize len, jchar *buf) = 0;
	virtual void JNICALL GetShortArrayRegion(jshortArray _array, jsize start, jsize len, jshort *buf) = 0;
	virtual void JNICALL GetIntArrayRegion(jintArray _array, jsize start, jsize len, jint *buf) = 0;
	virtual void JNICALL GetLongArrayRegion(jlongArray _array, jsize start, jsize len, jlong *buf) = 0;
	virtual void JNICALL GetFloatArrayRegion(jfloatArray _array, jsize start, jsize len, jfloat *buf) = 0;
	virtual void JNICALL GetDoubleArrayRegion(jdoubleArray _array, jsize start, jsize len, jdouble *buf) = 0;
	
	virtual void JNICALL SetBooleanArrayRegion(jbooleanArray _array, jsize start, jsize l, const jboolean *buf) = 0;
	virtual void JNICALL SetByteArrayRegion(jbyteArray _array, jsize start, jsize len, const jbyte *buf) = 0;
	virtual void JNICALL SetCharArrayRegion(jcharArray _array, jsize start, jsize len, const jchar *buf) = 0;
	virtual void JNICALL SetShortArrayRegion(jshortArray _array, jsize start, jsize len, const jshort *buf) = 0;
	virtual void JNICALL SetIntArrayRegion(jintArray _array, jsize start, jsize len, const jint *buf) = 0;
	virtual void JNICALL SetLongArrayRegion(jlongArray _array, jsize start, jsize len, const jlong *buf) = 0;
	virtual void JNICALL SetFloatArrayRegion(jfloatArray _array, jsize start, jsize len, const jfloat *buf) = 0;
	virtual void JNICALL SetDoubleArrayRegion(jdoubleArray _array, jsize start, jsize len, const jdouble *buf) = 0;
	
	virtual jint JNICALL RegisterNatives(jclass clazz, const JNINativeMethod *methods, jint nMethods) = 0;
	virtual jint JNICALL UnregisterNatives(jclass clazz) = 0;
	
	virtual jint JNICALL MonitorEnter(jobject obj) = 0;
	virtual jint JNICALL MonitorExit(jobject obj) = 0;
	
	virtual jint JNICALL GetJavaVM(void/*JavaVM*/ **vm) = 0;
	
	virtual void JNICALL GetStringRegion(jstring str, jsize start, jsize len, jchar *buf) = 0;
	virtual void JNICALL GetStringUTFRegion(jstring str, jsize start, jsize len, char *buf) = 0;
	
	virtual void* JNICALL GetPrimitiveArrayCritical(jarray _array, jboolean *isCopy) = 0;
	virtual void JNICALL ReleasePrimitiveArrayCritical(jarray _array, void *carray, jint mode) = 0;
	
	virtual const jchar* JNICALL GetStringCritical(jstring string, jboolean *isCopy) = 0;
	virtual void JNICALL ReleaseStringCritical(jstring string, const jchar *cstring) = 0;
	
	virtual jweak JNICALL NewWeakGlobalRef(jobject obj) = 0;
	virtual void JNICALL DeleteWeakGlobalRef(jweak ref) = 0;
	
	virtual jboolean JNICALL ExceptionCheck() = 0;
	
	virtual jobject JNICALL NewDirectByteBuffer(void* address, jlong capacity) = 0;
	virtual void* JNICALL GetDirectBufferAddress(jobject buf) = 0;
	virtual jlong JNICALL GetDirectBufferCapacity(jobject buf) = 0;
};

typedef struct JavaVMOption
{
	char *optionString;
	void *extraInfo;
}
JavaVMOption;

typedef struct JavaVMInitArgs
{
	jint version;

	jint nOptions;
	JavaVMOption *options;
	jboolean ignoreUnrecognized;
}
JavaVMInitArgs;

typedef struct JavaVMAttachArgs
{
	jint version;

	char *name;
	jobject group;
}
JavaVMAttachArgs;

/* These will be VM-specific. */

#define JDK1_2
#define JDK1_4

/* End VM-specific. */

interface JavaVM
{
	virtual void JNICALL reserved0() = 0;
	virtual void JNICALL reserved1() = 0;
	virtual void JNICALL reserved2() = 0;

	virtual jint JNICALL DestroyJavaVM() = 0;
	virtual jint JNICALL AttachCurrentThread(void** penv, void* args) = 0;
	virtual jint JNICALL DetachCurrentThread() = 0;
	virtual jint JNICALL GetEnv(void** penv, jint version) = 0;
	virtual jint JNICALL AttachCurrentThreadAsDaemon(void** penv, void* args) = 0;
};

#ifdef _JNI_IMPLEMENTATION_
#define _JNI_IMPORT_OR_EXPORT_ JNIEXPORT
#else
#define _JNI_IMPORT_OR_EXPORT_ JNIIMPORT
#endif

extern "C"
{

_JNI_IMPORT_OR_EXPORT_ jint JNICALL JNI_GetDefaultJavaVMInitArgs(void* args);
_JNI_IMPORT_OR_EXPORT_ jint JNICALL JNI_CreateJavaVM(JavaVM** pvm, void** penv, void* args);
_JNI_IMPORT_OR_EXPORT_ jint JNICALL JNI_GetCreatedJavaVMs(JavaVM**, jsize, jsize* );

/* Defined by native libraries. */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved);

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved);

}

#define JNI_VERSION_1_1 0x00010001
#define JNI_VERSION_1_2 0x00010002
#define JNI_VERSION_1_4 0x00010004
#define JNI_VERSION_1_6 0x00010006

}	// JavaVM
}	// System

#endif // jni_h
