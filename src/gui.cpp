#include "gui.hpp"
#include <iostream>

GUI::GUI(sf::RenderWindow &window, Config &config) : gui(window)
{
    gui.loadWidgetsFromFile("../../forms/gameForm.txt");

    settingsWindow = gui.get<tgui::ChildWindow>("settingsWindow");
    settingsBtn = gui.get<tgui::Button>("settingsBtn");
    fpsCheckbox = gui.get<tgui::CheckBox>("fpsCheckbox");
    fpsLimitCombo = gui.get<tgui::ComboBox>("fpsLimitCombo");
    resolutionCombo = gui.get<tgui::ComboBox>("resolutionCombo");
    fpsLabel = gui.get<tgui::Label>("fpsLabel");
    fullscreenCheckbox = gui.get<tgui::CheckBox>("fullscreenCheckbox");

    fpsLabel->setVisible(fpsCheckbox->isChecked());

    fpsLimit = config.screen.maxFps;
    windowSize = {config.screen.width, config.screen.height};

    handleCallbacks(window);
}

void GUI::handleEvent(sf::Event event)
{
    gui.handleEvent(event);
}

void GUI::draw()
{
    gui.draw();
}

void GUI::update(int fps)
{
    if (fpsCheckbox->isChecked()) {
        fpsLabel->setText("FPS: " + std::to_string(static_cast<int>(fps)));
    }
}

void GUI::handleCallbacks(sf::RenderWindow &window)
{
    settingsBtn->onPress([this] {
        settingsWindow->setVisible(!settingsWindow->isVisible());
    });

    fpsCheckbox->onChange([this] {
        fpsLabel->setVisible(fpsCheckbox->isChecked());
    });

    fpsLimitCombo->onItemSelect([this, &window] {
        fpsLimit = fpsLimitCombo->getSelectedItem().toInt();
        window.setFramerateLimit(fpsLimit);
    });

    resolutionCombo->onItemSelect([this, &window] {
        std::stringstream ss(resolutionCombo->getSelectedItem().toStdString());

        std::vector<std::string> tokens;
        std::string token;
        while(std::getline(ss, token, 'x'))
        {
            tokens.push_back(token);
        }

        windowSize = {static_cast<unsigned int>(std::stoi(tokens[0])), static_cast<unsigned int>(std::stoi(tokens[1]))};

        window.setSize(windowSize);
        gui.setAbsoluteView({0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    });

    fullscreenCheckbox->onChange([this, &window] {
        if(fullscreenCheckbox->isChecked())
        {
            window.create(sf::VideoMode::getFullscreenModes()[0], "SFML 3.0 RPG", sf::State::Fullscreen);
            window.setFramerateLimit(fpsLimit);
        }
        else
        {
            window.create(sf::VideoMode(windowSize), "SFML 3.0 RPG");
            window.setFramerateLimit(fpsLimit);
        }
        gui.setAbsoluteView({0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    });
}
