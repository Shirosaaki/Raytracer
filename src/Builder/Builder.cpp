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
#include <thread>
#include <vector>
#include <mutex>

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
    // Try to load the plugin manager, but don't fail if it's missing
    primitives::PrimitiveManager *primitiveManager = nullptr;
    
    try {
        auto manager = new tools::DLManager("plugins/primitiveManager.so");
        auto createPrimitiveManager = (primitives::PrimitiveManager *(*)())manager->getFunction("createPrimitiveManager");
        if (createPrimitiveManager)
            primitiveManager = createPrimitiveManager();
    } catch (const tools::Error &e) {
        // Plugin manager not available - continue without it
        // Errors will be thrown only when a primitive actually tries to use it
    }
    
    for (int i = 0; i < primitives->getLength(); ++i) {
        const libconfig::Setting &primitiveList = (*primitives)[i];

        for (int j = 0; j < primitiveList.getLength(); ++j) {
            const libconfig::Setting &primitive = primitiveList[j];
            std::string obj;
            
            if (static_cast<std::string>(primitiveList.getName()) == "spheres")
                obj = "sphere";
            else if (static_cast<std::string>(primitiveList.getName()) == "planes")
                obj = "plane";
            else if (static_cast<std::string>(primitiveList.getName()) == "cubes")
                obj = "cube";
            else if (static_cast<std::string>(primitiveList.getName()) == "pyramids")
                obj = "pyramid";
            else if (static_cast<std::string>(primitiveList.getName()) == "cones")
                obj = "cone";
            else if (static_cast<std::string>(primitiveList.getName()) == "cylinders")
                obj = "cylinder";
            else if (static_cast<std::string>(primitiveList.getName()) == "icosahedrons")
                obj = "icosahedron";
            else if (static_cast<std::string>(primitiveList.getName()) == "ellipsoids")
                obj = "ellipsoid";
            else if (static_cast<std::string>(primitiveList.getName()) == "hemispheres")
                obj = "hemisphere";
            else if (static_cast<std::string>(primitiveList.getName()) == "dodecahedrons")
                obj = "dodecahedron";
            else if (static_cast<std::string>(primitiveList.getName()) == "triangularprisms")
                obj = "triangularprism";
            else if (static_cast<std::string>(primitiveList.getName()) == "toruses")
                obj = "torus";
            else if (static_cast<std::string>(primitiveList.getName()) == "tetrahedrons")
                obj = "tetrahedron";
            else if (static_cast<std::string>(primitiveList.getName()) == "octahedrons")
                obj = "octahedron";
            else if (static_cast<std::string>(primitiveList.getName()) == "pentagrammicprisms")
                obj = "pentagrammicprism";
            else if (static_cast<std::string>(primitiveList.getName()) == "hexagonalpyramids")
                obj = "hexagonalpyramid";
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
                
                if (!primitiveManager) {
                    std::cerr << "Erreur: Plugin manager not loaded, cannot create Sphere primitive" << std::endl;
                    continue;
                }
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
                    
                    if (!primitiveManager) {
                        std::cerr << "Erreur: Plugin manager not loaded, cannot create Plane primitive" << std::endl;
                        continue;
                    }
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
            } else if (obj == "cube" || obj == "pyramid" || obj == "cone" || obj == "cylinder" || 
                       obj == "icosahedron" || obj == "ellipsoid" || obj == "hemisphere" || 
                       obj == "dodecahedron" || obj == "triangularprism" || obj == "torus" || 
                       obj == "tetrahedron" || obj == "octahedron" || obj == "pentagrammicprism" || 
                       obj == "hexagonalpyramid") {
                
                Math::Vector3D position;
                Math::Vector3D scale;
                std::tuple<int, int, int> color;
                std::string mat;

                int x = 0, y = 0, z = 0;
                double sx = 1, sy = 1, sz = 1;
                
                try {
                    if (!primitive.lookupValue("x", x) || !primitive.lookupValue("y", y) || !primitive.lookupValue("z", z)) {
                        std::cerr << "Failed to read position values" << std::endl;
                        continue;
                    }
                    
                    // Optional scale params (default to 1 or use specific ones depending on primitive)
                    // For torus, sx = major radius, sy = minor radius
                    // For spheres/polyhedrons, sx usually acts as radius
                    primitive.lookupValue("sx", sx);
                    primitive.lookupValue("sy", sy);
                    primitive.lookupValue("sz", sz);
                    
                } catch (const libconfig::SettingTypeException &e) {
                    std::cerr << "Type error reading " << obj << " values: " << e.what() << std::endl;
                    continue;
                } catch (const libconfig::SettingNotFoundException &e) {
                    std::cerr << "Setting not found: " << e.what() << std::endl;
                    continue;
                }
                
                position = Math::Vector3D(x, y, z);
                scale = Math::Vector3D(sx, sy, sz);

                const libconfig::Setting &colorSetting = primitive.lookup("color");
                int r, g, b;
                colorSetting.lookupValue("r", r);
                colorSetting.lookupValue("g", g);
                colorSetting.lookupValue("b", b);
                double r255 = r / 255.0;
                double g255 = g / 255.0;
                double b255 = b / 255.0;
                
                std::string className;
                if (obj == "cube") className = "Cube";
                else if (obj == "pyramid") className = "Pyramid";
                else if (obj == "cone") className = "Cone";
                else if (obj == "cylinder") className = "Cylinder";
                else if (obj == "icosahedron") className = "Icosahedron";
                else if (obj == "ellipsoid") className = "Ellipsoid";
                else if (obj == "hemisphere") className = "Hemisphere";
                else if (obj == "dodecahedron") className = "Dodecahedron";
                else if (obj == "triangularprism") className = "TriangularPrism";
                else if (obj == "torus") className = "Torus";
                else if (obj == "tetrahedron") className = "Tetrahedron";
                else if (obj == "octahedron") className = "Octahedron";
                else if (obj == "pentagrammicprism") className = "PentagrammicPrism";
                else if (obj == "hexagonalpyramid") className = "HexagonalPyramid";

                if (!primitiveManager) {
                    std::cerr << "Erreur: Plugin manager not loaded, cannot create " << className << " primitive" << std::endl;
                    continue;
                }
                
                primitives::IPrimitive *item = primitiveManager->createPrimitive(className);
                if (!item) {
                    std::cerr << "Erreur: Impossible de créer une primitive " << className << std::endl;
                    continue;
                }
                
                primitive.lookupValue("mat", mat);
                if (mat == "F") {
                    item->Init(position, scale, new RayTracer::Flat(Math::Vector3D(r255, g255, b255)));
                } else if (mat == "M") {
                    item->Init(position, scale, new RayTracer::Metal(Math::Vector3D(r255, g255, b255), 0.1));
                } else {
                    std::cerr << "Invalid material type" << std::endl;
                    continue;
                }
                loaded_primitives.push_back(item);
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
        Math::Vector3D attenuation(0, 0, 0);
        if (depth < 50 && rec.material && rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        if (rec.material) {
            return attenuation;
        }
        return Math::Vector3D(1.0, 0.0, 0.0);
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

    std::cerr << "DEBUG: Loaded " << loaded_primitives.size() << " primitives\n";
    std::cout << "P3\n" << cam.getWidth() << " " << cam.getHeight() << "\n255\n";
    std::shared_ptr<primitives::IPrimitive> world = std::make_shared<primitives::PrimitivesList>(loaded_primitives.data(), loaded_primitives.size());
    int process = 0;
    std::mutex image_mutex;
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;

    while (1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
        }
        
        std::vector<std::thread> threads;
        std::vector<std::vector<std::string>> pixel_data(cam.getHeight());
        
        // Lambda function to render a row
        auto render_row = [&](int row_idx) {
            std::vector<std::string> row_colors;
            for (int j = 0; j < cam.getWidth(); ++j) {
                Math::Vector3D col(0, 0, 0);
                for (int s = 0; s < ns; ++s) {
                    double u = double(j + drand48()) / double(cam.getWidth());
                    double v = double(row_idx + drand48()) / double(cam.getHeight());
                    RayTracer::Ray r = cam.ray(u, v);
                    col += color(r, world.get(), 0);
                }
                col /= double(ns);
                col = Math::Vector3D(sqrt(col.x), sqrt(col.y), sqrt(col.z));
                int ir = static_cast<int>(255.99 * col.x);
                int ig = static_cast<int>(255.99 * col.y);
                int ib = static_cast<int>(255.99 * col.z);
                
                row_colors.push_back(std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib) + "\n");
                
                {
                    std::lock_guard<std::mutex> lock(image_mutex);
                    image.setPixel(j, cam.getHeight() - row_idx - 1, sf::Color(ir, ig, ib));
                }
            }
            pixel_data[row_idx] = row_colors;
        };
        
        // Launch threads for each row
        for (int i = cam.getHeight() - 1; i >= 0; --i) {
            threads.push_back(std::thread(render_row, i));
            
            // Limit number of concurrent threads
            if (threads.size() >= num_threads) {
                threads[threads.size() - num_threads].join();
                threads.erase(threads.begin());
            }
            
            if ((cam.getHeight() - i) * 100 / cam.getHeight() > process) {
                process = (cam.getHeight() - i) * 100 / cam.getHeight();
                std::cerr << "\rRendering: " << process << "% (using " << num_threads << " threads)" << std::flush;
            }
        }
        
        // Wait for remaining threads
        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }
        
        // Output pixel data
        for (int i = cam.getHeight() - 1; i >= 0; --i) {
            for (const auto& color_str : pixel_data[i]) {
                std::cout << color_str;
            }
        }
        
        // Update texture and display
        texture.update(image);
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
