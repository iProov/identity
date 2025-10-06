#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSString.h>
#import <Foundation/NSValue.h>

@class IdentityAccessControl, IdentityActiveAuthentication, IdentityActiveAuthenticationCompanion, IdentityApiClient, IdentityApiException, IdentityApiExceptionHttpError, IdentityApiExceptionNetworkError, IdentityApiExceptionSerializationError, IdentityApiExceptionTimeoutError, IdentityAppInfo, IdentityAppInfoCompanion, IdentityAppleKeyPairLocation, IdentityAssuranceType, IdentityAssuranceTypeCompanion, IdentityBacKey, IdentityBacKeyCompanion, IdentityByteArrayAsBase64Serializer, IdentityChallenge, IdentityClaim, IdentityClaimCompanion, IdentityCredential, IdentityCredentialCompanion, IdentityCredentialDeserializer, IdentityCredentialDeserializerCompanion, IdentityCredentialIdentityCredential, IdentityCredentialIdentityCredentialCompanion, IdentityCredentialIdentityCredentialMrtd, IdentityCredentialUriCredential, IdentityDataAsBase64Serializer, IdentityDeviceInfo, IdentityDeviceInfoCompanion, IdentityDocumentChallenge, IdentityDocumentChallengeCompanion, IdentityDocumentChallengeResponder, IdentityEllipticCurvePublicKey, IdentityEllipticCurvePublicKeyCompanion, IdentityFaceReverificationRequest, IdentityFlowWrapper<__covariant T>, IdentityFormat, IdentityGender, IdentityIdentityPlatformInterface, IdentityJwk, IdentityJwkCompanion, IdentityJwt, IdentityJwtCompanion, IdentityJwtVerificationStatus, IdentityJwtVerificationStatusExpired, IdentityJwtVerificationStatusInvalid, IdentityJwtVerificationStatusMalformed, IdentityJwtVerificationStatusNotVerified, IdentityJwtVerificationStatusUnsecured, IdentityJwtVerificationStatusValid, IdentityKotlinAbstractCoroutineContextElement, IdentityKotlinAbstractCoroutineContextKey<B, E>, IdentityKotlinArray<T>, IdentityKotlinBase64, IdentityKotlinBase64Default, IdentityKotlinBase64PaddingOption, IdentityKotlinByteArray, IdentityKotlinByteIterator, IdentityKotlinCancellationException, IdentityKotlinEnum<E>, IdentityKotlinEnumCompanion, IdentityKotlinException, IdentityKotlinIllegalStateException, IdentityKotlinKTypeProjection, IdentityKotlinKTypeProjectionCompanion, IdentityKotlinKVariance, IdentityKotlinNothing, IdentityKotlinRuntimeException, IdentityKotlinThrowable, IdentityKotlinTriple<__covariant A, __covariant B, __covariant C>, IdentityKotlinUnit, IdentityKotlinx_coroutines_coreCoroutineDispatcher, IdentityKotlinx_coroutines_coreCoroutineDispatcherKey, IdentityKotlinx_datetimeInstant, IdentityKotlinx_datetimeInstantCompanion, IdentityKotlinx_io_coreBuffer, IdentityKotlinx_serialization_coreSerialKind, IdentityKotlinx_serialization_coreSerializersModule, IdentityKotlinx_serialization_jsonJsonElement, IdentityKotlinx_serialization_jsonJsonElementCompanion, IdentityKtor_client_coreHttpClient, IdentityKtor_client_coreHttpClientCall, IdentityKtor_client_coreHttpClientCallCompanion, IdentityKtor_client_coreHttpClientConfig<T>, IdentityKtor_client_coreHttpClientEngineConfig, IdentityKtor_client_coreHttpReceivePipeline, IdentityKtor_client_coreHttpReceivePipelinePhases, IdentityKtor_client_coreHttpRequestBuilder, IdentityKtor_client_coreHttpRequestBuilderCompanion, IdentityKtor_client_coreHttpRequestData, IdentityKtor_client_coreHttpRequestPipeline, IdentityKtor_client_coreHttpRequestPipelinePhases, IdentityKtor_client_coreHttpResponse, IdentityKtor_client_coreHttpResponseContainer, IdentityKtor_client_coreHttpResponseData, IdentityKtor_client_coreHttpResponsePipeline, IdentityKtor_client_coreHttpResponsePipelinePhases, IdentityKtor_client_coreHttpSendPipeline, IdentityKtor_client_coreHttpSendPipelinePhases, IdentityKtor_client_coreProxyConfig, IdentityKtor_eventsEventDefinition<T>, IdentityKtor_eventsEvents, IdentityKtor_httpContentType, IdentityKtor_httpContentTypeCompanion, IdentityKtor_httpHeaderValueParam, IdentityKtor_httpHeaderValueWithParameters, IdentityKtor_httpHeaderValueWithParametersCompanion, IdentityKtor_httpHeadersBuilder, IdentityKtor_httpHttpMethod, IdentityKtor_httpHttpMethodCompanion, IdentityKtor_httpHttpProtocolVersion, IdentityKtor_httpHttpProtocolVersionCompanion, IdentityKtor_httpHttpStatusCode, IdentityKtor_httpHttpStatusCodeCompanion, IdentityKtor_httpOutgoingContent, IdentityKtor_httpURLBuilder, IdentityKtor_httpURLBuilderCompanion, IdentityKtor_httpURLProtocol, IdentityKtor_httpURLProtocolCompanion, IdentityKtor_httpUrl, IdentityKtor_httpUrlCompanion, IdentityKtor_utilsAttributeKey<T>, IdentityKtor_utilsGMTDate, IdentityKtor_utilsGMTDateCompanion, IdentityKtor_utilsMonth, IdentityKtor_utilsMonthCompanion, IdentityKtor_utilsPipeline<TSubject, TContext>, IdentityKtor_utilsPipelinePhase, IdentityKtor_utilsStringValuesBuilderImpl, IdentityKtor_utilsTypeInfo, IdentityKtor_utilsWeekDay, IdentityKtor_utilsWeekDayCompanion, IdentityLength, IdentityLocalStorage, IdentityLogLevel, IdentityLoginRequest, IdentityLoginRequestCompanion, IdentityLoginResponse, IdentityLoginResponseCompanion, IdentityMrtdCompanion, IdentityMrtdData, IdentityMrtdDataCompanion, IdentityMrzField, IdentityMrzFieldCompanion, IdentityPlatformTarget, IdentityRegisterAppleAttestationPayload, IdentityRegisterAppleAttestationPayloadCompanion, IdentityRegisterAppleWalletPayload, IdentityRegisterAppleWalletPayloadCompanion, IdentityRelyingParty, IdentityRelyingPartyCompanion, IdentityRepository, IdentityRequestedClaim, IdentityRespondableChallenge<T>, IdentityRespondableChallengeCompanion, IdentityRespondableLoginRequest, IdentityRespondableLoginRequestCompanion, IdentityReverificationRequest, IdentityReverificationRequestCompanion, IdentitySdkCamera, IdentitySdkIproovOptions, IdentitySdkIproovOptionsCertificate, IdentitySdkIproovOptionsCloseButton, IdentitySdkIproovOptionsFilter, IdentitySdkIproovOptionsGenuinePresenceAssurance, IdentitySdkIproovOptionsLivenessAssurance, IdentitySdkOrientation, IdentitySymmetricKey, IdentitySymmetricKeyCompanion, IdentityUriCredentialChallenge, IdentityUriCredentialChallengeResponder, IdentityUserAgent, IdentityUserAgentCompanion, IdentityVerificationEvent, IdentityVerificationEventCanceled, IdentityVerificationEventCompanion, IdentityVerificationEventCompleted, IdentityVerificationEventError, IdentityVerificationEventErrorCompanion, IdentityVerificationEventLoading, IdentityVerificationEventStarted, IdentityVerificationException, IdentityVerificationMethod, IdentityVerificationMethodCompanion, IdentityVerificationMethodIProov, IdentityVerificationMethodIProovCompanion, IdentityWallet, IdentityWalletCompanion, IdentityWalletFactory, NSData, NSDate, NSDictionary, NSError;

@protocol IdentityCredentialFactory, IdentityKeyPair, IdentityKotlinAnnotation, IdentityKotlinAppendable, IdentityKotlinAutoCloseable, IdentityKotlinComparable, IdentityKotlinContinuation, IdentityKotlinContinuationInterceptor, IdentityKotlinCoroutineContext, IdentityKotlinCoroutineContextElement, IdentityKotlinCoroutineContextKey, IdentityKotlinFunction, IdentityKotlinIterator, IdentityKotlinKAnnotatedElement, IdentityKotlinKClass, IdentityKotlinKClassifier, IdentityKotlinKDeclarationContainer, IdentityKotlinKType, IdentityKotlinMapEntry, IdentityKotlinSequence, IdentityKotlinSuspendFunction2, IdentityKotlinx_coroutines_coreChildHandle, IdentityKotlinx_coroutines_coreChildJob, IdentityKotlinx_coroutines_coreCoroutineScope, IdentityKotlinx_coroutines_coreDeferred, IdentityKotlinx_coroutines_coreDisposableHandle, IdentityKotlinx_coroutines_coreFlow, IdentityKotlinx_coroutines_coreFlowCollector, IdentityKotlinx_coroutines_coreJob, IdentityKotlinx_coroutines_coreParentJob, IdentityKotlinx_coroutines_coreRunnable, IdentityKotlinx_coroutines_coreSelectClause, IdentityKotlinx_coroutines_coreSelectClause0, IdentityKotlinx_coroutines_coreSelectClause1, IdentityKotlinx_coroutines_coreSelectInstance, IdentityKotlinx_datetimeDateTimeFormat, IdentityKotlinx_io_coreRawSink, IdentityKotlinx_io_coreRawSource, IdentityKotlinx_io_coreSink, IdentityKotlinx_io_coreSource, IdentityKotlinx_serialization_coreCompositeDecoder, IdentityKotlinx_serialization_coreCompositeEncoder, IdentityKotlinx_serialization_coreDecoder, IdentityKotlinx_serialization_coreDeserializationStrategy, IdentityKotlinx_serialization_coreEncoder, IdentityKotlinx_serialization_coreKSerializer, IdentityKotlinx_serialization_coreSerialDescriptor, IdentityKotlinx_serialization_coreSerializationStrategy, IdentityKotlinx_serialization_coreSerializersModuleCollector, IdentityKtor_client_coreHttpClientEngine, IdentityKtor_client_coreHttpClientEngineCapability, IdentityKtor_client_coreHttpClientPlugin, IdentityKtor_client_coreHttpRequest, IdentityKtor_httpHeaders, IdentityKtor_httpHttpMessage, IdentityKtor_httpHttpMessageBuilder, IdentityKtor_httpParameters, IdentityKtor_httpParametersBuilder, IdentityKtor_ioByteReadChannel, IdentityKtor_ioCloseable, IdentityKtor_ioJvmSerializable, IdentityKtor_utilsAttributes, IdentityKtor_utilsStringValues, IdentityKtor_utilsStringValuesBuilder, IdentityPlatform, IdentityStorageEngine, IdentitySyncedKeyValueStorage;

NS_ASSUME_NONNULL_BEGIN
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wincompatible-property-type"
#pragma clang diagnostic ignored "-Wnullability"

#pragma push_macro("_Nullable_result")
#if !__has_feature(nullability_nullable_result)
#undef _Nullable_result
#define _Nullable_result _Nullable
#endif

__attribute__((swift_name("KotlinBase")))
@interface IdentityBase : NSObject
- (instancetype)init __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
+ (void)initialize __attribute__((objc_requires_super));
@end

@interface IdentityBase (IdentityBaseCopying) <NSCopying>
@end

__attribute__((swift_name("KotlinMutableSet")))
@interface IdentityMutableSet<ObjectType> : NSMutableSet<ObjectType>
@end

__attribute__((swift_name("KotlinMutableDictionary")))
@interface IdentityMutableDictionary<KeyType, ObjectType> : NSMutableDictionary<KeyType, ObjectType>
@end

@interface NSError (NSErrorIdentityKotlinException)
@property (readonly) id _Nullable kotlinException;
@end

__attribute__((swift_name("KotlinNumber")))
@interface IdentityNumber : NSNumber
- (instancetype)initWithChar:(char)value __attribute__((unavailable));
- (instancetype)initWithUnsignedChar:(unsigned char)value __attribute__((unavailable));
- (instancetype)initWithShort:(short)value __attribute__((unavailable));
- (instancetype)initWithUnsignedShort:(unsigned short)value __attribute__((unavailable));
- (instancetype)initWithInt:(int)value __attribute__((unavailable));
- (instancetype)initWithUnsignedInt:(unsigned int)value __attribute__((unavailable));
- (instancetype)initWithLong:(long)value __attribute__((unavailable));
- (instancetype)initWithUnsignedLong:(unsigned long)value __attribute__((unavailable));
- (instancetype)initWithLongLong:(long long)value __attribute__((unavailable));
- (instancetype)initWithUnsignedLongLong:(unsigned long long)value __attribute__((unavailable));
- (instancetype)initWithFloat:(float)value __attribute__((unavailable));
- (instancetype)initWithDouble:(double)value __attribute__((unavailable));
- (instancetype)initWithBool:(BOOL)value __attribute__((unavailable));
- (instancetype)initWithInteger:(NSInteger)value __attribute__((unavailable));
- (instancetype)initWithUnsignedInteger:(NSUInteger)value __attribute__((unavailable));
+ (instancetype)numberWithChar:(char)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedChar:(unsigned char)value __attribute__((unavailable));
+ (instancetype)numberWithShort:(short)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedShort:(unsigned short)value __attribute__((unavailable));
+ (instancetype)numberWithInt:(int)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedInt:(unsigned int)value __attribute__((unavailable));
+ (instancetype)numberWithLong:(long)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedLong:(unsigned long)value __attribute__((unavailable));
+ (instancetype)numberWithLongLong:(long long)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedLongLong:(unsigned long long)value __attribute__((unavailable));
+ (instancetype)numberWithFloat:(float)value __attribute__((unavailable));
+ (instancetype)numberWithDouble:(double)value __attribute__((unavailable));
+ (instancetype)numberWithBool:(BOOL)value __attribute__((unavailable));
+ (instancetype)numberWithInteger:(NSInteger)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedInteger:(NSUInteger)value __attribute__((unavailable));
@end

__attribute__((swift_name("KotlinByte")))
@interface IdentityByte : IdentityNumber
- (instancetype)initWithChar:(char)value;
+ (instancetype)numberWithChar:(char)value;
@end

__attribute__((swift_name("KotlinUByte")))
@interface IdentityUByte : IdentityNumber
- (instancetype)initWithUnsignedChar:(unsigned char)value;
+ (instancetype)numberWithUnsignedChar:(unsigned char)value;
@end

__attribute__((swift_name("KotlinShort")))
@interface IdentityShort : IdentityNumber
- (instancetype)initWithShort:(short)value;
+ (instancetype)numberWithShort:(short)value;
@end

__attribute__((swift_name("KotlinUShort")))
@interface IdentityUShort : IdentityNumber
- (instancetype)initWithUnsignedShort:(unsigned short)value;
+ (instancetype)numberWithUnsignedShort:(unsigned short)value;
@end

__attribute__((swift_name("KotlinInt")))
@interface IdentityInt : IdentityNumber
- (instancetype)initWithInt:(int)value;
+ (instancetype)numberWithInt:(int)value;
@end

__attribute__((swift_name("KotlinUInt")))
@interface IdentityUInt : IdentityNumber
- (instancetype)initWithUnsignedInt:(unsigned int)value;
+ (instancetype)numberWithUnsignedInt:(unsigned int)value;
@end

__attribute__((swift_name("KotlinLong")))
@interface IdentityLong : IdentityNumber
- (instancetype)initWithLongLong:(long long)value;
+ (instancetype)numberWithLongLong:(long long)value;
@end

__attribute__((swift_name("KotlinULong")))
@interface IdentityULong : IdentityNumber
- (instancetype)initWithUnsignedLongLong:(unsigned long long)value;
+ (instancetype)numberWithUnsignedLongLong:(unsigned long long)value;
@end

__attribute__((swift_name("KotlinFloat")))
@interface IdentityFloat : IdentityNumber
- (instancetype)initWithFloat:(float)value;
+ (instancetype)numberWithFloat:(float)value;
@end

__attribute__((swift_name("KotlinDouble")))
@interface IdentityDouble : IdentityNumber
- (instancetype)initWithDouble:(double)value;
+ (instancetype)numberWithDouble:(double)value;
@end

__attribute__((swift_name("KotlinBoolean")))
@interface IdentityBoolean : IdentityNumber
- (instancetype)initWithBool:(BOOL)value;
+ (instancetype)numberWithBool:(BOOL)value;
@end

__attribute__((swift_name("KotlinThrowable")))
@interface IdentityKotlinThrowable : IdentityBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));

/**
 * @note annotations
 *   kotlin.experimental.ExperimentalNativeApi
*/
- (IdentityKotlinArray<NSString *> *)getStackTrace __attribute__((swift_name("getStackTrace()")));
- (void)printStackTrace __attribute__((swift_name("printStackTrace()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) IdentityKotlinThrowable * _Nullable cause __attribute__((swift_name("cause")));
@property (readonly) NSString * _Nullable message __attribute__((swift_name("message")));
- (NSError *)asError __attribute__((swift_name("asError()")));
@end

__attribute__((swift_name("KotlinException")))
@interface IdentityKotlinException : IdentityKotlinThrowable
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppIdNotSupportedException")))
@interface IdentityAppIdNotSupportedException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppInfo")))
@interface IdentityAppInfo : IdentityBase
- (instancetype)initWithClient:(NSString *)client version:(NSString *)version __attribute__((swift_name("init(client:version:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityAppInfoCompanion *companion __attribute__((swift_name("companion")));
- (IdentityAppInfo *)doCopyClient:(NSString *)client version:(NSString *)version __attribute__((swift_name("doCopy(client:version:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *client __attribute__((swift_name("client")));
@property (readonly) NSString *version __attribute__((swift_name("version")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppInfo.Companion")))
@interface IdentityAppInfoCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityAppInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((swift_name("Platform")))
@protocol IdentityPlatform
@required
@property (readonly) IdentityAppInfo *appInfo __attribute__((swift_name("appInfo")));
@property (readonly) IdentityDeviceInfo *deviceInfo __attribute__((swift_name("deviceInfo")));
@property (readonly) IdentityPlatformTarget *target __attribute__((swift_name("target")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ApplePlatform")))
@interface IdentityApplePlatform : IdentityBase <IdentityPlatform>
- (instancetype)initWithInstanceId:(NSString *)instanceId __attribute__((swift_name("init(instanceId:)"))) __attribute__((objc_designated_initializer));
@property (readonly) IdentityAppInfo *appInfo __attribute__((swift_name("appInfo")));
@property (readonly) IdentityDeviceInfo *deviceInfo __attribute__((swift_name("deviceInfo")));
@property (readonly) IdentityPlatformTarget *target __attribute__((swift_name("target")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("CredentialAlreadyExistsException")))
@interface IdentityCredentialAlreadyExistsException : IdentityKotlinException
- (instancetype)initWithSource:(NSString *)source __attribute__((swift_name("init(source:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("CredentialNotFoundException")))
@interface IdentityCredentialNotFoundException : IdentityKotlinException
- (instancetype)initWithId:(NSString *)id __attribute__((swift_name("init(id:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DeviceInfo")))
@interface IdentityDeviceInfo : IdentityBase
- (instancetype)initWithManufacturer:(NSString *)manufacturer model:(NSString *)model os:(NSString *)os osversion:(NSString *)osversion instanceId:(NSString *)instanceId __attribute__((swift_name("init(manufacturer:model:os:osversion:instanceId:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityDeviceInfoCompanion *companion __attribute__((swift_name("companion")));
- (IdentityDeviceInfo *)doCopyManufacturer:(NSString *)manufacturer model:(NSString *)model os:(NSString *)os osversion:(NSString *)osversion instanceId:(NSString *)instanceId __attribute__((swift_name("doCopy(manufacturer:model:os:osversion:instanceId:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="id")
*/
@property (readonly) NSString *instanceId __attribute__((swift_name("instanceId")));
@property (readonly) NSString *manufacturer __attribute__((swift_name("manufacturer")));
@property (readonly) NSString *model __attribute__((swift_name("model")));
@property (readonly) NSString *os __attribute__((swift_name("os")));
@property (readonly) NSString *osversion __attribute__((swift_name("osversion")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DeviceInfo.Companion")))
@interface IdentityDeviceInfoCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityDeviceInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("FlowWrapper")))
@interface IdentityFlowWrapper<__covariant T> : IdentityBase

/**
 *  Cancels the flow
 */
- (void)cancel __attribute__((swift_name("cancel()")));

/**
 * Starts the flow
 * @param onEach callback called on each emission
 * @param onError callback called when flow completes. It will be provided with a non
 * nullable Throwable if it completes abnormally
 */
- (void)collectOnEach:(void (^)(T _Nullable))onEach onError:(void (^)(NSError *))onError __attribute__((swift_name("collect(onEach:onError:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("InvalidAppException")))
@interface IdentityInvalidAppException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("InvalidOpenIdServerConfiguration")))
@interface IdentityInvalidOpenIdServerConfiguration : IdentityKotlinException
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((swift_name("KotlinComparable")))
@protocol IdentityKotlinComparable
@required
- (int32_t)compareToOther:(id _Nullable)other __attribute__((swift_name("compareTo(other:)")));
@end

__attribute__((swift_name("KotlinEnum")))
@interface IdentityKotlinEnum<E> : IdentityBase <IdentityKotlinComparable>
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKotlinEnumCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(E)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) int32_t ordinal __attribute__((swift_name("ordinal")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("LogLevel")))
@interface IdentityLogLevel : IdentityKotlinEnum<IdentityLogLevel *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentityLogLevel *debug __attribute__((swift_name("debug")));
@property (class, readonly) IdentityLogLevel *info __attribute__((swift_name("info")));
@property (class, readonly) IdentityLogLevel *error __attribute__((swift_name("error")));
@property (class, readonly) IdentityLogLevel *none __attribute__((swift_name("none")));
+ (IdentityKotlinArray<IdentityLogLevel *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityLogLevel *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PlatformTarget")))
@interface IdentityPlatformTarget : IdentityKotlinEnum<IdentityPlatformTarget *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentityPlatformTarget *ios __attribute__((swift_name("ios")));
@property (class, readonly) IdentityPlatformTarget *android __attribute__((swift_name("android")));
+ (IdentityKotlinArray<IdentityPlatformTarget *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityPlatformTarget *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RequiredClaimNotPresent")))
@interface IdentityRequiredClaimNotPresent : IdentityKotlinException
- (instancetype)initWithClaimName:(NSString *)claimName message:(NSString *)message __attribute__((swift_name("init(claimName:message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (readonly) NSString *claimName __attribute__((swift_name("claimName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UnsupportedVerificationMethodException")))
@interface IdentityUnsupportedVerificationMethodException : IdentityKotlinException
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((swift_name("VerificationEvent")))
@interface IdentityVerificationEvent : IdentityBase
@property (class, readonly, getter=companion) IdentityVerificationEventCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)toJsonString __attribute__((swift_name("toJsonString()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
 *   kotlinx.serialization.SerialName(value="cancelled")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationEvent.Canceled")))
@interface IdentityVerificationEventCanceled : IdentityVerificationEvent
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)canceled __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityVerificationEventCanceled *shared __attribute__((swift_name("shared")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(IdentityKotlinArray<id<IdentityKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationEvent.Companion")))
@interface IdentityVerificationEventCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityVerificationEventCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(IdentityKotlinArray<id<IdentityKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
 *   kotlinx.serialization.SerialName(value="completed")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationEvent.Completed")))
@interface IdentityVerificationEventCompleted : IdentityVerificationEvent
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)completed __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityVerificationEventCompleted *shared __attribute__((swift_name("shared")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(IdentityKotlinArray<id<IdentityKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
 *   kotlinx.serialization.SerialName(value="error")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationEvent.Error")))
@interface IdentityVerificationEventError : IdentityVerificationEvent
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityVerificationEventErrorCompanion *companion __attribute__((swift_name("companion")));
- (IdentityVerificationEventError *)doCopyMessage:(NSString *)message __attribute__((swift_name("doCopy(message:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *message __attribute__((swift_name("message")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationEvent.ErrorCompanion")))
@interface IdentityVerificationEventErrorCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityVerificationEventErrorCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
 *   kotlinx.serialization.SerialName(value="loading")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationEvent.Loading")))
@interface IdentityVerificationEventLoading : IdentityVerificationEvent
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)loading __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityVerificationEventLoading *shared __attribute__((swift_name("shared")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(IdentityKotlinArray<id<IdentityKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
 *   kotlinx.serialization.SerialName(value="started")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationEvent.Started")))
@interface IdentityVerificationEventStarted : IdentityVerificationEvent
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)started __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityVerificationEventStarted *shared __attribute__((swift_name("shared")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(IdentityKotlinArray<id<IdentityKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Wallet")))
@interface IdentityWallet : IdentityBase
@property (class, readonly, getter=companion) IdentityWalletCompanion *companion __attribute__((swift_name("companion")));

/**
 * Add a document with fields
 * @param documentNumber
 * @param dateOfExpiry Expiration date of the document in DDMMYY format
 * @param dateOfBirth Date of birth on the document in DDMMYY format
 *
 * @note This method converts instances of WalletNotRegisteredException, ApiException, CancellationException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)addDocumentWithFieldsDocumentNumber:(NSString *)documentNumber dateOfBirth:(NSString *)dateOfBirth dateOfExpiry:(NSString *)dateOfExpiry loginRequest:(IdentityLoginRequest * _Nullable)loginRequest completionHandler:(void (^)(IdentityDocumentChallenge * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("addDocumentWithFields(documentNumber:dateOfBirth:dateOfExpiry:loginRequest:completionHandler:)")));

/**
 * @note This method converts instances of WalletNotRegisteredException, ApiException, CancellationException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)addDocumentWithMrzMrz:(NSString *)mrz loginRequest:(IdentityLoginRequest * _Nullable)loginRequest completionHandler:(void (^)(IdentityDocumentChallenge * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("addDocumentWithMrz(mrz:loginRequest:completionHandler:)")));

/**
 * @note This method converts instances of WalletNotRegisteredException, CancellationException, ApiException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)addUriCredentialUri:(NSString *)uri completionHandler:(void (^)(IdentityUriCredentialChallenge * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("addUriCredential(uri:completionHandler:)")));

/**
 * @note This method converts instances of WalletNotRegisteredException, ApiException, CancellationException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)createDemoMrtdWithCompletionHandler:(void (^)(IdentityMrtdData * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("createDemoMrtd(completionHandler:)")));

/**
 * @note This method converts instances of WalletNotRegisteredException, AttestationNotSupportedException, StorageException, KeyPairException, CancellationException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)deleteWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("delete(completionHandler:)")));

/**
 * Delete a credential from the wallet.
 *
 * @note This method converts instances of WalletNotRegisteredException, CancellationException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)deleteCredentialCredential:(IdentityCredential *)credential completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("deleteCredential(credential:completionHandler:)")));

/**
 * Helper method for deleting a credential with and ID
 *
 * @note This method converts instances of CredentialNotFoundException, WalletNotRegisteredException, CancellationException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)deleteCredentialSource:(NSString *)source completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("deleteCredential(source:completionHandler:)")));

/**
 * @note This method converts instances of KeyPairException, StorageException, CancellationException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)destroyAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("destroy()")));

/**
 * @note This method converts instances of StorageException, WalletNotRegisteredException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (NSArray<IdentityClaim *> * _Nullable)getAllClaimsAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("getAllClaims()")));

/**
 * @note This method converts instances of StorageException, WalletNotRegisteredException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (IdentityCredential * _Nullable)getCredentialSource:(NSString *)source error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("getCredential(source:)"))) __attribute__((swift_error(nonnull_error)));

/**
 * @note This method converts instances of StorageException, WalletNotRegisteredException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (NSArray<IdentityCredential *> * _Nullable)getCredentialsAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("getCredentials()")));

/**
 * @note This method converts instances of InvalidLoginRequestFormatException, CancellationException, InvalidAppException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getLoginRequestUri:(NSString *)uri isNfcCapable:(BOOL)isNfcCapable completionHandler:(void (^)(IdentityRespondableLoginRequest * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getLoginRequest(uri:isNfcCapable:completionHandler:)")));

/**
 * @note This method converts instances of WalletAlreadyRegisteredException, AttestationNotSupportedException, AttestationException, ApiException, CancellationException, StorageException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)registerWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("register(completionHandler:)")));

/**
 * @note This method converts instances of WalletNotRegisteredException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)throwIfNotRegisteredAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("throwIfNotRegistered()")));
- (NSArray<IdentityJwt *> *)updateJwtsJwts:(NSArray<IdentityJwt *> *)jwts loginRequest:(IdentityLoginRequest * _Nullable)loginRequest __attribute__((swift_name("updateJwts(jwts:loginRequest:)")));

/**
 * @note This method converts instances of WalletNotRegisteredException, CancellationException, ApiException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)verifyUriCredentialUri:(NSString *)uri token:(NSString *)token completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("verifyUriCredential(uri:token:completionHandler:)")));
@property (readonly) IdentityIdentityPlatformInterface *identityPlatformInterface __attribute__((swift_name("identityPlatformInterface")));
@property (readonly) BOOL isRegistered __attribute__((swift_name("isRegistered")));
@property (readonly) IdentityRepository *repository __attribute__((swift_name("repository")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Wallet.Companion")))
@interface IdentityWalletCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityWalletCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *DTC_CLAIM_NAME __attribute__((swift_name("DTC_CLAIM_NAME")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("WalletAlreadyRegisteredException")))
@interface IdentityWalletAlreadyRegisteredException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("WalletFactory")))
@interface IdentityWalletFactory : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)walletFactory __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityWalletFactory *shared __attribute__((swift_name("shared")));
- (IdentityWallet *)getInstanceBaseUrl:(NSString *)baseUrl isLoggingEnabled:(BOOL)isLoggingEnabled __attribute__((swift_name("getInstance(baseUrl:isLoggingEnabled:)")));
- (IdentityWallet *)getInstanceBaseUrl:(NSString *)baseUrl isLoggingEnabled:(BOOL)isLoggingEnabled credentialDeserializer:(IdentityCredentialDeserializer *)credentialDeserializer __attribute__((swift_name("getInstance(baseUrl:isLoggingEnabled:credentialDeserializer:)")));
- (IdentityWallet *)getInstanceBaseUrl:(NSString *)baseUrl isLoggingEnabled:(BOOL)isLoggingEnabled storageEngine:(id<IdentityStorageEngine>)storageEngine __attribute__((swift_name("getInstance(baseUrl:isLoggingEnabled:storageEngine:)")));
- (IdentityWallet *)getInstanceBaseUrl:(NSString *)baseUrl isLoggingEnabled:(BOOL)isLoggingEnabled keyPairFactory:(id<IdentityKeyPair> (^)(void))keyPairFactory __attribute__((swift_name("getInstance(baseUrl:isLoggingEnabled:keyPairFactory:)")));
- (IdentityWallet *)getInstanceBaseUrl:(NSString *)baseUrl isLoggingEnabled:(BOOL)isLoggingEnabled storageEngine:(id<IdentityStorageEngine>)storageEngine credentialDeserializer:(IdentityCredentialDeserializer *)credentialDeserializer __attribute__((swift_name("getInstance(baseUrl:isLoggingEnabled:storageEngine:credentialDeserializer:)")));
- (IdentityWallet *)getInstanceBaseUrl:(NSString *)baseUrl isLoggingEnabled:(BOOL)isLoggingEnabled storageEngine:(id<IdentityStorageEngine>)storageEngine keyPairFactory:(id<IdentityKeyPair> (^)(void))keyPairFactory credentialDeserializer:(IdentityCredentialDeserializer *)credentialDeserializer __attribute__((swift_name("getInstance(baseUrl:isLoggingEnabled:storageEngine:keyPairFactory:credentialDeserializer:)")));
@property IdentityWallet * _Nullable instance __attribute__((swift_name("instance")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("WalletNotRegisteredException")))
@interface IdentityWalletNotRegisteredException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ApiClient")))
@interface IdentityApiClient : IdentityBase
- (instancetype)initWithBaseUrl:(NSString *)baseUrl keyPairGenerator:(id<IdentityKeyPair> (^)(void))keyPairGenerator platform:(id<IdentityPlatform>)platform instanceId:(NSString *)instanceId __attribute__((swift_name("init(baseUrl:keyPairGenerator:platform:instanceId:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts instances of ApiException, CancellationException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getUrl:(NSString *)url headers:(NSDictionary<NSString *, NSString *> *)headers completionHandler:(void (^)(IdentityKtor_client_coreHttpResponse * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("get(url:headers:completionHandler:)")));

/**
 * @note This method converts instances of ApiException, CancellationException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)postUrl:(NSString *)url body:(id)body headers:(NSDictionary<NSString *, NSString *> *)headers completionHandler:(void (^)(IdentityKtor_client_coreHttpResponse * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("post(url:body:headers:completionHandler:)")));

/**
 * @note This method converts instances of ApiException, CancellationException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)signAndPostPath:(NSString *)path body:(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *)body headers:(NSDictionary<NSString *, NSString *> *)headers keyId:(NSString * _Nullable)keyId completionHandler:(void (^)(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signAndPost(path:body:headers:keyId:completionHandler:)")));
@property (readonly) NSString *baseUrl __attribute__((swift_name("baseUrl")));
@property (readonly) id<IdentityKeyPair> (^keyPairGenerator)(void) __attribute__((swift_name("keyPairGenerator")));
@property (readonly) id<IdentityPlatform> platform __attribute__((swift_name("platform")));
@end

__attribute__((swift_name("ApiException")))
@interface IdentityApiException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ApiException.HttpError")))
@interface IdentityApiExceptionHttpError : IdentityApiException
- (instancetype)initWithStatusCode:(IdentityKtor_httpHttpStatusCode *)statusCode message:(NSString * _Nullable)message errorCode:(NSString * _Nullable)errorCode recoveryMessage:(NSString * _Nullable)recoveryMessage __attribute__((swift_name("init(statusCode:message:errorCode:recoveryMessage:)"))) __attribute__((objc_designated_initializer));
- (IdentityApiExceptionHttpError *)doCopyStatusCode:(IdentityKtor_httpHttpStatusCode *)statusCode message:(NSString * _Nullable)message errorCode:(NSString * _Nullable)errorCode recoveryMessage:(NSString * _Nullable)recoveryMessage __attribute__((swift_name("doCopy(statusCode:message:errorCode:recoveryMessage:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable errorCode __attribute__((swift_name("errorCode")));
@property (readonly) NSString * _Nullable message __attribute__((swift_name("message")));
@property (readonly) NSString * _Nullable recoveryMessage __attribute__((swift_name("recoveryMessage")));
@property (readonly) IdentityKtor_httpHttpStatusCode *statusCode __attribute__((swift_name("statusCode")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ApiException.NetworkError")))
@interface IdentityApiExceptionNetworkError : IdentityKotlinException
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)networkError __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityApiExceptionNetworkError *shared __attribute__((swift_name("shared")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ApiException.SerializationError")))
@interface IdentityApiExceptionSerializationError : IdentityApiException
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)serializationError __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityApiExceptionSerializationError *shared __attribute__((swift_name("shared")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ApiException.TimeoutError")))
@interface IdentityApiExceptionTimeoutError : IdentityApiException
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)timeoutError __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityApiExceptionTimeoutError *shared __attribute__((swift_name("shared")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((swift_name("Challenge")))
@interface IdentityChallenge : IdentityBase
- (instancetype)initWithChallenge:(IdentityKotlinByteArray * _Nullable)challenge expires:(IdentityKotlinx_datetimeInstant *)expires __attribute__((swift_name("init(challenge:expires:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((swift_name("RespondableChallenge")))
@interface IdentityRespondableChallenge<T> : IdentityChallenge
- (instancetype)initWithRespond:(T _Nullable)respond challenge:(IdentityChallenge *)challenge __attribute__((swift_name("init(respond:challenge:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithChallenge:(IdentityKotlinByteArray * _Nullable)challenge expires:(IdentityKotlinx_datetimeInstant *)expires __attribute__((swift_name("init(challenge:expires:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityRespondableChallengeCompanion *companion __attribute__((swift_name("companion")));
@property (readonly) T _Nullable respond __attribute__((swift_name("respond")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DocumentChallenge")))
@interface IdentityDocumentChallenge : IdentityRespondableChallenge<IdentityDocumentChallengeResponder *>
- (instancetype)initWithBacKey:(NSString *)bacKey respond:(IdentityDocumentChallengeResponder *)respond challenge:(IdentityChallenge *)challenge __attribute__((swift_name("init(bacKey:respond:challenge:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithRespond:(id _Nullable)respond challenge:(IdentityChallenge *)challenge __attribute__((swift_name("init(respond:challenge:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityDocumentChallengeCompanion *companion __attribute__((swift_name("companion")));
@property (readonly) NSString *bacKey __attribute__((swift_name("bacKey")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DocumentChallenge.Companion")))
@interface IdentityDocumentChallengeCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityDocumentChallengeCompanion *shared __attribute__((swift_name("shared")));
- (IdentityDocumentChallenge *)fromChallengeChallenge:(IdentityChallenge *)challenge bacKey:(NSString *)bacKey respond:(IdentityDocumentChallengeResponder *)respond __attribute__((swift_name("fromChallenge(challenge:bacKey:respond:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DocumentChallengeResponder")))
@interface IdentityDocumentChallengeResponder : IdentityBase
- (instancetype)initWithUsingMrtd:(id<IdentityKotlinx_coroutines_coreDeferred> (^)(IdentityMrtdData *, IdentityAccessControl *, IdentityKotlinByteArray * _Nullable))usingMrtd usingReadId:(id<IdentityKotlinx_coroutines_coreDeferred> (^)(NSString *))usingReadId __attribute__((swift_name("init(usingMrtd:usingReadId:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts instances of Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)withReadIdSessionId:(NSString *)sessionId completionHandler:(void (^)(IdentityKotlinNothing * _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("withReadId(sessionId:completionHandler:)")));
@end

__attribute__((swift_name("IdentityPlatformInterface")))
@interface IdentityIdentityPlatformInterface : IdentityBase
- (instancetype)initWithApiClient:(IdentityApiClient *)apiClient keyPairFactory:(id<IdentityKeyPair> (^)(void))keyPairFactory __attribute__((swift_name("init(apiClient:keyPairFactory:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)deleteWalletWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("deleteWallet(completionHandler:)")));

/**
 * @note This method converts instances of ApiException, CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getAuthRequestBaseUrl:(NSString *)baseUrl code:(NSString *)code nfcCapable:(BOOL)nfcCapable completionHandler:(void (^)(IdentityJwt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getAuthRequest(baseUrl:code:nfcCapable:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getChallengeKeyIdentifier:(NSString * _Nullable)keyIdentifier completionHandler:(void (^)(IdentityChallenge * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getChallenge(keyIdentifier:completionHandler:)")));
- (NSArray<IdentityJwt *> *)getClaimsPayload:(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *)payload __attribute__((swift_name("getClaims(payload:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getDemoGender:(IdentityGender *)gender format:(IdentityFormat *)format completionHandler:(void (^)(IdentityMrtdData * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getDemo(gender:format:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getOidcServersWithCompletionHandler:(void (^)(NSArray<NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getOidcServers(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException, ApiException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getTranslationsWithCompletionHandler:(void (^)(NSDictionary<NSString *, id> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getTranslations(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)doInitDocChallenge:(IdentityKotlinByteArray *)challenge reverificationToken:(NSString * _Nullable)reverificationToken completionHandler:(void (^)(IdentityChallenge * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("doInitDoc(challenge:reverificationToken:completionHandler:)")));

/**
 * @param reference The reference used by the identity platform to fetch the data representing the identity being added.
 * @param reverificationToken A token for re-verifying the identity reference
 * @param demoReferencePhoto An image used to verify the identity reference.
 *
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)doInitDocReferenceReference:(NSString *)reference reverificationToken:(NSString * _Nullable)reverificationToken demoReferencePhoto:(IdentityKotlinByteArray * _Nullable)demoReferencePhoto completionHandler:(void (^)(IdentityVerificationMethod * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("doInitDocReference(reference:reverificationToken:demoReferencePhoto:completionHandler:)")));

/**
 * @note This method converts instances of ApiException, CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)doInitFaceDtc:(IdentityClaim *)dtc reverificationToken:(NSString * _Nullable)reverificationToken completionHandler:(void (^)(IdentityVerificationMethod * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("doInitFace(dtc:reverificationToken:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException, ApiException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)doInitUriCredentialUri:(NSString *)uri completionHandler:(void (^)(IdentityChallenge * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("doInitUriCredential(uri:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)registerWalletAttestationToken:(NSString *)attestationToken completionHandler:(void (^)(NSArray<IdentityJwt *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("registerWallet(attestationToken:completionHandler:)")));

/**
 * @note This method converts instances of ApiException, CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)respondToAuthRequestBaseUrl:(NSString *)baseUrl loginRequest:(IdentityLoginRequest *)loginRequest jwts:(NSArray<IdentityJwt *> *)jwts completionHandler:(void (^)(IdentityLoginResponse * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("respondToAuthRequest(baseUrl:loginRequest:jwts:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException, ApiException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)signAndPostPath:(NSString *)path payload:(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *)payload headers:(NSDictionary<NSString *, NSString *> *)headers completionHandler:(void (^)(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signAndPost(path:payload:headers:completionHandler:)")));

/**
 * @note This method converts instances of ApiException, CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)verifyFaceToken:(NSString *)token completionHandler:(void (^)(NSArray<IdentityJwt *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("verifyFace(token:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)verifyMrtdMrtd:(IdentityMrtdData *)mrtd challenge:(IdentityKotlinByteArray *)challenge secret:(IdentityKotlinByteArray *)secret aaSignature:(IdentityKotlinByteArray * _Nullable)aaSignature accessControl:(IdentityAccessControl *)accessControl completionHandler:(void (^)(NSArray<IdentityJwt *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("verifyMrtd(mrtd:challenge:secret:aaSignature:accessControl:completionHandler:)")));

/**
 * @note This method converts instances of ApiException, CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)verifyReadIdSession:(NSString *)session secret:(IdentityKotlinByteArray *)secret completionHandler:(void (^)(NSArray<IdentityJwt *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("verifyReadId(session:secret:completionHandler:)")));

/**
 * @note This method converts instances of ApiException, CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)verifyReferenceDocumentToken:(NSString *)token completionHandler:(void (^)(NSArray<IdentityJwt *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("verifyReferenceDocument(token:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException, ApiException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)verifyUriCredentialUri:(NSString *)uri token:(NSString *)token completionHandler:(void (^)(NSArray<IdentityJwt *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("verifyUriCredential(uri:token:completionHandler:)")));
@property (readonly) IdentityApiClient *apiClient __attribute__((swift_name("apiClient")));
@property (readonly) id<IdentityKeyPair> (^keyPairFactory)(void) __attribute__((swift_name("keyPairFactory")));
@property NSString * _Nullable platformAttestationKeyId __attribute__((swift_name("platformAttestationKeyId")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RegisterAppleAttestationPayload")))
@interface IdentityRegisterAppleAttestationPayload : IdentityBase
- (instancetype)initWithKeyId:(NSString *)keyId attestationObjectB64:(NSString *)attestationObjectB64 __attribute__((swift_name("init(keyId:attestationObjectB64:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityRegisterAppleAttestationPayloadCompanion *companion __attribute__((swift_name("companion")));
- (IdentityRegisterAppleAttestationPayload *)doCopyKeyId:(NSString *)keyId attestationObjectB64:(NSString *)attestationObjectB64 __attribute__((swift_name("doCopy(keyId:attestationObjectB64:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="attestation_string")
*/
@property (readonly) NSString *attestationObjectB64 __attribute__((swift_name("attestationObjectB64")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="key_identifier")
*/
@property (readonly) NSString *keyId __attribute__((swift_name("keyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RegisterAppleAttestationPayload.Companion")))
@interface IdentityRegisterAppleAttestationPayloadCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityRegisterAppleAttestationPayloadCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RegisterAppleWalletPayload")))
@interface IdentityRegisterAppleWalletPayload : IdentityBase
- (instancetype)initWithDevice:(IdentityDeviceInfo *)device app:(IdentityAppInfo *)app __attribute__((swift_name("init(device:app:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityRegisterAppleWalletPayloadCompanion *companion __attribute__((swift_name("companion")));
- (IdentityRegisterAppleWalletPayload *)doCopyDevice:(IdentityDeviceInfo *)device app:(IdentityAppInfo *)app __attribute__((swift_name("doCopy(device:app:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) IdentityAppInfo *app __attribute__((swift_name("app")));
@property (readonly) IdentityDeviceInfo *device __attribute__((swift_name("device")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RegisterAppleWalletPayload.Companion")))
@interface IdentityRegisterAppleWalletPayloadCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityRegisterAppleWalletPayloadCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RespondableChallengeCompanion")))
@interface IdentityRespondableChallengeCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityRespondableChallengeCompanion *shared __attribute__((swift_name("shared")));
- (IdentityRespondableChallenge<id> *)fromChallengeChallenge:(IdentityChallenge *)challenge respond:(id _Nullable)respond __attribute__((swift_name("fromChallenge(challenge:respond:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UriCredentialChallenge")))
@interface IdentityUriCredentialChallenge : IdentityRespondableChallenge<IdentityUriCredentialChallengeResponder *>
- (instancetype)initWithChallenge:(IdentityChallenge *)challenge respond:(IdentityUriCredentialChallengeResponder *)respond __attribute__((swift_name("init(challenge:respond:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithRespond:(id _Nullable)respond challenge:(IdentityChallenge *)challenge __attribute__((swift_name("init(respond:challenge:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UriCredentialChallengeResponder")))
@interface IdentityUriCredentialChallengeResponder : IdentityBase
- (instancetype)initWithUsingToken:(id<IdentityKotlinx_coroutines_coreDeferred> (^)(NSString *))usingToken __attribute__((swift_name("init(usingToken:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts instances of Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)withTokenToken:(NSString *)token completionHandler:(void (^)(IdentityKotlinNothing * _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("withToken(token:completionHandler:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserAgent")))
@interface IdentityUserAgent : IdentityBase
- (instancetype)initWithSdkVersion:(NSString *)sdkVersion operatingSystem:(NSString *)operatingSystem operatingSystemVersion:(NSString *)operatingSystemVersion deviceModel:(NSString *)deviceModel __attribute__((swift_name("init(sdkVersion:operatingSystem:operatingSystemVersion:deviceModel:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityUserAgentCompanion *companion __attribute__((swift_name("companion")));
- (IdentityUserAgent *)doCopySdkVersion:(NSString *)sdkVersion operatingSystem:(NSString *)operatingSystem operatingSystemVersion:(NSString *)operatingSystemVersion deviceModel:(NSString *)deviceModel __attribute__((swift_name("doCopy(sdkVersion:operatingSystem:operatingSystemVersion:deviceModel:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *deviceModel __attribute__((swift_name("deviceModel")));

/**
 * Header that's sent to the identity backend to identify the device and SDK.
 */
@property (readonly) NSString *header __attribute__((swift_name("header")));
@property (readonly) NSString *operatingSystem __attribute__((swift_name("operatingSystem")));
@property (readonly) NSString *operatingSystemVersion __attribute__((swift_name("operatingSystemVersion")));
@property (readonly) NSString *sdkVersion __attribute__((swift_name("sdkVersion")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserAgent.Companion")))
@interface IdentityUserAgentCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityUserAgentCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AttestationException")))
@interface IdentityAttestationException : IdentityKotlinException
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AttestationKeyGenerationException")))
@interface IdentityAttestationKeyGenerationException : IdentityKotlinException
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AttestationNotSupportedException")))
@interface IdentityAttestationNotSupportedException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((swift_name("KeyPair")))
@protocol IdentityKeyPair
@required
- (IdentityEllipticCurvePublicKey *)getJwk __attribute__((swift_name("getJwk()")));
- (NSString *)getKeySecurityLevel __attribute__((swift_name("getKeySecurityLevel()")));
- (IdentityKotlinByteArray *)getPublicKey __attribute__((swift_name("getPublicKey()")));

/**
 * @note This method converts instances of KeyPairException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)resetAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("reset()")));
- (IdentityKotlinByteArray *)signData:(IdentityKotlinByteArray *)data __attribute__((swift_name("sign(data:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppleKeyPair")))
@interface IdentityAppleKeyPair : IdentityBase <IdentityKeyPair>
- (instancetype)initWithTag:(NSString *)tag __attribute__((swift_name("init(tag:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts instances of KeyPairException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (IdentityKotlinByteArray * _Nullable)decryptData:(IdentityKotlinByteArray *)data error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decrypt(data:)")));

/**
 * @note This method converts instances of KeyPairException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (IdentityKotlinByteArray * _Nullable)encryptData:(IdentityKotlinByteArray *)data error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("encrypt(data:)")));
- (IdentityEllipticCurvePublicKey *)getJwk __attribute__((swift_name("getJwk()")));
- (NSString *)getKeySecurityLevel __attribute__((swift_name("getKeySecurityLevel()")));
- (IdentityKotlinByteArray *)getPublicKey __attribute__((swift_name("getPublicKey()")));

/**
 * @note This method converts instances of KeyPairException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)resetAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("reset()")));
- (IdentityKotlinByteArray *)signData:(IdentityKotlinByteArray *)data __attribute__((swift_name("sign(data:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppleKeyPair.Location")))
@interface IdentityAppleKeyPairLocation : IdentityKotlinEnum<IdentityAppleKeyPairLocation *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentityAppleKeyPairLocation *secureEnclave __attribute__((swift_name("secureEnclave")));
@property (class, readonly) IdentityAppleKeyPairLocation *keychain __attribute__((swift_name("keychain")));
+ (IdentityKotlinArray<IdentityAppleKeyPairLocation *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityAppleKeyPairLocation *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString *stringValue __attribute__((swift_name("stringValue")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EllipticCurvePublicKey")))
@interface IdentityEllipticCurvePublicKey : IdentityBase
- (instancetype)initWithAlg:(NSString *)alg jwk:(IdentityJwk *)jwk __attribute__((swift_name("init(alg:jwk:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityEllipticCurvePublicKeyCompanion *companion __attribute__((swift_name("companion")));
- (IdentityEllipticCurvePublicKey *)doCopyAlg:(NSString *)alg jwk:(IdentityJwk *)jwk __attribute__((swift_name("doCopy(alg:jwk:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *alg __attribute__((swift_name("alg")));
@property (readonly) IdentityJwk *jwk __attribute__((swift_name("jwk")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EllipticCurvePublicKey.Companion")))
@interface IdentityEllipticCurvePublicKeyCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityEllipticCurvePublicKeyCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwk")))
@interface IdentityJwk : IdentityBase
- (instancetype)initWithCrv:(NSString *)crv kty:(NSString *)kty x:(NSString *)x y:(NSString *)y keyId:(NSString * _Nullable)keyId __attribute__((swift_name("init(crv:kty:x:y:keyId:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityJwkCompanion *companion __attribute__((swift_name("companion")));
- (IdentityJwk *)doCopyCrv:(NSString *)crv kty:(NSString *)kty x:(NSString *)x y:(NSString *)y keyId:(NSString * _Nullable)keyId __attribute__((swift_name("doCopy(crv:kty:x:y:keyId:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *crv __attribute__((swift_name("crv")));

/**
 * @note annotations
 *   kotlinx.serialization.Transient
*/
@property (readonly) NSString * _Nullable keyId __attribute__((swift_name("keyId")));
@property (readonly) NSString *kty __attribute__((swift_name("kty")));
@property (readonly) NSString *x __attribute__((swift_name("x")));
@property (readonly) NSString *y __attribute__((swift_name("y")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwk.Companion")))
@interface IdentityJwkCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityJwkCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KeyPairException")))
@interface IdentityKeyPairException : IdentityKotlinException
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Length")))
@interface IdentityLength : IdentityBase
- (instancetype)initWithValue:(int32_t)value lengthBytes:(int32_t)lengthBytes __attribute__((swift_name("init(value:lengthBytes:)"))) __attribute__((objc_designated_initializer));
- (IdentityLength *)doCopyValue:(int32_t)value lengthBytes:(int32_t)lengthBytes __attribute__((swift_name("doCopy(value:lengthBytes:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t lengthBytes __attribute__((swift_name("lengthBytes")));
@property (readonly) int32_t value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SymmetricKey")))
@interface IdentitySymmetricKey : IdentityBase
- (instancetype)initWithKeyBytes:(IdentityKotlinByteArray *)keyBytes __attribute__((swift_name("init(keyBytes:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithKeyString:(NSString *)keyString __attribute__((swift_name("init(keyString:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentitySymmetricKeyCompanion *companion __attribute__((swift_name("companion")));
- (IdentityKotlinByteArray * _Nullable)decryptEncryptedData:(IdentityKotlinByteArray *)encryptedData __attribute__((swift_name("decrypt(encryptedData:)")));
- (IdentityKotlinByteArray * _Nullable)encryptPlainData:(IdentityKotlinByteArray *)plainData __attribute__((swift_name("encrypt(plainData:)")));
- (IdentityKotlinByteArray *)getKeyBytes __attribute__((swift_name("getKeyBytes()")));
- (NSString *)getKeyString __attribute__((swift_name("getKeyString()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SymmetricKey.Companion")))
@interface IdentitySymmetricKeyCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentitySymmetricKeyCompanion *shared __attribute__((swift_name("shared")));
- (IdentitySymmetricKey *)doNew __attribute__((swift_name("doNew()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AccessControl")))
@interface IdentityAccessControl : IdentityKotlinEnum<IdentityAccessControl *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentityAccessControl *bac __attribute__((swift_name("bac")));
@property (class, readonly) IdentityAccessControl *pace __attribute__((swift_name("pace")));
+ (IdentityKotlinArray<IdentityAccessControl *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityAccessControl *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((swift_name("ActiveAuthentication")))
@interface IdentityActiveAuthentication : IdentityBase
- (instancetype)initWithChallenge:(IdentityKotlinByteArray *)challenge secret:(IdentityKotlinByteArray *)secret __attribute__((swift_name("init(challenge:secret:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityActiveAuthenticationCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ActiveAuthentication.Companion")))
@interface IdentityActiveAuthenticationCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityActiveAuthenticationCompanion *shared __attribute__((swift_name("shared")));
- (IdentityActiveAuthentication *)generateFromBacKeyBacKey:(IdentityBacKey *)bacKey __attribute__((swift_name("generateFromBacKey(bacKey:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssuranceType")))
@interface IdentityAssuranceType : IdentityKotlinEnum<IdentityAssuranceType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityAssuranceTypeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) IdentityAssuranceType *express __attribute__((swift_name("express")));
@property (class, readonly) IdentityAssuranceType *dynamic __attribute__((swift_name("dynamic")));
+ (IdentityKotlinArray<IdentityAssuranceType *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityAssuranceType *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString *shortName __attribute__((swift_name("shortName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssuranceType.Companion")))
@interface IdentityAssuranceTypeCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityAssuranceTypeCompanion *shared __attribute__((swift_name("shared")));
- (IdentityAssuranceType *)fromStringValue:(NSString *)value __attribute__((swift_name("fromString(value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("BacKey")))
@interface IdentityBacKey : IdentityBase
@property (class, readonly, getter=companion) IdentityBacKeyCompanion *companion __attribute__((swift_name("companion")));
@property (readonly) NSString *key __attribute__((swift_name("key")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("BacKey.Companion")))
@interface IdentityBacKeyCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityBacKeyCompanion *shared __attribute__((swift_name("shared")));
- (IdentityBacKey *)fromFieldsDocumentNumber:(NSString *)documentNumber dateOfBirth:(NSString *)dateOfBirth dateOfExpiry:(NSString *)dateOfExpiry __attribute__((swift_name("fromFields(documentNumber:dateOfBirth:dateOfExpiry:)")));
- (IdentityBacKey *)fromMrzMrz:(NSString *)mrz __attribute__((swift_name("fromMrz(mrz:)")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreSerializationStrategy")))
@protocol IdentityKotlinx_serialization_coreSerializationStrategy
@required
- (void)serializeEncoder:(id<IdentityKotlinx_serialization_coreEncoder>)encoder value:(id _Nullable)value __attribute__((swift_name("serialize(encoder:value:)")));
@property (readonly) id<IdentityKotlinx_serialization_coreSerialDescriptor> descriptor __attribute__((swift_name("descriptor")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreDeserializationStrategy")))
@protocol IdentityKotlinx_serialization_coreDeserializationStrategy
@required
- (id _Nullable)deserializeDecoder:(id<IdentityKotlinx_serialization_coreDecoder>)decoder __attribute__((swift_name("deserialize(decoder:)")));
@property (readonly) id<IdentityKotlinx_serialization_coreSerialDescriptor> descriptor __attribute__((swift_name("descriptor")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreKSerializer")))
@protocol IdentityKotlinx_serialization_coreKSerializer <IdentityKotlinx_serialization_coreSerializationStrategy, IdentityKotlinx_serialization_coreDeserializationStrategy>
@required
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ByteArrayAsBase64Serializer")))
@interface IdentityByteArrayAsBase64Serializer : IdentityBase <IdentityKotlinx_serialization_coreKSerializer>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)byteArrayAsBase64Serializer __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityByteArrayAsBase64Serializer *shared __attribute__((swift_name("shared")));
- (IdentityKotlinByteArray *)deserializeDecoder:(id<IdentityKotlinx_serialization_coreDecoder>)decoder __attribute__((swift_name("deserialize(decoder:)")));
- (void)serializeEncoder:(id<IdentityKotlinx_serialization_coreEncoder>)encoder value:(IdentityKotlinByteArray *)value __attribute__((swift_name("serialize(encoder:value:)")));
@property (readonly) id<IdentityKotlinx_serialization_coreSerialDescriptor> descriptor __attribute__((swift_name("descriptor")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Claim")))
@interface IdentityClaim : IdentityBase
- (instancetype)initWithJwt:(IdentityJwt *)jwt displayName:(NSString * _Nullable)displayName __attribute__((swift_name("init(jwt:displayName:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityClaimCompanion *companion __attribute__((swift_name("companion")));
- (IdentityClaim *)doCopyJwt:(IdentityJwt *)jwt displayName:(NSString * _Nullable)displayName __attribute__((swift_name("doCopy(jwt:displayName:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable displayName __attribute__((swift_name("displayName")));
@property (readonly) IdentityJwt *jwt __attribute__((swift_name("jwt")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) NSString *source __attribute__((swift_name("source")));
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Claim.Companion")))
@interface IdentityClaimCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityClaimCompanion *shared __attribute__((swift_name("shared")));
- (IdentityClaim *)fromJwtJwt:(IdentityJwt *)jwt translations:(NSDictionary<NSString *, id> *)translations __attribute__((swift_name("fromJwt(jwt:translations:)")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((swift_name("Credential")))
@interface IdentityCredential : IdentityBase
- (instancetype)initWithSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("init(source:claims:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityCredentialCompanion *companion __attribute__((swift_name("companion")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)deleteWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("delete(completionHandler:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));

/**
 * Helper function to retrieve and cast a specific claim's value.
 * @param name The full name of the claim.
 * @return The claim's value cast to type T, or null if not found or type mismatch.
 *
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (id _Nullable)getClaimValueName:(NSString *)name __attribute__((swift_name("getClaimValue(name:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<IdentityClaim *> *claims __attribute__((swift_name("claims")));
@property (readonly) NSString *source __attribute__((swift_name("source")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Credential.Companion")))
@interface IdentityCredentialCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityCredentialCompanion *shared __attribute__((swift_name("shared")));
- (IdentityCredential *)fromClaimsSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("fromClaims(source:claims:)")));
@end

__attribute__((swift_name("Credential.IdentityCredential")))
@interface IdentityCredentialIdentityCredential : IdentityCredential
- (instancetype)initWithSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("init(source:claims:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityCredentialIdentityCredentialCompanion *companion __attribute__((swift_name("companion")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Credential.IdentityCredentialCompanion")))
@interface IdentityCredentialIdentityCredentialCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityCredentialIdentityCredentialCompanion *shared __attribute__((swift_name("shared")));
- (IdentityCredentialIdentityCredential *)fromClaimsSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("fromClaims(source:claims:)")));
@end


/**
 * Represents a machine readable travel document
 *
 * Must contain a DTC claim & MRZ claim
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Credential.IdentityCredentialMrtd")))
@interface IdentityCredentialIdentityCredentialMrtd : IdentityCredentialIdentityCredential
- (instancetype)initWithSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("init(source:claims:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts instances of WalletNotRegisteredException, ApiException, CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (id<IdentityKotlinx_coroutines_coreFlow> _Nullable)verifyFaceLoginRequest:(IdentityLoginRequest * _Nullable)loginRequest options:(IdentitySdkIproovOptions * _Nullable)options error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("verifyFace(loginRequest:options:)")));
@property (readonly) IdentityClaim *dtc __attribute__((swift_name("dtc")));
@property (readonly) IdentityClaim *mrz __attribute__((swift_name("mrz")));
@end


/**
 * Represents a reference to a digital identity
 *
 * Must contain a reference claim
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Credential.IdentityCredentialReference")))
@interface IdentityCredentialIdentityCredentialReference : IdentityCredentialIdentityCredential
- (instancetype)initWithSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("init(source:claims:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((swift_name("Credential.UriCredential")))
@interface IdentityCredentialUriCredential : IdentityCredential
- (instancetype)initWithSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("init(source:claims:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (readonly) NSString *url __attribute__((swift_name("url")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Credential.UriCredentialEmailAddress")))
@interface IdentityCredentialUriCredentialEmailAddress : IdentityCredentialUriCredential
- (instancetype)initWithSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("init(source:claims:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Credential.UriCredentialPhoneNumber")))
@interface IdentityCredentialUriCredentialPhoneNumber : IdentityCredentialUriCredential
- (instancetype)initWithSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("init(source:claims:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DataAsBase64Serializer")))
@interface IdentityDataAsBase64Serializer : IdentityBase <IdentityKotlinx_serialization_coreKSerializer>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)dataAsBase64Serializer __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityDataAsBase64Serializer *shared __attribute__((swift_name("shared")));
- (NSData *)deserializeDecoder:(id<IdentityKotlinx_serialization_coreDecoder>)decoder __attribute__((swift_name("deserialize(decoder:)")));
- (void)serializeEncoder:(id<IdentityKotlinx_serialization_coreEncoder>)encoder value:(NSData *)value __attribute__((swift_name("serialize(encoder:value:)")));
@property (readonly) id<IdentityKotlinx_serialization_coreSerialDescriptor> descriptor __attribute__((swift_name("descriptor")));
@end

__attribute__((swift_name("ReverificationRequest")))
@interface IdentityReverificationRequest : IdentityBase
@property (class, readonly, getter=companion) IdentityReverificationRequestCompanion *companion __attribute__((swift_name("companion")));
@property (readonly) NSString *displayName __attribute__((swift_name("displayName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DocumentReverificationRequest")))
@interface IdentityDocumentReverificationRequest : IdentityReverificationRequest
- (instancetype)initWithOnGetChallenge:(id<IdentityKotlinx_coroutines_coreDeferred> (^)(IdentityCredentialIdentityCredentialMrtd *))onGetChallenge __attribute__((swift_name("init(onGetChallenge:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts instances of Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getChallengeMrtd:(IdentityCredentialIdentityCredentialMrtd *)mrtd completionHandler:(void (^)(IdentityDocumentChallenge * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getChallenge(mrtd:completionHandler:)")));
@property (readonly) NSString *displayName __attribute__((swift_name("displayName")));
@end

__attribute__((swift_name("VerificationException")))
@interface IdentityVerificationException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ExpectedVerificationConfig")))
@interface IdentityExpectedVerificationConfig : IdentityVerificationException
- (instancetype)initWithMethod:(NSString *)method __attribute__((swift_name("init(method:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("FaceReverificationRequest")))
@interface IdentityFaceReverificationRequest : IdentityReverificationRequest
- (instancetype)initWithVerify:(id<IdentityKotlinx_coroutines_coreFlow> (^)(IdentityCredentialIdentityCredentialMrtd *, IdentitySdkIproovOptions * _Nullable))verify assuranceType:(IdentityAssuranceType *)assuranceType __attribute__((swift_name("init(verify:assuranceType:)"))) __attribute__((objc_designated_initializer));
@property (readonly) IdentityAssuranceType *assuranceType __attribute__((swift_name("assuranceType")));
@property (readonly) NSString *displayName __attribute__((swift_name("displayName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Format")))
@interface IdentityFormat : IdentityKotlinEnum<IdentityFormat *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentityFormat *base64 __attribute__((swift_name("base64")));
@property (class, readonly) IdentityFormat *hex __attribute__((swift_name("hex")));
+ (IdentityKotlinArray<IdentityFormat *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityFormat *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Gender")))
@interface IdentityGender : IdentityKotlinEnum<IdentityGender *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentityGender *male __attribute__((swift_name("male")));
@property (class, readonly) IdentityGender *female __attribute__((swift_name("female")));
+ (IdentityKotlinArray<IdentityGender *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityGender *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("InvalidLoginRequestFormatException")))
@interface IdentityInvalidLoginRequestFormatException : IdentityKotlinException
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("InvalidMrzException")))
@interface IdentityInvalidMrzException : IdentityKotlinException
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("InvalidVerificationConfig")))
@interface IdentityInvalidVerificationConfig : IdentityVerificationException
- (instancetype)initWithMethod:(NSString *)method missingKey:(NSString *)missingKey __attribute__((swift_name("init(method:missingKey:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("InvalidVerificationMethod")))
@interface IdentityInvalidVerificationMethod : IdentityVerificationException
- (instancetype)initWithMethod:(NSString *)method __attribute__((swift_name("init(method:)"))) __attribute__((objc_designated_initializer));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwt")))
@interface IdentityJwt : IdentityBase
- (instancetype)initWithCompactString:(NSString *)compactString __attribute__((swift_name("init(compactString:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityJwtCompanion *companion __attribute__((swift_name("companion")));
- (IdentityJwt *)doCopyCompactString:(NSString *)compactString __attribute__((swift_name("doCopy(compactString:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
- (void)wasSignedByPublicKey __attribute__((swift_name("wasSignedByPublicKey()")));
@property (readonly) NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *body __attribute__((swift_name("body")));
@property (readonly) NSString *compactString __attribute__((swift_name("compactString")));

/**
 * Helper method to get the decoded header
 */
@property (readonly) NSDictionary<NSString *, id> *header __attribute__((swift_name("header")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *payload __attribute__((swift_name("payload")));

/**
 * Helper method to get the decoded header
 */
@property (readonly) NSString *signature __attribute__((swift_name("signature")));
@property (readonly) NSString *source __attribute__((swift_name("source")));
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@property (readonly) IdentityJwtVerificationStatus *verificationStatus __attribute__((swift_name("verificationStatus")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwt.Companion")))
@interface IdentityJwtCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityJwtCompanion *shared __attribute__((swift_name("shared")));
- (NSString *)createPublicKey:(IdentityEllipticCurvePublicKey *)publicKey payload:(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *)payload signingFunction:(IdentityKotlinByteArray *(^)(IdentityKotlinByteArray *))signingFunction __attribute__((swift_name("create(publicKey:payload:signingFunction:)")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@property (readonly) IdentityKotlinBase64 *base64 __attribute__((swift_name("base64")));
@end

__attribute__((swift_name("Jwt.VerificationStatus")))
@interface IdentityJwtVerificationStatus : IdentityBase
@end


/**
 * Claim (if issued) inside JWT has expired
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwt.VerificationStatusExpired")))
@interface IdentityJwtVerificationStatusExpired : IdentityJwtVerificationStatus
- (instancetype)initWithExpired:(id)expired __attribute__((swift_name("init(expired:)"))) __attribute__((objc_designated_initializer));

/**
 * Claim (if issued) inside JWT has expired
 */
- (IdentityJwtVerificationStatusExpired *)doCopyExpired:(id)expired __attribute__((swift_name("doCopy(expired:)")));

/**
 * Claim (if issued) inside JWT has expired
 */
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));

/**
 * Claim (if issued) inside JWT has expired
 */
- (NSUInteger)hash __attribute__((swift_name("hash()")));

/**
 * Claim (if issued) inside JWT has expired
 */
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id expired __attribute__((swift_name("expired")));
@end


/**
 * Invalid Signature
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwt.VerificationStatusInvalid")))
@interface IdentityJwtVerificationStatusInvalid : IdentityJwtVerificationStatus
+ (instancetype)alloc __attribute__((unavailable));

/**
 * Invalid Signature
 */
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)invalid __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityJwtVerificationStatusInvalid *shared __attribute__((swift_name("shared")));

/**
 * Invalid Signature
 */
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));

/**
 * Invalid Signature
 */
- (NSUInteger)hash __attribute__((swift_name("hash()")));

/**
 * Invalid Signature
 */
- (NSString *)description __attribute__((swift_name("description()")));
@end


/**
 * JWT was malformed when it was received or parsing failed
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwt.VerificationStatusMalformed")))
@interface IdentityJwtVerificationStatusMalformed : IdentityJwtVerificationStatus
+ (instancetype)alloc __attribute__((unavailable));

/**
 * JWT was malformed when it was received or parsing failed
 */
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)malformed __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityJwtVerificationStatusMalformed *shared __attribute__((swift_name("shared")));

/**
 * JWT was malformed when it was received or parsing failed
 */
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));

/**
 * JWT was malformed when it was received or parsing failed
 */
- (NSUInteger)hash __attribute__((swift_name("hash()")));

/**
 * JWT was malformed when it was received or parsing failed
 */
- (NSString *)description __attribute__((swift_name("description()")));
@end


/**
 * No public key present to check the signature of the JWT
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwt.VerificationStatusNotVerified")))
@interface IdentityJwtVerificationStatusNotVerified : IdentityJwtVerificationStatus
+ (instancetype)alloc __attribute__((unavailable));

/**
 * No public key present to check the signature of the JWT
 */
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)notVerified __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityJwtVerificationStatusNotVerified *shared __attribute__((swift_name("shared")));

/**
 * No public key present to check the signature of the JWT
 */
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));

/**
 * No public key present to check the signature of the JWT
 */
- (NSUInteger)hash __attribute__((swift_name("hash()")));

/**
 * No public key present to check the signature of the JWT
 */
- (NSString *)description __attribute__((swift_name("description()")));
@end


/**
 * There is no signature present (this is an Unsecure JWS)
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwt.VerificationStatusUnsecured")))
@interface IdentityJwtVerificationStatusUnsecured : IdentityJwtVerificationStatus
+ (instancetype)alloc __attribute__((unavailable));

/**
 * There is no signature present (this is an Unsecure JWS)
 */
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)unsecured __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityJwtVerificationStatusUnsecured *shared __attribute__((swift_name("shared")));

/**
 * There is no signature present (this is an Unsecure JWS)
 */
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));

/**
 * There is no signature present (this is an Unsecure JWS)
 */
- (NSUInteger)hash __attribute__((swift_name("hash()")));

/**
 * There is no signature present (this is an Unsecure JWS)
 */
- (NSString *)description __attribute__((swift_name("description()")));
@end


/**
 * JWT was in a valid format, has not expired and signature was verified
 * @param signature Signature of the signer that was valid
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Jwt.VerificationStatusValid")))
@interface IdentityJwtVerificationStatusValid : IdentityJwtVerificationStatus
- (instancetype)initWithSignature:(id)signature __attribute__((swift_name("init(signature:)"))) __attribute__((objc_designated_initializer));

/**
 * JWT was in a valid format, has not expired and signature was verified
 * @param signature Signature of the signer that was valid
 */
- (IdentityJwtVerificationStatusValid *)doCopySignature:(id)signature __attribute__((swift_name("doCopy(signature:)")));

/**
 * JWT was in a valid format, has not expired and signature was verified
 * @param signature Signature of the signer that was valid
 */
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));

/**
 * JWT was in a valid format, has not expired and signature was verified
 * @param signature Signature of the signer that was valid
 */
- (NSUInteger)hash __attribute__((swift_name("hash()")));

/**
 * JWT was in a valid format, has not expired and signature was verified
 * @param signature Signature of the signer that was valid
 */
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id signature __attribute__((swift_name("signature")));
@end

__attribute__((swift_name("LoginRequest")))
@interface IdentityLoginRequest : IdentityBase
- (instancetype)initWithJwt:(IdentityJwt *)jwt translations:(NSDictionary<NSString *, id> *)translations __attribute__((swift_name("init(jwt:translations:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (instancetype)initWithTranslations:(NSDictionary<NSString *, id> *)translations claims:(NSArray<IdentityRequestedClaim *> *)claims acrs:(NSArray<NSString *> *)acrs relyingParty:(IdentityRelyingParty *)relyingParty json:(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *)json jwt:(IdentityJwt *)jwt __attribute__((swift_name("init(translations:claims:acrs:relyingParty:json:jwt:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityLoginRequestCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<NSString *> *acrs __attribute__((swift_name("acrs")));
@property (readonly) NSArray<IdentityRequestedClaim *> *claims __attribute__((swift_name("claims")));
@property (readonly) NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *json __attribute__((swift_name("json")));
@property (readonly) IdentityJwt *jwt __attribute__((swift_name("jwt")));
@property (readonly) IdentityRelyingParty *relyingParty __attribute__((swift_name("relyingParty")));
@property (readonly) NSMutableArray<IdentityJwt *> *reverificationJwts __attribute__((swift_name("reverificationJwts")));
@property (readonly) NSDictionary<NSString *, id> *translations __attribute__((swift_name("translations")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("LoginRequest.Companion")))
@interface IdentityLoginRequestCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityLoginRequestCompanion *shared __attribute__((swift_name("shared")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("LoginResponse")))
@interface IdentityLoginResponse : IdentityBase
- (instancetype)initWithRedirectUri:(NSString * _Nullable)redirectUri __attribute__((swift_name("init(redirectUri:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityLoginResponseCompanion *companion __attribute__((swift_name("companion")));
- (IdentityLoginResponse *)doCopyRedirectUri:(NSString * _Nullable)redirectUri __attribute__((swift_name("doCopy(redirectUri:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="redirect_uri")
*/
@property (readonly) NSString * _Nullable redirectUri __attribute__((swift_name("redirectUri")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("LoginResponse.Companion")))
@interface IdentityLoginResponseCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityLoginResponseCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((swift_name("MrtdData")))
@interface IdentityMrtdData : IdentityBase
- (instancetype)initWithSod:(IdentityKotlinByteArray *)sod dg1:(IdentityKotlinByteArray *)dg1 dg2:(IdentityKotlinByteArray *)dg2 dg3:(IdentityKotlinByteArray * _Nullable)dg3 dg4:(IdentityKotlinByteArray * _Nullable)dg4 dg5:(IdentityKotlinByteArray * _Nullable)dg5 dg6:(IdentityKotlinByteArray * _Nullable)dg6 dg7:(IdentityKotlinByteArray * _Nullable)dg7 dg8:(IdentityKotlinByteArray * _Nullable)dg8 dg9:(IdentityKotlinByteArray * _Nullable)dg9 dg10:(IdentityKotlinByteArray * _Nullable)dg10 dg11:(IdentityKotlinByteArray * _Nullable)dg11 dg12:(IdentityKotlinByteArray * _Nullable)dg12 dg13:(IdentityKotlinByteArray * _Nullable)dg13 dg14:(IdentityKotlinByteArray * _Nullable)dg14 dg15:(IdentityKotlinByteArray * _Nullable)dg15 dg16:(IdentityKotlinByteArray * _Nullable)dg16 dg17:(IdentityKotlinByteArray * _Nullable)dg17 dg18:(IdentityKotlinByteArray * _Nullable)dg18 dg19:(IdentityKotlinByteArray * _Nullable)dg19 com:(IdentityKotlinByteArray * _Nullable)com cvca:(IdentityKotlinByteArray * _Nullable)cvca __attribute__((swift_name("init(sod:dg1:dg2:dg3:dg4:dg5:dg6:dg7:dg8:dg9:dg10:dg11:dg12:dg13:dg14:dg15:dg16:dg17:dg18:dg19:com:cvca:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithSeen0:(int32_t)seen0 sod:(IdentityKotlinByteArray * _Nullable)sod dg1:(IdentityKotlinByteArray * _Nullable)dg1 dg2:(IdentityKotlinByteArray * _Nullable)dg2 dg3:(IdentityKotlinByteArray * _Nullable)dg3 dg4:(IdentityKotlinByteArray * _Nullable)dg4 dg5:(IdentityKotlinByteArray * _Nullable)dg5 dg6:(IdentityKotlinByteArray * _Nullable)dg6 dg7:(IdentityKotlinByteArray * _Nullable)dg7 dg8:(IdentityKotlinByteArray * _Nullable)dg8 dg9:(IdentityKotlinByteArray * _Nullable)dg9 dg10:(IdentityKotlinByteArray * _Nullable)dg10 dg11:(IdentityKotlinByteArray * _Nullable)dg11 dg12:(IdentityKotlinByteArray * _Nullable)dg12 dg13:(IdentityKotlinByteArray * _Nullable)dg13 dg14:(IdentityKotlinByteArray * _Nullable)dg14 dg15:(IdentityKotlinByteArray * _Nullable)dg15 dg16:(IdentityKotlinByteArray * _Nullable)dg16 dg17:(IdentityKotlinByteArray * _Nullable)dg17 dg18:(IdentityKotlinByteArray * _Nullable)dg18 dg19:(IdentityKotlinByteArray * _Nullable)dg19 com:(IdentityKotlinByteArray * _Nullable)com cvca:(IdentityKotlinByteArray * _Nullable)cvca serializationConstructorMarker:(id _Nullable)serializationConstructorMarker __attribute__((swift_name("init(seen0:sod:dg1:dg2:dg3:dg4:dg5:dg6:dg7:dg8:dg9:dg10:dg11:dg12:dg13:dg14:dg15:dg16:dg17:dg18:dg19:com:cvca:serializationConstructorMarker:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityMrtdDataCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *mrz __attribute__((swift_name("mrz")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Mrtd")))
@interface IdentityMrtd : IdentityMrtdData
- (instancetype)initWithSod:(NSData *)sod dg1:(NSData *)dg1 dg2:(NSData *)dg2 dg3:(NSData * _Nullable)dg3 dg4:(NSData * _Nullable)dg4 dg5:(NSData * _Nullable)dg5 dg6:(NSData * _Nullable)dg6 dg7:(NSData * _Nullable)dg7 dg8:(NSData * _Nullable)dg8 dg9:(NSData * _Nullable)dg9 dg10:(NSData * _Nullable)dg10 dg11:(NSData * _Nullable)dg11 dg12:(NSData * _Nullable)dg12 dg13:(NSData * _Nullable)dg13 dg14:(NSData * _Nullable)dg14 dg15:(NSData * _Nullable)dg15 dg16:(NSData * _Nullable)dg16 dg17:(NSData * _Nullable)dg17 dg18:(NSData * _Nullable)dg18 dg19:(NSData * _Nullable)dg19 com:(NSData * _Nullable)com cvca:(NSData * _Nullable)cvca __attribute__((swift_name("init(sod:dg1:dg2:dg3:dg4:dg5:dg6:dg7:dg8:dg9:dg10:dg11:dg12:dg13:dg14:dg15:dg16:dg17:dg18:dg19:com:cvca:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithSeen0:(int32_t)seen0 sod:(IdentityKotlinByteArray * _Nullable)sod dg1:(IdentityKotlinByteArray * _Nullable)dg1 dg2:(IdentityKotlinByteArray * _Nullable)dg2 dg3:(IdentityKotlinByteArray * _Nullable)dg3 dg4:(IdentityKotlinByteArray * _Nullable)dg4 dg5:(IdentityKotlinByteArray * _Nullable)dg5 dg6:(IdentityKotlinByteArray * _Nullable)dg6 dg7:(IdentityKotlinByteArray * _Nullable)dg7 dg8:(IdentityKotlinByteArray * _Nullable)dg8 dg9:(IdentityKotlinByteArray * _Nullable)dg9 dg10:(IdentityKotlinByteArray * _Nullable)dg10 dg11:(IdentityKotlinByteArray * _Nullable)dg11 dg12:(IdentityKotlinByteArray * _Nullable)dg12 dg13:(IdentityKotlinByteArray * _Nullable)dg13 dg14:(IdentityKotlinByteArray * _Nullable)dg14 dg15:(IdentityKotlinByteArray * _Nullable)dg15 dg16:(IdentityKotlinByteArray * _Nullable)dg16 dg17:(IdentityKotlinByteArray * _Nullable)dg17 dg18:(IdentityKotlinByteArray * _Nullable)dg18 dg19:(IdentityKotlinByteArray * _Nullable)dg19 com:(IdentityKotlinByteArray * _Nullable)com cvca:(IdentityKotlinByteArray * _Nullable)cvca serializationConstructorMarker:(id _Nullable)serializationConstructorMarker __attribute__((swift_name("init(seen0:sod:dg1:dg2:dg3:dg4:dg5:dg6:dg7:dg8:dg9:dg10:dg11:dg12:dg13:dg14:dg15:dg16:dg17:dg18:dg19:com:cvca:serializationConstructorMarker:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityMrtdCompanion *companion __attribute__((swift_name("companion")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Mrtd.Companion")))
@interface IdentityMrtdCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityMrtdCompanion *shared __attribute__((swift_name("shared")));
- (IdentityMrtdData *)fromDtcVcDtcVc:(NSData *)dtcVc __attribute__((swift_name("fromDtcVc(dtcVc:)")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("MrtdData.Companion")))
@interface IdentityMrtdDataCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityMrtdDataCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("MrzField")))
@interface IdentityMrzField : IdentityBase
@property (class, readonly, getter=companion) IdentityMrzFieldCompanion *companion __attribute__((swift_name("companion")));
@property (readonly) int32_t checksum __attribute__((swift_name("checksum")));
@property (readonly) BOOL isValid __attribute__((swift_name("isValid")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@property (readonly) NSString *valueWithChecksum __attribute__((swift_name("valueWithChecksum")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("MrzField.Companion")))
@interface IdentityMrzFieldCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityMrzFieldCompanion *shared __attribute__((swift_name("shared")));
- (IdentityMrzField *)fromStringWithChecksumValueWithChecksum:(NSString *)valueWithChecksum __attribute__((swift_name("fromStringWithChecksum(valueWithChecksum:)")));
- (IdentityMrzField *)fromValueValue:(NSString *)value __attribute__((swift_name("fromValue(value:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RelyingParty")))
@interface IdentityRelyingParty : IdentityBase
- (instancetype)initWithLogoUri:(NSString *)logoUri name:(NSString *)name description:(NSString *)description reason:(NSString *)reason __attribute__((swift_name("init(logoUri:name:description:reason:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityRelyingPartyCompanion *companion __attribute__((swift_name("companion")));
- (IdentityRelyingParty *)doCopyLogoUri:(NSString *)logoUri name:(NSString *)name description:(NSString *)description reason:(NSString *)reason __attribute__((swift_name("doCopy(logoUri:name:description:reason:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *description_ __attribute__((swift_name("description_")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="logo_uri")
*/
@property (readonly) NSString *logoUri __attribute__((swift_name("logoUri")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) NSString *reason __attribute__((swift_name("reason")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RelyingParty.Companion")))
@interface IdentityRelyingPartyCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityRelyingPartyCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RequestedClaim")))
@interface IdentityRequestedClaim : IdentityBase
- (instancetype)initWithName:(NSString *)name displayName:(NSString * _Nullable)displayName isEssential:(BOOL)isEssential values:(NSArray<NSString *> * _Nullable)values __attribute__((swift_name("init(name:displayName:isEssential:values:)"))) __attribute__((objc_designated_initializer));
- (IdentityRequestedClaim *)doCopyName:(NSString *)name displayName:(NSString * _Nullable)displayName isEssential:(BOOL)isEssential values:(NSArray<NSString *> * _Nullable)values __attribute__((swift_name("doCopy(name:displayName:isEssential:values:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable displayName __attribute__((swift_name("displayName")));
@property (readonly) BOOL isEssential __attribute__((swift_name("isEssential")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) NSArray<NSString *> * _Nullable values __attribute__((swift_name("values")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RespondableLoginRequest")))
@interface IdentityRespondableLoginRequest : IdentityLoginRequest
- (instancetype)initWithJwt:(IdentityJwt *)jwt translations:(NSDictionary<NSString *, id> *)translations __attribute__((swift_name("init(jwt:translations:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (instancetype)initWithTranslations:(NSDictionary<NSString *, id> *)translations claims:(NSArray<IdentityRequestedClaim *> *)claims acrs:(NSArray<NSString *> *)acrs relyingParty:(IdentityRelyingParty *)relyingParty json:(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *)json jwt:(IdentityJwt *)jwt __attribute__((swift_name("init(translations:claims:acrs:relyingParty:json:jwt:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityRespondableLoginRequestCompanion *companion __attribute__((swift_name("companion")));

/**
 * @note This method converts instances of Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)acceptClaims:(NSArray<IdentityClaim *> *)claims completionHandler:(void (^)(IdentityLoginResponse * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("accept(claims:completionHandler:)")));

/**
 * @note This method converts instances of Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)denyWithCompletionHandler:(void (^)(IdentityKotlinNothing * _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("deny(completionHandler:)")));
@property NSArray<IdentityReverificationRequest *> *reverifications __attribute__((swift_name("reverifications")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RespondableLoginRequest.Companion")))
@interface IdentityRespondableLoginRequestCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityRespondableLoginRequestCompanion *shared __attribute__((swift_name("shared")));
- (IdentityRespondableLoginRequest *)fromLoginRequestLoginRequest:(IdentityLoginRequest *)loginRequest reverifications:(NSArray<IdentityReverificationRequest *> *)reverifications accept:(id<IdentityKotlinx_coroutines_coreDeferred> (^)(NSArray<IdentityJwt *> *))accept deny:(id<IdentityKotlinx_coroutines_coreDeferred> (^)(void))deny __attribute__((swift_name("fromLoginRequest(loginRequest:reverifications:accept:deny:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ReverificationRequest.Companion")))
@interface IdentityReverificationRequestCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityReverificationRequestCompanion *shared __attribute__((swift_name("shared")));

/**
 * @note This method converts instances of IllegalArgumentException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (IdentityReverificationRequest * _Nullable)forAcrString:(NSString *)string loginRequest:(IdentityLoginRequest *)loginRequest error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("forAcr(string:loginRequest:)")));
@end

__attribute__((swift_name("VerificationMethod")))
@interface IdentityVerificationMethod : IdentityBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property (class, readonly, getter=companion) IdentityVerificationMethodCompanion *companion __attribute__((swift_name("companion")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationMethod.Companion")))
@interface IdentityVerificationMethodCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityVerificationMethodCompanion *shared __attribute__((swift_name("shared")));
- (IdentityVerificationMethod *)fromJsonJson:(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *)json __attribute__((swift_name("fromJson(json:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationMethod.IProov")))
@interface IdentityVerificationMethodIProov : IdentityVerificationMethod
- (instancetype)initWithToken:(NSString *)token url:(NSString *)url __attribute__((swift_name("init(token:url:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityVerificationMethodIProovCompanion *companion __attribute__((swift_name("companion")));
- (IdentityVerificationMethodIProov *)doCopyToken:(NSString *)token url:(NSString *)url __attribute__((swift_name("doCopy(token:url:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *token __attribute__((swift_name("token")));
@property (readonly) NSString *url __attribute__((swift_name("url")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("VerificationMethod.IProovCompanion")))
@interface IdentityVerificationMethodIProovCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityVerificationMethodIProovCompanion *shared __attribute__((swift_name("shared")));
- (IdentityVerificationMethodIProov *)fromConfigJson:(NSDictionary<NSString *, IdentityKotlinx_serialization_jsonJsonElement *> *)json __attribute__((swift_name("fromConfig(json:)")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * A deserializer for Credentials that can be extended by registering custom CredentialFactory instances.
 * This allows plugins or other modules to introduce new credential types.
 */
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("CredentialDeserializer")))
@interface IdentityCredentialDeserializer : IdentityBase

/**
 * A deserializer for Credentials that can be extended by registering custom CredentialFactory instances.
 * This allows plugins or other modules to introduce new credential types.
 */
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));

/**
 * A deserializer for Credentials that can be extended by registering custom CredentialFactory instances.
 * This allows plugins or other modules to introduce new credential types.
 */
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property (class, readonly, getter=companion) IdentityCredentialDeserializerCompanion *companion __attribute__((swift_name("companion")));

/**
 * Deserializes a Credential from a source string and a list of claims.
 * It first checks registered custom factories, then default deserializers.
 * If no specific handler is found, it returns a generic Credential instance.
 *
 * @param source The source string identifying the credential type and instance.
 * @param claims The list of claims for the credential.
 * @return A specific Credential instance if a handler is found, or a generic Credential otherwise.
 */
- (IdentityCredential *)deserializeSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("deserialize(source:claims:)")));

/**
 * Registers a custom CredentialFactory.
 * If a factory for the same prefix already exists (either custom or default),
 * a warning is printed, and the new factory will take precedence over custom ones,
 * and custom ones take precedence over defaults.
 *
 * @param factory The CredentialFactory to register.
 */
- (void)registerFactoryFactory:(id<IdentityCredentialFactory>)factory __attribute__((swift_name("registerFactory(factory:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("CredentialDeserializer.Companion")))
@interface IdentityCredentialDeserializerCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityCredentialDeserializerCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *TAG __attribute__((swift_name("TAG")));
@property (readonly) NSDictionary<NSString *, IdentityCredential *(^)(NSString *, NSArray<IdentityClaim *> *)> *defaultDeserializer __attribute__((swift_name("defaultDeserializer")));
@end


/**
 * Defines a contract for creating a specific type of Credential.
 * Implementations of this interface can be registered with the PluggableCredentialDeserializer.
 */
__attribute__((swift_name("CredentialFactory")))
@protocol IdentityCredentialFactory
@required

/**
 * Creates a Credential instance from the given source and claims.
 *
 * @param source The full source string for the credential (e.g., "fp:user-thumb").
 * @param claims The list of claims associated with this credential.
 * @return The constructed Credential object.
 */
- (IdentityCredential *)createCredentialSource:(NSString *)source claims:(NSArray<IdentityClaim *> *)claims __attribute__((swift_name("createCredential(source:claims:)")));

/**
 * The unique prefix string that this factory handles (e.g., "iddoc").
 * This prefix is typically the part of the source string before the first colon.
 * Can be used to override the deserialization of existing credentials
 */
@property (readonly) NSString *prefix __attribute__((swift_name("prefix")));
@end

__attribute__((swift_name("StorageEngine")))
@protocol IdentityStorageEngine
@required
- (void)deleteAll __attribute__((swift_name("deleteAll()")));

/**
 * @note This method converts instances of IOException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (NSString * _Nullable)readKey:(NSString *)key error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("read(key:)"))) __attribute__((swift_error(nonnull_error)));

/**
 * @note This method converts instances of IOException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)writeKey:(NSString *)key value:(NSString * _Nullable)value error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("write(key:value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DeviceBoundAppleStorageEngine")))
@interface IdentityDeviceBoundAppleStorageEngine : IdentityBase <IdentityStorageEngine>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)deleteAll __attribute__((swift_name("deleteAll()")));

/**
 * @note This method converts instances of IOException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (NSString * _Nullable)readKey:(NSString *)key error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("read(key:)"))) __attribute__((swift_error(nonnull_error)));

/**
 * @note This method converts instances of IOException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)writeKey:(NSString *)key value:(NSString * _Nullable)value error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("write(key:value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("FileStorage")))
@interface IdentityFileStorage : IdentityBase
- (instancetype)initWithFileName:(NSString *)fileName __attribute__((swift_name("init(fileName:)"))) __attribute__((objc_designated_initializer));

/**
 * Archives the provided NSDictionary into NSData using NSKeyedArchiver with secure coding.
 *
 * It enforces secure coding (`requiringSecureCoding = true`)
 * and wraps potential `NSError` results or `nil` returns in a `StorageException`.
 * Primarily used to serialize data before encryption or persistence.
 *
 * @param data The NSDictionary instance originating from or bridged for iOS.
 * @return NSData containing the securely archived representation of the input dictionary.
 * @throws StorageException if `NSKeyedArchiver` fails during serialization.
 */
- (NSData *)archiveDictionaryData:(NSDictionary *)data __attribute__((swift_name("archiveDictionary(data:)")));

/**
 * @note This method converts instances of StorageException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)deleteAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("delete()")));
- (void)preventBackup __attribute__((swift_name("preventBackup()")));
- (NSData *)read __attribute__((swift_name("read()")));

/**
 * Unarchives NSData into an NSDictionary using the secure NSKeyedUnarchiver.
 *
 * Includes checks for `NSError` population (specifically if the result is nil) and
 * explicitly verifies the returned root object is non-null and of the expected
 * `NSDictionary` type. Wraps various failure conditions in a `StorageException`.
 *
 * @param data The NSData containing the output of a corresponding NSKeyedArchiver process
 * (using compatible classes and secure coding).
 * @return The successfully unarchived NSDictionary.
 * @throws StorageException If unarchiving fails due to decoding errors, nil return,
 * `NSError` being set, or the root object having an unexpected type.
 */
- (NSDictionary *)unarchiveDataData:(NSData *)data __attribute__((swift_name("unarchiveData(data:)")));

/**
 * Writes the provided NSData to the member `fileUrl` atomically.
 *
 * Ensures the target directory exists by calling `ensureDirectoryExists()` first.
 * Uses `NSData.writeToURL` with the `NSDataWritingAtomic` option for safer writes
 * (writes to a temporary file then renames).
 *
 * Handles potential `NSError` and wraps failures in a `StorageException`.
 * Assumes `fileUrl` is an initialized member variable.
 *
 * @param data The NSData to write to disk.
 * @throws StorageException if the directory cannot be created or the file write fails.
 *
 * @note This method converts instances of StorageException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)writeData:(NSData *)data error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("write(data:)")));
@property (readonly) BOOL fileHasBeenCreated __attribute__((swift_name("fileHasBeenCreated")));
@end

__attribute__((swift_name("SyncedKeyValueStorage")))
@protocol IdentitySyncedKeyValueStorage
@required
- (NSString * _Nullable)readKey:(NSString *)key __attribute__((swift_name("read(key_:)")));
- (void)writeKey:(NSString *)key value:(NSString * _Nullable)value __attribute__((swift_name("write(key:value_:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ICloudKeyValueStorage")))
@interface IdentityICloudKeyValueStorage : IdentityBase <IdentitySyncedKeyValueStorage>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (NSString * _Nullable)readKey:(NSString *)key __attribute__((swift_name("read(key_:)")));
- (void)writeKey:(NSString *)key value:(NSString * _Nullable)value __attribute__((swift_name("write(key:value_:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("InMemoryStorageEngine")))
@interface IdentityInMemoryStorageEngine : IdentityBase <IdentityStorageEngine>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)deleteAll __attribute__((swift_name("deleteAll()")));

/**
 * @note This method converts instances of IOException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (NSString * _Nullable)readKey:(NSString *)key error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("read(key:)"))) __attribute__((swift_error(nonnull_error)));

/**
 * @note This method converts instances of IOException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (BOOL)writeKey:(NSString *)key value:(NSString * _Nullable)value error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("write(key:value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Keychain")))
@interface IdentityKeychain : IdentityBase
- (instancetype)initWithNamespace:(NSString *)namespace_ __attribute__((swift_name("init(namespace:)"))) __attribute__((objc_designated_initializer));
- (void)deleteKey:(NSString *)key __attribute__((swift_name("delete(key:)")));
- (NSString * _Nullable)getKey:(NSString *)key __attribute__((swift_name("get(key:)")));
- (void)setKey:(NSString *)key value:(NSString *)value __attribute__((swift_name("set(key:value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("LocalStorage")))
@interface IdentityLocalStorage : IdentityBase
- (instancetype)initWithStorageEngine:(id<IdentityStorageEngine>)storageEngine __attribute__((swift_name("init(storageEngine:)"))) __attribute__((objc_designated_initializer));
- (void)deleteAll __attribute__((swift_name("deleteAll()")));
@property NSString * _Nullable attestationToken __attribute__((swift_name("attestationToken")));
@property NSArray<IdentityJwt *> *jwts __attribute__((swift_name("jwts")));
@property NSDictionary<NSString *, id> * _Nullable translations __attribute__((swift_name("translations")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Repository")))
@interface IdentityRepository : IdentityBase
- (instancetype)initWithLocalStorage:(IdentityLocalStorage *)localStorage credentialDeserializer:(IdentityCredentialDeserializer *)credentialDeserializer __attribute__((swift_name("init(localStorage:credentialDeserializer:)"))) __attribute__((objc_designated_initializer));
- (NSArray<IdentityJwt *> *)addOrUpdateJwtsJwts:(NSArray<IdentityJwt *> *)jwts __attribute__((swift_name("addOrUpdateJwts(jwts:)")));
- (void)deleteJwtsJwtsToDelete:(NSArray<IdentityJwt *> *)jwtsToDelete __attribute__((swift_name("deleteJwts(jwtsToDelete:)")));
- (NSArray<IdentityClaim *> *)getAllClaims __attribute__((swift_name("getAllClaims()")));
- (NSArray<IdentityCredential *> *)getAllCredentials __attribute__((swift_name("getAllCredentials()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StorageException")))
@interface IdentityStorageException : IdentityKotlinException
- (instancetype)initWithMessage:(NSString *)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@end

@interface IdentityWallet (Extensions)

/**
 * @note This method converts instances of WalletNotRegisteredException, ApiException, CancellationException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (IdentityFlowWrapper<IdentityVerificationEvent *> * _Nullable)addDocumentWithReferenceReference:(NSString *)reference demoReferencePhoto:(NSData * _Nullable)demoReferencePhoto loginRequest:(IdentityLoginRequest * _Nullable)loginRequest options:(IdentitySdkIproovOptions * _Nullable)options error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("addDocumentWithReference(reference:demoReferencePhoto:loginRequest:options:)")));

/**
 * @note This method converts instances of WalletNotRegisteredException, RequiredClaimNotPresent, ApiException, CancellationException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (IdentityFlowWrapper<IdentityVerificationEvent *> * _Nullable)addFaceVerificationCredential:(IdentityCredential *)credential loginRequest:(IdentityLoginRequest * _Nullable)loginRequest options:(IdentitySdkIproovOptions * _Nullable)options error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("addFaceVerification(credential:loginRequest:options:)")));
@end

@interface IdentityChallenge (Extensions)
@property (readonly) NSData * _Nullable challenge __attribute__((swift_name("challenge")));
@property (readonly) NSDate *expires __attribute__((swift_name("expires")));
@end

@interface IdentityDocumentChallengeResponder (Extensions)

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)withMrtdMrtd:(IdentityMrtdData *)mrtd accessControl:(IdentityAccessControl *)accessControl signature:(NSData * _Nullable)signature completionHandler:(void (^)(IdentityKotlinNothing * _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("withMrtd(mrtd:accessControl:signature:completionHandler:)")));
@end

@interface IdentityActiveAuthentication (Extensions)
@property (readonly) NSData *challenge __attribute__((swift_name("challenge")));
@property (readonly) NSData *secret __attribute__((swift_name("secret")));
@end

@interface IdentityFaceReverificationRequest (Extensions)

/**
 * @note This method converts instances of WalletNotRegisteredException, RequiredClaimNotPresent, ApiException, CancellationException, AppIdNotSupportedException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (IdentityFlowWrapper<IdentityVerificationEvent *> * _Nullable)verifyCredential:(IdentityCredentialIdentityCredentialMrtd *)credential options:(IdentitySdkIproovOptions * _Nullable)options error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("verify(credential:options:)")));
@end

@interface IdentityJwt (Extensions)
- (BOOL)isSameAsOther:(IdentityJwt *)other __attribute__((swift_name("isSameAs(other:)")));
@end

@interface IdentityMrtdData (Extensions)
@property (readonly) NSData * _Nullable com __attribute__((swift_name("com")));
@property (readonly) NSData * _Nullable cvca __attribute__((swift_name("cvca")));
@property (readonly) NSData *dg1 __attribute__((swift_name("dg1")));
@property (readonly) NSData * _Nullable dg10 __attribute__((swift_name("dg10")));
@property (readonly) NSData * _Nullable dg11 __attribute__((swift_name("dg11")));
@property (readonly) NSData * _Nullable dg12 __attribute__((swift_name("dg12")));
@property (readonly) NSData * _Nullable dg13 __attribute__((swift_name("dg13")));
@property (readonly) NSData * _Nullable dg14 __attribute__((swift_name("dg14")));
@property (readonly) NSData * _Nullable dg15 __attribute__((swift_name("dg15")));
@property (readonly) NSData * _Nullable dg16 __attribute__((swift_name("dg16")));
@property (readonly) NSData *dg2 __attribute__((swift_name("dg2")));
@property (readonly) NSData * _Nullable dg3 __attribute__((swift_name("dg3")));
@property (readonly) NSData * _Nullable dg4 __attribute__((swift_name("dg4")));
@property (readonly) NSData * _Nullable dg5 __attribute__((swift_name("dg5")));
@property (readonly) NSData * _Nullable dg6 __attribute__((swift_name("dg6")));
@property (readonly) NSData * _Nullable dg7 __attribute__((swift_name("dg7")));
@property (readonly) NSData * _Nullable dg8 __attribute__((swift_name("dg8")));
@property (readonly) NSData * _Nullable dg9 __attribute__((swift_name("dg9")));
@property (readonly) NSData *sod __attribute__((swift_name("sod")));
@end

__attribute__((swift_name("Ktor_httpHttpMessage")))
@protocol IdentityKtor_httpHttpMessage
@required
@property (readonly) id<IdentityKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreCoroutineScope")))
@protocol IdentityKotlinx_coroutines_coreCoroutineScope
@required
@property (readonly) id<IdentityKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@end

__attribute__((swift_name("Ktor_client_coreHttpResponse")))
@interface IdentityKtor_client_coreHttpResponse : IdentityBase <IdentityKtor_httpHttpMessage, IdentityKotlinx_coroutines_coreCoroutineScope>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) IdentityKtor_client_coreHttpClientCall *call __attribute__((swift_name("call")));
@property (readonly) id<IdentityKtor_ioByteReadChannel> rawContent __attribute__((swift_name("rawContent")));
@property (readonly) IdentityKtor_utilsGMTDate *requestTime __attribute__((swift_name("requestTime")));
@property (readonly) IdentityKtor_utilsGMTDate *responseTime __attribute__((swift_name("responseTime")));
@property (readonly) IdentityKtor_httpHttpStatusCode *status __attribute__((swift_name("status")));
@property (readonly) IdentityKtor_httpHttpProtocolVersion *version __attribute__((swift_name("version")));
@end

@interface IdentityKtor_client_coreHttpResponse (Extensions)

/**
 * @note This method converts instances of ApiException, CancellationException, Exception to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)validateWithCompletionHandler:(void (^)(IdentityKtor_client_coreHttpResponse * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("validate(completionHandler:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinByteArray")))
@interface IdentityKotlinByteArray : IdentityBase
+ (instancetype)arrayWithSize:(int32_t)size __attribute__((swift_name("init(size:)")));
+ (instancetype)arrayWithSize:(int32_t)size init:(IdentityByte *(^)(IdentityInt *))init __attribute__((swift_name("init(size:init:)")));
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (int8_t)getIndex:(int32_t)index __attribute__((swift_name("get(index:)")));
- (IdentityKotlinByteIterator *)iterator __attribute__((swift_name("iterator()")));
- (void)setIndex:(int32_t)index value:(int8_t)value __attribute__((swift_name("set(index:value:)")));
@property (readonly) int32_t size __attribute__((swift_name("size")));
@end

@interface IdentityKotlinByteArray (Extensions)
- (void * _Nullable)toCFData __attribute__((swift_name("toCFData()")));
- (NSData *)toNSData __attribute__((swift_name("toNSData()")));
@end

@interface IdentityKotlinThrowable (Extensions)
- (NSError *)toNSErrorDomain:(NSString *)domain code:(int64_t)code __attribute__((swift_name("toNSError(domain:code:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/serialization/json/JsonElementSerializer))
*/
__attribute__((swift_name("Kotlinx_serialization_jsonJsonElement")))
@interface IdentityKotlinx_serialization_jsonJsonElement : IdentityBase
@property (class, readonly, getter=companion) IdentityKotlinx_serialization_jsonJsonElementCompanion *companion __attribute__((swift_name("companion")));
@end

@interface IdentityKotlinx_serialization_jsonJsonElement (Extensions)
- (id _Nullable)toNativeTypes __attribute__((swift_name("toNativeTypes()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ActiveAuthentication_appleKt")))
@interface IdentityActiveAuthentication_appleKt : IdentityBase
+ (IdentityKotlinByteArray *)generateRandomBytesLength:(int32_t)length __attribute__((swift_name("generateRandomBytes(length:)")));
+ (IdentityKotlinByteArray *)hashData:(IdentityKotlinByteArray *)data __attribute__((swift_name("hash(data:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ApiClient_appleKt")))
@interface IdentityApiClient_appleKt : IdentityBase

/**
 * This will be called each signed post request to the backend, at the moment only getting the iOS assertion header
 * on iOS and keyId is provided, however may contain more headers in the future.
 *
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
+ (void)getPlatformHeadersJws:(NSString *)jws keyId:(NSString * _Nullable)keyId completionHandler:(void (^)(NSDictionary<NSString *, NSString *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getPlatformHeaders(jws:keyId:completionHandler:)")));
@property (class, readonly) IdentityKtor_client_coreHttpClient *httpClient __attribute__((swift_name("httpClient")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AttestationService_appleKt")))
@interface IdentityAttestationService_appleKt : IdentityBase
+ (IdentityKotlinByteArray *)hashInput:(IdentityKotlinByteArray *)input __attribute__((swift_name("hash(input:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KeyPair_appleKt")))
@interface IdentityKeyPair_appleKt : IdentityBase
+ (IdentityJwk *)derToJwkDerBytes:(IdentityKotlinByteArray *)derBytes __attribute__((swift_name("derToJwk(derBytes:)")));
+ (id _Nullable)getCFDictionaryValueDictionary:(void * _Nullable)dictionary key:(void * _Nullable)key __attribute__((swift_name("getCFDictionaryValue(dictionary:key:)")));
+ (id<IdentityKeyPair>)getKeyPair __attribute__((swift_name("getKeyPair()")));
+ (IdentityKotlinTriple<NSString *, IdentityKotlinByteArray *, IdentityKotlinByteArray *> *)parseEcPublicKeyFromDerDerBytes:(IdentityKotlinByteArray *)derBytes __attribute__((swift_name("parseEcPublicKeyFromDer(derBytes:)")));
+ (IdentityLength *)toLength:(int8_t)receiver input:(IdentityKotlinByteArray *)input startIndex:(int32_t)startIndex __attribute__((swift_name("toLength(_:input:startIndex:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KeyPairKt")))
@interface IdentityKeyPairKt : IdentityBase
+ (IdentityKotlinByteArray *)asn1ToRsSignature:(IdentityKotlinByteArray *)signature __attribute__((swift_name("asn1ToRs(signature:)")));
+ (IdentityKotlinByteArray *)signRs:(id<IdentityKeyPair>)receiver data:(IdentityKotlinByteArray *)data __attribute__((swift_name("signRs(_:data:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Keychain_appleKt")))
@interface IdentityKeychain_appleKt : IdentityBase
+ (void *)createCFDictionaryMap:(NSDictionary<id, id> *)map __attribute__((swift_name("createCFDictionary(map:)")));

/**
 * Converts a CFDataRef to a Kotlin ByteArray.
 * This function creates a copy of the data, so it's safe to release the CFDataRef after calling this.
 */
+ (IdentityKotlinByteArray *)toByteArray:(void *)receiver __attribute__((swift_name("toByteArray(_:)")));
+ (IdentityKotlinByteArray *)toByteArray_:(NSData *)receiver __attribute__((swift_name("toByteArray(__:)")));
+ (void * _Nullable)toCFNumber:(int32_t)receiver __attribute__((swift_name("toCFNumber(_:)")));
+ (void * _Nullable)toCFString:(NSString *)receiver __attribute__((swift_name("toCFString(_:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StorageEngine_appleKt")))
@interface IdentityStorageEngine_appleKt : IdentityBase
+ (id<IdentityStorageEngine>)getDeviceBoundStorageEngine __attribute__((swift_name("getDeviceBoundStorageEngine()")));
+ (id<IdentityStorageEngine>)getSyncedKeyValueStorageEngine __attribute__((swift_name("getSyncedKeyValueStorageEngine()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SymmetricKeyKt")))
@interface IdentitySymmetricKeyKt : IdentityBase
@property (class, readonly) int32_t AES_BLOCK_SIZE_BYTES __attribute__((swift_name("AES_BLOCK_SIZE_BYTES")));
@property (class, readonly) int32_t AES_KEY_SIZE_BYTES __attribute__((swift_name("AES_KEY_SIZE_BYTES")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SyncedKeyValueStorage_appleKt")))
@interface IdentitySyncedKeyValueStorage_appleKt : IdentityBase
+ (id<IdentitySyncedKeyValueStorage>)getSyncedKeyValueStorage __attribute__((swift_name("getSyncedKeyValueStorage()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserAgent_appleKt")))
@interface IdentityUserAgent_appleKt : IdentityBase
+ (IdentityUserAgent *)getUserAgent __attribute__((swift_name("getUserAgent()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Wallet_appleKt")))
@interface IdentityWallet_appleKt : IdentityBase
+ (IdentityWallet *)getWalletInstanceBaseUrl:(NSString *)baseUrl isLoggingEnabled:(BOOL)isLoggingEnabled storageEngine:(id<IdentityStorageEngine>)storageEngine keyPairFactory:(id<IdentityKeyPair> (^)(void))keyPairFactory credentialDeserializer:(IdentityCredentialDeserializer *)credentialDeserializer __attribute__((swift_name("getWalletInstance(baseUrl:isLoggingEnabled:storageEngine:keyPairFactory:credentialDeserializer:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinArray")))
@interface IdentityKotlinArray<T> : IdentityBase
+ (instancetype)arrayWithSize:(int32_t)size init:(T _Nullable (^)(IdentityInt *))init __attribute__((swift_name("init(size:init:)")));
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (T _Nullable)getIndex:(int32_t)index __attribute__((swift_name("get(index:)")));
- (id<IdentityKotlinIterator>)iterator __attribute__((swift_name("iterator()")));
- (void)setIndex:(int32_t)index value:(T _Nullable)value __attribute__((swift_name("set(index:value:)")));
@property (readonly) int32_t size __attribute__((swift_name("size")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinEnumCompanion")))
@interface IdentityKotlinEnumCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKotlinEnumCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((swift_name("KotlinRuntimeException")))
@interface IdentityKotlinRuntimeException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((swift_name("KotlinIllegalStateException")))
@interface IdentityKotlinIllegalStateException : IdentityKotlinRuntimeException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.4")
*/
__attribute__((swift_name("KotlinCancellationException")))
@interface IdentityKotlinCancellationException : IdentityKotlinIllegalStateException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpStatusCode")))
@interface IdentityKtor_httpHttpStatusCode : IdentityBase <IdentityKotlinComparable>
- (instancetype)initWithValue:(int32_t)value description:(NSString *)description __attribute__((swift_name("init(value:description:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKtor_httpHttpStatusCodeCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(IdentityKtor_httpHttpStatusCode *)other __attribute__((swift_name("compareTo(other:)")));
- (IdentityKtor_httpHttpStatusCode *)doCopyValue:(int32_t)value description:(NSString *)description __attribute__((swift_name("doCopy(value:description:)")));
- (IdentityKtor_httpHttpStatusCode *)descriptionValue:(NSString *)value __attribute__((swift_name("description(value:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *description_ __attribute__((swift_name("description_")));
@property (readonly) int32_t value __attribute__((swift_name("value")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/InstantIso8601Serializer))
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeInstant")))
@interface IdentityKotlinx_datetimeInstant : IdentityBase <IdentityKotlinComparable>
@property (class, readonly, getter=companion) IdentityKotlinx_datetimeInstantCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(IdentityKotlinx_datetimeInstant *)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (IdentityKotlinx_datetimeInstant *)minusDuration:(int64_t)duration __attribute__((swift_name("minus(duration:)")));
- (int64_t)minusOther:(IdentityKotlinx_datetimeInstant *)other __attribute__((swift_name("minus(other:)")));
- (IdentityKotlinx_datetimeInstant *)plusDuration:(int64_t)duration __attribute__((swift_name("plus(duration:)")));
- (int64_t)toEpochMilliseconds __attribute__((swift_name("toEpochMilliseconds()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int64_t epochSeconds __attribute__((swift_name("epochSeconds")));
@property (readonly) int32_t nanosecondsOfSecond __attribute__((swift_name("nanosecondsOfSecond")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
*/
__attribute__((swift_name("KotlinCoroutineContext")))
@protocol IdentityKotlinCoroutineContext
@required
- (id _Nullable)foldInitial:(id _Nullable)initial operation:(id _Nullable (^)(id _Nullable, id<IdentityKotlinCoroutineContextElement>))operation __attribute__((swift_name("fold(initial:operation:)")));
- (id<IdentityKotlinCoroutineContextElement> _Nullable)getKey:(id<IdentityKotlinCoroutineContextKey>)key __attribute__((swift_name("get(key:)")));
- (id<IdentityKotlinCoroutineContext>)minusKeyKey:(id<IdentityKotlinCoroutineContextKey>)key __attribute__((swift_name("minusKey(key:)")));
- (id<IdentityKotlinCoroutineContext>)plusContext:(id<IdentityKotlinCoroutineContext>)context __attribute__((swift_name("plus(context:)")));
@end

__attribute__((swift_name("KotlinCoroutineContextElement")))
@protocol IdentityKotlinCoroutineContextElement <IdentityKotlinCoroutineContext>
@required
@property (readonly) id<IdentityKotlinCoroutineContextKey> key __attribute__((swift_name("key")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreJob")))
@protocol IdentityKotlinx_coroutines_coreJob <IdentityKotlinCoroutineContextElement>
@required

/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
- (id<IdentityKotlinx_coroutines_coreChildHandle>)attachChildChild:(id<IdentityKotlinx_coroutines_coreChildJob>)child __attribute__((swift_name("attachChild(child:)")));
- (void)cancelCause:(IdentityKotlinCancellationException * _Nullable)cause __attribute__((swift_name("cancel(cause:)")));

/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
- (IdentityKotlinCancellationException *)getCancellationException __attribute__((swift_name("getCancellationException()")));
- (id<IdentityKotlinx_coroutines_coreDisposableHandle>)invokeOnCompletionHandler:(void (^)(IdentityKotlinThrowable * _Nullable))handler __attribute__((swift_name("invokeOnCompletion(handler:)")));

/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
- (id<IdentityKotlinx_coroutines_coreDisposableHandle>)invokeOnCompletionOnCancelling:(BOOL)onCancelling invokeImmediately:(BOOL)invokeImmediately handler:(void (^)(IdentityKotlinThrowable * _Nullable))handler __attribute__((swift_name("invokeOnCompletion(onCancelling:invokeImmediately:handler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)joinWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("join(completionHandler:)")));
- (id<IdentityKotlinx_coroutines_coreJob>)plusOther:(id<IdentityKotlinx_coroutines_coreJob>)other __attribute__((swift_name("plus(other:)"))) __attribute__((unavailable("Operator '+' on two Job objects is meaningless. Job is a coroutine context element and `+` is a set-sum operator for coroutine contexts. The job to the right of `+` just replaces the job the left of `+`.")));
- (BOOL)start __attribute__((swift_name("start()")));
@property (readonly) id<IdentityKotlinSequence> children __attribute__((swift_name("children")));
@property (readonly) BOOL isActive __attribute__((swift_name("isActive")));
@property (readonly) BOOL isCancelled __attribute__((swift_name("isCancelled")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) id<IdentityKotlinx_coroutines_coreSelectClause0> onJoin __attribute__((swift_name("onJoin")));

/**
 * @note annotations
 *   kotlinx.coroutines.ExperimentalCoroutinesApi
*/
@property (readonly) id<IdentityKotlinx_coroutines_coreJob> _Nullable parent __attribute__((swift_name("parent")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreDeferred")))
@protocol IdentityKotlinx_coroutines_coreDeferred <IdentityKotlinx_coroutines_coreJob>
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)awaitWithCompletionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("await(completionHandler:)")));

/**
 * @note annotations
 *   kotlinx.coroutines.ExperimentalCoroutinesApi
*/
- (id _Nullable)getCompleted __attribute__((swift_name("getCompleted()")));

/**
 * @note annotations
 *   kotlinx.coroutines.ExperimentalCoroutinesApi
*/
- (IdentityKotlinThrowable * _Nullable)getCompletionExceptionOrNull __attribute__((swift_name("getCompletionExceptionOrNull()")));
@property (readonly) id<IdentityKotlinx_coroutines_coreSelectClause1> onAwait __attribute__((swift_name("onAwait")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinNothing")))
@interface IdentityKotlinNothing : IdentityBase
@end

__attribute__((swift_name("Kotlinx_serialization_coreEncoder")))
@protocol IdentityKotlinx_serialization_coreEncoder
@required
- (id<IdentityKotlinx_serialization_coreCompositeEncoder>)beginCollectionDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor collectionSize:(int32_t)collectionSize __attribute__((swift_name("beginCollection(descriptor:collectionSize:)")));
- (id<IdentityKotlinx_serialization_coreCompositeEncoder>)beginStructureDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("beginStructure(descriptor:)")));
- (void)encodeBooleanValue:(BOOL)value __attribute__((swift_name("encodeBoolean(value:)")));
- (void)encodeByteValue:(int8_t)value __attribute__((swift_name("encodeByte(value:)")));
- (void)encodeCharValue:(unichar)value __attribute__((swift_name("encodeChar(value:)")));
- (void)encodeDoubleValue:(double)value __attribute__((swift_name("encodeDouble(value:)")));
- (void)encodeEnumEnumDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)enumDescriptor index:(int32_t)index __attribute__((swift_name("encodeEnum(enumDescriptor:index:)")));
- (void)encodeFloatValue:(float)value __attribute__((swift_name("encodeFloat(value:)")));
- (id<IdentityKotlinx_serialization_coreEncoder>)encodeInlineDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("encodeInline(descriptor:)")));
- (void)encodeIntValue:(int32_t)value __attribute__((swift_name("encodeInt(value:)")));
- (void)encodeLongValue:(int64_t)value __attribute__((swift_name("encodeLong(value:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)encodeNotNullMark __attribute__((swift_name("encodeNotNullMark()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)encodeNull __attribute__((swift_name("encodeNull()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)encodeNullableSerializableValueSerializer:(id<IdentityKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeNullableSerializableValue(serializer:value:)")));
- (void)encodeSerializableValueSerializer:(id<IdentityKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeSerializableValue(serializer:value:)")));
- (void)encodeShortValue:(int16_t)value __attribute__((swift_name("encodeShort(value:)")));
- (void)encodeStringValue:(NSString *)value __attribute__((swift_name("encodeString(value:)")));
@property (readonly) IdentityKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreSerialDescriptor")))
@protocol IdentityKotlinx_serialization_coreSerialDescriptor
@required
- (NSArray<id<IdentityKotlinAnnotation>> *)getElementAnnotationsIndex:(int32_t)index __attribute__((swift_name("getElementAnnotations(index:)")));
- (id<IdentityKotlinx_serialization_coreSerialDescriptor>)getElementDescriptorIndex:(int32_t)index __attribute__((swift_name("getElementDescriptor(index:)")));
- (int32_t)getElementIndexName:(NSString *)name __attribute__((swift_name("getElementIndex(name:)")));
- (NSString *)getElementNameIndex:(int32_t)index __attribute__((swift_name("getElementName(index:)")));
- (BOOL)isElementOptionalIndex:(int32_t)index __attribute__((swift_name("isElementOptional(index:)")));
@property (readonly) NSArray<id<IdentityKotlinAnnotation>> *annotations __attribute__((swift_name("annotations")));
@property (readonly) int32_t elementsCount __attribute__((swift_name("elementsCount")));
@property (readonly) BOOL isInline __attribute__((swift_name("isInline")));
@property (readonly) BOOL isNullable __attribute__((swift_name("isNullable")));
@property (readonly) IdentityKotlinx_serialization_coreSerialKind *kind __attribute__((swift_name("kind")));
@property (readonly) NSString *serialName __attribute__((swift_name("serialName")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreDecoder")))
@protocol IdentityKotlinx_serialization_coreDecoder
@required
- (id<IdentityKotlinx_serialization_coreCompositeDecoder>)beginStructureDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("beginStructure(descriptor:)")));
- (BOOL)decodeBoolean __attribute__((swift_name("decodeBoolean()")));
- (int8_t)decodeByte __attribute__((swift_name("decodeByte()")));
- (unichar)decodeChar __attribute__((swift_name("decodeChar()")));
- (double)decodeDouble __attribute__((swift_name("decodeDouble()")));
- (int32_t)decodeEnumEnumDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)enumDescriptor __attribute__((swift_name("decodeEnum(enumDescriptor:)")));
- (float)decodeFloat __attribute__((swift_name("decodeFloat()")));
- (id<IdentityKotlinx_serialization_coreDecoder>)decodeInlineDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("decodeInline(descriptor:)")));
- (int32_t)decodeInt __attribute__((swift_name("decodeInt()")));
- (int64_t)decodeLong __attribute__((swift_name("decodeLong()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (BOOL)decodeNotNullMark __attribute__((swift_name("decodeNotNullMark()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (IdentityKotlinNothing * _Nullable)decodeNull __attribute__((swift_name("decodeNull()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id _Nullable)decodeNullableSerializableValueDeserializer:(id<IdentityKotlinx_serialization_coreDeserializationStrategy>)deserializer __attribute__((swift_name("decodeNullableSerializableValue(deserializer:)")));
- (id _Nullable)decodeSerializableValueDeserializer:(id<IdentityKotlinx_serialization_coreDeserializationStrategy>)deserializer __attribute__((swift_name("decodeSerializableValue(deserializer:)")));
- (int16_t)decodeShort __attribute__((swift_name("decodeShort()")));
- (NSString *)decodeString __attribute__((swift_name("decodeString()")));
@property (readonly) IdentityKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreFlow")))
@protocol IdentityKotlinx_coroutines_coreFlow
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)collectCollector:(id<IdentityKotlinx_coroutines_coreFlowCollector>)collector completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("collect(collector:completionHandler:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SdkIproovOptions")))
@interface IdentitySdkIproovOptions : IdentityBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property IdentitySdkCamera *camera __attribute__((swift_name("camera")));
@property NSArray<IdentitySdkIproovOptionsCertificate *> *certificates __attribute__((swift_name("certificates")));
@property IdentitySdkIproovOptionsCloseButton *closeButton __attribute__((swift_name("closeButton")));
@property BOOL disableExteriorEffects __attribute__((swift_name("disableExteriorEffects")));
@property BOOL enableScreenshots __attribute__((swift_name("enableScreenshots")));
@property IdentitySdkIproovOptionsFilter *filter __attribute__((swift_name("filter")));
@property NSString * _Nullable fontPath __attribute__((swift_name("fontPath")));
@property IdentitySdkIproovOptionsGenuinePresenceAssurance *genuinePresenceAssurance __attribute__((swift_name("genuinePresenceAssurance")));
@property int32_t headerBackgroundColor __attribute__((swift_name("headerBackgroundColor")));
@property IdentitySdkIproovOptionsLivenessAssurance *livenessAssurance __attribute__((swift_name("livenessAssurance")));
@property IdentityKotlinByteArray * _Nullable logo __attribute__((swift_name("logo")));
@property IdentitySdkOrientation *orientation __attribute__((swift_name("orientation")));
@property int32_t promptBackgroundColor __attribute__((swift_name("promptBackgroundColor")));
@property BOOL promptRoundedCorners __attribute__((swift_name("promptRoundedCorners")));
@property int32_t promptTextColor __attribute__((swift_name("promptTextColor")));
@property int32_t surroundColor __attribute__((swift_name("surroundColor")));
@property int32_t timeoutSecs __attribute__((swift_name("timeoutSecs")));
@property NSString *title __attribute__((swift_name("title")));
@property int32_t titleTextColor __attribute__((swift_name("titleTextColor")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.8")
 *   kotlin.io.encoding.ExperimentalEncodingApi
*/
__attribute__((swift_name("KotlinBase64")))
@interface IdentityKotlinBase64 : IdentityBase
@property (class, readonly, getter=companion) IdentityKotlinBase64Default *companion __attribute__((swift_name("companion")));
- (IdentityKotlinByteArray *)decodeSource:(IdentityKotlinByteArray *)source startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("decode(source:startIndex:endIndex:)")));
- (IdentityKotlinByteArray *)decodeSource:(id)source startIndex:(int32_t)startIndex endIndex_:(int32_t)endIndex __attribute__((swift_name("decode(source:startIndex:endIndex_:)")));
- (int32_t)decodeIntoByteArraySource:(IdentityKotlinByteArray *)source destination:(IdentityKotlinByteArray *)destination destinationOffset:(int32_t)destinationOffset startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("decodeIntoByteArray(source:destination:destinationOffset:startIndex:endIndex:)")));
- (int32_t)decodeIntoByteArraySource:(id)source destination:(IdentityKotlinByteArray *)destination destinationOffset:(int32_t)destinationOffset startIndex:(int32_t)startIndex endIndex_:(int32_t)endIndex __attribute__((swift_name("decodeIntoByteArray(source:destination:destinationOffset:startIndex:endIndex_:)")));
- (NSString *)encodeSource:(IdentityKotlinByteArray *)source startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("encode(source:startIndex:endIndex:)")));
- (int32_t)encodeIntoByteArraySource:(IdentityKotlinByteArray *)source destination:(IdentityKotlinByteArray *)destination destinationOffset:(int32_t)destinationOffset startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("encodeIntoByteArray(source:destination:destinationOffset:startIndex:endIndex:)")));
- (id<IdentityKotlinAppendable>)encodeToAppendableSource:(IdentityKotlinByteArray *)source destination:(id<IdentityKotlinAppendable>)destination startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("encodeToAppendable(source:destination:startIndex:endIndex:)")));
- (IdentityKotlinByteArray *)encodeToByteArraySource:(IdentityKotlinByteArray *)source startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("encodeToByteArray(source:startIndex:endIndex:)")));

/**
 * @note annotations
 *   kotlin.SinceKotlin(version="2.0")
*/
- (IdentityKotlinBase64 *)withPaddingOption:(IdentityKotlinBase64PaddingOption *)option __attribute__((swift_name("withPadding(option:)")));
@end

__attribute__((swift_name("KotlinIllegalArgumentException")))
@interface IdentityKotlinIllegalArgumentException : IdentityKotlinRuntimeException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((swift_name("Kotlinx_io_coreIOException")))
@interface IdentityKotlinx_io_coreIOException : IdentityKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((swift_name("Ktor_utilsStringValues")))
@protocol IdentityKtor_utilsStringValues
@required
- (BOOL)containsName:(NSString *)name __attribute__((swift_name("contains(name:)")));
- (BOOL)containsName:(NSString *)name value:(NSString *)value __attribute__((swift_name("contains(name:value:)")));
- (NSSet<id<IdentityKotlinMapEntry>> *)entries __attribute__((swift_name("entries()")));
- (void)forEachBody:(void (^)(NSString *, NSArray<NSString *> *))body __attribute__((swift_name("forEach(body:)")));
- (NSString * _Nullable)getName:(NSString *)name __attribute__((swift_name("get(name:)")));
- (NSArray<NSString *> * _Nullable)getAllName:(NSString *)name __attribute__((swift_name("getAll(name:)")));
- (BOOL)isEmpty __attribute__((swift_name("isEmpty()")));
- (NSSet<NSString *> *)names __attribute__((swift_name("names()")));
@property (readonly) BOOL caseInsensitiveName __attribute__((swift_name("caseInsensitiveName")));
@end

__attribute__((swift_name("Ktor_httpHeaders")))
@protocol IdentityKtor_httpHeaders <IdentityKtor_utilsStringValues>
@required
@end

__attribute__((swift_name("Ktor_client_coreHttpClientCall")))
@interface IdentityKtor_client_coreHttpClientCall : IdentityBase <IdentityKotlinx_coroutines_coreCoroutineScope>
- (instancetype)initWithClient:(IdentityKtor_client_coreHttpClient *)client __attribute__((swift_name("init(client:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithClient:(IdentityKtor_client_coreHttpClient *)client requestData:(IdentityKtor_client_coreHttpRequestData *)requestData responseData:(IdentityKtor_client_coreHttpResponseData *)responseData __attribute__((swift_name("init(client:requestData:responseData:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKtor_client_coreHttpClientCallCompanion *companion __attribute__((swift_name("companion")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)bodyInfo:(IdentityKtor_utilsTypeInfo *)info completionHandler:(void (^)(id _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("body(info:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)bodyNullableInfo:(IdentityKtor_utilsTypeInfo *)info completionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("bodyNullable(info:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)getResponseContentWithCompletionHandler:(void (^)(id<IdentityKtor_ioByteReadChannel> _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getResponseContent(completionHandler:)")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) BOOL allowDoubleReceive __attribute__((swift_name("allowDoubleReceive")));
@property (readonly) id<IdentityKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) IdentityKtor_client_coreHttpClient *client __attribute__((swift_name("client")));
@property (readonly) id<IdentityKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@property id<IdentityKtor_client_coreHttpRequest> request __attribute__((swift_name("request")));
@property IdentityKtor_client_coreHttpResponse *response __attribute__((swift_name("response")));
@end

__attribute__((swift_name("Ktor_ioByteReadChannel")))
@protocol IdentityKtor_ioByteReadChannel
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)awaitContentMin:(int32_t)min completionHandler:(void (^)(IdentityBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("awaitContent(min:completionHandler:)")));
- (void)cancelCause_:(IdentityKotlinThrowable * _Nullable)cause __attribute__((swift_name("cancel(cause_:)")));
@property (readonly) IdentityKotlinThrowable * _Nullable closedCause __attribute__((swift_name("closedCause")));
@property (readonly) BOOL isClosedForRead __attribute__((swift_name("isClosedForRead")));
@property (readonly) id<IdentityKotlinx_io_coreSource> readBuffer __attribute__((swift_name("readBuffer")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsGMTDate")))
@interface IdentityKtor_utilsGMTDate : IdentityBase <IdentityKotlinComparable>
- (instancetype)initWithSeconds:(int32_t)seconds minutes:(int32_t)minutes hours:(int32_t)hours dayOfWeek:(IdentityKtor_utilsWeekDay *)dayOfWeek dayOfMonth:(int32_t)dayOfMonth dayOfYear:(int32_t)dayOfYear month:(IdentityKtor_utilsMonth *)month year:(int32_t)year timestamp:(int64_t)timestamp __attribute__((swift_name("init(seconds:minutes:hours:dayOfWeek:dayOfMonth:dayOfYear:month:year:timestamp:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKtor_utilsGMTDateCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(IdentityKtor_utilsGMTDate *)other __attribute__((swift_name("compareTo(other:)")));
- (IdentityKtor_utilsGMTDate *)doCopy __attribute__((swift_name("doCopy()")));
- (IdentityKtor_utilsGMTDate *)doCopySeconds:(int32_t)seconds minutes:(int32_t)minutes hours:(int32_t)hours dayOfWeek:(IdentityKtor_utilsWeekDay *)dayOfWeek dayOfMonth:(int32_t)dayOfMonth dayOfYear:(int32_t)dayOfYear month:(IdentityKtor_utilsMonth *)month year:(int32_t)year timestamp:(int64_t)timestamp __attribute__((swift_name("doCopy(seconds:minutes:hours:dayOfWeek:dayOfMonth:dayOfYear:month:year:timestamp:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t dayOfMonth __attribute__((swift_name("dayOfMonth")));
@property (readonly) IdentityKtor_utilsWeekDay *dayOfWeek __attribute__((swift_name("dayOfWeek")));
@property (readonly) int32_t dayOfYear __attribute__((swift_name("dayOfYear")));
@property (readonly) int32_t hours __attribute__((swift_name("hours")));
@property (readonly) int32_t minutes __attribute__((swift_name("minutes")));
@property (readonly) IdentityKtor_utilsMonth *month __attribute__((swift_name("month")));
@property (readonly) int32_t seconds __attribute__((swift_name("seconds")));
@property (readonly) int64_t timestamp __attribute__((swift_name("timestamp")));
@property (readonly) int32_t year __attribute__((swift_name("year")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpProtocolVersion")))
@interface IdentityKtor_httpHttpProtocolVersion : IdentityBase
- (instancetype)initWithName:(NSString *)name major:(int32_t)major minor:(int32_t)minor __attribute__((swift_name("init(name:major:minor:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKtor_httpHttpProtocolVersionCompanion *companion __attribute__((swift_name("companion")));
- (IdentityKtor_httpHttpProtocolVersion *)doCopyName:(NSString *)name major:(int32_t)major minor:(int32_t)minor __attribute__((swift_name("doCopy(name:major:minor:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t major __attribute__((swift_name("major")));
@property (readonly) int32_t minor __attribute__((swift_name("minor")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end

__attribute__((swift_name("KotlinIterator")))
@protocol IdentityKotlinIterator
@required
- (BOOL)hasNext __attribute__((swift_name("hasNext()")));
- (id _Nullable)next __attribute__((swift_name("next()")));
@end

__attribute__((swift_name("KotlinByteIterator")))
@interface IdentityKotlinByteIterator : IdentityBase <IdentityKotlinIterator>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (IdentityByte *)next __attribute__((swift_name("next()")));
- (int8_t)nextByte __attribute__((swift_name("nextByte()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_serialization_jsonJsonElement.Companion")))
@interface IdentityKotlinx_serialization_jsonJsonElementCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKotlinx_serialization_jsonJsonElementCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="2.0")
*/
__attribute__((swift_name("KotlinAutoCloseable")))
@protocol IdentityKotlinAutoCloseable
@required
- (void)close __attribute__((swift_name("close()")));
@end

__attribute__((swift_name("Ktor_ioCloseable")))
@protocol IdentityKtor_ioCloseable <IdentityKotlinAutoCloseable>
@required
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClient")))
@interface IdentityKtor_client_coreHttpClient : IdentityBase <IdentityKotlinx_coroutines_coreCoroutineScope, IdentityKtor_ioCloseable>
- (instancetype)initWithEngine:(id<IdentityKtor_client_coreHttpClientEngine>)engine userConfig:(IdentityKtor_client_coreHttpClientConfig<IdentityKtor_client_coreHttpClientEngineConfig *> *)userConfig __attribute__((swift_name("init(engine:userConfig:)"))) __attribute__((objc_designated_initializer));
- (void)close __attribute__((swift_name("close()")));
- (IdentityKtor_client_coreHttpClient *)configBlock:(void (^)(IdentityKtor_client_coreHttpClientConfig<id> *))block __attribute__((swift_name("config(block:)")));
- (BOOL)isSupportedCapability:(id<IdentityKtor_client_coreHttpClientEngineCapability>)capability __attribute__((swift_name("isSupported(capability:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<IdentityKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) id<IdentityKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@property (readonly) id<IdentityKtor_client_coreHttpClientEngine> engine __attribute__((swift_name("engine")));
@property (readonly) IdentityKtor_client_coreHttpClientEngineConfig *engineConfig __attribute__((swift_name("engineConfig")));
@property (readonly) IdentityKtor_eventsEvents *monitor __attribute__((swift_name("monitor")));
@property (readonly) IdentityKtor_client_coreHttpReceivePipeline *receivePipeline __attribute__((swift_name("receivePipeline")));
@property (readonly) IdentityKtor_client_coreHttpRequestPipeline *requestPipeline __attribute__((swift_name("requestPipeline")));
@property (readonly) IdentityKtor_client_coreHttpResponsePipeline *responsePipeline __attribute__((swift_name("responsePipeline")));
@property (readonly) IdentityKtor_client_coreHttpSendPipeline *sendPipeline __attribute__((swift_name("sendPipeline")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinTriple")))
@interface IdentityKotlinTriple<__covariant A, __covariant B, __covariant C> : IdentityBase
- (instancetype)initWithFirst:(A _Nullable)first second:(B _Nullable)second third:(C _Nullable)third __attribute__((swift_name("init(first:second:third:)"))) __attribute__((objc_designated_initializer));
- (IdentityKotlinTriple<A, B, C> *)doCopyFirst:(A _Nullable)first second:(B _Nullable)second third:(C _Nullable)third __attribute__((swift_name("doCopy(first:second:third:)")));
- (BOOL)equalsOther:(id _Nullable)other __attribute__((swift_name("equals(other:)")));
- (int32_t)hashCode __attribute__((swift_name("hashCode()")));
- (NSString *)toString __attribute__((swift_name("toString()")));
@property (readonly) A _Nullable first __attribute__((swift_name("first")));
@property (readonly) B _Nullable second __attribute__((swift_name("second")));
@property (readonly) C _Nullable third __attribute__((swift_name("third")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpStatusCode.Companion")))
@interface IdentityKtor_httpHttpStatusCodeCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_httpHttpStatusCodeCompanion *shared __attribute__((swift_name("shared")));
- (IdentityKtor_httpHttpStatusCode *)fromValueValue:(int32_t)value __attribute__((swift_name("fromValue(value:)")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Accepted __attribute__((swift_name("Accepted")));
@property (readonly) IdentityKtor_httpHttpStatusCode *BadGateway __attribute__((swift_name("BadGateway")));
@property (readonly) IdentityKtor_httpHttpStatusCode *BadRequest __attribute__((swift_name("BadRequest")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Conflict __attribute__((swift_name("Conflict")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Continue __attribute__((swift_name("Continue")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Created __attribute__((swift_name("Created")));
@property (readonly) IdentityKtor_httpHttpStatusCode *ExpectationFailed __attribute__((swift_name("ExpectationFailed")));
@property (readonly) IdentityKtor_httpHttpStatusCode *FailedDependency __attribute__((swift_name("FailedDependency")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Forbidden __attribute__((swift_name("Forbidden")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Found __attribute__((swift_name("Found")));
@property (readonly) IdentityKtor_httpHttpStatusCode *GatewayTimeout __attribute__((swift_name("GatewayTimeout")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Gone __attribute__((swift_name("Gone")));
@property (readonly) IdentityKtor_httpHttpStatusCode *InsufficientStorage __attribute__((swift_name("InsufficientStorage")));
@property (readonly) IdentityKtor_httpHttpStatusCode *InternalServerError __attribute__((swift_name("InternalServerError")));
@property (readonly) IdentityKtor_httpHttpStatusCode *LengthRequired __attribute__((swift_name("LengthRequired")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Locked __attribute__((swift_name("Locked")));
@property (readonly) IdentityKtor_httpHttpStatusCode *MethodNotAllowed __attribute__((swift_name("MethodNotAllowed")));
@property (readonly) IdentityKtor_httpHttpStatusCode *MovedPermanently __attribute__((swift_name("MovedPermanently")));
@property (readonly) IdentityKtor_httpHttpStatusCode *MultiStatus __attribute__((swift_name("MultiStatus")));
@property (readonly) IdentityKtor_httpHttpStatusCode *MultipleChoices __attribute__((swift_name("MultipleChoices")));
@property (readonly) IdentityKtor_httpHttpStatusCode *NoContent __attribute__((swift_name("NoContent")));
@property (readonly) IdentityKtor_httpHttpStatusCode *NonAuthoritativeInformation __attribute__((swift_name("NonAuthoritativeInformation")));
@property (readonly) IdentityKtor_httpHttpStatusCode *NotAcceptable __attribute__((swift_name("NotAcceptable")));
@property (readonly) IdentityKtor_httpHttpStatusCode *NotFound __attribute__((swift_name("NotFound")));
@property (readonly) IdentityKtor_httpHttpStatusCode *NotImplemented __attribute__((swift_name("NotImplemented")));
@property (readonly) IdentityKtor_httpHttpStatusCode *NotModified __attribute__((swift_name("NotModified")));
@property (readonly) IdentityKtor_httpHttpStatusCode *OK __attribute__((swift_name("OK")));
@property (readonly) IdentityKtor_httpHttpStatusCode *PartialContent __attribute__((swift_name("PartialContent")));
@property (readonly) IdentityKtor_httpHttpStatusCode *PayloadTooLarge __attribute__((swift_name("PayloadTooLarge")));
@property (readonly) IdentityKtor_httpHttpStatusCode *PaymentRequired __attribute__((swift_name("PaymentRequired")));
@property (readonly) IdentityKtor_httpHttpStatusCode *PermanentRedirect __attribute__((swift_name("PermanentRedirect")));
@property (readonly) IdentityKtor_httpHttpStatusCode *PreconditionFailed __attribute__((swift_name("PreconditionFailed")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Processing __attribute__((swift_name("Processing")));
@property (readonly) IdentityKtor_httpHttpStatusCode *ProxyAuthenticationRequired __attribute__((swift_name("ProxyAuthenticationRequired")));
@property (readonly) IdentityKtor_httpHttpStatusCode *RequestHeaderFieldTooLarge __attribute__((swift_name("RequestHeaderFieldTooLarge")));
@property (readonly) IdentityKtor_httpHttpStatusCode *RequestTimeout __attribute__((swift_name("RequestTimeout")));
@property (readonly) IdentityKtor_httpHttpStatusCode *RequestURITooLong __attribute__((swift_name("RequestURITooLong")));
@property (readonly) IdentityKtor_httpHttpStatusCode *RequestedRangeNotSatisfiable __attribute__((swift_name("RequestedRangeNotSatisfiable")));
@property (readonly) IdentityKtor_httpHttpStatusCode *ResetContent __attribute__((swift_name("ResetContent")));
@property (readonly) IdentityKtor_httpHttpStatusCode *SeeOther __attribute__((swift_name("SeeOther")));
@property (readonly) IdentityKtor_httpHttpStatusCode *ServiceUnavailable __attribute__((swift_name("ServiceUnavailable")));
@property (readonly) IdentityKtor_httpHttpStatusCode *SwitchProxy __attribute__((swift_name("SwitchProxy")));
@property (readonly) IdentityKtor_httpHttpStatusCode *SwitchingProtocols __attribute__((swift_name("SwitchingProtocols")));
@property (readonly) IdentityKtor_httpHttpStatusCode *TemporaryRedirect __attribute__((swift_name("TemporaryRedirect")));
@property (readonly) IdentityKtor_httpHttpStatusCode *TooEarly __attribute__((swift_name("TooEarly")));
@property (readonly) IdentityKtor_httpHttpStatusCode *TooManyRequests __attribute__((swift_name("TooManyRequests")));
@property (readonly) IdentityKtor_httpHttpStatusCode *Unauthorized __attribute__((swift_name("Unauthorized")));
@property (readonly) IdentityKtor_httpHttpStatusCode *UnprocessableEntity __attribute__((swift_name("UnprocessableEntity")));
@property (readonly) IdentityKtor_httpHttpStatusCode *UnsupportedMediaType __attribute__((swift_name("UnsupportedMediaType")));
@property (readonly) IdentityKtor_httpHttpStatusCode *UpgradeRequired __attribute__((swift_name("UpgradeRequired")));
@property (readonly) IdentityKtor_httpHttpStatusCode *UseProxy __attribute__((swift_name("UseProxy")));
@property (readonly) IdentityKtor_httpHttpStatusCode *VariantAlsoNegotiates __attribute__((swift_name("VariantAlsoNegotiates")));
@property (readonly) IdentityKtor_httpHttpStatusCode *VersionNotSupported __attribute__((swift_name("VersionNotSupported")));
@property (readonly) NSArray<IdentityKtor_httpHttpStatusCode *> *allStatusCodes __attribute__((swift_name("allStatusCodes")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeInstant.Companion")))
@interface IdentityKotlinx_datetimeInstantCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKotlinx_datetimeInstantCompanion *shared __attribute__((swift_name("shared")));
- (IdentityKotlinx_datetimeInstant *)fromEpochMillisecondsEpochMilliseconds:(int64_t)epochMilliseconds __attribute__((swift_name("fromEpochMilliseconds(epochMilliseconds:)")));
- (IdentityKotlinx_datetimeInstant *)fromEpochSecondsEpochSeconds:(int64_t)epochSeconds nanosecondAdjustment:(int32_t)nanosecondAdjustment __attribute__((swift_name("fromEpochSeconds(epochSeconds:nanosecondAdjustment:)")));
- (IdentityKotlinx_datetimeInstant *)fromEpochSecondsEpochSeconds:(int64_t)epochSeconds nanosecondAdjustment_:(int64_t)nanosecondAdjustment __attribute__((swift_name("fromEpochSeconds(epochSeconds:nanosecondAdjustment_:)")));
- (IdentityKotlinx_datetimeInstant *)now __attribute__((swift_name("now()"))) __attribute__((unavailable("Use Clock.System.now() instead")));
- (IdentityKotlinx_datetimeInstant *)parseInput:(id)input format:(id<IdentityKotlinx_datetimeDateTimeFormat>)format __attribute__((swift_name("parse(input:format:)")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@property (readonly) IdentityKotlinx_datetimeInstant *DISTANT_FUTURE __attribute__((swift_name("DISTANT_FUTURE")));
@property (readonly) IdentityKotlinx_datetimeInstant *DISTANT_PAST __attribute__((swift_name("DISTANT_PAST")));
@end


/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
__attribute__((swift_name("Kotlinx_coroutines_coreSelectClause")))
@protocol IdentityKotlinx_coroutines_coreSelectClause
@required
@property (readonly) id clauseObject __attribute__((swift_name("clauseObject")));
@property (readonly) IdentityKotlinUnit *(^(^ _Nullable onCancellationConstructor)(id<IdentityKotlinx_coroutines_coreSelectInstance>, id _Nullable, id _Nullable))(IdentityKotlinThrowable *, id _Nullable, id<IdentityKotlinCoroutineContext>) __attribute__((swift_name("onCancellationConstructor")));
@property (readonly) id _Nullable (^processResFunc)(id, id _Nullable, id _Nullable) __attribute__((swift_name("processResFunc")));
@property (readonly) void (^regFunc)(id, id<IdentityKotlinx_coroutines_coreSelectInstance>, id _Nullable) __attribute__((swift_name("regFunc")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreSelectClause1")))
@protocol IdentityKotlinx_coroutines_coreSelectClause1 <IdentityKotlinx_coroutines_coreSelectClause>
@required
@end

__attribute__((swift_name("Kotlinx_coroutines_coreDisposableHandle")))
@protocol IdentityKotlinx_coroutines_coreDisposableHandle
@required
- (void)dispose __attribute__((swift_name("dispose()")));
@end


/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
__attribute__((swift_name("Kotlinx_coroutines_coreChildHandle")))
@protocol IdentityKotlinx_coroutines_coreChildHandle <IdentityKotlinx_coroutines_coreDisposableHandle>
@required

/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
- (BOOL)childCancelledCause:(IdentityKotlinThrowable *)cause __attribute__((swift_name("childCancelled(cause:)")));

/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
@property (readonly) id<IdentityKotlinx_coroutines_coreJob> _Nullable parent __attribute__((swift_name("parent")));
@end


/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
__attribute__((swift_name("Kotlinx_coroutines_coreChildJob")))
@protocol IdentityKotlinx_coroutines_coreChildJob <IdentityKotlinx_coroutines_coreJob>
@required

/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
- (void)parentCancelledParentJob:(id<IdentityKotlinx_coroutines_coreParentJob>)parentJob __attribute__((swift_name("parentCancelled(parentJob:)")));
@end

__attribute__((swift_name("KotlinSequence")))
@protocol IdentityKotlinSequence
@required
- (id<IdentityKotlinIterator>)iterator __attribute__((swift_name("iterator()")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreSelectClause0")))
@protocol IdentityKotlinx_coroutines_coreSelectClause0 <IdentityKotlinx_coroutines_coreSelectClause>
@required
@end

__attribute__((swift_name("KotlinCoroutineContextKey")))
@protocol IdentityKotlinCoroutineContextKey
@required
@end

__attribute__((swift_name("Kotlinx_serialization_coreCompositeEncoder")))
@protocol IdentityKotlinx_serialization_coreCompositeEncoder
@required
- (void)encodeBooleanElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(BOOL)value __attribute__((swift_name("encodeBooleanElement(descriptor:index:value:)")));
- (void)encodeByteElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int8_t)value __attribute__((swift_name("encodeByteElement(descriptor:index:value:)")));
- (void)encodeCharElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(unichar)value __attribute__((swift_name("encodeCharElement(descriptor:index:value:)")));
- (void)encodeDoubleElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(double)value __attribute__((swift_name("encodeDoubleElement(descriptor:index:value:)")));
- (void)encodeFloatElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(float)value __attribute__((swift_name("encodeFloatElement(descriptor:index:value:)")));
- (id<IdentityKotlinx_serialization_coreEncoder>)encodeInlineElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("encodeInlineElement(descriptor:index:)")));
- (void)encodeIntElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int32_t)value __attribute__((swift_name("encodeIntElement(descriptor:index:value:)")));
- (void)encodeLongElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int64_t)value __attribute__((swift_name("encodeLongElement(descriptor:index:value:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)encodeNullableSerializableElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index serializer:(id<IdentityKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeNullableSerializableElement(descriptor:index:serializer:value:)")));
- (void)encodeSerializableElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index serializer:(id<IdentityKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeSerializableElement(descriptor:index:serializer:value:)")));
- (void)encodeShortElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int16_t)value __attribute__((swift_name("encodeShortElement(descriptor:index:value:)")));
- (void)encodeStringElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(NSString *)value __attribute__((swift_name("encodeStringElement(descriptor:index:value:)")));
- (void)endStructureDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("endStructure(descriptor:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (BOOL)shouldEncodeElementDefaultDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("shouldEncodeElementDefault(descriptor:index:)")));
@property (readonly) IdentityKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreSerializersModule")))
@interface IdentityKotlinx_serialization_coreSerializersModule : IdentityBase

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)dumpToCollector:(id<IdentityKotlinx_serialization_coreSerializersModuleCollector>)collector __attribute__((swift_name("dumpTo(collector:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id<IdentityKotlinx_serialization_coreKSerializer> _Nullable)getContextualKClass:(id<IdentityKotlinKClass>)kClass typeArgumentsSerializers:(NSArray<id<IdentityKotlinx_serialization_coreKSerializer>> *)typeArgumentsSerializers __attribute__((swift_name("getContextual(kClass:typeArgumentsSerializers:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id<IdentityKotlinx_serialization_coreSerializationStrategy> _Nullable)getPolymorphicBaseClass:(id<IdentityKotlinKClass>)baseClass value:(id)value __attribute__((swift_name("getPolymorphic(baseClass:value:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id<IdentityKotlinx_serialization_coreDeserializationStrategy> _Nullable)getPolymorphicBaseClass:(id<IdentityKotlinKClass>)baseClass serializedClassName:(NSString * _Nullable)serializedClassName __attribute__((swift_name("getPolymorphic(baseClass:serializedClassName:)")));
@end

__attribute__((swift_name("KotlinAnnotation")))
@protocol IdentityKotlinAnnotation
@required
@end

__attribute__((swift_name("Kotlinx_serialization_coreSerialKind")))
@interface IdentityKotlinx_serialization_coreSerialKind : IdentityBase
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreCompositeDecoder")))
@protocol IdentityKotlinx_serialization_coreCompositeDecoder
@required
- (BOOL)decodeBooleanElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeBooleanElement(descriptor:index:)")));
- (int8_t)decodeByteElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeByteElement(descriptor:index:)")));
- (unichar)decodeCharElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeCharElement(descriptor:index:)")));
- (int32_t)decodeCollectionSizeDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("decodeCollectionSize(descriptor:)")));
- (double)decodeDoubleElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeDoubleElement(descriptor:index:)")));
- (int32_t)decodeElementIndexDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("decodeElementIndex(descriptor:)")));
- (float)decodeFloatElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeFloatElement(descriptor:index:)")));
- (id<IdentityKotlinx_serialization_coreDecoder>)decodeInlineElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeInlineElement(descriptor:index:)")));
- (int32_t)decodeIntElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeIntElement(descriptor:index:)")));
- (int64_t)decodeLongElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeLongElement(descriptor:index:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id _Nullable)decodeNullableSerializableElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index deserializer:(id<IdentityKotlinx_serialization_coreDeserializationStrategy>)deserializer previousValue:(id _Nullable)previousValue __attribute__((swift_name("decodeNullableSerializableElement(descriptor:index:deserializer:previousValue:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (BOOL)decodeSequentially __attribute__((swift_name("decodeSequentially()")));
- (id _Nullable)decodeSerializableElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index deserializer:(id<IdentityKotlinx_serialization_coreDeserializationStrategy>)deserializer previousValue:(id _Nullable)previousValue __attribute__((swift_name("decodeSerializableElement(descriptor:index:deserializer:previousValue:)")));
- (int16_t)decodeShortElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeShortElement(descriptor:index:)")));
- (NSString *)decodeStringElementDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeStringElement(descriptor:index:)")));
- (void)endStructureDescriptor:(id<IdentityKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("endStructure(descriptor:)")));
@property (readonly) IdentityKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreFlowCollector")))
@protocol IdentityKotlinx_coroutines_coreFlowCollector
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)emitValue:(id _Nullable)value completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("emit(value:completionHandler:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SdkCamera")))
@interface IdentitySdkCamera : IdentityKotlinEnum<IdentitySdkCamera *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentitySdkCamera *front __attribute__((swift_name("front")));
@property (class, readonly) IdentitySdkCamera *external __attribute__((swift_name("external")));
+ (IdentityKotlinArray<IdentitySdkCamera *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentitySdkCamera *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SdkIproovOptions.Certificate")))
@interface IdentitySdkIproovOptionsCertificate : IdentityBase
- (instancetype)initWithSpki:(NSString *)spki __attribute__((swift_name("init(spki:)"))) __attribute__((objc_designated_initializer));
- (IdentitySdkIproovOptionsCertificate *)doCopySpki:(NSString *)spki __attribute__((swift_name("doCopy(spki:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *spki __attribute__((swift_name("spki")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SdkIproovOptions.CloseButton")))
@interface IdentitySdkIproovOptionsCloseButton : IdentityBase
- (instancetype)initWithIcon:(IdentityKotlinByteArray * _Nullable)icon colorTint:(int32_t)colorTint __attribute__((swift_name("init(icon:colorTint:)"))) __attribute__((objc_designated_initializer));
- (IdentitySdkIproovOptionsCloseButton *)doCopyIcon:(IdentityKotlinByteArray * _Nullable)icon colorTint:(int32_t)colorTint __attribute__((swift_name("doCopy(icon:colorTint:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property int32_t colorTint __attribute__((swift_name("colorTint")));
@property IdentityKotlinByteArray * _Nullable icon __attribute__((swift_name("icon")));
@end

__attribute__((swift_name("SdkIproovOptions.Filter")))
@interface IdentitySdkIproovOptionsFilter : IdentityBase
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SdkIproovOptions.GenuinePresenceAssurance")))
@interface IdentitySdkIproovOptionsGenuinePresenceAssurance : IdentityBase
- (instancetype)initWithReadyOvalStrokeColor:(int32_t)readyOvalStrokeColor notReadyOvalStrokeColor:(int32_t)notReadyOvalStrokeColor scanningPrompts:(BOOL)scanningPrompts __attribute__((swift_name("init(readyOvalStrokeColor:notReadyOvalStrokeColor:scanningPrompts:)"))) __attribute__((objc_designated_initializer));
- (IdentitySdkIproovOptionsGenuinePresenceAssurance *)doCopyReadyOvalStrokeColor:(int32_t)readyOvalStrokeColor notReadyOvalStrokeColor:(int32_t)notReadyOvalStrokeColor scanningPrompts:(BOOL)scanningPrompts __attribute__((swift_name("doCopy(readyOvalStrokeColor:notReadyOvalStrokeColor:scanningPrompts:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property int32_t notReadyOvalStrokeColor __attribute__((swift_name("notReadyOvalStrokeColor")));
@property int32_t readyOvalStrokeColor __attribute__((swift_name("readyOvalStrokeColor")));
@property BOOL scanningPrompts __attribute__((swift_name("scanningPrompts")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SdkIproovOptions.LivenessAssurance")))
@interface IdentitySdkIproovOptionsLivenessAssurance : IdentityBase
- (instancetype)initWithOvalStrokeColor:(int32_t)ovalStrokeColor completedOvalStrokeColor:(int32_t)completedOvalStrokeColor __attribute__((swift_name("init(ovalStrokeColor:completedOvalStrokeColor:)"))) __attribute__((objc_designated_initializer));
- (IdentitySdkIproovOptionsLivenessAssurance *)doCopyOvalStrokeColor:(int32_t)ovalStrokeColor completedOvalStrokeColor:(int32_t)completedOvalStrokeColor __attribute__((swift_name("doCopy(ovalStrokeColor:completedOvalStrokeColor:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property int32_t completedOvalStrokeColor __attribute__((swift_name("completedOvalStrokeColor")));
@property int32_t ovalStrokeColor __attribute__((swift_name("ovalStrokeColor")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SdkOrientation")))
@interface IdentitySdkOrientation : IdentityKotlinEnum<IdentitySdkOrientation *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentitySdkOrientation *portrait __attribute__((swift_name("portrait")));
@property (class, readonly) IdentitySdkOrientation *landscape __attribute__((swift_name("landscape")));
@property (class, readonly) IdentitySdkOrientation *reversePortrait __attribute__((swift_name("reversePortrait")));
@property (class, readonly) IdentitySdkOrientation *reverseLandscape __attribute__((swift_name("reverseLandscape")));
+ (IdentityKotlinArray<IdentitySdkOrientation *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentitySdkOrientation *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinBase64.Default")))
@interface IdentityKotlinBase64Default : IdentityKotlinBase64
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)default_ __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKotlinBase64Default *shared __attribute__((swift_name("shared")));
@property (readonly) IdentityKotlinBase64 *Mime __attribute__((swift_name("Mime")));
@property (readonly) IdentityKotlinBase64 *UrlSafe __attribute__((swift_name("UrlSafe")));
@end

__attribute__((swift_name("KotlinAppendable")))
@protocol IdentityKotlinAppendable
@required
- (id<IdentityKotlinAppendable>)appendValue:(unichar)value __attribute__((swift_name("append(value:)")));
- (id<IdentityKotlinAppendable>)appendValue_:(id _Nullable)value __attribute__((swift_name("append(value_:)")));
- (id<IdentityKotlinAppendable>)appendValue:(id _Nullable)value startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("append(value:startIndex:endIndex:)")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="2.0")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinBase64.PaddingOption")))
@interface IdentityKotlinBase64PaddingOption : IdentityKotlinEnum<IdentityKotlinBase64PaddingOption *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentityKotlinBase64PaddingOption *present __attribute__((swift_name("present")));
@property (class, readonly) IdentityKotlinBase64PaddingOption *absent __attribute__((swift_name("absent")));
@property (class, readonly) IdentityKotlinBase64PaddingOption *presentOptional __attribute__((swift_name("presentOptional")));
@property (class, readonly) IdentityKotlinBase64PaddingOption *absentOptional __attribute__((swift_name("absentOptional")));
+ (IdentityKotlinArray<IdentityKotlinBase64PaddingOption *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityKotlinBase64PaddingOption *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((swift_name("KotlinMapEntry")))
@protocol IdentityKotlinMapEntry
@required
@property (readonly) id _Nullable key __attribute__((swift_name("key")));
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestData")))
@interface IdentityKtor_client_coreHttpRequestData : IdentityBase
- (instancetype)initWithUrl:(IdentityKtor_httpUrl *)url method:(IdentityKtor_httpHttpMethod *)method headers:(id<IdentityKtor_httpHeaders>)headers body:(IdentityKtor_httpOutgoingContent *)body executionContext:(id<IdentityKotlinx_coroutines_coreJob>)executionContext attributes:(id<IdentityKtor_utilsAttributes>)attributes __attribute__((swift_name("init(url:method:headers:body:executionContext:attributes:)"))) __attribute__((objc_designated_initializer));
- (id _Nullable)getCapabilityOrNullKey:(id<IdentityKtor_client_coreHttpClientEngineCapability>)key __attribute__((swift_name("getCapabilityOrNull(key:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<IdentityKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) IdentityKtor_httpOutgoingContent *body __attribute__((swift_name("body")));
@property (readonly) id<IdentityKotlinx_coroutines_coreJob> executionContext __attribute__((swift_name("executionContext")));
@property (readonly) id<IdentityKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@property (readonly) IdentityKtor_httpHttpMethod *method __attribute__((swift_name("method")));
@property (readonly) IdentityKtor_httpUrl *url __attribute__((swift_name("url")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponseData")))
@interface IdentityKtor_client_coreHttpResponseData : IdentityBase
- (instancetype)initWithStatusCode:(IdentityKtor_httpHttpStatusCode *)statusCode requestTime:(IdentityKtor_utilsGMTDate *)requestTime headers:(id<IdentityKtor_httpHeaders>)headers version:(IdentityKtor_httpHttpProtocolVersion *)version body:(id)body callContext:(id<IdentityKotlinCoroutineContext>)callContext __attribute__((swift_name("init(statusCode:requestTime:headers:version:body:callContext:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id body __attribute__((swift_name("body")));
@property (readonly) id<IdentityKotlinCoroutineContext> callContext __attribute__((swift_name("callContext")));
@property (readonly) id<IdentityKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@property (readonly) IdentityKtor_utilsGMTDate *requestTime __attribute__((swift_name("requestTime")));
@property (readonly) IdentityKtor_utilsGMTDate *responseTime __attribute__((swift_name("responseTime")));
@property (readonly) IdentityKtor_httpHttpStatusCode *statusCode __attribute__((swift_name("statusCode")));
@property (readonly) IdentityKtor_httpHttpProtocolVersion *version __attribute__((swift_name("version")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClientCall.Companion")))
@interface IdentityKtor_client_coreHttpClientCallCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_client_coreHttpClientCallCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsTypeInfo")))
@interface IdentityKtor_utilsTypeInfo : IdentityBase
- (instancetype)initWithType:(id<IdentityKotlinKClass>)type kotlinType:(id<IdentityKotlinKType> _Nullable)kotlinType __attribute__((swift_name("init(type:kotlinType:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithType:(id<IdentityKotlinKClass>)type reifiedType:(id<IdentityKotlinKType>)reifiedType kotlinType:(id<IdentityKotlinKType> _Nullable)kotlinType __attribute__((swift_name("init(type:reifiedType:kotlinType:)"))) __attribute__((objc_designated_initializer)) __attribute__((deprecated("Use constructor without reifiedType parameter.")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<IdentityKotlinKType> _Nullable kotlinType __attribute__((swift_name("kotlinType")));
@property (readonly) id<IdentityKotlinKClass> type __attribute__((swift_name("type")));
@end

__attribute__((swift_name("Ktor_utilsAttributes")))
@protocol IdentityKtor_utilsAttributes
@required
- (id)computeIfAbsentKey:(IdentityKtor_utilsAttributeKey<id> *)key block:(id (^)(void))block __attribute__((swift_name("computeIfAbsent(key:block:)")));
- (BOOL)containsKey:(IdentityKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("contains(key:)")));
- (id)getKey_:(IdentityKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("get(key_:)")));
- (id _Nullable)getOrNullKey:(IdentityKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("getOrNull(key:)")));
- (void)putKey:(IdentityKtor_utilsAttributeKey<id> *)key value:(id)value __attribute__((swift_name("put(key:value:)")));
- (void)removeKey:(IdentityKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("remove(key:)")));
- (id)takeKey:(IdentityKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("take(key:)")));
- (id _Nullable)takeOrNullKey:(IdentityKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("takeOrNull(key:)")));
@property (readonly) NSArray<IdentityKtor_utilsAttributeKey<id> *> *allKeys __attribute__((swift_name("allKeys")));
@end

__attribute__((swift_name("Ktor_client_coreHttpRequest")))
@protocol IdentityKtor_client_coreHttpRequest <IdentityKtor_httpHttpMessage, IdentityKotlinx_coroutines_coreCoroutineScope>
@required
@property (readonly) id<IdentityKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) IdentityKtor_client_coreHttpClientCall *call __attribute__((swift_name("call")));
@property (readonly) IdentityKtor_httpOutgoingContent *content __attribute__((swift_name("content")));
@property (readonly) IdentityKtor_httpHttpMethod *method __attribute__((swift_name("method")));
@property (readonly) IdentityKtor_httpUrl *url __attribute__((swift_name("url")));
@end

__attribute__((swift_name("Kotlinx_io_coreRawSource")))
@protocol IdentityKotlinx_io_coreRawSource <IdentityKotlinAutoCloseable>
@required
- (int64_t)readAtMostToSink:(IdentityKotlinx_io_coreBuffer *)sink byteCount:(int64_t)byteCount __attribute__((swift_name("readAtMostTo(sink:byteCount:)")));
@end

__attribute__((swift_name("Kotlinx_io_coreSource")))
@protocol IdentityKotlinx_io_coreSource <IdentityKotlinx_io_coreRawSource>
@required
- (BOOL)exhausted __attribute__((swift_name("exhausted()")));
- (id<IdentityKotlinx_io_coreSource>)peek __attribute__((swift_name("peek()")));
- (int32_t)readAtMostToSink:(IdentityKotlinByteArray *)sink startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("readAtMostTo(sink:startIndex:endIndex:)")));
- (int8_t)readByte __attribute__((swift_name("readByte()")));
- (int32_t)readInt __attribute__((swift_name("readInt()")));
- (int64_t)readLong __attribute__((swift_name("readLong()")));
- (int16_t)readShort __attribute__((swift_name("readShort()")));
- (void)readToSink:(id<IdentityKotlinx_io_coreRawSink>)sink byteCount:(int64_t)byteCount __attribute__((swift_name("readTo(sink:byteCount:)")));
- (BOOL)requestByteCount:(int64_t)byteCount __attribute__((swift_name("request(byteCount:)")));
- (void)requireByteCount:(int64_t)byteCount __attribute__((swift_name("require(byteCount:)")));
- (void)skipByteCount:(int64_t)byteCount __attribute__((swift_name("skip(byteCount:)")));
- (int64_t)transferToSink:(id<IdentityKotlinx_io_coreRawSink>)sink __attribute__((swift_name("transferTo(sink:)")));

/**
 * @note annotations
 *   kotlinx.io.InternalIoApi
*/
@property (readonly) IdentityKotlinx_io_coreBuffer *buffer __attribute__((swift_name("buffer")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsWeekDay")))
@interface IdentityKtor_utilsWeekDay : IdentityKotlinEnum<IdentityKtor_utilsWeekDay *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityKtor_utilsWeekDayCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) IdentityKtor_utilsWeekDay *monday __attribute__((swift_name("monday")));
@property (class, readonly) IdentityKtor_utilsWeekDay *tuesday __attribute__((swift_name("tuesday")));
@property (class, readonly) IdentityKtor_utilsWeekDay *wednesday __attribute__((swift_name("wednesday")));
@property (class, readonly) IdentityKtor_utilsWeekDay *thursday __attribute__((swift_name("thursday")));
@property (class, readonly) IdentityKtor_utilsWeekDay *friday __attribute__((swift_name("friday")));
@property (class, readonly) IdentityKtor_utilsWeekDay *saturday __attribute__((swift_name("saturday")));
@property (class, readonly) IdentityKtor_utilsWeekDay *sunday __attribute__((swift_name("sunday")));
+ (IdentityKotlinArray<IdentityKtor_utilsWeekDay *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityKtor_utilsWeekDay *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsMonth")))
@interface IdentityKtor_utilsMonth : IdentityKotlinEnum<IdentityKtor_utilsMonth *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityKtor_utilsMonthCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) IdentityKtor_utilsMonth *january __attribute__((swift_name("january")));
@property (class, readonly) IdentityKtor_utilsMonth *february __attribute__((swift_name("february")));
@property (class, readonly) IdentityKtor_utilsMonth *march __attribute__((swift_name("march")));
@property (class, readonly) IdentityKtor_utilsMonth *april __attribute__((swift_name("april")));
@property (class, readonly) IdentityKtor_utilsMonth *may __attribute__((swift_name("may")));
@property (class, readonly) IdentityKtor_utilsMonth *june __attribute__((swift_name("june")));
@property (class, readonly) IdentityKtor_utilsMonth *july __attribute__((swift_name("july")));
@property (class, readonly) IdentityKtor_utilsMonth *august __attribute__((swift_name("august")));
@property (class, readonly) IdentityKtor_utilsMonth *september __attribute__((swift_name("september")));
@property (class, readonly) IdentityKtor_utilsMonth *october __attribute__((swift_name("october")));
@property (class, readonly) IdentityKtor_utilsMonth *november __attribute__((swift_name("november")));
@property (class, readonly) IdentityKtor_utilsMonth *december __attribute__((swift_name("december")));
+ (IdentityKotlinArray<IdentityKtor_utilsMonth *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityKtor_utilsMonth *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsGMTDate.Companion")))
@interface IdentityKtor_utilsGMTDateCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_utilsGMTDateCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@property (readonly) IdentityKtor_utilsGMTDate *START __attribute__((swift_name("START")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpProtocolVersion.Companion")))
@interface IdentityKtor_httpHttpProtocolVersionCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_httpHttpProtocolVersionCompanion *shared __attribute__((swift_name("shared")));
- (IdentityKtor_httpHttpProtocolVersion *)fromValueName:(NSString *)name major:(int32_t)major minor:(int32_t)minor __attribute__((swift_name("fromValue(name:major:minor:)")));
- (IdentityKtor_httpHttpProtocolVersion *)parseValue:(id)value __attribute__((swift_name("parse(value:)")));
@property (readonly) IdentityKtor_httpHttpProtocolVersion *HTTP_1_0 __attribute__((swift_name("HTTP_1_0")));
@property (readonly) IdentityKtor_httpHttpProtocolVersion *HTTP_1_1 __attribute__((swift_name("HTTP_1_1")));
@property (readonly) IdentityKtor_httpHttpProtocolVersion *HTTP_2_0 __attribute__((swift_name("HTTP_2_0")));
@property (readonly) IdentityKtor_httpHttpProtocolVersion *QUIC __attribute__((swift_name("QUIC")));
@property (readonly) IdentityKtor_httpHttpProtocolVersion *SPDY_3 __attribute__((swift_name("SPDY_3")));
@end

__attribute__((swift_name("Ktor_client_coreHttpClientEngine")))
@protocol IdentityKtor_client_coreHttpClientEngine <IdentityKotlinx_coroutines_coreCoroutineScope, IdentityKtor_ioCloseable>
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)executeData:(IdentityKtor_client_coreHttpRequestData *)data completionHandler:(void (^)(IdentityKtor_client_coreHttpResponseData * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("execute(data:completionHandler:)")));
- (void)installClient:(IdentityKtor_client_coreHttpClient *)client __attribute__((swift_name("install(client:)")));
@property (readonly) IdentityKtor_client_coreHttpClientEngineConfig *config __attribute__((swift_name("config")));
@property (readonly) IdentityKotlinx_coroutines_coreCoroutineDispatcher *dispatcher __attribute__((swift_name("dispatcher")));
@property (readonly) NSSet<id<IdentityKtor_client_coreHttpClientEngineCapability>> *supportedCapabilities __attribute__((swift_name("supportedCapabilities")));
@end

__attribute__((swift_name("Ktor_client_coreHttpClientEngineConfig")))
@interface IdentityKtor_client_coreHttpClientEngineConfig : IdentityBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property IdentityKotlinx_coroutines_coreCoroutineDispatcher * _Nullable dispatcher __attribute__((swift_name("dispatcher")));
@property BOOL pipelining __attribute__((swift_name("pipelining")));
@property IdentityKtor_client_coreProxyConfig * _Nullable proxy __attribute__((swift_name("proxy")));
@property int32_t threadsCount __attribute__((swift_name("threadsCount"))) __attribute__((unavailable("The [threadsCount] property is deprecated. Consider setting [dispatcher] instead.")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClientConfig")))
@interface IdentityKtor_client_coreHttpClientConfig<T> : IdentityBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (IdentityKtor_client_coreHttpClientConfig<T> *)clone __attribute__((swift_name("clone()")));
- (void)engineBlock:(void (^)(T))block __attribute__((swift_name("engine(block:)")));
- (void)installClient:(IdentityKtor_client_coreHttpClient *)client __attribute__((swift_name("install(client:)")));
- (void)installPlugin:(id<IdentityKtor_client_coreHttpClientPlugin>)plugin configure:(void (^)(id))configure __attribute__((swift_name("install(plugin:configure:)")));
- (void)installKey:(NSString *)key block:(void (^)(IdentityKtor_client_coreHttpClient *))block __attribute__((swift_name("install(key:block:)")));
- (void)plusAssignOther:(IdentityKtor_client_coreHttpClientConfig<T> *)other __attribute__((swift_name("plusAssign(other:)")));
@property BOOL developmentMode __attribute__((swift_name("developmentMode"))) __attribute__((deprecated("Development mode is no longer required. The property will be removed in the future.")));
@property BOOL expectSuccess __attribute__((swift_name("expectSuccess")));
@property BOOL followRedirects __attribute__((swift_name("followRedirects")));
@property BOOL useDefaultTransformers __attribute__((swift_name("useDefaultTransformers")));
@end

__attribute__((swift_name("Ktor_client_coreHttpClientEngineCapability")))
@protocol IdentityKtor_client_coreHttpClientEngineCapability
@required
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_eventsEvents")))
@interface IdentityKtor_eventsEvents : IdentityBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)raiseDefinition:(IdentityKtor_eventsEventDefinition<id> *)definition value:(id _Nullable)value __attribute__((swift_name("raise(definition:value:)")));
- (id<IdentityKotlinx_coroutines_coreDisposableHandle>)subscribeDefinition:(IdentityKtor_eventsEventDefinition<id> *)definition handler:(void (^)(id _Nullable))handler __attribute__((swift_name("subscribe(definition:handler:)")));
- (void)unsubscribeDefinition:(IdentityKtor_eventsEventDefinition<id> *)definition handler:(void (^)(id _Nullable))handler __attribute__((swift_name("unsubscribe(definition:handler:)")));
@end

__attribute__((swift_name("Ktor_utilsPipeline")))
@interface IdentityKtor_utilsPipeline<TSubject, TContext> : IdentityBase
- (instancetype)initWithPhases:(IdentityKotlinArray<IdentityKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(IdentityKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<IdentityKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer));
- (void)addPhasePhase:(IdentityKtor_utilsPipelinePhase *)phase __attribute__((swift_name("addPhase(phase:)")));
- (void)afterIntercepted __attribute__((swift_name("afterIntercepted()")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)executeContext:(TContext)context subject:(TSubject)subject completionHandler:(void (^)(TSubject _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("execute(context:subject:completionHandler:)")));
- (void)insertPhaseAfterReference:(IdentityKtor_utilsPipelinePhase *)reference phase:(IdentityKtor_utilsPipelinePhase *)phase __attribute__((swift_name("insertPhaseAfter(reference:phase:)")));
- (void)insertPhaseBeforeReference:(IdentityKtor_utilsPipelinePhase *)reference phase:(IdentityKtor_utilsPipelinePhase *)phase __attribute__((swift_name("insertPhaseBefore(reference:phase:)")));
- (void)interceptPhase:(IdentityKtor_utilsPipelinePhase *)phase block:(id<IdentityKotlinSuspendFunction2>)block __attribute__((swift_name("intercept(phase:block:)")));
- (NSArray<id<IdentityKotlinSuspendFunction2>> *)interceptorsForPhasePhase:(IdentityKtor_utilsPipelinePhase *)phase __attribute__((swift_name("interceptorsForPhase(phase:)")));
- (void)mergeFrom:(IdentityKtor_utilsPipeline<TSubject, TContext> *)from __attribute__((swift_name("merge(from:)")));
- (void)mergePhasesFrom:(IdentityKtor_utilsPipeline<TSubject, TContext> *)from __attribute__((swift_name("mergePhases(from:)")));
- (void)resetFromFrom:(IdentityKtor_utilsPipeline<TSubject, TContext> *)from __attribute__((swift_name("resetFrom(from:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<IdentityKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@property (readonly, getter=isEmpty_) BOOL isEmpty __attribute__((swift_name("isEmpty")));
@property (readonly) NSArray<IdentityKtor_utilsPipelinePhase *> *items __attribute__((swift_name("items")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpReceivePipeline")))
@interface IdentityKtor_client_coreHttpReceivePipeline : IdentityKtor_utilsPipeline<IdentityKtor_client_coreHttpResponse *, IdentityKotlinUnit *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhases:(IdentityKotlinArray<IdentityKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhase:(IdentityKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<IdentityKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityKtor_client_coreHttpReceivePipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestPipeline")))
@interface IdentityKtor_client_coreHttpRequestPipeline : IdentityKtor_utilsPipeline<id, IdentityKtor_client_coreHttpRequestBuilder *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhases:(IdentityKotlinArray<IdentityKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhase:(IdentityKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<IdentityKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityKtor_client_coreHttpRequestPipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponsePipeline")))
@interface IdentityKtor_client_coreHttpResponsePipeline : IdentityKtor_utilsPipeline<IdentityKtor_client_coreHttpResponseContainer *, IdentityKtor_client_coreHttpClientCall *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhases:(IdentityKotlinArray<IdentityKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhase:(IdentityKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<IdentityKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityKtor_client_coreHttpResponsePipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpSendPipeline")))
@interface IdentityKtor_client_coreHttpSendPipeline : IdentityKtor_utilsPipeline<id, IdentityKtor_client_coreHttpRequestBuilder *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhases:(IdentityKotlinArray<IdentityKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhase:(IdentityKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<IdentityKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityKtor_client_coreHttpSendPipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end

__attribute__((swift_name("Kotlinx_datetimeDateTimeFormat")))
@protocol IdentityKotlinx_datetimeDateTimeFormat
@required
- (NSString *)formatValue:(id _Nullable)value __attribute__((swift_name("format(value:)")));
- (id<IdentityKotlinAppendable>)formatToAppendable:(id<IdentityKotlinAppendable>)appendable value:(id _Nullable)value __attribute__((swift_name("formatTo(appendable:value:)")));
- (id _Nullable)parseInput:(id)input __attribute__((swift_name("parse(input:)")));
- (id _Nullable)parseOrNullInput:(id)input __attribute__((swift_name("parseOrNull(input:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinUnit")))
@interface IdentityKotlinUnit : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)unit __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKotlinUnit *shared __attribute__((swift_name("shared")));
- (NSString *)description __attribute__((swift_name("description()")));
@end


/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
__attribute__((swift_name("Kotlinx_coroutines_coreSelectInstance")))
@protocol IdentityKotlinx_coroutines_coreSelectInstance
@required
- (void)disposeOnCompletionDisposableHandle:(id<IdentityKotlinx_coroutines_coreDisposableHandle>)disposableHandle __attribute__((swift_name("disposeOnCompletion(disposableHandle:)")));
- (void)selectInRegistrationPhaseInternalResult:(id _Nullable)internalResult __attribute__((swift_name("selectInRegistrationPhase(internalResult:)")));
- (BOOL)trySelectClauseObject:(id)clauseObject result:(id _Nullable)result __attribute__((swift_name("trySelect(clauseObject:result:)")));
@property (readonly) id<IdentityKotlinCoroutineContext> context __attribute__((swift_name("context")));
@end


/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
__attribute__((swift_name("Kotlinx_coroutines_coreParentJob")))
@protocol IdentityKotlinx_coroutines_coreParentJob <IdentityKotlinx_coroutines_coreJob>
@required

/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
- (IdentityKotlinCancellationException *)getChildJobCancellationCause __attribute__((swift_name("getChildJobCancellationCause()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
__attribute__((swift_name("Kotlinx_serialization_coreSerializersModuleCollector")))
@protocol IdentityKotlinx_serialization_coreSerializersModuleCollector
@required
- (void)contextualKClass:(id<IdentityKotlinKClass>)kClass provider:(id<IdentityKotlinx_serialization_coreKSerializer> (^)(NSArray<id<IdentityKotlinx_serialization_coreKSerializer>> *))provider __attribute__((swift_name("contextual(kClass:provider:)")));
- (void)contextualKClass:(id<IdentityKotlinKClass>)kClass serializer:(id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("contextual(kClass:serializer:)")));
- (void)polymorphicBaseClass:(id<IdentityKotlinKClass>)baseClass actualClass:(id<IdentityKotlinKClass>)actualClass actualSerializer:(id<IdentityKotlinx_serialization_coreKSerializer>)actualSerializer __attribute__((swift_name("polymorphic(baseClass:actualClass:actualSerializer:)")));
- (void)polymorphicDefaultBaseClass:(id<IdentityKotlinKClass>)baseClass defaultDeserializerProvider:(id<IdentityKotlinx_serialization_coreDeserializationStrategy> _Nullable (^)(NSString * _Nullable))defaultDeserializerProvider __attribute__((swift_name("polymorphicDefault(baseClass:defaultDeserializerProvider:)"))) __attribute__((deprecated("Deprecated in favor of function with more precise name: polymorphicDefaultDeserializer")));
- (void)polymorphicDefaultDeserializerBaseClass:(id<IdentityKotlinKClass>)baseClass defaultDeserializerProvider:(id<IdentityKotlinx_serialization_coreDeserializationStrategy> _Nullable (^)(NSString * _Nullable))defaultDeserializerProvider __attribute__((swift_name("polymorphicDefaultDeserializer(baseClass:defaultDeserializerProvider:)")));
- (void)polymorphicDefaultSerializerBaseClass:(id<IdentityKotlinKClass>)baseClass defaultSerializerProvider:(id<IdentityKotlinx_serialization_coreSerializationStrategy> _Nullable (^)(id))defaultSerializerProvider __attribute__((swift_name("polymorphicDefaultSerializer(baseClass:defaultSerializerProvider:)")));
@end

__attribute__((swift_name("KotlinKDeclarationContainer")))
@protocol IdentityKotlinKDeclarationContainer
@required
@end

__attribute__((swift_name("KotlinKAnnotatedElement")))
@protocol IdentityKotlinKAnnotatedElement
@required
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
__attribute__((swift_name("KotlinKClassifier")))
@protocol IdentityKotlinKClassifier
@required
@end

__attribute__((swift_name("KotlinKClass")))
@protocol IdentityKotlinKClass <IdentityKotlinKDeclarationContainer, IdentityKotlinKAnnotatedElement, IdentityKotlinKClassifier>
@required

/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
- (BOOL)isInstanceValue:(id _Nullable)value __attribute__((swift_name("isInstance(value:)")));
@property (readonly) NSString * _Nullable qualifiedName __attribute__((swift_name("qualifiedName")));
@property (readonly) NSString * _Nullable simpleName __attribute__((swift_name("simpleName")));
@end

__attribute__((swift_name("Ktor_ioJvmSerializable")))
@protocol IdentityKtor_ioJvmSerializable
@required
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=io/ktor/http/UrlSerializer))
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpUrl")))
@interface IdentityKtor_httpUrl : IdentityBase <IdentityKtor_ioJvmSerializable>
@property (class, readonly, getter=companion) IdentityKtor_httpUrlCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *encodedFragment __attribute__((swift_name("encodedFragment")));
@property (readonly) NSString * _Nullable encodedPassword __attribute__((swift_name("encodedPassword")));
@property (readonly) NSString *encodedPath __attribute__((swift_name("encodedPath")));
@property (readonly) NSString *encodedPathAndQuery __attribute__((swift_name("encodedPathAndQuery")));
@property (readonly) NSString *encodedQuery __attribute__((swift_name("encodedQuery")));
@property (readonly) NSString * _Nullable encodedUser __attribute__((swift_name("encodedUser")));
@property (readonly) NSString *fragment __attribute__((swift_name("fragment")));
@property (readonly) NSString *host __attribute__((swift_name("host")));
@property (readonly) id<IdentityKtor_httpParameters> parameters __attribute__((swift_name("parameters")));
@property (readonly) NSString * _Nullable password __attribute__((swift_name("password")));
@property (readonly) NSArray<NSString *> *pathSegments __attribute__((swift_name("pathSegments"))) __attribute__((deprecated("\n        `pathSegments` is deprecated.\n\n        This property will contain an empty path segment at the beginning for URLs with a hostname,\n        and an empty path segment at the end for the URLs with a trailing slash. If you need to keep this behaviour please\n        use [rawSegments]. If you only need to access the meaningful parts of the path, consider using [segments] instead.\n             \n        Please decide if you need [rawSegments] or [segments] explicitly.\n        ")));
@property (readonly) int32_t port __attribute__((swift_name("port")));
@property (readonly) IdentityKtor_httpURLProtocol *protocol __attribute__((swift_name("protocol")));
@property (readonly) IdentityKtor_httpURLProtocol * _Nullable protocolOrNull __attribute__((swift_name("protocolOrNull")));
@property (readonly) NSArray<NSString *> *rawSegments __attribute__((swift_name("rawSegments")));
@property (readonly) NSArray<NSString *> *segments __attribute__((swift_name("segments")));
@property (readonly) int32_t specifiedPort __attribute__((swift_name("specifiedPort")));
@property (readonly) BOOL trailingQuery __attribute__((swift_name("trailingQuery")));
@property (readonly) NSString * _Nullable user __attribute__((swift_name("user")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpMethod")))
@interface IdentityKtor_httpHttpMethod : IdentityBase
- (instancetype)initWithValue:(NSString *)value __attribute__((swift_name("init(value:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKtor_httpHttpMethodCompanion *companion __attribute__((swift_name("companion")));
- (IdentityKtor_httpHttpMethod *)doCopyValue:(NSString *)value __attribute__((swift_name("doCopy(value:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((swift_name("Ktor_httpOutgoingContent")))
@interface IdentityKtor_httpOutgoingContent : IdentityBase
- (id _Nullable)getPropertyKey:(IdentityKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("getProperty(key:)")));
- (void)setPropertyKey:(IdentityKtor_utilsAttributeKey<id> *)key value:(id _Nullable)value __attribute__((swift_name("setProperty(key:value:)")));
- (id<IdentityKtor_httpHeaders> _Nullable)trailers __attribute__((swift_name("trailers()")));
@property (readonly) IdentityLong * _Nullable contentLength __attribute__((swift_name("contentLength")));
@property (readonly) IdentityKtor_httpContentType * _Nullable contentType __attribute__((swift_name("contentType")));
@property (readonly) id<IdentityKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@property (readonly) IdentityKtor_httpHttpStatusCode * _Nullable status __attribute__((swift_name("status")));
@end

__attribute__((swift_name("KotlinKType")))
@protocol IdentityKotlinKType
@required

/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
@property (readonly) NSArray<IdentityKotlinKTypeProjection *> *arguments __attribute__((swift_name("arguments")));

/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
@property (readonly) id<IdentityKotlinKClassifier> _Nullable classifier __attribute__((swift_name("classifier")));
@property (readonly) BOOL isMarkedNullable __attribute__((swift_name("isMarkedNullable")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsAttributeKey")))
@interface IdentityKtor_utilsAttributeKey<T> : IdentityBase

/**
 * @note annotations
 *   kotlin.jvm.JvmOverloads
*/
- (instancetype)initWithName:(NSString *)name type:(IdentityKtor_utilsTypeInfo *)type __attribute__((swift_name("init(name:type:)"))) __attribute__((objc_designated_initializer));
- (IdentityKtor_utilsAttributeKey<T> *)doCopyName:(NSString *)name type:(IdentityKtor_utilsTypeInfo *)type __attribute__((swift_name("doCopy(name:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end

__attribute__((swift_name("Kotlinx_io_coreRawSink")))
@protocol IdentityKotlinx_io_coreRawSink <IdentityKotlinAutoCloseable>
@required
- (void)flush __attribute__((swift_name("flush()")));
- (void)writeSource:(IdentityKotlinx_io_coreBuffer *)source byteCount:(int64_t)byteCount __attribute__((swift_name("write(source:byteCount:)")));
@end

__attribute__((swift_name("Kotlinx_io_coreSink")))
@protocol IdentityKotlinx_io_coreSink <IdentityKotlinx_io_coreRawSink>
@required
- (void)emit __attribute__((swift_name("emit()")));

/**
 * @note annotations
 *   kotlinx.io.InternalIoApi
*/
- (void)hintEmit __attribute__((swift_name("hintEmit()")));
- (int64_t)transferFromSource:(id<IdentityKotlinx_io_coreRawSource>)source __attribute__((swift_name("transferFrom(source:)")));
- (void)writeSource:(id<IdentityKotlinx_io_coreRawSource>)source byteCount_:(int64_t)byteCount __attribute__((swift_name("write(source:byteCount_:)")));
- (void)writeSource:(IdentityKotlinByteArray *)source startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("write(source:startIndex:endIndex:)")));
- (void)writeByteByte:(int8_t)byte __attribute__((swift_name("writeByte(byte:)")));
- (void)writeIntInt:(int32_t)int_ __attribute__((swift_name("writeInt(int:)")));
- (void)writeLongLong:(int64_t)long_ __attribute__((swift_name("writeLong(long:)")));
- (void)writeShortShort:(int16_t)short_ __attribute__((swift_name("writeShort(short:)")));

/**
 * @note annotations
 *   kotlinx.io.InternalIoApi
*/
@property (readonly) IdentityKotlinx_io_coreBuffer *buffer __attribute__((swift_name("buffer")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_io_coreBuffer")))
@interface IdentityKotlinx_io_coreBuffer : IdentityBase <IdentityKotlinx_io_coreSource, IdentityKotlinx_io_coreSink>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)clear __attribute__((swift_name("clear()")));
- (void)close __attribute__((swift_name("close()")));
- (IdentityKotlinx_io_coreBuffer *)doCopy __attribute__((swift_name("doCopy()")));
- (void)doCopyToOut:(IdentityKotlinx_io_coreBuffer *)out startIndex:(int64_t)startIndex endIndex:(int64_t)endIndex __attribute__((swift_name("doCopyTo(out:startIndex:endIndex:)")));
- (void)emit __attribute__((swift_name("emit()")));
- (BOOL)exhausted __attribute__((swift_name("exhausted()")));
- (void)flush __attribute__((swift_name("flush()")));
- (int8_t)getPosition:(int64_t)position __attribute__((swift_name("get(position:)")));

/**
 * @note annotations
 *   kotlinx.io.InternalIoApi
*/
- (void)hintEmit __attribute__((swift_name("hintEmit()")));
- (id<IdentityKotlinx_io_coreSource>)peek __attribute__((swift_name("peek()")));
- (int64_t)readAtMostToSink:(IdentityKotlinx_io_coreBuffer *)sink byteCount:(int64_t)byteCount __attribute__((swift_name("readAtMostTo(sink:byteCount:)")));
- (int32_t)readAtMostToSink:(IdentityKotlinByteArray *)sink startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("readAtMostTo(sink:startIndex:endIndex:)")));
- (int8_t)readByte __attribute__((swift_name("readByte()")));
- (int32_t)readInt __attribute__((swift_name("readInt()")));
- (int64_t)readLong __attribute__((swift_name("readLong()")));
- (int16_t)readShort __attribute__((swift_name("readShort()")));
- (void)readToSink:(id<IdentityKotlinx_io_coreRawSink>)sink byteCount:(int64_t)byteCount __attribute__((swift_name("readTo(sink:byteCount:)")));
- (BOOL)requestByteCount:(int64_t)byteCount __attribute__((swift_name("request(byteCount:)")));
- (void)requireByteCount:(int64_t)byteCount __attribute__((swift_name("require(byteCount:)")));
- (void)skipByteCount:(int64_t)byteCount __attribute__((swift_name("skip(byteCount:)")));
- (NSString *)description __attribute__((swift_name("description()")));
- (int64_t)transferFromSource:(id<IdentityKotlinx_io_coreRawSource>)source __attribute__((swift_name("transferFrom(source:)")));
- (int64_t)transferToSink:(id<IdentityKotlinx_io_coreRawSink>)sink __attribute__((swift_name("transferTo(sink:)")));
- (void)writeSource:(IdentityKotlinx_io_coreBuffer *)source byteCount:(int64_t)byteCount __attribute__((swift_name("write(source:byteCount:)")));
- (void)writeSource:(id<IdentityKotlinx_io_coreRawSource>)source byteCount_:(int64_t)byteCount __attribute__((swift_name("write(source:byteCount_:)")));
- (void)writeSource:(IdentityKotlinByteArray *)source startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("write(source:startIndex:endIndex:)")));
- (void)writeByteByte:(int8_t)byte __attribute__((swift_name("writeByte(byte:)")));
- (void)writeIntInt:(int32_t)int_ __attribute__((swift_name("writeInt(int:)")));
- (void)writeLongLong:(int64_t)long_ __attribute__((swift_name("writeLong(long:)")));
- (void)writeShortShort:(int16_t)short_ __attribute__((swift_name("writeShort(short:)")));

/**
 * @note annotations
 *   kotlinx.io.InternalIoApi
*/
@property (readonly) IdentityKotlinx_io_coreBuffer *buffer __attribute__((swift_name("buffer")));
@property (readonly) int64_t size __attribute__((swift_name("size")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsWeekDay.Companion")))
@interface IdentityKtor_utilsWeekDayCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_utilsWeekDayCompanion *shared __attribute__((swift_name("shared")));
- (IdentityKtor_utilsWeekDay *)fromOrdinal:(int32_t)ordinal __attribute__((swift_name("from(ordinal:)")));
- (IdentityKtor_utilsWeekDay *)fromValue:(NSString *)value __attribute__((swift_name("from(value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsMonth.Companion")))
@interface IdentityKtor_utilsMonthCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_utilsMonthCompanion *shared __attribute__((swift_name("shared")));
- (IdentityKtor_utilsMonth *)fromOrdinal:(int32_t)ordinal __attribute__((swift_name("from(ordinal:)")));
- (IdentityKtor_utilsMonth *)fromValue:(NSString *)value __attribute__((swift_name("from(value:)")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
*/
__attribute__((swift_name("KotlinAbstractCoroutineContextElement")))
@interface IdentityKotlinAbstractCoroutineContextElement : IdentityBase <IdentityKotlinCoroutineContextElement>
- (instancetype)initWithKey:(id<IdentityKotlinCoroutineContextKey>)key __attribute__((swift_name("init(key:)"))) __attribute__((objc_designated_initializer));
@property (readonly) id<IdentityKotlinCoroutineContextKey> key __attribute__((swift_name("key")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
*/
__attribute__((swift_name("KotlinContinuationInterceptor")))
@protocol IdentityKotlinContinuationInterceptor <IdentityKotlinCoroutineContextElement>
@required
- (id<IdentityKotlinContinuation>)interceptContinuationContinuation:(id<IdentityKotlinContinuation>)continuation __attribute__((swift_name("interceptContinuation(continuation:)")));
- (void)releaseInterceptedContinuationContinuation:(id<IdentityKotlinContinuation>)continuation __attribute__((swift_name("releaseInterceptedContinuation(continuation:)")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreCoroutineDispatcher")))
@interface IdentityKotlinx_coroutines_coreCoroutineDispatcher : IdentityKotlinAbstractCoroutineContextElement <IdentityKotlinContinuationInterceptor>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithKey:(id<IdentityKotlinCoroutineContextKey>)key __attribute__((swift_name("init(key:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityKotlinx_coroutines_coreCoroutineDispatcherKey *companion __attribute__((swift_name("companion")));
- (void)dispatchContext:(id<IdentityKotlinCoroutineContext>)context block:(id<IdentityKotlinx_coroutines_coreRunnable>)block __attribute__((swift_name("dispatch(context:block:)")));

/**
 * @note annotations
 *   kotlinx.coroutines.InternalCoroutinesApi
*/
- (void)dispatchYieldContext:(id<IdentityKotlinCoroutineContext>)context block:(id<IdentityKotlinx_coroutines_coreRunnable>)block __attribute__((swift_name("dispatchYield(context:block:)")));
- (id<IdentityKotlinContinuation>)interceptContinuationContinuation:(id<IdentityKotlinContinuation>)continuation __attribute__((swift_name("interceptContinuation(continuation:)")));
- (BOOL)isDispatchNeededContext:(id<IdentityKotlinCoroutineContext>)context __attribute__((swift_name("isDispatchNeeded(context:)")));
- (IdentityKotlinx_coroutines_coreCoroutineDispatcher *)limitedParallelismParallelism:(int32_t)parallelism name:(NSString * _Nullable)name __attribute__((swift_name("limitedParallelism(parallelism:name:)")));
- (IdentityKotlinx_coroutines_coreCoroutineDispatcher *)plusOther_:(IdentityKotlinx_coroutines_coreCoroutineDispatcher *)other __attribute__((swift_name("plus(other_:)"))) __attribute__((unavailable("Operator '+' on two CoroutineDispatcher objects is meaningless. CoroutineDispatcher is a coroutine context element and `+` is a set-sum operator for coroutine contexts. The dispatcher to the right of `+` just replaces the dispatcher to the left.")));
- (void)releaseInterceptedContinuationContinuation:(id<IdentityKotlinContinuation>)continuation __attribute__((swift_name("releaseInterceptedContinuation(continuation:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreProxyConfig")))
@interface IdentityKtor_client_coreProxyConfig : IdentityBase
- (instancetype)initWithUrl:(IdentityKtor_httpUrl *)url __attribute__((swift_name("init(url:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) IdentityKtor_httpUrl *url __attribute__((swift_name("url")));
@end

__attribute__((swift_name("Ktor_client_coreHttpClientPlugin")))
@protocol IdentityKtor_client_coreHttpClientPlugin
@required
- (void)installPlugin:(id)plugin scope:(IdentityKtor_client_coreHttpClient *)scope __attribute__((swift_name("install(plugin:scope:)")));
- (id)prepareBlock:(void (^)(id))block __attribute__((swift_name("prepare(block:)")));
@property (readonly) IdentityKtor_utilsAttributeKey<id> *key __attribute__((swift_name("key")));
@end

__attribute__((swift_name("Ktor_eventsEventDefinition")))
@interface IdentityKtor_eventsEventDefinition<T> : IdentityBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsPipelinePhase")))
@interface IdentityKtor_utilsPipelinePhase : IdentityBase
- (instancetype)initWithName:(NSString *)name __attribute__((swift_name("init(name:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end

__attribute__((swift_name("KotlinFunction")))
@protocol IdentityKotlinFunction
@required
@end

__attribute__((swift_name("KotlinSuspendFunction2")))
@protocol IdentityKotlinSuspendFunction2 <IdentityKotlinFunction>
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)invokeP1:(id _Nullable)p1 p2:(id _Nullable)p2 completionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("invoke(p1:p2:completionHandler:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpReceivePipeline.Phases")))
@interface IdentityKtor_client_coreHttpReceivePipelinePhases : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)phases __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_client_coreHttpReceivePipelinePhases *shared __attribute__((swift_name("shared")));
@property (readonly) IdentityKtor_utilsPipelinePhase *After __attribute__((swift_name("After")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Before __attribute__((swift_name("Before")));
@property (readonly) IdentityKtor_utilsPipelinePhase *State __attribute__((swift_name("State")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestPipeline.Phases")))
@interface IdentityKtor_client_coreHttpRequestPipelinePhases : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)phases __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_client_coreHttpRequestPipelinePhases *shared __attribute__((swift_name("shared")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Before __attribute__((swift_name("Before")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Render __attribute__((swift_name("Render")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Send __attribute__((swift_name("Send")));
@property (readonly) IdentityKtor_utilsPipelinePhase *State __attribute__((swift_name("State")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Transform __attribute__((swift_name("Transform")));
@end

__attribute__((swift_name("Ktor_httpHttpMessageBuilder")))
@protocol IdentityKtor_httpHttpMessageBuilder
@required
@property (readonly) IdentityKtor_httpHeadersBuilder *headers __attribute__((swift_name("headers")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestBuilder")))
@interface IdentityKtor_client_coreHttpRequestBuilder : IdentityBase <IdentityKtor_httpHttpMessageBuilder>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property (class, readonly, getter=companion) IdentityKtor_client_coreHttpRequestBuilderCompanion *companion __attribute__((swift_name("companion")));
- (IdentityKtor_client_coreHttpRequestData *)build __attribute__((swift_name("build()")));
- (id _Nullable)getCapabilityOrNullKey:(id<IdentityKtor_client_coreHttpClientEngineCapability>)key __attribute__((swift_name("getCapabilityOrNull(key:)")));
- (void)setAttributesBlock:(void (^)(id<IdentityKtor_utilsAttributes>))block __attribute__((swift_name("setAttributes(block:)")));
- (void)setCapabilityKey:(id<IdentityKtor_client_coreHttpClientEngineCapability>)key capability:(id)capability __attribute__((swift_name("setCapability(key:capability:)")));
- (IdentityKtor_client_coreHttpRequestBuilder *)takeFromBuilder:(IdentityKtor_client_coreHttpRequestBuilder *)builder __attribute__((swift_name("takeFrom(builder:)")));
- (IdentityKtor_client_coreHttpRequestBuilder *)takeFromWithExecutionContextBuilder:(IdentityKtor_client_coreHttpRequestBuilder *)builder __attribute__((swift_name("takeFromWithExecutionContext(builder:)")));
- (void)urlBlock:(void (^)(IdentityKtor_httpURLBuilder *, IdentityKtor_httpURLBuilder *))block __attribute__((swift_name("url(block:)")));
@property (readonly) id<IdentityKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property id body __attribute__((swift_name("body")));
@property IdentityKtor_utilsTypeInfo * _Nullable bodyType __attribute__((swift_name("bodyType")));
@property (readonly) id<IdentityKotlinx_coroutines_coreJob> executionContext __attribute__((swift_name("executionContext")));
@property (readonly) IdentityKtor_httpHeadersBuilder *headers __attribute__((swift_name("headers")));
@property IdentityKtor_httpHttpMethod *method __attribute__((swift_name("method")));
@property (readonly) IdentityKtor_httpURLBuilder *url __attribute__((swift_name("url")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponsePipeline.Phases")))
@interface IdentityKtor_client_coreHttpResponsePipelinePhases : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)phases __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_client_coreHttpResponsePipelinePhases *shared __attribute__((swift_name("shared")));
@property (readonly) IdentityKtor_utilsPipelinePhase *After __attribute__((swift_name("After")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Parse __attribute__((swift_name("Parse")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Receive __attribute__((swift_name("Receive")));
@property (readonly) IdentityKtor_utilsPipelinePhase *State __attribute__((swift_name("State")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Transform __attribute__((swift_name("Transform")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponseContainer")))
@interface IdentityKtor_client_coreHttpResponseContainer : IdentityBase
- (instancetype)initWithExpectedType:(IdentityKtor_utilsTypeInfo *)expectedType response:(id)response __attribute__((swift_name("init(expectedType:response:)"))) __attribute__((objc_designated_initializer));
- (IdentityKtor_client_coreHttpResponseContainer *)doCopyExpectedType:(IdentityKtor_utilsTypeInfo *)expectedType response:(id)response __attribute__((swift_name("doCopy(expectedType:response:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) IdentityKtor_utilsTypeInfo *expectedType __attribute__((swift_name("expectedType")));
@property (readonly) id response __attribute__((swift_name("response")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpSendPipeline.Phases")))
@interface IdentityKtor_client_coreHttpSendPipelinePhases : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)phases __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_client_coreHttpSendPipelinePhases *shared __attribute__((swift_name("shared")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Before __attribute__((swift_name("Before")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Engine __attribute__((swift_name("Engine")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Monitoring __attribute__((swift_name("Monitoring")));
@property (readonly) IdentityKtor_utilsPipelinePhase *Receive __attribute__((swift_name("Receive")));
@property (readonly) IdentityKtor_utilsPipelinePhase *State __attribute__((swift_name("State")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpUrl.Companion")))
@interface IdentityKtor_httpUrlCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_httpUrlCompanion *shared __attribute__((swift_name("shared")));
- (id<IdentityKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((swift_name("Ktor_httpParameters")))
@protocol IdentityKtor_httpParameters <IdentityKtor_utilsStringValues>
@required
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLProtocol")))
@interface IdentityKtor_httpURLProtocol : IdentityBase <IdentityKtor_ioJvmSerializable>
- (instancetype)initWithName:(NSString *)name defaultPort:(int32_t)defaultPort __attribute__((swift_name("init(name:defaultPort:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKtor_httpURLProtocolCompanion *companion __attribute__((swift_name("companion")));
- (IdentityKtor_httpURLProtocol *)doCopyName:(NSString *)name defaultPort:(int32_t)defaultPort __attribute__((swift_name("doCopy(name:defaultPort:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t defaultPort __attribute__((swift_name("defaultPort")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpMethod.Companion")))
@interface IdentityKtor_httpHttpMethodCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_httpHttpMethodCompanion *shared __attribute__((swift_name("shared")));
- (IdentityKtor_httpHttpMethod *)parseMethod:(NSString *)method __attribute__((swift_name("parse(method:)")));
@property (readonly) NSArray<IdentityKtor_httpHttpMethod *> *DefaultMethods __attribute__((swift_name("DefaultMethods")));
@property (readonly) IdentityKtor_httpHttpMethod *Delete __attribute__((swift_name("Delete")));
@property (readonly) IdentityKtor_httpHttpMethod *Get __attribute__((swift_name("Get")));
@property (readonly) IdentityKtor_httpHttpMethod *Head __attribute__((swift_name("Head")));
@property (readonly) IdentityKtor_httpHttpMethod *Options __attribute__((swift_name("Options")));
@property (readonly) IdentityKtor_httpHttpMethod *Patch __attribute__((swift_name("Patch")));
@property (readonly) IdentityKtor_httpHttpMethod *Post __attribute__((swift_name("Post")));
@property (readonly) IdentityKtor_httpHttpMethod *Put __attribute__((swift_name("Put")));
@end

__attribute__((swift_name("Ktor_httpHeaderValueWithParameters")))
@interface IdentityKtor_httpHeaderValueWithParameters : IdentityBase
- (instancetype)initWithContent:(NSString *)content parameters:(NSArray<IdentityKtor_httpHeaderValueParam *> *)parameters __attribute__((swift_name("init(content:parameters:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKtor_httpHeaderValueWithParametersCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)parameterName:(NSString *)name __attribute__((swift_name("parameter(name:)")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) NSString *content __attribute__((swift_name("content")));
@property (readonly) NSArray<IdentityKtor_httpHeaderValueParam *> *parameters __attribute__((swift_name("parameters")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpContentType")))
@interface IdentityKtor_httpContentType : IdentityKtor_httpHeaderValueWithParameters
- (instancetype)initWithContentType:(NSString *)contentType contentSubtype:(NSString *)contentSubtype parameters:(NSArray<IdentityKtor_httpHeaderValueParam *> *)parameters __attribute__((swift_name("init(contentType:contentSubtype:parameters:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithContent:(NSString *)content parameters:(NSArray<IdentityKtor_httpHeaderValueParam *> *)parameters __attribute__((swift_name("init(content:parameters:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) IdentityKtor_httpContentTypeCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (BOOL)matchPattern:(IdentityKtor_httpContentType *)pattern __attribute__((swift_name("match(pattern:)")));
- (BOOL)matchPattern_:(NSString *)pattern __attribute__((swift_name("match(pattern_:)")));
- (IdentityKtor_httpContentType *)withParameterName:(NSString *)name value:(NSString *)value __attribute__((swift_name("withParameter(name:value:)")));
- (IdentityKtor_httpContentType *)withoutParameters __attribute__((swift_name("withoutParameters()")));
@property (readonly) NSString *contentSubtype __attribute__((swift_name("contentSubtype")));
@property (readonly) NSString *contentType __attribute__((swift_name("contentType")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinKTypeProjection")))
@interface IdentityKotlinKTypeProjection : IdentityBase
- (instancetype)initWithVariance:(IdentityKotlinKVariance * _Nullable)variance type:(id<IdentityKotlinKType> _Nullable)type __attribute__((swift_name("init(variance:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKotlinKTypeProjectionCompanion *companion __attribute__((swift_name("companion")));
- (IdentityKotlinKTypeProjection *)doCopyVariance:(IdentityKotlinKVariance * _Nullable)variance type:(id<IdentityKotlinKType> _Nullable)type __attribute__((swift_name("doCopy(variance:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<IdentityKotlinKType> _Nullable type __attribute__((swift_name("type")));
@property (readonly) IdentityKotlinKVariance * _Nullable variance __attribute__((swift_name("variance")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
*/
__attribute__((swift_name("KotlinContinuation")))
@protocol IdentityKotlinContinuation
@required
- (void)resumeWithResult:(id _Nullable)result __attribute__((swift_name("resumeWith(result:)")));
@property (readonly) id<IdentityKotlinCoroutineContext> context __attribute__((swift_name("context")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
 *   kotlin.ExperimentalStdlibApi
*/
__attribute__((swift_name("KotlinAbstractCoroutineContextKey")))
@interface IdentityKotlinAbstractCoroutineContextKey<B, E> : IdentityBase <IdentityKotlinCoroutineContextKey>
- (instancetype)initWithBaseKey:(id<IdentityKotlinCoroutineContextKey>)baseKey safeCast:(E _Nullable (^)(id<IdentityKotlinCoroutineContextElement>))safeCast __attribute__((swift_name("init(baseKey:safeCast:)"))) __attribute__((objc_designated_initializer));
@end


/**
 * @note annotations
 *   kotlin.ExperimentalStdlibApi
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_coroutines_coreCoroutineDispatcher.Key")))
@interface IdentityKotlinx_coroutines_coreCoroutineDispatcherKey : IdentityKotlinAbstractCoroutineContextKey<id<IdentityKotlinContinuationInterceptor>, IdentityKotlinx_coroutines_coreCoroutineDispatcher *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithBaseKey:(id<IdentityKotlinCoroutineContextKey>)baseKey safeCast:(id<IdentityKotlinCoroutineContextElement> _Nullable (^)(id<IdentityKotlinCoroutineContextElement>))safeCast __attribute__((swift_name("init(baseKey:safeCast:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)key __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKotlinx_coroutines_coreCoroutineDispatcherKey *shared __attribute__((swift_name("shared")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreRunnable")))
@protocol IdentityKotlinx_coroutines_coreRunnable
@required
- (void)run __attribute__((swift_name("run()")));
@end

__attribute__((swift_name("Ktor_utilsStringValuesBuilder")))
@protocol IdentityKtor_utilsStringValuesBuilder
@required
- (void)appendName:(NSString *)name value:(NSString *)value __attribute__((swift_name("append(name:value:)")));
- (void)appendAllStringValues:(id<IdentityKtor_utilsStringValues>)stringValues __attribute__((swift_name("appendAll(stringValues:)")));
- (void)appendAllName:(NSString *)name values:(id)values __attribute__((swift_name("appendAll(name:values:)")));
- (void)appendMissingStringValues:(id<IdentityKtor_utilsStringValues>)stringValues __attribute__((swift_name("appendMissing(stringValues:)")));
- (void)appendMissingName:(NSString *)name values:(id)values __attribute__((swift_name("appendMissing(name:values:)")));
- (id<IdentityKtor_utilsStringValues>)build __attribute__((swift_name("build()")));
- (void)clear __attribute__((swift_name("clear()")));
- (BOOL)containsName:(NSString *)name __attribute__((swift_name("contains(name:)")));
- (BOOL)containsName:(NSString *)name value:(NSString *)value __attribute__((swift_name("contains(name:value:)")));
- (NSSet<id<IdentityKotlinMapEntry>> *)entries __attribute__((swift_name("entries()")));
- (NSString * _Nullable)getName:(NSString *)name __attribute__((swift_name("get(name:)")));
- (NSArray<NSString *> * _Nullable)getAllName:(NSString *)name __attribute__((swift_name("getAll(name:)")));
- (BOOL)isEmpty __attribute__((swift_name("isEmpty()")));
- (NSSet<NSString *> *)names __attribute__((swift_name("names()")));
- (void)removeName:(NSString *)name __attribute__((swift_name("remove(name:)")));
- (BOOL)removeName:(NSString *)name value:(NSString *)value __attribute__((swift_name("remove(name:value:)")));
- (void)removeKeysWithNoEntries __attribute__((swift_name("removeKeysWithNoEntries()")));
- (void)setName:(NSString *)name value:(NSString *)value __attribute__((swift_name("set(name:value:)")));
@property (readonly) BOOL caseInsensitiveName __attribute__((swift_name("caseInsensitiveName")));
@end

__attribute__((swift_name("Ktor_utilsStringValuesBuilderImpl")))
@interface IdentityKtor_utilsStringValuesBuilderImpl : IdentityBase <IdentityKtor_utilsStringValuesBuilder>
- (instancetype)initWithCaseInsensitiveName:(BOOL)caseInsensitiveName size:(int32_t)size __attribute__((swift_name("init(caseInsensitiveName:size:)"))) __attribute__((objc_designated_initializer));
- (void)appendName:(NSString *)name value:(NSString *)value __attribute__((swift_name("append(name:value:)")));
- (void)appendAllStringValues:(id<IdentityKtor_utilsStringValues>)stringValues __attribute__((swift_name("appendAll(stringValues:)")));
- (void)appendAllName:(NSString *)name values:(id)values __attribute__((swift_name("appendAll(name:values:)")));
- (void)appendMissingStringValues:(id<IdentityKtor_utilsStringValues>)stringValues __attribute__((swift_name("appendMissing(stringValues:)")));
- (void)appendMissingName:(NSString *)name values:(id)values __attribute__((swift_name("appendMissing(name:values:)")));
- (id<IdentityKtor_utilsStringValues>)build __attribute__((swift_name("build()")));
- (void)clear __attribute__((swift_name("clear()")));
- (BOOL)containsName:(NSString *)name __attribute__((swift_name("contains(name:)")));
- (BOOL)containsName:(NSString *)name value:(NSString *)value __attribute__((swift_name("contains(name:value:)")));
- (NSSet<id<IdentityKotlinMapEntry>> *)entries __attribute__((swift_name("entries()")));
- (NSString * _Nullable)getName:(NSString *)name __attribute__((swift_name("get(name:)")));
- (NSArray<NSString *> * _Nullable)getAllName:(NSString *)name __attribute__((swift_name("getAll(name:)")));
- (BOOL)isEmpty __attribute__((swift_name("isEmpty()")));
- (NSSet<NSString *> *)names __attribute__((swift_name("names()")));
- (void)removeName:(NSString *)name __attribute__((swift_name("remove(name:)")));
- (BOOL)removeName:(NSString *)name value:(NSString *)value __attribute__((swift_name("remove(name:value:)")));
- (void)removeKeysWithNoEntries __attribute__((swift_name("removeKeysWithNoEntries()")));
- (void)setName:(NSString *)name value:(NSString *)value __attribute__((swift_name("set(name:value:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)validateNameName:(NSString *)name __attribute__((swift_name("validateName(name:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)validateValueValue:(NSString *)value __attribute__((swift_name("validateValue(value:)")));
@property (readonly) BOOL caseInsensitiveName __attribute__((swift_name("caseInsensitiveName")));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) IdentityMutableDictionary<NSString *, NSMutableArray<NSString *> *> *values __attribute__((swift_name("values")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeadersBuilder")))
@interface IdentityKtor_httpHeadersBuilder : IdentityKtor_utilsStringValuesBuilderImpl
- (instancetype)initWithSize:(int32_t)size __attribute__((swift_name("init(size:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCaseInsensitiveName:(BOOL)caseInsensitiveName size:(int32_t)size __attribute__((swift_name("init(caseInsensitiveName:size:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<IdentityKtor_httpHeaders>)build __attribute__((swift_name("build()")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)validateNameName:(NSString *)name __attribute__((swift_name("validateName(name:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)validateValueValue:(NSString *)value __attribute__((swift_name("validateValue(value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestBuilder.Companion")))
@interface IdentityKtor_client_coreHttpRequestBuilderCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_client_coreHttpRequestBuilderCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLBuilder")))
@interface IdentityKtor_httpURLBuilder : IdentityBase
- (instancetype)initWithProtocol:(IdentityKtor_httpURLProtocol * _Nullable)protocol host:(NSString *)host port:(int32_t)port user:(NSString * _Nullable)user password:(NSString * _Nullable)password pathSegments:(NSArray<NSString *> *)pathSegments parameters:(id<IdentityKtor_httpParameters>)parameters fragment:(NSString *)fragment trailingQuery:(BOOL)trailingQuery __attribute__((swift_name("init(protocol:host:port:user:password:pathSegments:parameters:fragment:trailingQuery:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) IdentityKtor_httpURLBuilderCompanion *companion __attribute__((swift_name("companion")));
- (IdentityKtor_httpUrl *)build __attribute__((swift_name("build()")));
- (NSString *)buildString __attribute__((swift_name("buildString()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property NSString *encodedFragment __attribute__((swift_name("encodedFragment")));
@property id<IdentityKtor_httpParametersBuilder> encodedParameters __attribute__((swift_name("encodedParameters")));
@property NSString * _Nullable encodedPassword __attribute__((swift_name("encodedPassword")));
@property NSArray<NSString *> *encodedPathSegments __attribute__((swift_name("encodedPathSegments")));
@property NSString * _Nullable encodedUser __attribute__((swift_name("encodedUser")));
@property NSString *fragment __attribute__((swift_name("fragment")));
@property NSString *host __attribute__((swift_name("host")));
@property (readonly) id<IdentityKtor_httpParametersBuilder> parameters __attribute__((swift_name("parameters")));
@property NSString * _Nullable password __attribute__((swift_name("password")));
@property NSArray<NSString *> *pathSegments __attribute__((swift_name("pathSegments")));
@property int32_t port __attribute__((swift_name("port")));
@property IdentityKtor_httpURLProtocol *protocol __attribute__((swift_name("protocol")));
@property IdentityKtor_httpURLProtocol * _Nullable protocolOrNull __attribute__((swift_name("protocolOrNull")));
@property BOOL trailingQuery __attribute__((swift_name("trailingQuery")));
@property NSString * _Nullable user __attribute__((swift_name("user")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLProtocol.Companion")))
@interface IdentityKtor_httpURLProtocolCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_httpURLProtocolCompanion *shared __attribute__((swift_name("shared")));
- (IdentityKtor_httpURLProtocol *)createOrDefaultName:(NSString *)name __attribute__((swift_name("createOrDefault(name:)")));
@property (readonly) IdentityKtor_httpURLProtocol *HTTP __attribute__((swift_name("HTTP")));
@property (readonly) IdentityKtor_httpURLProtocol *HTTPS __attribute__((swift_name("HTTPS")));
@property (readonly) IdentityKtor_httpURLProtocol *SOCKS __attribute__((swift_name("SOCKS")));
@property (readonly) IdentityKtor_httpURLProtocol *WS __attribute__((swift_name("WS")));
@property (readonly) IdentityKtor_httpURLProtocol *WSS __attribute__((swift_name("WSS")));
@property (readonly) NSDictionary<NSString *, IdentityKtor_httpURLProtocol *> *byName __attribute__((swift_name("byName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeaderValueParam")))
@interface IdentityKtor_httpHeaderValueParam : IdentityBase
- (instancetype)initWithName:(NSString *)name value:(NSString *)value __attribute__((swift_name("init(name:value:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithName:(NSString *)name value:(NSString *)value escapeValue:(BOOL)escapeValue __attribute__((swift_name("init(name:value:escapeValue:)"))) __attribute__((objc_designated_initializer));
- (IdentityKtor_httpHeaderValueParam *)doCopyName:(NSString *)name value:(NSString *)value escapeValue:(BOOL)escapeValue __attribute__((swift_name("doCopy(name:value:escapeValue:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BOOL escapeValue __attribute__((swift_name("escapeValue")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeaderValueWithParameters.Companion")))
@interface IdentityKtor_httpHeaderValueWithParametersCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_httpHeaderValueWithParametersCompanion *shared __attribute__((swift_name("shared")));
- (id _Nullable)parseValue:(NSString *)value init:(id _Nullable (^)(NSString *, NSArray<IdentityKtor_httpHeaderValueParam *> *))init __attribute__((swift_name("parse(value:init:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpContentType.Companion")))
@interface IdentityKtor_httpContentTypeCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_httpContentTypeCompanion *shared __attribute__((swift_name("shared")));
- (IdentityKtor_httpContentType *)parseValue:(NSString *)value __attribute__((swift_name("parse(value:)")));
@property (readonly) IdentityKtor_httpContentType *Any __attribute__((swift_name("Any")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinKVariance")))
@interface IdentityKotlinKVariance : IdentityKotlinEnum<IdentityKotlinKVariance *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) IdentityKotlinKVariance *invariant __attribute__((swift_name("invariant")));
@property (class, readonly) IdentityKotlinKVariance *in __attribute__((swift_name("in")));
@property (class, readonly) IdentityKotlinKVariance *out __attribute__((swift_name("out")));
+ (IdentityKotlinArray<IdentityKotlinKVariance *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<IdentityKotlinKVariance *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinKTypeProjection.Companion")))
@interface IdentityKotlinKTypeProjectionCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKotlinKTypeProjectionCompanion *shared __attribute__((swift_name("shared")));

/**
 * @note annotations
 *   kotlin.jvm.JvmStatic
*/
- (IdentityKotlinKTypeProjection *)contravariantType:(id<IdentityKotlinKType>)type __attribute__((swift_name("contravariant(type:)")));

/**
 * @note annotations
 *   kotlin.jvm.JvmStatic
*/
- (IdentityKotlinKTypeProjection *)covariantType:(id<IdentityKotlinKType>)type __attribute__((swift_name("covariant(type:)")));

/**
 * @note annotations
 *   kotlin.jvm.JvmStatic
*/
- (IdentityKotlinKTypeProjection *)invariantType:(id<IdentityKotlinKType>)type __attribute__((swift_name("invariant(type:)")));
@property (readonly) IdentityKotlinKTypeProjection *STAR __attribute__((swift_name("STAR")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLBuilder.Companion")))
@interface IdentityKtor_httpURLBuilderCompanion : IdentityBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) IdentityKtor_httpURLBuilderCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((swift_name("Ktor_httpParametersBuilder")))
@protocol IdentityKtor_httpParametersBuilder <IdentityKtor_utilsStringValuesBuilder>
@required
@end

#pragma pop_macro("_Nullable_result")
#pragma clang diagnostic pop
NS_ASSUME_NONNULL_END
