#include "api.h"

void _extractTargetTempFromResponse(String, float &);

Api::Api()
{
    errorMessage = "";
}

bool Api::postData(float humidityData, float celData, float thermostatTargetTemp)
{
    String request, response;
    int statusCode = 0;

    request = "/update?api_key=" + (String)THINGSPEAK_API_KEY + (String) "&field1=" + (String)humidityData +
              "&field2=" + (String)celData + "&field3=" + (String)thermostatTargetTemp;
    Serial.println(request);

    HttpClient client = HttpClient(wifi, "api.thingspeak.com", 80);
    client.get(request);
    statusCode = client.responseStatusCode();
    response = client.responseBody();
    if (statusCode != 200)
    {
        errorMessage = (String)statusCode + ": " + response;
        return false;
    }
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
    return true;
}

bool Api::getTargetTemp(float &targetTemp)
{
    String request, response;
    int statusCode = 0;

    request = "/channels/" + (String)THINGSPEAK_CHANNEL_ID + "/feeds.json?results=" + (String)GET_NO_RESULTS; // Get only the last 5 results
    Serial.println(request);

    HttpClient client = HttpClient(wifi, "api.thingspeak.com", 80);
    client.get(request);
    statusCode = client.responseStatusCode();
    response = client.responseBody();

    if (statusCode != 200)
    {
        errorMessage = (String)statusCode + ": " + response;
        return false;
    }
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);

    _extractTargetTempFromResponse(response, targetTemp);
    return true;
}

void _extractTargetTempFromResponse(String response, float &targetTemp)
{
    const int responseLength = response.length();
    char json[responseLength + 1];
    for (int i = 0; i < responseLength; ++i)
        json[i] = response.charAt(i);
    json[responseLength] = 0; // put null characther

    DynamicJsonBuffer jsonBuffer(responseLength * 2);
    JsonObject &root = jsonBuffer.parseObject(json);
    if (!root.success())
    {
        Serial.println("parseObject() failed");
        return;
    }
    for (int i = GET_NO_RESULTS - 1; i >= 0; --i)
    {
        float temp = root["feeds"][i]["field3"];
        if (temp >= 10 && temp <= 30) // make sure the targetTemp is valid
        {
            if (temp != targetTemp)
            {
                targetTemp = temp;
                Serial.println("New target temperature has been set.");
            }
            break;
        }
    }
}