#include <pylon/PylonIncludes.h>
#include <opencv2/opencv.hpp>

using namespace Pylon;
using namespace cv;
using namespace std;

Mat CaptureImageBySerialNumber(const string& serialNumber)
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
            return Mat();
        }

        CInstantCamera camera(tlFactory.CreateDevice(deviceInfo));

        camera.Open();
        camera.StartGrabbing(GrabStrategy_LatestImageOnly);

        CGrabResultPtr grabResult;
        camera.RetrieveResult(1000, grabResult, TimeoutHandling_ThrowException);

        if (grabResult->GrabSucceeded())
        {
            Mat image(grabResult->GetHeight(), grabResult->GetWidth(), CV_8UC1, grabResult->GetBuffer());
            cvtColor(image, image, COLOR_BayerBG2BGR);

            // Guardar la imagen en un archivo JPG
            imwrite("resultado.jpg", image);
            cout << "Imagen guardada exitosamente." << endl;
            
            return image.clone();
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

    return Mat();
}

int main()
{
    string serialNumber = "21246949";  // Reemplaza con el número de serie de tu cámara

    Mat image = CaptureImageBySerialNumber(serialNumber);
    if (!image.empty())
    {
        cout << "Imagen generada con exito." << endl;
    }
    else
    {
        cerr << "No se pudo generar la imagen." << endl;
    }

    return 0;
}
