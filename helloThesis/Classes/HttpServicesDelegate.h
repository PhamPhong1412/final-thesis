#ifndef __HTTP_SERVICES_DELEGATE_H__
#define __HTTP_SERVICES_DELEGATE_H__


enum HttpRequestMethod{
	UPLOAD_MAP,
	RATE_MAP,
	COMMENT_MAP
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

	//virtual void uploadMap(std::string uid) {};

};

#endif // __HELLOWORLD_SCENE_H__
