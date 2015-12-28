#ifndef __HTTP_SERVICES_DELEGATE_H__
#define __HTTP_SERVICES_DELEGATE_H__

#define phoneKey		"phone_id_mapping"
#define mapData			"mapData"

enum HttpRequestMethod{
	UPLOAD_MAP,
	RATE_MAP,
	GET_MAP_UPLOAD_TIME_RANK,
	GET_MAP_RATING_RANK,
	COMMENT_MAP
};

typedef struct HttpShortMapInfo
{
	std::string mid;
	std::string creatorID;
	std::string rating;
	std::string uploadTime;
	std::string rateCounter;

	HttpShortMapInfo(std::string mapID, std::string creator, std::string rate,
		std::string timeUpload, std::string ratecount)
		:mid(mapID),
		creatorID(creator),
		rating(rate),
		uploadTime(timeUpload),
		rateCounter(ratecount)
	{}
};

class HttpServicesDelegate
{
public:
	/**
	* @js NA
	* @lua NA
	*/
	virtual ~HttpServicesDelegate() {}
	/**
	* @js NA
	* @lua NA
	*/
	virtual void getUID(std::string uid) {};

	//virtual void getMID(std::string uid) {};

	virtual void uploadMap() {};

	virtual void getMapUploadTimeRank(std::vector<HttpShortMapInfo> result) {};

};

#endif // __HELLOWORLD_SCENE_H__
