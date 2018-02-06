#include "libOpencastIngest.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>


using std::cout;
using std::endl;
using std::string;
using std::runtime_error;

using namespace libOpencastIngest;


static void throwWhenError(long curlReturnCode, long httpReturnCode)
{
	std::stringstream str{};

	if (curlReturnCode != 0)
	{
		str << "Curl error: " << curlReturnCode;

		throw runtime_error{str.str()};
	}

	if (httpReturnCode != 200)
	{
		str << "Http error: " << httpReturnCode;

		throw runtime_error{str.str()};
	}

	return;
}


// just a rudimentary test for the library
// can also be used as an example
int main(void){

	// testing generateDCCatalog
	
	string genDC = generateDCCatalog("created", "a", "b", "c", "d", "e", "f", "g", "h", "i");

	cout << "Generated DCCatalog: " << genDC << endl << endl;

	// testing generateDCCatalog

	string host = "http://localhost:8080/";
	libOpencastIngest_AuthType authType = LIBOPENCASTINGEST_DIGESTAUTH;
	string username = "opencast_system_account";
	string password = "CHANGE_ME";
	string authCookie = "";
	string useragent = "testLibOpencastIngest";


	string flavorDCCatalog = "dublincore/episode";
	string DCCatalog = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><dublincore xmlns=\"http://www.opencastproject.org/xsd/1.0/dublincore/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><dcterms:created xsi:type=\"dcterms:W3CDTF\">2017-05-24T15:28Z</dcterms:created><dcterms:creator>Test Creator</dcterms:creator><dcterms:extent xsi:type=\"dcterms:ISO8601\">PT5.568S</dcterms:extent><dcterms:title>Test Title</dcterms:title></dublincore>";

	string flavorTrack = "presenter/source";
	string pathToTrack = "video.flv";

	string workflowId = "fast";

	try
	{
		long curlCode = -1;
		long httpCode = -1;

		HostInformation hI{host, authType, username, password, authCookie, useragent};

		string mediaPackage{};
		long curlReturnCode = 0;
		long httpReturnCode = 0;

		std::tie(curlReturnCode, httpReturnCode, mediaPackage) = createMediaPackage(hI);
		throwWhenError(curlReturnCode, httpReturnCode);



		cout << "createMediaPackage WORKS!" << endl;

		cout << endl << "mediaPackage:" << endl << mediaPackage << endl;
		cout << endl << "DCCatalog:" << endl << DCCatalog << endl << endl;

		std::tie(curlReturnCode, httpReturnCode, mediaPackage) = addDCCatalog(hI,
						flavorDCCatalog, mediaPackage, DCCatalog);
		throwWhenError(curlReturnCode, httpReturnCode);

		cout << "addDCCatalog WORKS!" << endl;

		std::tie(curlReturnCode, httpReturnCode, mediaPackage) = addTrack(hI,
				flavorTrack,  mediaPackage,  pathToTrack);
		throwWhenError(curlReturnCode, httpReturnCode);

		cout << "addTrack WORKS!" << endl;

		std::tie(curlReturnCode, httpReturnCode, mediaPackage) = ingest(hI,
					mediaPackage, workflowId);
		throwWhenError(curlReturnCode, httpReturnCode);

		cout << "ingest WORKS!" << endl;

		cout << endl << endl << endl << mediaPackage << endl;
	}
	catch(runtime_error & e)
	{
		cout << "Catched Exception: " << e.what() << endl;
	}

	return 0;
}
