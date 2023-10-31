#include "VerificacionVersion.h"
#include <curl/curl.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include "servers.h"

VerificacionVersion::VerificacionVersion()
{
}

bool VerificacionVersion::verificarVersion()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    std::string archivo_version = "latest_version.txt";
    
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, (servidor + archivo_version).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, VerificacionVersion::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
            std::cout << "URL usada: " << servidor + UPDATER_NAME << std::endl;
            std::cin.get();
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }
        else
        {
            curl_easy_cleanup(curl);
            if(readBuffer == VERSION)
				return true;
			else
				return false;
        }

    }
    return false;
}

int VerificacionVersion::descargarActualizacion()
{
    CURL* curl;
    CURLcode res;
    FILE* fp;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        errno_t err = fopen_s(&fp, UPDATER_NAME.c_str(), "wb");
        if (err != 0 || fp == NULL)
        {
            printf("Could not open file %s for writing\n", UPDATER_NAME.c_str());
            return false;
        }

        curl_easy_setopt(curl, CURLOPT_URL, (servidor + UPDATER_NAME).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, VerificacionVersion::write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            std::cout << "URL usada: " << servidor + UPDATER_NAME << std::endl;
            std::cin.get();
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    curl_global_cleanup();

    std::string comandoEjecucionActualizador = "powershell -Command \"Start-Process -FilePath \'.\\" + UPDATER_NAME + "\'\"";

    system(comandoEjecucionActualizador.c_str());

    return true;
}

bool VerificacionVersion::checkConnection() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, servidor.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // Realizar un HTTP HEAD request
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            // Si hay un error, imprimimos el mensaje de error y devolvemos false.
#ifdef _DEBUG
            fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
            std::cout << "URL usada: " << servidor + UPDATER_NAME << std::endl;
            std::cin.get();
#endif
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return true;
}

bool VerificacionVersion::existeActualizador()
{
    return std::filesystem::exists(UPDATER_NAME);
}

void VerificacionVersion::eliminarActualizador()
{
    std::filesystem::path filePath(UPDATER_NAME);
    std::filesystem::remove(filePath);
}

size_t VerificacionVersion::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s)
{
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

size_t VerificacionVersion::write_data(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

const std::string VerificacionVersion::VERSION = "1.0.12";
const std::string VerificacionVersion::UPDATER_NAME = "Updater.bat";
const std::string VerificacionVersion::FILENAME = "HorasTrabajadas.exe";
std::string VerificacionVersion::servidor = "http://" + apache_ip + "/";