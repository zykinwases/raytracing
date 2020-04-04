#include <iostream>
#include <cstdint>

#include <string>
#include <vector>
#include <unordered_map>

#include "Bitmap.h"
#include "shapes.h"
#include "trace_ray.h"

#include <omp.h>
#include <ctime>


const uint32_t PICSIZE_X = 1024; //разрешение выходной картинки
const uint32_t PICSIZE_Y = 1024;

const Vec3m CAM(0., 0., 0.);
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

    int numThreads = 1;
    if(cmdLineParams.find("-threads") != cmdLineParams.end())
        numThreads = atoi(cmdLineParams["-threads"].c_str());

    vec2 image(PICSIZE_Y);
    for (size_t i = 0; i < PICSIZE_Y; i++) {
        image[i].resize(PICSIZE_X);
    }

//описание сцены
    std::vector<Shape*> shapes;
    std::vector<Light*> lights;
    //Первая сцена
    Material yellow(Colour(120, 120, 0), 50, 0.1);
    Material black(Colour(0, 0, 0), 125, 0.1);
    Material red(Colour(90, 20, 20), 10, 0.3);
    Material black_specular(Colour(120, 120, 120), 1425, 0.8);
    Material floor_white(Colour(120, 120, 120), 1000, 0.9);
    Material floor_black(Colour(0, 0, 0), 1000, 0);
    Sphere sph1(Vec3m(-6, 2, 16), 2, yellow);
    Sphere sph2(Vec3m(13, 0, 4), 2, black);
    Sphere sph3(Vec3m(0, 4, 18), 3, red);
    Sphere sph4(Vec3m(1.5, 1, 7), 1, black_specular);
    Floor fl(-2, floor_white, floor_black);
    Light l1(Vec3m(-15, 10, -20), 0.5);
    Light l2(Vec3m(7, 20, -10), 0.8);
    Light l3(Vec3m(3, 40, -30), 0.7);
    //вторая сцена
    Material box_yellow(Colour(120,120,0), -1);
    Material box_red(Colour(120,0,0), -1);
    Material box_green(Colour(0,120,0), -1);
    Material box_blue(Colour(0,0,120), -1);
    Material box_black(Colour(0,0,0), -1);
    Sphere sph5(Vec3m(-1.7,-1,6), 1, yellow);
    Sphere sph6(Vec3m(2.3,-1,7), 1, red);
    Plane dist(Vec3m(0,0,-1), 10, box_yellow);
    Plane left(Vec3m(1,0,0), 3, box_red);
    Plane right(Vec3m(-1,0,0), 3, box_green);
    Plane top(Vec3m(0,-1,0), 3, box_blue);
    Plane bot(Vec3m(0,1,0), 2, box_blue);
    Plane back(Vec3m(0,0,1),5, box_black);
    Light l4(Vec3m(0,2.9,-3), 1);
    if (sceneId == 1) {
        shapes.push_back(&sph1);
        shapes.push_back(&sph2);
        shapes.push_back(&sph3);
        shapes.push_back(&sph4);
        shapes.push_back(&fl);

        lights.push_back(&l1);
        lights.push_back(&l2);
        lights.push_back(&l3);
    } else if (sceneId == 2) {
        shapes.push_back(&dist);
        shapes.push_back(&left);
        shapes.push_back(&right);
        shapes.push_back(&top);
        shapes.push_back(&bot);
        shapes.push_back(&back);
        shapes.push_back(&sph5);
        shapes.push_back(&sph6);

        lights.push_back(&l4);
    } else {
        std::cout << "end." << std::endl;
        return 0;
    }


omp_set_num_threads(numThreads);
#pragma omp parallel for collapse(2)
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