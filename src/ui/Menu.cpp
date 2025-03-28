#include "Menu.h"

void menu(Graph<Location> *cityGraph)
{
    bool menuOpen = true;

    while (menuOpen)
    {
        printMenuOptions();
        switch (int choice = Utils::getUserChoice(0,4))
        {
            case 1:
            {
                Utils::printReport(cityGraph);
                break;
            }

            case 2:
            {
                IndependentRoutePlanning::planDrivingRoute(cityGraph);
                break;
            }

            case 3:
            {
                RestrictedRoutePlanning::planRestrictedRoute(cityGraph);
                break;
            }

            case 4:
            {
                HybridRoutes::planEnvFriendlyRoute(cityGraph);
                break;
            }
            case 0:
            {
                std::cout << "Exiting..." << std::endl;
                menuOpen = false;
                break;
            }
        }
    }
}

void printMenuOptions()
{
    std::cout << "Route Planning Analysis Tool Menu:" << std::endl;
    std::cout << "1. Print All Locations and Edges" << std::endl;
    std::cout << "2. Independent Route Planning" << std::endl;
    std::cout << "3. Restricted Route Planning" << std::endl;
    std::cout << "4. Environmentally-Friendly Route Planning" << std::endl;
    std::cout << "0. Exit" << std::endl;
}
