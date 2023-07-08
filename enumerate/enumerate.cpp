#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <pylon/PylonIncludes.h>

using namespace Pylon;
using namespace rapidjson;
using namespace std;

string GetGigECamerasJSON()
{
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    try
    {
        PylonInitialize();

        CTlFactory& tlFactory = CTlFactory::GetInstance();
        DeviceInfoList_t devices;
        tlFactory.EnumerateDevices(devices);

        Value cameraArray(kArrayType);

        for (size_t i = 0; i < devices.size(); ++i)
        {
            Value cameraObject(kObjectType);
            cameraObject.AddMember("SerialNumber", Value(devices[i].GetSerialNumber().c_str(), allocator).Move(), allocator);
            cameraObject.AddMember("ModelName", Value(devices[i].GetModelName().c_str(), allocator).Move(), allocator);
            cameraObject.AddMember("IpAddress", Value(devices[i].GetIpAddress().c_str(), allocator).Move(), allocator);

            cameraArray.PushBack(cameraObject, allocator);
        }

        document.AddMember("Cameras", cameraArray, allocator);

        PylonTerminate();
    }
    catch (const GenericException& e)
    {
        cerr << "Error: " << e.GetDescription() << endl;
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

int main()
{
    string json = GetGigECamerasJSON();
    cout << json << endl;

    return 0;
}
