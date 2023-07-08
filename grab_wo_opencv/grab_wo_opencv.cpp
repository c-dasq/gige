#include <pylon/PylonIncludes.h>

using namespace Pylon;
using namespace std;

void CaptureImageBySerialNumber(const string& serialNumber)
{
    PylonInitialize();

    try
    {
        CTlFactory& tlFactory = CTlFactory::GetInstance();
        DeviceInfoList_t devices;
        tlFactory.EnumerateDevices(devices);

        // Buscar la cámara con el número de serie especificado
        CDeviceInfo deviceInfo;
        bool found = false;
        for (size_t i = 0; i < devices.size(); ++i)
        {
            std::string currentSerialNumber(devices[i].GetSerialNumber().c_str());  // Convertir Pylon::String_t a std::string
            if (currentSerialNumber == serialNumber)
            {
                deviceInfo = devices[i];
                found = true;
                break;
            }
        }

        if (!found)
        {
            cerr << "Cámara no encontrada." << endl;
            return;
        }

        CInstantCamera camera(tlFactory.CreateDevice(deviceInfo));

        camera.Open();
        camera.StartGrabbing(GrabStrategy_LatestImageOnly);

        CGrabResultPtr grabResult;
        camera.RetrieveResult(1000, grabResult, TimeoutHandling_ThrowException);

        if (grabResult->GrabSucceeded())
        {
            // Guardar la imagen en un archivo, en éste caso tipo TIF
            CPylonImage image;
            image.AttachGrabResultBuffer(grabResult);
            image.Save(ImageFileFormat_Tiff, "resultado.tif");
            cout << "Imagen guardada exitosamente." << endl;
        }
        else
        {
            cerr << "Error: " << grabResult->GetErrorCode() << " " << grabResult->GetErrorDescription() << endl;
        }

        camera.StopGrabbing();
        camera.Close();
    }
    catch (const GenericException& e)
    {
        cerr << "Ocurrió una excepción: " << e.GetDescription() << endl;
    }

    PylonTerminate();
}

int main()
{
    string serialNumber = "21246949";  // Reemplaza con el número de serie de tu cámara

    CaptureImageBySerialNumber(serialNumber);

    return 0;
}
