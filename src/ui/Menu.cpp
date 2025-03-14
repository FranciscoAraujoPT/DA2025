#include "Menu.h"

void menu(Graph<Location> *cityGraph)
{
    bool menuOpen = true;

    while (menuOpen)
    {
        printMenuOptions();
        switch (int choice = getUserChoice(0,5))
        {
            case 1:
            {
                printReport("Locations", cityGraph);
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
                HybridRoutes::handleEnvFriendlyRoute(cityGraph);
                break;
            }
            case 5:
            {
                std::cout << "Approximate Solution" << std::endl;
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
    std::cout << "1. Print All Locations" << std::endl;
    std::cout << "2. Independent Route Planning" << std::endl;
    std::cout << "3. Restricted Route Planning" << std::endl;
    std::cout << "4. Environmentally-Friendly Route Planning" << std::endl;
    std::cout << "5. Approximate Solution" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

int getUserChoice(int min, int max) {
    int choice;
    while (true) {
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}