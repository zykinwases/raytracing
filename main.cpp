#include <iostream>
#include <cstdint>

#include <string>
#include <vector>
#include <unordered_map>

#include "Bitmap.h"
#include "shapes.h"
#include "trace_ray.h"

const double DEST = 1; 

const uint32_t PICSIZE_X = 1024; //разрешение выходной картинки
const uint32_t PICSIZE_Y = 1024;
#define PICX_TO_VIEWX(x) (((x) - (double)PICSIZE_X / 2) * DEST / PICSIZE_X) // переходим от координат пикселя к координатам соответствующей
#define PICY_TO_VIEWY(y) (((y) - (double)PICSIZE_Y / 2) * DEST / PICSIZE_Y) // точки экрана (координата z равна DEST)

const Vec3m CAM(0, 0, 0);

int main(int argc, const char** argv) {
    std::unordered_map<std::string, std::string> cmdLineParams;

    for(int i=0; i<argc; i++) {
        std::string key(argv[i]);
        if(key.size() > 0 && key[0]=='-') {
            if(i != argc-1) { // not last argument
                cmdLineParams[key] = argv[i+1];
                i++;
            }
        else
            cmdLineParams[key] = "";
        }
    }

    std::string outFilePath = "zout.bmp";
    if(cmdLineParams.find("-out") != cmdLineParams.end())
        outFilePath = cmdLineParams["-out"];

    int sceneId = 0;
    if(cmdLineParams.find("-scene") != cmdLineParams.end())
        sceneId = atoi(cmdLineParams["-scene"].c_str());

    vec2 image(PICSIZE_Y);
    for (size_t i = 0; i < PICSIZE_Y; i++) {
        image[i].resize(PICSIZE_X);
    }

//описание сцены
    std::vector<Shape*> bulk;
    Colour red = Colour(255, 0, 0);
    Colour blue = Colour(0, 0, 255);
    Material red_ball(red);
    Material blue_ball(blue);
    Sphere sph1(Vec3m(0, -1, 3), 1, red_ball);
    Sphere sph2(Vec3m(1, 0, 5), 1, blue_ball);
    bulk.push_back(&sph1);
    bulk.push_back(&sph2);

    for(int i = 0; i < PICSIZE_Y; i++) {
        for(int j = 0; j < PICSIZE_X; j++) {
            double dir_x = ((j + 0.5) -  PICSIZE_X/2.) * DEST / PICSIZE_X; //0.5 - центр пикселя
            double dir_y = ((i + 0.5) - PICSIZE_Y/2.) * DEST / PICSIZE_Y;
            
            Vec3m dir(dir_x, dir_y, DEST);
            image[i][j] = trace_ray(CAM, dir.normilize(), bulk, 1000); //1000 - ограничение расстояния   
        }
    }

    SaveBMP(outFilePath.c_str(), image, PICSIZE_X, PICSIZE_Y);

    std::cout << "end." << std::endl;
    return 0;
}