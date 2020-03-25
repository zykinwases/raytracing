#include <iostream>
#include <cstdint>

#include <string>
#include <vector>
#include <unordered_map>

#include "Bitmap.h"
#include "shapes.h"
#include "trace_ray.h"


const uint32_t PICSIZE_X = 1024; //разрешение выходной картинки
const uint32_t PICSIZE_Y = 1024;

const Vec3m CAM(0, 0, 0);
const double DEST = 1; 

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
    std::vector<Shape*> shapes;
    Colour red = Colour(255 * 0.4, 255 * 0.4, 255 * 0.3); //заменить названия
    Colour blue = Colour(0, 0, 0);
    Colour green = Colour(255 * 0.3, 255 * 0.1, 255 * 0.1);
    Colour black = Colour(0, 0, 0);
    Colour min_white = Colour(255 * 0.3, 255 * 0.3, 255 * 0.3);
    Colour brown = Colour(255 * 0.3, 255 * 0.2, 255 * 0.2);
    Material red_ball(red, 50, 0.1);
    Material blue_ball(blue, 125, 0.1);
    Material green_ball(green, 10, 0.);
    Material white_ball(black, 1425, 0.8);
    Material floor_white(min_white);
    Material floor_brown(brown);
    Sphere sph1(Vec3m(-3, 0, 16), 2, red_ball);
    Sphere sph2(Vec3m(-1, -1.5, 12), 2, blue_ball);
    Sphere sph3(Vec3m(1.5, -0.5, 18), 3, green_ball);
    Sphere sph4(Vec3m(7, 5, 18), 4, white_ball);
    Floor fl(-10, min_white, brown);
    shapes.push_back(&sph1);
    shapes.push_back(&sph2);
    shapes.push_back(&sph3);
    shapes.push_back(&sph4);
    shapes.push_back(&fl);

    std::vector<Light*> lights;
    Light l1(Vec3m(-20, 20, 20), 0.5);
    Light l2(Vec3m(0, 10, -10), 0.8);
    Light l3(Vec3m(30, 20, 30), 0.7);
    lights.push_back(&l1);
    lights.push_back(&l2);
    lights.push_back(&l3);

    for(int i = 0; i < PICSIZE_Y; i++) {
        for(int j = 0; j < PICSIZE_X; j++) {
            double dir_x = ((j + 0.5) -  PICSIZE_X/2.) * DEST / PICSIZE_X; //0.5 - центр пикселя
            double dir_y = ((i + 0.5) - PICSIZE_Y/2.) * DEST / PICSIZE_Y;        
            Vec3m dir(dir_x, dir_y, DEST);
            image[i][j] = trace_ray(CAM, dir.normilize(), shapes, lights, 1000); //1000 - ограничение расстояния   
        }
    }

    SaveBMP(outFilePath.c_str(), image, PICSIZE_X, PICSIZE_Y);

    std::cout << "end." << std::endl;
    return 0;
}