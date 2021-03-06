#ifndef __COCOS_SCRIPTING_LUA_BINDINGS_LUA_XML_HTTP_REQUEST_H__
#define __COCOS_SCRIPTING_LUA_BINDINGS_LUA_XML_HTTP_REQUEST_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif


#include "network/HttpClient.h"

class LuaMinXmlHttpRequest : public cocos2d::Object
{
public:
    enum class ResponseType
    {
        STRING,
        ARRAY_BUFFER,
        BLOB,
        DOCUMENT,
        JSON
    };
    
    // Ready States (http://www.w3.org/TR/XMLHttpRequest/#interface-xmlhttprequest)
    static const unsigned short UNSENT = 0;
    static const unsigned short OPENED = 1;
    static const unsigned short HEADERS_RECEIVED = 2;
    static const unsigned short LOADING = 3;
    static const unsigned short DONE = 4;
    
    LuaMinXmlHttpRequest();
    ~LuaMinXmlHttpRequest();
    
    void handle_requestResponse(network::HttpClient *sender, network::HttpResponse *response);

    inline void setResponseType(ResponseType type) { _responseType = type; }
    inline ResponseType getResponseType() {return _responseType; }

    inline void setWithCredentialsValue(bool value) { _withCredentialsValue = value; }
    inline bool getWithCredentialsValue() {return _withCredentialsValue; }

    inline void setTimeout(unsigned timeOut) {_timeout = timeOut; }
    inline unsigned getTimeout() { return _timeout;}

    inline void setReadyState(int readyState) { _readyState = readyState; }
    inline int getReadyState() { return _readyState ;}

    inline network::HttpRequest*  getHttpRequest() { return _httpRequest; }
    inline int getStatus() { return _status; }
    inline std::string getStatusText() { return _statusText ;}

    inline std::string getUrl(){return _url;}
    inline void setUrl(std::string url) { _url = url ;}

    inline std::string getMethod(){return _meth;}
    inline void setMethod(std::string meth) { _meth = meth ; }

    inline void setAsync(bool isAsync){ _isAsync = isAsync; }
    inline void setIsNetWork(bool isNetWork) {_isNetwork = isNetWork; }

    void _setHttpRequestHeader();
    void _sendRequest();
    void setRequestHeader(const char* field, const char* value);

    std::map<std::string, std::string> getHttpHeader() { return _httpHeader ;}
    
    void getByteData(unsigned char* byteData);
    
    inline std::string getDataStr() { return _data.str(); }
    
    inline size_t getDataSize() {   return _dataSize; }
    
private:
    void _gotHeader(std::string header);
    

    std::string                          _url;
    std::string                          _meth;
    std::string                          _type;
    std::stringstream                    _data;
    size_t                               _dataSize;
    int                                  _readyState;
    int                                  _status;
    std::string                          _statusText;
    ResponseType                         _responseType;
    unsigned                             _timeout;
    bool                                 _isAsync;
    network::HttpRequest*                _httpRequest;
    bool                                 _isNetwork;
    bool                                 _withCredentialsValue;
    std::map<std::string, std::string>   _httpHeader;
    std::map<std::string, std::string>   _requestHeader;
};

TOLUA_API int register_xml_http_request(lua_State* L);

#endif //#ifndef __COCOS_SCRIPTING_LUA_BINDINGS_LUA_XML_HTTP_REQUEST_H__
