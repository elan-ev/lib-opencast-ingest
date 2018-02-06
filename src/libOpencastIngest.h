#ifndef libOpencastIngest_h
#define libOpencastIngest_h

#ifdef __cplusplus
extern "C"
{
#endif


// set LIBOPENCASTINGEST_EXPORT define according to compilation settings
#if defined(_WIN32) && defined(LIBOPENCASTINGEST_AS_DYNAMIC_LIB)
#ifdef LIBOPENCASTINGEST_COMPILE_HEADER_ALS_LIB
	#define LIBOPENCASTINGEST_EXPORT __declspec(dllexport)
#else
	#define LIBOPENCASTINGEST_EXPORT __declspec(dllimport)
#endif
#else
	#define LIBOPENCASTINGEST_EXPORT
#endif

// used for setting the Authentication Methode, which will be used
enum libOpencastIngest_AuthType
{
	LIBOPENCASTINGEST_DIGESTAUTH = 1,
	LIBOPENCASTINGEST_BASICAUTH = 2,
	LIBOPENCASTINGEST_COOKIEAUTH = 3
};


// the char * needs to be cleared by libOpencastIngest_cleanup
LIBOPENCASTINGEST_EXPORT const char * libOpencastIngest_generateDCCatalog(
		const char * pCreated,
		const char * pTitle,
		const char * pSubject,
		const char * pDescription,
		const char * pLanguage,
		const char * pRights,
		const char * pLicense,
		const char * pSeriesId,
		const char * pPresenters,
		const char * pContributors);

// the char * needs to be cleared by libOpencastIngest_cleanup
LIBOPENCASTINGEST_EXPORT const char * libOpencastIngest_createMediaPackage(
		const char * pOpencastInstanceUrl,
		libOpencastIngest_AuthType pAuthType,
		const char * pUsername,
		const char * pPassword,
		const char * pAuthCookie,
		const char * pUseragent,
		long * outCurlReturnCode,
		long * outHttpReturnCode
		);

// the char * needs to be cleared by libOpencastIngest_cleanup
LIBOPENCASTINGEST_EXPORT const char * libOpencastIngest_addDCCatalog(
		const char * pOpencastInstanceUrl,
		libOpencastIngest_AuthType pAuthType,
		const char * pUsername,
		const char * pPassword,
		const char * pAuthCookie,
		const char * pUseragent,
		const char * pFlavor,
		const char * pMediaPackage,
		const char * pDublinCore,
		long * outCurlReturnCode,
		long * outHttpReturnCode
		);

// the char * needs to be cleared by libOpencastIngest_cleanup
LIBOPENCASTINGEST_EXPORT const char * libOpencastIngest_addTrack(
		const char * pOpencastInstanceUrl,
		libOpencastIngest_AuthType pAuthType,
		const char * pUsername,
		const char * pPassword,
		const char * pAuthCookie,
		const char * pUseragent,
		const char * pFlavor,
		const char * pMediaPackage,
		const char * pPathToTrack,
		long * outCurlReturnCode,
		long * outHttpReturnCode
		);

// the char * needs to be cleared by libOpencastIngest_cleanup
LIBOPENCASTINGEST_EXPORT const char * libOpencastIngest_ingest(
		const char * pOpencastInstanceUrl,
		libOpencastIngest_AuthType pAuthType,
		const char * pUsername,
		const char * pPassword,
		const char * pAuthCookie,
		const char * pUseragent,
		const char * pMediaPackage,
		const char * pWorkflowId,
		long * outCurlReturnCode,
		long * outHttpReturnCode
		);

// for cleanup of returned char *
LIBOPENCASTINGEST_EXPORT void libOpencastIngest_cleanup(const char * toCleanup);


#ifdef __cplusplus
}
#endif

#endif
