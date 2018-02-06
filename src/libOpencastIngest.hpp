#ifndef libOpencastIngest_hpp
#define libOpencastIngest_hpp

#include "libOpencastIngest.h"

#include <string>
#include <tuple>

namespace libOpencastIngest
{

struct HostInformation
{
	const std::string opencastInstanceUrl;
	const libOpencastIngest_AuthType authType;
	const std::string username;
	const std::string password;
	const std::string authCookie;
	const std::string useragent;

	HostInformation(
			const std::string & pOpencastInstanceUrl,
			libOpencastIngest_AuthType pAuthType,
			const std::string & pUsername,
			const std::string & pPassword,
			const std::string & pAuthCookie,
			const std::string & pUseragent):
		opencastInstanceUrl{pOpencastInstanceUrl},
		authType{pAuthType},
		username{pUsername},
		password{pPassword},
		authCookie{pAuthCookie},
		useragent{pUseragent}
	{
		return;
	}
};

inline std::string generateDCCatalog(
		const std::string & pCreated,
		const std::string & pTitle,
		const std::string & pSubject,
		const std::string & pDescription,
		const std::string & pLanguage,
		const std::string & pRights,
		const std::string & pLicense,
		const std::string & pSeriesId,
		const std::string & pPresenters,
		const std::string & pContributors)
{
	const char * result = libOpencastIngest_generateDCCatalog(
			pCreated.c_str(),
			pTitle.c_str(),
			pSubject.c_str(),
			pDescription.c_str(),
			pLanguage.c_str(),
			pRights.c_str(),
			pLicense.c_str(),
			pSeriesId.c_str(),
			pPresenters.c_str(),
			pContributors.c_str()
			);

	std::string ret{result};

	libOpencastIngest_cleanup(result);

	return ret;
}

inline std::tuple<long, long, std::string> createMediaPackage(
		const HostInformation & hI)
{
	long curlReturnCode = 0;
	long httpReturnCode = 0;

	const char * result = libOpencastIngest_createMediaPackage(
			hI.opencastInstanceUrl.c_str(),
			hI.authType,
			hI.username.c_str(),
			hI.password.c_str(),
			hI.authCookie.c_str(),
			hI.useragent.c_str(),
			&curlReturnCode,
			&httpReturnCode
			);

	std::string ret{result};

	libOpencastIngest_cleanup(result);

	return std::make_tuple(curlReturnCode, httpReturnCode, ret);
}

inline const std::tuple<long, long, std::string> addDCCatalog(
		const HostInformation & hI,
		const std::string & pFlavor,
		const std::string & pMediaPackage,
		const std::string & pDublinCore)
{
	long curlReturnCode = 0;
	long httpReturnCode = 0;

	const char * result = libOpencastIngest_addDCCatalog(
			hI.opencastInstanceUrl.c_str(),
			hI.authType,
			hI.username.c_str(),
			hI.password.c_str(),
			hI.authCookie.c_str(),
			hI.useragent.c_str(),
			pFlavor.c_str(),
			pMediaPackage.c_str(),
			pDublinCore.c_str(),
			&curlReturnCode,
			&httpReturnCode
			);

	std::string ret{result};

	libOpencastIngest_cleanup(result);

	return std::make_tuple(curlReturnCode, httpReturnCode, ret);
}


inline std::tuple<long, long, std::string> addTrack(
		const HostInformation & hI,
		const std::string & pFlavor,
		const std::string & pMediaPackage,
		const std::string & pPathToTrack)
{
	long curlReturnCode = 0;
	long httpReturnCode = 0;

	const char * result = libOpencastIngest_addTrack(
			hI.opencastInstanceUrl.c_str(),
			hI.authType,
			hI.username.c_str(),
			hI.password.c_str(),
			hI.authCookie.c_str(),
			hI.useragent.c_str(),
			pFlavor.c_str(),
			pMediaPackage.c_str(),
			pPathToTrack.c_str(),
			&curlReturnCode,
			&httpReturnCode
			);

	std::string ret{result};

	libOpencastIngest_cleanup(result);

	return std::make_tuple(curlReturnCode, httpReturnCode, ret);
}


inline std::tuple<long, long, std::string> ingest(
		const HostInformation & hI,
		const std::string & pMediaPackage,
		const std::string & pWorkflowId)
{
	long curlReturnCode = 0;
	long httpReturnCode = 0;

	const char * result = libOpencastIngest_ingest(
			hI.opencastInstanceUrl.c_str(),
			hI.authType,
			hI.username.c_str(),
			hI.password.c_str(),
			hI.authCookie.c_str(),
			hI.useragent.c_str(),
			pMediaPackage.c_str(),
			pWorkflowId.c_str(),
			&curlReturnCode,
			&httpReturnCode
			);

	std::string ret{result};

	libOpencastIngest_cleanup(result);

	return std::make_tuple(curlReturnCode, httpReturnCode, ret);
}


}

#endif
