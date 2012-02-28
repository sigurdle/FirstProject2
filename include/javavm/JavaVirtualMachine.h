#ifndef __JavaVM_Java_h__
#define __JavaVM_Java_h__

//#include "JavaClassFileLoader.h"

namespace System
{

void flog(const char* str, ...);

//#define LOG flog
#define LOG TRACE

namespace javavm
{

class JavaClass;
class JProcess;
class Thread;


class DataType
{
	union
	{
		char byte_dt;
		short short_dt;
		long int_dt;
		long bool_dt;
		LONGLONG long_dt;
		float float_dt;
		double double_dt;
	}
	u;
};


/*
class Operand
{
public:
	Operand* prev;
	long value;
};
*/

enum
{
	ArrayType_BOOLEAN  = 4 ,
	ArrayType_CHAR  = 5,
	ArrayType_FLOAT  = 6,
	ArrayType_DOUBLE  = 7,
	ArrayType_BYTE  = 8,
	ArrayType_SHORT  = 9,
	ArrayType_INT  = 10,
	ArrayType_LONG  = 11,
};

//typedef JavaObject ArrayRef;

/*
class ArrayRef
{
public:
	ArrayRef()
	{
		count = 0;
		m_data = 0;
	}
	JavaClass* m_TypeOfClass;
	uint8 baseType;
	uint8* m_data;
};
*/

class Operand
{
public:

	CTOR Operand()
	{
		kind = 0;
		u._long = 0;
	}

	CTOR Operand(int8 value)
	{
		kind = 1;
		u._int = value;
	}

	CTOR Operand(int16 value)
	{
		kind = 1;
		u._int = value;
	}

	CTOR Operand(jint value)
	{
		kind = 1;
		u._int = value;
	}

	CTOR Operand(LONGLONG value)
	{
		kind = 1 | 16;
		u._long = value;
	}

	CTOR Operand(float f)
	{
		kind = 2;
		u._float = f;
	}

	CTOR Operand(double d)
	{
		kind = 2 | 16;
		u._double = d;
	}

	/*
	CTOR Operand(JavaObject* r)
	{
		kind = 4;
		ref.m_object = r;
		ref.m_id = objcount++;
	}
	*/

	CTOR Operand(ObjectRef& r)
	{
		ASSERT(r.m_object == NULL || dynamic_cast<JavaObject*>(r.m_object));
		kind = 4;
		ref = r;
	}

	CTOR Operand(uint8* address)
	{
		kind = 8;
		u.address = address;
	}

	/*
	Operand(ArrayRef* ar)
	{
		kind = 5;
		u.arrayref = ar;
	}
	*/

	operator bool () const
	{
		ASSERT(kind == 1);
		return (bool)(u._int & 1);
	}

	operator int8 () const
	{
		ASSERT(kind == 1);
		return (int8)u._int;
	}

	operator int16 () const
	{
		ASSERT(kind == 1);
		return (int16)u._int;
	}

	operator uint16 () const
	{
		ASSERT(kind == 1);
		return (uint16)u._int;
	}

	operator jint () const
	{
		ASSERT(kind == 1);
		return (jint)u._int;
	}

	operator LONGLONG () const
	{
		ASSERT(kind == (1 | 16));
		return u._long;
	}

	operator float () const
	{
		ASSERT(kind == 2);
		return u._float;
	}

	operator double () const
	{
		ASSERT(kind == (2 | 16));
		return u._double;
	}

	operator ObjectRef () const
	{
		ASSERT(kind == 4);
		return ref;
	}

	operator JavaObject* () const
	{
		ASSERT(kind == 4);
		return ref;
	}

/*
	operator ArrayRef* () const
	{
		ASSERT(kind == 5);
		return u.arrayref;
	}
*/

	UINT kind;

	union
	{
		int32 _int;
		int64 _long;
		float _float;
		double _double;
//		JavaObject* ref;
		uint8* address;
	}
	u;

	ObjectRef ref;
};

class LocalVariable
{
public:
	CTOR LocalVariable()
	{
		kind = 1;
		m_value = 0;
	}

	CTOR LocalVariable(const ObjectRef& ref)
	{
		kind = 4;
		m_ref = ref;
	}

	CTOR LocalVariable(const Operand& op)
	{
		if (op.kind == 4)
		{
			kind = 4;
			m_ref = op;
		}
		else if (op.kind == 1 || op.kind == 2)
		{
			kind = 1;
			m_value = op.u._int;
		}
		else
			ASSERT(0);
	}

	CTOR LocalVariable(int32 value)
	{
		kind = 1;
		m_value = value;
	}

	operator int32 ()
	{
		ASSERT(kind == 1);
		return m_value;
	}

	operator ObjectRef ()
	{
		ASSERT(kind == 4);
		return m_ref;
	}

	/*
	operator Operand ()
	{
		if (kind == 1)
			return m_value;
		else
			return m_ref;
	}
	*/

	int kind;
	int32 m_value;
	ObjectRef m_ref;
};

class JNINativeInterface : public JNIEnv
{
public:

    virtual void JNICALL reserved0()
	 {
		 TRACE("TODO\n");
		 ASSERT(0);
	 }
    virtual void JNICALL reserved1()
	 {
		 TRACE("TODO\n");
		 ASSERT(0);
	 }
    virtual void JNICALL reserved2()
	 {
		 TRACE("TODO\n");
		 ASSERT(0);
	 }

    virtual void JNICALL reserved3()
	 {
		 TRACE("TODO\n");
		 ASSERT(0);
	 }

    virtual jint JNICALL GetVersion();

    virtual jclass JNICALL DefineClass(const char *name, jobject loader, const jbyte *buf, jsize len);
    virtual jclass JNICALL FindClass(const char *name);

	virtual jmethodID JNICALL FromReflectedMethod(jobject method);
	virtual jfieldID JNICALL FromReflectedField(jobject field);
	
	virtual jobject JNICALL ToReflectedMethod(jclass cls, jmethodID methodID, jboolean isStatic);
	
	virtual jclass JNICALL GetSuperclass(jclass sub);
	virtual jboolean JNICALL IsAssignableFrom(jclass sub, jclass sup);
	
	virtual jobject JNICALL ToReflectedField(jclass cls, jfieldID fieldID, jboolean isStatic);
	
	virtual jint JNICALL Throw(jthrowable obj);
	virtual jint JNICALL ThrowNew(jclass clazz, const char *msg);
	virtual jthrowable JNICALL ExceptionOccurred();
	virtual void JNICALL ExceptionDescribe();
	virtual void JNICALL ExceptionClear();
	virtual void JNICALL FatalError(const char *msg);
	
	virtual jint JNICALL PushLocalFrame(jint capacity);
	virtual jobject JNICALL PopLocalFrame(jobject result);
	
	virtual jobject JNICALL NewGlobalRef(jobject lobj);
	virtual void JNICALL DeleteGlobalRef(jobject gref);
	virtual void JNICALL DeleteLocalRef(jobject obj);
	virtual jboolean JNICALL IsSameObject(jobject obj1, jobject obj2);
	virtual jobject JNICALL NewLocalRef(jobject ref);
	virtual jint JNICALL EnsureLocalCapacity(jint capacity);
	
	virtual jobject JNICALL AllocObject(jclass clazz);
	virtual jobject JNICALL NewObject(jclass clazz, jmethodID method_ID, ...);
	virtual jobject JNICALL NewObjectV(jclass clazz, jmethodID methodID, va_list args);
	virtual jobject JNICALL NewObjectA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jclass JNICALL GetObjectClass(jobject obj);
	virtual jboolean JNICALL IsInstanceOf(jobject obj, jclass clazz);
	
	virtual jmethodID JNICALL GetMethodID(jclass clazz, const char *name, const char *sig);
	
	virtual jobject JNICALL CallObjectMethod(jobject obj, jmethodID methodID, ...);
	virtual jobject JNICALL CallObjectMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jobject JNICALL CallObjectMethodA(jobject obj, jmethodID methodID, const jvalue * args);
	
	virtual jboolean JNICALL CallBooleanMethod(jobject obj, jmethodID methodID, ...);
	virtual jboolean JNICALL CallBooleanMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jboolean JNICALL CallBooleanMethodA(jobject obj, jmethodID methodID, const jvalue * args);
	
	virtual jbyte JNICALL CallByteMethod(jobject obj, jmethodID methodID, ...);
	virtual jbyte JNICALL CallByteMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jbyte JNICALL CallByteMethodA(jobject obj, jmethodID methodID, const jvalue *args);
	
	virtual jchar JNICALL CallCharMethod(jobject obj, jmethodID methodID, ...);
	virtual jchar JNICALL CallCharMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jchar JNICALL CallCharMethodA(jobject obj, jmethodID methodID, const jvalue *args);
	
	virtual jshort JNICALL CallShortMethod(jobject obj, jmethodID methodID, ...);
	virtual jshort JNICALL CallShortMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jshort JNICALL CallShortMethodA(jobject obj, jmethodID methodID, const jvalue *args);
	
	virtual jint JNICALL CallIntMethod(jobject obj, jmethodID methodID, ...);
	virtual jint JNICALL CallIntMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jint JNICALL CallIntMethodA(jobject obj, jmethodID methodID, const jvalue *args);
	
	virtual jlong JNICALL CallLongMethod(jobject obj, jmethodID methodID, ...);
	virtual jlong JNICALL CallLongMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jlong JNICALL CallLongMethodA(jobject obj, jmethodID methodID, const jvalue *args);
	
	virtual jfloat JNICALL CallFloatMethod(jobject obj, jmethodID methodID, ...);
	virtual jfloat JNICALL CallFloatMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jfloat JNICALL CallFloatMethodA(jobject obj, jmethodID methodID, const jvalue *args);
	
	virtual jdouble JNICALL CallDoubleMethod(jobject obj, jmethodID methodID, ...);
	virtual jdouble JNICALL CallDoubleMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual jdouble JNICALL CallDoubleMethodA(jobject obj, jmethodID methodID, const jvalue *args);
	
	virtual void JNICALL CallVoidMethod(jobject obj, jmethodID methodID, ...);
	virtual void JNICALL CallVoidMethodV(jobject obj, jmethodID methodID, va_list args);
	virtual void JNICALL CallVoidMethodA(jobject obj, jmethodID methodID, const jvalue * args);
	
	virtual jobject JNICALL CallNonvirtualObjectMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jobject JNICALL CallNonvirtualObjectMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jobject JNICALL CallNonvirtualObjectMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue* args);
	
	virtual jboolean JNICALL CallNonvirtualBooleanMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jboolean JNICALL CallNonvirtualBooleanMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jboolean JNICALL CallNonvirtualBooleanMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue * args);
	
	virtual jbyte JNICALL CallNonvirtualByteMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jbyte JNICALL CallNonvirtualByteMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jbyte JNICALL CallNonvirtualByteMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jchar JNICALL CallNonvirtualCharMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jchar JNICALL CallNonvirtualCharMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jchar JNICALL CallNonvirtualCharMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jshort JNICALL CallNonvirtualShortMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jshort JNICALL CallNonvirtualShortMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jshort JNICALL CallNonvirtualShortMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jint JNICALL CallNonvirtualIntMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jint JNICALL CallNonvirtualIntMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jint JNICALL CallNonvirtualIntMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jlong JNICALL CallNonvirtualLongMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jlong JNICALL CallNonvirtualLongMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jlong JNICALL CallNonvirtualLongMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jfloat JNICALL CallNonvirtualFloatMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jfloat JNICALL CallNonvirtualFloatMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jfloat JNICALL CallNonvirtualFloatMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jdouble JNICALL CallNonvirtualDoubleMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual jdouble JNICALL CallNonvirtualDoubleMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual jdouble JNICALL CallNonvirtualDoubleMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual void JNICALL CallNonvirtualVoidMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
	virtual void JNICALL CallNonvirtualVoidMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
	virtual void JNICALL CallNonvirtualVoidMethodA(jobject obj, jclass clazz, jmethodID methodID, const jvalue * args);
	
	virtual jfieldID JNICALL GetFieldID(jclass clazz, const char *name, const char *sig);
	
	virtual jobject JNICALL GetObjectField(jobject obj, jfieldID fieldID);
	virtual jboolean JNICALL GetBooleanField(jobject obj, jfieldID fieldID);
	virtual jbyte JNICALL GetByteField(jobject obj, jfieldID fieldID);
	virtual jchar JNICALL GetCharField(jobject obj, jfieldID fieldID);
	virtual jshort JNICALL GetShortField(jobject obj, jfieldID fieldID);
	virtual jint JNICALL GetIntField(jobject obj, jfieldID fieldID);
	virtual jlong JNICALL GetLongField(jobject obj, jfieldID fieldID);
	virtual jfloat JNICALL GetFloatField(jobject obj, jfieldID fieldID);
	virtual jdouble JNICALL GetDoubleField(jobject obj, jfieldID fieldID);
	
	virtual void JNICALL SetObjectField(jobject obj, jfieldID fieldID, jobject val);
	virtual void JNICALL SetBooleanField(jobject obj, jfieldID fieldID, jboolean val);
	virtual void JNICALL SetByteField(jobject obj, jfieldID fieldID, jbyte val);
	virtual void JNICALL SetCharField(jobject obj, jfieldID fieldID, jchar val);
	virtual void JNICALL SetShortField(jobject obj, jfieldID fieldID, jshort val);
	virtual void JNICALL SetIntField(jobject obj, jfieldID fieldID, jint val);
	virtual void JNICALL SetLongField(jobject obj, jfieldID fieldID, jlong val);
	virtual void JNICALL SetFloatField(jobject obj, jfieldID fieldID, jfloat val);
	virtual void JNICALL SetDoubleField(jobject obj, jfieldID fieldID, jdouble val);
	
	virtual jmethodID JNICALL GetStaticMethodID(jclass clazz, const char *name, const char *sig);
	
	virtual jobject JNICALL CallStaticObjectMethod(jclass clazz, jmethodID methodID, ...);
	virtual jobject JNICALL CallStaticObjectMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jobject JNICALL CallStaticObjectMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jboolean JNICALL CallStaticBooleanMethod(jclass clazz, jmethodID methodID, ...);
	virtual jboolean JNICALL CallStaticBooleanMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jboolean JNICALL CallStaticBooleanMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jbyte JNICALL CallStaticByteMethod(jclass clazz, jmethodID methodID, ...);
	virtual jbyte JNICALL CallStaticByteMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jbyte JNICALL CallStaticByteMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jchar JNICALL CallStaticCharMethod(jclass clazz, jmethodID methodID, ...);
	virtual jchar JNICALL CallStaticCharMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jchar JNICALL CallStaticCharMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jshort JNICALL CallStaticShortMethod(jclass clazz, jmethodID methodID, ...);
	virtual jshort JNICALL CallStaticShortMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jshort JNICALL CallStaticShortMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jint JNICALL CallStaticIntMethod(jclass clazz, jmethodID methodID, ...);
	virtual jint JNICALL CallStaticIntMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jint JNICALL CallStaticIntMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jlong JNICALL CallStaticLongMethod(jclass clazz, jmethodID methodID, ...);
	virtual jlong JNICALL CallStaticLongMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jlong JNICALL CallStaticLongMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jfloat JNICALL CallStaticFloatMethod(jclass clazz, jmethodID methodID, ...);
	virtual jfloat JNICALL CallStaticFloatMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jfloat JNICALL CallStaticFloatMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual jdouble JNICALL CallStaticDoubleMethod(jclass clazz, jmethodID methodID, ...);
	virtual jdouble JNICALL CallStaticDoubleMethodV(jclass clazz, jmethodID methodID, va_list args);
	virtual jdouble JNICALL CallStaticDoubleMethodA(jclass clazz, jmethodID methodID, const jvalue *args);
	
	virtual void JNICALL CallStaticVoidMethod(jclass cls, jmethodID methodID, ...);
	virtual void JNICALL CallStaticVoidMethodV(jclass cls, jmethodID methodID, va_list args);
	virtual void JNICALL CallStaticVoidMethodA(jclass cls, jmethodID methodID, const jvalue * args);
	
	virtual jfieldID JNICALL GetStaticFieldID(jclass clazz, const char *name, const char *sig);
	virtual jobject JNICALL GetStaticObjectField(jclass clazz, jfieldID fieldID);
	virtual jboolean JNICALL GetStaticBooleanField(jclass clazz, jfieldID fieldID);
	virtual jbyte JNICALL GetStaticByteField(jclass clazz, jfieldID fieldID);
	virtual jchar JNICALL GetStaticCharField(jclass clazz, jfieldID fieldID);
	virtual jshort JNICALL GetStaticShortField(jclass clazz, jfieldID fieldID);
	virtual jint JNICALL GetStaticIntField(jclass clazz, jfieldID fieldID);
	virtual jlong JNICALL GetStaticLongField(jclass clazz, jfieldID fieldID);
	virtual jfloat JNICALL GetStaticFloatField(jclass clazz, jfieldID fieldID);
	virtual jdouble JNICALL GetStaticDoubleField(jclass clazz, jfieldID fieldID);
	
	virtual void JNICALL SetStaticObjectField(jclass clazz, jfieldID fieldID, jobject value);
	virtual void JNICALL SetStaticBooleanField(jclass clazz, jfieldID fieldID, jboolean value);
	virtual void JNICALL SetStaticByteField(jclass clazz, jfieldID fieldID, jbyte value);
	virtual void JNICALL SetStaticCharField(jclass clazz, jfieldID fieldID, jchar value);
	virtual void JNICALL SetStaticShortField(jclass clazz, jfieldID fieldID, jshort value);
	virtual void JNICALL SetStaticIntField(jclass clazz, jfieldID fieldID, jint value);
	virtual void JNICALL SetStaticLongField(jclass clazz, jfieldID fieldID, jlong value);
	virtual void JNICALL SetStaticFloatField(jclass clazz, jfieldID fieldID, jfloat value);
	virtual void JNICALL SetStaticDoubleField(jclass clazz, jfieldID fieldID, jdouble value);
	
	virtual jstring JNICALL NewString(const jchar *unicode, jsize len);
	virtual jsize JNICALL GetStringLength(jstring str);
	virtual const jchar *JNICALL GetStringChars(jstring str, jboolean *isCopy);
	virtual void JNICALL ReleaseStringChars(jstring str, const jchar *chars);
	
	virtual jstring JNICALL NewStringUTF(const char *utf);
	virtual jsize JNICALL GetStringUTFLength(jstring str);
	virtual const char* JNICALL GetStringUTFChars(jstring str, jboolean *isCopy);
	virtual void JNICALL ReleaseStringUTFChars(jstring str, const char* chars);
	
	virtual jsize JNICALL GetArrayLength(jarray _array);
	
	virtual jobjectArray JNICALL NewObjectArray(jsize len, jclass clazz, jobject init);
	virtual jobject JNICALL GetObjectArrayElement(jobjectArray _array, jsize index);
	virtual void JNICALL SetObjectArrayElement(jobjectArray _array, jsize index, jobject val);
	
	virtual jbooleanArray JNICALL NewBooleanArray(jsize len);
	virtual jbyteArray JNICALL NewByteArray(jsize len);
	virtual jcharArray JNICALL NewCharArray(jsize len);
	virtual jshortArray JNICALL NewShortArray(jsize len);
	virtual jintArray JNICALL NewIntArray(jsize len);
	virtual jlongArray JNICALL NewLongArray(jsize len);
	virtual jfloatArray JNICALL NewFloatArray(jsize len);
	virtual jdoubleArray JNICALL NewDoubleArray(jsize len);
	
	virtual jboolean* JNICALL GetBooleanArrayElements(jbooleanArray _array, jboolean *isCopy);
	virtual jbyte* JNICALL GetByteArrayElements(jbyteArray _array, jboolean *isCopy);
	virtual jchar* JNICALL GetCharArrayElements(jcharArray _array, jboolean *isCopy);
	virtual jshort* JNICALL GetShortArrayElements(jshortArray _array, jboolean *isCopy);
	virtual jint* JNICALL GetIntArrayElements(jintArray _array, jboolean *isCopy);
	virtual jlong* JNICALL GetLongArrayElements(jlongArray _array, jboolean *isCopy);
	virtual jfloat* JNICALL GetFloatArrayElements(jfloatArray _array, jboolean *isCopy);
	virtual jdouble* JNICALL GetDoubleArrayElements(jdoubleArray _array, jboolean *isCopy);
	
	virtual void JNICALL ReleaseBooleanArrayElements(jbooleanArray _array, jboolean *elems, jint mode);
	virtual void JNICALL ReleaseByteArrayElements(jbyteArray _array, jbyte *elems, jint mode);
	virtual void JNICALL ReleaseCharArrayElements(jcharArray _array, jchar *elems, jint mode);
	virtual void JNICALL ReleaseShortArrayElements(jshortArray _array, jshort *elems, jint mode);
	virtual void JNICALL ReleaseIntArrayElements(jintArray _array, jint *elems, jint mode);
	virtual void JNICALL ReleaseLongArrayElements(jlongArray _array, jlong *elems, jint mode);
	virtual void JNICALL ReleaseFloatArrayElements(jfloatArray _array, jfloat *elems, jint mode);
	virtual void JNICALL ReleaseDoubleArrayElements(jdoubleArray _array, jdouble *elems, jint mode);
	
	virtual void JNICALL GetBooleanArrayRegion(jbooleanArray _array, jsize start, jsize l, jboolean *buf);
	virtual void JNICALL GetByteArrayRegion(jbyteArray _array, jsize start, jsize len, jbyte *buf);
	virtual void JNICALL GetCharArrayRegion(jcharArray _array, jsize start, jsize len, jchar *buf);
	virtual void JNICALL GetShortArrayRegion(jshortArray _array, jsize start, jsize len, jshort *buf);
	virtual void JNICALL GetIntArrayRegion(jintArray _array, jsize start, jsize len, jint *buf);
	virtual void JNICALL GetLongArrayRegion(jlongArray _array, jsize start, jsize len, jlong *buf);
	virtual void JNICALL GetFloatArrayRegion(jfloatArray _array, jsize start, jsize len, jfloat *buf);
	virtual void JNICALL GetDoubleArrayRegion(jdoubleArray _array, jsize start, jsize len, jdouble *buf);
	
	virtual void JNICALL SetBooleanArrayRegion(jbooleanArray _array, jsize start, jsize l, const jboolean *buf);
	virtual void JNICALL SetByteArrayRegion(jbyteArray _array, jsize start, jsize len, const jbyte *buf);
	virtual void JNICALL SetCharArrayRegion(jcharArray _array, jsize start, jsize len, const jchar *buf);
	virtual void JNICALL SetShortArrayRegion(jshortArray _array, jsize start, jsize len, const jshort *buf);
	virtual void JNICALL SetIntArrayRegion(jintArray _array, jsize start, jsize len, const jint *buf);
	virtual void JNICALL SetLongArrayRegion(jlongArray _array, jsize start, jsize len, const jlong *buf);
	virtual void JNICALL SetFloatArrayRegion(jfloatArray _array, jsize start, jsize len, const jfloat *buf);
	virtual void JNICALL SetDoubleArrayRegion(jdoubleArray _array, jsize start, jsize len, const jdouble *buf);
	
	virtual jint JNICALL RegisterNatives(jclass clazz, const JNINativeMethod *methods, jint nMethods);
	virtual jint JNICALL UnregisterNatives(jclass clazz);
	
	virtual jint JNICALL MonitorEnter(jobject obj);
	virtual jint JNICALL MonitorExit(jobject obj);
	
	virtual jint JNICALL GetJavaVM(void/*JavaVM*/ **vm);
	
	virtual void JNICALL GetStringRegion(jstring str, jsize start, jsize len, jchar *buf);
	virtual void JNICALL GetStringUTFRegion(jstring str, jsize start, jsize len, char *buf);
	
	virtual void* JNICALL GetPrimitiveArrayCritical(jarray _array, jboolean *isCopy);
	virtual void JNICALL ReleasePrimitiveArrayCritical(jarray _array, void *carray, jint mode);
	
	virtual const jchar* JNICALL GetStringCritical(jstring string, jboolean *isCopy);
	virtual void JNICALL ReleaseStringCritical(jstring string, const jchar *cstring);
	
	virtual jweak JNICALL NewWeakGlobalRef(jobject obj);
	virtual void JNICALL DeleteWeakGlobalRef(jweak ref);
	
	virtual jboolean JNICALL ExceptionCheck();
	
	virtual jobject JNICALL NewDirectByteBuffer(void* address, jlong capacity);
	virtual void* JNICALL GetDirectBufferAddress(jobject buf);
	virtual jlong JNICALL GetDirectBufferCapacity(jobject buf);

	jstring NewString(string_data<WCHAR> strdata);
	jstring NewString(const WCHAR* cstr);

	Thread* m_pThread;
};

class javavmext Frame
{
public:
	CTOR Frame()
	{
		m_pMethod = NULL;
		m_pCode = NULL;
		m_pCaller = NULL;
		m_localVariables = NULL;
		m_returnAddress = NULL;
	}

	CTOR Frame(JavaMethod* pMethod, CodeAttribute* pCode);
	CTOR Frame(JavaMethod* pMethod, CodeAttribute* pCode, Frame* pCaller, uint8* returnAddress);

	JavaMethod* m_pMethod;
	CodeAttribute* m_pCode;

	Frame* m_pCaller;
	uint8* m_returnAddress;

	LocalVariable* m_localVariables;
	vector<Operand> m_operands;

//	Operand* top;
//	uint8* pc;

//	JavaClass* m_pJavaClass;

	void push(Operand value);
	Operand pop();

	inline int16 getword(uint8* & pc)
	{
		int16 value = (*pc++)<<8;
		value |= (*pc++);
		return value;
	}

	inline int32 getlong(uint8* & pc)
	{
		int32 value = (*pc++)<<24;
		value |= (*pc++)<<16;
		value |= (*pc++)<<8;
		value |= (*pc++);
		return value;
	}

	JavaMethod* GetMethod(Thread* c, uint16 methodIndex);

	typedef uint8* (Frame::*tyfunc)(Thread* c, uint8* pc);

	static tyfunc funcs[256];

	uint8* jop_notimpl(Thread* c, uint8* pc);
	uint8* jop_nop(Thread* c, uint8* pc);
	uint8* jop_lcmp(Thread* c, uint8* pc);
	uint8* jop_fcmpl(Thread* c, uint8* pc);
	uint8* jop_fcmpg(Thread* c, uint8* pc);
	uint8* jop_dcmpl(Thread* c, uint8* pc);
	uint8* jop_dcmpg(Thread* c, uint8* pc);
	uint8* jop_ifnull(Thread* c, uint8* pc);
	uint8* jop_ifnonnull(Thread* c, uint8* pc);
	uint8* jop_ifeq(Thread* c, uint8* pc);
	uint8* jop_ifne(Thread* c, uint8* pc);
	uint8* jop_iflt(Thread* c, uint8* pc);
	uint8* jop_ifge(Thread* c, uint8* pc);
	uint8* jop_ifgt(Thread* c, uint8* pc);
	uint8* jop_ifle(Thread* c, uint8* pc);
	uint8* jop_lconst_0(Thread* c, uint8* pc);
	uint8* jop_lconst_1(Thread* c, uint8* pc);
	uint8* jop_aconst_null(Thread* c, uint8* pc);
	uint8* jop_fconst_0(Thread* c, uint8* pc);
	uint8* jop_fconst_1(Thread* c, uint8* pc);
	uint8* jop_fconst_2(Thread* c, uint8* pc);
	uint8* jop_dconst_0(Thread* c, uint8* pc);
	uint8* jop_dconst_1(Thread* c, uint8* pc);
	uint8* jop_iconst_m1(Thread* c, uint8* pc);	// minus 1
	uint8* jop_iconst_0(Thread* c, uint8* pc);
	uint8* jop_iconst_1(Thread* c, uint8* pc);
	uint8* jop_iconst_2(Thread* c, uint8* pc);
	uint8* jop_iconst_3(Thread* c, uint8* pc);
	uint8* jop_iconst_4(Thread* c, uint8* pc);
	uint8* jop_iconst_5(Thread* c, uint8* pc);
	uint8* jop_istore(Thread* c, uint8* pc);
	uint8* jop_lstore(Thread* c, uint8* pc);
	uint8* jop_istore_0(Thread* c, uint8* pc);
	uint8* jop_istore_1(Thread* c, uint8* pc);
	uint8* jop_istore_2(Thread* c, uint8* pc);
	uint8* jop_istore_3(Thread* c, uint8* pc);
	uint8* jop_lstore_0(Thread* c, uint8* pc);
	uint8* jop_lstore_1(Thread* c, uint8* pc);
	uint8* jop_lstore_2(Thread* c, uint8* pc);
	uint8* jop_lstore_3(Thread* c, uint8* pc);
	uint8* jop_astore(Thread* c, uint8* pc);
	uint8* jop_astore_0(Thread* c, uint8* pc);
	uint8* jop_astore_1(Thread* c, uint8* pc);
	uint8* jop_astore_2(Thread* c, uint8* pc);
	uint8* jop_astore_3(Thread* c, uint8* pc);
	uint8* jop_iload(Thread* c, uint8* pc);
	uint8* jop_lload(Thread* c, uint8* pc);
	uint8* jop_iload_0(Thread* c, uint8* pc);
	uint8* jop_iload_1(Thread* c, uint8* pc);
	uint8* jop_iload_2(Thread* c, uint8* pc);
	uint8* jop_iload_3(Thread* c, uint8* pc);
	uint8* jop_lload_0(Thread* c, uint8* pc);
	uint8* jop_lload_1(Thread* c, uint8* pc);
	uint8* jop_lload_2(Thread* c, uint8* pc);
	uint8* jop_lload_3(Thread* c, uint8* pc);
	uint8* jop_caload(Thread* c, uint8* pc);
	uint8* jop_iaload(Thread* c, uint8* pc);
	uint8* jop_aaload(Thread* c, uint8* pc);
	uint8* jop_baload(Thread* c, uint8* pc);
	uint8* jop_castore(Thread* c, uint8* pc);
	uint8* jop_iastore(Thread* c, uint8* pc);
	uint8* jop_aastore(Thread* c, uint8* pc);
	uint8* jop_bastore(Thread* c, uint8* pc);
	uint8* jop_pop(Thread* c, uint8* pc);
	uint8* jop_pop2(Thread* c, uint8* pc);
	uint8* jop_dup(Thread* c, uint8* pc);
	uint8* jop_dup_x1(Thread* c, uint8* pc);
	uint8* jop_dup_x2(Thread* c, uint8* pc);
	uint8* jop_dup2(Thread* c, uint8* pc);
	uint8* jop_return(Thread* c, uint8* pc);
	uint8* jop_areturn(Thread* c, uint8* pc);
	uint8* jop_fload_0(Thread* c, uint8* pc);
	uint8* jop_fload_1(Thread* c, uint8* pc);
	uint8* jop_fload_2(Thread* c, uint8* pc);
	uint8* jop_fload_3(Thread* c, uint8* pc);
	uint8* jop_dload_0(Thread* c, uint8* pc);
	uint8* jop_dload_1(Thread* c, uint8* pc);
	uint8* jop_dload_2(Thread* c, uint8* pc);
	uint8* jop_dload_3(Thread* c, uint8* pc);
	uint8* jop_aload(Thread* c, uint8* pc);
	uint8* jop_aload_0(Thread* c, uint8* pc);
	uint8* jop_aload_1(Thread* c, uint8* pc);
	uint8* jop_aload_2(Thread* c, uint8* pc);
	uint8* jop_aload_3(Thread* c, uint8* pc);
	uint8* jop_iadd(Thread* c, uint8* pc);
	uint8* jop_ladd(Thread* c, uint8* pc);
	uint8* jop_isub(Thread* c, uint8* pc);
	uint8* jop_iand(Thread* c, uint8* pc);
	uint8* jop_land(Thread* c, uint8* pc);
	uint8* jop_ior(Thread* c, uint8* pc);
	uint8* jop_lor(Thread* c, uint8* pc);
	uint8* jop_ixor(Thread* c, uint8* pc);
	uint8* jop_ishl(Thread* c, uint8* pc);
	uint8* jop_ishr(Thread* c, uint8* pc);
	uint8* jop_iinc(Thread* c, uint8* pc);
	uint8* jop_ineg(Thread* c, uint8* pc);
	uint8* jop_imul(Thread* c, uint8* pc);
	uint8* jop_irem(Thread* c, uint8* pc);
	uint8* jop_fmul(Thread* c, uint8* pc);
	uint8* jop_idiv(Thread* c, uint8* pc);
	uint8* jop_f2d(Thread* c, uint8* pc);
	uint8* jop_i2f(Thread* c, uint8* pc);
	uint8* jop_i2c(Thread* c, uint8* pc);
	uint8* jop_i2b(Thread* c, uint8* pc);
	uint8* jop_i2l(Thread* c, uint8* pc);
	uint8* jop_f2i(Thread* c, uint8* pc);
	uint8* jop_invokevirtual(Thread* c, uint8* pc);
	uint8* jop_invokespecial(Thread* c, uint8* pc);
	uint8* jop_invokestatic(Thread* c, uint8* pc);
	uint8* jop_invokeinterface(Thread* c, uint8* pc);
	uint8* jop_getstatic(Thread* c, uint8* pc);
	uint8* jop_putstatic(Thread* c, uint8* pc);
	uint8* jop_getfield(Thread* c, uint8* pc);
	uint8* jop_putfield(Thread* c, uint8* pc);
	uint8* jop_ldc(Thread* c, uint8* pc);
	uint8* jop_ldc_w(Thread* c, uint8* pc);
	uint8* jop_ldc2_w(Thread* c, uint8* pc);
	uint8* jop_jsr(Thread* c, uint8* pc);
	uint8* jop_ret(Thread* c, uint8* pc);
	uint8* jop_new(Thread* c, uint8* pc);
	uint8* jop_newarray(Thread* c, uint8* pc);
	uint8* jop_anewarray(Thread* c, uint8* pc);
	uint8* jop_arraylength(Thread* c, uint8* pc);
	uint8* jop_if_icmpeq(Thread* c, uint8* pc);
	uint8* jop_if_icmpne(Thread* c, uint8* pc);
	uint8* jop_if_icmplt(Thread* c, uint8* pc);
	uint8* jop_if_icmpgt(Thread* c, uint8* pc);
	uint8* jop_if_icmple(Thread* c, uint8* pc);
	uint8* jop_if_icmpge(Thread* c, uint8* pc);
	uint8* jop_if_acmpeq(Thread* c, uint8* pc);
	uint8* jop_if_acmpne(Thread* c, uint8* pc);
	uint8* jop_bipush(Thread* c, uint8* pc);
	uint8* jop_sipush(Thread* c, uint8* pc);
	uint8* jop_ireturn(Thread* c, uint8* pc);
	uint8* jop_lreturn(Thread* c, uint8* pc);
	uint8* jop_freturn(Thread* c, uint8* pc);
	uint8* jop_tableswitch(Thread* c, uint8* pc);
	uint8* jop_lookupswitch(Thread* c, uint8* pc);
	uint8* jop_monitorenter(Thread* c, uint8* pc);
	uint8* jop_monitorexit(Thread* c, uint8* pc);
	uint8* jop_goto(Thread* c, uint8* pc);
	uint8* jop_checkcast(Thread* c, uint8* pc);
	uint8* jop_instanceof(Thread* c, uint8* pc);
	uint8* jop_athrow(Thread* c, uint8* pc);
	uint8* jop_iushr(Thread* c, uint8* pc);
	uint8* jop_breakpoint(Thread* c, uint8* pc);

	void astore(int n)
	{
		Operand operand = pop();
		if (operand.kind == 8)
		{
			m_localVariables[n] = (long)operand.u.address;
		}
		else if (operand.kind == 4)
		{
			m_localVariables[n] = operand.ref;
		}
		else
		{
			ASSERT(0);
			THROW(-1);
		}
	}
};

class javavmext Thread
{
public:
	CTOR Thread();

	int next_instruction();
	JavaClass* LoadClass(StringIn className);
	JavaObject* NewString(jchar *unicode, jsize len);

public:

	uint8* m_pc;
	Frame* m_pFrame;
	JavaObject* m_p;
	JProcess* m_vm;
	JNINativeInterface* m_jni;
};

interface IHost
{
	virtual void OnLoadedClass(JavaClass* pClass) = 0;
};

class javavmext JProcess
{
public:
	CTOR JProcess();
//	LoadClass(StringA className);
//	LinkClass();

//	JavaClass* m_pJavaClass;

	JavaObject* StringIntern(JavaObject* stringref);

	JavaClass* m_pObjectClass;
	JavaClass* m_pClassClass;
	JavaClass* m_pClassLoaderClass;
	JavaClass* m_pCloneableClass;
	JavaClass* m_pStringClass;

	void (*Breakpoint)(Thread* thread, int cause);

	map<String, JavaClass*> m_classes;
	vector<Thread*> m_threads;
	map<string_data<WCHAR>, JavaObject*> m_strings;

#ifdef __LERSTAD__
	typedef void (*RegisterNativesFunc)(JNIEnv*, JavaClass*);
#else
	typedef void (__stdcall *RegisterNativesFunc)(JNIEnv*, JavaClass*);
#endif

	map<String, RegisterNativesFunc> m_registerNatives;

	IHost* m_pHost;

	ULONG m_flags;

	void Init();
};

}	// JavaVM
}

#endif	// __JavaVM_Java_h__
