#include "ResponseStatusCode.h"

std::string http::responseStatusCodeToString(const http::ResponseStatusCode &responseStatusCode) {
    switch (responseStatusCode) {
        case ResponseStatusCode::CONTINUE: return "Continue";
        case ResponseStatusCode::SWITCHING_PROTOCOLS: return "Switching Protocols";
        case ResponseStatusCode::PROCESSING: return "Processing";
        case ResponseStatusCode::EARLY_HINTS: return "Early Hints";
        case ResponseStatusCode::OK: return "OK";
        case ResponseStatusCode::CREATED: return "Created";
        case ResponseStatusCode::ACCEPTED: return "Accepted";
        case ResponseStatusCode::NO_CONTENT: return "No Content";
        case ResponseStatusCode::RESET_CONTENT: return "Reset Content";
        case ResponseStatusCode::PARTIAL_CONTENT: return "Partial Content";
        case ResponseStatusCode::MULTI_STATUS: return "Multi-Status";
        case ResponseStatusCode::ALREADY_REPORTED: return "Already Reported";
        case ResponseStatusCode::MULTIPLE_CHOICES: return "Multiple Choices";
        case ResponseStatusCode::MOVED_PERMANENTLY: return "Moved Permanently";
        case ResponseStatusCode::FOUND: return "Found";
        case ResponseStatusCode::SEE_OTHER: return "See Other";
        case ResponseStatusCode::NOT_MODIFIED: return "Not Modified";
        case ResponseStatusCode::TEMPORARY_REDIRECT: return "Temporary Redirect";
        case ResponseStatusCode::PERMANENT_REDIRECT: return "Permanent Redirect";
        case ResponseStatusCode::BAD_REQUEST: return "Bad Request";
        case ResponseStatusCode::UNAUTHORIZED: return "Unauthorized";
        case ResponseStatusCode::PAYMENT_REQUIRED: return "Payment Required";
        case ResponseStatusCode::FORBIDDEN: return "Forbidden";
        case ResponseStatusCode::NOT_FOUND: return "Not Found";
        case ResponseStatusCode::METHOD_NOT_ALLOWED: return "Method Not Allowed";
        case ResponseStatusCode::NOT_ACCEPTABLE: return "Not Acceptable";
        case ResponseStatusCode::PROXY_AUTHENTICATION_REQUIRED: return "Proxy Authentication Required";
        case ResponseStatusCode::REQUEST_TIMEOUT: return "Request Timeout";
        case ResponseStatusCode::CONFLICT: return "Conflict";
        case ResponseStatusCode::GONE: return "Gone";
        case ResponseStatusCode::LENGTH_REQUIRED: return "Length Required";
        case ResponseStatusCode::PRECONDITION_FAILED: return "Precondition Failed";
        case ResponseStatusCode::CONTENT_TOO_LARGE: return "Content Too Large";
        case ResponseStatusCode::URI_TOO_LONG: return "URI Too Long";
        case ResponseStatusCode::UNSUPPORTED_MEDIA_TYPE: return "Unsupported Media Type";
        case ResponseStatusCode::MISDIRECTED_REQUEST: return "Misdirected Request";
        case ResponseStatusCode::UNPROCESSABLE_CONTENT: return "Unprocessable Content";
        case ResponseStatusCode::LOCKED: return "Locked";
        case ResponseStatusCode::INTERNAL_SERVER_ERROR: return "Internal Server Error";
        case ResponseStatusCode::NOT_IMPLEMENTED: return "Not Implemented";
        case ResponseStatusCode::BAD_GATEWAY: return "Bad Gateway";
        case ResponseStatusCode::SERVICE_UNAVAILABLE: return "Service Unavailable";
        case ResponseStatusCode::GATEWAY_TIMEOUT: return "Gateway Timeout";
        case ResponseStatusCode::HTTP_VERSION_NOT_SUPPORTED: return "HTTP Version Not Supported";
        case ResponseStatusCode::VARIANT_ALSO_NEGOTIATES: return "Variant Also Negotiates";
        case ResponseStatusCode::INSUFFICIENT_STORAGE: return "Insufficient Storage";
        case ResponseStatusCode::LOOP_DETECTED: return "Loop Detected";
        case ResponseStatusCode::NOT_EXTENDED: return "Not Extended";
        case ResponseStatusCode::NETWORK_AUTHENTICATION_REQUIRED: return "Network Authentication Required";
    }
}

std::string http::responseStatusCodeToStringNumber(const http::ResponseStatusCode &responseStatusCode) {
    switch (responseStatusCode) {
        case ResponseStatusCode::CONTINUE: return "100";
        case ResponseStatusCode::SWITCHING_PROTOCOLS: return "101";
        case ResponseStatusCode::PROCESSING: return "102";
        case ResponseStatusCode::EARLY_HINTS: return "103";
        case ResponseStatusCode::OK: return "200";
        case ResponseStatusCode::CREATED: return "201";
        case ResponseStatusCode::ACCEPTED: return "202";
        case ResponseStatusCode::NO_CONTENT: return "204";
        case ResponseStatusCode::RESET_CONTENT: return "205";
        case ResponseStatusCode::PARTIAL_CONTENT: return "206";
        case ResponseStatusCode::MULTI_STATUS: return "207";
        case ResponseStatusCode::ALREADY_REPORTED: return "208";
        case ResponseStatusCode::MULTIPLE_CHOICES: return "300";
        case ResponseStatusCode::MOVED_PERMANENTLY: return "301";
        case ResponseStatusCode::FOUND: return "302";
        case ResponseStatusCode::SEE_OTHER: return "303";
        case ResponseStatusCode::NOT_MODIFIED: return "304";
        case ResponseStatusCode::TEMPORARY_REDIRECT: return "307";
        case ResponseStatusCode::PERMANENT_REDIRECT: return "308";
        case ResponseStatusCode::BAD_REQUEST: return "400";
        case ResponseStatusCode::UNAUTHORIZED: return "401";
        case ResponseStatusCode::PAYMENT_REQUIRED: return "402";
        case ResponseStatusCode::FORBIDDEN: return "403";
        case ResponseStatusCode::NOT_FOUND: return "404";
        case ResponseStatusCode::METHOD_NOT_ALLOWED: return "405";
        case ResponseStatusCode::NOT_ACCEPTABLE: return "406";
        case ResponseStatusCode::PROXY_AUTHENTICATION_REQUIRED: return "407";
        case ResponseStatusCode::REQUEST_TIMEOUT: return "408";
        case ResponseStatusCode::CONFLICT: return "409";
        case ResponseStatusCode::GONE: return "410";
        case ResponseStatusCode::LENGTH_REQUIRED: return "411";
        case ResponseStatusCode::PRECONDITION_FAILED: return "412";
        case ResponseStatusCode::CONTENT_TOO_LARGE: return "413";
        case ResponseStatusCode::URI_TOO_LONG: return "414";
        case ResponseStatusCode::UNSUPPORTED_MEDIA_TYPE: return "415";
        case ResponseStatusCode::MISDIRECTED_REQUEST: return "421";
        case ResponseStatusCode::UNPROCESSABLE_CONTENT: return "422";
        case ResponseStatusCode::LOCKED: return "423";
        case ResponseStatusCode::INTERNAL_SERVER_ERROR: return "500";
        case ResponseStatusCode::NOT_IMPLEMENTED: return "501";
        case ResponseStatusCode::BAD_GATEWAY: return "502";
        case ResponseStatusCode::SERVICE_UNAVAILABLE: return "503";
        case ResponseStatusCode::GATEWAY_TIMEOUT: return "504";
        case ResponseStatusCode::HTTP_VERSION_NOT_SUPPORTED: return "505";
        case ResponseStatusCode::VARIANT_ALSO_NEGOTIATES: return "506";
        case ResponseStatusCode::INSUFFICIENT_STORAGE: return "507";
        case ResponseStatusCode::LOOP_DETECTED: return "508";
        case ResponseStatusCode::NOT_EXTENDED: return "510";
        case ResponseStatusCode::NETWORK_AUTHENTICATION_REQUIRED: return "511";
    }
}

http::ResponseStatusCode http::stringToResponseStatusCode(const std::string &str) {
    if (str == "100") return ResponseStatusCode::CONTINUE;
    else if(str == "101") return ResponseStatusCode::SWITCHING_PROTOCOLS;
    else if(str == "102") return ResponseStatusCode::PROCESSING;
    else if(str == "103") return ResponseStatusCode::EARLY_HINTS;
    else if(str == "200") return ResponseStatusCode::OK;
    else if(str == "201") return ResponseStatusCode::CREATED;
    else if(str == "202") return ResponseStatusCode::ACCEPTED;
    else if(str == "204") return ResponseStatusCode::NO_CONTENT;
    else if(str == "205") return ResponseStatusCode::RESET_CONTENT;
    else if(str == "206") return ResponseStatusCode::PARTIAL_CONTENT;
    else if(str == "207") return ResponseStatusCode::MULTI_STATUS;
    else if(str == "208") return ResponseStatusCode::ALREADY_REPORTED;
    else if(str == "300") return ResponseStatusCode::MULTIPLE_CHOICES;
    else if(str == "301") return ResponseStatusCode::MOVED_PERMANENTLY;
    else if(str == "302") return ResponseStatusCode::FOUND;
    else if(str == "303") return ResponseStatusCode::SEE_OTHER;
    else if(str == "304") return ResponseStatusCode::NOT_MODIFIED;
    else if(str == "307") return ResponseStatusCode::TEMPORARY_REDIRECT;
    else if(str == "308") return ResponseStatusCode::PERMANENT_REDIRECT;
    else if(str == "400") return ResponseStatusCode::BAD_REQUEST;
    else if(str == "401") return ResponseStatusCode::UNAUTHORIZED;
    else if(str == "402") return ResponseStatusCode::PAYMENT_REQUIRED;
    else if(str == "403") return ResponseStatusCode::FORBIDDEN;
    else if(str == "404") return ResponseStatusCode::NOT_FOUND;
    else if(str == "405") return ResponseStatusCode::METHOD_NOT_ALLOWED;
    else if(str == "406") return ResponseStatusCode::NOT_ACCEPTABLE;
    else if(str == "407") return ResponseStatusCode::PROXY_AUTHENTICATION_REQUIRED;
    else if(str == "408") return ResponseStatusCode::REQUEST_TIMEOUT;
    else if(str == "409") return ResponseStatusCode::CONFLICT;
    else if(str == "410") return ResponseStatusCode::GONE;
    else if(str == "411") return ResponseStatusCode::LENGTH_REQUIRED;
    else if(str == "412") return ResponseStatusCode::PRECONDITION_FAILED;
    else if(str == "413") return ResponseStatusCode::CONTENT_TOO_LARGE;
    else if(str == "414") return ResponseStatusCode::URI_TOO_LONG;
    else if(str == "415") return ResponseStatusCode::UNSUPPORTED_MEDIA_TYPE;
    else if(str == "421") return ResponseStatusCode::MISDIRECTED_REQUEST;
    else if(str == "422") return ResponseStatusCode::UNPROCESSABLE_CONTENT;
    else if(str == "423") return ResponseStatusCode::LOCKED;
    else if(str == "500") return ResponseStatusCode::INTERNAL_SERVER_ERROR;
    else if(str == "501") return ResponseStatusCode::NOT_IMPLEMENTED;
    else if(str == "502") return ResponseStatusCode::BAD_GATEWAY;
    else if(str == "503") return ResponseStatusCode::SERVICE_UNAVAILABLE;
    else if(str == "504") return ResponseStatusCode::GATEWAY_TIMEOUT;
    else if(str == "505") return ResponseStatusCode::HTTP_VERSION_NOT_SUPPORTED;
    else if(str == "506") return ResponseStatusCode::VARIANT_ALSO_NEGOTIATES;
    else if(str == "507") return ResponseStatusCode::INSUFFICIENT_STORAGE;
    else if(str == "508") return ResponseStatusCode::LOOP_DETECTED;
    else if(str == "510") return ResponseStatusCode::NOT_EXTENDED;
    else if(str == "511") return ResponseStatusCode::NETWORK_AUTHENTICATION_REQUIRED;
}


