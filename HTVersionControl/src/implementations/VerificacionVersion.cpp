#include "VerificacionVersion.h"
#include <curl/curl.h>
#include <string>
#include <iostream>

const char* VerificacionVersion::VERSION = "1.0.0";

VerificacionVersion::VerificacionVersion()
{
}

bool VerificacionVersion::verificarVersion()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/latest_version.txt");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, VerificacionVersion::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
            std::cin.get();
            return false;
        }
        else
        {
            if(readBuffer == VERSION)
				return true;
			else
				return false;
        }

    }
}

int VerificacionVersion::descargarActualizacion()
{

}

size_t VerificacionVersion::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch (std::bad_alloc e)
    {
        // handle memory problem
        return 0;
    }

    std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
    return size * nmemb;
}