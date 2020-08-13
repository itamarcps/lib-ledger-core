// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from idl.djinni

#ifndef DJINNI_GENERATED_ALGORANDNETWORKPARAMETERS_HPP_JNI_
#define DJINNI_GENERATED_ALGORANDNETWORKPARAMETERS_HPP_JNI_

#include "../../api/AlgorandNetworkParameters.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class AlgorandNetworkParameters final {
public:
    using CppType = ::ledger::core::api::AlgorandNetworkParameters;
    using JniType = jobject;

    using Boxed = AlgorandNetworkParameters;

    ~AlgorandNetworkParameters();

    static CppType toCpp(JNIEnv* jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c);

private:
    AlgorandNetworkParameters();
    friend ::djinni::JniClass<AlgorandNetworkParameters>;

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("co/ledger/core/AlgorandNetworkParameters") };
    const jmethodID jconstructor { ::djinni::jniGetMethodID(clazz.get(), "<init>", "(Ljava/lang/String;Ljava/lang/String;)V") };
    const jfieldID field_genesisID { ::djinni::jniGetFieldID(clazz.get(), "genesisID", "Ljava/lang/String;") };
    const jfieldID field_genesisHash { ::djinni::jniGetFieldID(clazz.get(), "genesisHash", "Ljava/lang/String;") };
};

}  // namespace djinni_generated
#endif //DJINNI_GENERATED_ALGORANDNETWORKPARAMETERS_HPP_JNI_