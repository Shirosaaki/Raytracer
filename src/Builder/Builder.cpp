/*
** EPITECH PROJECT, 2025
** Builder
** File description:
** Builder
*/
#include "Builder.hpp"
#include <iostream>
#include <libconfig.h++>
#include <memory>
#include "../tools/Error.hpp"
#include "../Materials/Flat.hpp"
#include "../Materials/Metal.hpp"
#include "../Primitives/PrimitiveList.hpp"
#include <iomanip>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Builder::Builder(std::string nameFile)
    : root(nullptr), primitives(nullptr), lights(nullptr), camera(nullptr)
{
    try {
        cfg.readFile(nameFile.c_str());
        root = &cfg.getRoot();
        primitives = &root->lookup("primitives");
        lights = &root->lookup("lights");
        camera = &root->lookup("camera");
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "File I/O error: " << fioex.what() << std::endl;
        throw tools::Error(tools::Error::ErrorType::FILE_NOT_FOUND);
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting not found: " << nfex.what() << std::endl;
        throw tools::Error(tools::Error::ErrorType::UNKNOWN_ERROR);
    } catch (const libconfig::ConfigException &cex) {
        std::cerr << "Config error: " << cex.what() << std::endl;
        throw tools::Error(tools::Error::ErrorType::FILE_NOT_FOUND);
    } catch (const tools::Error &e) {
        std::cerr << "Tools error: " << e.what() << std::endl;
        throw tools::Error(tools::Error::ErrorType::UNKNOWN_ERROR);
    }
}

Builder::~Builder()
{
}

void Builder::loadPrimitives()
{
    auto manager = new tools::DLManager("plugins/primitiveManager.so");
    if (!manager->getLibrary())
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_LIBRARY);
    auto createPrimitiveManager = (primitives::PrimitiveManager *(*)())manager->getFunction("createPrimitiveManager");
    if (!createPrimitiveManager)
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_FUNCTION);
    primitives::PrimitiveManager *primitiveManager = createPrimitiveManager();
    
    for (int i = 0; i < primitives->getLength(); ++i) {
        const libconfig::Setting &primitiveList = (*primitives)[i];

        for (int j = 0; j < primitiveList.getLength(); ++j) {
            const libconfig::Setting &primitive = primitiveList[j];
            std::string obj;
            
            if (static_cast<std::string>(primitiveList.getName()) == "spheres")
                obj = "sphere";
            else if (static_cast<std::string>(primitiveList.getName()) == "planes")
                obj = "plane";
            else
                continue;
                
            if (obj == "sphere") {
                Math::Vector3D position;
                double radius;
                std::tuple<int, int, int> color;
                std::string mat;

                int x = 0, y = 0, z = 0, ra = 0;
                try {
                    if (!primitive.lookupValue("x", x)) {
                        std::cerr << "Failed to read x value" << std::endl;
                        continue;
                    }
                    if (!primitive.lookupValue("y", y)) {
                        std::cerr << "Failed to read y value" << std::endl;
                        continue;
                    }
                    if (!primitive.lookupValue("z", z)) {
                        std::cerr << "Failed to read z value" << std::endl;
                        continue;
                    }
                    if (!primitive.lookupValue("r", ra)) {
                        std::cerr << "Failed to read radius value" << std::endl;
                        continue;
                    }
                } catch (const libconfig::SettingTypeException &e) {
                    std::cerr << "Type error reading sphere values: " << e.what() << std::endl;
                    continue;
                } catch (const libconfig::SettingNotFoundException &e) {
                    std::cerr << "Setting not found: " << e.what() << std::endl;
                    continue;
                }
                position = Math::Vector3D(x, y, z);
                radius = ra;

                libconfig::Setting &colorSetting = primitive.lookup("color");
                int r, g, b;
                colorSetting.lookupValue("r", r);
                colorSetting.lookupValue("g", g);
                colorSetting.lookupValue("b", b);
                double r255 = r / 255.0;
                double g255 = g / 255.0;
                double b255 = b / 255.0;
                primitives::IPrimitive *sphere = primitiveManager->createPrimitive("Sphere");
                if (!sphere) {
                    std::cerr << "Erreur: Impossible de créer une primitive Sphere" << std::endl;
                    continue;
                }
                primitive.lookupValue("mat", mat);
                if (mat == "F") {
                    sphere->Init(position, Math::Vector3D(radius, radius, radius), new RayTracer::Flat(Math::Vector3D(r255, g255, b255)));
                } else if (mat == "M") {
                    sphere->Init(position, Math::Vector3D(radius, radius, radius), new RayTracer::Metal(Math::Vector3D(r255, g255, b255), 0.1));
                } else {
                    std::cerr << "Invalid material type" << std::endl;
                    continue;
                }
                loaded_primitives.push_back(sphere);
            } else if (obj == "plane") {
                Math::Vector3D position;
                std::tuple<int, int, int> color;
                std::string axeName;
                Math::Vector3D axis;
                std::string mat;
                int pos = 0;

                try {
                    if (!primitive.lookupValue("axis", axeName)) {
                        std::cerr << "Failed to read axis value" << std::endl;
                        continue;
                    }
                    if (!primitive.lookupValue("position", pos)) {
                        std::cerr << "Failed to read position value" << std::endl;
                        continue;
                    }
                    if (axeName == "X") {
                        axis = Math::Vector3D(1, 0, 0);
                        position = Math::Vector3D(pos, 0, 0);
                    } else if (axeName == "Y") {
                        axis = Math::Vector3D(0, 0, 1);
                        position = Math::Vector3D(0, 0, pos);
                    } else if (axeName == "Z") {
                        axis = Math::Vector3D(0, 1, 0);
                        position = Math::Vector3D(0, pos, 0);
                    } else {
                        std::cerr << "Invalid axis name" << std::endl;
                        continue;
                    }

                    const libconfig::Setting &colorSetting = primitive.lookup("color");
                    int r = 0, g = 0, b = 0;
                    if (!colorSetting.lookupValue("r", r) ||
                        !colorSetting.lookupValue("g", g) ||
                        !colorSetting.lookupValue("b", b)) {
                        std::cerr << "Failed to read color values" << std::endl;
                        continue;
                    }
                    double r255 = r / 255.0;
                    double g255 = g / 255.0;
                    double b255 = b / 255.0;
                    primitives::IPrimitive *plane = primitiveManager->createPrimitive("Plane");
                    if (!plane) {
                        std::cerr << "Erreur: Impossible de créer une primitive Plane" << std::endl;
                        continue;
                    }
                    primitive.lookupValue("mat", mat);
                    if (mat == "F") {
                        plane->Init(position, axis, new RayTracer::Flat(Math::Vector3D(r255, g255, b255)));
                    } else if (mat == "M") {
                        plane->Init(position, axis, new RayTracer::Metal(Math::Vector3D(r255, g255, b255), 1));
                    } else {
                        std::cerr << "Invalid material type" << std::endl;
                        continue;
                    }
                    loaded_primitives.push_back(plane);
                } catch (const libconfig::SettingTypeException &e) {
                    std::cerr << "Type error reading plane values: " << e.what() << std::endl;
                    continue;
                } catch (const libconfig::SettingNotFoundException &e) {
                    std::cerr << "Setting not found: " << e.what() << std::endl;
                    continue;
                }
            } else {
                std::cerr << "Unknown primitive type: " << obj << std::endl;
                continue;
            }
        }
    }
}

void Builder::loadCamera()
{
    int w, h;
    int x, y, z;
    int fov;
    
    const libconfig::Setting& resolution = camera->lookup("resolution");
    resolution.lookupValue("width", w);
    resolution.lookupValue("height", h);

    const libconfig::Setting& position_setting = camera->lookup("position");
    position_setting.lookupValue("x", x);
    position_setting.lookupValue("y", y);
    position_setting.lookupValue("z", z);

    camera->lookupValue("fieldOfView", fov);

    cam = RayTracer::Camera(w, h, x, y, z, fov);
}

void Builder::loadLights()
{
    // at implement
}


Math::Vector3D color(const RayTracer::Ray &r, primitives::IPrimitive *world, int depth)
{
    primitives::HitRecord rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        RayTracer::Ray scattered;
        Math::Vector3D attenuation;
        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        return Math::Vector3D(0, 0, 0);
    }    
    Math::Vector3D unit_direction = r.getDirection();
    double t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * Math::Vector3D(1.0, 1.0, 1.0) + t * Math::Vector3D(0.5, 0.7, 1.0);
}

void Builder::loadScene()
{
    int ns = 100;
    sf::RenderWindow window(sf::VideoMode(cam.getWidth(), cam.getHeight()), "Ray Tracer");
    window.setPosition(sf::Vector2i(0, 0));
    sf::Image image;
    image.create(cam.getWidth(), cam.getHeight(), sf::Color::Black);
    sf::Texture texture;
    texture.create(cam.getWidth(), cam.getHeight());
    sf::Sprite sprite;
    sprite.setTexture(texture);
    srand48(time(NULL));

    std::cout << "P3\n" << cam.getWidth() << " " << cam.getHeight() << "\n255\n";
    std::shared_ptr<primitives::IPrimitive> world = std::make_shared<primitives::PrimitivesList>(loaded_primitives.data(), loaded_primitives.size());
    int process = 0;
    while (1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
        }
        for (int i = cam.getHeight() - 1; i >= 0; --i) {
            if ((cam.getHeight() - i) * 100 / cam.getHeight() > process) {
                process = (cam.getHeight() - i) * 100 / cam.getHeight();
                std::cerr << "\rRendering: " << process << "%" << std::flush;
            }
            for (int j = 0; j < cam.getWidth(); ++j) {
                Math::Vector3D col(0, 0, 0);
                for (int s = 0; s < ns; ++s) {
                    double u = double(j + drand48()) / double(cam.getWidth());
                    double v = double(i + drand48()) / double(cam.getHeight());
                    RayTracer::Ray r = cam.ray(u, v);
                    Math::Vector3D pixel_color = r.at(2.0);
                    col += color(r, world.get(), 0);
                }
                col /= double(ns);
                col = Math::Vector3D(sqrt(col.x), sqrt(col.y), sqrt(col.z));
                int ir = static_cast<int>(255.99 * col.x);
                int ig = static_cast<int>(255.99 * col.y);
                int ib = static_cast<int>(255.99 * col.z);
                std::cout << ir << " " << ig << " " << ib << "\n";
                image.setPixel(j, cam.getHeight() - i, sf::Color(ir, ig, ib));
                texture.update(image);
                window.clear();
                window.draw(sprite);
                window.display();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }

}

void Builder::loadAll()
{
    loadPrimitives();
    loadCamera();
    loadLights();
    loadScene();
}
